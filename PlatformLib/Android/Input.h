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

#include "android_native_app_glue.h"
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

		// Handle joystick event
		void handleJoystickEvent(AInputEvent* _pEvent);

		// Handle key event
		void handleKeyEvent(AInputEvent* _pEvent);

		// Device change
		virtual void deviceChange();

		// Callbacks
		bool onCreate();
		void onDestroy();
		void onPause();
		void onResume();

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
		// Moga controller
		jobject		m_mogaController;

		// Limit to 4 way
		bool		m_b4Way;
		
		// Has Axis
		bool		m_bHasAxis;

		// Joystick dead zone
		float		m_fDeadZone;

		// Current input
		uint32_t	m_uCurrentInput;
		
		// Active input
		uint32_t	m_uActiveInput;
		
		// Active input
		uint32_t	m_uActiveJoystick;
		
		// Last input
		uint32_t	m_uLastInput;
		
		// Exit?
		bool		m_bExit;

		// Key indexes
		int			m_iKeyUp;
		int			m_iKeyDown;
		int			m_iKeyLeft;
		int			m_iKeyRight;
		int			m_iKeyA;
		int			m_iKeyB;
		int			m_iKeyX;
		int			m_iKeyY;
		int			m_iKeyL;
		int			m_iKeyR;
		int			m_iSelectKey;
		int			m_iStartKey;

		// Initialize Moga
		bool initializeMoga();

		// Closea Moga
		void closeMoga();

		// Get Moga input
		uint32_t getMogaInput();
};

ENDNAMESPACE
