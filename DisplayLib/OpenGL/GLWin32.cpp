// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "GLWin32.h"
#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "Window.h"

#pragma comment(lib, "opengl32.lib")

NAMESPACE(SPlay)

GLPlatform::GLPlatform()	:
	m_hRC(NULL),
	m_hDC(NULL)
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
	if (false == setupPixelFormat())
	{
		return	false;
	}

	if (false == setupWGL())
	{
		return	false;
	}

	return	true;
}

bool GLPlatform::setupPixelFormat()
{
	HWND	hWnd	= Platform::getWindow()->getHwnd();
	
	PIXELFORMATDESCRIPTOR	PixelFormatDescriptor	=
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	m_hDC	= GetDC(Platform::getWindow()->getHwnd());

	if (NULL == m_hDC)
	{
		Log::instance()->logError("Unable to get device context (%08X)", GetLastError());

		return	false;
	}

	int	iPixelFormat	= ChoosePixelFormat(m_hDC, &PixelFormatDescriptor);

	if (0 == iPixelFormat)
	{
		Log::instance()->logError("Unable to choose pixel format (%08X)", GetLastError());

		return	false;
	}

	if (FALSE == SetPixelFormat(m_hDC, iPixelFormat, &PixelFormatDescriptor))
	{
		Log::instance()->logError("Unable to set pixel format (%08X)", GetLastError());

		return	false;
	}
	
	return	true;
}

bool GLPlatform::setupWGL()
{
	m_hRC	= wglCreateContext(m_hDC);

	if (NULL == m_hRC)
	{
		Log::instance()->logError("Unable to create context (%08X)", GetLastError());

		return	false;
	}

	if (FALSE == wglMakeCurrent(m_hDC, m_hRC))
	{
		Log::instance()->logError("Unable to set current context (%08X)", GetLastError());

		return	false;
	}
	
	return	true;
}

void GLPlatform::close()
{	
	if (m_hRC != NULL)
	{
		wglMakeCurrent(NULL, NULL);
	
		wglDeleteContext(m_hRC);

		m_hRC	= NULL;
	}

	if (m_hDC != NULL)
	{
		ReleaseDC(Platform::getWindow()->getHwnd(), m_hDC);

		m_hDC	= NULL;
	}
}

bool GLPlatform::swapBuffers()
{
	if (FALSE == SwapBuffers(m_hDC))
	{
		return	false;
	}

	return	true;
}

ENDNAMESPACE
