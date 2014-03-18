// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>

#include "AssertLog.h"
#include "BG.h"
#include "GameHeader.h"
#include "Hardware.h"
#include "IDisplay.h"
#include "Image.h"
#include "ISpriteBatch.h"
#include "System.h"

NAMESPACE(SPlay)

BG::BG(int _iIndex)	:
	m_pSpriteBatch(NULL),
	m_iTileSize(0),
	m_iTilesWide(0),
	m_iTilesHigh(0),
	m_iScrollX(0),
	m_iScrollY(0),
	m_iIndex(_iIndex),
	m_iMosaic(0),
	m_bWrap(false),
	m_bActive(false)
{
}

BG::~BG()
{
	close();
}

BG* BG::create(int _iIndex)
{
	BG*	pBG	= new BG(_iIndex);

	if (false == pBG->initialize())
	{
		delete	pBG;

		pBG	= NULL;
	}

	return	pBG;
}

bool BG::initialize()
{
	return	true;
}

void BG::close()
{
	delete	m_pSpriteBatch;

	m_pSpriteBatch	= NULL;
}

void BG::render()
{
	if (true == m_bActive && m_pSpriteBatch != NULL)
	{
		if (m_iMosaic > 0)
		{
			return	renderMosaic();
		}

		float	fStartTileX;

		RenderParams	renderParams;
		renderParams.fZ	= 1.0f;

		int	iScrollX	= m_iScrollX % m_iMapWidth;

		if (iScrollX < 0)
		{
			int iScrollPart	= (-iScrollX % m_iTileSize);

			if (iScrollPart != 0)
			{
				fStartTileX = static_cast<float>(-m_iTileSize + iScrollPart);
			}

			else
			{
				fStartTileX	= 0.0f;
			}
		}

		else
		{
			fStartTileX = static_cast<float>(-(iScrollX % m_iTileSize));
		}

		int	iScrollY	= m_iScrollY % m_iMapHeight;

		if (iScrollY < 0)
		{
			int iScrollPart	= (-iScrollY % m_iTileSize);

			if (iScrollPart != 0)
			{
				renderParams.fY = static_cast<float>(-m_iTileSize + iScrollPart);
			}

			else
			{
				renderParams.fY	= 0.0f;
			}
		}

		else
		{
			renderParams.fY	= static_cast<float>(-(iScrollY % m_iTileSize));
		}

		const GameHeader&	gameHeader	= System::getGameHeader();

		int	iEndX	= iScrollX + gameHeader.iScreenWidth;
		int	iEndY	= iScrollY + gameHeader.iScreenHeight;

		float	fTileSize	= static_cast<float>(m_iTileSize);

		int	iTileStartX	= static_cast<int>(floor(static_cast<float>(iScrollX) / fTileSize));
		int	iTileStartY	= static_cast<int>(floor(static_cast<float>(iScrollY) / fTileSize));
		int	iTileEndX	= static_cast<int>(ceil(static_cast<float>(iEndX) / fTileSize));
		int	iTileEndY	= static_cast<int>(ceil(static_cast<float>(iEndY) / fTileSize));

		BGVRAM*	pVRAM	= Hardware::getBGVRAM();

		renderParams.iTextureIndex	= pVRAM->getTextureIndex(m_iIndex);
		renderParams.fWidth			= fTileSize;
		renderParams.fHeight		= fTileSize;

		m_pSpriteBatch->startBatch();

		for (int iYLoop = iTileStartY; iYLoop < iTileEndY; ++iYLoop)
		{
			int	iTileY	= iYLoop;

			if (true == m_bWrap)
			{
				if (iTileY < 0)
				{
					iTileY	+= m_iTilesHigh;
				}

				else if (iTileY >= m_iTilesHigh)
				{
					iTileY	-= m_iTilesHigh;
				}
			}
			
			else if (iTileY < 0 || iTileY >= m_iTilesHigh)
			{
				renderParams.fY	+= m_iTileSize;

				continue;
			}

			int	iTileIndex		= iTileY * m_iTilesWide;

			renderParams.fX	= fStartTileX;

			for (int iXLoop = iTileStartX; iXLoop < iTileEndX; ++iXLoop)
			{
				int	iTileX	= iXLoop;

				if (true == m_bWrap)
				{
					if (iTileX < 0)
					{
						iTileX	+= m_iTilesWide;
					}

					else if (iTileX >= m_iTilesWide)
					{
						iTileX	-= m_iTilesWide;
					}
				}

				else if (iTileX < 0 || iTileX >= m_iTilesWide)
				{
					renderParams.fX	+= fTileSize;

					continue;
				}

				const TileInfo&	tileInfo	= m_vecTileMap[iTileIndex + iTileX];

				int	iTile	= tileInfo.iTileIndex;

				pVRAM->getTileUVs(iTile, tileInfo.eFlip, renderParams.fU1, renderParams.fV1, renderParams.fU2, renderParams.fV2);

				m_pSpriteBatch->addSprite(renderParams);

				renderParams.fX	+= fTileSize;
			}

			renderParams.fY	+= m_iTileSize;
		}

		m_pSpriteBatch->endBatch();
	}
}

