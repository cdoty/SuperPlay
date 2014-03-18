// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/vector.h>

#include "Macros.h"
#include "BGVRAM.h"

NAMESPACE(SPlay)

class Image;
class ISpriteBatch;

class BG
{
	friend class	MapLoader;

	public:
		// Constructor
		BG(int _iIndex);

		// Destructor
		~BG();

		// Create the VRAM texture
		static BG* create(int _iIndex);

		// Initialize
		bool initialize();

		// Close
		void close();

		// Render
		void render();

		// Set mosaic
		void setMosiac(int _iMosaic) {m_iMosaic = _iMosaic;}

		// Set scroll position
		void setScrollPosition(int _iOffsetX, int _iOffsetY);

		// Set wrap
		void setWrap(bool _bWrap) {m_bWrap = _bWrap;}

		// Set active
		void setActive(bool _bActive) {m_bActive = _bActive;}

	private:
		// Sprite batch
		ISpriteBatch*			m_pSpriteBatch;

		// Map
		tinystl::vector<TileInfo>	m_vecTileMap;

		// Tile size
		int						m_iTileSize;

		// Tile size
		int						m_iTilesWide;
		int						m_iTilesHigh;
		int						m_iMapSize;

		// Map size
		int						m_iMapWidth;
		int						m_iMapHeight;

		// Scroll position
		int						m_iScrollX;
		int						m_iScrollY;

		// BG index
		int						m_iIndex;

		// Mosaic
		int						m_iMosaic;

		// Wrap?
		bool					m_bWrap;

		// Active?
		bool					m_bActive;

		// Setup sprite batch
		bool setupSpriteBatch();

		// Render mosaic
		void renderMosaic();
};

ENDNAMESPACE
