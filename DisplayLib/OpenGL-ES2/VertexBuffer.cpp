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

bool VertexBuffer::create(int _iVertices, bool _bDynamic)
{
	m_iVertices	= _iVertices;
	m_bDynamic	= _bDynamic;

	m_pVertexBuffer	= new CustomVertex[m_iVertices];
	
	return	true;
}

void VertexBuffer::close()
{
	delete[]	m_pVertexBuffer;

	m_pVertexBuffer	= NULL;

	m_iVertices	= 0;
}

void* VertexBuffer::getBuffer(int& _iVertices) const
{
	_iVertices	= m_iVertices;
		
	return	m_pVertexBuffer;
}

void VertexBuffer::releaseBuffer()
{
}

ENDNAMESPACE
