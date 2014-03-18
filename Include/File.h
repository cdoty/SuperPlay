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
#include <TinySTL/stdint.h>
#include <TinySTL/string.h>

#include "Macros.h"

NAMESPACE(SPlay)

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
		bool open(const tinystl::string& _strFilename, bool _bBinary = false);
	
		// Close file
		bool close();
		
		// Read 8 bit value
		bool read8Bit(char& _iValue);
		
		// Read unsigned 8 bit value
		bool readUnsigned8Bit(uint8_t& _iValue);
		
		// Read 16 bit
		bool read16Bit(short& _iValue);
		
		// Read unsigned 16 bit
		bool readUnsigned16Bit(uint16_t& _iValue);
		
		// Read 32 bit
		bool read32Bit(int& _iValue);
		
		// Read unsigned 32 bit
		bool readUnsigned32Bit(uint32_t& _iValue);
		
		// Read buffer
		bool readBuffer(uint8_t** _pBuffer, int iBufferSize = -1);
		
		// Read buffer
		bool readBuffer(uint8_t* _pBuffer, int iBufferSize = -1);
		
		// Seek
		bool seek(int _iOffset, SeekPoint _eSeekPoint = SeekFromCurrent);
		
		// Get position
		int getPosition() const;
		
		// Get length
		int getLength() const;
		
	private:
		// File handle
		void*	m_pHandle;

		// Writing in binary format?
		bool	m_bBinary;
};

ENDNAMESPACE
