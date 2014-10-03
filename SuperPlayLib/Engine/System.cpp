// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdlib.h>
#include <time.h>

#include "Hardware.h"
#include "IDisplay.h"
#include "IInput.h"
#include "Log.h"
#include "PlatformLib.h"
#include "ResourceManager.h"
#include "System.h"
#include "mtrand/mtrand.h"

extern	SPlay::IGame* createGame();

NAMESPACE(SPlay)

IDisplay*			System::ms_pDisplay			= NULL;
IGame*				System::ms_pGame			= NULL;
IInput*				System::ms_pInput			= NULL;
ResourceManager*	System::ms_pResourceManager	= NULL;
ISoundSystem*		System::ms_pSoundSystem		= NULL;
GameHeader			System::ms_gameHeader;

MTRand_int32		gsc_randomNumber;

bool System::initialize()
{
	Log::instance()->logMessage("Initializing");

	// Get game header
	::getGameHeader(ms_gameHeader);

	Log::instance()->logMessage("Initializing Platform");

	// Initialize platform
	if (false == initializePlatform())
	{
		return	false;
	}

	Log::instance()->logMessage("Initializing Resource manager");

	// Create resource manager
	ms_pResourceManager	= ResourceManager::create();

	if (NULL == ms_pResourceManager)
	{
		return	false;
	}

	Log::instance()->logMessage("Initializing Hardware");

	// Initialize hardware
	if (false == Hardware::initialize())
	{
		return	false;
	}

	Log::instance()->logMessage("Creating game");

	// Create game
	ms_pGame	= createGame();

	if (NULL == ms_pGame)
	{
		return	false;
	}

	return	true;																							 
}

void System::close()
{
	// Delete game
	delete	ms_pGame;

	ms_pGame	= NULL;

	// Close hardware
	Hardware::close();

	// Close platform
	closePlatform();

	delete	System::ms_pInput;

	System::ms_pInput	= NULL;

	// Delete resource manager
	delete	ms_pResourceManager;

	ms_pResourceManager	= NULL;
	
	// Remove the log instance
	Log::deleteInstance();
}

void System::redraw()
{
	ms_pDisplay->render();
}

void System::seedRandomNumber(int _iSeed)
{
	gsc_randomNumber.seed(_iSeed);
}

int System::getRandomValue(int _iUpper)
{
	return	static_cast<int>((gsc_randomNumber() % (_iUpper + 1)));
}

ENDNAMESPACE
