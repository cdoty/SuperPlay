// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "ResourceManager.h"

ResourceManager::ResourceManager()	:
	m_pAudioLoader(NULL)
{
}

ResourceManager::~ResourceManager()
{
	close();
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
	m_pAudioLoader	= AudioLoader::create("SoundEvents");

	if (NULL == m_pAudioLoader)
	{
		return	false;
	}
    
	return	true;
}

void ResourceManager::close()
{
	for (SpriteResourceIterator iterator = m_mapSpriteResources.begin(); iterator != m_mapSpriteResources.end(); ++iterator)
	{
		delete	iterator->second;
	}

	m_mapSpriteResources.clear();

	delete	m_pAudioLoader;

	m_pAudioLoader	= NULL;
}

bool ResourceManager::loadSprite(const tinystl::string& _strSpriteName)
{
	SpriteLoader*	pSpriteLoader	= SpriteLoader::create(_strSpriteName);

	if (NULL == pSpriteLoader)
	{
		return	false;
	}

	m_mapSpriteResources[_strSpriteName]	= pSpriteLoader;

	return	true;
}

SpriteLoader* ResourceManager::getSpriteLoader(const tinystl::string& _strSpriteName)
{
	SpriteResourceIterator	iterator	= m_mapSpriteResources.find(_strSpriteName);

	if (iterator != m_mapSpriteResources.end())
	{
		return	iterator->second;
	}

	return	NULL;
}
