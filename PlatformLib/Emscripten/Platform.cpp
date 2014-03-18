// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <time.h>

#include "IDisplay.h"
#include "Input.h"
#include "ISoundSystem.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "Platform.h"
#include "Sound.h"
#include "System.h"
#include "Timer.h"
#include "Window.h"

NAMESPACE(SPlay)

Timer*		Platform::ms_pTimer		= NULL;
Window*		Platform::ms_pWindow	= NULL;
tinystl::string Platform::ms_strStoragePath;

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

bool Platform::initialize()
{
	setStoragePath();

	ms_pWindow	= Window::create();
	
	if (NULL == ms_pWindow)
	{
		return	false;
	}

	System::ms_pDisplay	= createDisplay();

	if (NULL == System::ms_pDisplay)
	{
		return	false;
	}

	ms_pTimer	= Timer::create();

	if (NULL == ms_pTimer)
	{
		return	false;
	}

	System::ms_pInput	= Input::create();

	if (NULL == System::ms_pInput)
	{
		return	false;
	}

	if (false == initializeSound())
	{
		return	false;
	}

	return	true;
}

void Platform::close()
{
	// Delete window
	delete	ms_pWindow;

	ms_pWindow	= NULL;

	// Delete timer
	delete	ms_pTimer;

	ms_pTimer	= NULL;

	// Delete display
	delete	System::ms_pDisplay;

	System::ms_pDisplay	= NULL;

	// Close sound system
	closeSound();
	
	// Delete input
	delete	System::ms_pInput;

	System::ms_pInput	= NULL;
}

void Platform::runLoop()
{
	// Get the elapsed time
	float	fElapsed	= ms_pTimer->getElapsedFloat();

	System::getInput()->update();

	if (false == System::getGame()->update(fElapsed))
	{
		return;
	}

	redraw();
}

void Platform::redraw()
{
	System::getDisplay()->render();
}

const tinystl::string& Platform::getStoragePath()
{
	return	ms_strStoragePath;
}

void Platform::setStoragePath()
{
	ms_strStoragePath	= "./";
}

ENDNAMESPACE
