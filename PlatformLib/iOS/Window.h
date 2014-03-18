// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "Macros.h"

NAMESPACE(SPlay)

class Window
{
	public:
		// Constructor
		Window();

		// Destructor
		~Window();

		// Create
		static Window* create();
		
		// Initialize
		bool initialize();
		
		// Close
		void close();

	private:
		// Resize client area
		void resizeClientArea();
};

ENDNAMESPACE
