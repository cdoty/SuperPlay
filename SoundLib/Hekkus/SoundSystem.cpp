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
#include "PlatformDefines.h"
#include "SoundSystem.h"

#ifdef WIN32
#pragma warning(disable: 4099)
#pragma comment(lib, "hss.lib")

#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#endif
#endif

NAMESPACE(SPlay)

SoundSystem::SoundSystem()
#if !defined __ANDROID__ && !defined MARMALADE 
	:
	m_pSpeaker(NULL)
#endif
{
}

SoundSystem::~SoundSystem()
{
	close();
}

SoundSystem* SoundSystem::create()
{
	SoundSystem*	pSoundSystem	= new SoundSystem();
	
	if (false == pSoundSystem->initialize())
	{
		delete	pSoundSystem;
		
		pSoundSystem	= NULL;
	}
	
	return	pSoundSystem;
}

bool SoundSystem::initialize()
{
#if !defined __ANDROID__ && !defined MARMALADE 
	m_pSpeaker	= hss::Speaker::createSpeaker();
        
	if (NULL == m_pSpeaker)
	{
		Log::instance()->logError("Unable to create speaker.");

		return	false;
	}

	int	iRetVal	= m_pSpeaker->open(gsc_iSoundFrequency, 16, true);

	if (iRetVal != hss::kOk)
	{
		Log::instance()->logError("Unable to setup audio %d.", iRetVal);

		return        false;
	}
#endif
        
	return	true;
}

void SoundSystem::close()
{
	releaseSounds();
	releaseMusic();

#if !defined __ANDROID__ && !defined MARMALADE 
	if (m_pSpeaker != NULL)
	{
		m_pSpeaker->close();
		m_pSpeaker->release();

		m_pSpeaker	= NULL;
	}
#endif
}

void SoundSystem::pause()
{
#if !defined __ANDROID__ && !defined MARMALADE 
	ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

	m_pSpeaker->pauseSounds();
#endif
}

void SoundSystem::unpause()
{
#if !defined __ANDROID__ && !defined MARMALADE 
	ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

	m_pSpeaker->unpauseSounds();
#endif
}

void SoundSystem::setVolume(int _iVolume)
{
#if !defined __ANDROID__ && !defined MARMALADE 
	ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

	hss::ChannelGroup*	pGroup	= m_pSpeaker->getMasterChannelGroup();

	if (pGroup != NULL)
	{
		pGroup->setVolume(static_cast<float>(_iVolume) / 100.0f);
	}
#endif
}

bool SoundSystem::addSoundEvent(const tinystl::string& _strSoundName, int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		return	false;
	}

#if !defined __ANDROID__ && !defined MARMALADE 
	ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

	hss::Sound*	pSound	= m_pSpeaker->createSound(_strSoundName.c_str());

	if (NULL == pSound)
	{
		Log::instance()->logError("Unable to create sound %s", _strSoundName.c_str());

		return	false;
	}

	m_mapSoundEvents[_iEventID]	= pSound;
#endif

	return	true;
}

void SoundSystem::triggerSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
#if !defined __ANDROID__ && !defined MARMALADE 
		ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

		m_pSpeaker->playSound(m_mapSoundEvents[_iEventID]);
#endif
	}
}

void SoundSystem::stopSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
#if !defined __ANDROID__ && !defined MARMALADE 
		ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

		m_pSpeaker->stopSoundInstances(m_mapSoundEvents[_iEventID]);
#endif
	}
}

bool SoundSystem::addMusicEvent(const tinystl::string& _strMusicName, int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		return	false;
	}

#if !defined __ANDROID__ && !defined MARMALADE 
	ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

	hss::Sound*	pSound	= m_pSpeaker->createSound(_strMusicName.c_str());

	if (NULL == pSound)
	{
		Log::instance()->logError("Unable to create music %s", _strMusicName.c_str());

		return	false;
	}

	m_mapMusicEvents[_iEventID]	= pSound;
#endif

	return	true;
}

void SoundSystem::triggerMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
#if !defined __ANDROID__ && !defined MARMALADE 
		ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

		m_pSpeaker->playSound(m_mapMusicEvents[_iEventID]);
#endif
	}
}

void SoundSystem::stopMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
#if !defined __ANDROID__ && !defined MARMALADE 
		ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

		m_pSpeaker->stopSoundInstances(m_mapMusicEvents[_iEventID]);
#endif
	}
}

void SoundSystem::releaseSounds()
{
#if !defined __ANDROID__ && !defined MARMALADE 
	for (SoundEventIterator iterator = m_mapSoundEvents.begin(); iterator != m_mapSoundEvents.end(); ++iterator)
	{
		if (iterator->second != NULL)
		{
			ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

			m_pSpeaker->releaseSound(iterator->second);
		}
	}

	m_mapSoundEvents.clear();
#endif
}

bool SoundSystem::soundExists(int _iEventID)
{
#if !defined __ANDROID__ && !defined MARMALADE 
	if (m_mapSoundEvents.find(_iEventID) == m_mapSoundEvents.end())
	{
		return	false;
	}
#endif

	return	true;
}

void SoundSystem::releaseMusic()
{
#if !defined __ANDROID__ && !defined MARMALADE 
	for (MusicEventIterator iterator = m_mapMusicEvents.begin(); iterator != m_mapMusicEvents.end(); ++iterator)
	{
		if (iterator->second != NULL)
		{
			ASSERT_LOG(m_pSpeaker != NULL, "Sound system not initialized");

			m_pSpeaker->releaseSound(iterator->second);
		}
	}

	m_mapMusicEvents.clear();
#endif
}

bool SoundSystem::musicExists(int _iEventID)
{
#if !defined __ANDROID__ && !defined MARMALADE 
	if (m_mapMusicEvents.find(_iEventID) == m_mapMusicEvents.end())
	{
		return	false;
	}
#endif

	return	true;
}

ENDNAMESPACE
