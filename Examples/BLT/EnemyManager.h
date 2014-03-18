// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "EnemySprite.h"
#include "GameDefines.h"

enum EnemyTypes
{
	AntEnemy	= 0,
	BeeEnemy,
	BugEnemy,
	MosquitoEnemy,

	EnemyCount
};

class EnemyManager
{
	public:
		// Constructor
		EnemyManager();

		// Destructor
		~EnemyManager();

		// Create
		static EnemyManager* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		void update(float _fElapsedTime);

		// Check collisions
		bool checkCollisions(const Rect& _rctCollide);

		// Add enemy
		void addEnemy(float _fX, int _iType);

		// Reset
		void reset();

		// Clear enemies
		void clearEnemies();

	private:
		struct Enemy
		{
			// Position
			float			fX;
			float			fY;

			// Delay
			float			fDelay;

			// Frame delay
			float			fFrameDelay;

			// Original Frame delay
			float			fOriginalFrameDelay;

			// Current frame
			int				iCurrentFrame;

			// Max frames
			int				iMaxFrames;

			// Bullet sprite
			EnemySprite*	pSprite;

			// Exploding
			bool			bExploding;

			// Used
			bool			bUsed;
		};

		// Enemies
		Enemy		m_enemies[gsc_iMaxEnemies];

		// Top start
		float		m_fTopStart;

		// Bottom limit
		float		m_fBottomLimit;

		// Frame width
		float		m_fFrameWidth;

		// Setup enemies
		void setupEnemies();

		// Enemy hit
		void enemyHit(int _iIndex);

		// Enemy removed
		void enemyRemoved(int _iIndex);
};
