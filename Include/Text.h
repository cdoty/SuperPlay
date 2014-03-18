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
#include "Macros.h"

NAMESPACE(SPlay)

class ISpriteBatch;

class Text
{
	public:
		// Constructor
		Text();

		// Destructor
		~Text();

		// Create the Text layer
		static Text* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Render
		void render();

		// Set active
		void setActive(bool _bActive) {m_bActive = _bActive;}

		// Set font data
		void setFontData(uint8_t* _pImageBuffer, uint8_t* _pPaletteBuffer, int _iCharacterCount);

		// Clear
		bool clear(int _iX = 0, int _iY = 0, int _iWidth = -1, int _iHeight = -1);

		// Update
		bool update(int _iX, int _iY, int _iWidth, int _iHeight, const uint8_t* _pMap, int _iMapStride);

		// Draw text
		bool drawText(int _iX, int _iY, const char* _szString);

	private:
		// Font image
		uint8_t*	m_pImageBuffer;
			
		// Paletted?
		uint32_t*	m_pPaletteBuffer;

		// Character count
		int			m_iCharacterCount;

		// VRAM size
		int			m_iVRAMWidth;
		int			m_iVRAMHeight;

		// Screen size
		int			m_iScreenWidth;
		int			m_iScreenHeight;

		// Width and height in characters
		int			m_iCharWidth;
		int			m_iCharHeight;

		// Texture UV
		float		m_fU2;
		float		m_fV2;
		
		// Sprite batch
		ISpriteBatch*	m_pSpriteBatch;

		// Texture index
		int			m_iTextureIndex;

		// Active?
		bool		m_bActive;

		// Create texture
		bool createTexture();

		// Setup sprite batch
		bool setupSpriteBatch();

		// Draw character
		void drawCharacter(int _iIndex, uint32_t* _pVRAM);

		// Clear character
		void clearCharacter(uint32_t* _pVRAM);

		// Clear VRAM
		bool clearVRAM(int _iX, int _iY, int _iWidth, int _iHeight, uint32_t*& _pBuffer);

		// Draw grid
		bool drawGrid();
};

ENDNAMESPACE
