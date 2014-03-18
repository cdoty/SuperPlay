// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <Expansion/MapLoader.h>

using namespace SPlay;

class Background
{
	public:
		// Constructor
		Background(int _iBG);

		// Destructor
		~Background();

		// Create
		static Background* create(int _iBG, const tinystl::string& _strMapName);

		// Initialize
		bool initialize();

		// Close
		void close();

		// Update
		void update(float _fElapsedTime);

		// Load
		bool load(const tinystl::string& _strMapName);

		// Set scroll position
		void setScrollPosition(int _iX, int _iY);

	private:
		// Map loader
		MapLoader*		m_pMapLoader;

		// BG number
		int				m_iBG;

		// Scroll position
		float			m_fScrollY;

		// Scroll height
		float			m_fScrollHeight;
};
