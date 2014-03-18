// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <TinySTL/stddef.h>

#include "AssertLog.h"
#include "HardwareDefines.h"
#include "IDisplay.h"
#include "ISpriteBatch.h"
#include "Log.h"
#include "System.h"
#include "Text.h"
#include "Utilities.h"

NAMESPACE(SPlay)

Text::Text()	:
	m_pImageBuffer(NULL),
	m_pPaletteBuffer(NULL),
	m_iCharacterCount(0),
	m_iTextureIndex(-1),
	m_pSpriteBatch(NULL),
	m_bActive(false)
{
}

Text::~Text()
{
	close();
}

Text* Text::create()
{
	Text*	pText	= new Text();

	if (false == pText->initialize())
	{
		delete	pText;

		pText	= NULL;
	}

	return	pText;
}

bool Text::initialize()
{
	if (false == createTexture())
	{
		return	false;
	}

	if (false == setupSpriteBatch())
	{
		return	false;
	}

	return	true;
}

void Text::close()
{
	if (m_iTextureIndex != -1)
	{
		System::getDisplay()->removeTexture(m_iTextureIndex);
	}

	delete	m_pSpriteBatch;

	m_pSpriteBatch	= NULL;

	delete	m_pImageBuffer;

	m_pImageBuffer	= NULL;

	delete	m_pPaletteBuffer;

	m_pPaletteBuffer	= NULL;
}

void Text::render()
{
	if (true == m_bActive && m_pSpriteBatch != NULL)
	{
		RenderParams	renderParams;

		renderParams.fX				= 0.0f;
		renderParams.fY				= 0.0f;
		renderParams.fZ 			= 0.0f;
		renderParams.fWidth			= static_cast<float>(m_iScreenWidth);
		renderParams.fHeight		= static_cast<float>(m_iScreenHeight);
		renderParams.fU1			= 0.0f;
		renderParams.fV1			= 0.0f;
		renderParams.fU2			= m_fU2;
		renderParams.fV2			= m_fV2;
		renderParams.iTextureIndex	= m_iTextureIndex;
	
		m_pSpriteBatch->startBatch();

		m_pSpriteBatch->addSprite(renderParams);

		m_pSpriteBatch->endBatch();
	}
}

void Text::setFontData(uint8_t* _pImageBuffer, uint8_t* _pPaletteBuffer, int _iCharacterCount)
{
	m_pImageBuffer		= _pImageBuffer;
	m_pPaletteBuffer	= reinterpret_cast<uint32_t*>(_pPaletteBuffer); 
	m_iCharacterCount	= _iCharacterCount;
}

bool Text::clear(int _iX, int _iY, int _iWidth, int _iHeight)
{
	ITexture*	pTexture	= System::getDisplay()->getTexture(m_iTextureIndex);

	uint32_t*	pBuffer;
	int			iStride;

	if (false == pTexture->getBuffer(pBuffer, iStride))
	{
		return	false;
	}

	clearVRAM(_iX, _iY, _iWidth, _iHeight, pBuffer);

	pTexture->releaseBuffer();

	return	true;
}

bool Text::update(int _iX, int _iY, int _iWidth, int _iHeight, const uint8_t* _pMap, int _iMapStride)
{
	ITexture*	pTexture	= System::getDisplay()->getTexture(m_iTextureIndex);

	uint32_t*	pBuffer;
	int			iStride;

	if (false == pTexture->getBuffer(pBuffer, iStride))
	{
		return	false;
	}

	int	iX	= _iX * gsc_iFontSize;
	int	iY	= _iY * gsc_iFontSize;

	pBuffer	+= iY * m_iVRAMWidth + iX;

	const uint8_t*	pMap	= _pMap;

	iStride	= _iMapStride - _iWidth;

	for (int iYLoop = 0; iYLoop < _iHeight; ++iYLoop)
	{
		uint32_t*	pLine	= pBuffer;

		for (int iXLoop = 0; iXLoop < _iWidth; ++iXLoop)
		{
			int	iCharacter	= *pMap;
		
			if (-1 == iCharacter)
			{
				clearCharacter(pLine);
			}

			else if (iCharacter >= 0 && iCharacter < m_iCharacterCount)
			{
				drawCharacter(iCharacter, pLine);
			}

			pLine	+= gsc_iFontSize;
			pMap++;
		}

		pBuffer	+= m_iVRAMWidth;
		pMap	+= iStride;
	}

	pTexture->releaseBuffer();

	return	true;
}

bool Text::drawText(int _iX, int _iY, const char* _szString)
{
	int	iWidth	= static_cast<int>(strlen(_szString));
	int	iHeight	= 1;

	const	char*	szClippedString	= _szString;

	if (_iX < 0 && iWidth > -_iX)
	{
		// Scan into the string. _iX is negative.
		iWidth			+= _iX;
		szClippedString	-= _iX;
		_iX				= 0;
	}

	else if (_iX + iWidth >= m_iCharWidth && _iX < m_iCharWidth)
	{
		iWidth	-= (_iX + iWidth) - m_iCharWidth + 1;
	}

	int	iX		= _iX * gsc_iFontSize;
	int	iY		= _iY * gsc_iFontSize;
	
	if (iX < 0 || iX + iWidth > m_iVRAMWidth || iY < 0 || iY + iHeight > m_iVRAMHeight)
	{
		return	false;
	}

	ITexture*	pTexture	= System::getDisplay()->getTexture(m_iTextureIndex);

	uint32_t*	pBuffer;
	int			iStride;

	if (false == pTexture->getBuffer(pBuffer, iStride))
	{
		return	false;
	}

	pBuffer	+= iY * m_iVRAMWidth + iX;

	const char*	pMap	= szClippedString;

	for (int iXLoop = 0; iXLoop < iWidth; ++iXLoop)
	{
		int	iCharacter	= *pMap - gsc_iFontStart;

		if (-1 == iCharacter)
		{
			clearCharacter(pBuffer);
		}
		
		else if (iCharacter >= 0 && iCharacter < m_iCharacterCount)
		{
			drawCharacter(iCharacter, pBuffer);
		}

		pBuffer	+= gsc_iFontSize;
		pMap++;
	}

	pTexture->releaseBuffer();

	return	true;
}

