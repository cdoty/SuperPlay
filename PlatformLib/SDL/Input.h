// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <SDL.h>
#include <TinySTL/stdint.h>

#include "IInput.h"
#include "Macros.h"

NAMESPACE(SPlay)

class Input	: public IInput
{
	public:
		// Constructor
		Input();
		
		// Destructor
		~Input();
		
		// Create
		static Input* create();

		// Initialize
		bool initialize();

		// Close
		void close();
		
		// Update
		virtual bool update();

		// Get current input
		virtual uint32_t getCurrentInput() const {return m_uCurrentInput;}
		
		// Get last input
		virtual uint32_t getLastInput() const {return m_uLastInput;}
		
		// Get exit
		virtual bool getExit() const {return m_bExit;}

		// Set exit
		virtual void setExit(bool _bExit) {m_bExit = _bExit;}

		// Set 4 way
		virtual void set4Way(bool _b4Way) {m_b4Way = _b4Way;}
		
		// Device change
		virtual void deviceChange();

	private:
		// Key count
		static const int		msc_iKeyCount		= 256;

		// Button count, taken directly from dinput header
		static const int		msc_iButtonCount	= 128;

		// Joystick
		SDL_Joystick*			m_pJoystick;

		// Exit?
		bool					m_bExit;

		// Joystick attached?
		bool					m_bJoystickAttached;

		// Limit to 4 way
		bool					m_b4Way;
		
		// Has X and Y axis
		bool					m_bHasAxis;

		// Has POV
		bool					m_bHasPOV;
		
		// Joystick dead zone
		int						m_iDeadZone;

		// Joystick buttons
		int						m_iJoystickButtons;
		
		// Current input
		uint32_t				m_uCurrentInput;
		
		// Last input
		uint32_t				m_uLastInput;
		
		// Button indexes
		int						m_iButtonA;
		int						m_iButtonB;
		int						m_iButtonX;
		int						m_iButtonY;
		int						m_iButtonL;
		int						m_iButtonR;
		int						m_iSelectButton;
		int						m_iStartButton;
				
		// Key indexes
		int						m_iKeyUp;
		int						m_iKeyDown;
		int						m_iKeyLeft;
		int						m_iKeyRight;
		int						m_iKeyA;
		int						m_iKeyB;
		int						m_iKeyX;
		int						m_iKeyY;
		int						m_iKeyL;
		int						m_iKeyR;
		int						m_iSelectKey;
		int						m_iStartKey;
				
		// Game pad
		uint32_t				m_uGamePad;

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

		// Load xml
		void loadXML();
};

ENDNAMESPACE
