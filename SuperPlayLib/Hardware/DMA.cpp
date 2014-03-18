// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdlib.h>
#include <string.h>
#include <TinySTL/stddef.h>

#include "AssertLog.h"
#include "DMA.h"
#include "Hardware.h"
#include "HardwareDefines.h"
#include "IDisplay.h"
#include "ITexture.h"
#include "System.h"

NAMESPACE(SPlay)

DMA::DMA()
{
}

DMA::~DMA()
{
	close();
}

DMA* DMA::create()
{
	DMA*	pDMA	= new DMA();

	if (false == pDMA->initialize())
	{
		delete	pDMA;

		pDMA	= NULL;
	}

	return	pDMA;
}

bool DMA::initialize()
{
	return	true;
}

void DMA::close()
{
}

bool DMA::update(int _iElapsedTime)
{
	return	true;
}

void DMA::setupDMATransfer(DMAType _eDMAType, uint32_t* _pSource, int _iStartTile, int _iWidth, int _iHeight, int _iBG)
{
	DMATransfer	dmaTransfer;

	dmaTransfer.pSource		= _pSource;
	dmaTransfer.iStartTile	= _iStartTile;
	dmaTransfer.iWidth		= _iWidth;
	dmaTransfer.iHeight		= _iHeight;
	dmaTransfer.iBG			= _iBG;

	m_vecDMATransfers[_eDMAType].push_back(dmaTransfer);
}

void DMA::setupDMATransfer(DMAType _eDMAType, uint32_t* _pSource, int _iStartTile, int _iTileCount, int _iBG)
{
	DMATransfer	dmaTransfer;

	dmaTransfer.pSource		= _pSource;
	dmaTransfer.iStartTile	= _iStartTile;
	dmaTransfer.iWidth		= _iTileCount;
	dmaTransfer.iHeight		= -1;
	dmaTransfer.iBG			= _iBG;

	m_vecDMATransfers[_eDMAType].push_back(dmaTransfer);
}

void DMA::clearVRAM()
{
	DMATransfer	dmaTransfer;

	BGVRAM*	pVRAM			= Hardware::getBGVRAM();

	int	iVRAMWidth			= pVRAM->getVRAMWidth();
	int	iVRAMHeight			= pVRAM->getVRAMHeight();

	dmaTransfer.pSource		= NULL;
	dmaTransfer.iStartTile	= 0;
	dmaTransfer.iWidth		= iVRAMWidth;
	dmaTransfer.iHeight		= iVRAMHeight;

	m_vecDMATransfers[BGDMA].push_back(dmaTransfer);
}

bool DMA::doOAMTransfer()
{
	int	t_c	= static_cast<int>(m_vecDMATransfers[OAMDMA].size());

	if (t_c > 0)
	{
		ITexture*	pTexture	= getTexture(OAMDMA, 0);

		if (NULL == pTexture)
		{
			return	false;
		}

		uint32_t*	pTextureData;
		int			iStride;

		if (false == pTexture->getBuffer(pTextureData, iStride))
		{
			return	false;
		}

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			const DMATransfer&	dmaTransfer	= m_vecDMATransfers[OAMDMA][iLoop];

			if (NULL == dmaTransfer.pSource)
			{
				continue;
			}

			else
			{
				if (-1 == dmaTransfer.iHeight)
				{
					doDMATransfer(dmaTransfer.pSource, pTextureData, iStride, dmaTransfer.iStartTile, dmaTransfer.iWidth, OAMDMA);
				}

				else
				{
					doDMATransfer(dmaTransfer.pSource, pTextureData, iStride, dmaTransfer.iStartTile, dmaTransfer.iWidth, dmaTransfer.iHeight, 
						OAMDMA);
				}
			}
		}

		pTexture->releaseBuffer();
	}

	m_vecDMATransfers[OAMDMA].clear();

	return	true;
}

