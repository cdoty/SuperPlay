// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "Hardware.h"
#include "HardwareDefines.h"
#include "IDisplay.h"
#include "ISpriteBatch.h"
#include "OAM.h"
#include "RenderParams.h"
#include "System.h"

NAMESPACE(SPlay)

OAM::OAM()	:
	m_pSpriteBatch(NULL)
{
	for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
	{
		m_pObjs[iLoop]	= NULL;
	}
}

OAM::~OAM()
{
	close();
}

OAM* OAM::create()
{
	OAM*	pOAM	= new OAM();

	if (false == pOAM->initialize())
	{
		delete	pOAM;

		pOAM	= NULL;
	}

	return	pOAM;
}

bool OAM::initialize()
{
	for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
	{
		m_pObjs[iLoop]	= new Obj();
	}

	// Clear Objs
	clearObjs();

	// Create sprite batch
	m_pSpriteBatch	= createSpriteBatch(gsc_iMaxObjs);
	
	if (NULL == m_pSpriteBatch)
	{
		return	false;
	}
	
	return	true;
}

void OAM::close()
{
	for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
	{
		delete	m_pObjs[iLoop];

		m_pObjs[iLoop]	= NULL;
	}
		
	delete	m_pSpriteBatch;

	m_pSpriteBatch	= NULL;
}

void OAM::render(int _iLayer)
{
	m_pSpriteBatch->startBatch();
	
	float	fZ			= 0.0f;
	float	fZIncrement	= 1.0f / static_cast<float>(gsc_iMaxObjs);
	int		iTexture	= Hardware::getObjVRAM()->getTextureIndex();

	// Draw sprites in back to front order
	for (int iLoop = gsc_iMaxObjs - 1; iLoop >= 0; --iLoop)
	{
		m_pObjs[iLoop]->render(m_pSpriteBatch, iTexture, _iLayer, fZ);

		fZ	+= fZIncrement;
	}

	m_pSpriteBatch->endBatch();
}

void OAM::setPosition(int _iIndex, float _fX, float _fY)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setPosition(_fX, _fY);
}

void OAM::setTileNumber(int _iIndex, int _iTileNumber)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setTileNumber(_iTileNumber);
}

void OAM::setObjSize(int _iIndex, ObjSize _eObjSize)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setObjSize(_eObjSize);
}

bool OAM::getActive(int _iIndex)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	return	m_pObjs[_iIndex]->getActive();
}

void OAM::setActive(int _iIndex, bool _bActive)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setActive(_bActive);
}

void OAM::setBG(int _iIndex, int _iLayer)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setBG(_iLayer);
}

Flip OAM::getFlip(int _iIndex)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	return	m_pObjs[_iIndex]->getFlip();
}

void OAM::setFlip(int _iIndex, Flip _eFlip)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setFlip(_eFlip);
}

void OAM::setSortOrder(int _iIndex, int _iSortOrder)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setSortOrder(_iSortOrder);
}

void OAM::setUsed(int _iIndex, bool _bUsed)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxObjs, "OAM index is invalid");

	m_pObjs[_iIndex]->setUsed(_bUsed);
}

void OAM::clearObjs()
{
	for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
	{
		m_pObjs[iLoop]->clear();
	}
}

int OAM::getAvailableObj()
{
	for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
	{
		if (false == m_pObjs[iLoop]->getUsed())
		{
			return	iLoop;
		}
	}

	return	-1;
}

ENDNAMESPACE
