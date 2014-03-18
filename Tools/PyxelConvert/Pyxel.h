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
#include "PyxelStructs.h"

struct jsonADT;

class Pyxel
{
	public:
		// Constructor
		Pyxel();

		// Destructor
		~Pyxel();

		// Create
		static Pyxel* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	private:
		// Animations
		std::vector<Animation>	m_vecAnimations;

		// Tileset
		std::vector<Tileset>	m_vecTilesets;

		// Canvas
		Canvas					m_canvas;

		// Sprite final size
		int						m_iWidth;
		int						m_iHeight;
		int						m_iBPP;

		// Load JSON file
		bool loadJSON(const std::string& _strFilename);

		// Load sprites
		bool loadSprites(const std::string& _strFilename);

		// Parse animations node
		bool parseAnimationsNode(jsonADT* _pADT);
		
		// Parse animation
		bool parseAnimation(jsonADT* _pADT);
		
		// Parse tileset node
		bool parseTilesetNode(jsonADT* _pADT);
		
		// Parse canvas node
		bool parseCanvasNode(jsonADT* _pADT);
		
		// Parse layers node
		bool parseLayersNode(jsonADT* _pADT);
		
		// Parse layer
		bool parseLayer(jsonADT* _pADT);
		
		// Parse tileRefs node
		bool parseTileRefsNode(jsonADT* _pADT, Layer& _layer);
		
		// Parse tileRef
		bool parseTileRef(jsonADT* _pADT, Layer& _layer);
		
		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);
};

