// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdlib.h>
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
	m_pJoystick(NULL),
	m_bExit(false),
	m_bJoystickAttached(false),
	m_b4Way(false),
	m_bHasAxis(false),
	m_bHasPOV(false),
	m_iJoystickButtons(0),
	m_iDeadZone(16384),
	m_uCurrentInput(0),
	m_uLastInput(0),
	m_iKeyUp(SDL_SCANCODE_UP),
	m_iKeyDown(SDL_SCANCODE_DOWN),
	m_iKeyLeft(SDL_SCANCODE_LEFT),
	m_iKeyRight(SDL_SCANCODE_RIGHT),
	m_iKeyA(SDL_SCANCODE_Z),
	m_iKeyB(SDL_SCANCODE_X),
	m_iKeyX(SDL_SCANCODE_C),
	m_iKeyY(SDL_SCANCODE_V),
	m_iKeyL(SDL_SCANCODE_Q),
	m_iKeyR(SDL_SCANCODE_E),
	m_iSelectKey(SDL_SCANCODE_TAB),
	m_iStartKey(SDL_SCANCODE_SPACE),
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

bool Input::initializeKeyboard()
{
	return	true;
}

void Input::releaseKeyboard()
{
}

bool Input::updateKeyboard()
{
	int	iCount;

	const uint8_t*	pKeys	= SDL_GetKeyboardState(&iCount);
	
	if (true == m_b4Way)
	{
		if (1 == pKeys[m_iKeyUp])
		{
			m_uCurrentInput	|= IK_PAD_UP;
		}

		else if (1 == pKeys[m_iKeyDown])
		{
			m_uCurrentInput	|= IK_PAD_DOWN;
		}

		else if (1 == pKeys[m_iKeyLeft])
		{
			m_uCurrentInput	|= IK_PAD_LEFT;
		}

		else if (1 == pKeys[m_iKeyRight])
		{
			m_uCurrentInput	|= IK_PAD_RIGHT;
		}
	}
			
	else
	{
		if (1 == pKeys[m_iKeyUp])
		{
			m_uCurrentInput	|= IK_PAD_UP;
		}

		else if (1 == pKeys[m_iKeyDown])
		{
			m_uCurrentInput	|= IK_PAD_DOWN;
		}

		if (1 == pKeys[m_iKeyLeft])
		{
			m_uCurrentInput	|= IK_PAD_LEFT;
		}

		else if (1 == pKeys[m_iKeyRight])
		{
			m_uCurrentInput	|= IK_PAD_RIGHT;
		}
	}

	if (1 == pKeys[m_iKeyA])
	{
		m_uCurrentInput	|= IK_A;
	}

	if (1 == pKeys[m_iKeyB])
	{
		m_uCurrentInput	|= IK_B;
	}
		
	if (1 == pKeys[m_iKeyX])
	{
		m_uCurrentInput	|= IK_X;
	}

	if (1 == pKeys[m_iKeyY])
	{
		m_uCurrentInput	|= IK_Y;
	}
		
	if (1 == pKeys[m_iKeyL])
	{
		m_uCurrentInput	|= IK_L;
	}

	if (1 == pKeys[m_iKeyR])
	{
		m_uCurrentInput	|= IK_R;
	}
		
	if (1 == pKeys[m_iStartKey])
	{
		m_uCurrentInput	|= IK_START;
	}

	if (1 == pKeys[m_iSelectKey])
	{
		m_uCurrentInput	|= IK_SELECT;
	}

	return	true;
}

bool Input::initializeJoystick()
{
	int	iJoysticks	= SDL_NumJoysticks();

	for (int iLoop = 0; iLoop < iJoysticks; ++iLoop)
	{
		m_pJoystick	= SDL_JoystickOpen(iLoop);

		if (m_pJoystick != NULL)
		{
			SDL_JoystickGUID	Guid	= SDL_JoystickGetGUID(m_pJoystick);
	
			// Find gampad ID
			uint32_t	uGamePad	= (Guid.data[3] << 24) | (Guid.data[2] << 16) | (Guid.data[1] << 8) | Guid.data[0];

			setupButtons(uGamePad);

			m_bJoystickAttached	= true;

			break;
		}
	}

	return	true;
}

void Input::releaseJoystick()
{
	if (m_pJoystick != NULL)
	{
		SDL_JoystickClose(m_pJoystick);

		m_pJoystick	= NULL;
	}
}

