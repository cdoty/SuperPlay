// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <GameHeader.h>

#include "GameDefines.h"

using namespace	SPlay;

void getGameHeader(GameHeader& _gameHeader)
{
	// App name
	_gameHeader.strAppName		= "BLT Shooter";

	// Screen size
	_gameHeader.iScreenWidth	= gsc_iScreenWidth;
	_gameHeader.iScreenHeight	= gsc_iScreenHeight;

	// Window size
	_gameHeader.iWindowedWidth	= gsc_iScreenWidth;
	_gameHeader.iWindowedHeight	= gsc_iScreenHeight;

	// Full screen
	_gameHeader.bFullScreen		= false;

	// Framed window
	_gameHeader.bFramedWindow	= true;

	// Use Shadow OAM
	_gameHeader.bUseShadowOAM	= true;

	// SRAM size
	_gameHeader.iSRAMSize		= 0;
}
