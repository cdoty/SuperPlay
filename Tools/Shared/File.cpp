// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <direct.h>
#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#include <stdlib.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#include "AssertLog.h"
#include "File.h"

File::File()	:
	m_pHandle(NULL),
	m_bBinary(false)
{
}

File::~File()
{
	close();
}

bool File::open(const std::string& _strFilename, bool _bBinary)
{
	// Close a previously opened file.
	if (m_pHandle != NULL)
	{
		close();
	}
	
	fopen_s(&m_pHandle, _strFilename.c_str(), true == _bBinary ? "rb" : "rt");
	
	if (NULL == m_pHandle)
	{
		return	false;
	}
	
	m_bBinary	= _bBinary;

	return	true;
}

bool File::create(const std::string& _strFilename, bool _bBinary)
{
	// Close a previously opened file.
	if (m_pHandle != NULL)
	{
		close();
	}
	
	fopen_s(&m_pHandle, _strFilename.c_str(), true == _bBinary ? "wb" : "wt");
	
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
		fclose(m_pHandle);
	
		m_pHandle	= NULL;
	}
	
	return	true;
}

bool File::read8Bit(char& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(char), m_pHandle) != sizeof(char))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned8Bit(uint8_t& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(uint8_t), m_pHandle) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read16Bit(short& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(short), m_pHandle) != sizeof(short))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned16Bit(uint16_t& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(uint16_t), m_pHandle) != sizeof(uint16_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::read32Bit(int& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(int), m_pHandle) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool File::readUnsigned32Bit(uint32_t& _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fread(&_iValue, 1, sizeof(uint32_t), m_pHandle) != sizeof(uint32_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::readBuffer(uint8_t** _pBuffer, int iBufferSize) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");
	
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
	
	if (fread(*_pBuffer, 1, iBufferSize, m_pHandle) != iBufferSize)
	{
		return	false;
	}
	
	return	true;
}

bool File::write8Bit(uint8_t _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fwrite(&_iValue, 1, sizeof(uint8_t), m_pHandle) != sizeof(uint8_t))
	{
		return	false;
	}
	
	return	true;
}

bool File::write32Bit(int _iValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fwrite(&_iValue, 1, sizeof(int), m_pHandle) != sizeof(int))
	{
		return	false;
	}
	
	return	true;
}

bool File::writeFloat(float _fValue) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");

	if (fwrite(&_fValue, 1, sizeof(float), m_pHandle) != sizeof(float))
	{
		return	false;
	}
	
	return	true;
}

bool File::writeBuffer(const uint8_t* _pBuffer, int iBufferSize) const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");
	
	if (fwrite(_pBuffer, 1, iBufferSize, m_pHandle) != iBufferSize)
	{
		return	false;
	}
	
	return	true;
}

bool File::writeString(const std::string& _strString)
{
	if (false == _strString.empty())
	{
		int	iBufferSize;
		
		if (true == m_bBinary)
		{
			iBufferSize	= _strString.length() + 1;
		}
		
		else
		{
			iBufferSize	= _strString.length();
		}
		
		return	writeBuffer(reinterpret_cast<const uint8_t*>(_strString.c_str()), iBufferSize);
	}
	
	return	true;
}

bool File::seek(int _iOffset, SeekPoint _eSeekPoint) const
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
	
	if (fseek(m_pHandle, _iOffset, iOrigin) != 0)
	{
		return	false;
	}
	
	return	true;
}

int File::getPosition() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");
	
	return	ftell(m_pHandle);
}

int File::getLength() const
{
	ASSERT_LOG(m_pHandle != NULL, "File handle is invalid\n");
	
	int	iCurrentPosition	= ftell(m_pHandle);
	
	if (-1 == iCurrentPosition || fseek(m_pHandle, 0, SEEK_END) != 0)
	{
		return	-1;
	}
	
	int	iLength	= ftell(m_pHandle);
	
	fseek(m_pHandle, iCurrentPosition, SEEK_SET);
	
	return	iLength;
}

bool File::fileExists(const std::string& _strFilename)
{
	if (-1 == _access(_strFilename.c_str(), 0))
	{
		return	true;
	}

	return	false;
}

bool File::deleteFile(const std::string& _strFilename)
{
	if (_unlink(_strFilename.c_str()) != 0)
	{
		return	false;
	}
	
	return	true;
}

bool File::createDirectory(const std::string& _strDirectory)
{
    if (false == makeDirectory(_strDirectory))
	{
		int	iSeparator;

		if (strchr(_strDirectory.c_str(), '\\'))
		{
			iSeparator	= '\\';
		}

		else
		{
			iSeparator	= '/';
		}

		int	t_c	= (int)_strDirectory.size();

		std::string	strPath;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			int	iCharacter	= _strDirectory[iLoop];

			if (iSeparator == iCharacter)
			{
				int	iLength	= (int)strPath.length();

				if (iLength > 0 && strPath[iLength - 1] != ':' && strPath[iLength - 1] != '.')
				{
					if (false == makeDirectory(strPath))
					{
						return	false;
					}
				}
			}

			strPath.push_back(iCharacter);
		}

		t_c	= (int)strPath.length();

		if (t_c > 0 && strPath[t_c - 1] != iSeparator)
		{
			if (false == makeDirectory(strPath))
			{
				return	false;
			}
		}
	}
	
	return	true;
}

bool File::makeDirectory(const std::string& _strFilename)
{
	if (_mkdir(_strFilename.c_str()) != 0)
	{
		if (EEXIST == errno)
		{
			return	true;
		}

		return	false;
	}

	return	true;
}
