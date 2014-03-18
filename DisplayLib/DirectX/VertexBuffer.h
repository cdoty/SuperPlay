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

#include "IVertexBuffer.h"
#include "Macros.h"

NAMESPACE(SPlay)

class VertexBuffer : public IVertexBuffer
{
	public:
		// Constructor
		VertexBuffer();

		// Destructor
		~VertexBuffer();

		// Create
		bool create(LPDIRECT3DDEVICE9 _pD3DDevice, int _iVertices, bool _bDynamic = false);

		// Close
		void close();

		// Get buffer
		virtual void* getBuffer(int& _iVertices) const;

		// Release buffer
		virtual void releaseBuffer();

		// Get vertex buffer
		LPDIRECT3DVERTEXBUFFER9 getVertexBuffer() const {return m_pVertexBuffer;}

		// Get vertex count
		virtual int getVertexCount() const {return m_iVertices;}

	private:
		// Vertex buffer
		LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;

		// Number of vertices
		int		m_iVertices;

		// Dynamic
		bool	m_bDynamic;
};

ENDNAMESPACE
