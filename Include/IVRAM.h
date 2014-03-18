// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

class IVRAM
{
	public:
		// Destructor
		~IVRAM() {}

		// Get tile size
		virtual int getTileSize() const = 0;

		// Get tile offset
		virtual int getTileOffset(int _iIndex) const = 0;

		// Get VRAM size
		virtual int getVRAMWidth() const = 0;
		virtual int getVRAMHeight() const = 0;

	protected:
		struct TextureInfo
		{
			// UVs
			float		fU1;
			float		fV1;

			// UVs
			float		fU2;
			float		fV2;

			// Texture offset
			uint32_t	pOffset;
		};
};
