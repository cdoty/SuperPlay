// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <float.h>
#include <math.h>

#include "Game.h"
#include "Hardware.h"

// Animation frames
enum AnimationFrames
{
	Level1 = 0,
	Level2 = 1,
	Level3 = 2,
	Level4 = 3,

	LevelCount
};

PlayerSprite::PlayerSprite(int _iTileIndex)	:
	super(_iTileIndex)
{
}

PlayerSprite::~PlayerSprite()
{
	close();
}

PlayerSprite* PlayerSprite::create(int _iTileIndex)
{
	PlayerSprite*	pPlayerSprite	= new PlayerSprite(_iTileIndex);

	if (false == pPlayerSprite->initialize())
	{
		delete	pPlayerSprite;

		pPlayerSprite	= NULL;
	}

	return	pPlayerSprite;
}

bool PlayerSprite::initialize()
{
	if (false == super::initialize())
	{
		return	false;
	}
	
	if (false == load("Player"))
	{
		return	false;
	}

	if (false == addSpriteToOAM())
	{
		return	false;
	}

	// Set initial sprite
	m_iLevel	= Level1;

	m_pSpriteLoader->transferFrame(m_iLevel, m_iTileIndex);

	m_fX	= static_cast<float>((gsc_iScreenWidth - m_iFrameWidth) / 2);
	m_fY	= static_cast<float>(gsc_iScreenHeight - m_iFrameHeight - gsc_iBottomOffset);

	OAM*	pOAM	= Hardware::getOAM();

	pOAM->setTileNumber(m_iSpriteIndex, m_iTileIndex);
	pOAM->setObjSize(m_iSpriteIndex, m_pSpriteLoader->getObjSize());
	pOAM->setSortOrder(m_iSpriteIndex, gsc_iPlayerSortOrder);

	setPosition(m_fX, m_fY);
	setActive(true);

	m_fLeftLimit	= 0.0f;
	m_fRightLimit	= static_cast<float>(gsc_iScreenWidth - m_iFrameWidth - 1);
	m_fTopLimit		= 0.0f;
	m_fBottomLimit	= static_cast<float>(gsc_iScreenHeight - m_iFrameHeight - 1);

	m_fButtonCooldown	= 0.0f;

	return	true;
}

void PlayerSprite::close()
{
	super::close();
}

void PlayerSprite::updateInput(float _fElapsedTime)
{
	m_fButtonCooldown	-= _fElapsedTime;

	uint32_t	uCurrentInput	= Hardware::getJoypad()->getCurrentInput();

	// Calculate movement speed based on elapsed time
	float	fMovement	= 0.0f;

	// Adjust for diagonal movement
	if ((uCurrentInput & (IK_PAD_UP | IK_PAD_DOWN)) != 0 || (uCurrentInput & (IK_PAD_LEFT | IK_PAD_RIGHT)) != 0)
	{
		fMovement	= gsc_fPlayerSpeed * _fElapsedTime / gsc_fFramePeriod;

		if ((uCurrentInput & (IK_PAD_UP | IK_PAD_DOWN)) != 0 && (uCurrentInput & (IK_PAD_LEFT | IK_PAD_RIGHT)) != 0)
		{
			fMovement	*= 0.707f;
		}
	}

	if (uCurrentInput & IK_PAD_UP)
	{
		m_fY	-= fMovement;
	}

	else if (uCurrentInput & IK_PAD_DOWN)
	{
		m_fY	+= fMovement;
	}

	if (uCurrentInput & IK_PAD_LEFT)
	{
		m_fX	-= fMovement;
	}

	else if (uCurrentInput & IK_PAD_RIGHT)
	{
		m_fX	+= fMovement;
	}

	if (m_fX < m_fLeftLimit)
	{
		m_fX	= m_fLeftLimit;
	}

	else if (m_fX > m_fRightLimit)
	{
		m_fX	= m_fRightLimit;
	}

	if (m_fY < m_fTopLimit)
	{
		m_fY	= m_fTopLimit;
	}

	else if (m_fY > m_fBottomLimit)
	{
		m_fY	= m_fBottomLimit;
	}

	if (fabs(fMovement) >= FLT_EPSILON)
	{
		Hardware::getOAM()->setPosition(m_iSpriteIndex, m_fX, m_fY);
	}

	if (m_fButtonCooldown <= 0.0f && uCurrentInput & IK_A)
	{
		m_fButtonCooldown	= gsc_iButtonCooldown;

		g_pGame->getBulletManager()->addBullet(m_fX, m_fY);
	}
}

void PlayerSprite::setLevel(int _iLevel)
{
	m_iLevel	= _iLevel;

	if (m_iLevel >= LevelCount)
	{
		m_iLevel	= LevelCount - 1;
	}

	setFrame(m_iLevel);
}

void PlayerSprite::reset()
{
	m_fX	= static_cast<float>((gsc_iScreenWidth - m_iFrameWidth) / 2);
	m_fY	= static_cast<float>(gsc_iScreenHeight - m_iFrameHeight - gsc_iBottomOffset);

	setPosition(m_fX, m_fY);

	setLevel(0);
}
