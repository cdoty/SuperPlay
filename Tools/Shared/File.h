// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <memory>
#include <string>

enum SeekPoint
{
	SeekFromStart,
	SeekFromCurrent,
	SeekFromEnd
};

// File read and writing class. Wraps FILE*, and provides additional functionality.
class File
{
	public:
		// Constructor
		File();
		
		// Destructor
		~File();

		// Open file
		bool open(const std::string& _strFilename, bool _bBinary = false);
	
		// Create file
		bool create(const std::string& _strFilename, bool _bBinary = false);
	
		// Close file
		bool close();
		
		// Read 8 bit value
		bool read8Bit(char& _iValue) const;
		
		// Read unsigned 8 bit value
		bool readUnsigned8Bit(uint8_t& _iValue) const;
		
		// Read 16 bit
		bool read16Bit(short& _iValue) const;
		
		// Read unsigned 16 bit
		bool readUnsigned16Bit(uint16_t& _iValue) const;
		
		// Read 32 bit
		bool read32Bit(int& _iValue) const;
		
		// Read unsigned 32 bit
		bool readUnsigned32Bit(uint32_t& _iValue) const;
		
		// Read buffer
		bool readBuffer(uint8_t** _pBuffer, int iBufferSize) const;
		
		// Write signed/unsigned 8 bit value
		bool write8Bit(uint8_t _iValue) const;
		
		// Write signed/unsigned 32 bit value
		bool write32Bit(int _iValue) const;
		
		// Write float value
		bool writeFloat(float _fValue) const;
		
		// Write buffer
		bool writeBuffer(const uint8_t* _pBuffer, int iBufferSize) const;
		
		// Write string
		bool writeString(const std::string& _strString);
		
		// Seek
		bool seek(int _iOffset, SeekPoint _eSeekPoint = SeekFromCurrent) const;
		
		// Get position
		int getPosition() const;
		
		// Get length
		int getLength() const;
		
		// File exists?
		static bool fileExists(const std::string& _strFilename);
		
		// Delete file
		static bool deleteFile(const std::string& _strFilename);
		
		// Create directory
		static bool createDirectory(const std::string& _strFilename);
		
	private:
		// File handle
		FILE*	m_pHandle;

		// Writing in binary format?
		bool	m_bBinary;

		// Make directory
		static bool makeDirectory(const std::string& _strFilename);
};
