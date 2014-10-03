// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#define EGL_EGLEXT_PROTOTYPES
#include <EGL/egl.h>

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
		
		// Get window size
		int getWidth() const {return m_iWidth;}
		int getHeight() const {return m_iHeight;}

		// Get display
		EGLDisplay getDisplay() const {return m_display;}

		// Get surface
		EGLSurface getSurface() const {return m_surface;}

	private:
		// Display
		EGLDisplay	m_display;

		// Surface
		EGLSurface	m_surface;

		// Context
		EGLContext	m_context;

		// Window size
		int			m_iWidth;
		int			m_iHeight;

		// Show mouse
		void showMouse(bool _bShow) const;
};

ENDNAMESPACE
