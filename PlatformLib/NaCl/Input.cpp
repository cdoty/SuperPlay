// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdlib.h>

#include "IDisplay.h"
#include "Input.h"
#include "Joypad.h"
#include "Log.h"
#include "PathDefines.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

#define	USE_GS
//#define	USE_IMPULSE

NAMESPACE(SPlay)

Input::Input()	:
	m_bExit(false),
	m_bJoystickAttached(false),
	m_b4Way(false),
	m_bHasAxis(false),
	m_bHasPOV(false),
	m_iJoystickButtons(0),
	m_iDeadZone(16384),
	m_uCurrentInput(0),
	m_uLastInput(0),
	m_iKeyUp('W'),
	m_iKeyDown('S'),
	m_iKeyLeft('A'),
	m_iKeyRight('D'),
	m_iKeyA('2'),
	m_iKeyB('1'),
	m_iKeyX('4'),
	m_iKeyY('3'),
	m_iKeyL('5'),
	m_iKeyR('7'),
	m_iKeySelect('6'),
	m_iKeyStart('8'),
	m_iButtonA(-1),
	m_iButtonB(-1),
	m_iButtonX(-1),
	m_iButtonY(-1),
	m_iButtonL(-1),
	m_iButtonR(-1),
	m_iButtonSelect(-1),
	m_iButtonStart(-1)
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

	return	true;
}

void Input::close()
{
}

bool Input::update()
{
	m_uLastInput	= m_uCurrentInput;

	return	true;
}

void Input::deviceChange()
{
}

void Input::handleKeyDown(uint32_t _uKey)
{
#ifdef USE_IMPULSE
		if ("W" == _uKey)
		{
			m_uCurrentInput	|= IK_PAD_UP;
		}

		else if ("E" == _uKey)
		{
			m_uCurrentInput	&= ~IK_PAD_UP;
		}

		if ("X" == _uKey)
		{
			m_uCurrentInput	|= IK_PAD_DOWN;
		}

		else if ("Z" == _uKey)
		{
			m_uCurrentInput	&= ~IK_PAD_DOWN;
		}

		if ("A" == _uKey)
		{
			m_uCurrentInput	|= IK_PAD_LEFT;
		}

		else if ("Q" == _uKey)
		{
			m_uCurrentInput	&= ~IK_PAD_LEFT;
		}

		if ("D" == _uKey)
		{
			m_uCurrentInput	|= IK_PAD_RIGHT;
		}

		else if ("C" == _uKey)
		{
			m_uCurrentInput	&= ~IK_PAD_RIGHT;
		}

		if ("Y" == _uKey)
		{
			m_uCurrentInput	|= IK_A;
		}

		else if ("T" == _uKey)
		{
			m_uCurrentInput	&= ~IK_A;
		}

		if ("K" == _uKey)
		{
			m_uCurrentInput	|= IK_B;
		}

		else if ("P" == _uKey)
		{
			m_uCurrentInput	&= ~IK_B;
		}

		if ("O" == _uKey)
		{
			m_uCurrentInput	|= IK_X;
		}

		else if ("G" == _uKey)
		{
			m_uCurrentInput	&= ~IK_X;
		}

		if ("L" == _uKey)
		{
			m_uCurrentInput	|= IK_Y;
		}

		else if ("V" == _uKey)
		{
			m_uCurrentInput	&= ~IK_Y;
		}

		if ("H" == _uKey)
		{
			m_uCurrentInput	|= IK_SELECT;
		}

		else if ("R" == _uKey)
		{
			m_uCurrentInput	&= ~IK_SELECT;
		}

		if ("J" == _uKey)
		{
			m_uCurrentInput	|= IK_START;
		}

		else if ("N" == _uKey)
		{
			m_uCurrentInput	&= ~IK_START;
		}
#endif

#ifdef USE_GS
	if (m_iKeyUp == _uKey || 38 == _uKey)
	{
		m_uCurrentInput	|= IK_PAD_UP;
	}

	else if (m_iKeyDown == _uKey || 40 == _uKey)
	{
		m_uCurrentInput	|= IK_PAD_DOWN;
	}

	else if (m_iKeyLeft == _uKey || 37 == _uKey)
	{
		m_uCurrentInput	|= IK_PAD_LEFT;
	}

	else if (m_iKeyRight == _uKey || 39 == _uKey)
	{
		m_uCurrentInput	|= IK_PAD_RIGHT;
	}

	else if (m_iKeyA == _uKey)
	{
		m_uCurrentInput	|= IK_A;
	}

	else if (m_iKeyB == _uKey)
	{
		m_uCurrentInput	|= IK_B;
	}

	else if (m_iKeyX == _uKey)
	{
		m_uCurrentInput	|= IK_X;
	}

	else if (m_iKeyY == _uKey)
	{
		m_uCurrentInput	|= IK_Y;
	}

	else if (m_iKeyL == _uKey)
	{
		m_uCurrentInput	|= IK_L;
	}

	else if (m_iKeyR == _uKey)
	{
		m_uCurrentInput	|= IK_R;
	}

	else if (m_iKeySelect == _uKey)
	{
		m_uCurrentInput	|= IK_SELECT;
	}

	else if (m_iKeyStart == _uKey)
	{
		m_uCurrentInput	|= IK_START;
	}
#endif
}

void Input::handleKeyUp(uint32_t _uKey)
{
#ifdef USE_IMPULSE
#endif

#ifdef USE_GS
	if (m_iKeyUp == _uKey)
	{
		m_uCurrentInput	&= ~IK_PAD_UP;
	}

	else if (m_iKeyDown == _uKey)
	{
		m_uCurrentInput	&= ~IK_PAD_DOWN;
	}

	else if (m_iKeyLeft == _uKey)
	{
		m_uCurrentInput	&= ~IK_PAD_LEFT;
	}

	else if (m_iKeyRight == _uKey)
	{
		m_uCurrentInput	&= ~IK_PAD_RIGHT;
	}

	else if (m_iKeyA == _uKey)
	{
		m_uCurrentInput	&= ~IK_A;
	}

	else if (m_iKeyB == _uKey)
	{
		m_uCurrentInput	&= ~IK_B;
	}

	else if (m_iKeyX == _uKey)
	{
		m_uCurrentInput	&= ~IK_X;
	}

	else if (m_iKeyY == _uKey)
	{
		m_uCurrentInput	&= ~IK_Y;
	}

	else if (m_iKeyL == _uKey)
	{
		m_uCurrentInput	&= ~IK_L;
	}

	else if (m_iKeyR == _uKey)
	{
		m_uCurrentInput	&= ~IK_R;
	}

	else if (m_iKeySelect == _uKey)
	{
		m_uCurrentInput	&= ~IK_SELECT;
	}

	else if (m_iKeyStart == _uKey)
	{
		m_uCurrentInput	&= ~IK_START;
	}
#endif
}

ENDNAMESPACE
