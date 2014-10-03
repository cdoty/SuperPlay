// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <OpenGLES/ES1/gl.h>
#else
#include <OpenGL/gl.h>
#endif
#elif defined __ANDROID__ || defined EMSCRIPTEN
#include <GLES/gl.h>
#elif defined MARMALADE
#include <IwGL.h>
#else
#include <GL/gl.h>
#endif

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
		bool create(int _iIndices, bool _bDynamic);

		// Close
		void close();

		// Get buffer
		virtual void* getBuffer(int& _iIndices) const;

		// Release buffer
		virtual void releaseBuffer();

		// Get index count
		virtual int getIndexCount() const {return m_iIndices;}

	private:
		// Index buffer
		GLushort*	m_pIndexBuffer;
		
		// Number of indices
		int			m_iIndices;

		// Dynamic
		bool		m_bDynamic;
};

ENDNAMESPACE
