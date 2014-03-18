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

		// Set input
		void setInput(uint32_t _uInput);

		// Reset input
		void resetInput(uint32_t _uInput);

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

		// Event handler
		static int32 eventHandler(void* _pSystemData, void* _pUserData);

	private:
		// Exit?
		bool					m_bExit;

		// Limit to 4 way
		bool					m_b4Way;
		
		// Current input
		uint32_t				m_uCurrentInput;
		
		// Last input
		uint32_t				m_uLastInput;
		
		// Initialize joystick
		bool initializeJoystick();

		// Release joystick
		void releaseJoystick();
};

ENDNAMESPACE
