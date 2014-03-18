// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinyXML2/tinyxml2.h>

#include "File.h"
#include "IDisplay.h"
#include "Input.h"
#include "Joypad.h"
#include "JoystickGUIDs.h"
#include "Log.h"
#include "PathDefines.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

#pragma comment(lib, "dinput8.lib")

NAMESPACE(SPlay)

// Controls
static const char*	gsc_szControls[]	= 
{
	"JoypadUp",
	"JoypadDown",
	"JoypadLeft",
	"JoypadRight",
	"AButton",
	"BButton",
	"XButton",
	"YButton",
	"LButton",
	"RButton",
	"SelectButton",
	"StartButton"
};

// Number of control strings
static const int	gsc_iControlCount	= (sizeof(gsc_szControls) / sizeof(char*));

Input::Input()	:
	m_pDirectInput8(NULL),
	m_pKeyboardDevice(NULL),
	m_pJoystickDevice(NULL),
	m_bExit(false),
	m_bJoystickAttached(false),
	m_b4Way(false),
	m_bHasAxis(false),
	m_bHasPOV(false),
	m_iJoystickButtons(0),
	m_iDeadZone(16384),
	m_uCurrentInput(0),
	m_uLastInput(0),
	m_iKeyUp(DIK_UP),
	m_iKeyDown(DIK_DOWN),
	m_iKeyLeft(DIK_LEFT),
	m_iKeyRight(DIK_RIGHT),
	m_iKeyA(DIK_Z),
	m_iKeyB(DIK_X),
	m_iKeyX(DIK_C),
	m_iKeyY(DIK_V),
	m_iKeyL(DIK_Q),
	m_iKeyR(DIK_E),
	m_iSelectKey(DIK_TAB),
	m_iStartKey(DIK_SPACE),
	m_iButtonA(-1),
	m_iButtonB(-1),
	m_iButtonX(-1),
	m_iButtonY(-1),
	m_iButtonL(-1),
	m_iButtonR(-1),
	m_iStartButton(-1),
	m_iSelectButton(-1),
	m_uGamePad(0xFFFFFFFF)
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

	HRESULT	hResult	= DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput8, NULL);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Unable to get DirectInput8 object (%08X)", hResult);
		
		return	false;
	}

	if (false == initializeKeyboard())
	{
		return	false;
	}

	if (false == initializeJoystick())
	{
		return	false;
	}

	// Load input config (Config.xml)
	loadXML();

	return	true;
}

void Input::close()
{
	releaseKeyboard();
	releaseJoystick();

	SAFE_RELEASE(m_pDirectInput8);
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
	releaseJoystick();

	initializeJoystick();
}

BOOL Input::foundJoystick(const DIDEVICEINSTANCE* _pInstance, void* _pContext)
{
	LPDIRECTINPUTDEVICE8	pJoystickDevice;
	
	HRESULT	hResult	= m_pDirectInput8->CreateDevice(_pInstance->guidInstance, &pJoystickDevice, NULL);
		
	if (FAILED(hResult) || false == setupButtons(_pInstance->guidProduct.Data1))
	{
		return	DIENUM_CONTINUE;
	}

	m_pJoystickDevice	= pJoystickDevice;

	return	DIENUM_STOP;
}

BOOL CALLBACK Input::joystickFoundCallback(const DIDEVICEINSTANCE* _pInstance, void* _pContext)
{
	Input*	pInput	= reinterpret_cast<Input*>(_pContext);

	return	pInput->foundJoystick(_pInstance, _pContext);
}

bool Input::initializeKeyboard()
{
	HRESULT	hResult	= m_pDirectInput8->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, NULL);
		
	if (FAILED(hResult))
	{
		Log::instance()->logError("Unable to create keyboard device (%08X)", hResult);
		
		return	false;
	}

	hResult	= m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Unable to set keyboard data format (%08X)", hResult);
		
		return	false;
	}

	hResult	= m_pKeyboardDevice->SetCooperativeLevel(Platform::getWindow()->getHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Unable to set keyboard cooperative level (%08X)", hResult);
		
		return	false;
	}

	hResult	= DIERR_INPUTLOST;

	while (DIERR_INPUTLOST == hResult)
	{
		hResult	= m_pKeyboardDevice->Acquire();

		if (FAILED(hResult))
		{
			Log::instance()->logError("Unable to acquire keyboard (%08X)", hResult);
		
			return	false;
		}
	}

	return	true;
}

void Input::releaseKeyboard()
{
	if (m_pKeyboardDevice != NULL)
	{
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();

		m_pKeyboardDevice	= NULL;
	}
}

