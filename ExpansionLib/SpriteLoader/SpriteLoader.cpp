// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinyXML2/tinyxml2.h>

#include "AssertLog.h"
#include "File.h"
#include "Log.h"
#include "Hardware.h"
#include "ResourceManager.h"
#include "SpriteLoader.h"
#include "System.h"
#include "Utilities.h"

NAMESPACE(SPlay)

SpriteLoader::SpriteLoader()
{
}

SpriteLoader::~SpriteLoader()
{
	close();
}

SpriteLoader* SpriteLoader::create(const tinystl::string& _strSpriteName, const tinystl::string& _strSubDirectory)
{
	SpriteLoader*	pSpriteLoader	= new SpriteLoader();

	if (false == pSpriteLoader->initialize(_strSpriteName, _strSubDirectory))
	{
		delete	pSpriteLoader;

		pSpriteLoader	= NULL;
	}

	return	pSpriteLoader;
}

bool SpriteLoader::initialize(const tinystl::string& _strSpriteName, const tinystl::string& _strSubDirectory)
{
	if (_strSubDirectory.length() > 0)
	{
		m_strSubDirectory	= _strSubDirectory;
		m_strSubDirectory	+= "/";
	}

	if (false == loadXML(_strSpriteName))
	{
		return	false;
	}

	if (false == loadTiles())
	{
		return	false;
	}

	return	true;
}

void SpriteLoader::close()
{
}

ObjSize SpriteLoader::getObjSize() const
{
	if (16 == m_iFrameWidth)
	{
		if (16 == m_iFrameHeight)
		{
			return	ObjSize16x16;
		}

		else if (32 == m_iFrameHeight)
		{
			return	ObjSize16x32;
		}
	}

	if (32 == m_iFrameWidth)
	{
		if (16 == m_iFrameHeight)
		{
			return	ObjSize32x16;
		}

		else if (32 == m_iFrameHeight)
		{
			return	ObjSize32x32;
		}

		else if (64 == m_iFrameHeight)
		{
			return	ObjSize32x64;
		}
	}

	if (64 == m_iFrameWidth)
	{
		if (32 == m_iFrameHeight)
		{
			return	ObjSize64x32;
		}

		else if (64 == m_iFrameHeight)
		{
			return	ObjSize64x64;
		}
	}

	return	ObjSizes;
}

void SpriteLoader::transferFrame(int _iFrameIndex, int _iTileIndex) const
{
	ASSERT_LOG(_iFrameIndex >= 0 && _iFrameIndex < m_iFrameCount, "Frame index is invalid");

	DMA*	pDMA	= Hardware::getDMA();

	uint32_t*	pData	= System::getResourceManager()->getImage(m_iImageIndex)->getPixels();

	pData	+= _iFrameIndex * m_iFrameWidth * m_iFrameHeight;

	pDMA->setupDMATransfer(OAMDMA, pData, _iTileIndex, m_iFrameWidth, m_iFrameHeight, -1);
//	pDMA->startDMATransfer(OAMDMA);
}

bool SpriteLoader::loadXML(const tinystl::string& _strSpriteName)
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= gsc_szSpritesDirectory;
	strFilename	+= _strSpriteName;
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

			else if ("FrameWidth" == strElementName)
			{
				m_iFrameWidth	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("FrameHeight" == strElementName)
			{
				m_iFrameHeight	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("FrameCount" == strElementName)
			{
				m_iFrameCount	= Utilities::convertStringToInt(pTextNode->Value());
			}
		}
		
		xmlChildNode	= xmlChildNode->NextSibling();
	}

	delete	xmlDocument;

	return	true;
}

bool SpriteLoader::loadTiles()
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= gsc_szSpritesDirectory;
	strFilename	+= m_strTileName;

	ResourceManager*	pResourceManager	= System::getResourceManager();

	m_iImageIndex	= pResourceManager->loadImage(strFilename, true);

	if (-1 == m_iImageIndex)
	{
		return	false;
	}

	return	true;
}

ENDNAMESPACE
