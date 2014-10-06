// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>

#include "Macros.h"

NAMESPACE(SPlay)

// Game info
struct GameHeader
{
	// App name
	tinystl::string	strAppName;

	// Screen size
	int		iScreenWidth;
	int		iScreenHeight;

	// Windowed size
	int		iWindowedWidth;
	int		iWindowedHeight;

	// Full screen
	bool	bFullScreen;

	// Framed window (Windows only). bFullScreen must be false to work.
	bool	bFramedWindow;

	// Portrait orientation. Ignored on platforms that don't support screen orientations.
	bool	bPortrait;

	// Use shadow OAM
	bool	bUseShadowOAM;

	// SRAM size
	int		iSRAMSize;

	GameHeader()	:
		strAppName("Super Play"),
		iScreenWidth(256),
		iScreenHeight(224),
		iWindowedWidth(256),
		iWindowedHeight(224),
		bFullScreen(true),
		bFramedWindow(false),
		bPortrait(false),
		bUseShadowOAM(false),
		iSRAMSize(0)
	{
	}
};

ENDNAMESPACE

// Get game header function provided by game.
extern void getGameHeader(SPlay::GameHeader& _gameHeader);
