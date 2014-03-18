// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <algorithm>
#include <process.h>
#include <stddef.h>
#include <windows.h>
#include <TinyXML2/tinyxml2.h>

#include "AssertLog.h"
#include "Config.h"
#include "DuiUtilities.h"
#include "File.h"
#include "Log.h"
#include "PathDefines.h"

#ifdef _DEBUG
#pragma comment(lib, "DuiLIb_d.lib")
#else
#pragma comment(lib, "DuiLIb.lib")
#endif

#pragma comment(lib, "comctl32.lib")

// Timer id
static const int	gsc_iTimerID	= 0x07201970;

// Control names
static const char*	gsc_szControlList	= "ControlList";

// Controls
static const char*	gsc_szControls[]	= 
{
	"Joypad Up",
	"Joypad Down",
	"Joypad Left",
	"Joypad Right",
	"A Button",
	"B Button",
	"X Button",
	"Y Button",
	"L Button",
	"R Button",
	"Select Button",
	"Start Button"
};

// Number of control strings
static const int	gsc_iControlCount	= (sizeof(gsc_szControls) / sizeof(char*));

DUI_BEGIN_MESSAGE_MAP(Config, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMSELECT, OnItemSelect)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_KILLFOCUS, OnKillFocus)
DUI_END_MESSAGE_MAP()

Config::Config()
{
}

Config::~Config()
{
	close();
}

ConfigPtr Config::create()
{
	ConfigPtr	pConfig(new Config());

	if (false == pConfig->initialize())
	{
		pConfig.reset();

		pConfig	= nullptr;
	}

	return	pConfig;
}

bool Config::initialize()
{
    CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
    
    HRESULT	hResult	= CoInitialize(NULL);

    if (FAILED(hResult))
	{
		return	false;
	}

	return	true;
}

void Config::close()
{
    CoUninitialize();
}

bool Config::show()
{
	Create(NULL, _T("Joypad Config"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
    CenterWindow();

    ShowWindow(true);

	if (false == setupInput())
	{
		return	false;
	}

	SetTimer(m_hWnd, gsc_iTimerID, 33, NULL);

	CPaintManagerUI::MessageLoop();

	KillTimer(m_hWnd, gsc_iTimerID);

	CPaintManagerUI::Term();

	return	true;
}

LPCTSTR Config::GetWindowClassName() const
{
	return	_T("SPWindow");
}

void Config::InitWindow()
{
}

void Config::OnFinalMessage(HWND _hWnd)
{
};

void Config::input(int _iKeycode)
{
	if (GetActiveWindow() != m_hWnd)
	{
		int	iInput	= getInputFromButton(_iKeycode);

		if (iInput != -1 && m_pWindow != nullptr)
		{
			m_pWindow->setInput(iInput);
		}
	}

	else
	{
		std::string strName	= m_pInput->getKeyName(_iKeycode);

		if (strName.length() > 0)
		{
			CListUI*	pControlList	= reinterpret_cast<CListUI*>(m_PaintManager.FindControl(gsc_szControlList));

			if (pControlList != NULL)
			{
				int	iSelection	= pControlList->GetCurSel();

				if (iSelection >= 0 && iSelection < static_cast<int>(m_vecButtonConfigs.size()))
				{
					m_vecButtonConfigs[iSelection]	= _iKeycode;

					CListTextElementUI*	pItem	= static_cast<CListTextElementUI*>(pControlList->GetItemAt(iSelection));

					if (pItem != NULL)
					{
						pItem->SetText(1, strName.c_str());
					}
				}
			}
		}
	}
}

void Config::OnClick(TNotifyUI& _msg)
{
	CDuiString	strControlName	= _msg.pSender->GetName();

	// Save
	if (strControlName == "ButtonSave")
	{
		if (true == saveConfig())
		{
			Close();
		}
	}

	// Test
	if (strControlName == "ButtonTest")
	{
		testConfig();
	}

	// Exit
	else if (strControlName == "ButtonExit")
	{
		Close();
	}
}

void Config::OnItemSelect(TNotifyUI& _msg)
{
}

void Config::OnSelectChanged(TNotifyUI& _msg)
{
}

void Config::OnKillFocus(TNotifyUI& _msg)
{
}

LRESULT Config::HandleMessage(UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);

			break;
		
		case WM_ERASEBKGND:
			return	1;
	
		case WM_KEYDOWN:
			switch (_wParam)
			{
				case VK_UP:
				case VK_DOWN:
				case VK_LEFT:
				case VK_RIGHT:
				case VK_HOME:
				case VK_END:
				case VK_LWIN:
				case VK_RWIN:
					return	TRUE;
			}

			break;
		case WM_TIMER:
			if (gsc_iTimerID == _wParam)
			{
				m_pInput->update();
			}

			break;
	}

	return	__super::HandleMessage(_uMsg, _wParam, _lParam);
}

