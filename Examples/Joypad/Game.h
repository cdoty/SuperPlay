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
#include <Point.h>
#include <Expansion/FontLoader.h>
#include <Expansion/MapLoader.h>
#include <Expansion/SpriteLoader.h>
#include <TinySTL/vector.h>

using namespace	SPlay;

class Game : public IGame
{
	public:
		// Number of buttons to configure
		static const int	msc_iButtons	= 12;

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
		// Font loader
		FontLoader*		m_pFontLoader;

		// Map loader
		MapLoader*		m_pMapLoader;

		// Sprite loader
		SpriteLoader*	m_pSpriteLoader;

		// Button positions
		tinystl::vector<Point>	m_vecButtonPositions;

		// Update input
		void updateInput(float _fElapsedTime);

		// Load font
		bool loadFont();

		// Load map
		bool loadMap();

		// Load sprite
		bool loadSprite();

		// Setup sprite
		bool setupSprite();

		// Set button positions
		void setButtonPositions();
};
