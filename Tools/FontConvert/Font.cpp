// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdio.h>
#include <stddef.h>

#include "Font.h"
#include "Functions.h"
#include "HardwareDefines.h"
#include "Log.h"
#include "LodePNG\lodepng.h"

Font::Font()	:
	m_pPalette(NULL),
	m_iPaletteCount(0),
	m_bPaletted(false)
{
}

Font::~Font()
{
	close();
}

Font* Font::create()
{
	Font*	pFont	= new Font();

	if (false == pFont->initialize())
	{
		delete	pFont;

		pFont	= NULL;
	}

	return	pFont;
}

bool Font::initialize()
{
	return	true;
}

void Font::close()
{
	delete	m_pPalette;

	m_pPalette	= NULL;

	int	t_c	= static_cast<int>(m_vec8BitTiles.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete[]	m_vec8BitTiles[iLoop].pImage;
	}

	m_vec8BitTiles.clear();

	t_c	= static_cast<int>(m_vec32BitTiles.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete[]	m_vec32BitTiles[iLoop].pImage;
	}

	m_vec32BitTiles.clear();
}

bool Font::load(const std::string& _strFilename)
{
	uint32_t	iWidth;
	uint32_t	iHeight;
	uint8_t*	pImageBuffer	= NULL;
	
	delete[]	m_pPalette;

	m_pPalette		= new uint8_t[256 * 4];

	if (LodePNG_decode_file(&pImageBuffer, &iWidth, &iHeight, _strFilename.c_str(), 3, 8, m_pPalette, &m_iPaletteCount) != 0)
	{
		m_bPaletted	= false;

		if (LodePNG_decode_file(&pImageBuffer, &iWidth, &iHeight, _strFilename.c_str(), 6, 8) != 0)
		{
			Log::instance()->logError("Unable to load font image");

			return	false;
		}
	}

	else if (m_iPaletteCount > 0)
	{
		m_bPaletted	= true;

		uint32_t*	pPalette	= reinterpret_cast<uint32_t*>(m_pPalette);

		for (int iLoop = 0; iLoop < m_iPaletteCount; iLoop++)
		{
			uint32_t	uValue = pPalette[iLoop];

			uint32_t	uRed	= (uValue & 0xFF);
			uint32_t	uGreen	= (uValue & 0xFF00) >> 8;
			uint32_t	uBlue	= (uValue & 0xFF0000) >> 16;
			uint32_t	uAlpha	= (uValue & 0xFF000000) >> 24;

			pPalette[iLoop]	= (uAlpha << 24) | (uRed << 16) | (uGreen << 8) | (uBlue);
		}
	}

	m_iWidth	= iWidth;
	m_iHeight	= iHeight;

	if (true == m_bPaletted)
	{
		extract8BitFont(pImageBuffer);
	}

	else
	{
		extract32BitFont(pImageBuffer);
	}

	free(pImageBuffer);

	return	true;
}

bool Font::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
{
	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strPNGFilename)))
	{
		return	false;
	}

	if (false == writePNG(_strPNGFilename))
	{
		return	false;
	}

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strXMLFilename)))
	{
		return	false;
	}

	if (false == writeXML(_strPNGFilename, _strXMLFilename))
	{
		return	false;
	}

	return	true;
}

bool Font::writePNG(const std::string& _strFilename)
{
	if (true == m_bPaletted)
	{
		int	t_c	= static_cast<int>(m_vec8BitTiles.size());

		if (0 == t_c)
		{
			return	false;
		}


		int	iWidth	= m_vec8BitTiles[0].iWidth;
		int	iHeight	= m_vec8BitTiles[0].iHeight;
		int	iSize	= iWidth * iHeight;

		uint8_t*	pBuffer	= new uint8_t[iSize * t_c];

		memset(pBuffer, 0, iSize * t_c);

		uint8_t*	pDest	= pBuffer;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			uint8_t*	pSrc	= m_vec8BitTiles[iLoop].pImage;

			memcpy(pDest, pSrc, iSize);

			pDest	+= iSize;
		}

		if (LodePNG_encode_file(_strFilename.c_str(), pBuffer, iWidth, iHeight * t_c, 3, 8, m_pPalette, m_iPaletteCount) != 0)
		{
			return	false;
		}
	}

	else
	{
		int	t_c	= static_cast<int>(m_vec32BitTiles.size());

		if (0 == t_c)
		{
			return	false;
		}


		int	iWidth	= m_vec32BitTiles[0].iWidth;
		int	iHeight	= m_vec32BitTiles[0].iHeight;
		int	iSize	= iWidth * iHeight;

		uint32_t*	pBuffer	= new uint32_t[iSize * t_c];

		memset(pBuffer, 0, iSize * t_c);

		uint32_t*	pDest	= pBuffer;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			uint32_t*	pSrc	= m_vec32BitTiles[iLoop].pImage;

			memcpy(pDest, pSrc, iSize * sizeof(uint32_t));

			pDest	+= iSize;
		}

		if (LodePNG_encode_file(_strFilename.c_str(), reinterpret_cast<uint8_t*>(pBuffer), iWidth, iHeight * t_c, 6, 8) != 0)
		{
			return	false;
		}
	}

	return	true;
}

