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

#include "Functions.h"
#include "Log.h"
#include "HardwareDefines.h"
#include "Pickle.h"
#include "JSON\JSON.h"
#include "LodePNG\LodePNG.h"
#include "MiniZ\miniz.h"
#include "stb_image\stb_image.h"

// JSON filename
static const char*	gsc_szJSONFilename	= "tileData.json";

// Image filename
static const char*	gsc_szImageFilename	= "tileImage.png";

Pickle::Pickle()
{
}

Pickle::~Pickle()
{
	close();
}

Pickle* Pickle::create()
{
	Pickle*	pPickle	= new Pickle();

	if (false == pPickle->initialize())
	{
		delete	pPickle;

		pPickle	= NULL;
	}

	return	pPickle;
}

bool Pickle::initialize()
{
	return	true;
}

void Pickle::close()
{
	int	t_c	= static_cast<int>(m_vecTilesets.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		int	iImages	= static_cast<int>(m_vecTilesets[iLoop].vecImages.size());

		for (int iImage = 0; iImage < iImages; ++iImage)
		{
			delete m_vecTilesets[iLoop].vecImages[iImage];
		}

		m_vecTilesets[iLoop].vecImages.clear();
	}

	m_vecTilesets.clear();
}


bool Pickle::load(const std::string& _strFilename)
{
	if (false == loadJSON(_strFilename))
	{
		Log::instance()->logError("Unable to load file details from the Pickle file.");

		return	false;
	}
	
	if (false == loadSprites(_strFilename))
	{
		Log::instance()->logError("Unable to load sprites from the Pickle file.");

		return	false;
	}
	
	return	true;
}

bool Pickle::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

bool Pickle::loadJSON(const std::string& _strFilename)
{
	size_t	iBufferSize = 0;

	void*	pBuffer	= mz_zip_extract_archive_file_to_heap(_strFilename.c_str(), gsc_szJSONFilename, &iBufferSize, 0);

	if (NULL == pBuffer || 0 == iBufferSize)
	{
		return	false;
	}

	jsonParser parsed(reinterpret_cast<const char*>(pBuffer));

	jsonADT	adt(&parsed);

	int	t_c	= adt.childrenCount;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		jsonADT*	pADT	= adt.children[iLoop];

		std::string	strName	= pADT->name;

		if ("backgroundColor" == strName)
		{
			m_fileInfo.uBackgroundColor	= static_cast<uint32_t>(pADT->integer);
		}

		else if ("colorPalette" == strName)
		{
		}

		else if ("frameWidth" == strName)
		{
			m_fileInfo.iFrameWidth	= pADT->integer;
		}

		else if ("frameHeight" == strName)
		{
			m_fileInfo.iFrameHeight	= pADT->integer;
		}

		else if ("numFrames" == strName)
		{
			m_fileInfo.iNumFrames	= pADT->integer;
		}

		else if ("frameRate" == strName)
		{
			m_fileInfo.iFrameRate	= pADT->integer;
		}

		else if ("numFramesAcross" == strName)
		{
			m_fileInfo.iHorizFrames	= pADT->integer;
		}

		else if ("sheetWidth" == strName)
		{
			m_fileInfo.iImageWidth	= pADT->integer;
		}

		else if ("sheetHeight" == strName)
		{
			m_fileInfo.iImageHeight	= pADT->integer;
		}

		else if ("terrainMap" == strName)
		{
		}

		else if ("frameOverlayStyle" == strName)
		{
		}

		else if ("previewType" == strName)
		{
		}
	}

	free(pBuffer);

	return	true;
}

bool Pickle::loadSprites(const std::string& _strFilename)
{
	size_t	iBufferSize = 0;

	void*	pBuffer	= mz_zip_extract_archive_file_to_heap(_strFilename.c_str(), gsc_szImageFilename, &iBufferSize, 0);
	
	if (NULL == pBuffer || 0 == iBufferSize)
	{
		Log::instance()->logError("Unable to load sprite image");

		return	false;
	}

	uint8_t*	pImageBuffer	= stbi_load_from_memory(static_cast<stbi_uc*>(pBuffer), iBufferSize, &m_iWidth, &m_iHeight, &m_iBPP, 4);
	
	if (NULL == pImageBuffer)
	{
		Log::instance()->logError("Unable to load sprite image");

		return	false;
	}

	if (m_iWidth != m_fileInfo.iImageWidth || m_iHeight != m_fileInfo.iImageHeight)
	{
		Log::instance()->logError("Sprite size does not match description");

		return	false;
	}
	
	int	iSize	= m_iWidth * m_iHeight * m_iBPP;

	uint8_t*	pSavedBuffer	= new uint8_t[iSize];

	memcpy(pSavedBuffer, pImageBuffer, iSize);

	stbi_image_free(pBuffer);

	int	t_c	= m_fileInfo.iNumFrames;

	Tileset	tileset;

	tileset.iTileWidth	= m_fileInfo.iFrameWidth;
	tileset.iTileHeight	= m_fileInfo.iFrameHeight;

	int	iSpriteX	= 0;
	int	iSpriteY	= 0;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		extractTile(reinterpret_cast<uint32_t*>(pSavedBuffer), iSpriteX, iSpriteY, tileset);

		iSpriteX	+= m_fileInfo.iFrameWidth;

		if (iSpriteX >= m_fileInfo.iImageWidth)
		{
			iSpriteX	= 0;
			iSpriteY	+= m_fileInfo.iFrameHeight;
		}
	}

	m_vecTilesets.push_back(tileset);

	return	true;
}

