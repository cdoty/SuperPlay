// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "Macros.h"

NAMESPACE(SPlay)

class SRAM
{
	public:
		// Constructor
		SRAM();

		// Destructor
		~SRAM();

		// Create the VRAM texture
		static SRAM* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Read SRAM
		bool readSRAM(uint8_t* _pData);

		// Update SRAM
		void updateSRAM(int _iOffset, uint8_t* _pData, int _iDataLength);

		// Commit SRAM
		bool commitSRAM();

		// Get corrupt status
		bool getCorrupt() {return m_bCorrupt;}

		// Get fixed status
		bool getFixed() {return m_bFixed;}

	private:
		// Buffer
		uint8_t*	m_pBuffer;

		// SRAM size
		int			m_iSize;

		// Changed
		bool		m_bChanged;

		// Corrupt
		bool		m_bCorrupt;

		// Fixed
		bool		m_bFixed;

		// Verify buffer
		bool verifyBuffer(uint8_t* _pBuffer, uint32_t _uChecksum);
};

ENDNAMESPACE
