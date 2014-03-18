// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "EnemySprite.h"
#include "Game.h"
#include "Hardware.h"

EnemySprite::EnemySprite(int _iTileIndex)	:
	super(_iTileIndex)
{
}

EnemySprite::~EnemySprite()
{
	close();
}

EnemySprite* EnemySprite::create(int _iTileIndex)
{
	EnemySprite*	pEnemySprite	= new EnemySprite(_iTileIndex);

	if (false == pEnemySprite->initialize())
	{
		delete	pEnemySprite;

		pEnemySprite	= NULL;
	}

	return	pEnemySprite;
}

bool EnemySprite::initialize()
{
	if (false == super::initialize())
	{
		return	false;
	}

	ResourceManager*	pResourceManager	= g_pGame->getResourceManager();
		
	if (NULL == pResourceManager)
	{
		return	false;
	}

	if (false == addSpriteToOAM())
	{
		return	false;
	}

	m_pSpriteLoader	= pResourceManager->getSpriteLoader("Ant");

	if (NULL == m_pSpriteLoader)
	{
		return	false;
	}

	// Setup the sprite frame
	m_pSpriteLoader->transferFrame(0, m_iTileIndex);

	m_fX	= 0.0f;
	m_fY	= 0.0f;

	OAM*	pOAM	= Hardware::getOAM();

	pOAM->setTileNumber(m_iSpriteIndex, m_iTileIndex);
	pOAM->setObjSize(m_iSpriteIndex, m_pSpriteLoader->getObjSize());
	pOAM->setPosition(m_iSpriteIndex, m_fX, m_fY);
	pOAM->setSortOrder(m_iSpriteIndex, gsc_iShotSortOrder);
	pOAM->setActive(m_iSpriteIndex, false);

	return	true;
}

void EnemySprite::close()
{
	super::close();
}
