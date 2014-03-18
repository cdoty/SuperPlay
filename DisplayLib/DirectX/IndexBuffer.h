// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <d3d9.h>

#include "IIndexBuffer.h"
#include "Macros.h"

NAMESPACE(SPlay)

class IndexBuffer : public IIndexBuffer
{
	public:
		// Constructor
		IndexBuffer();

		// Destructor
		~IndexBuffer();

		// Create
		bool create(LPDIRECT3DDEVICE9 _pD3DDevice, int _iIndices, bool _bDynamic);

		// Close
		void close();

		// Get buffer
		virtual void* getBuffer(int& _iIndices) const;

		// Release buffer
		virtual void releaseBuffer();

		// Get index buffer
		LPDIRECT3DINDEXBUFFER9 getIndexBuffer() const {return m_pIndexBuffer;}

		// Get index count
		virtual int getIndexCount() const {return m_iIndices;}

	private:
		// Index buffer
		LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;

		// Number of indices
		int		m_iIndices;

		// Dynamic
		bool	m_bDynamic;
};

ENDNAMESPACE
