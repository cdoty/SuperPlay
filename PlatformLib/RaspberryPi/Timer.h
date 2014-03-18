// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <stdint.h>

#include "Macros.h"

NAMESPACE(SPlay)

class Timer
{
	public:
		// Constructor
		Timer();

		// Destructor
		~Timer();

		// Create
		static Timer* create();
				
		// Initialize
		bool initialize();

		// Close
		void close();

		// Start
		void start();

		// Get elapsed time
		int getElapsed();
		
		// Get elapsed time
		float getElapsedFloat();
		
	protected:
		// Current time
		int64_t	m_iCurrentTime;
};

ENDNAMESPACE