bool Text::createTexture()
{
	const GameHeader&	gameHeader	= System::getGameHeader();

	m_iScreenWidth	= gameHeader.iScreenWidth;
	m_iScreenHeight	= gameHeader.iScreenHeight;

	m_iVRAMWidth	= static_cast<int>(pow(2, ceil(Utilities::log2(m_iScreenWidth))));
	m_iVRAMHeight	= static_cast<int>(pow(2, ceil(Utilities::log2(m_iScreenHeight))));

	m_iCharWidth	= m_iVRAMWidth / 8;
	m_iCharHeight	= m_iVRAMHeight / 8;

	m_fU2	= static_cast<float>(m_iScreenWidth) / static_cast<float>(m_iVRAMWidth);
	m_fV2	= static_cast<float>(m_iScreenHeight) / static_cast<float>(m_iVRAMHeight);

	IDisplay*	pDisplay	= System::getDisplay();

	m_iTextureIndex	= pDisplay->createTexture("Text", m_iVRAMWidth, m_iVRAMHeight, Alpha8Bit, false);

	if (-1 == m_iTextureIndex)
	{
		Log::instance()->logError("Unable to create Text texture");

		return	false;
	}

	return	true;
}

bool Text::setupSpriteBatch()
{
	m_pSpriteBatch	= createSpriteBatch(1);

	if (NULL == m_pSpriteBatch)
	{
		return	false;
	}

	return	true;
}

void Text::drawCharacter(int _iIndex, uint32_t* _pVRAM)
{
	if (m_pPaletteBuffer != NULL)
	{
		uint8_t*	pFont	= m_pImageBuffer + _iIndex * gsc_iFontSize * gsc_iFontSize;
		uint32_t*	pDest	= _pVRAM;

		int	iStride	= m_iVRAMWidth - gsc_iFontSize;
		
		for (int iYLoop = 0; iYLoop < gsc_iFontSize; ++iYLoop)
		{
			for (int iXLoop = 0; iXLoop < gsc_iFontSize; ++iXLoop)
			{
				*pDest	= m_pPaletteBuffer[*pFont];

				pFont++;
				pDest++;
			}

			pDest	+= iStride;
		}
	}

	else
	{
		uint32_t*	pFont	= reinterpret_cast<uint32_t*>(m_pImageBuffer) + _iIndex * gsc_iFontSize * gsc_iFontSize;
		uint32_t*	pDest	= _pVRAM;

		int	iSize	= gsc_iFontSize * sizeof(uint32_t);

		for (int iYLoop = 0; iYLoop < gsc_iFontSize; ++iYLoop)
		{
			memcpy(pDest, pFont, iSize);

			pFont	+= gsc_iFontSize;
			pDest	+= m_iVRAMWidth;
		}
	}
}

void Text::clearCharacter(uint32_t* _pVRAM)
{
	uint32_t*	pDest	= _pVRAM;

	int	iSize	= gsc_iFontSize * sizeof(uint32_t);

	for (int iYLoop = 0; iYLoop < gsc_iFontSize; ++iYLoop)
	{
		memset(pDest, 0, iSize);

		pDest	+= m_iVRAMWidth;
	}
}

bool Text::clearVRAM(int _iX, int _iY, int _iWidth, int _iHeight, uint32_t*& _pBuffer)
{
	int	iX		= _iX * gsc_iFontSize;
	int	iY		= _iY * gsc_iFontSize;
	int	iWidth	= _iWidth * gsc_iFontSize;
	int	iHeight	= _iHeight * gsc_iFontSize;
	
	if (iX < 0 || iX + _iWidth > m_iVRAMWidth || iY < 0 || iY + iHeight > m_iVRAMHeight)
	{
		return	false;
	}

	_pBuffer	+= iY * m_iVRAMWidth + iX;

	int	iByteWidth	= iWidth * sizeof(uint32_t);

	uint32_t*	pStart	= _pBuffer;

	for (int iLoop = 0; iLoop < _iHeight; ++iLoop)
	{
		memset(pStart, 0, iByteWidth);

		pStart	+= m_iVRAMWidth;
	}

	return	true;
}

bool Text::drawGrid()
{
	ITexture*	pTexture	= System::getDisplay()->getTexture(m_iTextureIndex);

	uint32_t*	pBuffer;
	int			iStride;

	if (false == pTexture->getBuffer(pBuffer, iStride))
	{
		return	false;
	}

	for (int iYLoop = 0; iYLoop < m_iVRAMHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < m_iVRAMWidth; ++iXLoop)
		{
			if (0 == iYLoop % 8 || 0 == iXLoop % 8)
			{
				*pBuffer	= 0xFFFFFFFF;
			}

			else
			{
				*pBuffer	= 0x00000000;
			}

			pBuffer++;
		}
	}

	pTexture->releaseBuffer();

	return	true;
}

ENDNAMESPACE
