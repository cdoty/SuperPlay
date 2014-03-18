// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "CustomVertex.h"
#include "Display.h"
#include "PlatformDefines.h"
#include "Utilities.h"
#include "VertexBuffer.h"

NAMESPACE(SPlay)

VertexBuffer::VertexBuffer()	:
	m_pVertexBuffer(NULL),
	m_iVertices(0),
	m_bDynamic(false)
{				   
}

VertexBuffer::~VertexBuffer()
{
	close();
}

bool VertexBuffer::create(LPDIRECT3DDEVICE9 _pD3DDevice, int _iVertices, bool _bDynamic)
{
	m_iVertices	= _iVertices;
	m_bDynamic	= _bDynamic;

	HRESULT	hResult	= _pD3DDevice->CreateVertexBuffer(m_iVertices * sizeof(CustomVertex), D3DUSAGE_WRITEONLY | (_bDynamic ? D3DUSAGE_DYNAMIC : 0),
		Display::VertexFormat, _bDynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateVertexBuffer error (%08X)", hResult);
		
		return	false;
	}

	void*	pVertices;

	hResult	= m_pVertexBuffer->Lock(0, m_iVertices * sizeof(CustomVertex), &pVertices, (true == m_bDynamic) ? D3DLOCK_DISCARD : 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Lock error (%08X)", hResult);
		
		return	false;
	}

	memset(pVertices, 0, m_iVertices * sizeof(CustomVertex));

	m_pVertexBuffer->Unlock();

	return	true;
}

void VertexBuffer::close()
{
	SAFE_RELEASE(m_pVertexBuffer);

	m_iVertices	= 0;
}

void* VertexBuffer::getBuffer(int& _iVertices) const
{
	void*	pBuffer;

	ASSERT_LOG(m_pVertexBuffer != NULL && m_iVertices > 0, "Vertex buffer is invalid or size is zero.\n");

	_iVertices	= m_iVertices;

	HRESULT	hResult	= m_pVertexBuffer->Lock(0, m_iVertices * sizeof(CustomVertex), &pBuffer, (true == m_bDynamic) ? D3DLOCK_DISCARD : 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Lock error (%08X)", hResult);
		
		return	NULL;
	}

	return	pBuffer;
}

void VertexBuffer::releaseBuffer()
{
	m_pVertexBuffer->Unlock();
}

ENDNAMESPACE
