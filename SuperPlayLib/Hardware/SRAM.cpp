// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <string.h>
#include <stdlib.h>
#include <TinySTL/vector.h>

#include "AssertLog.h"
#include "CRC32.h"
#include "HardwareDefines.h"
#include "PlatformLib.h"
#include "SRAM.h"
#include "StoragePath.h"
#include "System.h"

NAMESPACE(SPlay)

// SRAM filename
static const char*	gsc_szSRAMBaseFilename	= "SRAM";

// SRAM copies
static const int	gsc_iSRAMCopies			= 3;

SRAM::SRAM()	:
	m_pBuffer(NULL),
	m_iSize(0),
	m_bChanged(false),
	m_bCorrupt(false),
	m_bFixed(false)
{
}

SRAM::~SRAM()
{
	close();
}

SRAM* SRAM::create()
{
	SRAM*	pSRAM	= new SRAM();

	if (false == pSRAM->initialize())
	{
		delete	pSRAM;

		pSRAM	= NULL;
	}

	return	pSRAM;
}

bool SRAM::initialize()
{
	m_iSize	= System::getGameHeader().iSRAMSize;

	m_bFixed	= false;
	m_bCorrupt	= true;

	// See if any of the save files are valid
	for (int iLoop = 0; iLoop < gsc_iSRAMCopies; ++iLoop)
	{
		char	szFilename[gsc_iMaxPathLength];

		sprintf(szFilename, "%s%s%d.sram", getStoragePath().c_str(), gsc_szSRAMBaseFilename, iLoop + 1);
	
		if (true == Storage::fileExists(szFilename))
		{
			Storage*	pStorage	= new Storage();

			if (false == pStorage->open(szFilename, true))
			{
				pStorage->close();

				delete	pStorage;

				Storage::deleteFile(szFilename);

				continue;
			}

			m_pBuffer	= NULL;
			
			uint32_t	uChecksum	= 0;

			if (static_cast<int>(m_iSize + sizeof(uint32_t)) != pStorage->getLength() || false == pStorage->readUnsigned32Bit(uChecksum) ||
				false == pStorage->readBuffer(&m_pBuffer, m_iSize))
			{
				pStorage->close();

				delete	pStorage;

				Storage::deleteFile(szFilename);

				continue;
			}
			
			pStorage->close();

			delete	pStorage;

			if (true == verifyBuffer(m_pBuffer, uChecksum))
			{
				if (0 == iLoop)
				{
					m_bCorrupt	= false;
				}

				if (true == m_bCorrupt)
				{
					m_bFixed	= true;
				}

				return	true;
			}

			else
			{
				delete[]	m_pBuffer;

				m_pBuffer	= NULL;

				Storage::deleteFile(szFilename);
			}
		}
	}

	// Create the buffer if one wasn't loaded
	m_pBuffer	= new uint8_t[m_iSize];	

	memset(m_pBuffer, 0, m_iSize);

	return	true;
}

void SRAM::close()
{
	ASSERT_LOG(false == m_bChanged, "SRAM has uncommitted changes");

	delete	m_pBuffer;

	m_pBuffer	= NULL;
}

bool SRAM::readSRAM(uint8_t* _pData)
{
	if (m_iSize > 0 && m_pBuffer != NULL)
	{
		memcpy(_pData, m_pBuffer, m_iSize);

		return	true;
	}

	return	false;
}

bool SRAM::verifyBuffer(uint8_t* _pBuffer, uint32_t _uChecksum)
{
	uint32_t	uBufferChecksum	= calculateCRC32(_pBuffer, m_iSize);

	if (uBufferChecksum != _uChecksum)
	{
		return	false;
	}

	return	true;
}

void SRAM::updateSRAM(int _iOffset, uint8_t* _pData, int _iDataLength)
{
	ASSERT_LOG(_iOffset + _iDataLength <= m_iSize, "Attempting to write past the end of the SRAM buffer.");

	memcpy(m_pBuffer + _iOffset, _pData, _iDataLength);

	m_bChanged	= true;
}

bool SRAM::commitSRAM()
{
	bool	bRetVal	= true;

	m_bChanged	= false;

	if (m_iSize > 0)
	{
		uint32_t	uBufferChecksum	= calculateCRC32(m_pBuffer, m_iSize);

		for (int iLoop = 0; iLoop < gsc_iSRAMCopies; ++iLoop)
		{
			char	szFilename[gsc_iMaxPathLength];

			sprintf(szFilename, "%s%s%d.sram", getStoragePath().c_str(), gsc_szSRAMBaseFilename, iLoop + 1);
	
			Storage*	pStorage	= new Storage();

			if (false == pStorage->create(szFilename, true) || false == pStorage->write32Bit(uBufferChecksum) ||
				false == pStorage->writeBuffer(m_pBuffer, m_iSize))
			{
				bRetVal	= false;
			}

			pStorage->close();
				
			delete	pStorage;
		}
	}

	return	bRetVal;
}

ENDNAMESPACE
