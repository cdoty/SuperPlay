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
#include <TinySTL/vector.h>

#include "Image.h"
#include "PathDefines.h"

NAMESPACE(SPlay)

struct StoredImage
{
	// Image
	Image*	pImage;

	// Name hash
	int		iHash;
};

class ResourceManager
{
	public:
		// Constructor
		ResourceManager();

		// Destructor
		~ResourceManager();

		// Create resource manager
		static ResourceManager* create();

		// Initialize
		bool initialize();

		// Load image
		int loadImage(const tinystl::string& _strFilename, bool _bTransparent = false);

		// Get image
		Image* getImage(int iIndex) const;

	private:
		tinystl::vector<StoredImage>	m_vecImages;

		// Find image
		int findImage(int _iHash) const;

		// Remove images
		void removeImages();
};

ENDNAMESPACE
