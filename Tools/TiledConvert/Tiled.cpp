// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "File.h"
#include "Functions.h"
#include "HardwareDefines.h"
#include "Log.h"
#include "Tiled.h"
#include "LodePNG\lodepng.h"
#include "stb_image\stb_image.h"

// Tiled flip flags
static const uint32_t	gsc_uHorizFlipFlag	= 0x80000000;
static const uint32_t	gsc_uVertFlipFlag	= 0x40000000;

Tiled::Tiled()	:
	m_iTileCount(0)
{
}

Tiled::~Tiled()
{
	close();
}

Tiled* Tiled::create()
{
	Tiled*	pTiled	= new Tiled();

	if (false == pTiled->initialize())
	{
		delete	pTiled;

		pTiled	= NULL;
	}

	return	pTiled;
}

bool Tiled::initialize()
{
	return	true;
}

void Tiled::close()
{
	int	t_c	= static_cast<int>(m_vecTileSets.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete[]	m_vecTileSets[iLoop].pBuffer;
	}

	m_vecTileSets.clear();
}

bool Tiled::load(const std::string& _strFilename)
{
	xml::XMLDocument*	pDocument	= new xml::XMLDocument();
	
	if (pDocument->LoadFile(_strFilename.c_str()) != xml::XML_NO_ERROR)
	{
		return	false;
	}
	
	xml::XMLNode*	pNode	= pDocument->FirstChild();
	
	while (pNode != NULL)
	{
		std::string	strNodeName	= pNode->Value();

		if ("map" == strNodeName)
		{
			if (false == readMap(pNode))
			{
				return	false;
			}
		}

		pNode	= pNode->NextSibling();
	}

	delete	pDocument;

	if (0 == m_vecTileSets.size())
	{
		Log::instance()->logError("No tilesets loaded\n");

		return	false;
	}

	if (0 == m_vecLayers.size())
	{
		Log::instance()->logError("No layers loaded\n");

		return	false;
	}

	return	true;
}

bool Tiled::save(const std::string& _strPNGFilename, const std::string& _strMapFilename, const std::string& _strXMLFilename)
{
	if (false == convertTiles(0))
	{
		return	false;
	}

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strPNGFilename)))
	{
		return	false;
	}

	if (false == writePNG(_strPNGFilename))
	{
		return	false;
	}

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strMapFilename)))
	{
		return	false;
	}

	if (false == writeMap(_strMapFilename))
	{
		return	false;
	}

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strXMLFilename)))
	{
		return	false;
	}

	if (false == writeXML(_strPNGFilename, _strMapFilename, _strXMLFilename))
	{
		return	false;
	}

	return	true;
}

bool Tiled::writePNG(const std::string& _strFilename)
{
	int	t_c	= static_cast<int>(m_vecTileSets.size());

	if (0 == t_c || 0 == m_vecTileSets[0].iTileCount)
	{
		return	false;
	}

	const TileSet&	tileSet	= m_vecTileSets[0];

	if (tileSet.iTileWidth < SPlay::gsc_iMinTileSize || tileSet.iTileWidth > SPlay::gsc_iMaxTileSize || 
		tileSet.iTileHeight < SPlay::gsc_iMinTileSize || tileSet.iTileHeight > SPlay::gsc_iMaxTileSize)
	{
		Log::instance()->logError("Tiles must be %d or %d pixels wide and tall\n", SPlay::gsc_iMinTileSize, SPlay::gsc_iMaxTileSize);
		
		return	false;
	}

	if (LodePNG_encode32_file(_strFilename.c_str(), reinterpret_cast<uint8_t*>(tileSet.pBuffer), tileSet.iTileWidth, tileSet.iTileHeight * 
		tileSet.iTileCount) != 0)
	{
		return	false;
	}

	return	true;
}

bool Tiled::writeMap(const std::string& _strFilename)
{
	if (0 == m_vecLayers.size())
	{
		return	false;
	}

	int	t_c	= static_cast<int>(m_vecLayers[0].m_vecTiles.size());

	if (0 == t_c)
	{
		return	false;
	}

	File*	pFile	= new File();

	if (false == pFile->create(_strFilename.c_str(), true))
	{
		return	false;
	}

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		pFile->writeBuffer(reinterpret_cast<uint8_t*>(&m_vecLayers[0].m_vecTiles[iLoop]), sizeof(SPlay::TileInfo));
	}

	pFile->close();

	delete	pFile;

	return	true;
}

