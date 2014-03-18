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

// Show FPS?
#define	SHOW_FPS	1

Game::Game()	:
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

	// Draw text strings at the top and bottom of the screen
	Text*	pText	= Hardware::getText();

	tinystl::string	strTopMessage	= "TOP  TEXT";

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - (int)strTopMessage.length()) / 2, 0, strTopMessage.c_str());

	tinystl::string	strBottomMessage	= "BOTTOM TEXT";

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - (int)strBottomMessage.length()) / 2, gsc_iScreenHeight / gsc_iFontSize - 1, 
		strBottomMessage.c_str());

	// Activate text layer
	pText->setActive(true);

	return	true;
}

void Game::close()
{
	delete	m_pFontLoader;

	m_pFontLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
#if SHOW_FPS	
	m_fps.update(_fElapsedTime);
#endif

	// Check if the game is ready to exit
	if (true == Hardware::getJoypad()->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	return	true;
}
