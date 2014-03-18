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
#include "HardwareDefines.h"
#include "Log.h"
#include "Pyxel.h"
#include "JSON\JSON.h"
#include "LodePNG\LodePNG.h"
#include "MiniZ\miniz.h"
#include "stb_image\stb_image.h"

// JSON filename
static const char*	gsc_szJSONFilename	= "docData.json";

Pyxel::Pyxel()
{
}

Pyxel::~Pyxel()
{
	close();
}

Pyxel* Pyxel::create()
{
	Pyxel*	pPyxel	= new Pyxel();

	if (false == pPyxel->initialize())
	{
		delete	pPyxel;

		pPyxel	= NULL;
	}

	return	pPyxel;
}

bool Pyxel::initialize()
{
	return	true;
}

void Pyxel::close()
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


bool Pyxel::load(const std::string& _strFilename)
{
	if (false == loadJSON(_strFilename))
	{
		Log::instance()->logError("Unable to load file details from the pyxel file.");

		return	false;
	}
	
	if (false == loadSprites(_strFilename))
	{
		Log::instance()->logError("Unable to load sprites from the pyxel file.");

		return	false;
	}
	
	return	true;
}

bool Pyxel::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

bool Pyxel::loadJSON(const std::string& _strFilename)
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

		if ("animations" == strName)
		{
			parseAnimationsNode(pADT);
		}

		else if ("tileset" == strName)
		{
			parseTilesetNode(pADT);
		}

		else if ("name" == strName)
		{
		}

		else if ("canvas" == strName)
		{
			parseCanvasNode(pADT);
		}

		else if ("palette" == strName)
		{
		}

		else if ("version" == strName)
		{
		}
	}

	free(pBuffer);

	return	true;
}

bool Pyxel::loadSprites(const std::string& _strFilename)
{
	int	t_c	= static_cast<int>(m_vecTilesets.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		int	iImages	= m_vecTilesets[iLoop].iNumTiles;

		for (int iImage = 0; iImage < iImages; ++iImage)
		{
			const Tileset&	tileSet	= m_vecTilesets[iLoop];

			char	szFilename[FILENAME_MAX];

			sprintf(szFilename, "tile%d.png", iImage);

			size_t	iBufferSize = 0;

			void*	pBuffer	= mz_zip_extract_archive_file_to_heap(_strFilename.c_str(), szFilename, &iBufferSize, 0);

			if (NULL == pBuffer || 0 == iBufferSize)
			{
				Log::instance()->logError("Unable to read sprites");

				return	false;
			}

			uint8_t*	pImageBuffer	= stbi_load_from_memory(static_cast<stbi_uc*>(pBuffer), iBufferSize, &m_iWidth, &m_iHeight, &m_iBPP, 4);
	
			if (NULL == pImageBuffer)
			{
				Log::instance()->logError("Unable to load sprite image");

				return	false;
			}

			if (m_iWidth != tileSet.iTileWidth || m_iHeight != tileSet.iTileHeight)
			{
				Log::instance()->logError("Sprite size does not match description");

				return	false;
			}
	
			int	iSize	= m_iWidth * m_iHeight * m_iBPP;

			uint8_t*	pSavedBuffer	= new uint8_t[iSize];

			memcpy(pSavedBuffer, pImageBuffer, iSize);

			m_vecTilesets[iLoop].vecImages.push_back(pSavedBuffer);

			stbi_image_free(pBuffer);
		}
	}

	return	true;
}

bool Pyxel::parseAnimationsNode(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (false == parseAnimation(_pADT->children[iLoop]))
		{
			return	false;
		}
	}

	return	true;
}

bool Pyxel::parseAnimation(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	if (t_c > 0)
	{
		Animation	animation;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			jsonADT*	pADT	= _pADT->children[iLoop];

			std::string	strName	= pADT->name;

			if ("baseTile" == strName)
			{
				animation.iBaseTile	= pADT->integer;
			}

			else if ("frameDuration" == strName)
			{
				animation.iFrameDuration	= pADT->integer;
			}

			else if ("length" == strName)
			{
				animation.iLength	= pADT->integer;
			}

			else if ("name" == strName)
			{
				animation.strName	= pADT->stringOrBinary;
			}
		}

		m_vecAnimations.push_back(animation);
	}

	return	true;
}

