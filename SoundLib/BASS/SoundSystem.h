// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <bass.h>
#include <TinySTL/string.h>

#include "ISoundSystem.h"
#include "Macros.h"
#include "STLMacros.h"

NAMESPACE(SPlay)

class SoundSystem : public ISoundSystem
{
	public:
		// Constructor
		SoundSystem();

		// Destructor
		~SoundSystem();

		// Create
		static SoundSystem* create();
				
		// Initialize
		bool initialize();

		// Close
		void close();

		// Pause
		virtual void pause();

		// Unpause
		virtual void unpause();

		// Set volume (0 - 100)
		virtual void setVolume(int _iVolume);

		// Add sound event
		virtual bool addSoundEvent(const tinystl::string& _strSoundName, int _iEventID);

		// Trigger sound event
		virtual void triggerSoundEvent(int _iEventID);

		// Stop sound event
		virtual void stopSoundEvent(int _iEventID);

		// Add music event
		virtual bool addMusicEvent(const tinystl::string& _strMusicName, int _iEventID);

		// Trigger music event
		virtual void triggerMusicEvent(int _iEventID);

		// Stop music event
		virtual void stopMusicEvent(int _iEventID);

	protected:
		// Sound events
		UNORDERED_MAPTYPE(int, HSAMPLE, SoundEvent)
		SoundEventMap	m_mapSoundEvents;

		// Music events
		UNORDERED_MAPTYPE(int, HMUSIC, MusicEvent)
		MusicEventMap	m_mapMusicEvents;

		// Release sounds
		void releaseSounds();

		// Sound exists?
		bool soundExists(int _iEventID);

		// Music exists?
		bool musicExists(int _iEventID);

		// Release music
		void releaseMusic();

#ifdef __ANDROID__
		// Load shared library
		bool loadSharedLibrary();
#endif
};

ENDNAMESPACE