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

		// Acquire context
		bool acquireContext();

		// Release context
		void releaseContext();

		// Get size
		int getWidth() {return m_iWidth;}
		int getHeight() {return m_iHeight;}

	private:
		// Size
		int	m_iWidth;
		int	m_iHeight;

		// Format
		int	m_iFormat;

		// Config
		EGLConfig	m_config;
	
		// Display
		EGLDisplay	m_pDisplay;

		// Surface
		EGLSurface	m_pSurface;

		// Context
		EGLContext	m_pContext;
};

ENDNAMESPACE
