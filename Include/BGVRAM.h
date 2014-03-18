// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/stdint.h>
#include <TinySTL/vector.h>

#include "HardwareDefines.h"
#include "IVRAM.h"
#include "Macros.h"

NAMESPACE(SPlay)

class BGVRAM : public IVRAM
{
	public:
		// Constructor
		BGVRAM(TileSize _eTileSize);

		// Destructor
		virtual ~BGVRAM();

		// Create the VRAM texture
		static BGVRAM* create(TileSize _eTileSize);

		// Initialize
		bool initialize();

		// Close
		void close();

		// Get texture index
		int getTextureIndex(int _iBG) const;

		// Get tile UVs
		void getTileUVs(int _iTileIndex, Flip _eFlip, float& _fU1, float& _fV1, float& _fU2, float& _fV2);

		// Get pixel UV
		void getPixelUV(int _iTileIndex, Flip _eFlip, int _iX, int _iY, float& _fU1, float& _fV1, float& _fU2, float& _fV2);

		// Get tile size
		virtual int getTileSize() const {return m_iTileSize;}

		// Get tile offset
		virtual int getTileOffset(int _iIndex) const {return m_vecTiles[_iIndex].pOffset;}

		// Get VRAM size
		virtual int getVRAMWidth() const {return m_iVRAMWidth;}
		virtual int getVRAMHeight() const {return m_iVRAMHeight;}

	private:
		// Tile size
		TileSize						m_eTileSize;

		// Tile size
		int								m_iTileSize;

		// Pixel increment
		float							m_fPixelIncrement;

		// Texture index
		int								m_iTextureIndex[gsc_iMaxBGs];

		// Tiles
		tinystl::vector<TextureInfo>	m_vecTiles;

		// VRAM size
		int								m_iVRAMWidth;
		int								m_iVRAMHeight;

		// Create texture
		bool createTexture();

		// Create texture coordinates
		bool createTextureCoordinates();
};

ENDNAMESPACE
