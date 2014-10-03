// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <html5.h>
#include <TinySTL/string.h>

#include "Macros.h"

NAMESPACE(SPlay)

class Timer;
class Window;

class Platform
{
	public:
		// Initialize
		static bool initialize();
		
		// Close
		static void close();
		
		// Run loop
		static void runLoop();

		// Redraw
		static void redraw();

		// Get window
		static Window* getWindow() {return ms_pWindow;}

		// Get timer
		static Timer* getTimer() {return ms_pTimer;}

		// Get storage path
		static const tinystl::string& getStoragePath();

		// Event handlers
		static int handleKeyDown(int _iEventType, const EmscriptenKeyboardEvent* _pKeyEvent, void* _pUserData);
		static int handleKeyUp(int _iEventType, const EmscriptenKeyboardEvent* _pKeyEvent, void* _pUserData);
		static EM_BOOL handleFullscreen(int _iEventType, const EmscriptenFullscreenChangeEvent* _pFullscreenEvent, void* _pUserData);

	private:
		// Timer
		static Timer*	ms_pTimer;

		// Window
		static Window*	ms_pWindow;
		
		// Storage path
		static tinystl::string ms_strStoragePath;

		// Set storage path
		static void setStoragePath();
};

ENDNAMESPACE
