// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <shlobj.h>
#include <time.h>

#include "HardwareDefines.h"
#include "IDisplay.h"
#include "Input.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "Platform.h"
#include "Sound.h"
#include "System.h"
#include "Timer.h"
#include "Window.h"

NAMESPACE(SPlay)

Timer*			Platform::ms_pTimer		= NULL;
Window*			Platform::ms_pWindow	= NULL;
tinystl::string Platform::ms_strStoragePath;

// Initialize platform
bool initializePlatform()
{
	return	Platform::initialize();
}

// Close platform
void closePlatform()
{
	Platform::close();
}

// Get save path
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

	// Initialize sound
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

	// Close sound
	closeSound();

	// Delete input
	delete	System::ms_pInput;

	System::ms_pInput	= NULL;
}

bool Platform::runLoop()
{
	MSG	msg;

	memset(&msg, 0, sizeof(MSG));

	ms_pTimer->start();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			// Get the elapsed time
			float	fElapsed	= ms_pTimer->getElapsedFloat();

			System::getInput()->update();

			if (false == System::getGame()->update(fElapsed))
			{
				return	false;
			}

			redraw();
		}
	}

	return	true;
}

void Platform::redraw()
{
	System::getDisplay()->render();

	const GameHeader&	gameHeader	= System::getGameHeader();

	if (true == gameHeader.bFramedWindow && false == gameHeader.bFullScreen)
	{
		Platform::getWindow()->drawLayeredWindow();
	}
}

const tinystl::string& Platform::getStoragePath()
{
	return	ms_strStoragePath;
}

void Platform::setStoragePath()
{
	ms_strStoragePath	= "./";

	PIDLIST_ABSOLUTE	pItemList;

	// Find the game save path
	if (SUCCEEDED(SHGetKnownFolderIDList(FOLDERID_SavedGames, KF_FLAG_CREATE, NULL, &pItemList)))
	{
		PWSTR	szSaveGamesPath	= SysAllocStringLen(0, MAX_PATH);

		if (TRUE == SHGetPathFromIDListW(pItemList, szSaveGamesPath))
		{
			int	iLength	= SysStringLen(szSaveGamesPath);

			int	iConvertedLength	= WideCharToMultiByte(CP_ACP, 0, szSaveGamesPath, iLength, 0, 0, NULL, NULL);
		
			char*	pDest	= new char[iConvertedLength + 1];

			WideCharToMultiByte(CP_ACP, 0, szSaveGamesPath, iLength, pDest, iConvertedLength, NULL, NULL);

			pDest[iConvertedLength]	= 0;

			ms_strStoragePath	= pDest;
			ms_strStoragePath	+= "\\";
			ms_strStoragePath	+= System::getGameHeader().strAppName;
		}

		SysFreeString(szSaveGamesPath);
	}

	ILFree(pItemList);
}

ENDNAMESPACE
