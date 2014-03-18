// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "ASEStructs.h"
#include "File.h"

class ASE
{
	public:
		// Constructor
		ASE();

		// Destructor
		~ASE();

		// Create
		static ASE* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	private:
		struct CellInfo
		{
			// Position
			int	iX;
			int	iY;

			// Size
			int	iWidth;
			int	iHeight;

			// Image
			uint8_t*	pImage;
		};

		// File header
		ASEHeader	m_fileHeader;

		// Cels
		std::vector<CellInfo>	m_vecCels;

		// Read header
		bool readHeader(File* _pFile);

		// Read frames
		bool readFrames(File* _pFile);

		// Read frame
		bool readFrame(File* _pFile);

		// Read chunk
		bool readChunk(File* _pFile);

		// Read layer chunk
		bool readLayerChunk(File* _pFile, int _iChunkSize);

		// Read cel chunk
		bool readCelChunk(File* _pFile, int _iChunkSize);

		// Skip chunk
		bool skipChunk(File* _pFile, int _iChunkSize);

		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);
};

