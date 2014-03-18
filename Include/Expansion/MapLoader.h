// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>

#include "BG.h"
#include "Macros.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif
#endif

NAMESPACE(SPlay)

class MapLoader
{
	public:
		// Constructor
		MapLoader(int _iIndex);

		// Destructor
		virtual ~MapLoader();

		// Create the map loader
		static MapLoader* create(int _iIndex, const tinystl::string& _strMapName, const tinystl::string& _strSubDirectory = "");

		// Initialize
		bool initialize(const tinystl::string& _strMapName, const tinystl::string& _strSubDirectory);

		// Close
		void close();

		// Get map size (in pixels)
		int getMapWidth() const {return m_iTileWidth * m_iMapWidth;}
		int getMapHeight() const {return m_iTileHeight * m_iMapHeight;}

	private:
		// Background index
		int				m_iIndex;

		// Sub directory
		tinystl::string	m_strSubDirectory;

		// Tile name
		tinystl::string	m_strTileName;

		// Map name
		tinystl::string	m_strMapName;

		// Image index
		int				m_iImageIndex;

		// Tile size
		int				m_iTileWidth;
		int				m_iTileHeight;

		// Map size
		int				m_iMapWidth;
		int				m_iMapHeight;

		// Tile count
		int				m_iTileCount;

		// Load XML
		bool loadXML(const tinystl::string& _strMapName);

		// Create VRAM
		bool createVRAM();

		// Load tiles
		bool loadTiles();

		// Load map
		bool loadMap();
};

ENDNAMESPACE
