// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <unistd.h>
#include <sys/stat.h>

#include "AssertLog.h"
#include "StoragePath.h"

NAMESPACE(SPlay)

Storage::Storage()	:
	m_pHandle(NULL),
	m_bBinary(false)
{
}

Storage::~Storage()
{
	close();
}

bool Storage::open(const tinystl::string& _strFilename, bool _bBinary)
{
	// Close a previously opened file.
	if (m_pHandle != NULL)
	{
		close();
	}
	
	m_pHandle	= fopen(_strFilename.c_str(), true == _bBinary ? "rb" : "rt");
	
	if (NULL == m_pHandle)
	{
		return	false;
	}
	
	m_bBinary	= _bBinary;

	return	true;
}

bool Storage::create(const tinystl::string& _strFilename, bool _bBinary)
{
	// Close a previously opened file.
	if (m_pHandle != NULL)
	{
		close();
	}
	
	m_pHandle	= fopen(_strFilename.c_str(), true == _bBinary ? "wb" : "wt");
	
	if (NULL == m_pHandle)
	{
		return	false;
	}
	
	m_bBinary	= _bBinary;

	return	true;
}

bool Storage::close()
{
	if (m_pHandle != NULL)
	{
		fclose((FILE*)m_pHandle);
	
		m_pHandle	= NULL;
	}
	
	return	true;
}

bool Storage::read8Bit(char& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(char), (FILE*)m_pHandle) != sizeof(char))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::readUnsigned8Bit(uint8_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint8_t), (FILE*)m_pHandle) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::read16Bit(short& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(short), (FILE*)m_pHandle) != sizeof(short))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::readUnsigned16Bit(uint16_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint16_t), (FILE*)m_pHandle) != sizeof(uint16_t))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::read32Bit(int& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(int), (FILE*)m_pHandle) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::readUnsigned32Bit(uint32_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint32_t), (FILE*)m_pHandle) != sizeof(uint32_t))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::readBuffer(uint8_t** _pBuffer, int iBufferSize)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	if (-1 == iBufferSize)
	{
		iBufferSize	= getLength();
	}

	if (0 == iBufferSize)
	{
		return	false;
	}

	if (NULL == *_pBuffer)
	{
		*_pBuffer	= new  uint8_t[iBufferSize];
	}

	if (static_cast<int>(fread(*_pBuffer, 1, iBufferSize, (FILE*)m_pHandle)) != iBufferSize)
	{
		return	false;
	}
	
	return	true;
}

bool Storage::readBuffer(uint8_t* _pBuffer, int iBufferSize)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	ASSERT_LOG(_pBuffer != NULL, "Buffer is invalid");
	
	if (-1 == iBufferSize)
	{
		iBufferSize	= getLength();
	}

	if (0 == iBufferSize)
	{
		return	false;
	}

	if (static_cast<int>(fread(_pBuffer, 1, iBufferSize, (FILE*)m_pHandle)) != iBufferSize)
	{
		return	false;
	}
	
	return	true;
}

bool Storage::write8Bit(uint8_t _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fwrite(&_iValue, 1, sizeof(uint8_t), (FILE*)m_pHandle) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::write32Bit(int _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fwrite(&_iValue, 1, sizeof(int), (FILE*)m_pHandle) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool Storage::writeBuffer(const uint8_t* _pBuffer, int iBufferSize)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	if (fwrite(_pBuffer, 1, iBufferSize, (FILE*)m_pHandle) != iBufferSize)
	{
		return	false;
	}
	
	return	true;
}

bool Storage::writeString(const tinystl::string& _strString)
{
	int	iLength	= static_cast<int>(_strString.length());

	if (iLength > 0)
	{
		int	iBufferSize;
		
		if (true == m_bBinary)
		{
			iBufferSize	= iLength + 1;
		}
		
		else
		{
			iBufferSize	= iLength;
		}
		
		return	writeBuffer(reinterpret_cast<const uint8_t*>(_strString.c_str()), iBufferSize);
	}
	
	return	true;
}

bool Storage::seek(int _iOffset, SeekPoint _eSeekPoint)
{
	int	iOrigin;
	
	switch (_eSeekPoint)
	{
		case SeekFromStart:
			iOrigin	= SEEK_SET;
			
			break;
			
		case SeekFromCurrent:
			iOrigin	= SEEK_CUR;
			
			break;
			
		case SeekFromEnd:
			iOrigin	= SEEK_END;
			
			break;
	
		default:
			return	false;
	}
	
	if (fseek((FILE*)m_pHandle, _iOffset, iOrigin) != 0)
	{
		return	false;
	}
	
	return	true;
}

int Storage::getPosition() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	return	static_cast<int>(ftell((FILE*)m_pHandle));
}

int Storage::getLength() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	int	iCurrentPosition	= static_cast<int>(ftell((FILE*)m_pHandle));
	
	if (-1 == iCurrentPosition || fseek((FILE*)m_pHandle, 0, SEEK_END) != 0)
	{
		return	-1;
	}
	
	int	iLength	= static_cast<int>(ftell((FILE*)m_pHandle));
	
	fseek((FILE*)m_pHandle, iCurrentPosition, SEEK_SET);
	
	return	iLength;
}

bool Storage::fileExists(const tinystl::string& _strFilename)
{
	if (-1 == access(_strFilename.c_str(), F_OK))
	{
		return	true;
	}

	return	false;
}

bool Storage::deleteFile(const tinystl::string& _strFilename)
{
	if (unlink(_strFilename.c_str()) != 0)
	{
		return	false;
	}
	
	return	true;
}

bool Storage::createDirectory(const tinystl::string& _strFilename)
{
	if (mkdir(_strFilename.c_str(), 0777) != 0)
	{
		return	false;
	}

	return	true;
}

ENDNAMESPACE
