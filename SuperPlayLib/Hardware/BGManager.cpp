// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "BGManager.h"
#include "Hardware.h"

NAMESPACE(SPlay)

BGManager::BGManager()	:
	m_pHDMA(NULL),
	m_pText(NULL)
{
	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		m_pBGs[iLoop]	= NULL;
	}
}

BGManager::~BGManager()
{
	close();
}

BGManager* BGManager::create()
{
	BGManager*	pBGManager	= new BGManager();

	if (false == pBGManager->initialize())
	{
		delete	pBGManager;

		pBGManager	= NULL;
	}

	return	pBGManager;
}

bool BGManager::initialize()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		m_pBGs[iLoop]	= BG::create(iLoop);

		if (NULL == m_pBGs[iLoop])
		{
			return	false;
		}
	}

	m_pHDMA	= HDMA::create();

	if (NULL == m_pHDMA)
	{
		return	false;
	}

	m_pText	= Text::create();

	if (NULL == m_pText)
	{
		return	false;
	}

	return	true;
}

void BGManager::close()
{
	for (int iLoop = 0; iLoop < gsc_iMaxBGs; ++iLoop)
	{
		delete	m_pBGs[iLoop];

		m_pBGs[iLoop]	= NULL;
	}

	delete	m_pHDMA;

	m_pHDMA	= NULL;

	delete	m_pText;

	m_pText	= NULL;
}

void BGManager::setBackgroundColor(uint32_t _uColor)
{
	m_pHDMA->setBackgroundColor(_uColor);
}

void BGManager::render()
{
	m_pHDMA->render();

	DMA*	pDMA	= Hardware::getDMA();

	pDMA->doOAMTransfer();
	pDMA->doBGTransfer();

	OAM*	pOAM	= Hardware::getOAM();

	for (int iLoop = gsc_iMaxBGs - 1; iLoop >= 0; --iLoop)
	{
		// Render the background at the set layer
		m_pBGs[iLoop]->render();
		
		// Render the sprites at the set layer
		pOAM->render(iLoop);
	}

	// Render the text layer on top
	m_pText->render();
}

BG* BGManager::getBG(int _iIndex)
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < gsc_iMaxBGs, "Invalid BG index");

	return	m_pBGs[_iIndex];
}

ENDNAMESPACE
