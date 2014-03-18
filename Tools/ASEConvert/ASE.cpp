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

#include "ASE.h"
#include "Functions.h"
#include "HardwareDefines.h"
#include "Log.h"
#include "LodePNG\LodePNG.h"
#include "MiniZ\miniz.h"

ASE::ASE()
{
}

ASE::~ASE()
{
	close();
}

ASE* ASE::create()
{
	ASE*	pASE	= new ASE();

	if (false == pASE->initialize())
	{
		delete	pASE;

		pASE	= NULL;
	}

	return	pASE;
}

bool ASE::initialize()
{
	return	true;
}

void ASE::close()
{
	int	t_c	= static_cast<int>(m_vecCels.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete[]	m_vecCels[iLoop].pImage;
	}

	m_vecCels.clear();
}

bool ASE::load(const std::string& _strFilename)
{
	File*	pFile	= new File();

	if (false == pFile->open(_strFilename, true))
	{
		delete	pFile;

		return	false;
	}

	if (false == readHeader(pFile))
	{
		return	false;
	}

	if (false == readFrames(pFile))
	{
		return	false;
	}

	pFile->close();

	delete	pFile;

	return	true;
}

bool ASE::save(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

bool ASE::readHeader(File* _pFile)
{
	uint8_t*	pBuffer	= reinterpret_cast<uint8_t*>(&m_fileHeader);

	if (false == _pFile->readBuffer(&pBuffer, sizeof(ASEHeader)))
	{
		return	false;
	}

	if (m_fileHeader.uMagicNumber != 0xA5E0)
	{
		return	false;
	}
	
	return	true;
}

bool ASE::readFrames(File* _pFile)
{
	int	t_c	= m_fileHeader.uFrames;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (false == readFrame(_pFile))
		{
			return	false;
		}
	}

	return	true;
}

bool ASE::readFrame(File* _pFile)
{
	ASEFrameHeader	frameHeader;

	uint8_t*	pBuffer	= reinterpret_cast<uint8_t*>(&frameHeader);

	if (false == _pFile->readBuffer(&pBuffer, sizeof(ASEFrameHeader)))
	{
		return	false;
	}

	if (frameHeader.uMagicNumber != 0xF1FA)
	{
		return	false;
	}

	int	t_c	= frameHeader.uChunks;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (false == readChunk(_pFile))
		{
			return	false;
		}
	}

	return	true;
}

bool ASE::readChunk(File* _pFile)
{
	uint32_t	uChunkSize;
	uint16_t	uChunkType;

	if (false == _pFile->readUnsigned32Bit(uChunkSize))
	{
		return	false;
	}

	if (false == _pFile->readUnsigned16Bit(uChunkType))
	{
		return	false;
	}

	uChunkSize	-= (sizeof(uint32_t) + sizeof(uint16_t));

	switch (uChunkType)
	{
		case LayerChunk:
			readLayerChunk(_pFile, uChunkSize);

			break;

		case CelChunk:
			readCelChunk(_pFile, uChunkSize);

			break;
	
		default:
			skipChunk(_pFile, uChunkSize);
	}

	return	true;
}

bool ASE::readLayerChunk(File* _pFile, int _iChunkSize)
{
	uint8_t*	pBuffer	= NULL;

	if (false == _pFile->readBuffer(&pBuffer, _iChunkSize))
	{
		return	false;
	}

	LayerChunkData*	pLayerChunk	= reinterpret_cast<LayerChunkData*>(pBuffer);

	delete[]	pBuffer;

	return	true;
}

