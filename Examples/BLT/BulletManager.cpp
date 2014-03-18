// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "BulletManager.h"
#include "Game.h"

BulletManager::BulletManager()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		m_bullets[iLoop].pSprite	= NULL;
	}
}

BulletManager::~BulletManager()
{
	close();
}

BulletManager* BulletManager::create()
{
	BulletManager*	pBulletManager	= new BulletManager();

	if (false == pBulletManager->initialize())
	{
		delete	pBulletManager;

		pBulletManager	= NULL;
	}

	return	pBulletManager;
}

bool BulletManager::initialize()
{
	// Display the player on top of the bullets
	int	iBaseSort	= 2;

	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		m_bullets[iLoop].pSprite	= BulletSprite::create(BulletTile + iLoop * 2);
		
		if (NULL == m_bullets[iLoop].pSprite)
		{
			return	false;
		}

		m_bullets[iLoop].pSprite->setSortOrder(iLoop + iBaseSort);
	}

	// Reset the bullets
	reset();

	// Determine the point to stop the sprite.
	m_fTopLimit	= -static_cast<float>(g_pGame->getResourceManager()->getSpriteLoader("Shot")->getFrameHeight());

	return	true;
}

void BulletManager::close()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		delete	m_bullets[iLoop].pSprite;

		m_bullets[iLoop].pSprite	= NULL;
	}
}

void BulletManager::update(float _fElapsedTime)
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		if (true == m_bullets[iLoop].bUsed)
		{
			m_bullets[iLoop].fY	-= gsc_fBulletSpeed * _fElapsedTime / gsc_fFramePeriod;

			if (m_bullets[iLoop].fY < m_fTopLimit)
			{
				removeBullet(iLoop);
			}

			else
			{
				m_bullets[iLoop].pSprite->setPosition(m_bullets[iLoop].fX, m_bullets[iLoop].fY);
			}
		}
	}
}

void BulletManager::addBullet(float _fX, float _fY)
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		if (false == m_bullets[iLoop].bUsed)
		{
			m_bullets[iLoop].bUsed	= true;
			m_bullets[iLoop].fX		= _fX;
			m_bullets[iLoop].fY		= _fY;

			m_bullets[iLoop].pSprite->setPosition(m_bullets[iLoop].fX, m_bullets[iLoop].fY);
			m_bullets[iLoop].pSprite->setActive(true);

			break;
		}
	}
}

void BulletManager::clearBullets()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		removeBullet(iLoop);
	}
}

void BulletManager::checkCollisions(EnemyManager* _pEnemyManager)
{
	for (int iLoop = 0; iLoop < gsc_iMaxBullets; ++iLoop)
	{
		if (true == m_bullets[iLoop].bUsed)
		{
			Rect	rctBullet	= m_bullets[iLoop].pSprite->getCollisionRect();

			if (true == _pEnemyManager->checkCollisions(rctBullet))
			{
				removeBullet(iLoop);
			}
		}
	}
}

void BulletManager::reset()
{
	clearBullets();
}

void BulletManager::removeBullet(int _iIndex)
{
	m_bullets[_iIndex].bUsed	= false;

	m_bullets[_iIndex].pSprite->setActive(false);
}