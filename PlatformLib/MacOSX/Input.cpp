// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "IDisplay.h"
#include "Input.h"
#include "Joypad.h"
//#include "JoystickGUIDs.h"
#include "Log.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"

NAMESPACE(SPlay)

enum KeyDefines
{
	eLeftKey		= 0,
	eRightKey		= 1,
	eUpKey			= 2,
	eDownKey		= 3,	
	eButtonAKey		= 4,
	eButtonBKey		= 5,
	eButtonXKey		= 6,
	eButtonYKey		= 7,
	eButtonStart	= 8,
	eButtonSelect	= 9,
	eButtonL1Key	= 10,
	eButtonR1Key	= 11
};

Input::Input()	:
	m_bExit(false),
	m_bJoystickAttached(false),
	m_b4Way(false),
	m_bHasAxis(false),
	m_bHasPOV(false),
	m_iJoystickButtons(0),
	m_iDeadZone(16384),
	m_uCurrentInput(0),
	m_uLastInput(0)
{
}

Input::~Input()
{
	close();
}

Input* Input::create()
{
	Input*	pInput	= new Input();
	
	if (false == pInput->initialize())
	{
		delete	pInput;
		
		pInput	= NULL;
	}

	return	pInput;
}

bool Input::initialize()
{
	m_uCurrentInput	= 0;
	m_uLastInput	= 0;

	if (false == initializeKeyboard())
	{
		return	false;
	}

	if (false == initializeJoystick())
	{
		return	false;
	}

	return	true;
}

void Input::close()
{
	releaseKeyboard();
	releaseJoystick();
}

bool Input::update()
{
	m_uLastInput	= m_uCurrentInput;

	m_uCurrentInput	= 0;
	
	if (true == m_bJoystickAttached)
	{
		updateJoystick();
	}

	updateKeyboard();

	return	true;
}

void Input::deviceChange()
{
}

bool Input::initializeKeyboard()
{
	return	true;
}

void Input::releaseKeyboard()
{
}

bool Input::updateKeyboard()
{
	return	true;
}

bool Input::initializeJoystick()
{
	return	true;
}

void Input::releaseJoystick()
{
}

bool Input::updateJoystick()
{
	return	true;
}

ENDNAMESPACE
