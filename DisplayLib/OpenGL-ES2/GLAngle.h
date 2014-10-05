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
#include <EGL/eglext.h>

NAMESPACE(SPlay)

enum RendererType
{
    RENDERER_D3D9,
    RENDERER_D3D11
};

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
		// Display
		EGLDisplay		m_pDisplay;

		// Surface
		EGLSurface		m_pSurface;

		// Context
		EGLContext		m_pContext;

		// Renderer type
		RendererType	m_eRendererType;

		// Initialize EGL
		bool initializeEGL();
};

ENDNAMESPACE
