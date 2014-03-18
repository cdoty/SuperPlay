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
#elif defined __ANDROID__
#include <GLES/gl.h>
#elif defined MARMALADE
#include <IwGL.h>
#else
#include <GL/gl.h>
#endif

#include "CustomVertex.h"
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
		bool create(int _iVertices, bool _bDynamic = false);

		// Close
		void close();

		// Get buffer
		virtual void* getBuffer(int& _iVertices) const;

		// Release buffer
		virtual void releaseBuffer();

		// Get vertex count
		virtual int getVertexCount() const {return m_iVertices;}

	private:
		// Vertices
		CustomVertex*	m_pVertexBuffer;

		// Number of vertices
		int				m_iVertices;

		// Dynamic
		bool			m_bDynamic;
};

ENDNAMESPACE