bool ASE::readCelChunk(File* _pFile, int _iChunkSize)
{
	uint8_t*	pBuffer	= NULL;

	if (false == _pFile->readBuffer(&pBuffer, _iChunkSize))
	{
		return	false;
	}

	CelChunkData*	pCelChunk	= reinterpret_cast<CelChunkData*>(pBuffer);
	
	if (0 == pCelChunk->uCelType)
	{
		RawCel*	pRawCel	= reinterpret_cast<RawCel*>(pBuffer + sizeof(CelChunkData));

		CellInfo	cellInfo;

		cellInfo.iX			= 0;
		cellInfo.iY			= 0;
		cellInfo.iWidth		= pCelChunk->uX + pRawCel->uWidth;
		cellInfo.iHeight	= pCelChunk->uY + pRawCel->uHeight;
		
		int	iSize	= cellInfo.iWidth * cellInfo.iHeight * m_fileHeader.uColorDepth / 8;

		cellInfo.pImage		= new uint8_t[iSize];
	
		memcpy(cellInfo.pImage, pRawCel->uPixels, iSize);

		m_vecCels.push_back(cellInfo);
	}

	else if (2 == pCelChunk->uCelType)
	{
		RawCel*	pRawCel	= reinterpret_cast<RawCel*>(pBuffer + sizeof(CelChunkData));

		CellInfo	cellInfo;

		cellInfo.iX			= pCelChunk->uX;
		cellInfo.iY			= pCelChunk->uY;
		cellInfo.iWidth		= pRawCel->uWidth;
		cellInfo.iHeight	= pRawCel->uHeight;
		
		if (cellInfo.iWidth > m_fileHeader.uWidth)
		{
			cellInfo.iWidth	= m_fileHeader.uWidth;
		}

		if (cellInfo.iHeight > m_fileHeader.uHeight)
		{
			cellInfo.iHeight	= m_fileHeader.uHeight;
		}

		int	iCompressedSize	= _iChunkSize - sizeof(CelChunkData) - sizeof(RawCel) + 1;

		mz_ulong	uImageSize	= cellInfo.iWidth * cellInfo.iHeight * m_fileHeader.uColorDepth / 8;

		mz_ulong	uSize	= uImageSize;

		cellInfo.pImage		= new uint8_t[uSize];
	
		mz_uncompress(cellInfo.pImage, &uSize, pRawCel->uPixels, iCompressedSize);

		if (uImageSize != uSize)
		{
			return	false;
		}

		m_vecCels.push_back(cellInfo);
	}

	delete[]	pBuffer;

	return	true;
}

bool ASE::skipChunk(File* _pFile, int _iChunkSize)
{
	uint8_t*	pBuffer	= NULL;

	if (false == _pFile->readBuffer(&pBuffer, _iChunkSize))
	{
		return	false;
	}

	delete[]	pBuffer;

	return	true;
}

bool ASE::writePNG(const std::string& _strFilename)
{
	int	t_c	= static_cast<int>(m_vecCels.size());

	if (0 == t_c)
	{
		return	false;
	}

	// Find power of two for the sprites.
	m_fileHeader.uWidth		= static_cast<int>(pow(2, ceil(Functions::log2(m_fileHeader.uWidth))));
	m_fileHeader.uHeight	= static_cast<int>(pow(2, ceil(Functions::log2(m_fileHeader.uHeight))));
	
	if (m_fileHeader.uWidth < SPlay::gsc_iMinObjSize)
	{
		m_fileHeader.uWidth	= SPlay::gsc_iMinObjSize;
	}

	if (m_fileHeader.uHeight < SPlay::gsc_iMinObjSize)
	{
		m_fileHeader.uHeight	= SPlay::gsc_iMinObjSize;
	}

	if (m_fileHeader.uWidth > SPlay::gsc_iMaxObjSize || m_fileHeader.uHeight > SPlay::gsc_iMaxObjSize)
	{
		Log::instance()->logError("Sprites must be <= %d pixels wide and tall\n", SPlay::gsc_iMaxObjSize);
		
		return	false;
	}

	int	iWidth	= m_fileHeader.uWidth;
	int	iHeight	= m_fileHeader.uHeight;
	int	iBPP	= m_fileHeader.uColorDepth / 8;
	int	iSize	= iWidth * iHeight * iBPP;
	int	iStride	= iWidth * iBPP;

	uint8_t*	pBuffer	= new uint8_t[iSize * t_c];

	memset(pBuffer, 0, iSize * t_c);

	uint8_t*	pDest	= pBuffer;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		uint8_t*	pOffset	= pDest + (m_vecCels[iLoop].iY * iWidth + m_vecCels[iLoop].iX) * iBPP;

		int	iCelWidth	= m_vecCels[iLoop].iWidth * iBPP;
		int	iCelHeight	= m_vecCels[iLoop].iHeight;

		uint8_t*	pSrc	= m_vecCels[iLoop].pImage;

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

bool ASE::writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename)
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

	sprintf(szString, "\t<FrameWidth>%d</FrameWidth>\n", m_fileHeader.uWidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameHeight>%d</FrameHeight>\n", m_fileHeader.uHeight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}

	sprintf(szString, "\t<FrameCount>%d</FrameCount>\n", static_cast<int>(m_vecCels.size()));

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
