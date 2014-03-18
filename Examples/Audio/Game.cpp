// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <Hardware.h>
#include <HardwareDefines.h>

#include "Game.h"
#include "GameDefines.h"

// Defines the Game class.
CREATE_GAME(Game)

// Music event name
static const char*	gsc_szMusicEvent	= "Title";

// Sounds event names
static const char*	gsc_szKillShot		= "KillShot";
static const char*	gsc_szExplode		= "Explode";

Game::Game()	:
	m_pAudioLoader(NULL),
	m_pFontLoader(NULL)
{
}

Game::~Game()
{
	close();
}

Game* Game::create()
{
	Game*	pGame	= new Game();

	if (false == pGame->initialize())
	{
		delete	pGame;

		pGame	= NULL;
	}

	return	pGame;
}

bool Game::initialize()
{
	// Set background color
	Hardware::setBackgroundColor(0x00, 0x00, 0x88);

	// Load a font
	m_pFontLoader	= FontLoader::create("Font");	
	
	if (NULL == m_pFontLoader)
	{
		return	false;
	}

	// Load audio
	m_pAudioLoader	= AudioLoader::create("SoundEvents");

	if (NULL == m_pAudioLoader)
	{
		return	false;
	}

	m_pAudioLoader->playMusic(gsc_szMusicEvent);

	// Draw text strings at the top and bottom of the screen
	Text*	pText	= Hardware::getText();

	tinystl::string	strTopMessage;
	
	strTopMessage	= "Playing music event ";
	strTopMessage	+= gsc_szMusicEvent;

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strTopMessage.length()) / 2, (gsc_iScreenHeight / gsc_iFontSize) / 2 - 1, 
		strTopMessage.c_str());

	// Activate text layer
	pText->setActive(true);

	return	true;
}

void Game::close()
{
	delete	m_pAudioLoader;

	m_pAudioLoader	= NULL;

	delete	m_pFontLoader;

	m_pFontLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
	Joypad*	pJoypad	= Hardware::getJoypad();

	// Check if the game is ready to exit
	if (true == pJoypad->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	if (true == pJoypad->buttonChanged(IK_A) && true == pJoypad->buttonPressed(IK_A))
	{
		// Play open box sound event
		m_pAudioLoader->playSound(gsc_szKillShot);
	
		tinystl::string	strBottomMessage;
		
		strBottomMessage	= "Started sound event ";
		strBottomMessage	+= gsc_szKillShot;

		Hardware::getText()->drawText((gsc_iScreenWidth / gsc_iFontSize - strBottomMessage.length()) / 2, 
			(gsc_iScreenHeight / gsc_iFontSize) / 2, strBottomMessage.c_str());
	}

	else if (true == pJoypad->buttonChanged(IK_B) && true == pJoypad->buttonPressed(IK_B))
	{
		// Play explode sound event
		m_pAudioLoader->playSound(gsc_szExplode);

		tinystl::string	strBottomMessage;
		
		strBottomMessage	= "Started sound event ";
		strBottomMessage	+= gsc_szExplode;
		strBottomMessage	+= " ";
	
		Hardware::getText()->drawText((gsc_iScreenWidth / gsc_iFontSize - strBottomMessage.length()) / 2, 
			(gsc_iScreenHeight / gsc_iFontSize) / 2, strBottomMessage.c_str());
	}

	return	true;
}
