// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinyXML2/tinyxml2.h>

#include "File.h"
#include "Log.h"
#include "MapLoader.h"
#include "Hardware.h"
#include "ResourceManager.h"
#include "System.h"
#include "Utilities.h"

NAMESPACE(SPlay)

MapLoader::MapLoader(int _iIndex)	:
	m_iIndex(_iIndex),
	m_iImageIndex(-1)
{
}

MapLoader::~MapLoader()
{
	close();
}

MapLoader* MapLoader::create(int _iIndex, const tinystl::string& _strMapName, const tinystl::string& _strSubDirectory)
{
	MapLoader*	pMapLoader	= new MapLoader(_iIndex);

	if (false == pMapLoader->initialize(_strMapName, _strSubDirectory))
	{
		delete	pMapLoader;

		pMapLoader	= NULL;
	}

	return	pMapLoader;
}

bool MapLoader::initialize(const tinystl::string& _strMapName, const tinystl::string& _strSubDirectory)
{
	if (_strSubDirectory.length() > 0)
	{
		m_strSubDirectory	= _strSubDirectory;
		m_strSubDirectory	+= "/";
	}

	if (false == loadXML(_strMapName))
	{
		Log::instance()->logError("Unable to load xml %s", _strMapName.c_str());

		return	false;
	}

	if (false == createVRAM())
	{
		Log::instance()->logError("Unable to create VRAM");

		return	false;
	}

	if (false == loadTiles())
	{
		return	false;
	}

	if (false == loadMap())
	{
		return	false;
	}

	return	true;
}

void MapLoader::close()
{
}

bool MapLoader::loadXML(const tinystl::string& _strMapName)
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename += gsc_szMapsDirectory;
	strFilename	+= _strMapName;
	strFilename	+= ".xml";

	xml::XMLDocument*	xmlDocument	= new xml::XMLDocument();
	
	if (xmlDocument->LoadFile(strFilename.c_str()) != xml::XML_NO_ERROR)
	{
        Log::instance()->logError("(%d) Unable to load XML %s.", xmlDocument->ErrorID(), strFilename.c_str());

        return	false;
	}
	
	xml::XMLNode*	xmlFirstNode	= xmlDocument->FirstChild();
	
	if (NULL == xmlFirstNode)
	{
        Log::instance()->logError("(%d) XML file %s is malformed.", xmlDocument->ErrorID(), strFilename.c_str());

		return	false;
	}

	xml::XMLNode*	xmlChildNode	= xmlFirstNode->FirstChild();
	
	while (xmlChildNode != NULL)
	{
		tinystl::string	strElementName	= xmlChildNode->Value();

		xml::XMLNode*	pTextNode	= xmlChildNode->FirstChild();
		
		if (pTextNode != NULL)
		{
			if ("ImageName" == strElementName)
			{
				m_strTileName	= pTextNode->Value();
			}

			else if ("MapName" == strElementName)
			{
				m_strMapName	= pTextNode->Value();
			}

			else if ("MapWidth" == strElementName)
			{
				m_iMapWidth	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("MapHeight" == strElementName)
			{
				m_iMapHeight	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("TileWidth" == strElementName)
			{
				m_iTileWidth	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("TileHeight" == strElementName)
			{
				m_iTileHeight	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("TileCount" == strElementName)
			{
				m_iTileCount	= Utilities::convertStringToInt(pTextNode->Value());
			}
		}
		
		xmlChildNode	= xmlChildNode->NextSibling();
	}

	delete	xmlDocument;

	return	true;
}

bool MapLoader::createVRAM()
{
	BGVRAM*	pBGVRAM	= BGVRAM::create(32 == m_iTileWidth ? TileSize32x32 : TileSize16x16);

	if (NULL == pBGVRAM)
	{
		return	false;
	}

	Hardware::setBGVRAM(pBGVRAM);

	Hardware::getBG(m_iIndex)->m_iTileSize	= pBGVRAM->getTileSize();

	return	true;
}

bool MapLoader::loadTiles()
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename += gsc_szMapsDirectory;
	strFilename	+= m_strTileName;

	ResourceManager*	pResourceManager	= System::getResourceManager();

	m_iImageIndex	= pResourceManager->loadImage(strFilename, true);

	if (-1 == m_iImageIndex)
	{
		Log::instance()->logError("Unable to load image %s", strFilename.c_str());

		return	false;
	}

	DMA*	pDMA	= Hardware::getDMA();

	pDMA->setupDMATransfer(BGDMA, pResourceManager->getImage(m_iImageIndex)->getPixels(), 0, m_iTileCount, m_iIndex);
//	pDMA->startDMATransfer(BGDMA);

	return	true;
}

bool MapLoader::loadMap()
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename += gsc_szMapsDirectory;
	strFilename	+= m_strMapName;

	File*	pFile	= new File();

	if (false == pFile->open(strFilename, true))
	{
		Log::instance()->logError("Unable to load map %s", strFilename.c_str());

		delete	pFile;

		return	false;
	}

	uint8_t*	pBuffer	= NULL;

	if (false == pFile->readBuffer(&pBuffer, pFile->getLength()))
	{
		Log::instance()->logError("Unable to read map %s", strFilename.c_str());

		delete	pFile;

		return	false;
	}

	pFile->close();

	delete	pFile;

	BG*	pBG	= Hardware::getBG(m_iIndex);

	pBG->m_vecTileMap.clear();

	TileInfo*	pMapData	= reinterpret_cast<TileInfo*>(pBuffer);

	int	t_c	= m_iMapWidth * m_iMapHeight;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		TileInfo	tileInfo;

		tileInfo.iTileIndex	= pMapData[iLoop].iTileIndex;
		tileInfo.eFlip		= pMapData[iLoop].eFlip;

		pBG->m_vecTileMap.push_back(tileInfo);
	}

	delete[]	pBuffer;

	pBG->m_iTilesWide	= m_iMapWidth;
	pBG->m_iTilesHigh	= m_iMapHeight;
	pBG->m_iMapSize		= m_iMapWidth * m_iMapHeight;
	pBG->m_iMapWidth	= m_iMapWidth * m_iTileWidth;
	pBG->m_iMapHeight	= m_iMapHeight * m_iTileHeight;

	if (false == pBG->setupSpriteBatch())
	{
		Log::instance()->logError("Unable to setup sprite batch");

		return	false;
	}

	return	true;
}

ENDNAMESPACE
