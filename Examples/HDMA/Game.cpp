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
#include "Log.h"

// Defines the Game class.
CREATE_GAME(Game)

// Scroll speed
static const float	gsc_fScrollSpeed	= 4.0f;

// BG layer
static const int	gsc_iBGLayer		= 0;

Game::Game()	:
	m_pFontLoader(NULL),
	m_pHDMALoader(NULL),
	m_pMapLoader(NULL)
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
	Hardware::setBackgroundColor(0x21, 0x00, 0x10);

	// Load HDMA
	m_pHDMALoader	= HDMALoader::create("HDMA");

	if (NULL == m_pHDMALoader)
	{
		return	false;
	}

	// Enable HDMA
	m_bEnabled	= true;

	Hardware::getHDMA()->setEnable(m_bEnabled);
	
	// Load a map into the background
	m_pMapLoader	= MapLoader::create(gsc_iBGLayer, "Background");	
	
	if (NULL == m_pMapLoader)
	{
		return	false;
	}

	// Reset the scroll position
	m_fScrollX	= 0.0f;

	BG*	pBG	= Hardware::getBG(gsc_iBGLayer);

	// Reset the scroll position and active the BG
	pBG->setScrollPosition(static_cast<int>(m_fScrollX), 0);
	pBG->setActive(true);

	// Get the scroll size, in pixels, from the Map loader.
	m_fScrollLimitX	= static_cast<float>(m_pMapLoader->getMapWidth() - gsc_iScreenWidth);

	// Load a font
	m_pFontLoader	= FontLoader::create("Font");	
	
	if (NULL == m_pFontLoader)
	{
		return	false;
	}

	// Draw text strings at the top and bottom of the screen
	Text*	pText	= Hardware::getText();

	tinystl::string	strMessage	= "PRESS A TO TOGGLE HDMA EFFECT";

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strMessage.length()) / 2, (gsc_iScreenHeight / gsc_iFontSize) / 2 - 1, 
		strMessage.c_str());

	// Activate text layer
	pText->setActive(true);

	return	true;
}

void Game::close()
{
	delete	m_pFontLoader;

	m_pFontLoader	= NULL;

	delete	m_pHDMALoader;

	m_pHDMALoader	= NULL;

	delete	m_pMapLoader;

	m_pMapLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
	m_fps.update(_fElapsedTime);

	// Check if the game is ready to exit
	if (true == Hardware::getJoypad()->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	updateInput(_fElapsedTime);

	return	true;
}

void Game::updateInput(float _fElapsedTime)
{
	Joypad*	pJoypad	= Hardware::getJoypad();

	uint32_t	uCurrentInput	= Hardware::getJoypad()->getCurrentInput();

	// Toggle HDMA each time A is pressed
	if (true == pJoypad->buttonChanged(IK_A) && true == pJoypad->buttonPressed(IK_A))
	{
		m_bEnabled	= false == m_bEnabled;

		Hardware::getHDMA()->setEnable(m_bEnabled);
	}

	// Calculate scroll movement speed based on elapsed time
	float	fMovement	= gsc_fScrollSpeed * _fElapsedTime / gsc_fFramePeriod;

	// Scroll the layer based on joypad input
	if (uCurrentInput & IK_PAD_LEFT)
	{
		m_fScrollX	-= fMovement;
	}

	else if (uCurrentInput & IK_PAD_RIGHT)
	{
		m_fScrollX	+= fMovement;
	}

	// Limit scroll movement to the tilemap level
	if (m_fScrollX < 0.0f)
	{
		m_fScrollX	= 0.0f;
	}

	else if (m_fScrollX > m_fScrollLimitX)
	{
		m_fScrollX	= m_fScrollLimitX;
	}

	Hardware::getBG(gsc_iBGLayer)->setScrollPosition((int)m_fScrollX, 0);
}
