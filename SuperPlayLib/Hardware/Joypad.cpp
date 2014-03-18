// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "IInput.h"
#include "Joypad.h"
#include "System.h"

NAMESPACE(SPlay)

Joypad::Joypad()
{
}

Joypad::~Joypad()
{
	close();
}

Joypad* Joypad::create()
{
	Joypad*	pJoypad	= new Joypad();

	if (false == pJoypad->initialize())
	{
		delete	pJoypad;

		pJoypad	= NULL;
	}

	return	pJoypad;
}

bool Joypad::initialize()
{
	return	true;
}

void Joypad::close()
{
}

uint32_t Joypad::getCurrentInput() const
{
	IInput*	pInput	= System::getInput();

	return	pInput->getCurrentInput();
}

bool Joypad::newInput() const
{
	IInput*	pInput	= System::getInput();

	// See if there are any new buttons or DPad presses
	if ((pInput->getCurrentInput() & ~pInput->getLastInput()) != 0)
	{
		return	true;
	}
	
	return	false;
}

bool Joypad::inputChanged() const
{
	IInput*	pInput	= System::getInput();

	// See if any button or the DPad bas been pressed or released
	if ((pInput->getLastInput() ^ pInput->getCurrentInput()) != 0)
	{
		return	true;
	}
	
	return	false;
}

bool Joypad::buttonsPushed() const
{
	IInput*	pInput	= System::getInput();

	// See if any of the button are pushed
	if ((pInput->getCurrentInput() & BUTTON_MASK) != 0)
	{
		return	true;
	}

	return	false;
}

bool Joypad::buttonsChanged() const
{
	IInput*	pInput	= System::getInput();

	// See if any button has been pressed or released
	if (((pInput->getLastInput() & BUTTON_MASK) ^ (pInput->getCurrentInput() & BUTTON_MASK)) != 0)
	{
		return	true;
	}
	
	return	false;
}

bool Joypad::buttonPressed(uint32_t _uButton) const
{
	IInput*	pInput	= System::getInput();

	// See if a specific button is pressed
	if (_uButton == (pInput->getCurrentInput() & _uButton))
	{
		return	true;
	}
	 
	return	false;
}

bool Joypad::buttonChanged(uint32_t _uButton) const
{
	IInput*	pInput	= System::getInput();

	// See if a specific button bas been pressed or released
	if (((pInput->getLastInput() & _uButton) ^ (pInput->getCurrentInput() & _uButton)) != 0)
	{
		return	true;
	}
		
	return	false;
}

bool Joypad::dpadPushed() const
{
	IInput*	pInput	= System::getInput();

	// See if the DPad is pushed
	if ((pInput->getCurrentInput() & DPAD_MASK) != 0)
	{
		return	true;
	}

	return	false;
}

bool Joypad::dpadChanged() const
{
	IInput*	pInput	= System::getInput();

	// See if the DPad has been pressed or released
	if (((pInput->getLastInput() & DPAD_MASK) ^ (pInput->getCurrentInput() & DPAD_MASK)) != 0)
	{
		return	true;
	}

	return	false;
}

bool Joypad::dPadPressed(uint32_t _uDirection) const
{
	IInput*	pInput	= System::getInput();

	// See if a specific direction is pressed
	if ((pInput->getCurrentInput() & _uDirection) != 0)
	{
		return	true;
	}
	 
	return	false;
}

void Joypad::enable4Way(bool _b4Way)
{
	IInput*	pInput	= System::getInput();

	pInput->set4Way(_b4Way);
}

bool Joypad::getExit() const
{
	IInput*	pInput	= System::getInput();

	return	pInput->getExit();
}

void Joypad::setExit(bool _bExit)
{
	IInput*	pInput	= System::getInput();

	pInput->setExit(_bExit);
}

ENDNAMESPACE
