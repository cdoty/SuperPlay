// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stddef.h>

#include "AssertLog.h"
#include "Log.h"
#include "ResourceManager.h"
#include "Utilities.h"

NAMESPACE(SPlay)

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	removeImages();
}

ResourceManager* ResourceManager::create()
{
	ResourceManager*	pResourceManager	= new ResourceManager();

	if (false == pResourceManager->initialize())
	{
		delete	pResourceManager;

		pResourceManager	= NULL;
	}

	return	pResourceManager;
}

bool ResourceManager::initialize()
{
	return	true;
}

int ResourceManager::loadImage(const tinystl::string& _strFilename, bool _bTransparent)
{
	int	iHash	= Utilities::getHash(_strFilename);

	int	iImageIndex	= findImage(iHash);

	if (iImageIndex != -1)
	{
		return	iImageIndex;
	}

	Image*	pImage	= Image::create(_strFilename, _bTransparent);

	if (NULL == pImage)
	{
		return	-1;
	}

	iImageIndex	= static_cast<int>(m_vecImages.size());

	StoredImage	storedImage;

	storedImage.pImage	= pImage;
	storedImage.iHash	= iHash;
	
	m_vecImages.push_back(storedImage);
	
	return	iImageIndex;
}

Image* ResourceManager::getImage(int iIndex) const
{
	ASSERT_LOG(iIndex >= 0 && iIndex < static_cast<int>(m_vecImages.size()), "Image index is invalid");

	return	m_vecImages[iIndex].pImage;
}

int ResourceManager::findImage(int _iHash) const
{
	int	t_c	= static_cast<int>(m_vecImages.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (m_vecImages[iLoop].iHash == _iHash)
		{
			return	iLoop;
		}
	}

	return	-1;
}

void ResourceManager::removeImages()
{
	int	t_c	= static_cast<int>(m_vecImages.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete	m_vecImages[iLoop].pImage;

		m_vecImages[iLoop].pImage	= NULL;
	}

	m_vecImages.clear();
}

ENDNAMESPACE
