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

class Image
{
	public:
		// Constructor
		Image();

		// Destructor
		~Image();

		// Create an image from a bitmap
		static Image* create(const tinystl::string& _strFilename, bool _bTransparent = false);

		// Initialize
		bool initialize(const tinystl::string& _strFilename, bool _bTransparent = false);

		// Close
		void close();

		// Get pixels
		uint32_t* getPixels() const {return m_pImage;}

		// Get width
		int getWidth() const {return m_iWidth;}

		// Get height
		int getHeight() const {return m_iHeight;}

		// Get transparent
		bool getTransparent() const {return m_bTransparent;}

	private:
		// Image size
		int			m_iWidth;
		int			m_iHeight;

		// Is this a transparent image?
		bool		m_bTransparent;

		// Image pointer
		uint32_t*	m_pImage;
};

ENDNAMESPACE
