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

struct Tile8
{
	// Size
	int		iWidth;
	int		iHeight;

	// Image
	uint8_t*	pImage;
};

struct Tile32
{
	// Size
	int		iWidth;
	int		iHeight;

	// Image
	uint32_t*	pImage;
};

class Font
{
	public:
		// Constructor
		Font();

		// Destructor
		~Font();

		// Create
		static Font* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	private:
		// Palette
		uint8_t*	m_pPalette;
		int			m_iPaletteCount;

		// Paletted
		bool		m_bPaletted;

		// Image size
		int			m_iWidth;
		int			m_iHeight;

		// Tiles
		std::vector<Tile8>	m_vec8BitTiles;
		std::vector<Tile32>	m_vec32BitTiles;

		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

		// Extract 8 bit font
		bool extract8BitFont(uint8_t* _pBuffer);
		
		// Extract 8 bit character
		bool extract8BitCharacter(uint8_t* _pBuffer, int _iX1, int _iX2, uint8_t _uBackgroundColor);

		// Extract 32 bit font
		bool extract32BitFont(uint8_t* _pBuffer);

		// Extract 32 bit character
		bool extract32BitCharacter(uint32_t* _pBuffer, int _iX1, int _iX2, uint32_t _uBackgroundColor);
};


