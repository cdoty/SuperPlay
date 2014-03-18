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

NAMESPACE(SPlay)

class SPC
{
	public:
		// Constructor
		SPC();

		// Destructor
		~SPC();

		// Create
		static SPC* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Pause
		void pause();

		// Unpause
		void unpause();

		// Set volume (0 - 100)
		void setVolume(int _iVolume);

		// Add sound event
		bool addSoundEvent(const tinystl::string& _strSoundName, int _iEventID);

		// Trigger sound event
		void triggerSoundEvent(int _iEventID);

		// Stop sound event
		void stopSoundEvent(int _iEventID);

		// Add music event
		bool addMusicEvent(const tinystl::string& _strMusicName, int _iEventID);

		// Trigger music event
		void triggerMusicEvent(int _iEventID);

		// Stop music event
		void stopMusicEvent(int _iEventID);
};

ENDNAMESPACE
