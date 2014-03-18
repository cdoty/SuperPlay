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
#include "ProMotion.h"
#include "LodePNG\LodePNG.h"

// Size of the palette, in the Pro Motion file
static const int	gsc_iPaletteSize	= 256 * 3;

ProMotion::ProMotion()	:
	m_iFrames(0),
	m_iWidth(0),
	m_iHeight(0)
{
	m_vecFrames.clear();
}

ProMotion::~ProMotion()
{
	int	t_c	= static_cast<int>(m_vecFrames.size());
	
	// Delete all allocated memory in the frames
	for	(int iLoop = 0; iLoop < t_c; iLoop++)
	{
		delete[]	m_vecFrames[iLoop].pPalette;
			
		m_vecFrames[iLoop].pPalette	= NULL;

		delete[]	m_vecFrames[iLoop].pPixels;
			
		m_vecFrames[iLoop].pPixels	= NULL;
	}

	// Clear the frames
	m_vecFrames.clear();	
}

bool ProMotion::load(const std::string& _strFilename)
{
	uint8_t*	pSignature	= NULL;
	uint16_t	uTemp;

	File	*pFile	= new File();
	
	if (false == pFile->open(_strFilename, true))
	{
		Log::instance()->logError("Unable to open sprite file %s.", _strFilename.c_str());

		return	false;
	}

	// Read the 3 byte signature
	if (false == pFile->readBuffer(&pSignature, 3))
	{
		return	false;
	}
	
	if (pSignature[0] != 'S' && pSignature[1] != 'P' && pSignature[2] != 'R')
	{
		Log::instance()->logError("Sprite file, %s, is invalid.", _strFilename.c_str());	

		return	false;
	}

	delete[]	pSignature;
		
	// Read the number of frames
	if (false == pFile->readUnsigned16Bit(uTemp))
	{
		return	false;
	}

	m_iFrames	= uTemp;
	
	// Read the width
	if (false == pFile->readUnsigned16Bit(uTemp))
	{
		return	false;
	}

	m_iWidth	= uTemp;
	
	// Read the height
	if (false == pFile->readUnsigned16Bit(uTemp))
	{
		return	false;
	}

	m_iHeight	= uTemp;
	
	for (int iLoop = 0; iLoop < m_iFrames; iLoop++)
	{
		Frame	frame;
		
		// Read the frame delay
		if (false == pFile->readUnsigned16Bit(uTemp))
		{
			return	false;
		}

		frame.iDelay	= uTemp;
	
		frame.pPalette	= NULL;
	
		// Read the palette
		if (false == pFile->readBuffer(&frame.pPalette, gsc_iPaletteSize))
		{
			Log::instance()->logError("Unable to read palette.");

			return	false;
		}

		frame.pPixels	= NULL;
	
		// Read the pixels
		if (false == pFile->readBuffer(&frame.pPixels, m_iWidth * m_iHeight))
		{
			Log::instance()->logError("Unable to read pixels.");

			return	false;
		}

		// Store the frame
		m_vecFrames.push_back(frame);
	}
	
	int	iPosition	= pFile->getPosition();

	std::string	strTransparent	= "TRANSP";

	int	iStrSize	= strTransparent.length();

	if (iPosition + iStrSize <= pFile->getLength())
	{
		uint8_t*	pTransparent	= new uint8_t[iStrSize + 1];

		memset(pTransparent, 0, iStrSize + 1);

		if (true == pFile->readBuffer(&pTransparent, iStrSize))
		{
			std::string	strRead	= reinterpret_cast<char*>(pTransparent);

			if (strRead == strTransparent)
			{
				uint8_t	uValue;

				pFile->readUnsigned8Bit(uValue);

				m_iTransparentIndex	= uValue;
			}

			else
			{
				m_iTransparentIndex	= 0;
			}
		}
		
		else
		{
			m_iTransparentIndex	= 0;
		}
	}

	pFile->close();

	delete	pFile;

	return	true;
}

bool ProMotion::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

bool ProMotion::writePNG(const std::string& _strPNGFilename)
{
	int	t_c	= static_cast<int>(m_iFrames);

	if (0 == t_c)
	{
		return	false;
	}

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

	// Find power of two for the sprites.
	int	iWidth	= static_cast<int>(pow(2, ceil(Functions::log2(m_iWidth))));
	int	iHeight	= static_cast<int>(pow(2, ceil(Functions::log2(m_iHeight))));

	int	iFrameSize	= iWidth * iHeight;

	uint32_t*	pBuffer	= new uint32_t[t_c * iFrameSize];

	memset(pBuffer, 0, t_c * iFrameSize * sizeof(uint32_t));

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		writeFrame(iLoop, &pBuffer[iLoop * iFrameSize], iWidth);
	}
		
	if (LodePNG_encode32_file(_strPNGFilename.c_str(), reinterpret_cast<uint8_t*>(pBuffer), iWidth, iHeight * t_c) != 0)
	{
		return	false;
	}

	delete[]	pBuffer;

	return	true;
}

bool ProMotion::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
{
	std::string	strPNGName	= Functions::getFullFilenameFromPath(_strPNGFilename);

	File*	pFile	= new File();

	if (false == pFile->create(_strXMLFilename))
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

	sprintf(szString, "\t<FrameCount>%d</FrameCount>\n", m_iFrames);

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

void ProMotion::writeFrame(int _iIndex, uint32_t* _pBuffer, int _iStride)
{
	uint8_t*	pSrc		= m_vecFrames[_iIndex].pPixels;
	uint32_t*	pDest		= _pBuffer;
	uint8_t*	pPalette	= m_vecFrames[_iIndex].pPalette;

	for (int iYLoop = 0; iYLoop < m_iHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < m_iWidth; ++iXLoop)
		{
			int	iIndex	= *pSrc;

			uint32_t	uPixel;

			if (iIndex == m_iTransparentIndex)
			{
				uPixel	= 0;
			}

			else
			{
				uPixel	= (0xFF << 24) | (pPalette[iIndex * 3 + 2] << 16) | (pPalette[iIndex * 3 + 1] << 8) | (pPalette[iIndex * 3]);
			}

			*pDest	= uPixel;

			pSrc++;
			pDest++;
		}

		pDest	+= _iStride - m_iWidth;
	}
}
