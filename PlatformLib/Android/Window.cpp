// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "GameHeader.h"
#include "Hardware.h"
#include "Log.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

Window::Window()	:
	m_pDisplay(EGL_NO_DISPLAY),
	m_pSurface(EGL_NO_SURFACE),
	m_pContext(EGL_NO_CONTEXT)
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
	m_pDisplay	= eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if (EGL_NO_DISPLAY == m_pDisplay)
	{
		Log::instance()->logError("Unable to get display");

		return	false;
	}

	EGLint	iMajor;
	EGLint	iMinor;

	if (EGL_FALSE == eglInitialize(m_pDisplay, &iMajor, &iMinor))
	{
		Log::instance()->logError("Unable to initialize EGL");

		return	false;
	}

	EGLint iConfigAttributes[]	=
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	int			iConfigs;

	if (EGL_FALSE == eglChooseConfig(m_pDisplay, iConfigAttributes, &m_config, 1, &iConfigs))
	{
		Log::instance()->logError("Unable to choose config");

		return	false;
	}

	if (EGL_FALSE == eglGetConfigAttrib(m_pDisplay, m_config, EGL_NATIVE_VISUAL_ID, &m_iFormat))
	{
		Log::instance()->logError("Unable to get config attrib");

		return	false;
	}

	m_pContext	= eglCreateContext(m_pDisplay, m_config, NULL, NULL);

	if (EGL_NO_CONTEXT == m_pContext)
	{
		Log::instance()->logError("Unable to create context");

		return	false;
	}

	return	true;
}

void Window::close()
{
	if (m_pDisplay != EGL_NO_DISPLAY)
	{
		releaseContext();

		// Context must be deleted since
		if (m_pContext != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_pContext, m_pContext);
		
			m_pContext	= EGL_NO_CONTEXT;
		}

		eglTerminate(m_pDisplay);
		
		m_pDisplay	= EGL_NO_DISPLAY;
	}
}

bool Window::acquireContext()
{
	if (EGL_NO_SURFACE == m_pSurface)
	{
		ANativeWindow*	pWindow	= Platform::getAndroidApp()->window;

#if defined OUYA || defined GAMESTICK
		if (ANativeWindow_getHeight(pWindow) >= 540)
		{
			ANativeWindow_setBuffersGeometry(pWindow, 960, 540, m_iFormat);
		}

		else
		{
			ANativeWindow_setBuffersGeometry(pWindow, 0, 0, m_iFormat);
		}
#else
		ANativeWindow_setBuffersGeometry(pWindow, 0, 0, m_iFormat);
#endif

		m_pSurface	= eglCreateWindowSurface(m_pDisplay, m_config, pWindow, NULL);

		if (EGL_NO_SURFACE == m_pSurface)
		{
			Log::instance()->logError("Unable to create window surface");

			return	false;
		}
	}

	if (EGL_FALSE == eglMakeCurrent(m_pDisplay, m_pSurface, m_pSurface, m_pContext))
	{
		Log::instance()->logError("Unable to set current context");

		return	false;
    }

	// Set swap interval
	if (EGL_FALSE == eglSwapInterval(m_pDisplay, 60 / gsc_iFrameRate))
	{
		Log::instance()->logError("Unable to set swap interval");
	}

    if (EGL_FALSE == eglQuerySurface(m_pDisplay, m_pSurface, EGL_WIDTH, &m_iWidth))
	{
		Log::instance()->logError("Unable to query surface");

		return	false;
	}

    if (EGL_FALSE == eglQuerySurface(m_pDisplay, m_pSurface, EGL_HEIGHT, &m_iHeight))
	{
		Log::instance()->logError("Unable to query surface");

		return	false;
	}
	
	return	true;
}

void Window::releaseContext()
{
	if (m_pDisplay != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_pDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (m_pSurface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_pDisplay, m_pSurface);
			
			m_pSurface	= EGL_NO_SURFACE;
		}
	}
}

ENDNAMESPACE
