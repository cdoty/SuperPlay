// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <string>
#include <vector>

#include "Display.h"
#include "Input.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/WindowCanvas.h"
#include "Gwen/Controls/ImagePanel.h"
#include "Gwen/Controls/ListBox.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Input/Windows.h"

class Config : public Gwen::Event::Handler
{
	public:
		// Constructor
		Config();

		// Destructor
		~Config();

		// Create
		static Config* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Run
		void run();

		// Input
		void input(int _iKeycode);

		// On selection
		void OnSelection(Gwen::Controls::Base* _pControl);

	private:
		// Input
		InputPtr						m_pInput;

		// Display
		Display*						m_pDisplay;

		// Button configs
		std::vector<int>				m_vecButtonConfigs;

		// Skin
		Gwen::Skin::TexturedBase*		m_pSkin;
		
		// Canvas
		Gwen::Controls::WindowCanvas*	m_pCanvas;

		// List box
		Gwen::Controls::ListBox*		m_pListBox;

		// Buttons
		Gwen::Controls::Button*			m_pSaveButton;
		Gwen::Controls::Button*			m_pTestButton;
		Gwen::Controls::Button*			m_pBackButton;

		// Gamepad image
		Gwen::Controls::ImagePanel*		m_pGamePad;

		// Indicator image
		Gwen::Controls::ImagePanel*		m_pIndicator;

		// Testing?
		bool							m_bTesting;

		// Button positions
		std::vector<POINT>				m_vecButtonPositions;

		// Save config
		bool saveConfig();

		// Test config
		void testConfig(bool _bTest);

		// Setup controls
		void setupControls();

		// Setup input
		bool setupInput();

		// Load xml
		bool loadXML();

		// Get input from button
		int	getInputFromButton(int _iButton);

		// Show gamepad
		void showGamePad(bool _bShow);

		// Setup gamepad
		void setupGamepad();
};
