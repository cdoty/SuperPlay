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

// Target frame rate
static const int	gsc_iFrameRate		= 30;
static const float	gsc_fFramePeriod	= (1.0f / gsc_iFrameRate);

// Maximum layers
static const int	gsc_iMaxBGs			= 4;

// Maximum sprites
static const int	gsc_iMaxObjs		= 128;

// Min/Max obj size
static const int	gsc_iMinObjSize		= 16;
static const int	gsc_iMaxObjSize		= 64;

// Maximum tiles per background
static const int	gsc_iMaxTiles		= 1024;

// Min/Max tile size
static const int	gsc_iMinTileSize	= 16;
static const int	gsc_iMaxTileSize	= 32;

// Font size
static const int	gsc_iFontSize		= 8;

// Starting character of the font
static const int	gsc_iFontStart		= 33;

// Generate a color value from red green and blue values.
#define	COLOR(Red, Green, Blue) ((uint32_t)((0xFF << 24) | (Red << 16) | (Green << 8) | (Blue)))

// Tile sizes
enum TileSize
{
	// 8 x 8tiles
	TileSize8x8	= 0,

	// 16 x 16 tiles
	TileSize16x16,

	// 32 x 32 tiles
	TileSize32x32,

	// Tile sizes
	TileSizes
};

// Sprite sizes
enum ObjSize
{
	// 16 x 16 sprite
	ObjSize16x16	= 0,

	// 16 x 32 sprite
	ObjSize16x32,

	// 32 x 16 sprite
	ObjSize32x16,

	// 32 x 32 sprite
	ObjSize32x32,

	// 32 x 64 sprite
	ObjSize32x64,

	// 64 x 32 sprite
	ObjSize64x32,

	// 64 x 64 sprite
	ObjSize64x64,

	// Sprite sizes
	ObjSizes
};

enum Flip
{
	NoFlip	= 0,
	HFlip	= 0x01,
	VFlip	= 0x02,
	HVFlip	= HFlip | VFlip
};

struct TileInfo
{
	// Tile index
	int		iTileIndex;

	// Flip
	Flip	eFlip;
};

// Maximum path length. This is a safe value on all systems.
static const int	gsc_iMaxPathLength	= 128;

ENDNAMESPACE