bool Input::updateKeyboard()
{
	HRESULT	hResult	= m_pKeyboardDevice->Poll();

	if (FAILED(hResult))
	{
		hResult	= DIERR_INPUTLOST;

		while (DIERR_INPUTLOST == hResult)
		{
			hResult	= m_pKeyboardDevice->Acquire();
		}
	}

	if (SUCCEEDED(hResult))
	{
		hResult	= m_pKeyboardDevice->GetDeviceState(msc_iKeyCount, m_bKeys);

		if (SUCCEEDED(hResult))
		{
			if (true == m_b4Way)
			{
				if (0x80 == (m_bKeys[m_iKeyUp] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}

				else if (0x80 == (m_bKeys[m_iKeyDown] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}

				else if (0x80 == (m_bKeys[m_iKeyLeft] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (0x80 == (m_bKeys[m_iKeyRight] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}
			}
			
			else
			{
				if (0x80 == (m_bKeys[m_iKeyUp] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}

				else if (0x80 == (m_bKeys[m_iKeyDown] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}

				if (0x80 == (m_bKeys[m_iKeyLeft] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (0x80 == (m_bKeys[m_iKeyRight] & 0x80))
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}
			}

			if (0x80 == (m_bKeys[m_iKeyA] & 0x80))
			{
				m_uCurrentInput	|= IK_A;
			}

			if (0x80 == (m_bKeys[m_iKeyB] & 0x80))
			{
				m_uCurrentInput	|= IK_B;
			}
		
			if (0x80 == (m_bKeys[m_iKeyX] & 0x80))
			{
				m_uCurrentInput	|= IK_X;
			}

			if (0x80 == (m_bKeys[m_iKeyY] & 0x80))
			{
				m_uCurrentInput	|= IK_Y;
			}
		
			if (0x80 == (m_bKeys[m_iKeyL] & 0x80))
			{
				m_uCurrentInput	|= IK_L;
			}

			if (0x80 == (m_bKeys[m_iKeyR] & 0x80))
			{
				m_uCurrentInput	|= IK_R;
			}
		
			if (0x80 == (m_bKeys[m_iStartKey] & 0x80))
			{
				m_uCurrentInput	|= IK_START;
			}

			if (0x80 == (m_bKeys[m_iSelectKey] & 0x80))
			{
				m_uCurrentInput	|= IK_SELECT;
			}
		}
	}

	return	true;
}

bool Input::initializeJoystick()
{
	m_bJoystickAttached	= false;
	m_iJoystickButtons	= 0;
	
	HRESULT	hResult	= m_pDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, joystickFoundCallback, static_cast<void*>(this), DIEDFL_ATTACHEDONLY);

	// Don't return an error
	if (FAILED(hResult))
	{
		return	true;
	}

	if (m_pJoystickDevice != NULL)
	{
		DIDEVCAPS	devCaps;
		
		hResult	= m_pJoystickDevice->SetDataFormat(&c_dfDIJoystick2);

		if (FAILED(hResult))
		{
			Log::instance()->logError("Unable to set joystick data format (%08X)", hResult);
		
			return	false;
		}

		memset(&devCaps, 0, sizeof(DIDEVCAPS));
		
		devCaps.dwSize	= sizeof(DIDEVCAPS);
		
		hResult	= m_pJoystickDevice->GetCapabilities(&devCaps);
		
		if (FAILED(hResult))
		{
			Log::instance()->logError("Unable to get joystick capabilities (%08X)", hResult);
		
			return	false;
		}

		m_iJoystickButtons	= devCaps.dwButtons;
		
		if (devCaps.dwAxes >= 2)
		{
			m_bHasAxis	= true;
		}
		
		else
		{
			m_bHasAxis	= false;
		}
		
		if (devCaps.dwPOVs >= 1)
		{
			m_bHasPOV	= true;
		}
		
		else
		{
			m_bHasPOV	= false;
		}
		
		hResult	= m_pJoystickDevice->SetCooperativeLevel(Platform::getWindow()->getHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		if (FAILED(hResult))
		{
			Log::instance()->logError("Unable to set joystick cooperative level (%08X)", hResult);
		
			return	false;
		}

		hResult	= DIERR_INPUTLOST;

		while (DIERR_INPUTLOST == hResult)
		{
			hResult	= m_pJoystickDevice->Acquire();
		}

		m_bJoystickAttached	= true;
	}

	return	true;
}

void Input::releaseJoystick()
{
	if (m_pJoystickDevice != NULL)
	{
		m_pJoystickDevice->Unacquire();
		m_pJoystickDevice->Release();
		
		m_pJoystickDevice	= NULL;
	}
}

bool Input::updateJoystick()
{
	HRESULT	hResult	= m_pJoystickDevice->Poll();

	if (FAILED(hResult))
	{
		hResult	= DIERR_INPUTLOST;

		while (DIERR_INPUTLOST == hResult)
		{
			hResult	= m_pJoystickDevice->Acquire();
		}
	}

	if (SUCCEEDED(hResult))
	{
		DIJOYSTATE2	joystickState;

		hResult	= m_pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE2), &joystickState);

		if (true == m_bHasAxis)
		{
			int	iX	= joystickState.lX - 32768;
			
			if (iX < 0)
			{
				iX	= -iX;
			}
			
			int	iY	= joystickState.lY - 32768;
			
			if (iY < 0)
			{
				iY	= -iY;
			}
			
			if (false == m_b4Way)
			{
				if (joystickState.lX <= 32768 - m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (joystickState.lX >= 32768 + m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}

				if (joystickState.lY <= 32768 - m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
				
				else if (joystickState.lY >= 32768 + m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}
			
			else if (iX > iY)
			{
				if (joystickState.lX <= 32768 - m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (joystickState.lX >= 32768 + m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}
			}
			
			else
			{
				if (joystickState.lY <= 32768 - m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
				
				else if (joystickState.lY >= 32768 + m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}
		}
					
		if (true == m_bHasPOV)
		{		
			if (false == m_b4Way)
			{
				if (joystickState.rgdwPOV[0] >= 22500 && joystickState.rgdwPOV[0] <= 31500)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}
		
				else if (joystickState.rgdwPOV[0] >= 4500 && joystickState.rgdwPOV[0] <= 13500)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}

				if ((joystickState.rgdwPOV[0] >= 31500 && joystickState.rgdwPOV[0] < 36000) || joystickState.rgdwPOV[0] <= 4500)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
			
				else if (joystickState.rgdwPOV[0] >= 13500 && joystickState.rgdwPOV[0] <= 22500)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}

			else
			{
				if (joystickState.rgdwPOV[0] >= 22500 && joystickState.rgdwPOV[0] <= 31500)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}
		
				else if (joystickState.rgdwPOV[0] >= 4500 && joystickState.rgdwPOV[0] <= 13500)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}

				else if ((joystickState.rgdwPOV[0] >= 31500 && joystickState.rgdwPOV[0] < 36000) || joystickState.rgdwPOV[0] <= 4500)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
			
				else if (joystickState.rgdwPOV[0] >= 13500 && joystickState.rgdwPOV[0] <= 22500)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}
		}

		if (m_iButtonA != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonA] & 0x80))
		{
			m_uCurrentInput	|= IK_A;
		}

		if (m_iButtonB != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonB] & 0x80))
		{
			m_uCurrentInput	|= IK_B;
		}

		if (m_iButtonX != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonX] & 0x80))
		{
			m_uCurrentInput	|= IK_X;
		}

		if (m_iButtonY != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonY] & 0x80))
		{
			m_uCurrentInput	|= IK_Y;
		}

		if (m_iButtonL != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonL] & 0x80))
		{
			m_uCurrentInput	|= IK_L;
		}

		if (m_iButtonR != -1 && 0x80 == (joystickState.rgbButtons[m_iButtonR] & 0x80))
		{
			m_uCurrentInput	|= IK_R;
		}

		if (m_iStartButton != -1 && 0x80 == (joystickState.rgbButtons[m_iStartButton] & 0x80))
		{
			m_uCurrentInput	|= IK_START;
		}

		if (m_iSelectButton != -1 && 0x80 == (joystickState.rgbButtons[m_iSelectButton] & 0x80))
		{
			m_uCurrentInput	|= IK_SELECT;
		}
	}

	return	true;
}

