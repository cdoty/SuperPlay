// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

NAMESPACE(SPlay)

// Initialize sound
extern bool initializeSound();

// Close sound
extern void closeSound();

class Sound
{
	public:
		// Create sound system
		static bool createSoundSystem();

		// Delete sound system
		static void deleteSoundSystem();
};

ENDNAMESPACE
