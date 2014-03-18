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
#include <TinyXML2/tinyxml2.h>

#include "Macros.h"
#include "STLMacros.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif
#endif

NAMESPACE(SPlay)

class AudioLoader
{
	public:
		// Constructor
		AudioLoader();

		// Destructor
		virtual ~AudioLoader();

		// Create the audio loader
		static AudioLoader* create(const tinystl::string& _strAudioName, const tinystl::string& _strSubDirectory = "");

		// Initialize
		bool initialize(const tinystl::string& _strAudioName, const tinystl::string& _strSubDirectory);

		// Close
		void close();

		// Play sound
		void playSound(int _iSoundHash);
		void playSound(const tinystl::string& _strSoundName);

		// Play music
		void playMusic(int _iMusicHash);
		void playMusic(const tinystl::string& _strMusicName);

	private:
		struct AudioInfo
		{
			// Filename
			tinystl::string	strName;

			// Event ID hash
			int				iEventID;
		};

		// Sub directory
		tinystl::string	m_strSubDirectory;

		// Sound events
		tinystl::vector<AudioInfo>	m_vecSoundEvents;

		// Music events
		tinystl::vector<AudioInfo>	m_vecMusicEvents;

		// Load xml
		bool loadXML(const tinystl::string& _strAudioName);

		// Load from node
		bool loadFromNode(xml::XMLNode* _pNode, bool _bSound);

		// Add events
		bool addEvents();
};

ENDNAMESPACE