CDuiString Config::GetSkinFile()
{
	return	_T("JoypadConfig.xml");
}

CDuiString Config::GetSkinFolder()
{
	return	_T("UI");
}

bool Config::saveConfig()
{
	uint32_t uGamepadID	= m_pInput->getGamepadID();

	char	szFilename[MAX_PATH];

	sprintf_s(szFilename, "Config%08X.xml", uGamepadID);

	File*	pFile	= new File();

	if (false == pFile->create(szFilename, false))
	{
		delete	pFile;

		return	false;
	}

	for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
	{
		if (m_vecButtonConfigs[iLoop] >= 0)
		{
			std::string	strName	= gsc_szControls[iLoop];

			strName.erase(std::remove_if(strName.begin(), strName.end(), isspace), strName.end());

			char	szString[256];

			sprintf_s(szString, "<%s>%d</%s>\n", strName.c_str(), m_vecButtonConfigs[iLoop], strName.c_str());

			if (false == pFile->writeString(szString))
			{
				delete	pFile;

				return false;
			}
		}
	}

	pFile->close();

	delete	pFile;

	return	true;
}

void Config::testConfig()
{
	ShowWindow(false, false);

	m_pWindow	= Window::create();
		
	if (m_pWindow != nullptr)
	{
		m_pWindow->run();

		m_pWindow.reset();
	}

	ShowWindow(true, true);
}

void Config::setupControls()
{
	CListUI*	pControlList	= reinterpret_cast<CListUI*>(m_PaintManager.FindControl(gsc_szControlList));

	if (pControlList != NULL)
	{
		pControlList->SetName("ListContainer");
		pControlList->RemoveAll();

		for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
		{
			// Create list label element
			CListTextElementUI*	pElement	= new CListTextElementUI();

			pControlList->Add(pElement);

			pElement->SetTag(iLoop);
			pElement->SetText(0, gsc_szControls[iLoop]);
			
			if (-1 == m_vecButtonConfigs[iLoop])
			{
				m_vecButtonConfigs[iLoop]	= m_pInput->getPreloadedButton(iLoop);

				if (-1 == m_vecButtonConfigs[iLoop])
				{
					pElement->SetText(1, "Not Set");
				}
			}

			if (m_vecButtonConfigs[iLoop] != -1)
			{
				pElement->SetText(1, m_pInput->getKeyName(m_vecButtonConfigs[iLoop]).c_str());
			}

			char	szToolTip[64];

			sprintf_s(szToolTip, "Click to configure %s.", gsc_szControls[iLoop]);
			
			pElement->SetToolTip(szToolTip);
		}

		pControlList->SelectItem(0);
	}
}

bool Config::setupInput()
{
	m_pInput	= Input::create(m_hWnd, this);

	if (nullptr == m_pInput)
	{
		return	false;
	}

	if (false == loadXML())
	{
		return	false;
	}

	setupControls();

	return	true;
}


bool Config::loadXML()
{
	m_vecButtonConfigs.resize(gsc_iControlCount);

	for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
	{
		m_vecButtonConfigs[iLoop]	= -1;
	}

	uint32_t uGamepadID	= m_pInput->getGamepadID();

	char	szFilename[MAX_PATH];

	sprintf_s(szFilename, "Config%08X.xml", uGamepadID);

	xml::XMLDocument*	xmlDocument	= new xml::XMLDocument();
	
	if (xml::XML_NO_ERROR == xmlDocument->LoadFile(szFilename))
	{
		xml::XMLNode*	xmlFirstNode	= xmlDocument->FirstChild();
	
		if (NULL == xmlFirstNode)
		{
			return	true;
		}

		while (xmlFirstNode != NULL)
		{
			std::string	strElementName	= xmlFirstNode->Value();

			xml::XMLNode*	pTextNode	= xmlFirstNode->FirstChild();
		
			if (pTextNode != NULL)
			{
				int	iValue	= strtol(pTextNode->Value(), NULL, 10);

				for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
				{
					std::string	strName	= gsc_szControls[iLoop];

					strName.erase(std::remove_if(strName.begin(), strName.end(), isspace), strName.end());

					if (strName == strElementName)
					{
						m_vecButtonConfigs[iLoop]	= iValue;
					}
				}
			}
		
			xmlFirstNode	= xmlFirstNode->NextSibling();
		}
	}

	delete	xmlDocument;

	return	true;
}

int	Config::getInputFromButton(int _iButton)
{
	for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
	{
		if (m_vecButtonConfigs[iLoop] == _iButton)
		{
			return	iLoop;
		}
	}

	return	-1;
}
