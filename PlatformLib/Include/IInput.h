// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/stdint.h>

#include "Macros.h"

NAMESPACE(SPlay)

class IInput
{
	public:
		// Destructor
		virtual ~IInput() {}

		// Update
		virtual bool update() = 0;

		// Device change
		virtual void deviceChange() = 0;

		// Get current input
		virtual uint32_t getCurrentInput() const = 0;
		
		// Get last input
		virtual uint32_t getLastInput() const = 0;
		
		// Get exit
		virtual bool getExit() const = 0;

		// Set exit
		virtual void setExit(bool _bExit) = 0;

		// Set 4 way
		virtual void set4Way(bool _b4Way) = 0;
};

ENDNAMESPACE
