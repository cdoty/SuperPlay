// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stddef.h>

#include "IDisplay.h"
#include "Log.h"
#include "ObjVRAM.h"
#include "System.h"

NAMESPACE(SPlay)

// To achieve 128 sprites, the texture must have room for a 16x16 sprite array.
// This allows for 256 sprites, but 128 was chosen to remain consistent with the SNES.
static const int	gsc_iSpriteGridSize	= 16;

ObjVRAM::ObjVRAM()	:
	m_iTileSize(gsc_iMinObjSize),
	m_iVRAMWidth(gsc_iMaxObjSize * gsc_iSpriteGridSize),
	m_iVRAMHeight(gsc_iMaxObjSize * gsc_iSpriteGridSize)
{
}

ObjVRAM::~ObjVRAM()
{
	close();
}

ObjVRAM* ObjVRAM::create()
{
	ObjVRAM*	pObjVRAM	= new ObjVRAM();

	if (false == pObjVRAM->initialize())
	{
		delete	pObjVRAM;

		pObjVRAM	= NULL;
	}

	return	pObjVRAM;
}

bool ObjVRAM::initialize()
{
	if (false == createTexture())
	{
		return	false;
	}

	setupUVIncrements();

	if (false == createTextureCoordinates())
	{
		return	false;
	}
	
	return	true;
}

void ObjVRAM::close()
{
	if (m_iTextureIndex != -1)
	{
		IDisplay*	pDisplay	= System::getDisplay();

		pDisplay->removeTexture(m_iTextureIndex);

		m_iTextureIndex	= -1;
	}
}

void ObjVRAM::getObjUVs(int _iTileIndex, ObjSize _eObjSize, Flip _eFlip, float& _fU1, float& _fV1, float& _fU2, float& _fV2)
{
	const TextureInfo& textureInfo	= m_vecTiles[_iTileIndex];

	if (_eFlip & HFlip)
	{
		_fU1	= textureInfo.fU1 + m_fUIncrement[_eObjSize];
		_fU2	= textureInfo.fU1;
	}

	else
	{
		_fU1	= textureInfo.fU1;
		_fU2	= textureInfo.fU1 + m_fUIncrement[_eObjSize];
	}

	if (_eFlip & VFlip)
	{
		_fV1	= textureInfo.fV1 + m_fVIncrement[_eObjSize];
		_fV2	= textureInfo.fV1;
	}

	else
	{
		_fV1	= textureInfo.fV1;
		_fV2	= textureInfo.fV1 + m_fVIncrement[_eObjSize];
	}
}

bool ObjVRAM::createTexture()
{
	IDisplay*	pDisplay	= System::getDisplay();

	m_iTextureIndex	= pDisplay->createTexture("ObjVRAM", m_iVRAMWidth, m_iVRAMHeight, Alpha8Bit, false);

	if (-1 == m_iTextureIndex)
	{
		Log::instance()->logError("Unable to create ObjVRAM texture");

		return	false;
	}

	return	true;
}

void ObjVRAM::setupUVIncrements()
{
	float	fUIncrement	= static_cast<float>(m_iTileSize) / m_iVRAMWidth;
	float	fVIncrement	= static_cast<float>(m_iTileSize) / m_iVRAMHeight;

	m_fUIncrement[ObjSize16x16]	= 1.0f * fUIncrement;
	m_fVIncrement[ObjSize16x16]	= 1.0f * fVIncrement;

	m_fUIncrement[ObjSize16x32]	= 1.0f * fUIncrement;
	m_fVIncrement[ObjSize16x32]	= 2.0f * fVIncrement;

	m_fUIncrement[ObjSize32x16]	= 2.0f * fUIncrement;
	m_fVIncrement[ObjSize32x16]	= 1.0f * fVIncrement;

	m_fUIncrement[ObjSize32x32]	= 2.0f * fUIncrement;
	m_fVIncrement[ObjSize32x32]	= 2.0f * fVIncrement;

	m_fUIncrement[ObjSize32x64]	= 2.0f * fUIncrement;
	m_fVIncrement[ObjSize32x64]	= 4.0f * fVIncrement;

	m_fUIncrement[ObjSize64x32]	= 4.0f * fUIncrement;
	m_fVIncrement[ObjSize64x32]	= 2.0f * fVIncrement;

	m_fUIncrement[ObjSize64x64]	= 4.0f * fUIncrement;
	m_fVIncrement[ObjSize64x64]	= 4.0f * fVIncrement;
}

bool ObjVRAM::createTextureCoordinates()
{
	int	iTilesWide	= m_iVRAMWidth / m_iTileSize;
	int	iTilesHigh	= m_iVRAMHeight / m_iTileSize;

	float	fY	= 0.0f;

	for (int iYLoop = 0; iYLoop < iTilesHigh; ++iYLoop)
	{
		float	fX	= 0.0f;

		for (int iXLoop = 0; iXLoop < iTilesWide; ++iXLoop)
		{
			TextureInfo	textureUVs;

			textureUVs.fU1		= fX;
			textureUVs.fV1		= fY;
			textureUVs.pOffset	= iYLoop * m_iVRAMWidth * m_iTileSize + iXLoop * m_iTileSize;
							
			m_vecTiles.push_back(textureUVs);

			fX	+= m_fUIncrement[0];
		}

		fY	+= m_fVIncrement[0];
	}

	return	true;
}

ENDNAMESPACE
