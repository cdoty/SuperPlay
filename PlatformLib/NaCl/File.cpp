// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "AssertLog.h"
#include "File.h"

NAMESPACE(SPlay)

File::File()	:
	m_pHandle(NULL),
	m_bBinary(false)
{
}

File::~File()
{
	close();
}

bool File::open(const tinystl::string& _strFilename, bool _bBinary)
{
	// Close a previously opened file.
	if (m_pHandle != NULL)
	{
		close();
	}
	
	tinystl::string	strFilepath;
	
	strFilepath	= "/";
	strFilepath += _strFilename;

	m_pHandle	= fopen(strFilepath.c_str(), true == _bBinary ? "rb" : "rt");
	
	if (NULL == m_pHandle)
	{
		return	false;
	}
	
	m_bBinary	= _bBinary;

	return	true;
}

bool File::close()
{
	if (m_pHandle != NULL)
	{
		fclose((FILE*)m_pHandle);
	
		m_pHandle	= NULL;
	}
	
	return	true;
}

bool File::read8Bit(char& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(char), (FILE*)m_pHandle) != sizeof(char))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned8Bit(uint8_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint8_t), (FILE*)m_pHandle) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read16Bit(short& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(short), (FILE*)m_pHandle) != sizeof(short))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned16Bit(uint16_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint16_t), (FILE*)m_pHandle) != sizeof(uint16_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read32Bit(int& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(int), (FILE*)m_pHandle) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned32Bit(uint32_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (fread(&_iValue, 1, sizeof(uint32_t), (FILE*)m_pHandle) != sizeof(uint32_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::readBuffer(uint8_t** _pBuffer, int iBufferSize)
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

bool File::readBuffer(uint8_t* _pBuffer, int iBufferSize)
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

bool File::seek(int _iOffset, SeekPoint _eSeekPoint)
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

int File::getPosition() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	return	ftell((FILE*)m_pHandle);
}

int File::getLength() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	int	iCurrentPosition	= ftell((FILE*)m_pHandle);
	
	if (-1 == iCurrentPosition || fseek((FILE*)m_pHandle, 0, SEEK_END) != 0)
	{
		return	-1;
	}
	
	int	iLength	= ftell((FILE*)m_pHandle);
	
	fseek((FILE*)m_pHandle, iCurrentPosition, SEEK_SET);
	
	return	iLength;
}

ENDNAMESPACE

