// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <dlfcn.h>

#include "controller.h"
#include "IDisplay.h"
#include "Input.h"
#include "Joypad.h"
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

enum
{
	OUYA_PAD_AXIS_LS_X	= 0,
	OUYA_PAD_AXIS_LS_Y	= 1,
	OUYA_PAD_AXIS_RS_X	= 11,
	OUYA_PAD_AXIS_RS_Y	= 14,

#ifdef GAMESTICK
	GAMESTICK_DPAD_X	= 15,
	GAMESTICK_DPAD_Y	= 16
#endif
};

// Moga dead zone
static const float	gsc_fMogaDeadZone	= 0.25f;

typedef float (*GetAxisValueFunc)(const AInputEvent* motion_event, int32_t axis, size_t pointerId);

static GetAxisValueFunc AMotionEvent_getAxisValue;

Input::Input()	:
	m_mogaController(NULL),
	m_bExit(false),
	m_b4Way(false),
	m_bHasAxis(true),
	m_fDeadZone(0.75f),
	m_uCurrentInput(0),
	m_uActiveInput(0),
	m_uActiveJoystick(0),
	m_uLastInput(0),
	m_iKeyUp(AKEYCODE_DPAD_UP),
	m_iKeyDown(AKEYCODE_DPAD_DOWN),
	m_iKeyLeft(AKEYCODE_DPAD_LEFT),
	m_iKeyRight(AKEYCODE_DPAD_RIGHT),
#if defined OUYA || defined GAMESTICK
	m_iKeyA(AKEYCODE_BUTTON_B),
	m_iKeyB(AKEYCODE_BUTTON_A),
	m_iKeyX(AKEYCODE_BUTTON_Y),
	m_iKeyY(AKEYCODE_BUTTON_X),
#else
	m_iKeyA(AKEYCODE_BACK),
	m_iKeyB(AKEYCODE_DPAD_CENTER),
	m_iKeyX(AKEYCODE_BUTTON_Y),
	m_iKeyY(AKEYCODE_BUTTON_X),
#endif
	m_iKeyL(AKEYCODE_BUTTON_L1),
	m_iKeyR(AKEYCODE_BUTTON_R1),
#ifdef OUYA
	m_iSelectKey(AKEYCODE_BUTTON_THUMBL),
	m_iStartKey(AKEYCODE_BUTTON_THUMBR)
#elif defined GAMESTICK
	m_iSelectKey(AKEYCODE_BACK),
	m_iStartKey(AKEYCODE_BUTTON_START)
#else
	m_iSelectKey(AKEYCODE_BUTTON_SELECT),
	m_iStartKey(AKEYCODE_BUTTON_START)
#endif
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

	void*	pAndroid	= dlopen("libandroid.so", 0);

	if (NULL == pAndroid)
	{
		m_bHasAxis	= false;
	}

	else
	{
		AMotionEvent_getAxisValue	= (GetAxisValueFunc)dlsym(pAndroid, "AMotionEvent_getAxisValue");

		if (NULL == AMotionEvent_getAxisValue)
		{
			m_bHasAxis	= false;
		}
	}

	return	true;
}

void Input::close()
{
	closeMoga();
}

bool Input::update()
{
	m_uLastInput	= m_uCurrentInput;		
	m_uCurrentInput	= m_uActiveInput | m_uActiveJoystick | getMogaInput();
	
#ifdef OUYA
	m_uActiveInput	&= ~IK_START;
#endif

	if (true == m_b4Way)
	{
		if (m_uCurrentInput & IK_PAD_LEFT)
		{
			m_uCurrentInput	&= BUTTON_MASK;
			m_uCurrentInput	|= IK_PAD_LEFT;
		}

		else if (m_uCurrentInput & IK_PAD_RIGHT)
		{
			m_uCurrentInput	&= BUTTON_MASK;
			m_uCurrentInput	|= IK_PAD_RIGHT;
		}
	}

	return	true;
}

