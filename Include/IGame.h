// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "SuperPlay_d.lib")
#pragma comment(lib, "Sound_d.lib")
#pragma comment(lib, "Platform_d.lib")
#ifdef ANGLE
#pragma comment(lib, "DisplayAngle_d.lib")
#elif defined GLWIN
#pragma comment(lib, "DisplayGL_d.lib")
#else
#pragma comment(lib, "Display_d.lib")
#endif
#pragma comment(lib, "winmm.lib")
#ifdef ANGLE
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#endif
#ifdef USE_SDL
#pragma comment(lib, "SDL2_d.lib")
#pragma comment(lib, "SDL2main_d.lib")
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "version.lib")
#endif
#else
#pragma comment(lib, "SuperPlay.lib")
#pragma comment(lib, "Sound.lib")
#pragma comment(lib, "Platform.lib")
#ifdef ANGLE
#pragma comment(lib, "DisplayAngle.lib")
#elif defined GLWIN
#pragma comment(lib, "DisplayGL.lib")
#else
#pragma comment(lib, "Display.lib")
#endif
#pragma comment(lib, "winmm.lib")
#ifdef ANGLE
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#endif
#ifdef USE_SDL
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "version.lib")
#endif
#endif
#endif

#include "Macros.h"


// Create the game class
#define CREATE_GAME(className) \
SPlay::IGame* createGame(); \
SPlay::IGame* createGame() \
{ \
return	className::create(); \
}

NAMESPACE(SPlay)

class IGame
{
	public:
		// Destructor
		virtual ~IGame() {}

		// Update
		virtual bool update(float _fElapsedTime) = 0;
};

ENDNAMESPACE
