// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <algorithm>
#include <TinyXML2/tinyxml2.h>

#include "AssertLog.h"
#include "Config.h"
#include "Defines.h"
#include "File.h"
#include "Log.h"
#include "PathDefines.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Input/Windows.h"

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
static const int	gsc_iControlCount		= (sizeof(gsc_szControls) / sizeof(char*));

// Skin file
static const char*	gsc_szSkinFile			= "DefaultSkin.png";

// Gamepad size
static const int	gsc_iGamepadWidth		= 258;
static const int	gsc_iGamepadHeight		= 116;

// Indicator size
static const int	gsc_iIndicatorWidth		= 8;
static const int	gsc_iIndicatorHeight	= 8;

Config::Config()	:
	m_pSkin(NULL),
	m_pDisplay(NULL),
	m_pCanvas(NULL),
	m_pInput(NULL),
	m_pListBox(NULL),
	m_pSaveButton(NULL),
	m_pTestButton(NULL),
	m_pBackButton(NULL),
	m_pGamePad(NULL),
	m_pIndicator(NULL),
	m_bTesting(false)
{
}

Config::~Config()
{
	close();
}

Config* Config::create()
{
	Config*	pConfig	= new Config();

	if (false == pConfig->initialize())
	{
		delete	pConfig;

		pConfig	= NULL;
	}

	return	pConfig;
}

bool Config::initialize()
{
	m_pDisplay	= Display::create();

	if (NULL == m_pDisplay)
	{
		return	false;
	}

	m_pSkin		= new Gwen::Skin::TexturedBase(m_pDisplay->getRenderer());

	m_pCanvas	= new Gwen::Controls::WindowCanvas(-1, -1, gsc_iWindowWidth, gsc_iWindowHeight, m_pSkin, "Joypad Config");

	m_pDisplay->initializeDirectX((HWND)m_pCanvas->GetWindow());

	m_pSkin->Init(gsc_szSkinFile);

	m_pCanvas->SetDrawBackground(true);
	m_pCanvas->SetBackgroundColor(Gwen::Color(57, 66, 100, 255));
	m_pCanvas->SetCanMaximize(false);

	if (false == setupInput())
	{
		return	false;
	}

	return	true;
}

void Config::close()
{
	delete	m_pListBox;

	m_pListBox	= NULL;

	delete	m_pSaveButton;

	m_pSaveButton	= NULL;

	delete	m_pTestButton;

	m_pTestButton	= NULL;

	delete	m_pBackButton;

	m_pBackButton	= NULL;

	delete	m_pGamePad;

	m_pGamePad	= NULL;
	
	delete	m_pIndicator;

	m_pIndicator	= NULL;
	
	delete	m_pCanvas;

	m_pCanvas	= NULL;

	delete	m_pSkin;

	m_pSkin	= NULL;

	// Delete display
	delete	m_pDisplay;

	m_pDisplay	= NULL;
}

void Config::run()
{
	while (false == m_pCanvas->WantsQuit())
	{
		m_pInput->update();

		m_pCanvas->DoThink();
	}
}

void Config::input(int _iKeycode)
{
	if (true == m_bTesting)
	{
		int	iInput	= getInputFromButton(_iKeycode);

		if (iInput != -1)
		{
			m_pIndicator->SetPos(m_vecButtonPositions[iInput].x, m_vecButtonPositions[iInput].y);
			m_pIndicator->Show();
		}
	}

	else
	{	
		std::string strName	= m_pInput->getKeyName(_iKeycode);

		if (strName.length() > 0)
		{
			int	iSelection	= -1;

			Gwen::String	strSelected	= m_pListBox->GetSelectedRowName();
		
			if (strSelected.length() > 0)
			{
				iSelection	= Gwen::Utility::Strings::To::Int(strSelected);
			}

			if (iSelection >= 0 && iSelection < static_cast<int>(m_vecButtonConfigs.size()))
			{
				m_vecButtonConfigs[iSelection]	= _iKeycode;

				Gwen::Controls::Layout::TableRow*	pRow	= m_pListBox->GetSelectedRow();

				pRow->SetCellText(1, strName.c_str());
			}
		}
	}
}

