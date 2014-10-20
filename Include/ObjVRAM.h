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

class ObjVRAM : public IVRAM
{
	public:
		// Constructor
		ObjVRAM();

		// Destructor
		virtual ~ObjVRAM();

		// Create the VRAM texture
		static ObjVRAM* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Get texture index
		int getTextureIndex() const {return m_iTextureIndex;}

		// Get Obj UVs
		void getObjUVs(int _iTileIndex, ObjSize _eObjSize, Flip _eFlip, float& _fU1, float& _fV1, float& _fU2, float& _fV2);

		// Get tile size
		virtual int getTileSize() const {return m_iTileSize;}

		// Get tile offset
		virtual int getTileOffset(int _iIndex) const {return m_vecTiles[_iIndex].pOffset;}

		// Get tile x
		virtual int getTileX(int _iIndex) const;

		// Get tile y
		virtual int getTileY(int _iIndex) const;

		// Get VRAM size
		virtual int getVRAMWidth() const {return m_iVRAMWidth;}
		virtual int getVRAMHeight() const {return m_iVRAMHeight;}

	private:
		// Tile size
		int								m_iTileSize;

		// UV increments
		float							m_fUIncrement[ObjSizes];
		float							m_fVIncrement[ObjSizes];

		// Texture index
		int								m_iTextureIndex;

		// Tiles
		tinystl::vector<TextureInfo>	m_vecTiles;

		// VRAM size
		int								m_iVRAMWidth;
		int								m_iVRAMHeight;

		// Create texture
		bool createTexture();

		// Setup UV increments
		void setupUVIncrements();

		// Create texture coordinates
		bool createTextureCoordinates();
};

ENDNAMESPACE
