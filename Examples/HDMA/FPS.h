// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

class FPS
{
	public:
		// Constructor
		FPS();

		// Destructor
		~FPS();

		// Add ticks
		void update(float _fElapsedTime);

	private:
		// Samples
		static const int msc_iMaxSamples	= 100;

		// Current tick
		int	m_iCurrentTick;

		// Tick sum
		float	m_fTickSum;

		// Tick list
		float	m_tickList[msc_iMaxSamples];
};

