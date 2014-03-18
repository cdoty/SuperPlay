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

#include "AssertLog.h"
#include "HDMA.h"
#include "GameHeader.h"
#include "IDisplay.h"
#include "ISpriteBatch.h"
#include "System.h"

NAMESPACE(SPlay)

HDMA::HDMA()	:
	m_pSpriteBatch(NULL),
	m_iTextureIndex(-1),
	m_bEnabled(false)
{
}

HDMA::~HDMA()
{
	close();
}

HDMA* HDMA::create()
{
	HDMA*	pHDMA	= new HDMA();

	if (false == pHDMA->initialize())
	{
		delete	pHDMA;

		pHDMA	= NULL;
	}

	return	pHDMA;
}

bool HDMA::initialize()
{
	const GameHeader& gameHeader	= System::getGameHeader();

	int	iWidth	= gameHeader.iScreenWidth;
	int	iHeight	= gameHeader.iScreenHeight;
	
	IDisplay*	pDisplay	= System::getDisplay();

	m_iTextureIndex	= pDisplay->createTexture("HDMATexture", 1, iHeight, NoAlpha, false);

	if (-1 == m_iTextureIndex)
	{
		Log::instance()->logError("Unable to create HDMA texture");

		return	false;
	}

	ITexture*	pTexture	= pDisplay->getTexture(m_iTextureIndex);

	m_fScreenWidth		= static_cast<float>(iWidth);
	m_fTextureIncrement	= 1.0f / static_cast<float>(pTexture->getTextureHeight());

	uint32_t*	pBuffer;
	int			iStride;

	if (false == pTexture->getBuffer(pBuffer, iStride))
	{
		return	false;
	}

	// Clear HDMA texture
	for (int iLoop = 0; iLoop < iHeight; ++iLoop)
	{
		*pBuffer	= 0;

		pBuffer++;
	}

	pTexture->releaseBuffer();

	m_iScreenHeight	= iHeight;

	if (false == setupSpriteBatch())
	{
		return	false;
	}

	setBackgroundColor(0);

	return	true;
}
	
void HDMA::close()
{
	if (m_iTextureIndex != -1)
	{
		IDisplay*	pDisplay	= System::getDisplay();

		pDisplay->removeTexture(m_iTextureIndex);

		m_iTextureIndex	= -1;
	}

	delete	m_pSpriteBatch;

	m_pSpriteBatch	= NULL;
}

void HDMA::render()
{
	if (true == m_bEnabled)
	{
		m_pSpriteBatch->startBatch();

		RenderParams	renderParams;

		renderParams.fU1			= 0.0f;
		renderParams.fU2			= 1.0f;
		renderParams.fV1			= 0.0f;
		renderParams.fV2			= m_fTextureIncrement;
		renderParams.fWidth			= m_fScreenWidth;
		renderParams.fHeight		= 1.0f;
		renderParams.fX				= 0.0f;
		renderParams.fY				= 0.0f;
		renderParams.iTextureIndex	= m_iTextureIndex;

		for (int iLoop = 0; iLoop < m_iScreenHeight; ++iLoop)
		{
			m_pSpriteBatch->addSprite(renderParams);

			renderParams.fV1	+= m_fTextureIncrement;
			renderParams.fV2	+= m_fTextureIncrement;
			renderParams.fY		+= 1.0f;
		}

		m_pSpriteBatch->endBatch();
	}

	else
	{
		System::getDisplay()->clear(m_uBackgroundColor);
	}
}

void HDMA::setBackgroundColor(uint32_t _uColor)
{
	m_uBackgroundColor	= _uColor;
}

void HDMA::setupHDMATransfer(uint32_t* _pSource, int _iStart, int _iCount)
{
	HDMATransfer	hdmaTransfer;

	hdmaTransfer.pSource	= _pSource;
	hdmaTransfer.iStart		= _iStart;
	hdmaTransfer.iCount		= _iCount;

	m_vecHDMATransfers.push_back(hdmaTransfer);
}

void HDMA::startHDMATransfer()
{
	int	t_c	= static_cast<int>(m_vecHDMATransfers.size());

	if (t_c > 0)
	{
		uint32_t*	pTextureData;
		int			iStride;

		ITexture*	pTexture	= System::getDisplay()->getTexture(m_iTextureIndex);

		if (true == pTexture->getBuffer(pTextureData, iStride))
		{
			for (int iLoop = 0; iLoop < t_c; ++iLoop)
			{
				const HDMATransfer&	hdmaTransfer	= m_vecHDMATransfers[iLoop];

				doHDMATransfer(hdmaTransfer.pSource, pTextureData, iStride, hdmaTransfer.iStart, hdmaTransfer.iCount);
			}
		}

		pTexture->releaseBuffer();

		m_vecHDMATransfers.clear();
	}
}

void HDMA::doHDMATransfer(uint32_t* _pSource, uint32_t* _pDest, int _iStride, int _iStart, int _iCount)
{
	int	t_c	= _iCount;

	if (t_c + _iStart > m_iScreenHeight)
	{
		t_c	-= (t_c + _iStart - m_iScreenHeight);
	}

	uint32_t*	pSrcPointer		= _pSource;
	uint32_t*	pDestPointer	= _pDest + _iStart;

	memcpy(pDestPointer, pSrcPointer, t_c * sizeof(uint32_t));
}

bool HDMA::setupSpriteBatch()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	m_pSpriteBatch	= createSpriteBatch(gameHeader.iScreenHeight);

	if (NULL == m_pSpriteBatch)
	{
		return	false;
	}

	return	true;
}

ENDNAMESPACE
