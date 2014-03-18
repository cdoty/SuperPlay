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

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif
#endif

NAMESPACE(SPlay)

class FontLoader
{
	public:
		// Constructor
		FontLoader();

		// Destructor
		virtual ~FontLoader();

		// Create the font loader
		static FontLoader* create(const tinystl::string& _strFontName, const tinystl::string& _strSubDirectory = "");

		// Initialize
		bool initialize(const tinystl::string& _strFontName, const tinystl::string& _strSubDirectory);

		// Close
		void close();

		// Get frame size
		int getFrameWidth() const {return m_iFrameWidth;}
		int getFrameHeight() const {return m_iFrameHeight;}

	private:
		// Sub directory
		tinystl::string	m_strSubDirectory;

		// Filename
		tinystl::string	m_strFilename;

		// Image buffer
		uint8_t*	m_pImageBuffer;

		// Palette
		uint8_t*	m_pPalette;
		int			m_iPaletteCount;

		// Character count
		int			m_iCharacterCount;

		// Frame size
		int			m_iFrameWidth;
		int			m_iFrameHeight;

		// Load xml
		bool loadXML(const tinystl::string& _strFontName);

		// Load font
		bool loadFont();
};

ENDNAMESPACE
