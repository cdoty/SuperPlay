// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinyXML2/tinyxml2.h>
#include <s3e.h>
#include <stdlib.h>

#include "File.h"
#include "IDisplay.h"
#include "Input.h"
#include "Joypad.h"
#include "Log.h"
#include "PathDefines.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

Input::Input()	:
	m_bExit(false),
	m_b4Way(false),
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

	if (false == initializeJoystick())
	{
		return	false;
	}

	return	true;
}

void Input::close()
{
	releaseJoystick();
}

bool Input::update()
{
	m_uLastInput	= m_uCurrentInput;

	return	true;
}

void Input::setInput(uint32_t _uInput)
{
	m_uCurrentInput	|= _uInput;
}

void Input::resetInput(uint32_t _uInput)
{
	m_uCurrentInput	&= ~_uInput;
}

void Input::deviceChange()
{
}

int32 Input::eventHandler(void* _pSystemData, void* _pUserData)
{
	Input*	pInput	= static_cast<Input*>(_pUserData);

    s3eKeyboardEvent*	pEvent	= static_cast<s3eKeyboardEvent*>(_pSystemData);

    s3eKey	key	= pEvent->m_Key;

	uint32_t	uInput;

	switch (key)
	{
		case s3eKeyAbsUp:
			uInput	= IK_PAD_UP;
						
			break;
	
		case s3eKeyAbsDown:
			uInput	= IK_PAD_DOWN;
						
			break;
	
		case s3eKeyAbsLeft:
			uInput	= IK_PAD_LEFT;
						
			break;
	
		case s3eKeyAbsRight:
			uInput	= IK_PAD_RIGHT;
						
			break;
	
		case s3eKeyAbsGameA:
			uInput	= IK_A;
						
			break;

		case s3eKeyAbsGameB:
			uInput	= IK_B;
						
			break;

		case s3eKeyAbsGameC:
			uInput	= IK_X;
						
			break;

		case s3eKeyAbsGameD:
			uInput	= IK_Y;
						
			break;

		default:
			uInput	= 0xFFFFFFFF;
	}

	if (uInput != 0xFFFFFFFF)
	{
		if (1 == pEvent->m_Pressed)
		{
			pInput->setInput(uInput);
		}

		else
		{
			pInput->resetInput(uInput);
		}
	}

	return	0;
}

bool Input::initializeJoystick()
{
	s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &eventHandler, this);

 	return	true;
}

void Input::releaseJoystick()
{
	s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, &eventHandler);
}

ENDNAMESPACE
