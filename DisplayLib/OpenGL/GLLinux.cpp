// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "GLLinux.h"
#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "Window.h"

NAMESPACE(SPlay)

GLPlatform::GLPlatform()
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
	if (false == setupXGL())
	{
		return	false;
	}

	return	true;
}

bool GLPlatform::setupXGL()
{
	Window* pWindow	= Platform::getWindow();
	
	Display*	pDisplay	= pWindow->getDisplay();
	
	m_context	= glXCreateNewContext(pDisplay, pWindow->getFBConfig()[0], GLX_RGBA_TYPE, NULL, GL_TRUE);
		
	GLenum	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create new context %d", error);

		return	false;
	}

	XSync(pDisplay, false);

	glXMakeCurrent(pDisplay, pWindow->getWindow(), m_context);
	
	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create new context %d", error);

		return	false;
	}

	return	true;
}

void GLPlatform::close()
{
	Display*	pDisplay	= Platform::getWindow()->getDisplay();
	
	glXMakeCurrent(pDisplay, 0, 0);
	glXDestroyContext(pDisplay, m_context);
}

bool GLPlatform::swapBuffers()
{
	Window* pWindow	= Platform::getWindow();
	
	glXSwapBuffers(pWindow->getDisplay(), pWindow->getWindow());
	
	return	true;
}

ENDNAMESPACE
