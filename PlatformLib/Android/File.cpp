// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "android_native_app_glue.h"
#include "AssertLog.h"
#include "File.h"
#include "Platform.h"

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

	m_pHandle	= AAssetManager_open(Platform::getAssetManager(), _strFilename.c_str(), AASSET_MODE_STREAMING);
	
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
		AAsset_close((AAsset*)m_pHandle);
	
		m_pHandle	= NULL;
	}
	
	return	true;
}

bool File::read8Bit(char& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(char)) != sizeof(char))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned8Bit(uint8_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(uint8_t)) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read16Bit(short& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(short)) != sizeof(short))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned16Bit(uint16_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(uint16_t)) != sizeof(uint16_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read32Bit(int& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(int)) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned32Bit(uint32_t& _iValue)
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");

	if (AAsset_read((AAsset*)m_pHandle, &_iValue, sizeof(uint32_t)) != sizeof(uint32_t))
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

	if (AAsset_read((AAsset*)m_pHandle, *_pBuffer, iBufferSize) != iBufferSize)
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

	if (AAsset_read((AAsset*)m_pHandle, _pBuffer, iBufferSize) != iBufferSize)
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
	
	if (AAsset_seek((AAsset*)m_pHandle, _iOffset, iOrigin) != 0)
	{
		return	false;
	}
	
	return	true;
}

int File::getPosition() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	return	AAsset_seek((AAsset*)m_pHandle, 0, SEEK_CUR);
}

int File::getLength() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid");
	
	int	iLength	= AAsset_getLength((AAsset*)m_pHandle);
	
	return	iLength;
}

ENDNAMESPACE
