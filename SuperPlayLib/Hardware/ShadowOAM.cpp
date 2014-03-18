// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdlib.h>

#include "Hardware.h"
#include "HardwareDefines.h"
#include "ISpriteBatch.h"
#include "ShadowOAM.h"

NAMESPACE(SPlay)

ShadowOAM::ShadowOAM()	:
	super(),
	m_bReSort(true)
{
	m_vecSortedObjs.resize(gsc_iMaxObjs);
}

ShadowOAM::~ShadowOAM()
{
	close();
}

ShadowOAM* ShadowOAM::create()
{
	ShadowOAM*	pShadowOAM	= new ShadowOAM();

	if (false == pShadowOAM->initialize())
	{
		delete	pShadowOAM;

		pShadowOAM	= NULL;
	}

	return	pShadowOAM;
}

bool ShadowOAM::initialize()
{
	if (false == super::initialize())
	{
		return	false;
	}

	return	true;
}

void ShadowOAM::close()
{
	
}

void ShadowOAM::render(int _iLayer)
{
	if (true == m_bReSort)
	{
		m_vecSortedObjs.clear();

		for (int iLoop = 0; iLoop < gsc_iMaxObjs; ++iLoop)
		{
			Obj*	pObject	= m_pObjs[iLoop];

			if (true == pObject->getUsed() && true == pObject->getActive())
			{
				m_vecSortedObjs.push_back(pObject);
			}
		}

		qsort(&m_vecSortedObjs[0], m_vecSortedObjs.size(), sizeof(Obj*), objSort);

		m_bReSort	= false;
	}

	m_pSpriteBatch->startBatch();
	
	float	fZ			= 0.0f;
	float	fZIncrement	= 1.0f / static_cast<float>(gsc_iMaxObjs);
	int		iTexture	= Hardware::getObjVRAM()->getTextureIndex();

	int	t_c	= static_cast<int>(m_vecSortedObjs.size());

	// Draw in back to front order
	for (int iLoop = t_c - 1; iLoop >= 0; --iLoop)
	{
		m_vecSortedObjs[iLoop]->render(m_pSpriteBatch, iTexture, _iLayer, fZ);

		fZ	+= fZIncrement;
	}

	m_pSpriteBatch->endBatch();
}

void ShadowOAM::setSortOrder(int _iIndex, int _iSortOrder)
{
	super::setSortOrder(_iIndex, _iSortOrder);

	m_bReSort	= true;
}

void ShadowOAM::setActive(int _iIndex, bool _bActive)
{
	super::setActive(_iIndex, _bActive);

	m_bReSort	= true;
}

void ShadowOAM::clearObjs()
{
	m_bReSort	= true;

	return	super::clearObjs();
}

int ShadowOAM::getAvailableObj()
{
	m_bReSort	= true;

	return	super::getAvailableObj();
}

int ShadowOAM::objSort(const void* _pObj1, const void* _pObj2)
{
	Obj*	pObj1	= *(Obj**)(_pObj1);
	Obj*	pObj2	= *(Obj**)(_pObj2);

	if (pObj1->getSortOrder() < pObj2->getSortOrder())
	{
		return	-1;
	}
	
	else if (pObj1->getSortOrder() > pObj2->getSortOrder())
	{
		return	1;
	}
	
	return	0;
}

ENDNAMESPACE
