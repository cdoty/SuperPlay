// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

struct NAnimFrame
{
	// Image name
	std::string	strImageName;

	// UVs
	float		fU1;
	float		fV1;
	float		fU2;
	float		fV2;
};

struct NAnimImage
{
	// Image name
	std::string	strImageName;

	// Size
	int			iWidth;
	int			iHeight;

	// Image
	uint32_t*	pImage;
};