bool Pyxel::parseTilesetNode(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	if (t_c > 0)
	{
		Tileset	tileset;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			jsonADT*	pADT	= _pADT->children[iLoop];

			std::string	strName	= pADT->name;

			if ("numTiles" == strName)
			{
				tileset.iNumTiles	= pADT->integer;
			}

			else if ("tilesWide" == strName)
			{
				tileset.iTilesWide	= pADT->integer;
			}

			else if ("tileWidth" == strName)
			{
				tileset.iTileWidth	= pADT->integer;
			}

			else if ("tileHeight" == strName)
			{
				tileset.iTileHeight	= pADT->integer;
			}
		}

		m_vecTilesets.push_back(tileset);
	}

	return	true;
}

bool Pyxel::parseCanvasNode(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	if (t_c > 0)
	{
		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			jsonADT*	pADT	= _pADT->children[iLoop];

			std::string	strName	= pADT->name;

			if ("numLayers" == strName)
			{
				m_canvas.iNumLayers	= pADT->integer;
			}

			else if ("layers" == strName)
			{
				if (false == parseLayersNode(pADT))
				{
					return	false;
				}
			}

			else if ("width" == strName)
			{
				m_canvas.iWidth	= pADT->integer;
			}

			else if ("height" == strName)
			{
				m_canvas.iHeight	= pADT->integer;
			}

			else if ("tileWidth" == strName)
			{
				m_canvas.iTileWidth	= pADT->integer;
			}

			else if ("tileHeight" == strName)
			{
				m_canvas.iTileHeight	= pADT->integer;
			}
		}
	}

	return	true;
}

bool Pyxel::parseLayersNode(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (false == parseLayer(_pADT->children[iLoop]))
		{
			return	false;
		}
	}

	return	true;
}

bool Pyxel::parseLayer(jsonADT* _pADT)
{
	int	t_c	= _pADT->childrenCount;

	if (t_c > 0)
	{
		Layer	layer;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			jsonADT*	pADT	= _pADT->children[iLoop];

			std::string	strName	= pADT->name;

			if ("name" == strName)
			{
				layer.strName	= pADT->stringOrBinary;
			}

			else if ("alpha" == strName)
			{
				layer.iAlpha	= pADT->integer;
			}

			else if ("hidden" == strName)
			{
				layer.bHidden	= pADT->boolean;
			}

			else if ("tileRefs" == strName)
			{
				parseTileRefsNode(pADT, layer);
			}
		}

		m_canvas.vecLayers.push_back(layer);
	}

	return	true;
}

bool Pyxel::parseTileRefsNode(jsonADT* _pADT, Layer& _layer)
{
	int	t_c	= _pADT->childrenCount;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (false == parseTileRef(_pADT->children[iLoop], _layer))
		{
			return	false;
		}
	}

	return	true;
}

bool Pyxel::parseTileRef(jsonADT* _pADT, Layer& _layer)
{
	int	t_c	= _pADT->childrenCount;

	if (t_c > 0)
	{
		TileRef	tileRef;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			jsonADT*	pADT	= _pADT->children[iLoop];

			std::string	strName	= pADT->name;

			if ("flipX" == strName)
			{
				tileRef.bFlipX	= pADT->boolean;
			}

			else if ("index" == strName)
			{
				tileRef.iIndex	= pADT->integer;
			}

			else if ("rot" == strName)
			{
				tileRef.iRotation	= pADT->integer;
			}
		}

		_layer.vecTileRefs.push_back(tileRef);
	}

	return	true;
}

bool Pyxel::writePNG(const std::string& _strFilename)
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
		uint8_t*	pSrc	= tileset.vecImages[iLoop];

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

	delete[]	pBuffer;

	return	true;
}

bool Pyxel::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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
