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
#include "ISoundSystem.h"
#include "SPC.h"
#include "System.h"

NAMESPACE(SPlay)

SPC::SPC()
{
}

SPC::~SPC()
{
	close();
}

SPC* SPC::create()
{
	SPC*	pSPC	= new SPC();

	if (false == pSPC->initialize())
	{
		delete	pSPC;

		pSPC	= NULL;
	}

	return	pSPC;
}

bool SPC::initialize()
{
	return	true;
}

void SPC::close()
{
}

void SPC::pause()
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->pause();
}

void SPC::unpause()
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->unpause();
}

void SPC::setVolume(int _iVolume)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->setVolume(_iVolume);
}

void SPC::triggerSoundEvent(int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->triggerSoundEvent(_iEventID);
}

void SPC::stopSoundEvent(int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->stopSoundEvent(_iEventID);
}

void SPC::triggerMusicEvent(int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->triggerMusicEvent(_iEventID);
}

void SPC::stopMusicEvent(int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	pSoundSystem->stopMusicEvent(_iEventID);
}

bool SPC::addSoundEvent(const tinystl::string& _strSoundName, int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	return	pSoundSystem->addSoundEvent(_strSoundName, _iEventID);
}

bool SPC::addMusicEvent(const tinystl::string& _strSoundName, int _iEventID)
{
	ISoundSystem*	pSoundSystem	= System::getSoundSystem();

	ASSERT_LOG(pSoundSystem != NULL, "Sound system is not valid");

	return	pSoundSystem->addMusicEvent(_strSoundName, _iEventID);
}

ENDNAMESPACE
