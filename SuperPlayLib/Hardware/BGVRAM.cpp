// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stddef.h>

#include "AssertLog.h"
#include "BGVRAM.h"
#include "HardwareDefines.h"
#include "IDisplay.h"
#include "Log.h"
#include "System.h"

NAMESPACE(SPlay)

// To achieve 1024 tiles, the texture must have room for a 32x32 tile array.
static const int	gsc_iTileGridSize	= 32;

BGVRAM::BGVRAM(TileSize _eTileSize)	:
	m_eTileSize(_eTileSize),
	m_iVRAMWidth(gsc_iMaxTileSize * gsc_iTileGridSize),
	m_iVRAMHeight(gsc_iMaxTileSize * gsc_iTileGridSize)
{
	switch (m_eTileSize)
	{
		case TileSize8x8:
			m_iTileSize	= 8;

			break;

		case TileSize16x16:
			m_iTileSize	= 16;

			break;

		case TileSize32x32:
			m_iTileSize	= 32;

			break;

		default:
			break;
	}

	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		m_iTextureIndex[iLoop]	= -1;
	}
}

BGVRAM::~BGVRAM()
{
	close();
}

BGVRAM* BGVRAM::create(TileSize _eTileSize)
{
	BGVRAM*	pBGVRAM	= new BGVRAM(_eTileSize);

	if (false == pBGVRAM->initialize())
	{
		delete	pBGVRAM;

		pBGVRAM	= NULL;
	}

	return	pBGVRAM;
}

bool BGVRAM::initialize()
{
	if (false == createTexture())
	{
		return	false;
	}

	if (false == createTextureCoordinates())
	{
		return	false;
	}
	
	return	true;
}

void BGVRAM::close()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		if (m_iTextureIndex[iLoop] != -1)
		{
			IDisplay*	pDisplay	= System::getDisplay();

			pDisplay->removeTexture(m_iTextureIndex[iLoop]);

			m_iTextureIndex[iLoop]	= -1;
		}
	}
}

int BGVRAM::getTextureIndex(int _iBG) const
{
	ASSERT_LOG(_iBG >= 0 && _iBG < gsc_iMaxBGs, "BG index is invalid");

	return	m_iTextureIndex[_iBG];
}

void BGVRAM::getTileUVs(int _iTileIndex, Flip _eFlip, float& _fU1, float& _fV1, float& _fU2, float& _fV2)
{
	if (_iTileIndex < 0 || _iTileIndex >= static_cast<int>(m_vecTiles.size()))
	{
		_fU1	= 1.0f;
		_fV1	= 1.0f;
		_fU2	= 1.0f;
		_fV2	= 1.0f;
	
		return;
	}

	const TextureInfo& textureInfo	= m_vecTiles[_iTileIndex];

	if (_eFlip & HFlip)
	{
		_fU1	= textureInfo.fU2;
		_fU2	= textureInfo.fU1;
	}

	else
	{
		_fU1	= textureInfo.fU1;
		_fU2	= textureInfo.fU2;
	}

	if (_eFlip & VFlip)
	{
		_fV1	= textureInfo.fV2;
		_fV2	= textureInfo.fV1;
	}

	else
	{
		_fV1	= textureInfo.fV1;
		_fV2	= textureInfo.fV2;
	}
}

void BGVRAM::getPixelUV(int _iTileIndex, Flip _eFlip, int _iX, int _iY, float& _fU1, float& _fV1, float& _fU2, float& _fV2)
{
	if (_iTileIndex < 0 || _iTileIndex >= static_cast<int>(m_vecTiles.size()))
	{
		_fU1	= 1.0f;
		_fV1	= 1.0f;
		_fU2	= 1.0f;
		_fV2	= 1.0f;
	
		return;
	}

	const TextureInfo& textureInfo	= m_vecTiles[_iTileIndex];

	if (_eFlip & HFlip)
	{
		_fU1	= textureInfo.fU2 - m_fPixelIncrement * static_cast<float>(_iX);
	}

	else
	{
		_fU1	= textureInfo.fU1 + m_fPixelIncrement * static_cast<float>(_iX);
	}

	if (_eFlip & VFlip)
	{
		_fV1	= textureInfo.fV2 - m_fPixelIncrement * static_cast<float>(_iY);
	}

	else
	{
		_fV1	= textureInfo.fV1 + m_fPixelIncrement * static_cast<float>(_iY);
	}

	_fU2	= _fU1;
	_fV2	= _fV1;
}

bool BGVRAM::createTexture()
{
	IDisplay*	pDisplay	= System::getDisplay();

	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		char	szTextureName[16];

		sprintf(szTextureName, "BGVRAM%d", iLoop + 1);

		m_iTextureIndex[iLoop]	= pDisplay->createTexture(szTextureName, m_iVRAMWidth, m_iVRAMHeight, Alpha8Bit, true);

		if (-1 == m_iTextureIndex[iLoop])
		{
			Log::instance()->logError("Unable to create %s texture", szTextureName);

			return	false;
		}
	}

	return	true;
}

bool BGVRAM::createTextureCoordinates()
{
	float	fTileX	= static_cast<float>(m_iTileSize) / m_iVRAMWidth;
	float	fTileY	= static_cast<float>(m_iTileSize) / m_iVRAMHeight;

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
			textureUVs.fU2		= fX + fTileX;
			textureUVs.fV2		= fY + fTileY;
			textureUVs.pOffset	= iYLoop * m_iVRAMWidth * m_iTileSize + iXLoop * m_iTileSize;
							
			m_vecTiles.push_back(textureUVs);

			fX	+= fTileX;
		}

		fY	+= fTileY;
	}

	m_fPixelIncrement	= 1.0f / static_cast<float>(m_iVRAMWidth);

	return	true;
}

ENDNAMESPACE
