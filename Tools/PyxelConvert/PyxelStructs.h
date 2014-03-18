// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

struct Animation
{
	// Name
	std::string	strName;

	// Base tile
	int	iBaseTile;

	// Frame duration
	int	iFrameDuration;

	// length
	int	iLength;
};

struct Tileset
{
	// Number of tiles
	int	iNumTiles;

	// Tiles wide
	int	iTilesWide;

	// Tile size
	int	iTileWidth;
	int	iTileHeight;

	// Image
	std::vector<uint8_t*>	vecImages;
};

struct TileRef
{
	// Index
	int		iIndex;

	// Flip X
	bool	bFlipX;

	// Rotation;
	int		iRotation;
};

struct Layer
{
	// Name
	std::string	strName;

	// Alpha
	int	iAlpha;

	// Hidden
	bool bHidden;

	//  Tile refs
	std::vector<TileRef>	vecTileRefs;
};

struct Canvas
{
	// Num layers
	int	iNumLayers;

	// Layers
	std::vector<Layer>	vecLayers;

	// Canvas size
	int	iWidth;
	int	iHeight;

	// Tile size
	int	iTileWidth;
	int	iTileHeight;
};
