// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>

NAMESPACE(SPlay)

class GLPlatform
{
	public:
		// Constructor
		GLPlatform();

		// Destructor
		virtual ~GLPlatform();

		// Create
		static GLPlatform* create();

		// Initialize
		bool initialize();

		// Close platform
		void close();

		// Render
		bool swapBuffers();

	private:
		// Render context
		HGLRC	m_hRC;

		// Device context
		HDC		m_hDC;

		// Setup pixel format
		bool setupPixelFormat();

		// Setup WGL
		bool setupWGL();
};

ENDNAMESPACE
