// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "AudioLoader.h"
#include "File.h"
#include "Hardware.h"
#include "Log.h"
#include "ResourceManager.h"
#include "System.h"
#include "Utilities.h"

NAMESPACE(SPlay)

AudioLoader::AudioLoader()
{
}

AudioLoader::~AudioLoader()
{
	close();
}

AudioLoader* AudioLoader::create(const tinystl::string& _strAudioName, const tinystl::string& _strSubDirectory)
{
	AudioLoader*	pFontLoader	= new AudioLoader();

	if (false == pFontLoader->initialize(_strAudioName, _strSubDirectory))
	{
		delete	pFontLoader;

		pFontLoader	= NULL;
	}

	return	pFontLoader;
}

bool AudioLoader::initialize(const tinystl::string& _strAudioName, const tinystl::string& _strSubDirectory)
{
	if (_strSubDirectory.length() > 0)
	{
		m_strSubDirectory	= _strSubDirectory;
		m_strSubDirectory	+= "/";
	}

	if (false == loadXML(_strAudioName))
	{
		return	false;
	}

	if (false == addEvents())
	{
		return	false;
	}

	return	true;
}

void AudioLoader::close()
{
	m_vecSoundEvents.clear();
	m_vecMusicEvents.clear();
}

void AudioLoader::playSound(int _iSoundHash)
{
	SPC*	pSPC	= Hardware::getSPC();

	pSPC->triggerSoundEvent(_iSoundHash);
}

void AudioLoader::playSound(const tinystl::string& _strSoundName)
{
	if (_strSoundName.length() > 0)
	{
		int	iHash	= Utilities::getHash(_strSoundName);

		playSound(iHash);
	}
}

void AudioLoader::playMusic(int _iMusicHash)
{
	SPC*	pSPC	= Hardware::getSPC();

	pSPC->triggerMusicEvent(_iMusicHash);
}

void AudioLoader::playMusic(const tinystl::string& _strMusicName)
{
	if (_strMusicName.length() > 0)
	{
		int	iHash	= Utilities::getHash(_strMusicName);

		playMusic(iHash);
	}
}

bool AudioLoader::loadXML(const tinystl::string& _strAudioName)
{
	tinystl::string	strFilename;

	strFilename	= m_strSubDirectory;
	strFilename	+= _strAudioName;
	strFilename	+= ".xml";

	xml::XMLDocument*	xmlDocument	= new xml::XMLDocument();
	
	if (xmlDocument->LoadFile(strFilename.c_str()) != xml::XML_NO_ERROR)
	{
        Log::instance()->logError("(%d) Unable to load XML %s.", xmlDocument->ErrorID(), strFilename.c_str());

		return	false;
	}
	
	xml::XMLNode*	xmlFirstNode	= xmlDocument->FirstChild();
	
	if (NULL == xmlFirstNode)
	{
        Log::instance()->logError("(%d) XML file %s is malformed.", xmlDocument->ErrorID(), strFilename.c_str());

		return	false;
	}
	
	while (xmlFirstNode != NULL)
	{
		tinystl::string	strElementName	= xmlFirstNode->Value();

		xml::XMLNode*	pTextNode	= xmlFirstNode->FirstChild();
		
		if (pTextNode != NULL)
		{
			if ("Sound" == strElementName)
			{
				if (false == loadFromNode(xmlFirstNode, true))
				{
					return	false;
				}
			}

			else if ("Music" == strElementName)
			{
				if (false == loadFromNode(xmlFirstNode, false))
				{
					return	false;
				}
			}
		}
		
		xmlFirstNode	= xmlFirstNode->NextSibling();
	}
	
	delete	xmlDocument;

	return	true;
}

bool AudioLoader::loadFromNode(xml::XMLNode* _pNode, bool _bSound)
{
	AudioInfo	audioInfo;

	audioInfo.strName	= m_strSubDirectory;
	audioInfo.iEventID	= -1;

	xml::XMLNode*	xmlChildNode	= _pNode->FirstChild();
	
	while (xmlChildNode != NULL)
	{
		tinystl::string	strElementName	= xmlChildNode->Value();

		xml::XMLNode*	pTextNode	= xmlChildNode->FirstChild();
		
		if (pTextNode != NULL)
		{
			if ("SoundName" == strElementName)
			{
				audioInfo.strName	+= gsc_szSoundsDirectory;
				audioInfo.strName	+= pTextNode->Value();
			}

			else if ("MusicName" == strElementName)
			{
				audioInfo.strName	+= gsc_szMusicDirectory;
				audioInfo.strName	+= pTextNode->Value();
			}

			else if ("EventID" == strElementName)
			{
				audioInfo.iEventID	= Utilities::getHash(pTextNode->Value());
			}
		}
		
		xmlChildNode	= xmlChildNode->NextSibling();
	}
	
	if (false == audioInfo.strName.empty() && audioInfo.iEventID != -1)
	{
		if (true == _bSound)
		{
			m_vecSoundEvents.push_back(audioInfo);
		}

		else
		{
			m_vecMusicEvents.push_back(audioInfo);
		}
	}

	return	true;
}

bool AudioLoader::addEvents()
{
	if (0 == m_vecSoundEvents.size() && 0 == m_vecMusicEvents.size())
	{
		Log::instance()->logError("No sound or music events loaded");

		return	false;
	}

	SPC*	pSPC	= Hardware::getSPC();

	int	t_c	= static_cast<int>(m_vecSoundEvents.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		pSPC->addSoundEvent(m_vecSoundEvents[iLoop].strName, m_vecSoundEvents[iLoop].iEventID);
	}

	t_c	= static_cast<int>(m_vecMusicEvents.size());

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		pSPC->addMusicEvent(m_vecMusicEvents[iLoop].strName, m_vecMusicEvents[iLoop].iEventID);
	}

	return	true;
}

ENDNAMESPACE
