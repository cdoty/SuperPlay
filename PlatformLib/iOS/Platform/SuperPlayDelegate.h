// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#import "GLView.h"
#import "GLViewController.h"

@interface SuperPlayDelegate : NSObject<UIApplicationDelegate, UITextFieldDelegate>
{
	@private
		// Window
		UIWindow*			m_pWindow;

		// OpenGL view controller
		GLViewController*	m_pViewController;

		// OpenGL ES based view
		GLView*				m_pView;
}

@end

