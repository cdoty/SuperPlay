// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "BulletSprite.h"
#include "Game.h"
#include "Hardware.h"

BulletSprite::BulletSprite(int _iTileIndex)	:
	super(_iTileIndex)
{
}

BulletSprite::~BulletSprite()
{
	close();
}

BulletSprite* BulletSprite::create(int _iTileIndex)
{
	BulletSprite*	pBulletSprite	= new BulletSprite(_iTileIndex);

	if (false == pBulletSprite->initialize())
	{
		delete	pBulletSprite;

		pBulletSprite	= NULL;
	}

	return	pBulletSprite;
}

bool BulletSprite::initialize()
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

	if (false == load("Shot"))
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

void BulletSprite::close()
{
	super::close();
}