bool Tiled::writeXML(const std::string& _strPNGFilename, const std::string& _strMapFilename, const std::string& _strXMLFilename)
{
	std::string	strPNGName	= Functions::getFullFilenameFromPath(_strPNGFilename);
	std::string	strMapName	= Functions::getFullFilenameFromPath(_strMapFilename);

	File*	pFile	= new File();

	if (false == pFile->create(_strXMLFilename.c_str()))
	{
		return	false;
	}

	if (false == pFile->writeString("<MapInfo>\n"))
	{
		return	false;
	}

	char	szString[256];

	sprintf(szString, "\t<ImageName>%s</ImageName>\n", strPNGName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<MapName>%s</MapName>\n", strMapName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<TileWidth>%d</TileWidth>\n", m_iTileWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<TileHeight>%d</TileHeight>\n", m_iTileHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<MapWidth>%d</MapWidth>\n", m_iMapWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<MapHeight>%d</MapHeight>\n", m_iMapHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<TileCount>%d</TileCount>\n", m_iTileCount);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	if (false == pFile->writeString("</MapInfo>\n"))
	{
		return	false;
	}

	pFile->close();

	delete	pFile;

	return	true;
}

bool Tiled::readMap(xml::XMLNode* _pNode)
{
	if (false == readMapInfo(_pNode))
	{
		return	false;
	}

	xml::XMLNode*	pNode	= _pNode->FirstChild();
	
	while (pNode != NULL)
	{
		std::string	strNodeName	= pNode->Value();

		if ("tileset" == strNodeName)
		{
			if (false == readTileset(pNode))
			{
				return	false;
			}
		}

		else if ("layer" == strNodeName)
		{
			if (false == readLayer(pNode))
			{
				return	false;
			}
		}

		pNode	= pNode->NextSibling();
	}

	return	true;
}

bool Tiled::readMapInfo(xml::XMLNode* _pNode)
{
	const xml::XMLAttribute*	pAttribute	= _pNode->ToElement()->FirstAttribute();
	
	if (NULL == pAttribute)
	{
		return	false;
	}

	while (pAttribute != NULL)
	{
		std::string	strName	= pAttribute->Name();

		// Version, orientation, and background color are ignored
		if ("version" == strName || "orientation" == strName || "backgroundcolor" == strName)
		{
		}

		else if ("width" == strName)
		{
			m_iMapWidth	= pAttribute->IntValue();
		}

		else if ("height" == strName)
		{
			m_iMapHeight	= pAttribute->IntValue();
		}

		else if ("tilewidth" == strName)
		{
			m_iTileWidth	= pAttribute->IntValue();
		}

		else if ("tileheight" == strName)
		{
			m_iTileHeight	= pAttribute->IntValue();
		}

		pAttribute	= pAttribute->Next();
	}

	return	true;
}

bool Tiled::readTileset(xml::XMLNode* _pNode)
{
	TileSet	tileSet;

	if (false == readTilesetInfo(_pNode, tileSet))
	{
		return	false;
	}

	if (false == readTilesetChildren(_pNode, tileSet))
	{
		return	false;
	}

	m_vecTileSets.push_back(tileSet);

	return	true;
}

bool Tiled::readTilesetInfo(xml::XMLNode* _pNode, TileSet& _tileSet)
{
	const xml::XMLAttribute*	pAttribute	= _pNode->ToElement()->FirstAttribute();
	
	if (NULL == pAttribute)
	{
		return	false;
	}

	while (pAttribute != NULL)
	{
		std::string	strName	= pAttribute->Name();

		if ("firstgid" == strName)
		{
			_tileSet.iFirstGid	= pAttribute->IntValue();
		}

		else if ("name" == strName)
		{
			_tileSet.strName	= pAttribute->Value();
		}

		else if ("tilewidth" == strName)
		{
			_tileSet.iTileWidth	= pAttribute->IntValue();
		}

		else if ("tileheight" == strName)
		{
			_tileSet.iTileHeight	= pAttribute->IntValue();
		}

		pAttribute	= pAttribute->Next();
	}

	return	true;
}

bool Tiled::readTilesetChildren(xml::XMLNode* _pNode, TileSet& _tileSet)
{
	xml::XMLNode*	pNode	= _pNode->FirstChild();
	
	while (pNode != NULL)
	{
		std::string	strNodeName	= pNode->Value();

		if ("image" == strNodeName)
		{
			if (false == readImageInfo(pNode, _tileSet.tileImage))
			{
				return	false;
			}
		}

		pNode	= pNode->NextSibling();
	}

	return	true;
}

bool Tiled::readImageInfo(xml::XMLNode* _pNode, TileImage& _tileImage)
{
	const xml::XMLAttribute*	pAttribute	= _pNode->ToElement()->FirstAttribute();
	
	if (NULL == pAttribute)
	{
		return	false;
	}

	while (pAttribute != NULL)
	{
		std::string	strName	= pAttribute->Name();

		if ("source" == strName)
		{
			
			_tileImage.strSource	= pAttribute->Value();
		}

		else if ("width" == strName)
		{
			_tileImage.iWidth	= pAttribute->IntValue();
		}

		else if ("height" == strName)
		{
			_tileImage.iHeight	= pAttribute->IntValue();
		}

		// TODO: Need to handle transparent color
		else if ("trans" == strName)
		{
		}
		
		pAttribute	= pAttribute->Next();
	}

	return	true;
}

