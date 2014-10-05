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
#include "FontLoader.h"
#include "Log.h"
#include "Hardware.h"
#include "ResourceManager.h"
#include "System.h"
#include "Utilities.h"
#include "yspng/yspng.h"

NAMESPACE(SPlay)

FontLoader::FontLoader()	:
	m_pImageBuffer(NULL),
	m_pPalette(NULL),
	m_iPaletteCount(0)
{
}

FontLoader::~FontLoader()
{
	close();
}

FontLoader* FontLoader::create(const tinystl::string& _strFontName, const tinystl::string& _strSubDirectory)
{
	FontLoader*	pFontLoader	= new FontLoader();

	if (false == pFontLoader->initialize(_strFontName, _strSubDirectory))
	{
		delete	pFontLoader;

		pFontLoader	= NULL;
	}

	return	pFontLoader;
}

bool FontLoader::initialize(const tinystl::string& _strFontName, const tinystl::string& _strSubDirectory)
{
	if (_strSubDirectory.length() > 0)
	{
		m_strSubDirectory	= _strSubDirectory;
		m_strSubDirectory	+= "/";
	}

	if (false == loadXML(_strFontName))
	{
		return	false;
	}

	if (false == loadFont())
	{
		return	false;
	}

	return	true;
}

void FontLoader::close()
{
	// Memory cleanup is left to the Text layer.
}

bool FontLoader::loadXML(const tinystl::string& _strFontName)
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= gsc_szFontsDirectory;
	strFilename	+= _strFontName;
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
				m_strFilename	= pTextNode->Value();
			}

			else if ("FrameWidth" == strElementName)
			{
				m_iFrameWidth	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("FrameHeight" == strElementName)
			{
				m_iFrameHeight	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("CharacterCount" == strElementName)
			{
				m_iCharacterCount	= Utilities::convertStringToInt(pTextNode->Value());
			}

			else if ("PaletteCount" == strElementName)
			{
				m_iPaletteCount	= Utilities::convertStringToInt(pTextNode->Value());
			}
		}
		
		xmlChildNode	= xmlChildNode->NextSibling();
	}	
	
	delete	xmlDocument;

	return	true;
}

bool FontLoader::loadFont()
{
	uint32_t	iWidth;
	uint32_t	iHeight;

	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= gsc_szFontsDirectory;
	strFilename	+= m_strFilename;

	if (m_iPaletteCount > 0)
	{
		YsRawPngDecoder*	pDecoder	= new YsRawPngDecoder();

		if (pDecoder->Decode(strFilename.c_str()) != YSOK)
		{
			Log::instance()->logError("Unable to load image %s", strFilename.c_str());

			delete	pDecoder;

			return	false;
		}
		
		if (m_iPaletteCount != static_cast<int>(pDecoder->plt.nEntry))
		{
			Log::instance()->logError("Palette mismatch in image %s", strFilename.c_str());

			delete	pDecoder;

			return	false;
		}

		m_pPalette	= new uint8_t[m_iPaletteCount * 4];

		uint8_t*	pPalette	= m_pPalette;
		uint8_t*	pBuffer		= pDecoder->plt.entry;

		for (int iLoop = 0; iLoop < m_iPaletteCount; ++iLoop)
		{
			pPalette[0]	= pBuffer[2];
			pPalette[1]	= pBuffer[1];
			pPalette[2]	= pBuffer[0];
			pPalette[3]	= 0xFF;

			pPalette	+= 4;
			pBuffer		+= 3;
		}

		// The first palette entry is transparent
		m_pPalette[3]	= 0x00;

		iWidth	= pDecoder->wid;
		iHeight	= pDecoder->hei;
		
		int	iSize	= iWidth * iHeight;
		
		m_pImageBuffer	= new uint8_t[iSize];

		memcpy(m_pImageBuffer, pDecoder->indexed, iSize);

#if (!defined __ANDROID__ && !defined MARMALADE && !defined EMSCRIPTEN && !defined ANGLE) || (!defined __ARMEL__ && defined __APPLE__)
		uint32_t*	pSrc	= reinterpret_cast<uint32_t*>(m_pPalette);

		for (int iLoop = 0; iLoop < m_iPaletteCount; ++iLoop)
		{
			uint32_t	uValue = *pSrc;
		
			*pSrc	= (uValue & 0xFF00FF00) | ((uValue & 0x00FF0000) >> 16) | ((uValue & 0x000000FF) << 16);

			pSrc++;
		}
#endif

		delete	pDecoder;
	}
	
	else
	{
		YsRawPngDecoder*	pDecoder	= new YsRawPngDecoder();

		if (pDecoder->Decode(strFilename.c_str()) != YSOK)
		{
			Log::instance()->logError("Unable to load image %s", strFilename.c_str());

			delete	pDecoder;

			return	false;
		}

		iWidth	= pDecoder->wid;
		iHeight	= pDecoder->hei;

		int	iSize	= iWidth * iHeight * 4;

		m_pImageBuffer	= new uint8_t[iSize];

		memcpy(m_pImageBuffer, pDecoder->rgba, iSize);

#if (!defined __ANDROID__ && !defined MARMALADE && !defined EMSCRIPTEN && !defined ANGLE) || (!defined __ARMEL__ && defined __APPLE__)
		uint32_t*	pSrc	= reinterpret_cast<uint32_t*>(m_pImageBuffer);

		int	t_c	= iWidth * iHeight;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			uint32_t	uValue = *pSrc;

			uint32_t	uRed	= (uValue & 0xFF);
			uint32_t	uGreen	= (uValue & 0xFF00) >> 8;
			uint32_t	uBlue	= (uValue & 0xFF0000) >> 16;
			uint32_t	uAlpha	= (uValue & 0xFF000000) >> 24;

			*pSrc	= (uAlpha << 24) | (uRed << 16) | (uGreen << 8) | (uBlue);

			pSrc++;
		}
#endif

		delete	pDecoder;
	}

	Hardware::getText()->setFontData(m_pImageBuffer, m_pPalette, m_iCharacterCount);

	return	true;
}

ENDNAMESPACE