void Input::handleJoystickEvent(AInputEvent* _pEvent)
{
	if (true == m_bHasAxis)
	{
		float	fX		= AMotionEvent_getAxisValue(_pEvent, OUYA_PAD_AXIS_LS_X, 0);

#if defined GAMESTICK
		float	fHatX	= AMotionEvent_getAxisValue(_pEvent, GAMESTICK_DPAD_X, 0);
#endif
	
		if (fX <= -m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_LEFT;
		}

		else if (fX >= m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_RIGHT;
		}

#if defined GAMESTICK
		else if (fHatX <= -m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_LEFT;
		}

		else if (fHatX >= m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_RIGHT;
		}
#endif

		else
		{
			m_uActiveJoystick	&= ~(IK_PAD_LEFT | IK_PAD_RIGHT);
		}

		float	fY		= AMotionEvent_getAxisValue(_pEvent, OUYA_PAD_AXIS_LS_Y, 0);

#if defined GAMESTICK
		float	fHatY	= AMotionEvent_getAxisValue(_pEvent, GAMESTICK_DPAD_Y, 0);
#endif

		if (fY <= -m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_UP;
		}

		else if (fY >= m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_DOWN;
		}

#if defined GAMESTICK
		else if (fHatY <= -m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_UP;
		}

		else if (fHatY >= m_fDeadZone)
		{
			m_uActiveJoystick	|= IK_PAD_DOWN;
		}
#endif

		else
		{
			m_uActiveJoystick	&= ~(IK_PAD_UP | IK_PAD_DOWN);
		}
	}
}

void Input::handleKeyEvent(AInputEvent* _pEvent)
{
	int32_t	iAction		= AKeyEvent_getAction(_pEvent);
	int32_t	iKeyCode	= AKeyEvent_getKeyCode(_pEvent);

	if (AKEY_EVENT_ACTION_DOWN == iAction)
	{
#ifndef OUYA
#ifndef GAMESTICK
#if 0
		if (AKEYCODE_BACK == iKeyCode)
		{
			m_bExit	= true;
		}

		else
#endif
#endif
		
		if (iKeyCode == m_iKeyUp)
#else
		if (iKeyCode == m_iKeyUp)
#endif
		{
			m_uActiveInput	|= IK_PAD_UP;
		}
		
		else if (iKeyCode == m_iKeyDown)
		{
			m_uActiveInput	|= IK_PAD_DOWN;
		}

		else if (iKeyCode == m_iKeyLeft)
		{
			m_uActiveInput	|= IK_PAD_LEFT;
		}
		
		else if (iKeyCode == m_iKeyRight)
		{
			m_uActiveInput	|= IK_PAD_RIGHT;
		}

		else if (iKeyCode == m_iKeyA)
		{
			m_uActiveInput	|= IK_A;
		}

		else if (iKeyCode == m_iKeyB)
		{
			m_uActiveInput	|= IK_B;
		}

		else if (iKeyCode == m_iKeyX)
		{
			m_uActiveInput	|= IK_X;
		}

		else if (iKeyCode == m_iKeyY)
		{
			m_uActiveInput	|= IK_Y;
		}

		else if (iKeyCode == m_iKeyL)
		{
			m_uActiveInput	|= IK_L;
		}

		else if (iKeyCode == m_iKeyR)
		{
			m_uActiveInput	|= IK_R;
		}

		else if (iKeyCode == m_iSelectKey)
		{
			m_uActiveInput	|= IK_SELECT;
		}

		else if (iKeyCode == m_iStartKey)
		{
			m_uActiveInput	|= IK_START;
		}
	}

	else if (AKEY_EVENT_ACTION_UP == iAction)
	{
		if (iKeyCode == m_iKeyUp)
		{
			m_uActiveInput	&= ~IK_PAD_UP;
		}
		
		else if (iKeyCode == m_iKeyDown)
		{
			m_uActiveInput	&= ~IK_PAD_DOWN;
		}

		else if (iKeyCode == m_iKeyLeft)
		{
			m_uActiveInput	&= ~IK_PAD_LEFT;
		}
		
		else if (iKeyCode == m_iKeyRight)
		{
			m_uActiveInput	&= ~IK_PAD_RIGHT;
		}

		else if (iKeyCode == m_iKeyA)
		{
			m_uActiveInput	&= ~IK_A;
		}

		else if (iKeyCode == m_iKeyB)
		{
			m_uActiveInput	&= ~IK_B;
		}

		else if (iKeyCode == m_iKeyX)
		{
			m_uActiveInput	&= ~IK_X;
		}

		else if (iKeyCode == m_iKeyY)
		{
			m_uActiveInput	&= ~IK_Y;
		}

		else if (iKeyCode == m_iKeyL)
		{
			m_uActiveInput	&= ~IK_L;
		}

		else if (iKeyCode == m_iKeyR)
		{
			m_uActiveInput	&= ~IK_R;
		}

		else if (iKeyCode == m_iSelectKey)
		{
			m_uActiveInput	&= ~IK_SELECT;
		}

		else if (iKeyCode == m_iStartKey)
		{
#if !defined OUYA
			m_uActiveInput	&= ~IK_START;
#endif
		}
	}
}

