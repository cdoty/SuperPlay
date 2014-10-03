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

bool IndexBuffer::create(int _iIndices, bool _bDynamic)
{
	m_iIndices	= _iIndices;
	m_bDynamic	= _bDynamic;

	m_pIndexBuffer	= new GLushort[m_iIndices];

	return	true;
}

void IndexBuffer::close()
{
	delete[]	m_pIndexBuffer;

	m_pIndexBuffer	= NULL;

	m_iIndices	= 0;
}

void* IndexBuffer::getBuffer(int& _iIndices) const
{
	_iIndices	= m_iIndices;

	return	m_pIndexBuffer;
}

void IndexBuffer::releaseBuffer()
{
}

ENDNAMESPACE
