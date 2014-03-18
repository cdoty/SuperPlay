// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <IGame.h>

#include "Background.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "FPS.h"
#include "PlayerSprite.h"
#include "ResourceManager.h"
#include "ScoreBar.h"

using namespace	SPlay;

class Game : public IGame
{
	public:
		// Constructor
		Game();

		// Destructor
		virtual ~Game();

		// Static create function used to create the game class
		static Game* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		bool update(float _fElapsedTime);

		// Get bullet manager
		BulletManager* getBulletManager() {return m_pBulletManager;}

		// Get enemy manager
		EnemyManager* getEnemyManager() {return m_pEnemyManager;}

		// Get player sprite
		PlayerSprite* getPlayerSprite() {return m_pPlayerSprite;}

		// Get resource manager
		ResourceManager* getResourceManager() {return m_pResourceManager;}

		// Check collisions
		void checkCollisions();

		// Add score
		void addScore(int _iScore);

		// Remove life
		void removeLife();

	private:
		// Background
		Background*			m_pBackground;

		// Bullet manager
		BulletManager*		m_pBulletManager;

		// Enemy manager
		EnemyManager*		m_pEnemyManager;

		// Sprites
		PlayerSprite*		m_pPlayerSprite;

		// Resource manager
		ResourceManager*	m_pResourceManager;

		// Score bar
		ScoreBar*			m_pScoreBar;

		// FPS
		FPS					m_fps;

		// Score			
		int					m_iScore;

		// Lives
		int					m_iLives;

		// Game over?
		bool				m_bGameOver;

		// Paused?
		bool				m_bPaused;

		// Create managers
		bool createManagers();
		
		// Create player sprite
		bool createPlayerSprite();

		// Load resources
		bool loadResources();

		// Update score
		void updateScore();

		// Update lives
		void updateLives();

		// Game over
		void gameOver();

		// Reset
		void reset();
};

// Pointer to game class
extern	Game*	g_pGame;
