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

#include "File.h"
#include "PickleStructs.h"

struct jsonADT;

class Pickle
{
	public:
		// Constructor
		Pickle();

		// Destructor
		~Pickle();

		// Create
		static Pickle* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	private:
		// Canvas
		FileInfo				m_fileInfo;

		// Tileset
		std::vector<Tileset>	m_vecTilesets;

		// Sprite final size
		int						m_iWidth;
		int						m_iHeight;
		int						m_iBPP;

		// Load JSON file
		bool loadJSON(const std::string& _strFilename);

		// Load sprites
		bool loadSprites(const std::string& _strFilename);

		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

		// Extract tile
		void extractTile(uint32_t* _pSource, int _iX, int _iY, Tileset& _tileset);
};

