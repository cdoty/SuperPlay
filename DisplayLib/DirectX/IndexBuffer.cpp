// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "Display.h"
#include "IndexBuffer.h"
#include "PlatformDefines.h"
#include "Utilities.h"

NAMESPACE(SPlay)

IndexBuffer::IndexBuffer()	:
	m_pIndexBuffer(NULL),
	m_iIndices(0),
	m_bDynamic(false)
{
}

IndexBuffer::~IndexBuffer()
{
	close();
}

bool IndexBuffer::create(LPDIRECT3DDEVICE9 _pD3DDevice, int _iIndices, bool _bDynamic)
{
	m_iIndices	= _iIndices;
	m_bDynamic	= _bDynamic;

	HRESULT	hResult	= _pD3DDevice->CreateIndexBuffer(m_iIndices * sizeof(short), D3DUSAGE_WRITEONLY | (_bDynamic ? D3DUSAGE_DYNAMIC : 0), 
		D3DFMT_INDEX16, _bDynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);

	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateIndexBuffer error (%08X)", hResult);

		return	false;
	}

	void*	pIndices;

	hResult	= m_pIndexBuffer->Lock(0, m_iIndices * sizeof(short), &pIndices, (true == m_bDynamic) ? D3DLOCK_DISCARD : 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Lock error (%08X)", hResult);

		return	false;
	}

	memset(pIndices, 0, m_iIndices * sizeof(short));

	m_pIndexBuffer->Unlock();

	return	true;
}

void IndexBuffer::close()
{
	SAFE_RELEASE(m_pIndexBuffer);

	m_iIndices	= 0;
}

void* IndexBuffer::getBuffer(int& _iIndices) const
{
	void*	pBuffer;

	ASSERT_LOG(m_pIndexBuffer != NULL && m_iIndices > 0, "Index buffer is invalid or size is zero.\n");

	_iIndices	= m_iIndices;

	HRESULT	hResult	= m_pIndexBuffer->Lock(0, m_iIndices * sizeof(short), &pBuffer, (true == m_bDynamic) ? D3DLOCK_DISCARD : 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Lock error (%08X)", hResult);

		return	NULL;
	}

	return	pBuffer;
}

void IndexBuffer::releaseBuffer()
{
	m_pIndexBuffer->Unlock();
}

ENDNAMESPACE