bool Pickle::writePNG(const std::string& _strFilename)
{
	if (0 == m_vecTilesets.size())
	{
		return	false;
	}

	const Tileset&	tileset	= m_vecTilesets[0];

	int	t_c	= static_cast<int>(m_vecTilesets[0].vecImages.size());

	if (0 == t_c)
	{
		return	false;
	}

	// Find power of two for the sprites.
	m_iWidth	= static_cast<int>(pow(2, ceil(Functions::log2(tileset.iTileWidth))));
	m_iHeight	= static_cast<int>(pow(2, ceil(Functions::log2(tileset.iTileHeight))));
	
	if (m_iWidth < SPlay::gsc_iMinObjSize)
	{
		m_iWidth	= SPlay::gsc_iMinObjSize;
	}

	if (m_iHeight < SPlay::gsc_iMinObjSize)
	{
		m_iHeight	= SPlay::gsc_iMinObjSize;
	}

	if (m_iWidth > SPlay::gsc_iMaxObjSize || m_iHeight > SPlay::gsc_iMaxObjSize)
	{
		Log::instance()->logError("Sprites must be <= %d pixels wide and tall\n", SPlay::gsc_iMaxObjSize);
		
		return	false;
	}

	int	iSize	= m_iWidth * m_iHeight * m_iBPP;
	int	iStride	= m_iWidth * m_iBPP;

	uint8_t*	pBuffer	= new uint8_t[iSize * t_c];

	memset(pBuffer, 0, iSize * t_c);

	uint8_t*	pDest	= pBuffer;

	int	iTileWidth	= tileset.iTileWidth * m_iBPP;
	int	iTileHeight	= tileset.iTileHeight;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		uint8_t*	pSrc	= reinterpret_cast<uint8_t*>(tileset.vecImages[iLoop]);
		uint8_t*	pOffset	= pDest;

		for (int iYLoop = 0; iYLoop < iTileHeight; ++iYLoop)
		{
			memcpy(pOffset, pSrc, iTileWidth);

			pOffset	+= iStride;
			pSrc	+= iTileWidth;
		}

		pDest	+= iSize;
	}

	if (LodePNG_encode32_file(_strFilename.c_str(), reinterpret_cast<uint8_t*>(pBuffer), m_iWidth, m_iHeight * t_c) != 0)
	{
		return	false;
	}

	return	true;
}

bool Pickle::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
{
	std::string	strPNGName	= Functions::getFullFilenameFromPath(_strPNGFilename);

	File*	pFile	= new File();

	if (false == pFile->create(_strXMLFilename.c_str()))
	{
		return	false;
	}

	if (false == pFile->writeString("<SpriteInfo>\n"))
	{
		return	false;
	}

	char	szString[256];

	sprintf(szString, "\t<ImageName>%s</ImageName>\n", strPNGName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameWidth>%d</FrameWidth>\n", m_iWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameHeight>%d</FrameHeight>\n", m_iHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameCount>%d</FrameCount>\n", static_cast<int>(m_vecTilesets[0].vecImages.size()));

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	if (false == pFile->writeString("</SpriteInfo>\n"))
	{
		return	false;
	}

	pFile->close();

	delete	pFile;

	return	true;
}

void Pickle::extractTile(uint32_t* _pSource, int _iX, int _iY, Tileset& _tileset)
{
	int	iWidth	= _tileset.iTileWidth;
	int	iHeight	= _tileset.iTileHeight;

	uint32_t*	pBuffer	= new uint32_t[iWidth * iHeight];

	uint32_t*	pSrcPtr		= _pSource + _iY * m_fileInfo.iImageWidth + _iX;
	uint32_t*	pDestPtr	= pBuffer;

	for (int iYLoop = 0; iYLoop < iHeight; ++iYLoop)
	{
		memcpy(pDestPtr, pSrcPtr, iWidth * m_iBPP);

		pSrcPtr		+= m_fileInfo.iImageWidth;
		pDestPtr	+= iWidth;
	}

	_tileset.vecImages.push_back(pBuffer);
}
