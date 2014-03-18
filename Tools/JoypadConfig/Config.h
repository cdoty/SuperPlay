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
#include <UILib.h>
#include <vector>
#include <windows.h>

#include "Input.h"
#include "Macros.h"
#include "Window.h"

using namespace DuiLib;

CLASSPTR(Config)

class Config : public WindowImplBase
{
	public:
		// Constructor
		Config();

		// Destructor
		~Config();

		// Create
		static ConfigPtr create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Show
		bool show();

		// Get window class name
		LPCTSTR GetWindowClassName() const;
		
		// Init window
		virtual void InitWindow();

		// On final message
		void OnFinalMessage(HWND _hWnd);

		// Input
		void input(int _iKeycode);

		DUI_DECLARE_MESSAGE_MAP()		
		// On click
		virtual void OnClick(TNotifyUI& _msg);

		// On item select
		virtual void OnItemSelect(TNotifyUI& _msg);
		
		// On select changed
		virtual void OnSelectChanged(TNotifyUI& _msg);
		
		// On kill focus
		virtual void OnKillFocus(TNotifyUI& _msg);
		
		// Handle message
		LRESULT HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

		// Get skin file
		CDuiString GetSkinFile();

		// Get skin folder
		CDuiString GetSkinFolder();

	private:
		// Input
		InputPtr	m_pInput;

		// Window
		WindowPtr	m_pWindow;

		// Button configs
		std::vector<int>	m_vecButtonConfigs;

		// Save config
		bool saveConfig();

		// Test config
		void testConfig();

		// Setup controls
		void setupControls();

		// Setup input
		bool setupInput();

		// Load xml
		bool loadXML();

		// Get input from button
		int	getInputFromButton(int _iButton);
};
