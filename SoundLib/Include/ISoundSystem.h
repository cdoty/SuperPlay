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

class ISoundSystem
{
	public:
		// Destructor
		virtual ~ISoundSystem() {}
		
		// Pause
		virtual void pause() = 0;

		// Unpause
		virtual void unpause() = 0;

		// Set volume (0 - 100)
		virtual void setVolume(int _iVolume) = 0;

		// Add sound event
		virtual bool addSoundEvent(const tinystl::string& _strSoundName, int _iEventID) = 0;

		// Trigger sound event
		virtual void triggerSoundEvent(int _iEventID) = 0;

		// Stop sound event
		virtual void stopSoundEvent(int _iEventID) = 0;

		// Add music event
		virtual bool addMusicEvent(const tinystl::string& _strMusicName, int _iEventID) = 0;

		// Trigger music event
		virtual void triggerMusicEvent(int _iEventID) = 0;

		// Stop music event
		virtual void stopMusicEvent(int _iEventID) = 0;
};

ENDNAMESPACE
