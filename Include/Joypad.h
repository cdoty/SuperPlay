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

#include "Macros.h"

NAMESPACE(SPlay)

enum InputDefines
{
	// Input buttons
	IK_PAD_UP		= (1 << 0),
	IK_PAD_DOWN		= (1 << 1),
	IK_PAD_LEFT		= (1 << 2),
	IK_PAD_RIGHT	= (1 << 3),
	IK_A			= (1 << 4),
	IK_B			= (1 << 5),
	IK_X			= (1 << 6),
	IK_Y			= (1 << 7),
	IK_L			= (1 << 8),
	IK_R			= (1 << 9),
	IK_SELECT		= (1 << 10),
	IK_START		= (1 << 11),

	// Input masks
	DPAD_MASK		= (IK_PAD_UP | IK_PAD_DOWN | IK_PAD_LEFT | IK_PAD_RIGHT),
	BUTTON_MASK		= (~DPAD_MASK)
};

class Joypad
{
	public:
		// Constructor
		Joypad();

		// Destructor
		virtual ~Joypad();

		// Create the VRAM texture
		static Joypad* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Get current input
		uint32_t getCurrentInput() const;

		// Is there new input?
		bool newInput() const;

		// Has the input changed?
		bool inputChanged() const;

		// Is a button pushed or being held?
		bool buttonsPushed() const;

		// Have the buttons changed?
		bool buttonsChanged() const;

		// Was a specific button pressed?
		bool buttonPressed(uint32_t _uButton) const;

		// Did a specific button or dpad direction change?
		bool buttonChanged(uint32_t _uButton) const;

		// Is the DPad pushed or being held?
		bool dpadPushed() const;

		// Has the DPad changed?
		bool dpadChanged() const;

		// Has a specifc direction been pressed?
		bool dPadPressed(uint32_t _uDirection) const;
		
		// Enable 4 way
		void enable4Way(bool _b4Way);
		
		// Get exit
		bool getExit() const;

		// Set exit
		void setExit(bool _bExit);
};

ENDNAMESPACE