void Config::OnSelection(Gwen::Controls::Base* _pControl)
{
	Gwen::String	strName	= _pControl->GetValue();

	if ("Save" == strName)
	{
		saveConfig();
	}

	else if ("Test" == strName)
	{
		testConfig(true);
	}

	else if ("Back" == strName)
	{
		testConfig(false);
	}

	else if ("Exit" == strName)
	{
		m_pCanvas->InputQuit();
	}
}

bool Config::saveConfig()
{
	uint32_t uGamepadID	= m_pInput->getGamepadID();

	char	szFilename[MAX_PATH];

	sprintf(szFilename, "Config%08X.xml", uGamepadID);

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

			sprintf(szString, "<%s>%d</%s>\n", strName.c_str(), m_vecButtonConfigs[iLoop], strName.c_str());

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

void Config::testConfig(bool _bTest)
{
	showGamePad(_bTest);

	m_bTesting	= _bTest;
}

void Config::setupControls()
{
	m_pListBox	= new Gwen::Controls::ListBox(m_pCanvas);

	// Creates a list box that fills the area between the title bar and the buttons
	m_pListBox->SetBounds(0, 24, gsc_iWindowWidth, gsc_iWindowHeight - (24 + 40));
	m_pListBox->SetColumnCount(2);
	m_pListBox->SetAllowMultiSelect(false);
	
	for (int iLoop = 0; iLoop < gsc_iControlCount; ++iLoop)
	{
		Gwen::String	strDescription	= gsc_szControls[iLoop];

		Gwen::Controls::Layout::TableRow*	pRow	= m_pListBox->AddItem(strDescription, Gwen::Utility::ToString(iLoop));

		if (-1 == m_vecButtonConfigs[iLoop])
		{
			m_vecButtonConfigs[iLoop]	= m_pInput->getPreloadedButton(iLoop);

			if (-1 == m_vecButtonConfigs[iLoop])
			{
				pRow->SetCellText(1, L"Not Set");
			}
		}

		if (m_vecButtonConfigs[iLoop] != -1)
		{
			pRow->SetCellText(1, m_pInput->getKeyName(m_vecButtonConfigs[iLoop]));
		}

#if 0
		char	szToolTip[64];

		sprintf_s(szToolTip, "Click to configure %s.", gsc_szControls[iLoop]);
			
		pRow->SetToolTip(szToolTip);
#endif
	}

	m_pSaveButton	= new Gwen::Controls::Button(m_pCanvas);

	m_pSaveButton->SetPos(100, gsc_iWindowHeight - 35);
	m_pSaveButton->SetText("Save");
	m_pSaveButton->SetTextColorOverride(Gwen::Color(255, 255, 255, 255));
	m_pSaveButton->SetWidth(80);
	m_pSaveButton->SetHeight(30);
	m_pSaveButton->onPress.Add(this, &Config::OnSelection);

	m_pTestButton	= new Gwen::Controls::Button(m_pCanvas);

	m_pTestButton->SetPos(220, gsc_iWindowHeight - 35);
	m_pTestButton->SetText("Test");
	m_pTestButton->SetTextColorOverride(Gwen::Color(255, 255, 255, 255));
	m_pTestButton->SetWidth(80);
	m_pTestButton->SetHeight(30);
	m_pTestButton->onPress.Add(this, &Config::OnSelection);

	m_pBackButton	= new Gwen::Controls::Button(m_pCanvas);

	m_pBackButton->SetPos(220, gsc_iWindowHeight - 35);
	m_pBackButton->SetText("Back");
	m_pBackButton->SetTextColorOverride(Gwen::Color(255, 255, 255, 255));
	m_pBackButton->SetWidth(80);
	m_pBackButton->SetHeight(30);
	m_pBackButton->onPress.Add(this, &Config::OnSelection);
	m_pBackButton->Hide();

	// Setup gamepad
	setupGamepad();
}

bool Config::setupInput()
{
	// Create input handler
	m_pInput	= Input::create((HWND)m_pCanvas->GetWindow(), this);

	if (nullptr == m_pInput)
	{
		return	false;
	}

	// Load config XML
	if (false == loadXML())
	{
		return	false;
	}

	// Setup GUI controls
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

void Config::showGamePad(bool _bShow)
{
	m_pGamePad->SetHidden(false == _bShow);
	m_pBackButton->SetHidden(false == _bShow);
	m_pListBox->SetHidden(_bShow);
	m_pTestButton->SetHidden(_bShow);

	// Always hide the indicator. It will be reshown when input is detected.
	m_pIndicator->SetHidden(true);
}

void Config::setupGamepad()
{
	m_pGamePad	= new Gwen::Controls::ImagePanel(m_pCanvas);

	m_pGamePad->Hide();

	// Values must be offset, because the gamepad image is padded.
	int	iGamePadX	= (gsc_iWindowWidth - gsc_iGamepadWidth) / 2 + 2;
	int	iGamePadY	= (gsc_iWindowHeight - gsc_iGamepadHeight) / 2 + 2;
	
	m_pGamePad->SetImage(L"Gamepad.png");
	m_pGamePad->SetBounds(iGamePadX, iGamePadY, gsc_iGamepadWidth, gsc_iGamepadHeight);

	m_pIndicator	= new Gwen::Controls::ImagePanel(m_pCanvas);

	m_pIndicator->Hide();

	m_pIndicator->SetImage(L"Indicator.png");
	m_pIndicator->SetBounds((gsc_iWindowWidth - gsc_iIndicatorWidth) / 2, (gsc_iWindowHeight - gsc_iIndicatorHeight) / 2, 
		gsc_iIndicatorWidth, gsc_iIndicatorHeight);

	int	iSize	= gsc_iIndicatorWidth / 2;

	// Set dpad positions
	POINT	point1	= {iGamePadX + 54 - iSize, iGamePadY + 43 - iSize};
	m_vecButtonPositions.push_back(point1);

	POINT	point2	= {iGamePadX + 54 - iSize, iGamePadY + 72 - iSize};
	m_vecButtonPositions.push_back(point2);

	POINT	point3	= {iGamePadX + 40 - iSize, iGamePadY + 57 - iSize};
	m_vecButtonPositions.push_back(point3);

	POINT	point4	= {iGamePadX + 69 - iSize, iGamePadY + 57 - iSize};
	m_vecButtonPositions.push_back(point4);
	
	// Set ABXY positions
	POINT	point5	= {iGamePadX + 225 - iSize, iGamePadY + 57 - iSize};
	m_vecButtonPositions.push_back(point5);

	POINT	point6	= {iGamePadX + 202 - iSize, iGamePadY + 76 - iSize};
	m_vecButtonPositions.push_back(point6);

	POINT	point7	= {iGamePadX + 205 - iSize, iGamePadY + 35 - iSize};
	m_vecButtonPositions.push_back(point7);

	POINT	point8	= {iGamePadX + 181 - iSize, iGamePadY + 54 - iSize};
	m_vecButtonPositions.push_back(point8);
	
	// Set LR positions
	POINT	point9	= {iGamePadX + 59 - iSize, iGamePadY + 3 - iSize};
	m_vecButtonPositions.push_back(point9);

	POINT	point10	= {iGamePadX + 198 - iSize, iGamePadY + 3 - iSize};
	m_vecButtonPositions.push_back(point10);

	// Set Start and Select positions
	POINT	point11	= {iGamePadX + 105 - iSize, iGamePadY + 65 - iSize};
	m_vecButtonPositions.push_back(point11);

	POINT	point12	= {iGamePadX + 133 - iSize, iGamePadY + 65 - iSize};
	m_vecButtonPositions.push_back(point12);
}
