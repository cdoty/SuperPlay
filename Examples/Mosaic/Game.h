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
#include <Expansion/MapLoader.h>

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

		// Map loader
		MapLoader*	m_pMapLoader;

		// Current mosaic
		int			m_iMosaic;

		// Target mosaic
		int			m_iTargetMosaic;

		// Mosaic delay
		float		m_fMosaicDelay;

		// Mosaic in progress?
		bool		m_bMosaicInProgress;

		// Scroll position
		float		m_fScrollX;
		float		m_fScrollY;

		// Scroll limit
		float		m_fScrollLimitX;
		float		m_fScrollLimitY;

		// Update input
		void updateInput(float _fElapsedTime);

		// Update mosaic
		void updateMosaic(float _fElapsedTime);
};
