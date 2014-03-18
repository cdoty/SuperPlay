// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

NAMESPACE(SPlay)

struct RenderParams
{
	// Position
	float	fX;
	float	fY;
	float	fZ;

	// Frame UVs
	float	fU1;
	float	fV1;
	float	fU2;
	float	fV2;

	// Frame size
	float	fWidth;
	float	fHeight;

	// Texture index
	int		iTextureIndex;
};

ENDNAMESPACE
