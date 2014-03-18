// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

#import "DuoGamerSDK.h"
#import "iMpulseReaderView.h"

//#define	ARCADIE

#ifdef ARCADIE
// Number of arcadie buttons
static const int gsc_iArcadieButtons	= 6;
#endif

@interface GLView : UIView
{
	@public
		// Impulse
		iMpulseReaderView*	m_pImpulse;

		// Duo gamer interface
		DuoGamer*			m_pDuoGamer;

	@private
		// Context
		EAGLContext*		m_pContext;

		// Current time
		float				m_fCurrentTime;

#ifdef ARCADIE
		// Button rects
		CGRect				m_rctButtons[gsc_iArcadieButtons];

		// Arcadie input
		uint32_t		    m_arcadieInput;
#endif
}

- (void) drawView: (CADisplayLink*)displayLink;
//- (void) didRotate: (NSNotification*)notification;

#ifdef ARCADIE
// Setup arcadie
- (void) setupArcadie;
#endif

// Update impulse
- (uint32_t) updateImpulse;

// Update duo gamer
- (uint32_t) updateDuoGamer;

@end
