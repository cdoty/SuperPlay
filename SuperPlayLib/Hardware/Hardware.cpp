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
#include "BGManager.h"
#include "Hardware.h"
#include "Macros.h"
#include "ShadowOAM.h"
#include "System.h"

NAMESPACE(SPlay)

BGVRAM*		Hardware::ms_pBGVRAM	= NULL;
DMA*		Hardware::ms_pDMA		= NULL;
Joypad*		Hardware::ms_pJoypad	= NULL;
BGManager*	Hardware::ms_pBGManager	= NULL;
OAM*		Hardware::ms_pOAM		= NULL;
ObjVRAM*	Hardware::ms_pObjVRAM	= NULL;
SPC*		Hardware::ms_pSPC		= NULL;
SRAM*		Hardware::ms_pSRAM		= NULL;
bool		Hardware::ms_bPaused	= false;

bool Hardware::initialize()
{
	ms_pDMA	= DMA::create();

	if (NULL == ms_pDMA)
	{
		return	false;
	}

	if (true == System::getGameHeader().bUseShadowOAM)
	{
		ms_pOAM	= ShadowOAM::create();
	}

	else
	{
		ms_pOAM	= OAM::create();
	}

	if (NULL == ms_pOAM)
	{
		return	false;
	}

	ms_pSPC	= SPC::create();

	if (NULL == ms_pSPC)
	{
		return	false;
	}

	ms_pSRAM	= SRAM::create();

	if (NULL == ms_pSRAM)
	{
		return	false;
	}

	ms_pBGManager	= BGManager::create();
	
	if (NULL == ms_pBGManager)
	{
		return	false;
	}

	ms_pObjVRAM	= ObjVRAM::create();

	if (NULL == ms_pObjVRAM)
	{
		return	false;
	}

	return	true;
}

void Hardware::close()
{
	delete	ms_pDMA;

	ms_pDMA	= NULL;

	delete	ms_pOAM;

	ms_pOAM	= NULL;

	delete	ms_pSPC;

	ms_pSPC	= NULL;

	delete	ms_pSRAM;

	ms_pSRAM	= NULL;

	delete	ms_pObjVRAM;

	ms_pObjVRAM	= NULL;

	delete	ms_pBGVRAM;

	ms_pBGVRAM	= NULL;

	delete	ms_pBGManager;

	ms_pBGManager	= NULL;
}

void Hardware::render()
{
	ASSERT_LOG(ms_pBGManager != NULL, "BG Manager is invalid");

	ms_pBGManager->render();
}

Text* Hardware::getText()
{
	ASSERT_LOG(ms_pBGManager != NULL, "BG Manager is invalid");

	return	ms_pBGManager->getText();
}

void Hardware::setBackgroundColor(uint8_t _uRed, uint8_t _uGreen, uint8_t _uBlue)
{
	uint32_t	uColor	= toColor(_uRed, _uGreen, _uBlue);

	ms_pBGManager->setBackgroundColor(uColor);
}

HDMA* Hardware::getHDMA()
{
	ASSERT_LOG(ms_pBGManager != NULL, "BG Manager is invalid");

	return	ms_pBGManager->getHDMA();
}

BG* Hardware::getBG(int _iIndex)
{
	ASSERT_LOG(ms_pBGManager != NULL, "BG Manager is invalid");

	return	ms_pBGManager->getBG(_iIndex);
}

void Hardware::seedRandomNumber(int _iSeed)
{
	System::seedRandomNumber(_iSeed);
}

int Hardware::getRandomValue(int _iUpper)
{
	return	System::getRandomValue(_iUpper);
}

uint32_t Hardware::toColor(uint8_t _uRed, uint8_t _uGreen, uint8_t _uBlue)
{
	return	((uint32_t)(0xFF << 24) | (_uRed << 16) | (_uGreen << 8) | (_uBlue));
}

ENDNAMESPACE
