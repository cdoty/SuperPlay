// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <SDL2/SDL.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "Macros.h"

NAMESPACE(SPlay)

class Window
{
	public:
		// Constructor
		Window();

		// Destructor
		~Window();

		// Create
		static Window* create();
		
		// Initialize
		bool initialize();
		
		// Close
		void close();

		// Get display
		Display* getDisplay() const {return m_pDisplay;}
		
		// Get window
		::Window getWindow() const {return m_window;}
		
		// Get fb config
		GLXFBConfig* getFBConfig() const {return m_pFBConfig;}
		
	private:
		// X Windows Display
		Display*		m_pDisplay;

		// Window
		::Window		m_window;
		
		// Visual info
		GLXFBConfig*	m_pFBConfig;
		
		// Colormap
		Colormap		m_colormap;
		
		// SDL window
		SDL_Window*		m_pSDLWindow;
		
		// Resize client area
		void resizeClientArea();
};

ENDNAMESPACE
