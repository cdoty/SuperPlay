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

#pragma comment(lib, "irrKlang.lib")

NAMESPACE(SPlay)

SoundSystem::SoundSystem()	:
	m_pSoundEngine(NULL)
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
	m_pSoundEngine	= irrklang::createIrrKlangDevice();

	if (NULL == m_pSoundEngine)
	{
		Log::instance()->logError("Unable to creat irrKlang device");

		return	false;
	}
	
	return	true;
}

void SoundSystem::close()
{
	if (m_pSoundEngine != NULL)
	{
		m_pSoundEngine->stopAllSounds();
	}

	releaseSounds();
	releaseMusic();

	if (m_pSoundEngine != NULL)
	{
//		m_pSoundEngine->drop();

		m_pSoundEngine	= NULL;
	}
}

void SoundSystem::pause()
{
	m_pSoundEngine->setAllSoundsPaused(true);
}

void SoundSystem::unpause()
{
	m_pSoundEngine->setAllSoundsPaused(false);
}

void SoundSystem::setVolume(int _iVolume)
{
	m_pSoundEngine->setSoundVolume(static_cast<float>(_iVolume) / 100.0f);
}

bool SoundSystem::addSoundEvent(const tinystl::string& _strSoundName, int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		return	false;
	}

	irrklang::ISoundSource*	pSoundSource	= m_pSoundEngine->addSoundSourceFromFile(_strSoundName.c_str());

	m_mapSoundEvents[_iEventID]	= pSoundSource;

	return	true;
}

void SoundSystem::triggerSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		m_pSoundEngine->play2D(m_mapSoundEvents[_iEventID]);
	}
}

void SoundSystem::stopSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
	}
}

bool SoundSystem::addMusicEvent(const tinystl::string& _strMusicName, int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		return	false;
	}

	irrklang::ISoundSource*	pSoundSource	= m_pSoundEngine->addSoundSourceFromFile(_strMusicName.c_str());

	m_mapMusicEvents[_iEventID]	= pSoundSource;

	return	true;
}

void SoundSystem::triggerMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		m_pSoundEngine->play2D(m_mapMusicEvents[_iEventID], true);
	}
}

void SoundSystem::stopMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
	}
}

void SoundSystem::releaseSounds()
{
	for (SoundEventIterator iterator = m_mapSoundEvents.begin(); iterator != m_mapSoundEvents.end(); ++iterator)
	{
		if (iterator->second != NULL)
		{
			iterator->second->drop();
		}
	}

	m_mapSoundEvents.clear();
}

bool SoundSystem::soundExists(int _iEventID)
{
	if (m_mapSoundEvents.find(_iEventID) == m_mapSoundEvents.end())
	{
		return	false;
	}

	return	true;
}

void SoundSystem::releaseMusic()
{
	for (MusicEventIterator iterator = m_mapMusicEvents.begin(); iterator != m_mapMusicEvents.end(); ++iterator)
	{
		if (iterator->second != NULL)
		{
			iterator->second->drop();
		}
	}

	m_mapMusicEvents.clear();
}

bool SoundSystem::musicExists(int _iEventID)
{
	if (m_mapMusicEvents.find(_iEventID) == m_mapMusicEvents.end())
	{
		return	false;
	}

	return	true;
}

ENDNAMESPACE
