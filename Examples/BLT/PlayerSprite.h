// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "BaseSprite.h"

using namespace SPlay;

class PlayerSprite : public BaseSprite
{
	typedef	BaseSprite	super;

	public:
		// Constructor
		PlayerSprite(int _iTileIndex);

		// Destructor
		virtual ~PlayerSprite();

		// Create
		static PlayerSprite* create(int _iTileIndex);

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();
		
		// Update input
		void updateInput(float _fElapsedTime);

		// Set level
		void setLevel(int _iLevel);
		
		// Reset
		void reset();

	private:
		// Current 'upgrade' level
		int		m_iLevel;

		// Position limits
		float	m_fLeftLimit;
		float	m_fTopLimit;
		float	m_fRightLimit;
		float	m_fBottomLimit;

		// Button cool down
		float	m_fButtonCooldown;
};
