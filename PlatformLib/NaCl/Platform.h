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
#include <ppapi/cpp/instance.h>
#include <ppapi_simple/ps_instance.h>

#include "Macros.h"
#include "SPlayInstance.h"

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
		
		// Create display callback
		static void createDisplayCallback(void* _pData, int32_t _iValue);

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

		// Get instance
		static SPlayInstance* getInstance() {return ms_pInstance;}

		// Set instance
		static void setInstance(SPlayInstance* _pInstance) {ms_pInstance = _pInstance;}

		// Set bound
		static void setBound() {ms_bBound = true;}

	private:
		// Initialized
		static bool				ms_bInitialized;

		// Bound
		static bool				ms_bBound;

		// Timer
		static Timer*			ms_pTimer;

		// Window
		static Window*			ms_pWindow;
		
		// Storage path
		static tinystl::string	ms_strStoragePath;

		// Instance
		static SPlayInstance*	ms_pInstance;

		// Set storage path
		static void setStoragePath();
};

ENDNAMESPACE
