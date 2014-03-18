//
// 
//

/*
 * Copyright (C) 2013 by Matthias Ringwald
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MATTHIAS RINGWALD AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#import "DuoGamerSDK.h"

NSString * duoGamerProtocolString = @"com.discoverybaygames.v2";
NSString * duoGamerName = @"Duo Gamer";

@interface NSString (BTstack)
+(NSString*) stringForData:(const uint8_t*) data withSize:(uint16_t) size;
@end


@interface DuoGamer (private)
-(void) openSession:(EAAccessory *) accessor;
- (void)closeSession;
@end

static inline BOOL isBitSet(int data, int bit){
    if (data & (1<<bit)) return 1;
    return 0;
}

@implementation NSString (BTstatck)
+(NSString*) stringForData:(const uint8_t*) data withSize:(uint16_t) size{
    NSMutableString *output = [NSMutableString stringWithCapacity:size * 3];
    for(int i = 0; i < size; i++){
        [output appendFormat:@"%02x ",data[i]];
    }
    return output;
}
@end


@implementation DuoGamer
@synthesize accessory;
@synthesize session;
@synthesize delegate;
@synthesize state;

-(id) init {
    self = [super init];

    readData = [[NSMutableData alloc] init];

    // try to find already connected accessory
    NSArray * accessories = [[EAAccessoryManager sharedAccessoryManager] connectedAccessories];
    for (EAAccessory * connectedAccessory in accessories){
        if (![connectedAccessory.name hasPrefix:duoGamerName]) continue;
        [self openSession:connectedAccessory];
    }

    // register for notifications
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(_accessoryDidConnect:) name:EAAccessoryDidConnectNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(_accessoryDidDisconnect:) name:EAAccessoryDidDisconnectNotification object:nil];
    [[EAAccessoryManager sharedAccessoryManager] registerForLocalNotifications];

    return self;
}

-(void) dealloc {
    self.delegate = nil;
    [self closeSession];

    // unregister from notifications
    [[EAAccessoryManager sharedAccessoryManager] unregisterForLocalNotifications];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EAAccessoryDidConnectNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EAAccessoryDidDisconnectNotification object:nil];

    [super dealloc];
}

-(void) openSession:(EAAccessory *) connectedAccessory{

    if (accessory){
        NSLog(@"DuoGamer: already connected");
    }

    self.accessory = connectedAccessory;
    [accessory setDelegate:self];

    self.session = [[EASession alloc] initWithAccessory:accessory forProtocol:duoGamerProtocolString];

    if (!session) {
        NSLog(@"DuoGamer: creating session failed");
        self.accessory = nil;
        return;
    }

    [[session inputStream] setDelegate:self];
    [[session inputStream] scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [[session inputStream] open];

    if ([delegate respondsToSelector:@selector(connected)]){
        [delegate connected];
    }
}

// close the session with the accessory.
- (void)closeSession
{
    [[session inputStream] close];
    [[session inputStream] removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [[session inputStream] setDelegate:nil];

    [session release];
    session = nil;

    [readData release];
    readData = nil;

    if ([delegate respondsToSelector:@selector(disconnected)]){
        [delegate disconnected];
    }
}

- (void)_accessoryDidConnect:(NSNotification *)notification {
    EAAccessory *connectedAccessory = [[notification userInfo] objectForKey:EAAccessoryKey];
    [self openSession:connectedAccessory];
}

- (void)_accessoryDidDisconnect:(NSNotification *)notification {
    EAAccessory *disconnectedAccessory = [[notification userInfo] objectForKey:EAAccessoryKey];
    if (accessory.connectionID != disconnectedAccessory.connectionID) return;
    self.accessory = nil;
}

-(void)processPacket{

    // valid fixed data, but ignore xor checksum
    uint8_t * data = (uint8_t*) [readData bytes];
    if (data[0] != 0x5a) return;
    if (data[1] != 0xa5) return;
    if (data[2] != 0x04) return;
    if (data[9] != 0x00) return;

    uint8_t buttons_1      = data[3];
    uint8_t buttons_2      = data[4];
    state.buttonA          = isBitSet(buttons_1, 0);
    state.buttonB          = isBitSet(buttons_1, 1);
    state.buttonY          = isBitSet(buttons_1, 2);
    state.buttonX          = isBitSet(buttons_1, 3);
    state.analogLeftClick  = isBitSet(buttons_1, 5);
    state.analogRightClick = isBitSet(buttons_1, 6);
    state.shoulderRight    = isBitSet(buttons_2,  0);
    state.shoulderLeft     = isBitSet(buttons_2,  1);
    state.dpadUp           = isBitSet(buttons_2,  2);
    state.dpadRight        = isBitSet(buttons_2,  3);
    state.dpadDown         = isBitSet(buttons_2,  4);
    state.dpadLeft         = isBitSet(buttons_2,  5);
    state.analogLeftX      = data[5] - 0x80;
    state.analogLeftY      = data[6] - 0x80;
    state.analogRightX     = data[7] - 0x80;
    state.analogRightY     = data[8] - 0x80;

    if (![delegate respondsToSelector:@selector(handleState:)]) return;
    [delegate handleState:&state];
}

// asynchronous NSStream handleEvent method
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode
{
    if (eventCode != NSStreamEventHasBytesAvailable) return;

    #define EAD_INPUT_BUFFER_SIZE 128
    uint8_t buf[EAD_INPUT_BUFFER_SIZE];
    while ([[session inputStream] hasBytesAvailable])
    {
        NSInteger bytesRead = [[session inputStream] read:buf maxLength:EAD_INPUT_BUFFER_SIZE];
        [readData appendBytes:(void *)buf length:bytesRead];
    }

    if ([readData length] == 11){
        [self processPacket];        
        // NSLog(@"Read data (%u): %@", [readData length],
        //   [NSString stringForData:(const uint8_t*)[readData bytes] withSize:[readData length]] );
    }  

    // reset buffer - assumption: controller packet arrives in a single RFCOMM packet
    [readData setLength:0];
}

@end
// vim:ft=objc