void BG::setScrollPosition(int _iOffsetX, int _iOffsetY)
{
	m_iScrollX	= _iOffsetX;
	m_iScrollY	= _iOffsetY;

	if (true == m_bWrap)
	{
		if (m_iScrollX <= -m_iMapWidth)
		{
			while (m_iScrollX <= -m_iMapWidth)
			{
				m_iScrollX	+= m_iMapWidth;
			}
		}

		else if (m_iScrollX >= m_iMapWidth * 2)
		{
			while (m_iScrollX >= m_iMapWidth * 2)
			{
				m_iScrollX	-= m_iMapWidth;
			}
		}

		if (m_iScrollY <= -m_iMapHeight)
		{
			while (m_iScrollY <= -m_iMapHeight)
			{
				m_iScrollY	+= m_iMapHeight;
			}
		}

		else if (m_iScrollY >= m_iMapHeight * 2)
		{
			while (m_iScrollY >= m_iMapHeight * 2)
			{
				m_iScrollY	-= m_iMapHeight;
			}
		}
	}
}

bool BG::setupSpriteBatch()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	m_pSpriteBatch	= createSpriteBatch((gameHeader.iScreenWidth / m_iTileSize + 2) * (gameHeader.iScreenHeight / m_iTileSize + 2));

	if (NULL == m_pSpriteBatch)
	{
		return	false;
	}

	return	true;
}

void BG::renderMosaic()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	int	iWidth	= gameHeader.iScreenWidth;
	int	iHeight	= gameHeader.iScreenHeight;

	RenderParams	renderParams;

	BGVRAM*	pVRAM	= Hardware::getBGVRAM();

	int	iMosaic	= m_iMosaic + 1;

	renderParams.fY				= 0.0f;
	renderParams.fZ				= 1.0f;
 	renderParams.fWidth			= static_cast<float>(iMosaic);
	renderParams.fHeight		= static_cast<float>(iMosaic);
	renderParams.iTextureIndex	= pVRAM->getTextureIndex(m_iIndex);

	int	iTileAndValue	= (m_iTileSize - 1);

	int	iSizeX			= (iWidth < m_iMapWidth ? iWidth : m_iMapWidth);	
	int	iSizeY			= (iHeight < m_iMapHeight ? iHeight : m_iMapHeight);

	int	iPixelWidth		= m_iTilesWide * m_iTileSize;
	int	iPixelHeight	= m_iTilesHigh * m_iTileSize;

	int	iScrollX		= (m_iScrollX % m_iMapWidth);
	int	iYOffset		= (m_iScrollY % m_iMapHeight);
	
	if (false == m_bWrap)
	{
		int	iStartX;
		int	iEndX;
	
		if (iScrollX >= 0)
		{
			iStartX = 0;
			iEndX	= m_iMapWidth - iScrollX;
		}

		else
		{
			iStartX = -iScrollX;
			iEndX	= m_iMapWidth - iScrollX;
		}

		int	iStartY;
		int	iEndY;
	
		if (iYOffset >= 0)
		{
			iStartY	= 0;
			iEndY	= m_iMapHeight - iYOffset;
		}

		else
		{
			iStartY	= -iYOffset;
			iEndY	= m_iMapHeight - iYOffset;
		}

		m_pSpriteBatch->startBatch(Rect(iStartX, iStartY, iEndX - iStartX, iEndY - iStartY));
	}

	else
	{
		m_pSpriteBatch->startBatch();
	}

	for (int iYLoop = 0; iYLoop < iSizeY;)
	{
		renderParams.fX	= 0.0f;

		// Wrap y offset
		if (true == m_bWrap)
		{
			iYOffset	%= iPixelHeight;

			if (iYOffset < 0)
			{
				iYOffset	+= iPixelHeight;
			}
		}
			
		// Skip areas outside of the tilemap
		else if (iYOffset < 0 || iYOffset >= iPixelHeight)
		{
			renderParams.fY++;
			iYOffset++;
			iYLoop++;

			continue;
		}
		
		int	iTileY	= (iYOffset / m_iTileSize) * m_iTilesWide;

		int	iXOffset	= iScrollX % m_iMapWidth;

 		renderParams.fWidth	= static_cast<float>(iMosaic);

		for (int iXLoop = 0; iXLoop < iSizeX;)
		{
			// Wrap x offset
			if (true == m_bWrap)
			{
				iXOffset	%= iPixelWidth;

				if (iXOffset < 0)
				{
					iXOffset	+= iPixelWidth;
				}
			}

			// Skip areas outside of the tilemap
			else if (iXOffset < 0 || iXOffset >= iPixelWidth)
			{
				renderParams.fX++;
				iXOffset++;
				iXLoop++;
									
				continue;
			}

			int	iIndex	= iTileY + (iXOffset / m_iTileSize);

			const TileInfo&	tileInfo	= m_vecTileMap[iIndex];

			int	iTile	= tileInfo.iTileIndex;
			
			pVRAM->getPixelUV(iTile, tileInfo.eFlip, iXOffset & iTileAndValue, iYOffset & iTileAndValue, renderParams.fU1, renderParams.fV1, 
				renderParams.fU2, renderParams.fV2);

			m_pSpriteBatch->addSprite(renderParams);

			renderParams.fX	+= iMosaic;
			iXOffset		+= iMosaic;
			iXLoop			+= iMosaic;
		}

		renderParams.fY	+= iMosaic;
		iYOffset		+= iMosaic;
		iYLoop			+= iMosaic;
	}

	m_pSpriteBatch->endBatch();
}

ENDNAMESPACE
