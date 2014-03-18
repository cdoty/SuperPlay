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

// Sprite and tile indexes
static const int	gsc_iSpriteIndex	= 0;
static const int	gsc_iTileIndex		= 0;

// BG layer
static const int	gsc_iBGLayer		= 1;

// Sprite layer
static const int	gsc_iSpriteBG		= 1;

// Defines the Game class.
CREATE_GAME(Game)

Game::Game()	:
	m_pFontLoader(NULL),
	m_pMapLoader(NULL),
	m_pSpriteLoader(NULL)
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
	Hardware::setBackgroundColor(0x5D, 0x6A, 0x99);

	// Load resources
	if (false == loadFont())
	{
		return	false;
	}

	if (false == loadMap())
	{
		return	false;
	}

	if (false == loadSprite())
	{
		return	false;
	}

	if (false == setupSprite())
	{
		return	false;
	}

	// Set the locations of each button on the screen
	setButtonPositions();

	// Set joystick to 4 way (no diagonals)
	Hardware::getJoypad()->enable4Way(true);

	// Display the title text
	Text*	pText	= Hardware::getText();

	tinystl::string	strMessage	= "Joypad Test:";

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strMessage.length()) / 2, 1, strMessage.c_str());

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

	delete	m_pSpriteLoader;

	m_pSpriteLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
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
	// Reposition and activate the sprite
	OAM*	pOAM	= Hardware::getOAM();

	Joypad*	pJoypad	= Hardware::getJoypad();

	// Turn off the sprite if there is no input.
	if (false == pJoypad->buttonsPushed() && false == pJoypad->dpadPushed())
	{
		pOAM->setActive(gsc_iSpriteIndex, false);
	}

	else
	{
		uint32_t	uInput	= pJoypad->getCurrentInput();

		int	iIndex	= -1;

		if (uInput & IK_PAD_UP)
		{
			iIndex	= 0;
		}

		else if (uInput & IK_PAD_DOWN)
		{
			iIndex	= 1;
		}

		if (uInput & IK_PAD_LEFT)
		{
			iIndex	= 2;
		}

		else if (uInput & IK_PAD_RIGHT)
		{
			iIndex	= 3;
		}

		else if (uInput & IK_A)
		{
			iIndex	= 4;
		}

		else if (uInput & IK_B)
		{
			iIndex	= 5;
		}

		else if (uInput & IK_X)
		{
			iIndex	= 6;
		}

		else if (uInput & IK_Y)
		{
			iIndex	= 7;
		}

		else if (uInput & IK_L)
		{
			iIndex	= 8;
		}

		else if (uInput & IK_R)
		{
			iIndex	= 9;
		}

		else if (uInput & IK_START)
		{
			iIndex	= 10;
		}

		else if (uInput & IK_SELECT)
		{
			iIndex	= 11;
		}

		if (iIndex != -1)
		{
			pOAM->setPosition(gsc_iSpriteIndex, (float)m_vecButtonPositions[iIndex].iX, (float)m_vecButtonPositions[iIndex].iY);
			pOAM->setActive(gsc_iSpriteIndex, true);
		}
	}
}

bool Game::loadFont()
{
	// Load a font
	m_pFontLoader	= FontLoader::create("Font");
	
	if (NULL == m_pFontLoader)
	{
		return	false;
	}

	return	true;
}

bool Game::loadMap()
{
	// Load a map into the background
	m_pMapLoader	= MapLoader::create(gsc_iBGLayer, "Background");	
	
	if (NULL == m_pMapLoader)
	{
		return	false;
	}

	BG*	pBG	= Hardware::getBG(gsc_iBGLayer);

	// Reset the scroll position and active the BG
	pBG->setScrollPosition(0, 0);
	pBG->setActive(true);

	return	true;
}

bool Game::loadSprite()
{
	// Create a SpriteLoader and load the Dot image
	m_pSpriteLoader	= SpriteLoader::create("Dot");

	if (NULL == m_pSpriteLoader)
	{
		return	false;
	}

	// Transfer first frame to VRAM
	m_pSpriteLoader->transferFrame(0, gsc_iTileIndex);

	return	true;
}

bool Game::setupSprite()
{
	OAM*	pOAM	= Hardware::getOAM();

	// Set object size
	pOAM->setObjSize(gsc_iSpriteIndex, m_pSpriteLoader->getObjSize());
	
	// Set the starting tile number to use for the sprite
	pOAM->setTileNumber(gsc_iSpriteIndex, gsc_iTileIndex);

	pOAM->setBG(gsc_iSpriteIndex, gsc_iSpriteBG);
	pOAM->setActive(gsc_iSpriteIndex, false);

	return	true;
}

void Game::setButtonPositions()
{
	int	iWidth	= m_pSpriteLoader->getFrameWidth() / 2;
	int	iHeight	= m_pSpriteLoader->getFrameHeight() / 2;

	// Set dpad positions
	m_vecButtonPositions.push_back(Point(53 - iWidth, 99 - iHeight));
	m_vecButtonPositions.push_back(Point(53 - iWidth, 128 - iHeight));
	m_vecButtonPositions.push_back(Point(39 - iWidth, 113 - iHeight));
	m_vecButtonPositions.push_back(Point(68 - iWidth, 113 - iHeight));
	
	// Set ABXY positions
	m_vecButtonPositions.push_back(Point(225 - iWidth, 114 - iHeight));
	m_vecButtonPositions.push_back(Point(201 - iWidth, 132 - iHeight));
	m_vecButtonPositions.push_back(Point(204 - iWidth, 91 - iHeight));
	m_vecButtonPositions.push_back(Point(180 - iWidth, 110 - iHeight));
	
	// Set LR positions
	m_vecButtonPositions.push_back(Point(58 - iWidth, 59 - iHeight));	
	m_vecButtonPositions.push_back(Point(197 - iWidth, 59 - iHeight));

	// Set Start and Select positions
	m_vecButtonPositions.push_back(Point(132 - iWidth, 121 - iHeight));
	m_vecButtonPositions.push_back(Point(104 - iWidth, 121 - iHeight));
}