bool Tiled::readLayer(xml::XMLNode* _pNode)
{
	Layer	layer;

	if (false == readLayerInfo(_pNode, layer))
	{
		return	false;
	}

	xml::XMLNode* pNode	= _pNode->FirstChild();

	if (NULL == pNode)
	{
		return	false;
	}
	
	if (false == readTiles(pNode, layer))
	{
		return	false;
	}

	m_vecLayers.push_back(layer);

	return	true;
}

bool Tiled::readLayerInfo(xml::XMLNode* _pNode, Layer& _layer)
{
	const xml::XMLAttribute*	pAttribute	= _pNode->ToElement()->FirstAttribute();
	
	if (NULL == pAttribute)
	{
		return	false;
	}

	while (pAttribute != NULL)
	{
		std::string	strName	= pAttribute->Name();

		if ("name" == strName)
		{
			_layer.strName	= pAttribute->Value();
		}

		else if ("width" == strName)
		{
			_layer.iWidth	= pAttribute->IntValue();
		}

		else if ("height" == strName)
		{
			_layer.iHeight	= pAttribute->IntValue();
		}

		pAttribute	= pAttribute->Next();
	}

	return	true;
}

bool Tiled::readTiles(xml::XMLNode* _pNode, Layer& _layer)
{
	xml::XMLNode*	pNode	= _pNode->FirstChild();
	
	while (pNode != NULL)
	{
		std::string	strNodeName	= pNode->Value();

		if ("tile" == strNodeName)
		{
			xml::XMLElement*	pElement	= pNode->ToElement();
			
			if (pElement != NULL)
			{
				SPlay::TileInfo	tileInfo;

				int	iGID	= pElement->IntAttribute("gid");

				tileInfo.iTileIndex	= (iGID & 0x1FFFFFFF);

				if (tileInfo.iTileIndex > 0)
				{
					tileInfo.iTileIndex--;
				}

				tileInfo.eFlip	= SPlay::NoFlip;

				if (iGID & gsc_uHorizFlipFlag)
				{
					if (iGID & gsc_uVertFlipFlag)
					{
						tileInfo.eFlip	= SPlay::HVFlip;
					}

					else
					{
						tileInfo.eFlip	= SPlay::HFlip;
					}
				}
				
				else if (iGID & gsc_uVertFlipFlag)
				{
					tileInfo.eFlip	= SPlay::VFlip;
				}

				_layer.m_vecTiles.push_back(tileInfo);
			}
		}

		pNode	= pNode->NextSibling();
	}

	return	true;
}

bool Tiled::convertTiles(int _iTileSet)
{
	if (_iTileSet < 0 || _iTileSet > static_cast<int>(m_vecTileSets.size()))
	{
		return	false;
	}

	int	iWidth;
	int	iHeight;
	int	iBPP;

	const TileImage&	tileImage	= m_vecTileSets[_iTileSet].tileImage;

	uint8_t*	pBuffer	= stbi_load(tileImage.strSource.c_str(), &iWidth, &iHeight, &iBPP, 4);
	
	if (NULL == pBuffer)
	{
		Log::instance()->logError("Unable to load tile");

		return	false;
	}

	if (iWidth != tileImage.iWidth || iHeight != tileImage.iHeight)
	{
		Log::instance()->logError("Tile size does not match description");

		return	false;
	}

	if (false == extractTiles(pBuffer, iWidth, iHeight, _iTileSet))
	{
		return	false;
	}

	stbi_image_free(pBuffer);
				
	return	true;
}

bool Tiled::extractTiles(uint8_t* _pBuffer, int _iWidth, int _iHeight, int _iTileSet)
{
	TileSet&	tileset	= m_vecTileSets[_iTileSet];

	int	iTileWidth	= tileset.iTileWidth;
	int	iTileHeight	= tileset.iTileHeight;
	int	iTilesX		= _iWidth / iTileWidth;
	int	iTilesY		= _iHeight / iTileWidth;
	
	m_iTileCount	= iTilesY * iTilesX;

	tileset.iTileCount	= m_iTileCount;

	uint32_t*	pSrc	= reinterpret_cast<uint32_t*>(_pBuffer);

	tileset.pBuffer	= new uint32_t[m_iTileCount * iTileWidth * iTileHeight];

	uint32_t*	pDest	= tileset.pBuffer;

	for (int iYLoop = 0; iYLoop < iTilesY; ++iYLoop)
	{
		uint32_t*	pSrcPtr	= pSrc;

		for (int iXLoop = 0; iXLoop < iTilesX; ++iXLoop)
		{
			for (int iLineLoop = 0; iLineLoop < iTileHeight; ++iLineLoop)
			{
				memcpy(pDest, pSrcPtr + iLineLoop * _iWidth, iTileWidth * sizeof(uint32_t));

				pDest	+= iTileWidth;
			}

			pSrcPtr	+= iTileWidth;
		}

		pSrc	+= _iWidth * iTileHeight;
	}

	return	true;
}