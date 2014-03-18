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
static const char*	gsc_szTitleEvent	= "Title";

// Pointer to game class
Game*	g_pGame	= NULL;

// Show FPS?
#define	SHOW_FPS	1

Game::Game()	:
	m_pBackground(NULL),
	m_pBulletManager(NULL),
	m_pEnemyManager(NULL),
	m_pPlayerSprite(NULL),
	m_pResourceManager(NULL),
	m_pScoreBar(NULL),
	m_bGameOver(false),
	m_bPaused(false)
{
}

Game::~Game()
{
	close();
}

Game* Game::create()
{
	Game*	pGame	= new Game();

	// Retain a pointer to the Game class
	g_pGame	= pGame;

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
	m_pBackground	= Background::create(gsc_iBGLayer, "Map");	
	
	if (NULL == m_pBackground)
	{
		return	false;
	}

	// Create the scorebar
	m_pScoreBar	= ScoreBar::create("Font");	
	
	if (NULL == m_pScoreBar)
	{
		return	false;
	}

	// Create the resource, bullet, and enemy managers
	if (false == createManagers())
	{
		return	false;
	}

	// Create the  player sprite
	if (false == createPlayerSprite())
	{
		return	false;
	}

	// Reset the game parameters
	reset();

	// Start the title music playing
	m_pResourceManager->getAudioLoader()->playMusic(gsc_szTitleEvent);

	return	true;
}

void Game::close()
{
	// Delete player sprite
	delete	m_pPlayerSprite;

	m_pPlayerSprite	= NULL;

	// Delete background
	delete	m_pBackground;

	m_pBackground	= NULL;

	// Delete score bar
	delete	m_pScoreBar;

	m_pScoreBar	= NULL;

	// Delete bullet manager
	delete	m_pBulletManager;

	m_pBulletManager	= NULL;

	// Delete enemy manager
	delete	m_pEnemyManager;

	m_pEnemyManager	= NULL;

	// Delete resource manager
	delete	m_pResourceManager;

	m_pResourceManager	= NULL;
}

bool Game::update(float _fElapsedTime)
{
#if SHOW_FPS	
	m_fps.update(_fElapsedTime);
#endif

	if (m_bPaused != SPlay::Hardware::getPaused())
	{
		m_bPaused	= SPlay::Hardware::getPaused();

		m_pScoreBar->setPause(m_bPaused);
	}

	Joypad*	pJoypad	= Hardware::getJoypad();

	// Check if the game is ready to exit
	if (true == pJoypad->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	// Check to see if start has changed state and if the current state is pressed.
	else if (true == pJoypad->buttonChanged(IK_START) && true == pJoypad->buttonPressed(IK_START))
	{
		if (true == m_bGameOver)
		{
			reset();
		}

		else
		{
			SPlay::Hardware::setPaused(false == m_bPaused);
		}
	}

	else 
	{
		// Only update the game when not paused.
		if (false == m_bPaused && false == m_bGameOver)
		{
			// Update background
			m_pBackground->update(_fElapsedTime);

			// Update bullet manager
			m_pBulletManager->update(_fElapsedTime);

			// Update enemy manager
			m_pEnemyManager->update(_fElapsedTime);

			// Update player sprite 
			m_pPlayerSprite->updateInput(_fElapsedTime);

			// Check collisions
			checkCollisions();
		}

		// Handle select button press, when paused
		else if (true == m_bPaused || true == m_bGameOver)
		{
			// Check to see if select has changed state and if the current state is pressed.
			if (true == pJoypad->buttonChanged(IK_SELECT) && true == pJoypad->buttonPressed(IK_SELECT))
			{
				pJoypad->setExit(true);
			}
		}
	}

	return	true;
}

void Game::checkCollisions()
{
	Rect	rctPlayer	= m_pPlayerSprite->getCollisionRect();

	// Check collisions between the player and the enemies, and remove a life if there are any collisions.
	if (true == m_pEnemyManager->checkCollisions(rctPlayer))
	{
		removeLife();
	}

	// Check collisions between the bullets and the enemies.
	m_pBulletManager->checkCollisions(m_pEnemyManager);
}

void Game::addScore(int _iScore)
{
	int	iPreviousScore	= m_iScore;

	m_iScore	+= _iScore;

	updateScore();

	// Update the player sprite based on score
	if (iPreviousScore < 2500 && m_iScore >= 2500)
	{
		m_pPlayerSprite->setLevel(1);
	}

	else if (iPreviousScore < 5000 && m_iScore >= 5000)
	{
		m_pPlayerSprite->setLevel(2);
	}

	else if (iPreviousScore < 10000 && m_iScore >= 10000)
	{
		m_pPlayerSprite->setLevel(3);
	}
}

void Game::removeLife()
{
	if (m_iLives > 0)
	{
		m_iLives--;

		if (0 == m_iLives)
		{
			gameOver();
		}
	}

	updateLives();
}

bool Game::createManagers()
{
	// The resource manager handles loading sprites and contains the audio loader.
	m_pResourceManager	= ResourceManager::create();

	if (NULL == m_pResourceManager)
	{
		return	false;
	}

	// Load the resources for the game
	if (false == loadResources())
	{
		return	false;
	}

	// The bullet manager handles the player shots
	m_pBulletManager	= BulletManager::create();

	if (NULL == m_pBulletManager)
	{
		return	false;
	}

	// The enemy manager handles the enemies dropping from the top of the screen
	m_pEnemyManager	= EnemyManager::create();

	if (NULL == m_pEnemyManager)
	{
		return	false;
	}

	return	true;
}

bool Game::createPlayerSprite()
{
	// Create the player sprite
	m_pPlayerSprite	= PlayerSprite::create(PlayerTile);

	if (NULL == m_pPlayerSprite)
	{
		return	false;
	}

	return	true;
}

bool Game::loadResources()
{
	// Load sprite resources
	if (false == m_pResourceManager->loadSprite("Player"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Shot"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Ant"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Bee"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Bug"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Mosquito"))
	{
		return	false;
	}

	if (false == m_pResourceManager->loadSprite("Explosion"))
	{
		return	false;
	}

	return	true;
}

void Game::updateScore()
{
	m_pScoreBar->setScore(m_iScore);
}

void Game::updateLives()
{
	m_pScoreBar->setLives(m_iLives);
}

void Game::gameOver()
{
	m_bGameOver	= true;

	m_pScoreBar->setGameOver(m_bGameOver);
}

void Game::reset()
{
	m_iScore	= 0;
	m_iLives	= gsc_iMaxLives;

	// Reset the scorebar
	updateScore();
	updateLives();

	// Reset game over and remove message
	m_bGameOver	= false;
	m_pScoreBar->setGameOver(false);

	// Reset pause and remove message
	SPlay::Hardware::setPaused(false);
	m_pScoreBar->setPause(false);

	// Reset player sprite
	m_pPlayerSprite->reset();

	// Reset managers
	m_pBulletManager->reset();
	m_pEnemyManager->reset();
}
