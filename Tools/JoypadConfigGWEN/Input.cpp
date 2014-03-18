// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "Config.h"
#include "Input.h"
#include "Log.h"
#include "..\..\PlatformLib\Include\JoystickGUIDs.h"

#pragma comment(lib, "dinput8.lib")

Input::Input(HWND _hWnd, Config* _pConfig)	:
	m_pDirectInput8(NULL),
	m_pKeyboardDevice(NULL),
	m_pJoystickDevice(NULL),
	m_hWnd(_hWnd),
	m_pConfig(_pConfig),
	m_bJoystickAttached(false),
	m_bHasAxis(false),
	m_bHasPOV(false),
	m_iJoystickButtons(0),
	m_iDeadZone(16384),
	m_iButtonA(-1),
	m_iButtonB(-1),
	m_iButtonX(-1),
	m_iButtonY(-1),
	m_iButtonL(-1),
	m_iButtonR(-1),
	m_iSelectButton(-1),
	m_iStartButton(-1),
	m_uGamePad(0xFFFFFFFF)
{
}

Input::~Input()
{
	close();
}

InputPtr Input::create(HWND _hWnd, Config* _pConfig)
{
	InputPtr	pInput(new Input(_hWnd, _pConfig));
	
	if (false == pInput->initialize())
	{
		pInput.reset();
	}

	return	pInput;
}

bool Input::initialize()
{
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
	if (true == m_bJoystickAttached)
	{
		updateJoystick();
	}

	else
	{
		updateKeyboard();
	}

	return	true;
}

std::string Input::getKeyName(int _iKeycode)
{
	char	szKey[256]	= "\0";

	if (_iKeycode >= 0x0100)
	{
		switch (_iKeycode)
		{
			case 0x0180:
				sprintf_s(szKey, "Joystick -Y Axis");

				break;

			case 0x0181:
				sprintf_s(szKey, "Joystick +Y Axis");

				break;

			case 0x0182:
				sprintf_s(szKey, "Joystick -X Axis");

				break;

			case 0x0183:
				sprintf_s(szKey, "Joystick +X Axis");

				break;

			case 0x0184:
				sprintf_s(szKey, "POV -Y Axis");

				break;

			case 0x0185:
				sprintf_s(szKey, "POV +Y Axis");

				break;

			case 0x0186:
				sprintf_s(szKey, "POV -X Axis");

				break;

			case 0x0187:
				sprintf_s(szKey, "POV +X Axis");

				break;

			default:
				sprintf_s(szKey, "Joystick Button %d", _iKeycode - 0x0100);
		}
	}

	else
	{
		DIPROPSTRING	propString;

		propString.diph.dwSize			= sizeof(DIPROPSTRING);
		propString.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		propString.diph.dwObj			= _iKeycode;
		propString.diph.dwHow			= DIPH_BYOFFSET;

		HRESULT	hResult	= m_pKeyboardDevice->GetProperty(DIPROP_KEYNAME, &propString.diph);

		if (SUCCEEDED(hResult))
		{
			WideCharToMultiByte(CP_ACP, 0, propString.wsz, -1, szKey, sizeof(szKey), NULL, NULL);
		}
	}

	return	szKey;
}

int Input::getPreloadedButton(int _iIindex)
{
	if (false == m_bJoystickAttached)
	{
		switch (_iIindex)
		{
			case 0:
				return	DIK_UP;

			case 1:
				return	DIK_DOWN;

			case 2:
				return	DIK_LEFT;

			case 3:
				return	DIK_RIGHT;

			case 4:
				return	DIK_Z;

			case 5:
				return	DIK_X;

			case 6:
				return	DIK_C;

			case 7:
				return	DIK_V;

			case 8:
				return	DIK_Q;

			case 9:
				return	DIK_E;

			case 10:
				return	DIK_TAB;

			case 11:
				return	DIK_SPACE;
		}
	}

	else
	{
		switch (_iIindex)
		{
			case 0:
				if (true == m_bHasAxis)
				{
					return	0x0180;
				}

				return	0x0184;

			case 1:
				if (true == m_bHasAxis)
				{
					return	0x0181;
				}

				return	0x0185;

			case 2:
				if (true == m_bHasAxis)
				{
					return	0x0182;
				}

				return	0x0186;

			case 3:
				if (true == m_bHasAxis)
				{
					return	0x0183;
				}

				return	0x0187;

			case 4:
				return	0x0100 | m_iButtonA;

			case 5:
				return	0x0100 | m_iButtonB;

			case 6:
				return	0x0100 | m_iButtonX;

			case 7:
				return	0x0100 | m_iButtonY;

			case 8:
				return	0x0100 | m_iButtonL;

			case 9:
				return	0x0100 | m_iButtonR;

			case 10:
				return	0x0100 | m_iSelectButton;

			case 11:
				return	0x0100 | m_iStartButton;
		}
	}

	return	-1;
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
	// Reset all keys
	memset(m_bKeys, 0, msc_iKeyCount);
	memset(m_bLastKeys, 0, msc_iKeyCount);

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

	hResult	= m_pKeyboardDevice->SetCooperativeLevel(m_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

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
		// Keep a backup copy
		memcpy(m_bLastKeys, m_bKeys, msc_iKeyCount);

		m_pKeyboardDevice->GetDeviceState(msc_iKeyCount, m_bKeys);

		for (int iLoop = 0; iLoop < msc_iKeyCount; ++iLoop)
		{
			if ((m_bKeys[iLoop] & 0x80) && m_bKeys[iLoop] != m_bLastKeys[iLoop])
			{ 
				if (m_pConfig != NULL)
				{
					m_pConfig->input(iLoop);
				}
			}
		}
	}

	return	true;
}

