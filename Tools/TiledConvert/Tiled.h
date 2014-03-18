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
#include <TinyXML2\TinyXml2.h>

#include "HardwareDefines.h"

struct TileImage
{
	// Source
	std::string	strSource;

	// Image size
	int	iWidth;
	int	iHeight;
};

struct TileSet
{
	// First tile number
	int	iFirstGid;

	// Name
	std::string	strName;

	// Tile size
	int	iTileWidth;
	int	iTileHeight;

	// Image
	TileImage	tileImage;

	// Image
	uint32_t*	pBuffer;

	// Tile count
	int			iTileCount;
};

struct Layer
{
	// Name
	std::string	strName;

	// Image size
	int	iWidth;
	int	iHeight;
	
	// Tiles
	std::vector<SPlay::TileInfo>	m_vecTiles;
};

class Tiled
{
	public:
		// Constructor
		Tiled();

		// Destructor
		~Tiled();

		// Create
		static Tiled* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strMapFilename, const std::string& _strXMLFilename);

	private:
		// Map size (in tiles)
		int	m_iMapWidth;
		int	m_iMapHeight;

		// Tile size
		int	m_iTileWidth;
		int	m_iTileHeight;

		// Tile count
		int	m_iTileCount;

		// Tile sets
		std::vector<TileSet>	m_vecTileSets;

		// Layers
		std::vector<Layer>		m_vecLayers;

		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write Map
		bool writeMap(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strMapFilename, const std::string& _strXMLFilename);

		// Read map
		bool readMap(xml::XMLNode* _pNode);

		// Read map info
		bool readMapInfo(xml::XMLNode* _pNode);

		// Read tileset
		bool readTileset(xml::XMLNode* _pNode);

		// Read tileset info
		bool readTilesetInfo(xml::XMLNode* _pNode, TileSet& _tileSet);

		// Read tileset children
		bool readTilesetChildren(xml::XMLNode* _pNode, TileSet& _tileSet);

		// Read image info
		bool readImageInfo(xml::XMLNode* _pNode, TileImage& _tileImage);

		// Read layer
		bool readLayer(xml::XMLNode* _pNode);

		// Read layer info
		bool readLayerInfo(xml::XMLNode* _pNode, Layer& _layer);

		// Read tiles
		bool readTiles(xml::XMLNode* _pNode, Layer& _layer);

		// Convert tiles
		bool convertTiles(int _iTileSet);

		// Extract tiles
		bool extractTiles(uint8_t* _pBuffer, int _iWidth, int _iHeight, int _iTileSet);
};
