// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <InitGuid.h>
#define	DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <stdint.h>

#include "Macros.h"

#define SAFE_RELEASE(p) {if((p)) {(p)->Release(); (p) = NULL;}}

class Config;

CLASSPTR(Input)

class Input
{
	public:
		// Constructor
		Input(HWND _hWnd, Config* _pConfig);
		
		// Destructor
		~Input();
		
		// Create
		static InputPtr create(HWND _hWnd, Config* _pConfig);

		// Initialize
		bool initialize();

		// Close
		void close();
		
		// Update
		virtual bool update();

		// Get key name
		std::string getKeyName(int _iKeycode);

		// Get preloaded button
		int getPreloadedButton(int _iIindex);

		// Get gamepad id
		uint32_t getGamepadID() {return m_uGamePad;}

		// Device change
		virtual void deviceChange();

		// Found joystick
		BOOL foundJoystick(const DIDEVICEINSTANCE* _pInstance, void* _pContext);

		// Joystick found callback
		static BOOL CALLBACK joystickFoundCallback(const DIDEVICEINSTANCE* _pInstance, void* _pContext);

	private:
		// Key count
		static const int		msc_iKeyCount		= 256;

		// Button count, taken directly from dinput header
		static const int		msc_iButtonCount	= 128;

		// DirectInput 8 object
		LPDIRECTINPUT8			m_pDirectInput8;

		// Keyboard input device
		LPDIRECTINPUTDEVICE8	m_pKeyboardDevice;

		// Joystick input device
		LPDIRECTINPUTDEVICE8	m_pJoystickDevice;

		// Window handle
		HWND					m_hWnd;

		// Config class
		Config*					m_pConfig;

		// Joystick attached?
		bool					m_bJoystickAttached;

		// Has X and Y axis
		bool					m_bHasAxis;

		// Has POV
		bool					m_bHasPOV;
		
		// Joystick dead zone
		int						m_iDeadZone;

		// Joystick buttons
		int						m_iJoystickButtons;
		
		// Button indexes
		int						m_iButtonA;
		int						m_iButtonB;
		int						m_iButtonX;
		int						m_iButtonY;
		int						m_iButtonL;
		int						m_iButtonR;
		int						m_iSelectButton;
		int						m_iStartButton;
				
		// Game pad
		uint32_t				m_uGamePad;

		// Keys pressed
		BYTE					m_bKeys[msc_iKeyCount];

		// Last keys pressed
		BYTE					m_bLastKeys[msc_iKeyCount];

		// Buttons pressed
		BYTE					m_bButtons[msc_iButtonCount];

		// Last buttons pressed
		BYTE					m_bLastButtons[msc_iButtonCount];

		// Initialize keyboard
		bool initializeKeyboard();

		// Release keyboard
		void releaseKeyboard();

		// Update keyboard
		bool updateKeyboard();

		// Initialize joystick
		bool initializeJoystick();

		// Release joystick
		void releaseJoystick();

		// Update joystick
		bool updateJoystick();

		// Setup buttons		
		bool setupButtons(uint32_t _uGamePad);
};