bool Input::setupButtons(uint32_t _uGamePad)
{
	m_uGamePad	= _uGamePad;

	int	t_c	= sizeof(gsc_joysticks) / sizeof(JoystickDefine);
	
	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (_uGamePad == gsc_joysticks[iLoop].eGamePad)
		{
			if (-1 == m_iButtonA)
			{
				m_iButtonA	= gsc_joysticks[iLoop].m_iButtonA;
			}

			if (-1 == m_iButtonB)
			{
				m_iButtonB	= gsc_joysticks[iLoop].m_iButtonB;
			}

			if (-1 == m_iButtonX)
			{
				m_iButtonX	= gsc_joysticks[iLoop].m_iButtonX;
			}

			if (-1 == m_iButtonY)
			{
				m_iButtonY	= gsc_joysticks[iLoop].m_iButtonY;
			}

			if (-1 == m_iButtonL)
			{
				m_iButtonL	= gsc_joysticks[iLoop].m_iButtonL;
			}

			if (-1 == m_iButtonR)
			{
				m_iButtonR	= gsc_joysticks[iLoop].m_iButtonR;
			}

			if (-1 == m_iSelectButton)
			{
				m_iSelectButton	= gsc_joysticks[iLoop].m_iSelectButton;
			}

			if (-1 == m_iStartButton)
			{
				m_iStartButton	= gsc_joysticks[iLoop].m_iStartButton;
			}
		
			return	true;
		}
	}	

	// Map to XInput
	if (-1 == m_iButtonA)
	{
		m_iButtonA	= 1;
	}

	if (-1 == m_iButtonB)
	{
		m_iButtonB	= 0;
	}

	if (-1 == m_iButtonX)
	{
		m_iButtonX	= 3;
	}

	if (-1 == m_iButtonY)
	{
		m_iButtonY	= 2;
	}

	if (-1 == m_iButtonL)
	{
		m_iButtonL	= 4;
	}

	if (-1 == m_iButtonR)
	{
		m_iButtonR	= 5;
	}

	if (-1 == m_iSelectButton)
	{
		m_iSelectButton	= 6;
	}

	if (-1 == m_iStartButton)
	{
		m_iStartButton	= 7;
	}

	return	true;
}

