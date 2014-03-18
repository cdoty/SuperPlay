// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>
#include <Expansion/SpriteLoader.h>

#include "Point.h"
#include "Rect.h"

using namespace SPlay;

class BaseSprite
{
	public:
		// Constructor
		BaseSprite(int _iTileIndex);

		// Destructor
		virtual ~BaseSprite();

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();

		// Set position
		void setPosition(float _fX, float _fY);

		// Set active
		void setActive(bool _bActive);

		// Set frame
		void setFrame(int _iFrame);

		// Get frame count
		int getFrameCount();

		// Set sort order
		void setSortOrder(int _iSortOrder);

		// Get collision rect
		Rect getCollisionRect() const;

		// Load 
		bool load(const tinystl::string& _strSpriteName);

		// Add sprite to OAM
		bool addSpriteToOAM();

	protected:
		// Sprite loader
		SpriteLoader*	m_pSpriteLoader;

		// Position
		float			m_fX;
		float			m_fY;

		// Sprite index
		int				m_iSpriteIndex;

		// Tile index
		int				m_iTileIndex;

		// Frame size
		int				m_iFrameWidth;
		int				m_iFrameHeight;
};
