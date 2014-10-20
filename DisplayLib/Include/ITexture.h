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
#include "Rect.h"

NAMESPACE(SPlay)

enum eFormat
{
	NoAlpha,
	Alpha8Bit,
};

class ITexture
{
	public:
		// Destructor
		virtual ~ITexture() {}

		// Get texture width and height
		virtual void getSize(int& _iTextureWidth, int& _iTextureHeight) const = 0;

		// Get image width
		virtual int getImageWidth() const = 0;
		
		// Get image height
		virtual int getImageHeight() const = 0;
		
		// Get texture width
		virtual int getTextureWidth() const = 0;
		
		// Get texture height
		virtual int getTextureHeight() const = 0;
		
		// Get buffer
		virtual bool getBuffer(uint32_t*& _pBuffer, int& _iStride) const = 0;
		
		// Release buffer
		virtual void releaseBuffer() = 0;

		// Add update rect
		virtual void addUpdateRect(int _iStartY, int _iHeight) {};
};

ENDNAMESPACE
