// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdio.h>

#include "ScoreBar.h"
#include "GameDefines.h"
#include "Hardware.h"

// Start positions
static const int	gsc_iScoreStartX	= 9;
static const int	gsc_iLifeStartX		= 33;

ScoreBar::ScoreBar()	:
	m_pFontLoader(NULL)
{
}

ScoreBar::~ScoreBar()
{
	close();
}

ScoreBar* ScoreBar::create(const tinystl::string& _strFontName)
{
	ScoreBar*	pScoreBar	= new ScoreBar();

	if (false == pScoreBar->initialize() || false == pScoreBar->load(_strFontName))
	{
		delete	pScoreBar;

		pScoreBar	= NULL;
	}

	return	pScoreBar;
}

bool ScoreBar::initialize()
{
	return	true;
}

void ScoreBar::close()
{
	delete	m_pFontLoader;

	m_pFontLoader	= NULL;	
}

bool ScoreBar::load(const tinystl::string& _strFontName)
{
	// Load a font, and transfer it to the Text layer VRAM.
	m_pFontLoader	= FontLoader::create(_strFontName);

	// Get text layer
	Text*	pText	= Hardware::getText();
									  
	// Add scorebar text. '|' is used for a filled background block, since space is a blank character.
	// This is needed when the font has a non-transparent background.
	tinystl::string	strText	= "||SCORE:|||||||||||BACON|STRIPS:||||||||";

	// Draw text string to the Text Layer.
	pText->drawText(0, 0, strText.c_str());

	// Activate the text layer
	pText->setActive(true);

	return	true;
}

void ScoreBar::setScore(int _iScore)
{
	// Ensure the score doesn't overflow the space provided.
	if (_iScore > 999999)
	{
		_iScore	= 999999;
	}

	char	szScore[7];

	sprintf(szScore, "%06d", _iScore);

	// Get text layer
	Text*	pText	= Hardware::getText();

	// Draw text string to the Text Layer.
	pText->drawText(gsc_iScoreStartX, 0, szScore);
}

void ScoreBar::setLives(int _iCount)
{
	tinystl::string	strText;

	for (int iLoop = 0; iLoop < gsc_iMaxLives; ++iLoop)
	{
		// The '%' symbol has been replaced by the bacon icon.
		if (_iCount > iLoop)
		{
			strText	+= '%';
		}

		else
		{
			strText	+= '|';
		}
	}

	// Get text layer
	Text*	pText	= Hardware::getText();

	// Draw text string to the Text Layer.
	pText->drawText(gsc_iLifeStartX, 0, strText.c_str());
}

void ScoreBar::setPause(bool _bPause)
{
	// Get text layer
	Text*	pText	= Hardware::getText();

	tinystl::string	strPaused;
	tinystl::string	strExit;

	if (true == _bPause)
	{
		strPaused	= "Paused";
		strExit		= "Press|Select|to|Exit";
	}

	else
	{
		// The messages must be cleared away, since the Text Layer acts like a tile map, 
		// except it cannot be scrolled, it uses 8x8 tiles, and displays tiles 32-255.
		strPaused	= "      ";
		strExit		= "                    ";
	}

	int	iY	= gsc_iScreenHeight / gsc_iFontSize / 2;

	// Draw text strings to the Text Layer.
	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strPaused.length()) / 2, iY, strPaused.c_str());
	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strExit.length()) / 2, iY + 1, strExit.c_str());
}

// Game over
void ScoreBar::setGameOver(bool _bGameOver)
{
	// Get text layer
	Text*	pText	= Hardware::getText();

	tinystl::string	strGameOver;
	tinystl::string	strStart;
	tinystl::string	strExit;

	if (true == _bGameOver)
	{
		strGameOver	= "Game|Over";
		strStart	= "Press|Start|to|play|again";
		strExit		= "Press|Select|to|exit";
	}

	else
	{
		strGameOver	= "         ";
		strStart	= "                         ";
		strExit		= "                    ";
	}

	int	iY	= gsc_iScreenHeight / gsc_iFontSize / 2;

	// Draw text strings to the text layer
	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strGameOver.length()) / 2, iY, strGameOver.c_str());
	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strStart.length()) / 2, iY + 1, strStart.c_str());
	pText->drawText((gsc_iScreenWidth / gsc_iFontSize - strExit.length()) / 2, iY + 2, strExit.c_str());
}