bool DMA::doBGTransfer()
{
	int	t_c	= static_cast<int>(m_vecDMATransfers[BGDMA].size());

	int	iCurrentBG	= -1;

	if (t_c > 0)
	{
		qsort(&m_vecDMATransfers[BGDMA][0], m_vecDMATransfers[BGDMA].size(), sizeof(DMATransfer*), dmaSort);

		ITexture*	pTexture		= NULL;
		uint32_t*	pTextureData	= NULL;
		int			iStride;

		for (int iLoop = 0; iLoop < t_c; ++iLoop)
		{
			const DMATransfer&	dmaTransfer	= m_vecDMATransfers[BGDMA][iLoop];

			if (dmaTransfer.iBG != iCurrentBG)
			{
				iCurrentBG	= dmaTransfer.iBG;

				if (pTexture != NULL)
				{
					pTexture->releaseBuffer();
				}

				pTexture	= getTexture(BGDMA, dmaTransfer.iBG);

				if (NULL == pTexture)
				{
					return	false;
				}

				if (false == pTexture->getBuffer(pTextureData, iStride))
				{
					return	false;
				}
			}

			ASSERT_LOG(pTexture != NULL && pTextureData != NULL, "Texture wasn't set");

			if (NULL == dmaTransfer.pSource)
			{
				doVRAMClear(pTextureData, iStride, dmaTransfer.iStartTile, dmaTransfer.iWidth, dmaTransfer.iHeight, BGDMA);
			}

			else
			{
				if (-1 == dmaTransfer.iHeight)
				{
					doDMATransfer(dmaTransfer.pSource, pTextureData, iStride, dmaTransfer.iStartTile, dmaTransfer.iWidth, BGDMA);
				}

				else
				{
					doDMATransfer(dmaTransfer.pSource, pTextureData, iStride, dmaTransfer.iStartTile, dmaTransfer.iWidth, dmaTransfer.iHeight, 
						BGDMA);
				}
			}
		}

		if (pTexture != NULL)
		{
			pTexture->releaseBuffer();
		}
	}

	m_vecDMATransfers[BGDMA].clear();

	return	true;
}

int DMA::dmaSort(const void* _pTransfer1, const void* _pTransfer2)
{
	DMATransfer*	pTransfer1	= *(DMATransfer**)(_pTransfer1);
	DMATransfer*	pTransfer2	= *(DMATransfer**)(_pTransfer2);

	if (pTransfer1->iBG < pTransfer2->iBG)
	{
		return	-1;
	}
	
	else if (pTransfer1->iBG > pTransfer2->iBG)
	{
		return	1;
	}
	
	return	0;
}

void DMA::doDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStartTile, int _iWidth, int _iHeight, DMAType _eDMAType)
{
	uint32_t*	pSourcePtr	= _pSource;
	uint32_t*	pDestPtr	= _pDest;

	int	iIndex	= _iStartTile;

	int	iTileOffset;
	
	if (BGDMA == _eDMAType)
	{		
		iTileOffset	= Hardware::getBGVRAM()->getTileOffset(iIndex);
	}

	else
	{		
		iTileOffset	= Hardware::getObjVRAM()->getTileOffset(iIndex);
	}

	uint32_t*	pTile	= pDestPtr + iTileOffset;

	for (int iYLoop = 0; iYLoop < _iHeight; ++iYLoop)
	{
		memcpy(pTile, pSourcePtr, _iWidth * 4);

		pTile		+= _iStride;
		pSourcePtr	+= _iWidth;
	}
}

void DMA::doDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStartTile, int _iTileCount, DMAType _eDMAType)
{
	uint32_t*	pSourcePtr	= _pSource;
	uint32_t*	pDestPtr	= _pDest;

	int	iIndex	= _iStartTile;

	IVRAM*	pVRAM;
	
	if (BGDMA == _eDMAType)
	{		
		pVRAM	= Hardware::getBGVRAM();
	}

	else
	{
		pVRAM	= Hardware::getObjVRAM();
	}

	int	iTileSize	= pVRAM->getTileSize();

	for (int iLoop = 0; iLoop < _iTileCount; ++iLoop)
	{
		int	iTileOffset	= pVRAM->getTileOffset(iIndex);

		uint32_t*	pTile	= pDestPtr + iTileOffset;

		for (int iYLoop = 0; iYLoop < iTileSize; ++iYLoop)
		{
			memcpy(pTile, pSourcePtr, iTileSize * 4);

			pTile		+= _iStride;
			pSourcePtr	+= iTileSize;
		}

		iIndex++;
	}
}

void DMA::doVRAMClear(uint32_t* _pDest, int _iStride, int _iStartTile, int _iWidth, int _iHeight, DMAType _eDMAType)
{
	uint32_t*	pDestPtr	= _pDest;

	int	iIndex	= _iStartTile;

	int	iTileOffset	= Hardware::getBGVRAM()->getTileOffset(iIndex);

	uint32_t*	pTile	= pDestPtr + iTileOffset;

	for (int iYLoop = 0; iYLoop < _iHeight; ++iYLoop)
	{
		memset(pTile, 0, _iWidth * sizeof(uint32_t));
				
		pTile	+= _iStride;
	}
}

ITexture* DMA::getTexture(DMAType _eDMAType, int _iBG)
{
	int	iTextureIndex	= -1;

	switch (_eDMAType)
	{
		case BGDMA:
			iTextureIndex	= Hardware::getBGVRAM()->getTextureIndex(_iBG);

			break;

		case OAMDMA:
			iTextureIndex	= Hardware::getObjVRAM()->getTextureIndex();

			break;
	
		default:
			return	NULL;
	}

	return	System::getDisplay()->getTexture(iTextureIndex);
}

ENDNAMESPACE
