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

// Mosaic delay, in milliseconds
static const float	gsc_fMosaicDelay	= 0.1f;

// Scroll speed
static const float	gsc_fScrollSpeed	= 4.0f;

// BG layer
static const int	gsc_iBGLayer		= 0;

Game::Game()	:
	m_pFontLoader(NULL),
	m_pMapLoader(NULL),
	m_iMosaic(0),
	m_iTargetMosaic(0),
	m_fMosaicDelay(gsc_fMosaicDelay),
	m_bMosaicInProgress(false)
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
	Hardware::setBackgroundColor(0x00, 0x00, 0x00);

	// Load a map into the background
	m_pMapLoader	= MapLoader::create(gsc_iBGLayer, "Scroll");	
	
	if (NULL == m_pMapLoader)
	{
		return	false;
	}

	// Reset the scroll position
	m_fScrollX	= 0.0f;
	m_fScrollY	= 0.0f;

	BG*	pBG	= Hardware::getBG(gsc_iBGLayer);

	// Reset the scroll position and active the BG
	pBG->setScrollPosition(static_cast<int>(m_fScrollX), static_cast<int>(m_fScrollY));
	pBG->setActive(true);

	// Get the scroll size, in pixels, from the Map loader.
	m_fScrollLimitX	= static_cast<float>(m_pMapLoader->getMapWidth() - gsc_iScreenWidth);
	m_fScrollLimitY	= static_cast<float>(m_pMapLoader->getMapHeight() - gsc_iScreenHeight);

	// Load a font
	m_pFontLoader	= FontLoader::create("Font");	
	
	if (NULL == m_pFontLoader)
	{
		return	false;
	}

	// Draw text strings at the top and bottom of the screen
	Text*	pText	= Hardware::getText();

	tinystl::string	strMessage	= "PRESS A TO TOGGLE MOSAIC EFFECT";

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

	delete	m_pMapLoader;

	m_pMapLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
	// Check if the game is ready to exit
	if (true == Hardware::getJoypad()->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	updateMosaic(_fElapsedTime);
	updateInput(_fElapsedTime);

	return	true;
}

void Game::updateInput(float _fElapsedTime)
{
	BG*	pBG	= Hardware::getBG(gsc_iBGLayer);

	Joypad*	pJoypad	= Hardware::getJoypad();

	// Handle input
	if (pJoypad->buttonChanged(IK_A) && pJoypad->buttonPressed(IK_A) && false == m_bMosaicInProgress)
	{
		m_bMosaicInProgress	= true;
		m_fMosaicDelay		= gsc_fMosaicDelay;

		if (m_iMosaic != 0)
		{
			m_iMosaic--;

			m_iTargetMosaic	= 0;
		}

		else
		{
			m_iMosaic++;
			
			m_iTargetMosaic	= 15;
		}

		pBG->setMosiac(m_iMosaic);
	}

	uint32_t	uCurrentInput	= Hardware::getJoypad()->getCurrentInput();

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

	if (uCurrentInput & IK_PAD_UP)
	{
		m_fScrollY	-= fMovement;
	}

	else if (uCurrentInput & IK_PAD_DOWN)
	{
		m_fScrollY	+= fMovement;
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

	if (m_fScrollY < 0.0f)
	{
		m_fScrollY	= 0.0f;
	}

	else if (m_fScrollY > m_fScrollLimitY)
	{
		m_fScrollY	= m_fScrollLimitY;
	}

	pBG->setScrollPosition(static_cast<int>(m_fScrollX), static_cast<int>(m_fScrollY));
}

void Game::updateMosaic(float _fElapsedTime)
{
	if (true == m_bMosaicInProgress)
	{
		m_fMosaicDelay	-= _fElapsedTime;

		if (m_fMosaicDelay <= 0)
		{
			m_fMosaicDelay	+= gsc_fMosaicDelay;

			if (m_iMosaic < m_iTargetMosaic)
			{
				m_iMosaic++;
			}

			else
			{
				m_iMosaic--;
			}

			Hardware::getBG(gsc_iBGLayer)->setMosiac(m_iMosaic);

			if (m_iMosaic == m_iTargetMosaic)
			{
				m_bMosaicInProgress	= false;
			}
		}
	}
}
