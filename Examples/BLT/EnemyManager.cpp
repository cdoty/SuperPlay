// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "EnemyManager.h"
#include "Game.h"
#include "Hardware.h"

// Sounds event name
static const char*	gsc_szExplode	= "Explode";

// Explosion frame delay
static const float	gsc_fExplosionDelay	= gsc_fFramePeriod * 6;

// Animation frame delay
static const float	gsc_fAnimationDelay	= gsc_fFramePeriod * 3;

// Sprite names
static const char*	gsc_szResourceNames[EnemyCount]	=
{
	"Ant",
	"Bee",
	"Bug",
	"Mosquito",
};

EnemyManager::EnemyManager()
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		m_enemies[iLoop].pSprite	= NULL;
	}
}

EnemyManager::~EnemyManager()
{
	close();
}

EnemyManager* EnemyManager::create()
{
	EnemyManager*	pEnemyManager	= new EnemyManager();

	if (false == pEnemyManager->initialize())
	{
		delete	pEnemyManager;

		pEnemyManager	= NULL;
	}

	return	pEnemyManager;
}

bool EnemyManager::initialize()
{
	// Display the player, sizzle meter, and bullets on top of the enemies
	int	iBaseSort	= 2 + gsc_iMaxBullets;

	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		m_enemies[iLoop].pSprite	= EnemySprite::create(EnemyTile + iLoop * 2);
		
		if (NULL == m_enemies[iLoop].pSprite)
		{
			return	false;
		}

		m_enemies[iLoop].pSprite->setSortOrder(iLoop + iBaseSort);
	}

	SpriteLoader*	pLoader	= g_pGame->getResourceManager()->getSpriteLoader("Ant");

	int	iHeight	= pLoader->getFrameHeight();

	m_fFrameWidth	= static_cast<float>(pLoader->getFrameWidth());

	m_fBottomLimit	= static_cast<float>(gsc_iScreenHeight) + m_fFrameWidth;
	m_fTopStart		= static_cast<float>(-iHeight * 2);

	reset();

	return	true;
}

void EnemyManager::close()
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		delete	m_enemies[iLoop].pSprite;

		m_enemies[iLoop].pSprite	= NULL;
	}
}

void EnemyManager::update(float _fElapsedTime)
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		if (true == m_enemies[iLoop].bUsed)
		{
			if (m_enemies[iLoop].fDelay > 0)
			{
				m_enemies[iLoop].fDelay	-= _fElapsedTime;
			}
			
			else
			{
				m_enemies[iLoop].fY	+= gsc_fEnemySpeed * _fElapsedTime / gsc_fFramePeriod;

				if (m_enemies[iLoop].fY > m_fBottomLimit)
				{
					enemyRemoved(iLoop);
				}

				else
				{
					bool	bAnimate	= true;

					if (m_enemies[iLoop].fFrameDelay > 0)
					{
						m_enemies[iLoop].fFrameDelay	-= _fElapsedTime;

						if (m_enemies[iLoop].fFrameDelay <= 0)
						{
							m_enemies[iLoop].fFrameDelay	+= m_enemies[iLoop].fOriginalFrameDelay;
						}
					
						else
						{
							bAnimate	= false;
						}
					}

					if (true == bAnimate)
					{
						m_enemies[iLoop].iCurrentFrame++;

						if (m_enemies[iLoop].iCurrentFrame >= m_enemies[iLoop].iMaxFrames)
						{
							if (true == m_enemies[iLoop].bExploding)
							{
								enemyRemoved(iLoop);
							}

							else
							{
								m_enemies[iLoop].iCurrentFrame	= 0;
							}
						}

						m_enemies[iLoop].pSprite->setFrame(m_enemies[iLoop].iCurrentFrame);
					}

					m_enemies[iLoop].pSprite->setPosition(m_enemies[iLoop].fX, m_enemies[iLoop].fY);
				}
			}
		}
	}
}

bool EnemyManager::checkCollisions(const Rect& _rctCollide)
{
	bool	bCollides	= false;

	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		if (true == m_enemies[iLoop].bUsed && false == m_enemies[iLoop].bExploding)
		{
			Rect	rctEnemy	= m_enemies[iLoop].pSprite->getCollisionRect();

			if (_rctCollide.intersectsRect(rctEnemy))
			{
				bCollides	= true;

				enemyHit(iLoop);
			}
		}
	}

	return	bCollides;
}

void EnemyManager::addEnemy(float _fX, int _iType)
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		if (false == m_enemies[iLoop].bUsed)
		{
			m_enemies[iLoop].bUsed			= true;
			m_enemies[iLoop].bExploding		= false;
			m_enemies[iLoop].fX				= _fX;
			m_enemies[iLoop].fY				= m_fTopStart;
			
			// Create random delay up to 2.25 seconds
			m_enemies[iLoop].fDelay			= static_cast<float>(Hardware::getRandomValue(20)) / 10.0f + 0.25f;
			m_enemies[iLoop].iCurrentFrame	= 0;

			m_enemies[iLoop].pSprite->load(gsc_szResourceNames[_iType]);

			m_enemies[iLoop].fOriginalFrameDelay	= gsc_fAnimationDelay;
			m_enemies[iLoop].fFrameDelay			= gsc_fAnimationDelay;
			m_enemies[iLoop].iMaxFrames	= m_enemies[iLoop].pSprite->getFrameCount();

			m_enemies[iLoop].pSprite->setFrame(m_enemies[iLoop].iCurrentFrame);

			m_enemies[iLoop].pSprite->setPosition(m_enemies[iLoop].fX, m_enemies[iLoop].fY);
			m_enemies[iLoop].pSprite->setActive(true);

			break;
		}
	}
}

void EnemyManager::reset()
{
	clearEnemies();
	setupEnemies();
}

void EnemyManager::clearEnemies()
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		m_enemies[iLoop].bUsed	= false;

		m_enemies[iLoop].pSprite->setActive(false);
	}
}

void EnemyManager::setupEnemies()
{
	for (int iLoop = 0; iLoop < gsc_iMaxEnemies; ++iLoop)
	{
		int	iType	= Hardware::getRandomValue(EnemyCount - 1);

		addEnemy(static_cast<float>(iLoop) * static_cast<float>(gsc_iScreenWidth) / static_cast<float>(gsc_iMaxEnemies) + 
			m_fFrameWidth / 2.0f, iType);
	}
}

void EnemyManager::enemyHit(int _iIndex)
{
	m_enemies[_iIndex].bExploding			= true;
	m_enemies[_iIndex].fOriginalFrameDelay	= gsc_fExplosionDelay;
	m_enemies[_iIndex].fFrameDelay			= gsc_fExplosionDelay;

	m_enemies[_iIndex].pSprite->load("Explosion");
	m_enemies[_iIndex].iCurrentFrame	= 0;
	m_enemies[_iIndex].iMaxFrames		= m_enemies[_iIndex].pSprite->getFrameCount();

	m_enemies[_iIndex].pSprite->setFrame(0);

	g_pGame->getResourceManager()->getAudioLoader()->playSound(gsc_szExplode);

	g_pGame->addScore(gsc_iEnemyScore);
}

void EnemyManager::enemyRemoved(int _iIndex)
{
	m_enemies[_iIndex].bUsed	= false;

	m_enemies[_iIndex].pSprite->setActive(false);

	int	iType	= Hardware::getRandomValue(EnemyCount - 1);

	addEnemy(static_cast<float>(_iIndex) * static_cast<float>(gsc_iScreenWidth) / 
		static_cast<float>(gsc_iMaxEnemies) + m_fFrameWidth / 2.0f, iType);
}
