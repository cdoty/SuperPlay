// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "File.h"
#include "Image.h"
#include "Log.h"
#include "Utilities.h"
#include "stb_image/stb_image.h"

NAMESPACE(SPlay)

Image::Image()	:
	m_pImage(NULL)
{
}

Image::~Image()
{
	close();
}

Image* Image::create(const tinystl::string& _strFilename)
{
	Image*	pImage	= new Image();

	if (false == pImage->initialize(_strFilename))
	{
		delete	pImage;

		pImage	= NULL;
	}

	return	pImage;
}

bool Image::initialize(const tinystl::string& _strFilename)
{
	int	iWidth;
	int	iHeight;
	int	iBPP;
	
	delete[] m_pImage;

	File*	pFile	= new File();

	if (false == pFile->open(_strFilename, true))
	{
		Log::instance()->logError("Unable to open image %s", _strFilename.c_str());

		return	false;
	}

	int	iLength	= pFile->getLength();

	uint8_t*	pImage	= NULL;

	if (false == pFile->readBuffer(&pImage))
	{
		Log::instance()->logError("Unable to read image %s", _strFilename.c_str());

		return	false;
	}

	pFile->close();

	delete	pFile;

	// Load image as a 32 bit texture
	m_pImage	= reinterpret_cast<uint32_t*>(stbi_load_from_memory(pImage, iLength, &iWidth, &iHeight, &iBPP, 4));

	delete[]	pImage;

	if (NULL == m_pImage)
	{
		Log::instance()->logError("Unable to load image %s", _strFilename.c_str());

		return	false;
	}
	
	m_iWidth		= iWidth;
	m_iHeight		= iHeight;

#if (!defined __ANDROID__ && !defined MARMALADE && !defined EMSCRIPTEN && !defined ANGLE) || (!defined __ARMEL__ && defined __APPLE__)
	uint32_t*	pBuffer	= m_pImage;

	for (int iLoop = 0; iLoop < m_iWidth * m_iHeight; ++iLoop)
	{
		uint32_t	uValue	= *pBuffer;
		
		*pBuffer	= (uValue & 0xFF00FF00) | ((uValue & 0x00FF0000) >> 16) | ((uValue & 0x000000FF) << 16);

		pBuffer++;
	}
#endif

	return	true;
}

void Image::close()
{
	delete[] m_pImage;

	m_pImage	= NULL;
}

ENDNAMESPACE
