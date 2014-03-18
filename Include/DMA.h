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

NAMESPACE(SPlay)

enum DMAType
{
	BGDMA	= 0,
	OAMDMA,

	DMATypes
};

class ITexture;

class DMA
{
	public:
		struct DMATransfer
		{
			uint32_t*	pSource;
			int			iStartTile;
			int			iWidth;
			int			iHeight;
			int			iBG;
		};

		// Constructor
		DMA();

		// Destructor
		~DMA();

		// Create
		static DMA* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		bool update(int _iElapsedTime);
	
		// Setup DMA transfer
		void setupDMATransfer(DMAType _eDMAType, uint32_t* _pSource, int _iStartTile, int _iWidth, int _iHeight, int _iBG);
		void setupDMATransfer(DMAType _eDMAType, uint32_t* _pSource, int _iStartTile, int _iTileCount, int _iBG);
	
		// clear VRAM
		void clearVRAM();

		// Do OAM transfer
		bool doOAMTransfer();

		// Do BG transfer
		bool doBGTransfer();

		// DMA sort
		static int dmaSort(const void* _pTransfer1, const void* _pTransfer2);

	private:
		// DMA transfers
		tinystl::vector<DMATransfer>	m_vecDMATransfers[DMATypes];

		// Do DMA transfer
		void doDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStartTile, int _iWidth, int _iHeight, 
			DMAType _eDMAType);

		// Do DMA transfer
		void doDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStartTile, int _iTileCount, DMAType _eDMAType);

		// Do VRAM Clear
		void doVRAMClear(uint32_t* _pDest, int _iStride, int _iStartTile, int _iWidth, int _iHeight, DMAType _eDMAType);

		// Get texture
		ITexture* getTexture(DMAType _eDMAType, int _iBG);
};

ENDNAMESPACE
