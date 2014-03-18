// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#import <OpenGLES/ES2/gl.h>

#import "GLView.h"
#import "Input.h"
#import "Joypad.h"
#import "Log.h"
#import "Platform.h"
#include "System.h"

//#define USE_16BIT

#ifdef ARCADIE
static const uint32_t	gsc_uButtons[gsc_iArcadieButtons]	=
{
	SPlay::IK_PAD_LEFT,
	SPlay::IK_PAD_DOWN,
	SPlay::IK_A,
	SPlay::IK_PAD_UP,
	SPlay::IK_PAD_RIGHT,
	SPlay::IK_B
};
#endif

// Gamepad dead zone
static const int	gsc_iGamepadDeadZone	= 8;

@implementation GLView

+ (Class) layerClass
{
	return	[CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect)frame
{
	if (self = [super initWithFrame:frame])
	{
		CAEAGLLayer* pEAGLLayer	= (CAEAGLLayer*)super.layer;

		// Disable layer transparency
		pEAGLLayer.opaque				= YES;

		pEAGLLayer.drawableProperties	= [NSDictionary dictionaryWithObjectsAndKeys:
			[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking,
#ifdef USE_16BIT
		   kEAGLColorFormatRGB565, kEAGLDrawablePropertyColorFormat,
#else
		   kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
#endif
		   nil];

		// Create an OpenGL ES 1.1 context
		m_pContext	= [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];

		if (!m_pContext || ![EAGLContext setCurrentContext:m_pContext])
		{
			SPlay::Log::instance()->logError("Unable to create a context");

			[self release];

			return	nil;
		}

		// Create the render buffer, in C++ code
		if (false == SPlay::Platform::createRenderBuffer())
		{
			return	nil;
		}

		// Set the render buffer, from the current context and layer.
		[m_pContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:pEAGLLayer];

		// Setup the render buffer in C++ code
		if (false == SPlay::Platform::setupRenderBuffer())
		{
			return	nil;
		}

		NSString*	resourcePath	= [[NSBundle mainBundle] resourcePath];
		const char*	szResourcePath	= [resourcePath cStringUsingEncoding:1];

		SPlay::Platform::setResourcePath(szResourcePath);

		if (false == initialize(CGRectGetWidth(frame), CGRectGetHeight(frame)))
		{
			SPlay::Log::instance()->logError("Unable to initialize Super Play");

			[self release];

			return	nil;
		}

		// CADisplayLink calls a function when the display is ready to be redraw
		CADisplayLink*	pDisplayLink	= [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];

		// Set up for 60 fps. (60 / x)
		pDisplayLink.frameInterval	= 1;

		[pDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

		// Start the elapsed time measurement at the current time value.
		m_fCurrentTime	= CACurrentMediaTime();

#ifndef ARCADIE
		// Create Duo gamer interface
		m_pDuoGamer	= [DuoGamer new];
		
		// Create iMPulse controller view
		m_pImpulse	= [[iMpulseReaderView  alloc] initWithFrame:CGRectZero];
		
		m_pImpulse.active	= YES;
#endif
		
#ifdef ARCADIE
		[self setupArcadie];
#endif
	}

	return	self;
}

- (void) dealloc
{
	if (m_pContext == [EAGLContext currentContext])
	{
		[EAGLContext setCurrentContext:nil];

		[m_pContext release];
	}

#ifndef ARCADIE
	[m_pDuoGamer dealloc];

	[m_pImpulse release];
#endif
	
 	[super dealloc];
}

- (void) drawView: (CADisplayLink*)pDisplayLink
{
	[EAGLContext setCurrentContext:m_pContext];
	 
	if (pDisplayLink != nil)
	{
        float	_fElapsed	= pDisplayLink.timestamp - m_fCurrentTime;

        m_fCurrentTime	= pDisplayLink.timestamp;

#ifdef ARCADIE
		uint32_t uInput	= m_arcadieInput;
#else
		uint32_t uInput	= [self updateImpulse] | [self updateDuoGamer];
#endif
		SPlay::Input*	pInput	= (SPlay::Input*)SPlay::System::getInput();

		pInput->setInput(uInput);

		SPlay::Platform::update(_fElapsed);
	}

	[m_pContext presentRenderbuffer:GL_RENDERBUFFER];
}

#ifdef ARCADIE
- (void) setupArcadie
{
	int	iX		= 2;
	int	iXSpace	= 110;
	int	iY		= 324;
	int	iYSpace	= 86;
	int iWidth	= 86;
	int iHeight	= 88;

	// Set up button rects
	m_rctButtons[0]	= CGRectMake(iX, iY, iWidth, iHeight);
	m_rctButtons[1]	= CGRectMake(iX + iXSpace, iY, iWidth, iHeight);
	m_rctButtons[2]	= CGRectMake(iX + iXSpace * 2, iY, iWidth, iHeight);
	m_rctButtons[3]	= CGRectMake(iX, iY + iYSpace, iWidth, iHeight);
	m_rctButtons[4]	= CGRectMake(iX + iXSpace, iY + iYSpace, iWidth, iHeight);
	m_rctButtons[5]	= CGRectMake(iX + iXSpace * 2, iY + iYSpace, iWidth, iHeight);

	// Setup touch
	self.userInteractionEnabled	= YES;
	self.multipleTouchEnabled	= YES;
	self.exclusiveTouch			= NO;
}

- (void)touchHandler:(NSSet*)_pTouches withEvent:(UIEvent*)_pEvent
{
	m_arcadieInput	= 0;

	NSSet*	pAllTouches	= [_pEvent allTouches];

	for (UITouch* pTouch in pAllTouches)
	{
		if (nil == pTouch)
		{
			continue;
		}

		if (UITouchPhaseBegan == pTouch.phase || UITouchPhaseMoved == pTouch.phase || UITouchPhaseStationary == pTouch.phase)
		{
			CGPoint	ptLocation	= [pTouch locationInView:self];

			for (int iLoop = 0; iLoop < gsc_iArcadieButtons; ++iLoop)
			{
				if (CGRectContainsPoint(m_rctButtons[iLoop], ptLocation))
				{
					m_arcadieInput	|= gsc_uButtons[iLoop];
				}
			}
		}
	}
}

- (void)touchesBegan:(NSSet*)_pTouches withEvent:(UIEvent*)_pEvent
{
	[self touchHandler:_pTouches withEvent:_pEvent];
}

- (void)touchesMoved:(NSSet*)_pTouches withEvent:(UIEvent*)_pEvent
{
	[self touchHandler:_pTouches withEvent:_pEvent];
}

- (void)touchesEnded:(NSSet*)_pTouches withEvent:(UIEvent*)_pEvent
{
	[self touchHandler:_pTouches withEvent:_pEvent];
}

- (void)touchesCancelled:(NSSet *)_pTouches withEvent:(UIEvent *)_pEvent
{
	[self touchHandler:_pTouches withEvent:_pEvent];
}
#endif

- (uint32_t) updateImpulse
{
	uint32_t uInput	= 0;

	if (m_pImpulse.iMpulseState & iMpulseButton1V)
	{
		uInput	|= SPlay::IK_A;
	}

	if (m_pImpulse.iMpulseState & iMpulseButton1W)
	{
		uInput	|= SPlay::IK_B;
	}

	if (m_pImpulse.iMpulseState & iMpulseButton1M)
	{
		uInput	|= SPlay::IK_X;
	}

	if (m_pImpulse.iMpulseState & iMpulseButton1A)
	{
		uInput	|= SPlay::IK_Y;
	}

	if (m_pImpulse.iMpulseState & iMpulseButton1u)
	{
		uInput	|= SPlay::IK_SELECT;
	}

	if (m_pImpulse.iMpulseState & iMpulseButton1n)
	{
		uInput	|= SPlay::IK_START;
	}

	if (m_pImpulse.iMpulseState & iMpulseJoystickUp)
	{
		uInput	|= SPlay::IK_PAD_UP;
	}

	else if (m_pImpulse.iMpulseState & iMpulseJoystickDown)
	{
		uInput	|= SPlay::IK_PAD_DOWN;
	}

	if (m_pImpulse.iMpulseState & iMpulseJoystickLeft)
	{
		uInput	|= SPlay::IK_PAD_LEFT;
	}

	else if (m_pImpulse.iMpulseState & iMpulseJoystickRight)
	{
		uInput	|= SPlay::IK_PAD_RIGHT;
	}

	return uInput;
}

- (uint32_t) updateDuoGamer
{
	UInt32	uInput	= 0;

	if (TRUE == m_pDuoGamer.state.buttonA)
	{
		uInput	|= SPlay::IK_B;
	}

	if (TRUE == m_pDuoGamer.state.buttonB)
	{
		uInput	|= SPlay::IK_A;
	}

	if (TRUE == m_pDuoGamer.state.buttonY)
	{
		uInput	|= SPlay::IK_X;
	}

	if (TRUE == m_pDuoGamer.state.buttonX)
	{
		uInput	|= SPlay::IK_Y;
	}

	if (TRUE == m_pDuoGamer.state.shoulderLeft)
	{
		uInput	|= SPlay::IK_L;
	}

	if (TRUE == m_pDuoGamer.state.shoulderRight)
	{
		uInput	|= SPlay::IK_R;
	}

	if (TRUE == m_pDuoGamer.state.analogLeftClick)
	{
		uInput	|= SPlay::IK_SELECT;
	}

	if (TRUE == m_pDuoGamer.state.analogRightClick)
	{
		uInput	|= SPlay::IK_START;
	}

	if (TRUE == m_pDuoGamer.state.dpadLeft)
	{
		uInput	|= SPlay::IK_PAD_LEFT;
	}

	else if (TRUE == m_pDuoGamer.state.dpadRight)
	{
		uInput	|= SPlay::IK_PAD_RIGHT;
	}

	if (TRUE == m_pDuoGamer.state.dpadUp)
	{
		uInput	|= SPlay::IK_PAD_UP;
	}

	else if (TRUE == m_pDuoGamer.state.dpadDown)
	{
		uInput	|= SPlay::IK_PAD_DOWN;
	}

	int8_t iCurrentX	= m_pDuoGamer.state.analogLeftX;

	if (iCurrentX <= -gsc_iGamepadDeadZone)
	{
		uInput	|= SPlay::IK_PAD_LEFT;
	}

	else if (iCurrentX >= gsc_iGamepadDeadZone)
	{
		uInput	|= SPlay::IK_PAD_RIGHT;
	}

	int8_t iCurrentY	= m_pDuoGamer.state.analogLeftY;

	if (iCurrentY <= -gsc_iGamepadDeadZone)
	{
		uInput	|= SPlay::IK_PAD_UP;
	}

	else if (iCurrentY >= gsc_iGamepadDeadZone)
	{
		uInput	|= SPlay::IK_PAD_DOWN;
	}

	return	uInput;
}

@end
