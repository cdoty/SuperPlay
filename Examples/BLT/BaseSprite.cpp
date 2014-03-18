// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "BaseSprite.h"
#include "Game.h"
#include "Hardware.h"

BaseSprite::BaseSprite(int _iTileIndex)	:
	m_pSpriteLoader(NULL),
	m_iSpriteIndex(-1),
	m_iTileIndex(_iTileIndex),
	m_iFrameWidth(gsc_iMinObjSize),
	m_iFrameHeight(gsc_iMinObjSize)
{
}

BaseSprite::~BaseSprite()
{
}

bool BaseSprite::initialize()
{
	return	true;
}

void BaseSprite::close()
{
	OAM*	pOAM	= Hardware::getOAM();
	
	if (pOAM != NULL && m_iSpriteIndex != -1)
	{
		pOAM->setUsed(m_iSpriteIndex, true);
	}

	m_pSpriteLoader	= NULL;
}

void BaseSprite::setPosition(float _fX, float _fY)
{
	m_fX	= _fX;
	m_fY	= _fY;

	// Updates the sprite position
	Hardware::getOAM()->setPosition(m_iSpriteIndex, m_fX, m_fY);
}

void BaseSprite::setActive(bool _bActive)
{
	// Setting active to true will cause the sprite to be drawn on the screen.
	Hardware::getOAM()->setActive(m_iSpriteIndex, _bActive);
}

void BaseSprite::setFrame(int _iFrame)
{
	// Does an DMA transfer of the graphics frame to VRAM.
	m_pSpriteLoader->transferFrame(_iFrame, m_iTileIndex);
}

int BaseSprite::getFrameCount()
{
	// Gets the number of frames in an animation
	return	m_pSpriteLoader->getFrameCount();
}

void BaseSprite::setSortOrder(int _iSortOrder)
{
	// Set the sprite sort order. Changing the sort order will change the order that the sprites are drawn in.
	// Sprites with a lower sort order are drawn on top of sprites with a higher sort order.
	Hardware::getOAM()->setSortOrder(m_iSpriteIndex, _iSortOrder);
}

Rect BaseSprite::getCollisionRect() const
{
	Rect	collision;

	collision.iLeft		= static_cast<int>(m_fX);
	collision.iTop		= static_cast<int>(m_fY);
	
	collision.iWidth	= m_iFrameWidth;
	collision.iHeight	= m_iFrameHeight;

	return	collision;
}

bool BaseSprite::load(const tinystl::string& _strSpriteName)
{
	ResourceManager*	pResourceManager	= g_pGame->getResourceManager();
		
	if (NULL == pResourceManager)
	{
		return	false;
	}

	m_pSpriteLoader	= pResourceManager->getSpriteLoader(_strSpriteName);

	if (NULL == m_pSpriteLoader)
	{
		return	false;
	}

	m_iFrameWidth	= m_pSpriteLoader->getFrameWidth();
	m_iFrameHeight	= m_pSpriteLoader->getFrameHeight();

	return	true;
}

bool BaseSprite::addSpriteToOAM()
{
	OAM*	pOAM	= Hardware::getOAM();

	// Find an open OAM slot.
	m_iSpriteIndex	= pOAM->getAvailableObj();

	if (-1 == m_iSpriteIndex)
	{
		return	false;
	}

	// Mark the OAM spot as used
	pOAM->setUsed(m_iSpriteIndex, true);
	
	// Set the BG layer that this sprite will appear above.
	// It will be obscured by any backgrounds with a lower index.
	pOAM->setBG(m_iSpriteIndex, gsc_iBGLayer);

	return	true;
}
