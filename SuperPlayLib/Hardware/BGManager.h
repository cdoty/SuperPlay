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
#include "HardwareDefines.h"
#include "HDMA.h"
#include "Macros.h"
#include "Text.h"

NAMESPACE(SPlay)

class BGManager
{
	public:
		// Constructor
		BGManager();

		// Destructor
		~BGManager();

		// Create
		static BGManager* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Render
		void render();

		// Set background color
		void setBackgroundColor(uint32_t _uColor);

		// Get BG
		BG* getBG(int _iIndex);

		// Get HDMA
		HDMA* getHDMA() {return m_pHDMA;}

		// Get Text
		Text* getText() {return m_pText;}
	
	private:
		// BGs
		BG*	m_pBGs[gsc_iMaxBGs];

		// HDMA
		HDMA*	m_pHDMA;

		// Text
		Text*	m_pText;
};

ENDNAMESPACE
