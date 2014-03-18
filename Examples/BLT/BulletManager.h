// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "BulletSprite.h"
#include "EnemyManager.h"
#include "GameDefines.h"

class BulletManager
{
	public:
		// Constructor
		BulletManager();

		// Destructor
		~BulletManager();

		// Create
		static BulletManager* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		void update(float _fElapsedTime);

		// Add bullet
		void addBullet(float _fX, float _fY);

		// Clear bullets
		void clearBullets();
		
		// Check
		void checkCollisions(EnemyManager* _pEnemyManager);

		// Reset
		void reset();

	private:
		struct Bullet
		{
			// Position
			float			fX;
			float			fY;

			// Bullet sprite
			BulletSprite*	pSprite;

			// Used
			bool			bUsed;
		};

		// Bullets
		Bullet		m_bullets[gsc_iMaxBullets];

		// Top limit
		float		m_fTopLimit;

		// Remove bullet
		void removeBullet(int _iIndex);
};
