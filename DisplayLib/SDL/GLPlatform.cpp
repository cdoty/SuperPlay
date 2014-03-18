// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "GLPlatform.h"
#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "Window.h"

#ifdef WIN32
#pragma comment(lib, "opengl32.lib")
#endif

NAMESPACE(SPlay)

GLPlatform::GLPlatform()	:
	m_glContext(NULL)
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
	Window*	pWindow	= Platform::getWindow();

	SDL_Window*	pSDLWindow	= pWindow->getWindow();

	m_glContext	= SDL_GL_CreateContext(pSDLWindow);

	if (NULL == m_glContext)
	{
		Log::instance()->logError("Unable to create context");

		return	false;
	}
	 
	if (SDL_GL_MakeCurrent(pSDLWindow, m_glContext) != 0)
	{
		Log::instance()->logError("Unable to set current context");

		return	false;
	}

	SDL_GL_SetSwapInterval(1);

	return	true;
}

void GLPlatform::close()
{
	if (m_glContext != NULL)
	{
		SDL_GL_DeleteContext(m_glContext);
	}
}

bool GLPlatform::swapBuffers()
{
	Window*	pWindow	= Platform::getWindow();

	SDL_GL_SwapWindow(pWindow->getWindow());

	return	true;
}

ENDNAMESPACE
