// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stddef.h>

#include "Functions.h"
#include "HardwareDefines.h"
#include "Log.h"
#include "NAnim.h"
#include "LodePNG\LodePNG.h"

#ifdef _DEBUG
#pragma comment(lib, "libprotobuf_d.lib")
#else
#pragma comment(lib, "libprotobuf.lib")
#endif

NAnim::NAnim()
{
	// Verify that the version of the library that we linked against is compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

NAnim::~NAnim()
{
	close();
}

NAnim* NAnim::create()
{
	NAnim*	pNAnim	= new NAnim();

	if (false == pNAnim->initialize())
	{
		delete	pNAnim;

		pNAnim	= NULL;
	}

	return	pNAnim;
}

bool NAnim::initialize()
{
	return	true;
}

void NAnim::close()
{
	int	t_c	= static_cast<int>(m_vecImages.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete[]	m_vecImages[iLoop].pImage;
	}

	m_vecImages.clear();
}

bool NAnim::load(const std::string& _strFilename)
{
	std::fstream	file(_strFilename.c_str(), std::fstream::in | std::fstream::binary);

	im::bci::nanim::Nanim	anim;

	if (false == anim.ParseFromIstream(&file))
	{
		return	false;
	}

	if (false == loadAnimations(anim))
	{
		return	false;
	}

	if (false == loadImages(anim))
	{
		return	false;
	}

	file.close();

	google::protobuf::ShutdownProtobufLibrary();
	
	if (false == extractFrames())
	{
		return	false;
	}

	return	true;
}

bool NAnim::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

bool NAnim::loadAnimations(const im::bci::nanim::Nanim& _anim)
{
	int	iSize	= _anim.animations_size();

	if (iSize < 1)
	{
		Log::instance()->logError("File does not contain any animations");

		return	false;
	}

	im::bci::nanim::Animation	animation	= _anim.animations(0);
	
	int	iFrames	= animation.frames_size();

	if (iFrames < 1)
	{
		Log::instance()->logError("File does not contain any animation frames");

		return	false;
	}

	for (int iLoop = 0; iLoop < iFrames; ++iLoop)
	{
		if (false == loadFrame(animation.frames(iLoop)))
		{
			return	false;
		}
	}

	return	true;
}

bool NAnim::loadImages(const im::bci::nanim::Nanim& _anim)
{
	int	iImages	= _anim.images_size();

	if (iImages < 1)
	{
		Log::instance()->logError("File does not contain any images");

		return	false;
	}

	for (int iLoop = 0; iLoop < iImages; ++iLoop)
	{
		loadImage(_anim.images(iLoop));
	}

	return	true;
}

bool NAnim::loadFrame(const im::bci::nanim::Frame& _frame)
{
	NAnimFrame	frame;

	frame.strImageName	= _frame.imagename();
	frame.fU1			= _frame.u1();
	frame.fV1			= _frame.v1();
	frame.fU2			= _frame.u2();
	frame.fV2			= _frame.v2();

	m_vecFrames.push_back(frame);

	return	true;
}

bool NAnim::loadImage(const im::bci::nanim::Image& _image)
{
	NAnimImage	image;

	image.strImageName	= _image.name();
	image.iWidth		= _image.width();
	image.iHeight		= _image.height();

	int	iSize	= image.iWidth * image.iHeight;

	image.pImage	= new uint32_t[iSize];

	bool	rRGB	= _image.format() == im::bci::nanim::RGB_888;

	if (false == rRGB)
	{
		const uint32_t*	pSrc	= (const uint32_t*)&_image.pixels()[0];
	
		uint32_t*	pDest	= image.pImage;

		for (int iLoop = 0; iLoop < iSize; ++iLoop)
		{
			uint32_t	uPixel	= *pSrc;
			pSrc++;

			uint32_t	uAlpha	= (uPixel & 0xFF000000) >> 24;
			uint32_t	uRed	= (uPixel & 0x00FF0000) >> 16;
			uint32_t	uGreen	= (uPixel & 0x0000FF00) >> 8;
			uint32_t	uBlue	= (uPixel & 0x000000FF);

			if (uAlpha != 0)
			{
				uAlpha	= 0xFF;
			}

			*pDest	= (uAlpha << 24) | (uRed << 16) | (uGreen << 8) | uBlue;
			pDest++;
		}
	}

	else
	{
		const uint8_t*	pSrc	= (const uint8_t*)&_image.pixels();
	
		uint32_t*	pDest	= image.pImage;

		for (int iLoop = 0; iLoop < iSize; ++iLoop)
		{
			uint32_t	uRed	= *pSrc;
			pSrc++;

			uint32_t	uGreen	= *pSrc;
			pSrc++;

			uint32_t	uBlue	= *pSrc;
			pSrc++;

			*pDest	= 0xFF000000 | (uRed << 16) | (uGreen << 8) | uBlue;
			pDest++;
		}
	}

	m_vecImages.push_back(image);

	return	true;
}

bool NAnim::extractFrames()
{
	int	t_c	= static_cast<int>(m_vecFrames.size());

	if (0 == t_c)
	{
		return	false;
	}

	int	iImageWidth;
	int	iImageHeight;

	if (false == getImageSize(m_vecFrames[0].strImageName, iImageWidth, iImageHeight))
	{
		return	false;
	}

	m_iFrameWidth	= static_cast<int>(floor((m_vecFrames[0].fU2 - m_vecFrames[0].fU1) * static_cast<float>(iImageWidth)));
	m_iFrameHeight	= static_cast<int>(floor((m_vecFrames[0].fV2 - m_vecFrames[0].fV1) * static_cast<float>(iImageHeight)));

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		int	iImageWidth;
		int	iImageHeight;

		if (false == getImageSize(m_vecFrames[iLoop].strImageName, iImageWidth, iImageHeight))
		{
			return	false;
		}

		SpriteFrame	spriteFrame;

		spriteFrame.iWidth	= static_cast<int>(floor((m_vecFrames[iLoop].fU2 - m_vecFrames[iLoop].fU1) * static_cast<float>(iImageWidth)));
		spriteFrame.iHeight	= static_cast<int>(floor((m_vecFrames[iLoop].fV2 - m_vecFrames[iLoop].fV1) * static_cast<float>(iImageHeight)));
		
		spriteFrame.pImage	= new uint32_t[spriteFrame.iWidth * spriteFrame.iHeight];
	
		float	fX	= m_vecFrames[iLoop].fU1 * static_cast<float>(iImageWidth);
		float	fY	= m_vecFrames[iLoop].fV1 * static_cast<float>(iImageHeight);

		uint32_t*	pImageBuffer	= getImageBuffer(m_vecFrames[iLoop].strImageName);

		if (NULL == pImageBuffer)
		{
			Log::instance()->logError("Unable to find image buffer");

			return	false;
		}

		uint32_t*	pSrc	= pImageBuffer + static_cast<int>(static_cast<int>(fY) * static_cast<float>(iImageWidth) + static_cast<int>(fX));
		uint32_t*	pDest	= spriteFrame.pImage;

		for (int iYLoop = 0; iYLoop < spriteFrame.iHeight; ++iYLoop)
		{
			memcpy(pDest, pSrc, spriteFrame.iWidth * sizeof(uint32_t));

			pSrc	+= iImageWidth;
			pDest	+= spriteFrame.iWidth;
		}

		m_vecSpriteFrames.push_back(spriteFrame);
	}

	return	true;
}