bool Font::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
{
	std::string	strPNGName	= Functions::getFullFilenameFromPath(_strPNGFilename);

	File*	pFile	= new File();

	if (false == pFile->create(_strXMLFilename.c_str()))
	{
		return	false;
	}

	if (false == pFile->writeString("<FontInfo>\n"))
	{
		return	false;
	}

	char	szString[256];

	sprintf(szString, "\t<ImageName>%s</ImageName>\n", strPNGName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	int	iWidth;
	int	iHeight;
	int	iCount;

	if (true == m_bPaletted)
	{
		iWidth	= m_vec8BitTiles[0].iWidth;
		iHeight	= m_vec8BitTiles[0].iHeight;

		iCount	= static_cast<int>(m_vec8BitTiles.size());
	}

	else
	{
		iWidth	= m_vec32BitTiles[0].iWidth;
		iHeight	= m_vec32BitTiles[0].iHeight;

		iCount	= static_cast<int>(m_vec32BitTiles.size());
	}
	
	sprintf(szString, "\t<FrameWidth>%d</FrameWidth>\n", iWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameHeight>%d</FrameHeight>\n", iHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<CharacterCount>%d</CharacterCount>\n", iCount);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<PaletteCount>%d</PaletteCount>\n", m_iPaletteCount);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	if (false == pFile->writeString("</FontInfo>\n"))
	{
		return	false;
	}

	pFile->close();

	delete	pFile;

	return	true;
}

bool Font::extract8BitFont(uint8_t* _pBuffer)
{
	uint8_t	uMarker		= _pBuffer[0];
	uint8_t	uBackground	= _pBuffer[1];

	for (int iLoop = 0; iLoop < m_iWidth; ++iLoop)
	{
		if (_pBuffer[iLoop] == uMarker)
		{
			int	iNext	= iLoop + 1;

			for (; iNext < m_iWidth; ++iNext)
			{
				if (_pBuffer[iNext] == uMarker || iNext == (m_iWidth - 1))
				{
					if (iNext == (m_iWidth - 1))
					{
						iNext++;
					}

					extract8BitCharacter(_pBuffer, iLoop + 1, iNext, uBackground);

					break;
				}
			}
		}
	}

	for (int iLoop = uBackground; iLoop < uBackground + 4; ++iLoop)
	{
		m_pPalette[iLoop] = 0;
	}

	return	true;
}

bool Font::extract8BitCharacter(uint8_t* _pBuffer, int _iX1, int _iX2, uint8_t _uBackgroundColor)
{
	Tile8	tile;

	uint8_t*	pSrc	= _pBuffer + m_iWidth + _iX1;

	int	iWidth	= _iX2 - _iX1;
	int	iHeight	= m_iHeight - 1;

	if (iWidth != SPlay::gsc_iFontSize || iHeight != SPlay::gsc_iFontSize)
	{
		Log::instance()->logError("Each character in a font must be 8 pixels wide and tall");

		return	false;
	}

	tile.pImage	= new uint8_t[iWidth * iHeight];
	
	uint8_t*	pDest	= tile.pImage;

	for (int iLoop = 0; iLoop < iHeight; ++iLoop)
	{
		memcpy(pDest, pSrc, iWidth);

		pDest	+= iWidth;
		pSrc	+= m_iWidth;
	}

	tile.iWidth		= iWidth;
	tile.iHeight	= iHeight;
	
	m_vec8BitTiles.push_back(tile);

	return	true;
}

bool Font::extract32BitFont(uint8_t* _pBuffer)
{
	uint32_t*	pSrc		= reinterpret_cast<uint32_t*>(_pBuffer);
	uint32_t	uMarker		= pSrc[0];
	uint32_t	uBackground	= pSrc[1];

	for (int iLoop = 0; iLoop < m_iWidth; iLoop++)
	{
		if (pSrc[iLoop] == uMarker)
		{
			int	iNext	= iLoop + 1;

			for (; iNext < m_iWidth; ++iNext)
			{
				if (pSrc[iNext] == uMarker || iNext == (m_iWidth - 1))
				{
					if (iNext == (m_iWidth - 1))
					{
						iNext++;
					}

					extract32BitCharacter(pSrc, iLoop + 1, iNext, uBackground);

					break;
				}
			}
		}
	}

	return	true;
}

bool Font::extract32BitCharacter(uint32_t* _pBuffer, int _iX1, int _iX2, uint32_t _uBackgroundColor)
{
	Tile32	tile;

	uint32_t*	pSrc	= reinterpret_cast<uint32_t*>(_pBuffer) + m_iWidth + _iX1;

	int	iWidth	= _iX2 - _iX1;
	int	iHeight	= m_iHeight - 1;

	if (iWidth != SPlay::gsc_iFontSize || iHeight != SPlay::gsc_iFontSize)
	{
		Log::instance()->logError("Each character in a font must be 8 pixels wide and tall");

		return	false;
	}

	tile.pImage	= new uint32_t[iWidth * iHeight];

	uint32_t*	pDest	= tile.pImage;

	for (int iLoop = 0; iLoop < iHeight; ++iLoop)
	{
		for (int iLoopX = 0; iLoopX < iWidth; ++iLoopX)
		{
			if (pSrc[iLoopX] == _uBackgroundColor)
			{
				pDest[iLoopX]	= 0x00000000;
			}

			else
			{
				pDest[iLoopX]	= pSrc[iLoopX];
			}
		}

		pDest	+= iWidth;
		pSrc	+= m_iWidth;
	}

	tile.iWidth		= iWidth;
	tile.iHeight	= iHeight;
	
	m_vec32BitTiles.push_back(tile);

	return	true;
}