void Input::loadXML()
{
	char	szFilename[MAX_PATH];

	sprintf_s(szFilename, "Config%08X.xml", m_uGamePad);

	xml::XMLDocument*	xmlDocument	= new xml::XMLDocument();
	
	if (xml::XML_NO_ERROR == xmlDocument->LoadFile(szFilename))
	{
		xml::XMLNode*	xmlFirstNode	= xmlDocument->FirstChild();
	
		if (NULL == xmlFirstNode)
		{
			return;
		}

		while (xmlFirstNode != NULL)
		{
			tinystl::string	strElementName	= xmlFirstNode->Value();

			xml::XMLNode*	pTextNode	= xmlFirstNode->FirstChild();
		
			if (pTextNode != NULL)
			{
				int	iValue	= strtol(pTextNode->Value(), NULL, 10);

				for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
				{
					tinystl::string	strName	= gsc_szControls[iLoop];

					if (strName == strElementName)
					{
						switch (iLoop)
						{
							// Ignore direction input
							case 0:
								if (iValue < 0x0100)
								{
									m_iKeyUp	= iValue;
								}
												
								break;

							case 1:
								if (iValue < 0x0100)
								{
									m_iKeyDown	= iValue;
								}
												
								break;

							case 2:
								if (iValue < 0x0100)
								{
									m_iKeyLeft	= iValue;
								}
												
								break;

							case 3:
								if (iValue < 0x0100)
								{
									m_iKeyRight	= iValue;
								}
												
								break;

							case 4:
								if (iValue < 0x0100)
								{
									m_iKeyA	= iValue;
								}
						
								else
								{
									m_iButtonA	= iValue & 0xFF;
								}

								break;

							case 5:
								if (iValue < 0x0100)
								{
									m_iKeyB	= iValue;
								}
						
								else
								{
									m_iButtonB	= iValue & 0xFF;
								}

								break;

							case 6:
								if (iValue < 0x0100)
								{
									m_iKeyX	= iValue;
								}
						
								else
								{
									m_iButtonX	= iValue & 0xFF;
								}

								break;

							case 7:
								if (iValue < 0x0100)
								{
									m_iKeyY	= iValue;
								}
						
								else
								{
									m_iButtonY	= iValue & 0xFF;
								}

								break;

							case 8:
								if (iValue < 0x0100)
								{
									m_iKeyL	= iValue;
								}
						
								else
								{
									m_iButtonL	= iValue & 0xFF;
								}

								break;

							case 9:
								if (iValue < 0x0100)
								{
									m_iKeyR	= iValue;
								}
						
								else
								{
									m_iButtonR	= iValue & 0xFF;
								}

								break;

							case 10:
								if (iValue < 0x0100)
								{
									m_iSelectKey	= iValue;
								}
						
								else
								{
									m_iSelectButton	= iValue & 0xFF;
								}

								break;

							case 11:
								if (iValue < 0x0100)
								{
									m_iStartKey	= iValue;
								}
						
								else
								{
									m_iStartButton	= iValue & 0xFF;
								}

								break;
						}
			
						break;
					}
				}
			}
		
			xmlFirstNode	= xmlFirstNode->NextSibling();
		}
	}

	delete	xmlDocument;
}

ENDNAMESPACE
