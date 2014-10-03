// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <Expansion/AudioLoader.h>
#include <Expansion/SpriteLoader.h>
#include <TinySTL/unordered_map.h>

#include "STLMacros.h"

using namespace SPlay;

class ResourceManager
{
	public:
		// Constructor
		ResourceManager();

		// Destructor
		~ResourceManager();

		// Create
		static ResourceManager* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load sprite
		bool loadSprite(const tinystl::string& _strSpriteName);

		// Get audio loaded
		AudioLoader* getAudioLoader() const {return m_pAudioLoader;}

		// Get sprite loaded
		SpriteLoader* getSpriteLoader(const tinystl::string& _strSpriteName);

	private:
		// Audio loader
		AudioLoader*	m_pAudioLoader;

		UNORDERED_MAPTYPE(tinystl::string, SpriteLoader*, SpriteResource);

		// Sprite resources
		SpriteResourceMap	m_mapSpriteResources;
};
