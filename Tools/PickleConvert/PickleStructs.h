// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

struct FileInfo
{
	// Background color
	uint32_t	uBackgroundColor;

	// Frame size
	int			iFrameWidth;
	int			iFrameHeight;

	// Image size
	int			iImageWidth;
	int			iImageHeight;

	// Number of frames on the tilesheet
	int			iHorizFrames;

	// Number of frames
	int			iNumFrames;

	// Frame rate
	int			iFrameRate;
};

struct Tileset
{
	// Tile size
	int	iTileWidth;
	int	iTileHeight;

	// Image
	std::vector<uint32_t*>	vecImages;
};
