// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "BG.h"
#include "BGVRAM.h"
#include "DMA.h"
#include "HardwareDefines.h"
#include "HDMA.h"
#include "Joypad.h"
#include "Macros.h"
#include "OAM.h"
#include "ObjVRAM.h"
#include "SPC.h"
#include "SRAM.h"
#include "Text.h"

NAMESPACE(SPlay)

class BGManager;

class Hardware
{
	public:
		// Initialize
		static bool initialize();

		// Close
		static void close();

		// Remder
		static void render();

		// Get DMA
		static DMA* getDMA() {return ms_pDMA;}

		// Get HDMA
		static HDMA* getHDMA();

		// Get BG
		static BG* getBG(int _iIndex);

		// Get BG VRAM
		static BGVRAM* getBGVRAM() {return ms_pBGVRAM;}

		// Set BG VRAM
		static void setBGVRAM(BGVRAM* _pBGVRAM) {ms_pBGVRAM = _pBGVRAM;}

		// Get OAM
		static OAM* getOAM() {return ms_pOAM;}

		// Get Obj VRAM
		static ObjVRAM* getObjVRAM() {return ms_pObjVRAM;}

		// Get input
		static Joypad* getJoypad() {return ms_pJoypad;}

		// Get SPC
		static SPC* getSPC() {return ms_pSPC;}

		// Get SRAM
		static SRAM* getSRAM() {return ms_pSRAM;}

		// Get text
		static Text* getText();

		// Set background color
		static void setBackgroundColor(uint8_t _uRed, uint8_t _uGreen, uint8_t _uBlue);

		// Seed random number
		static void seedRandomNumber(int _iSeed);

		// Get a random value, will never return _iUpper
		static int getRandomValue(int _iUpper);

		// Convert red, green, and blue components to a color value.
		static uint32_t toColor(uint8_t _uRed, uint8_t _uGreen, uint8_t _uBlue);

		// Get paused
		static bool getPaused() {return ms_bPaused;}

		// Set paused
		static void setPaused(bool _bPaused) {ms_bPaused = _bPaused; true == ms_bPaused ? ms_pSPC->pause() : ms_pSPC->unpause();}

	private:
		// DMA
		static DMA*			ms_pDMA;

		// Joypad
		static Joypad*		ms_pJoypad;

		// BG manager
		static BGManager*	ms_pBGManager;

		// OAM
		static OAM*			ms_pOAM;

		// Obj VRAM
		static ObjVRAM*		ms_pObjVRAM;

		// SPC
		static SPC*			ms_pSPC;

		// SRAM
		static SRAM*		ms_pSRAM;

		// Tile VRAM
		static BGVRAM*		ms_pBGVRAM;

		// Paused?
		static bool			ms_bPaused;
};

ENDNAMESPACE