void Input::deviceChange()
{
}

bool Input::onCreate()
{
	if (false == initializeMoga())
	{
		return	false;
	}

	return	true;
}

void Input::onDestroy()
{
	closeMoga();
}

void Input::onPause()
{
	if (m_mogaController != NULL)
	{
		JNIEnv*	pEnv	= Platform::getJNIEnv();

		Controller	controller(m_mogaController);

		controller.onPause(pEnv);
	}
}

void Input::onResume()
{
	if (m_mogaController != NULL)
	{
		JNIEnv*	pEnv	= Platform::getJNIEnv();

		Controller	controller(m_mogaController);

		controller.onResume(pEnv);
	}
}

bool Input::initializeMoga()
{
	JNIEnv*	pEnv	= Platform::getJNIEnv();

	const jobject controllerInstance	= Controller::getInstance(pEnv, Platform::getActivity()->clazz);

	m_mogaController	= pEnv->NewGlobalRef(controllerInstance);

	Controller	controller(m_mogaController);
	
	if (JNI_FALSE == controller.init(pEnv))
	{
		return	false;
	}

	return	true;
}

void Input::closeMoga()
{
	if (m_mogaController != NULL)
	{
		JNIEnv*	pEnv	= Platform::getJNIEnv();

		Controller	controller(m_mogaController);

		controller.exit(pEnv);

		pEnv->DeleteGlobalRef(m_mogaController);

		m_mogaController	= NULL;
	}
}

uint32_t Input::getMogaInput()
{
	uint32_t	uInput = 0;

	if (m_mogaController != NULL)
	{
		JNIEnv*	pEnv	= Platform::getJNIEnv();

		Controller	controller(m_mogaController);

		if (Controller::ACTION_CONNECTED == controller.getState(pEnv, Controller::STATE_CONNECTION))
		{
			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_B))
			{
				uInput	|= IK_A;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_A))
			{
				uInput	|= IK_B;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_Y))
			{
				uInput	|= IK_X;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_X))
			{
				uInput	|= IK_Y;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_L1))
			{
				uInput	|= IK_L;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_R1))
			{
				uInput	|= IK_R;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_SELECT))
			{
				uInput	|= IK_SELECT;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_BUTTON_START))
			{
				uInput	|= IK_START;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_DPAD_UP))
			{
				uInput	|= IK_PAD_UP;
			}

			else if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_DPAD_DOWN))
			{
				uInput	|= IK_PAD_DOWN;
			}

			if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_DPAD_LEFT))
			{
				uInput	|= IK_PAD_LEFT;
			}

			else if (Controller::ACTION_DOWN == controller.getKeyCode(pEnv, Controller::KEYCODE_DPAD_RIGHT))
			{
				uInput	|= IK_PAD_RIGHT;
			}

			const jfloat	fX	= controller.getAxisValue(pEnv, Controller::AXIS_X);
			const jfloat	fY	= controller.getAxisValue(pEnv, Controller::AXIS_Y);
		
			if (fY <= -gsc_fMogaDeadZone)
			{
				uInput	|= IK_PAD_UP;
			}

			else if (fY >= gsc_fMogaDeadZone)
			{
				uInput	|= IK_PAD_DOWN;
			}

			if (fX <= -gsc_fMogaDeadZone)
			{
				uInput	|= IK_PAD_LEFT;
			}

			else if (fX >= gsc_fMogaDeadZone)
			{
				uInput	|= IK_PAD_RIGHT;
			}
		}
	}

	return	uInput;
}

ENDNAMESPACE
