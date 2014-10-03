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
#include "GLNaCl.h"
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
	return	true;
}

void GLPlatform::close()
{
}

bool GLPlatform::swapBuffers()
{
	return	true;
}

ENDNAMESPACE
