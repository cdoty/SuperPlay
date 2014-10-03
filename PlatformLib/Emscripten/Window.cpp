// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <emscripten.h>
#include <GLES/gl.h>

#include "GameHeader.h"
#include "Image.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

Window::Window()	:
	m_display(EGL_NO_DISPLAY),
	m_surface(EGL_NO_SURFACE),
	m_context(EGL_NO_CONTEXT)
{
}

Window::~Window()
{
	close();
}

Window* Window::create()
{
	Window*	pWindow	= new Window();
	
	if (false == pWindow->initialize())
	{
		delete	pWindow;
		
		pWindow	= NULL;
	}	
	
	return	pWindow;
}

bool Window::initialize()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	m_iWidth	= gameHeader.iWindowedWidth;
	m_iHeight	= gameHeader.iWindowedHeight;

	emscripten_set_canvas_size(m_iWidth, m_iHeight);

	m_display	= eglGetDisplay(EGL_DEFAULT_DISPLAY);
	
	if (EGL_NO_DISPLAY == m_display)
	{
		Log::instance()->logError("Failed to get a display");

		return	false;
	}

	EGLint	iMajor;
	EGLint	iMinor;

	if (EGL_FALSE == eglInitialize(m_display, &iMajor, &iMinor))
	{
		Log::instance()->logError("Failed to initialize EGL");

		return	false;
	}

	EGLint iConfigAttributes[]	=
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
 		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	EGLConfig	config;
	int			iConfigs;

	if (EGL_FALSE == eglChooseConfig(m_display, iConfigAttributes, &config, 1, &iConfigs))
	{
		Log::instance()->logError("Failed to find a valid config");

		return	false;
	}

	m_surface = eglCreateWindowSurface(m_display, config, NULL, NULL);

	if (EGL_NO_SURFACE == m_surface)
	{
		Log::instance()->logError("Failed to create window surface");

		return	false;
	}

	EGLint iContextAttributes[]	=
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	m_context	= eglCreateContext(m_display, config, EGL_NO_CONTEXT, iContextAttributes);

	if (EGL_NO_CONTEXT == m_context)
	{
		Log::instance()->logError("Failed to create a context");

		return	false;
	}

	if (EGL_FALSE == eglMakeCurrent(m_display, m_surface, m_surface, m_context))
	{
		Log::instance()->logError("Failed set current context");

		return	false;
	}

	GLenum	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("EGL errors %d", error);

		return	false;
	}

	showMouse(false);

	return	true;
}

void Window::close()
{
	showMouse(true);
}

void Window::showMouse(bool _bShow) const
{
}

ENDNAMESPACE
