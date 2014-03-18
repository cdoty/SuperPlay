//
// DuoGamerSDK 
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


#pragma once
#import <ExternalAccessory/ExternalAccessory.h>

typedef struct DuoGamerState {
    int8_t analogLeftX;
    int8_t analogLeftY;
    BOOL   analogLeftClick;

    int8_t analogRightX;
    int8_t analogRightY;
    BOOL   analogRightClick;

    BOOL dpadLeft;
    BOOL dpadRight;
    BOOL dpadUp;
    BOOL dpadDown;

    BOOL buttonA;
    BOOL buttonB;
    BOOL buttonX;
    BOOL buttonY;

    BOOL shoulderLeft;
    BOOL shoulderRight;
} DuoGamerState;

@protocol DuoGamerDelegate
-(void) connected;
-(void) handleState:(DuoGamerState*)state;
-(void) disconnected;
@end

@interface DuoGamer : NSObject <EAAccessoryDelegate, NSStreamDelegate>{
    EAAccessory * accessory;
    EASession * session;
    NSMutableData * readData;
    DuoGamerState	state;
}

@property (nonatomic, retain) EAAccessory * accessory;
@property (nonatomic, retain) EASession * session;
@property (nonatomic, assign) NSObject<DuoGamerDelegate> *delegate;
@property (nonatomic) DuoGamerState state;

@end
