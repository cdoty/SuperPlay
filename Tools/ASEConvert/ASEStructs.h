// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#pragma pack(push, 1)
struct ASEHeader
{		  
	// File size
	uint32_t	uFileSize;

	// Magic number
	uint16_t	uMagicNumber;

	// Frames
	uint16_t	uFrames;

	// Width
	uint16_t	uWidth;

	// Height
	uint16_t	uHeight;

	// Color depth
	uint16_t	uColorDepth;

	// Flags
	uint32_t	uFlags;

	// Speed
	uint16_t	uSpeed;

	// Blank
	uint32_t	uBlank[2];

	// Transparent color index
	uint8_t		uTransparentIndex;

	// Pad
	uint8_t		uPad[3];

	// Colors
	uint16_t	uColors;

	// Reserved
	uint8_t		uReserved[94];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ASEFrameHeader
{
	// Frame size
	uint32_t	uFrameSize;

	// Magic number
	uint16_t	uMagicNumber;

	// Chunks	
	uint16_t	uChunks;

	// Frame duration (ms)
	uint16_t	uFrameDuration;

	// Reserved
	uint8_t		uReserved[6];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ASEChunk
{
	// Chunk size
	uint32_t	uChunkSize;

	// Chunk type
	uint16_t	uChunkType;

	// Chunk data
	uint8_t		pChunkData[1];
};
#pragma pack(pop)

enum ChunkType
{
	LayerChunk	= 0x2004,
	CelChunk	= 0x2005
};

#pragma pack(push, 1)
struct LayerChunkData
{
	// Flags
	uint16_t	uFlags;

	// Layer type
	uint16_t	uLayerType;

	// Layer child level
	uint16_t	uLayerChildLevel;

	// Layer width
	uint16_t	uLayerWidth;

	// Layer height
	uint16_t	uLayerHeight;

	// Layer blend mode
	uint16_t	uLayerBlendMode;

	// Reserved
	uint8_t		uReserved[4];

	// Layer name length
	uint16_t	uLayerNameLength;

	// Layer name
	uint8_t		pLayerName[1];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CelChunkData
{
	// Layer index
	uint16_t	uLayerIndex;

	// Position
	uint16_t	uX;
	uint16_t	uY;

	// Opacity
	uint8_t		uOpacity;

	// Cell type
	uint16_t	uCelType;

	// Reserved
	uint8_t		uReserved[7];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RawCel
{
	// Width
	uint16_t	uWidth;

	// Height
	uint16_t	uHeight;

	// Pixels
	uint8_t		uPixels[1];
};
#pragma pack(pop)
