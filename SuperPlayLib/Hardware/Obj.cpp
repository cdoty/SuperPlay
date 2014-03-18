// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stddef.h>

#include "Hardware.h"
#include "ISpriteBatch.h"
#include "Obj.h"
#include "System.h"

NAMESPACE(SPlay)

// Initial position
static const	float	gsc_fInitialX	= -64.0f;
static const	float	gsc_fInitialY	= -64.0f;

Obj::Obj()	:
	m_fX(gsc_fInitialX),
	m_fY(gsc_fInitialY),
	m_iSortOrder(gsc_iMaxObjs),
	m_iTileNumber(-1),
	m_eObjSize(ObjSizes),
	m_iLayer(0),
	m_eFlip(NoFlip),
	m_bActive(false),
	m_bUsed(false)
{
}

Obj::~Obj()
{
	close();
}

Obj* Obj::create()
{
	Obj*	pObj	= new Obj();

	if (false == pObj->initialize())
	{
		delete	pObj;

		pObj	= NULL;
	}

	return	pObj;
}

bool Obj::initialize()
{
	return	true;
}

void Obj::close()
{
}

void Obj::render(ISpriteBatch* _pSpriteBatch, int _iTexture, int _iLayer, float _fZ)
{
	if (m_iLayer == _iLayer && true == m_bActive && m_iTileNumber != -1 && m_eObjSize != ObjSizes)
	{
		float	fWidth	= getWidth();
		float	fHeight	= getHeight();

		const GameHeader&	gameHeader	= System::getGameHeader();

		if (m_fX + fWidth >= 0 && m_fY + fHeight >= 0 && m_fX < gameHeader.iScreenWidth && m_fY < gameHeader.iScreenHeight)
		{
			RenderParams	renderParams;

			renderParams.fX			= m_fX;
			renderParams.fY			= m_fY;
			renderParams.fZ			= _fZ;
			renderParams.fWidth		= fWidth;
			renderParams.fHeight	= fHeight;
			renderParams.fU1		= m_fU1;
			renderParams.fV1		= m_fV1;
			renderParams.fU2		= m_fU2;
			renderParams.fV2		= m_fV2;

			renderParams.iTextureIndex	= _iTexture;

			_pSpriteBatch->addSprite(renderParams);
		}
	}
}

void Obj::setTileNumber(int _iTileNumber)
{
	m_iTileNumber	= _iTileNumber;

	updateUVs();
}

void Obj::setObjSize(ObjSize _eObjSize)
{
	m_eObjSize	= _eObjSize;

	updateUVs();
}

void Obj::setFlip(Flip _eFlip)
{
	m_eFlip	= _eFlip;

	updateUVs();
}

void Obj::clear()
{
	m_iTileNumber	= -1;
	m_eObjSize		= ObjSizes;
	m_fX			= gsc_fInitialX;
	m_fY			= gsc_fInitialY;
	m_bActive		= false;
	m_iLayer		= 0;
	m_eFlip			= NoFlip;
	m_bUsed			= false;
}

void Obj::updateUVs()
{
	if (m_iTileNumber != -1 && m_eObjSize != ObjSizes)
	{
		Hardware::getObjVRAM()->getObjUVs(m_iTileNumber, m_eObjSize, m_eFlip, m_fU1, m_fV1, m_fU2, m_fV2);
	}
}

float Obj::getWidth()
{
	float	fWidth	= 0.0f;

	switch (m_eObjSize)
	{
		case ObjSize16x16:
		case ObjSize16x32:
			fWidth	= 16.0f;

			break;

		case ObjSize32x16:
		case ObjSize32x32:
		case ObjSize32x64:
			fWidth	= 32.0f;

			break;

		case ObjSize64x32:
		case ObjSize64x64:
			fWidth	= 64.0f;

			break;
	}

	return	fWidth;
}

float Obj::getHeight()
{
	float	fHeight	= 0.0f;

	switch (m_eObjSize)
	{
		case ObjSize16x16:
		case ObjSize32x16:
			fHeight	= 16.0f;

			break;

		case ObjSize16x32:
		case ObjSize32x32:
		case ObjSize64x32:
			fHeight	= 32.0f;

			break;

		case ObjSize32x64:
		case ObjSize64x64:
			fHeight	= 64.0f;

			break;
	}

	return	fHeight;
}

ENDNAMESPACE
