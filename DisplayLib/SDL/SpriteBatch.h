// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "ISpriteBatch.h"
#include "Macros.h"
#include "RenderParams.h"

NAMESPACE(SPlay)

struct CustomVertex;
class VertexBuffer;

class SpriteBatch : public ISpriteBatch
{
	public:
		// Constructor
		SpriteBatch();

		// Destructor
		~SpriteBatch();

		// Create
		static SpriteBatch* create(int _iSprites = 64);

		// Initialize
		bool initialize(int _iSprites = 64);
		
		// Close
		void close();
		
		// Set texture
		void setTexture(int _iTextureIndex) {m_iTextureIndex = _iTextureIndex;}

		// Start batch
		virtual void startBatch(const Rect& _rctClip);
		virtual void startBatch();

		// Add sprite
		virtual void addSprite(const RenderParams& _renderParams);

		// End batch
		virtual void endBatch();

	protected:
		// Vertex buffer index
		int	m_iVertexBufferIndex;

		// Index buffer index
		int	m_iIndexBufferIndex;

		// Current texture index
		int	m_iTextureIndex;

		// Current sprite index
		int	m_iSpriteIndex;

		// Sprite batch maximum sprites
		int	m_iMaxSprites;

		// Temp vertex buffer pointer, used in between begin and end batch calls
		VertexBuffer*	m_pVertexBuffer;

		// Temp vertex buffer pointer
		CustomVertex*	m_pBuffer;

		// Draw batch
		void drawBatch();

		// Get vertex buffer
		void getVertexBuffer();

		// Release vertex buffer
		void releaseVertexBuffer();
};

ENDNAMESPACE
