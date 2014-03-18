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

// D3DFVF_XYZRHW | D3DFVF_TEX1 
struct CustomVertex
{
	float	fX, fY, fZ, fW; 
	float	fU, fV;
	
	// Padded to 32 bytes, for efficiency.
	float	fPad1, fPad2;
};

ENDNAMESPACE