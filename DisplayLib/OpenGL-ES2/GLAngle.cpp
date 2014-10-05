// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "Display.h"
#include "GLAngle.h"
#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "Window.h"

NAMESPACE(SPlay)

GLPlatform::GLPlatform()	:
	m_pDisplay(EGL_NO_DISPLAY),
	m_pSurface(EGL_NO_SURFACE),
	m_pContext(EGL_NO_CONTEXT),
	m_eRendererType(RENDERER_D3D9)
{
}

GLPlatform::~GLPlatform()
{
}

GLPlatform* GLPlatform::create()
{
	GLPlatform*	pGLPlatform	= new GLPlatform();

	if (false == pGLPlatform->initialize())
	{
		delete	pGLPlatform;

		pGLPlatform	= NULL;
	}

	return	pGLPlatform;
}

bool GLPlatform::initialize()
{
	if (false == initializeEGL())
	{
		return	false;
	}

	return	true;
}

void GLPlatform::close()
{
}

bool GLPlatform::swapBuffers()
{
	Window*	pWindow	= Platform::getWindow();

	eglSwapBuffers(m_pDisplay, m_pSurface);

	return	true;
}

bool GLPlatform::initializeEGL()
{
	HWND	hWnd	= Platform::getWindow()->getHwnd();
	HDC		hDC		= GetDC(hWnd);

	if (NULL == hDC)
	{
		Log::instance()->logError("HDC is invalid");

		return	false;
	}

	EGLNativeDisplayType	displayType	= hDC;

	if (RENDERER_D3D11 == m_eRendererType)
	{
		displayType	= EGL_D3D11_ONLY_DISPLAY_ANGLE;
	}

	m_pDisplay	= eglGetDisplay(displayType);
	
	if (EGL_NO_DISPLAY == m_pDisplay)
	{
		m_pDisplay	= eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}
	
	eglBindAPI(EGL_OPENGL_ES_API);

	if (eglGetError() != EGL_SUCCESS)
	{
		Log::instance()->logError("Unable to bind OpenGL ES api: %d", eglGetError());

		return	false;
	}

	EGLint	iMajor;
	EGLint	iMinor;

	if (EGL_FALSE == eglInitialize(m_pDisplay, &iMajor, &iMinor))
	{
		Log::instance()->logError("Unable to initialize EGL %d", eglGetError());

		return	false;
	}

	const EGLint iConfigAttributes[]	=
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_NONE
	};

	EGLConfig	config;
	int			iConfigs;

	if (false == eglChooseConfig(m_pDisplay, iConfigAttributes, &config, 1, &iConfigs))
	{
		Log::instance()->logError("Unable to choose config %d", eglGetError());

		return	false;
	}

	const EGLint iSurfaceAttributes[]	=
	{
        EGL_POST_SUB_BUFFER_SUPPORTED_NV, EGL_TRUE,
        EGL_NONE, EGL_NONE
	};

	m_pSurface	= eglCreateWindowSurface(m_pDisplay, config, (EGLNativeWindowType)hWnd, iSurfaceAttributes);

	if (EGL_NO_SURFACE == m_pSurface)
	{
		eglGetError(); // Clear error and try again
		
		m_pSurface	= eglCreateWindowSurface(m_pDisplay, config, NULL, NULL);
	}

	if (eglGetError() != EGL_SUCCESS)
	{
		Log::instance()->logError("Unable to create window surface %d", eglGetError());

		return	false;
	}

	EGLint iContextAttibutes[]	=
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	m_pContext	= eglCreateContext(m_pDisplay, config, NULL, iContextAttibutes);

	if (eglGetError() != EGL_SUCCESS)
	{
		Log::instance()->logError("Unable to create context %d", eglGetError());

		return	false;
	}

	eglMakeCurrent(m_pDisplay, m_pSurface, m_pSurface, m_pContext);
	
	if (eglGetError() != EGL_SUCCESS)
	{
		Log::instance()->logError("Unable to set current context %d", eglGetError());

		return false;
	}

	return	true;
}

ENDNAMESPACE
