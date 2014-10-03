// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <ppapi_simple/ps_event.h>
#include <ppapi/cpp/completion_callback.h>
#include <ppapi/cpp/core.h>

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

bool			Platform::ms_bInitialized	= false;
bool			Platform::ms_bBound			= false;
Timer*			Platform::ms_pTimer			= NULL;
Window*			Platform::ms_pWindow		= NULL;
SPlayInstance*	Platform::ms_pInstance		= NULL;
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
	Log::instance()->logMessage("Set storage");

	setStoragePath();

	Log::instance()->logMessage("Create window");

	ms_pWindow	= Window::create();
	
	if (NULL == ms_pWindow)
	{
		return	false;
	}

	Log::instance()->logMessage("Create display");

	if (ms_pInstance != NULL)
	{
		ms_pInstance->callOnMainThread(PP_MakeCompletionCallback(&Platform::createDisplayCallback, 0), 0);
	}

	if (NULL == System::ms_pDisplay)
	{
		return	false;
	}

	Log::instance()->logMessage("Create timer");

	ms_pTimer	= Timer::create();

	if (NULL == ms_pTimer)
	{
		return	false;
	}

	Log::instance()->logMessage("Create input");

	System::ms_pInput	= Input::create();

	if (NULL == System::ms_pInput)
	{
		return	false;
	}

#if 0
	Log::instance()->logMessage("Initialize sound");

	if (false == initializeSound())
	{
		return	false;
	}
#endif

	ms_bInitialized	= true;

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

void Platform::createDisplayCallback(void* _pData, int32_t _iValue)
{
	System::ms_pDisplay	= createDisplay();
}

void Platform::runLoop()
{
	Log::instance()->logMessage("Running");

	while (true)
	{
		PSEvent*	pEvent	= PSEventTryAcquire();

		while (pEvent != NULL)
		{
			PSEventRelease(pEvent);

			pEvent	= PSEventTryAcquire();
		}

		if (true == ms_bBound)
		{
			if (false == ms_bInitialized)
			{
				SPlay::System::initialize();
			}

			else
			{
				// Get the elapsed time
				float	fElapsed	= ms_pTimer->getElapsedFloat();

				System::getInput()->update();

#if 0
				if (false == System::getGame()->update(fElapsed))
				{
					break;
				}

				redraw();
#endif
			}
		}
	}
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
