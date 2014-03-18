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

// Frame defines
enum Frames
{
	WalkForward		= 0,
	WalkBackward	= 3,
	WalkRight		= 6,
	WalkLeft		= 9
};

// Anmation frames for each state
static const int	gsc_iAnimationFrames	= WalkBackward - WalkForward;

// Movement speed
static const float	gsc_fMovementSpeed		= 0.5f;

// Frame delay, 0.15 second per frame
static const float	gsc_fFrameDelay			= 0.5f / gsc_iAnimationFrames;

// Sprite index
static const int	gsc_iOAMIndex			= 0;

// Sprite layer
static const int	gsc_iSpriteBG			= 0;

// Starting sprite tile index
static const int	gsc_iTileIndex			= 0;

Game::Game()	:
	m_pSpriteLoader(NULL),
	m_fFrameDelay(gsc_fFrameDelay)
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
	Hardware::setBackgroundColor(0x00, 0x00, 0x7F);

	if (false == loadSpriteGraphics())
	{
		return	false;
	}

	if (false == setupSprite())
	{
		return	false;
	}

	// Set joystick to 4 way (no diagonals)
	Hardware::getJoypad()->enable4Way(true);

	return	true;
}

void Game::close()
{
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
	Joypad*	pJoypad	= Hardware::getJoypad();

	if (false == pJoypad->dpadPushed())
	{
		m_iCurrentFrame	= 0;
		m_fFrameDelay	= 0.0f;
	}

	else
	{
		m_fFrameDelay	-= _fElapsedTime;

		if (m_fFrameDelay <= 0.0f)
		{
			m_fFrameDelay	+= gsc_fFrameDelay;

			m_iCurrentFrame++;
		
			if (m_iCurrentFrame >= gsc_iAnimationFrames)
			{
				m_iCurrentFrame	= 0;
			}
		}

		// Calculate movement speed based on elapsed time
		float	fMovement	= gsc_fMovementSpeed * _fElapsedTime / gsc_fFramePeriod;

		uint32_t	uCurrentInput	= pJoypad->getCurrentInput();

		// Move and animate sprite
		if (uCurrentInput & IK_PAD_LEFT)
		{
			m_eCurrentDirection	= FacingLeft;

			m_fX	-= fMovement;
		}

		else if (uCurrentInput & IK_PAD_RIGHT)
		{
			m_eCurrentDirection	= FacingRight;

			m_fX	+= fMovement;
		}

		else if (uCurrentInput & IK_PAD_UP)
		{
			m_eCurrentDirection	= FacingUp;

			m_fY	-= fMovement;
		}

		else if (uCurrentInput & IK_PAD_DOWN)
		{
			m_eCurrentDirection	= FacingDown;

			m_fY	+= fMovement;
		}
	}

	// Transfer the correct frame to VRAM
	m_pSpriteLoader->transferFrame(getAnimationFrame(), gsc_iTileIndex);

	OAM*	pOAM	= Hardware::getOAM();

	// Move sprite
	pOAM->setPosition(gsc_iOAMIndex, m_fX, m_fY);
}

bool Game::loadSpriteGraphics()
{
	// Create a SpriteLoader and load the Skeleton graphics file.
	m_pSpriteLoader	= SpriteLoader::create("Skeleton");

	if (NULL == m_pSpriteLoader)
	{
		return	false;
	}

	m_iCurrentFrame		= 0;
	m_eCurrentDirection	= FacingDown;

	// Transfer the correct frame to VRAM
	m_pSpriteLoader->transferFrame(getAnimationFrame(), gsc_iTileIndex);

	return	true;
}

bool Game::setupSprite()
{
	// Get the sprite size from the SpriteLoader
	ObjSize	eObjSize	= m_pSpriteLoader->getObjSize();
	
	OAM*	pOAM	= Hardware::getOAM();

	// Set object size
	pOAM->setObjSize(gsc_iOAMIndex, eObjSize);
	
	// Set the starting tile number to use for the sprite
	pOAM->setTileNumber(gsc_iOAMIndex, gsc_iTileIndex);
	
	// Start the sprite in the center of the screen
	m_fX	= static_cast<float>(gsc_iScreenWidth - m_pSpriteLoader->getFrameWidth()) / 2.0f;
	m_fY	= static_cast<float>(gsc_iScreenHeight - m_pSpriteLoader->getFrameHeight()) / 2.0f;

	pOAM->setPosition(gsc_iOAMIndex, m_fX, m_fY);
	pOAM->setBG(gsc_iOAMIndex, gsc_iSpriteBG);
	pOAM->setActive(gsc_iOAMIndex, true);

	return	true;
}

int Game::getAnimationFrame()
{
	// Get the animation frame based on the current direction and frame
	int	iFrame	= 0;

	switch (m_eCurrentDirection)
	{
		case FacingUp:
			iFrame	= WalkBackward;

			break;

		case FacingDown:
			iFrame	= WalkForward;

			break;

		case FacingRight:
			iFrame	= WalkRight;

			break;

		case FacingLeft:
			iFrame	= WalkLeft;

			break;
	}

	return	iFrame + m_iCurrentFrame;
}