bool NAnim::writePNG(const std::string& _strFilename)
{
	int	t_c	= static_cast<int>(m_vecSpriteFrames.size());

	if (0 == t_c)
	{
		return	false;
	}

	// Find power of two for the sprites.
	m_iFrameWidth	= static_cast<int>(pow(2, ceil(Functions::log2(m_iFrameWidth))));
	m_iFrameHeight	= static_cast<int>(pow(2, ceil(Functions::log2(m_iFrameHeight))));
	
	if (m_iFrameWidth < SPlay::gsc_iMinObjSize)
	{
		m_iFrameWidth	= SPlay::gsc_iMinObjSize;
	}

	if (m_iFrameHeight < SPlay::gsc_iMinObjSize)
	{
		m_iFrameHeight	= SPlay::gsc_iMinObjSize;
	}

	if (m_iFrameWidth > SPlay::gsc_iMaxObjSize || m_iFrameHeight > SPlay::gsc_iMaxObjSize)
	{
		Log::instance()->logError("Sprites must be <= %d pixels wide and tall\n", SPlay::gsc_iMaxObjSize);
		
		return	false;
	}

	int	iWidth	= m_iFrameWidth;
	int	iHeight	= m_iFrameHeight;
	int	iBPP	= sizeof(uint32_t);
	int	iSize	= iWidth * iHeight * iBPP;
	int	iStride	= iWidth * iBPP;

	uint8_t*	pBuffer	= new uint8_t[iSize * t_c];

	memset(pBuffer, 0, iSize * t_c);

	uint8_t*	pDest	= pBuffer;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		uint8_t*	pOffset	= pDest;

		int	iCelWidth	= m_vecSpriteFrames[iLoop].iWidth * iBPP;
		int	iCelHeight	= m_vecSpriteFrames[iLoop].iHeight;

		uint8_t*	pSrc	= reinterpret_cast<uint8_t*>(m_vecSpriteFrames[iLoop].pImage);

		for (int iYLoop = 0; iYLoop < iCelHeight; ++iYLoop)
		{
			memcpy(pOffset, pSrc, iCelWidth);

			pOffset	+= iStride;
			pSrc	+= iCelWidth;
		}

		pDest	+= iSize;
	}

	if (LodePNG_encode32_file(_strFilename.c_str(), reinterpret_cast<uint8_t*>(pBuffer), iWidth, iHeight * t_c) != 0)
	{
		return	false;
	}

	return	true;
}

bool NAnim::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

	sprintf(szString, "\t<FrameWidth>%d</FrameWidth>\n", m_iFrameWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameHeight>%d</FrameHeight>\n", m_iFrameHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameCount>%d</FrameCount>\n", static_cast<int>(m_vecSpriteFrames.size()));

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

bool NAnim::getImageSize(const std::string& _strImageName, int& _iWidth, int& _iHeight)
{
	int	t_c	= static_cast<int>(m_vecImages.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (m_vecImages[iLoop].strImageName == _strImageName)
		{
			_iWidth		= m_vecImages[iLoop].iWidth;
			_iHeight	= m_vecImages[iLoop].iHeight;

			return	true;
		}
	}

	return	false;
}

uint32_t* NAnim::getImageBuffer(const std::string& _strImageName)
{
	int	t_c	= static_cast<int>(m_vecImages.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (m_vecImages[iLoop].strImageName == _strImageName)
		{
			return	m_vecImages[iLoop].pImage;
		}
	}

	return	NULL;
}
