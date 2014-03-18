// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#ifdef __ANDROID__
#include <dlfcn.h>
#define BASSDEF(f) (*f)	// define the BASS functions as pointers
#endif

#if defined __linux__
#include <linux/limits.h>
#endif

#include <TinySTL/stddef.h>

#include "AssertLog.h"
#include "File.h"
#include "Log.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "SoundSystem.h"

NAMESPACE(SPlay)

// Maximum number of simultaneous sample play backs
static const int	gsc_iMaxSimultaneous	= 4;

SoundSystem::SoundSystem()
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
#ifdef __ANDROID__
	if (false == loadSharedLibrary())
	{
		Log::instance()->logError("Unable to load BASS library");

		return	false;
	}
#endif

	if (false == BASS_Init(-1, gsc_iSoundFrequency, 0, NULL, NULL))
	{
		Log::instance()->logError("Unable to initialize BASS library %d", BASS_ErrorGetCode());

		return	false;
	}

	setVolume(100);

	return	true;
}

void SoundSystem::close()
{
	releaseSounds();
	releaseMusic();

#ifdef __ANDROID__
	if (BASS_Free != NULL)
	{
		BASS_Free();
	}
#else
	BASS_Free();
#endif
}

void SoundSystem::pause()
{
	BASS_Pause();
}

void SoundSystem::unpause()
{
	BASS_Start();
}

void SoundSystem::setVolume(int _iVolume)
{
	BASS_SetVolume(static_cast<float>(_iVolume) / 100.0f);
}

bool SoundSystem::addSoundEvent(const tinystl::string& _strSoundName, int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		return	false;
	}

	File*	pFile	 = new File();

	if (false == pFile->open(_strSoundName, true))
	{
		Log::instance()->logError("Unable to open sound file %s", _strSoundName.c_str());

		return	false;
	}

	int	iLength	= pFile->getLength();

	uint8_t*	pBuffer	= NULL;

	if (false == pFile->readBuffer(&pBuffer))
	{
		Log::instance()->logError("Unable to read from sound file %s", _strSoundName.c_str());

		return	false;
	}

	pFile->close();

	delete	pFile;

	HSAMPLE	hSample	= BASS_SampleLoad(TRUE, pBuffer, 0, iLength, gsc_iMaxSimultaneous, BASS_SAMPLE_OVER_POS);

	delete[]	pBuffer;

	if (0 == hSample)
	{
		Log::instance()->logError("Unable to create sound %s: %d", _strSoundName.c_str(), BASS_ErrorGetCode());

		return	false;
	}

	m_mapSoundEvents[_iEventID]	= hSample;

	return	true;
}

void SoundSystem::triggerSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		HCHANNEL	hChannel	= BASS_SampleGetChannel(m_mapSoundEvents[_iEventID], false);

		if (hChannel != 0)
		{
			BASS_ChannelPlay(hChannel, TRUE);
		}
	}
}

void SoundSystem::stopSoundEvent(int _iEventID)
{
	if (true == soundExists(_iEventID))
	{
		BASS_SampleStop(m_mapSoundEvents[_iEventID]);
	}
}

bool SoundSystem::addMusicEvent(const tinystl::string& _strMusicName, int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		return	false;
	}

	File*	pFile	 = new File();

	if (false == pFile->open(_strMusicName, true))
	{
		Log::instance()->logError("Unable to open sound file %s", _strMusicName.c_str());

		return	false;
	}

	int	iLength	= pFile->getLength();

	uint8_t*	pBuffer	= NULL;

	if (false == pFile->readBuffer(&pBuffer))
	{
		Log::instance()->logError("Unable to read from sound file %s", _strMusicName.c_str());

		return	false;
	}

	pFile->close();

	delete	pFile;

	HMUSIC	hMusic	= BASS_MusicLoad(TRUE, pBuffer, 0, iLength, gsc_iMaxSimultaneous, BASS_SAMPLE_OVER_POS);

	delete[]	pBuffer;

	if (0 == hMusic)
	{
		Log::instance()->logError("Unable to create music %s: %d", _strMusicName.c_str(), BASS_ErrorGetCode());

		return	false;
	}

	m_mapMusicEvents[_iEventID]	= hMusic;

	return	true;
}

void SoundSystem::triggerMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		BASS_ChannelPlay(m_mapMusicEvents[_iEventID], TRUE);
	}
}

void SoundSystem::stopMusicEvent(int _iEventID)
{
	if (true == musicExists(_iEventID))
	{
		BASS_ChannelStop(m_mapMusicEvents[_iEventID]);
	}
}

void SoundSystem::releaseSounds()
{
	for (SoundEventIterator iterator = m_mapSoundEvents.begin(); iterator != m_mapSoundEvents.end(); ++iterator)
	{
		BASS_SampleFree(iterator->second);
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
		BASS_MusicFree(iterator->second);
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

#ifdef __ANDROID__
bool SoundSystem::loadSharedLibrary()
{
    char	szPath[PATH_MAX];
	
	sprintf(szPath, "%s/lib/libbass.so", Platform::getExecPath().c_str());

	// Load the BASS library and get the needed functions
	void*	pBassLib	= dlopen(szPath, RTLD_LAZY);

	if (NULL == pBassLib)
	{
		Log::instance()->logError("Unable to load libbass.so");
		
		return	false;
	}
	
	#define LOADBASSFUNCTION(f) {*((void**)&f)=dlsym(pBassLib, #f); if (NULL==&f) return false;}
	LOADBASSFUNCTION(BASS_Init);
	LOADBASSFUNCTION(BASS_Free);
	LOADBASSFUNCTION(BASS_Pause);
	LOADBASSFUNCTION(BASS_Start);
	LOADBASSFUNCTION(BASS_SetVolume);
	LOADBASSFUNCTION(BASS_SampleLoad);
	LOADBASSFUNCTION(BASS_SampleStop);
	LOADBASSFUNCTION(BASS_SampleFree);
	LOADBASSFUNCTION(BASS_SampleGetChannel);
	LOADBASSFUNCTION(BASS_ChannelPlay);
	LOADBASSFUNCTION(BASS_ChannelStop);
	LOADBASSFUNCTION(BASS_MusicLoad);
	LOADBASSFUNCTION(BASS_MusicFree);
	LOADBASSFUNCTION(BASS_ErrorGetCode);

	return	true;
}
#endif

ENDNAMESPACE
