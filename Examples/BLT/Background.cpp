// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "Background.h"
#include "GameDefines.h"
#include "Hardware.h"

Background::Background(int _iBG)	:
	m_pMapLoader(NULL),
	m_iBG(_iBG)
{
}

Background::~Background()
{
	close();
}

Background* Background::create(int _iBG, const tinystl::string& _strMapName)
{
	Background*	pBackground	= new Background(_iBG);

	if (false == pBackground->initialize() || false == pBackground->load(_strMapName))
	{
		delete	pBackground;

		pBackground	= NULL;
	}

	return	pBackground;
}

bool Background::initialize()
{
	return	true;
}

void Background::close()
{
	delete	m_pMapLoader;

	m_pMapLoader	= NULL;	
}

void Background::update(float _fElapsedTime)
{
	m_fScrollY	-= gsc_fScrollSpeed * _fElapsedTime / gsc_fFramePeriod;

	if (m_fScrollY < 0)
	{
		m_fScrollY	+= m_fScrollHeight;
	}

	Hardware::getBG(m_iBG)->setScrollPosition(0, static_cast<int>(m_fScrollY));
}

bool Background::load(const tinystl::string& _strMapName)
{
	m_pMapLoader	= MapLoader::create(m_iBG, _strMapName);

	if (NULL == m_pMapLoader)
	{
		return	false;
	}

	// Set the scroll position to the bottom of the map
	m_fScrollY	= static_cast<float>(m_pMapLoader->getMapHeight() - gsc_iScreenHeight);

	m_fScrollHeight	= static_cast<float>(m_pMapLoader->getMapHeight());

	BG*	pBG	= Hardware::getBG(m_iBG);

	// Reset the scroll position and active the BG
	pBG->setScrollPosition(0, static_cast<int>(m_fScrollY));
	pBG->setWrap(true);
	pBG->setActive(true);

	return	true;
}

void Background::setScrollPosition(int _iX, int _iY)
{
	BG*	pBG	= Hardware::getBG(m_iBG);

	// Reset the scroll position and active the BG
	pBG->setScrollPosition(0, static_cast<int>(m_fScrollY));
}
