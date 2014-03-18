// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

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

		// Device change
		virtual void deviceChange();

		// Get current input
		virtual uint32_t getCurrentInput() const {return m_uCurrentInput;}
		
		// Get last input
		virtual uint32_t getLastInput() const {return m_uLastInput;}
		
		// Get exit
		bool getExit() const {return m_bExit;}

		// Set exit
		void setExit(bool _bExit) {m_bExit = _bExit;}

		// Set 4 way
		void set4Way(bool _b4Way) {m_b4Way = _b4Way;}

	private:
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
		
		// Exit?
		bool					m_bExit;

		// Button indexes
		int						m_iButtonA;
		int						m_iButtonB;
		int						m_iSelectButton;
		int						m_iStartButton;
				
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
};

ENDNAMESPACE
