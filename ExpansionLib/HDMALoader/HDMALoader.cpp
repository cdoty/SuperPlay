// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "File.h"
#include "HDMALoader.h"
#include "Log.h"
#include "Hardware.h"
#include "ResourceManager.h"
#include "System.h"
#include "Utilities.h"

NAMESPACE(SPlay)

HDMALoader::HDMALoader()	:
	m_pHDMATable(NULL)
{
}

HDMALoader::~HDMALoader()
{
	close();
}

HDMALoader* HDMALoader::create(const tinystl::string& _strFilename, const tinystl::string& _strSubDirectory)
{
	HDMALoader*	pHDMALoader	= new HDMALoader();

	if (false == pHDMALoader->initialize(_strFilename, _strSubDirectory))
	{
		delete	pHDMALoader;

		pHDMALoader	= NULL;
	}

	return	pHDMALoader;
}

bool HDMALoader::initialize(const tinystl::string& _strFilename, const tinystl::string& _strSubDirectory)
{
	if (_strSubDirectory.length() > 0)
	{
		m_strSubDirectory	= _strSubDirectory;
		m_strSubDirectory	+= "/";
	}

	if (false == loadImage(_strFilename))
	{
		return	false;
	}

	if (false == transferHDMA())
	{
		Log::instance()->logError("Unable to transfer HDMA");

		return	false;
	}

	return	true;
}

void HDMALoader::close()
{
	delete	m_pHDMATable;

	m_pHDMATable	= NULL;
}

bool HDMALoader::loadImage(const tinystl::string& _strFilename)
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= gsc_szHDMADirectory;
	strFilename	+= _strFilename;
	strFilename	+= ".png";

	ResourceManager*	pResourceManager	= System::getResourceManager();

	int	iImageIndex	= pResourceManager->loadImage(strFilename, true);

	if (-1 == iImageIndex)
	{
		Log::instance()->logError("Unable to load image %s", strFilename.c_str());

		return	false;
	}

	Image*	pImage	= pResourceManager->getImage(iImageIndex);

	int	iWidth	= pImage->getWidth();

	m_iHeight	= pImage->getHeight();

	m_pHDMATable	= new uint32_t[m_iHeight];
		
	uint32_t*	pPixels	= pImage->getPixels();

	for (int iYLoop = 0; iYLoop < m_iHeight; ++iYLoop)
	{
		uint32_t	uValue	= *pPixels;

#if (!defined __ANDROID__ && !defined MARMALADE && !defined EMSCRIPTEN && !defined ANGLE) || (!defined __ARMEL__ && defined __APPLE__)
		m_pHDMATable[iYLoop]	= uValue;
#else
		uint32_t	uAlpha	= (uValue & 0xFF000000) >> 24;
		uint32_t	uRed	= (uValue & 0x00FF0000) >> 16;
		uint32_t	uGreen	= (uValue & 0x0000FF00) >> 8;
		uint32_t	uBlue	= uValue & 0x000000FF;

		m_pHDMATable[iYLoop]	= (uAlpha << 24) | (uBlue << 16) | (uGreen << 8) | uRed;
#endif


		pPixels	+= iWidth;
	}

	return	true;
}

bool HDMALoader::transferHDMA()
{
	HDMA*	pHDMA	= Hardware::getHDMA();

	int	iScreenHeight	= System::getGameHeader().iScreenHeight;

	// Setup HDMA transfer of color table
	pHDMA->setupHDMATransfer(m_pHDMATable, 0, iScreenHeight < m_iHeight ? iScreenHeight : m_iHeight);
	
	// Transfer color table
	pHDMA->startHDMATransfer();

	return	true;
}

ENDNAMESPACE
