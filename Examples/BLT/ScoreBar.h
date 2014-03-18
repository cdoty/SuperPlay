// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <Expansion/FontLoader.h>

using namespace SPlay;

class ScoreBar
{
	public:
		// Constructor
		ScoreBar();

		// Destructor
		~ScoreBar();

		// Create
		static ScoreBar* create(const tinystl::string& _strFontName);

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const tinystl::string& _strFontName);

		// Set score
		void setScore(int _iScore);

		// Set lives
		void setLives(int _iCount);

		// Pause
		void setPause(bool _bPause);

		// Game over
		void setGameOver(bool _bGameOver);

	private:
		// Font loader
		FontLoader*		m_pFontLoader;
};
