// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#import "SuperPlayDelegate.h"
#import "DuoGamerSDK.h"
#import "Input.h"
#import "Joypad.h"
#import "System.h"

@implementation SuperPlayDelegate

- (void) applicationDidFinishLaunching: (UIApplication*)_pApplication
{
    CGRect	screenBounds	= [[UIScreen mainScreen] bounds];
    
    m_pWindow			= [[UIWindow alloc] initWithFrame:screenBounds];
    m_pView				= [[GLView alloc] initWithFrame:screenBounds];
	m_pViewController   = [[GLViewController alloc] init];

	m_pWindow.rootViewController	= m_pViewController;

	m_pViewController.view	= m_pView;

    [m_pWindow addSubview:m_pView];
    [m_pWindow makeKeyAndVisible];

	[m_pViewController.view addSubview:m_pView->m_pImpulse];

#if 0
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];
#endif
}

- (void) dealloc
{
	SPlay::System::close();

	[m_pViewController release];
    [m_pView release];
    [m_pWindow release];

    [super dealloc];
}

@end
