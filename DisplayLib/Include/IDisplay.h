// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/stdint.h>

#include "IIndexBuffer.h"
#include "ITexture.h"
#include "IVertexBuffer.h"
#include "Macros.h"
#include "Rect.h"

NAMESPACE(SPlay)

class IDisplay
{
	public:
		// Destructor
		virtual ~IDisplay() {}

		// Initialize
		virtual bool initialize() = 0;
	
		// Close
		virtual void close() = 0;
	
		// Render
		virtual bool render() = 0;

		// Clear
		virtual void clear(uint32_t _uColor) = 0;

		// Resize
		virtual void resize() = 0;

		// Create vertex buffer
		virtual int createVertexBuffer(int _iVertices, bool _bDynamic) = 0;

		// Get vertex buffer
		virtual IVertexBuffer* getVertexBuffer(int _iIndex) const = 0;

		// Remove vertex buffer
		virtual void removeVertexBuffer(int _iIndex) = 0;

		// Create index buffer
		virtual int createIndexBuffer(int _iVertices, bool _bDynamic) = 0;

		// Get index buffer
		virtual IIndexBuffer* getIndexBuffer(int _iIndex) const = 0;

		// Remove index buffer
		virtual void removeIndexBuffer(int _iIndex) = 0;

		// Create texture
		virtual int createTexture(const char* _szTextureName, int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic) = 0;
		
		// Get texture
		virtual ITexture* getTexture(int _iHash) = 0;

		// Remove texture
		virtual void removeTexture(int _iHash) = 0;

		// Bind texture
		virtual void bindTexture(int _iHash) = 0;

		// Draw triangles
		virtual bool drawTriangles(int _iVertexBufferIndex, int _iVertices = 0, int _iIndexBufferIndex = -1, int _iTriangles = 0) = 0;

		// Set clip rect
		virtual void setClipRect(const Rect& _rctClip) = 0;

		// Reset clip rect
		virtual void resetClipRect() = 0;
};

// Create display
extern IDisplay* createDisplay();

ENDNAMESPACE