bool Input::initializeJoystick()
{
	m_bJoystickAttached	= false;
	m_iJoystickButtons	= 0;
	
	memset(m_bButtons, 0, msc_iButtonCount);
	memset(m_bLastButtons, 0, msc_iButtonCount);

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
		
		hResult	= m_pJoystickDevice->SetCooperativeLevel(m_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

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
	int	iKeyState	= -1;

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
			
			if (iX > iY)
			{
				if (joystickState.lX <= 32768 - m_iDeadZone)
				{
					iKeyState	= 0x0182;
				}

				else if (joystickState.lX >= 32768 + m_iDeadZone)
				{
					iKeyState	= 0x0183;
				}
			}
			
			else
			{
				if (joystickState.lY <= 32768 - m_iDeadZone)
				{
					iKeyState	= 0x0180;
				}
				
				else if (joystickState.lY >= 32768 + m_iDeadZone)
				{
					iKeyState	= 0x0181;
				}
			}
		}
					
		if (-1 == iKeyState && true == m_bHasPOV)
		{		
			if (joystickState.rgdwPOV[0] >= 22500 && joystickState.rgdwPOV[0] <= 31500)
			{
				iKeyState	= 0x0186;
			}
		
			else if (joystickState.rgdwPOV[0] >= 4500 && joystickState.rgdwPOV[0] <= 13500)
			{
				iKeyState	= 0x0187;
			}

			if ((joystickState.rgdwPOV[0] >= 31500 && joystickState.rgdwPOV[0] < 36000) || joystickState.rgdwPOV[0] <= 4500)
			{
				iKeyState	= 0x0184;
			}
			
			else if (joystickState.rgdwPOV[0] >= 13500 && joystickState.rgdwPOV[0] <= 22500)
			{
				iKeyState	= 0x0185;
			}
		}

		if (iKeyState != -1)
		{
			if (m_pConfig != NULL)
			{
				m_pConfig->input(iKeyState);
			}
		}

		else
		{
			memcpy(m_bLastButtons, m_bButtons, m_iJoystickButtons);
			memcpy(m_bButtons, joystickState.rgbButtons, m_iJoystickButtons);

			for (int iLoop = 0; iLoop < msc_iButtonCount; ++iLoop)
			{
				if ((m_bButtons[iLoop] & 0x80) && m_bButtons[iLoop] != m_bLastButtons[iLoop])
				{ 
					if (m_pConfig != NULL)
					{
						m_pConfig->input(0x100 | iLoop);
					}
				}
			}
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
			m_iButtonA		= gsc_joysticks[iLoop].m_iButtonA;
			m_iButtonB		= gsc_joysticks[iLoop].m_iButtonB;
			m_iButtonX		= gsc_joysticks[iLoop].m_iButtonX;
			m_iButtonY		= gsc_joysticks[iLoop].m_iButtonY;
			m_iButtonL		= gsc_joysticks[iLoop].m_iButtonL;
			m_iButtonR		= gsc_joysticks[iLoop].m_iButtonR;
			m_iSelectButton	= gsc_joysticks[iLoop].m_iSelectButton;
			m_iStartButton	= gsc_joysticks[iLoop].m_iStartButton;
		
			return	true;
		}
	}	

	// Map to XInput
	m_iButtonA		= 0x0101;
	m_iButtonB		= 0x0100;
	m_iButtonX		= 0x0103;
	m_iButtonY		= 0x0102;
	m_iButtonL		= 0x0104;
	m_iButtonR		= 0x0105;
	m_iSelectButton	= 0x0106;
	m_iStartButton	= 0x0107;

	return	true;
}
