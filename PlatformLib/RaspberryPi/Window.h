// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <EGL/egl.h>
#include <SDL2/SDL.h>

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
		EGLDisplay getDisplay() {return m_pDisplay;}

		// Get surface
		EGLSurface getSurface() {return m_pSurface;}

		// Get window
		EGL_DISPMANX_WINDOW_T getWindow() {return m_window;}
		
	private:
		// Display
		EGLDisplay				m_pDisplay;

		// Surface
		EGLSurface				m_pSurface;

		// Context
		EGLContext				m_pContext;

		// SDL window
		SDL_Window*				m_pSDLWindow;

		// Window
		EGL_DISPMANX_WINDOW_T	m_window;
};

ENDNAMESPACE
