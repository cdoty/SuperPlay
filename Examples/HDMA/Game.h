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
#include <Expansion/FontLoader.h>
#include <Expansion/HDMALoader.h>
#include <Expansion/MapLoader.h>
#include <TinySTL/stdint.h>

#include "FPS.h"

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
		// Font loader
		FontLoader*	m_pFontLoader;

		// HDMA loader
		HDMALoader*	m_pHDMALoader;

		// Map loader
		MapLoader*	m_pMapLoader;

		// FPS
		FPS			m_fps;

		// Enabled
		bool		m_bEnabled;

		// Scroll position
		float		m_fScrollX;

		// Scroll limit
		float		m_fScrollLimitX;

		// Update input
		void updateInput(float _fElapsedTime);
};