bool Input::updateJoystick()
{
	SDL_JoystickUpdate();

	if (m_pJoystick != NULL && SDL_TRUE == SDL_JoystickGetAttached(m_pJoystick))
	{
		if (true == m_bHasAxis)
		{
			int	iJoystickX	= SDL_JoystickGetAxis(m_pJoystick, 0);
			int	iJoystickY	= SDL_JoystickGetAxis(m_pJoystick, 1);

			int	iX	= iJoystickX;
			
			if (iX < 0)
			{
				iX	= -iX;
			}
			
			int	iY	= iJoystickY;
			
			if (iY < 0)
			{
				iY	= -iY;
			}
			
			if (false == m_b4Way)
			{
				if (iJoystickX <= -m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (iJoystickX >= m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}

				if (iJoystickY <= -m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
				
				else if (iJoystickY >= m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}
			
			else if (iX > iY)
			{
				if (iJoystickX <= -m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_LEFT;
				}

				else if (iJoystickX >= m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_RIGHT;
				}
			}
			
			else
			{
				if (iJoystickY <= -m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_UP;
				}
				
				else if (iJoystickY >= m_iDeadZone)
				{
					m_uCurrentInput	|= IK_PAD_DOWN;
				}
			}
		}

		if (true == m_bHasPOV)
		{		
			uint8_t	uPosition	= SDL_JoystickGetHat(m_pJoystick, 0);

			switch (uPosition)
			{
				case SDL_HAT_LEFTUP:
					m_uCurrentInput	|= IK_PAD_LEFT;
					
					if (false == m_b4Way)
					{
						m_uCurrentInput	|= IK_PAD_UP;
					}

					break;

				case SDL_HAT_LEFT:
					m_uCurrentInput	|= IK_PAD_LEFT;
	
					break;

				case SDL_HAT_LEFTDOWN:
					m_uCurrentInput	|= IK_PAD_LEFT;
			
					if (false == m_b4Way)
					{
						m_uCurrentInput	|= IK_PAD_DOWN;
					}
	
					break;

				case SDL_HAT_RIGHTUP:
					m_uCurrentInput	|= IK_PAD_RIGHT;

					if (false == m_b4Way)
					{
						m_uCurrentInput	|= IK_PAD_UP;
					}

					break;

				case SDL_HAT_RIGHT:
					m_uCurrentInput	|= IK_PAD_RIGHT;
	
					break;

				case SDL_HAT_RIGHTDOWN:
					m_uCurrentInput	|= IK_PAD_RIGHT;

					if (false == m_b4Way)
					{
						m_uCurrentInput	|= IK_PAD_DOWN;
					}
	
					break;

				case SDL_HAT_UP:
					m_uCurrentInput	|= IK_PAD_UP;
	
					break;

				case SDL_HAT_DOWN:
					m_uCurrentInput	|= IK_PAD_DOWN;
	
					break;
			}
		}
	}

	if (m_iButtonA != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonA))
	{
		m_uCurrentInput	|= IK_A;
	}

	if (m_iButtonB != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonB))
	{
		m_uCurrentInput	|= IK_B;
	}

	if (m_iButtonX != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonX))
	{
		m_uCurrentInput	|= IK_X;
	}

	if (m_iButtonY != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonY))
	{
		m_uCurrentInput	|= IK_Y;
	}

	if (m_iButtonL != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonL))
	{
		m_uCurrentInput	|= IK_L;
	}

	if (m_iButtonR != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iButtonR))
	{
		m_uCurrentInput	|= IK_R;
	}

	if (m_iStartButton != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iStartButton))
	{
		m_uCurrentInput	|= IK_START;
	}

	if (m_iSelectButton != -1 && 1 == SDL_JoystickGetButton(m_pJoystick, m_iSelectButton))
	{
		m_uCurrentInput	|= IK_SELECT;
	}

	return	true;
}

bool Input::setupButtons(uint32_t _uGamePad)
{
	m_iJoystickButtons	= SDL_JoystickNumButtons(m_pJoystick);
	
	if (SDL_JoystickNumAxes(m_pJoystick) > 1)
	{
		m_bHasAxis	= true;
	}

	else
	{
		m_bHasAxis	= false;
	}

	if (SDL_JoystickNumHats(m_pJoystick) > 0)
	{
		m_bHasPOV	= true;
	}

	else
	{
		m_bHasPOV	= false;
	}

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
	char	szFilename[FILENAME_MAX];

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
