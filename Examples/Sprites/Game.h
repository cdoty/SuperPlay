// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <IGame.h>
#include <Expansion/SpriteLoader.h>

using namespace	SPlay;

class Game : public IGame
{
	public:
		// Constructor
		Game();

		// Destructor
		virtual ~Game();

		// Static create function used to create the game class
		static Game* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		bool update(float _fElapsedTime);

	private:
		enum Direction
		{
			FacingUp = 0,
			FacingDown,
			FacingRight,
			FacingLeft
		};

		// Sprite loader
		SpriteLoader*	m_pSpriteLoader;

		// Current animation frame
		int				m_iCurrentFrame;

		// Current direction
		Direction		m_eCurrentDirection;

		// Frame delay
		float			m_fFrameDelay;

		// Sprite position
		float			m_fX;
		float			m_fY;

		// Update input
		void updateInput(float _fElapsedTime);

		// Load sprite graphics
		bool loadSpriteGraphics();

		// Setup sprite
		bool setupSprite();

		// Get animation frame
		int getAnimationFrame();
};
