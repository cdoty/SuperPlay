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
#include <TinySTL/string.h>

#include "Macros.h"

NAMESPACE(SPlay)

#ifdef log2
#undef log2
#endif

class Utilities
{
	public:
		// Log 2 function
		static double log2(double _fValue);

		// String hash
		static int getHash(const tinystl::string& _strString);

		// Convert int string to int
		static int convertStringToInt(const tinystl::string& _strString);
};

ENDNAMESPACE
