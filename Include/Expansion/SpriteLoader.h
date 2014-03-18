// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>

#include "Macros.h"
#include "Obj.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif
#endif

NAMESPACE(SPlay)

class SpriteLoader
{
	public:
		// Constructor
		SpriteLoader();

		// Destructor
		virtual ~SpriteLoader();

		// Create the sprite loader
		static SpriteLoader* create(const tinystl::string& _strSpriteName, const tinystl::string& _strSubDirectory = "");

		// Initialize
		bool initialize(const tinystl::string& _strSpriteName, const tinystl::string& _strSubDirectory);

		// Close
		void close();

		// Get obj size
		ObjSize getObjSize() const;

		// Get frame size
		int getFrameWidth() const {return m_iFrameWidth;}
		int getFrameHeight() const {return m_iFrameHeight;}

		// Get frame count
		int getFrameCount() const {return m_iFrameCount;}

		// Get tile size
		int getTileWidth() const {return m_iFrameWidth / gsc_iMinObjSize;}
		int getTileHeight() const {return m_iFrameHeight / gsc_iMinObjSize;}

		// Transfer frame
		void transferFrame(int _iFrameIndex, int _iTileIndex) const;

	private:
		// Sub directory
		tinystl::string	m_strSubDirectory;

		// Tile name
		tinystl::string	m_strTileName;

		// Image index
		int			m_iImageIndex;

		// Frame size
		int			m_iFrameWidth;
		int			m_iFrameHeight;

		// Frame count
		int			m_iFrameCount;

		// Load XML
		bool loadXML(const tinystl::string& _strSpriteName);

		// Load tiles
		bool loadTiles();
};

ENDNAMESPACE
