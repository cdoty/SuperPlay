// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <time.h>

#include "AssertLog.h"
#include "Display.h"
#include "GameHeader.h"
#include "Input.h"
#include "Log.h"
#include "Platform.h"
#include "PlatformLib.h"
#include "Sound.h"
#include "System.h"

NAMESPACE(SPlay)

RenderBuffer*	Platform::ms_pRenderBuffer	= NULL;
int				Platform::ms_iWindowWidth	= 0;
int				Platform::ms_iWindowHeight	= 0;
tinystl::string Platform::ms_strStoragePath;
tinystl::string Platform::ms_strResourcePath;

bool initializePlatform()
{
	return	Platform::initialize();
}

// Close platform
void closePlatform()
{
	Platform::close();
}

// Get storage path
const tinystl::string& getStoragePath()
{
	return	Platform::getStoragePath();
}

bool Platform::createRenderBuffer()
{
	ASSERT_LOG(NULL == ms_pRenderBuffer, "Render buffer already created");

	ms_pRenderBuffer	= new RenderBuffer();

	return	true;
}

bool Platform::setupRenderBuffer()
{
	ASSERT_LOG(ms_pRenderBuffer != NULL, "Render buffer not created");

	if (false == ms_pRenderBuffer->initialize())
	{
		return	false;
	}

	return true;
}

bool Platform::initialize()
{
	setStoragePath();
    
	System::ms_pDisplay	= createDisplay();
	
	if (NULL == System::ms_pDisplay)
	{
		return	false;
	}
	
	reinterpret_cast<SPlay::Display*>(System::ms_pDisplay)->setDefaultFrameBuffer(ms_pRenderBuffer->getFrameBuffer());
	
	GameHeader& gameHeader	= System::getUpdateableGameHeader();

	gameHeader.iWindowedHeight	= ms_iWindowHeight;
	gameHeader.iWindowedWidth	= ms_iWindowWidth;

	reinterpret_cast<SPlay::Display*>(System::ms_pDisplay)->resize();

	System::ms_pInput	= Input::create();

	if (NULL == System::ms_pInput)
	{
		return	false;
	}

	if (false == initializeSound())
	{
		return false;
	}

	return	true;
}

void Platform::close()
{
	// Delete render buffer
	delete 	ms_pRenderBuffer;

	ms_pRenderBuffer	= NULL;

	// Delete display
	delete	System::ms_pDisplay;

	System::ms_pDisplay	= NULL;

	// Delete input
	delete	System::ms_pInput;

	System::ms_pInput	= NULL;
}

bool Platform::update(float _fElapsed)
{
	System::getInput()->update();

	if (false == System::getGame()->update(_fElapsed))
	{
		return	false;
	}

	redraw();

	return	true;
}

void Platform::stop()
{
	System::close();
}

void Platform::redraw()
{
	ms_pRenderBuffer->bindFrameBuffer();

	System::getDisplay()->render();

	ms_pRenderBuffer->bindRenderBuffer();
}

void Platform::setStoragePath()
{
	ms_strStoragePath	= "./";
}

ENDNAMESPACE
