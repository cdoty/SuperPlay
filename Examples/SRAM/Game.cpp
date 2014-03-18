// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <Hardware.h>
#include <HardwareDefines.h>
#include <stdio.h>
#include <string.h>

#include "Game.h"
#include "GameDefines.h"

// Defines the Game class.
CREATE_GAME(Game)

Game::Game()	:
	m_pFontLoader(NULL)
{
}

Game::~Game()
{
	close();
}

Game* Game::create()
{
	Game*	pGame	= new Game();

	if (false == pGame->initialize())
	{
		delete	pGame;

		pGame	= NULL;
	}

	return	pGame;
}

bool Game::initialize()
{
	memset(&m_sram, 0, gsc_iSRAMSize);
	
	SRAM*	pSRAM	= Hardware::getSRAM();

	pSRAM->readSRAM((uint8_t*)&m_sram);

	m_sram.uInitCount++;

	pSRAM->updateSRAM(0, (uint8_t*)&m_sram, gsc_iSRAMSize);
	pSRAM->commitSRAM();

	// Set background color
	Hardware::setBackgroundColor(0x00, 0x00, 0x88);

	// Load a font
	m_pFontLoader	= FontLoader::create("Font");	
	
	if (NULL == m_pFontLoader)
	{
		return	false;
	}

	// Draw text strings at the top and bottom of the screen
	Text*	pText	= Hardware::getText();

	tinystl::string	strLoadStatus;

	if (true == pSRAM->getCorrupt())
	{
		if (true == pSRAM->getFixed())
		{
			strLoadStatus	= "SAVE FILE CORRUPTION FIXED";
		}

		else
		{
			strLoadStatus	= "SAVE FILE NOT REPAIRABLE";
		}
	}

	else
	{
		strLoadStatus	= "SAVE FILE LOAD SUCCESSFFUL";
	}

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strLoadStatus.length()) / 2, (gsc_iScreenHeight / gsc_iFontSize) / 2 - 1, 
		strLoadStatus.c_str());

	char	szInitCount[32];

	sprintf(szInitCount, "PROGRAM RAN %u TIMES", m_sram.uInitCount);

	tinystl::string	strMessage	= szInitCount;

	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strMessage.length()) / 2, (gsc_iScreenHeight / gsc_iFontSize) / 2 + 1, 
		strMessage.c_str());

	// Activate text layer
	pText->setActive(true);

	return	true;
}

void Game::close()
{
	delete	m_pFontLoader;

	m_pFontLoader	= NULL;
}

bool Game::update(float _fElapsedTime)
{
	// Check if the game is ready to exit
	if (true == Hardware::getJoypad()->getExit())
	{
		// Indicate that the game should exit
		return	false;
	}

	return	true;
}
