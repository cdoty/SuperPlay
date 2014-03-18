// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "CustomVertex.h"
#include "Display.h"
#include "SpriteBatch.h"
#include "System.h"

NAMESPACE(SPlay)

ISpriteBatch* createSpriteBatch(int _iSprites)
{
	return	SpriteBatch::create(_iSprites);
}

SpriteBatch::SpriteBatch()	:
	m_iVertexBufferIndex(-1),
	m_iIndexBufferIndex(-1),
	m_iTextureIndex(-1),
	m_iSpriteIndex(0),
	m_iMaxSprites(0),
	m_pVertexBuffer(NULL),
	m_pBuffer(NULL)
{
}

SpriteBatch::~SpriteBatch()
{
	close();
}

SpriteBatch* SpriteBatch::create(int _iSprites)
{
	SpriteBatch*	pSpriteBatch	= new SpriteBatch();

	if (false == pSpriteBatch->initialize(_iSprites))
	{
		delete	pSpriteBatch;

		pSpriteBatch	= NULL;
	}

	return	pSpriteBatch;
}

bool SpriteBatch::initialize(int _iSize)
{
	m_iMaxSprites	= _iSize;
	
	Display* pDisplay	= static_cast<Display*>(System::getDisplay());

	// Create vertex buffer
	m_iVertexBufferIndex	= pDisplay->createVertexBuffer(_iSize * 4, true);
	
	// Create index buffer
	m_iIndexBufferIndex		= pDisplay->createIndexBuffer(_iSize * 6, false);

	IndexBuffer*	pIndexBuffer	= static_cast<IndexBuffer*>(pDisplay->getIndexBuffer(m_iIndexBufferIndex));

	int	iIndices;
	
	short*	pBuffer	= static_cast<short*>(pIndexBuffer->getBuffer(iIndices));

	if (NULL == pBuffer)
	{
		return	false;
	}

	// Pre assign indices
	for (int iLoop = 0; iLoop < _iSize; ++iLoop)
	{
		int	iIndex	= iLoop * 4;
		
		int	iBufferIndex	= iLoop * 6;
		
		pBuffer[iBufferIndex++]	= iIndex;
		pBuffer[iBufferIndex++]	= iIndex + 1;
		pBuffer[iBufferIndex++]	= iIndex + 2;
		pBuffer[iBufferIndex++]	= iIndex + 1;
		pBuffer[iBufferIndex++]	= iIndex + 3;
		pBuffer[iBufferIndex++]	= iIndex + 2;
	}

	pIndexBuffer->releaseBuffer();
	
	return	true;
}

void SpriteBatch::close()
{
	Display* pDisplay	= static_cast<Display*>(System::getDisplay());

	if (m_iVertexBufferIndex != -1)
	{
		pDisplay->removeVertexBuffer(m_iVertexBufferIndex);

		m_iVertexBufferIndex	= -1;
	}

	if (m_iIndexBufferIndex != -1)
	{
		pDisplay->removeIndexBuffer(m_iIndexBufferIndex);

		m_iIndexBufferIndex	= -1;
	}
}

void SpriteBatch::startBatch(const Rect& _rctClip)
{
	if (_rctClip.iWidth > 0 && _rctClip.iHeight > 0)
	{
		System::getDisplay()->setClipRect(_rctClip);
	}

	startBatch();
}

void SpriteBatch::startBatch()
{
	m_iTextureIndex	= -1;
	m_iSpriteIndex	= 0;
}

void SpriteBatch::addSprite(const RenderParams& _renderParams)
{
	// If changing texture, draw sprite batch
	if (m_iTextureIndex != _renderParams.iTextureIndex)
	{
		m_iTextureIndex	= _renderParams.iTextureIndex;

		System::getDisplay()->bindTexture(m_iTextureIndex);

		// Draw all sprite batches associated with the existing texture
		drawBatch();

		getVertexBuffer();
	}
	
	int	iIndex	= m_iSpriteIndex << 2;

	float	fX1	= _renderParams.fX;
	float	fY1	= _renderParams.fY;
	float	fX2	= fX1 + _renderParams.fWidth;
	float	fY2	= fY1 + _renderParams.fHeight;

	CustomVertex*	pBuffer	= &m_pBuffer[iIndex];

	// (0)*--*(2)
	//    | /|
	// (1)*--*(3)
	pBuffer->fX	= fX1;
	pBuffer->fY	= fY1;

	pBuffer->fU	= _renderParams.fU1;
	pBuffer->fV	= _renderParams.fV1;
	
	pBuffer++;

	pBuffer->fX	= fX1;
	pBuffer->fY	= fY2;

	pBuffer->fU	= _renderParams.fU1;
	pBuffer->fV	= _renderParams.fV2;
	
	pBuffer++;

	pBuffer->fX	= fX2;
	pBuffer->fY	= fY1;

	pBuffer->fU	= _renderParams.fU2;
	pBuffer->fV	= _renderParams.fV1;
	
	pBuffer++;

	pBuffer->fX	= fX2;
	pBuffer->fY	= fY2;

	pBuffer->fU	= _renderParams.fU2;
	pBuffer->fV	= _renderParams.fV2;
	
	m_iSpriteIndex++;

	if (m_iSpriteIndex >= m_iMaxSprites)
	{
		drawBatch();

		getVertexBuffer();
	}
}

void SpriteBatch::endBatch()
{
	// Draw any remaining sprite batches.
	drawBatch();

	System::getDisplay()->resetClipRect();
}

void SpriteBatch::drawBatch()
{
	releaseVertexBuffer();

	if (m_iSpriteIndex > 0)
	{
		// Draw the sprite batches
		System::getDisplay()->drawTriangles(m_iVertexBufferIndex, m_iSpriteIndex * 4, m_iIndexBufferIndex, m_iSpriteIndex * 2);
		
		m_iSpriteIndex	= 0;
	}
}

void SpriteBatch::getVertexBuffer()
{
	Display* pDisplay	= static_cast<Display*>(System::getDisplay());

	m_pVertexBuffer	= pDisplay->getVertexBuffer(m_iVertexBufferIndex);

	int	iVertices;
	
	m_pBuffer	= static_cast<CustomVertex*>(m_pVertexBuffer->getBuffer(iVertices));
}

void SpriteBatch::releaseVertexBuffer()
{
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->releaseBuffer();

		m_pVertexBuffer	= NULL;
		m_pBuffer		= NULL;
	}
}

ENDNAMESPACE
