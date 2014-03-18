// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stddef.h>

#include "Log.h"
#include "Sound.h"
#include "SoundSystem.h"
#include "System.h"

NAMESPACE(SPlay)

// Initialize sound
bool initializeSound()
{
	return	Sound::createSoundSystem();
}

// Close sound
void closeSound()
{
	Sound::deleteSoundSystem();
}

bool Sound::createSoundSystem()
{
	System::ms_pSoundSystem	= SoundSystem::create();

	if (NULL == System::ms_pSoundSystem)
	{
		return	false;
	}

	return	true;
}

void Sound::deleteSoundSystem()
{
	// Delete sound system
	delete	System::ms_pSoundSystem;

	System::ms_pSoundSystem	= NULL;
}

ENDNAMESPACE
