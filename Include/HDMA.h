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

#include "Macros.h"
#include "RenderParams.h"

NAMESPACE(SPlay)

class ISpriteBatch;

class HDMA
{
	public:
		// Constructor
		HDMA();

		// Destructor
		~HDMA();

		// Create HDMA
		static HDMA* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Render
		void render();

		// Set background color
		void setBackgroundColor(uint32_t _uColor);

		// Setup HDMA transfer
		void setupHDMATransfer(uint32_t* _pSource, int _iStart, int _iCount);
	
		// Start HDMA transfer
		void startHDMATransfer();

		// Set enable
		void setEnable(bool _bEnabled) {m_bEnabled = _bEnabled;}

	protected:
		struct HDMATransfer
		{
			uint32_t*	pSource;
			int			iStart;
			int			iCount;
		};

		// Sprite batch
		ISpriteBatch*	m_pSpriteBatch;
		
		// Texture index
		int				m_iTextureIndex;

		// Texture increment
		float			m_fTextureIncrement;

		// Screen width
		float			m_fScreenWidth;

		// Screen height
		int				m_iScreenHeight;

		// Enabled
		bool			m_bEnabled;

		// Background color
		uint32_t		m_uBackgroundColor;

		// DMA transfers
		tinystl::vector<HDMATransfer>	m_vecHDMATransfers;

		// Do HDMA transfer
		void doHDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStart, int _iCount);

		// Setup sprite batch
		bool setupSpriteBatch();
};

ENDNAMESPACE
