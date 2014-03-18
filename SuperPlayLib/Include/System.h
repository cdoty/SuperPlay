// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "IGame.h"
#include "GameHeader.h"

NAMESPACE(SPlay)

class IDisplay;
class IInput;
class ISoundSystem;
class ResourceManager;

class System
{
	friend class	Platform;
	friend class	Sound;

	public:
		// Initialize
		static bool initialize();
		
		// Close
		static void close();
		
		// Run loop
		static bool runLoop();

		// Redraw
		static void redraw();

		// Seed random number																  .
		static void seedRandomNumber(int _iSeed);

		// Get a random value, will never return _iUpper
		static int getRandomValue(int _iUpper);

		// Get display
		static IDisplay* getDisplay() {return ms_pDisplay;}

		// Get game
		static IGame* getGame() {return ms_pGame;}

		// Get input
		static IInput* getInput() {return ms_pInput;}

		// Get resource manager
		static ResourceManager* getResourceManager() {return ms_pResourceManager;}

		// Get sound system
		static ISoundSystem* getSoundSystem() {return ms_pSoundSystem;}

		// Get game header
		static const GameHeader& getGameHeader() {return ms_gameHeader;}

		// Get updateable game header
		static GameHeader& getUpdateableGameHeader() {return ms_gameHeader;}

	protected:
		// Display
		static IDisplay*		ms_pDisplay;

		// Input
		static IInput*			ms_pInput;

		// Input
		static ISoundSystem*	ms_pSoundSystem;

	private:
		// Game header
		static GameHeader		ms_gameHeader;

		// Game
		static IGame*			ms_pGame;

		// Resource manager
		static ResourceManager*	ms_pResourceManager;
};

ENDNAMESPACE
