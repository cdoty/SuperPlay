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

#include "android_native_app_glue.h"
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
		static void runLoop(android_app* _pApplication);

		// Get window
		static Window* getWindow() {return ms_pWindow;}

		// Get exec path
		static const tinystl::string& getExecPath() {return ms_strExecPath;}

		// Get storage path
		static const tinystl::string& getStoragePath() {return ms_strStoragePath;}

		// Get android app
		static android_app* getAndroidApp() {return ms_pApplication;}

		// Get activity
		static ANativeActivity* getActivity() {return ms_pApplication->activity;}

		// Get JNIEnv
		static JNIEnv* getJNIEnv() {return ms_pEnv;}

		// Get asset manager
		static AAssetManager* getAssetManager() {return ms_pApplication->activity->assetManager;}

		// App command handler
		static void onAppCmd(android_app* _pApplication, int32_t _iCommand);

		// Input event handler
		static int32_t onInputEvent(android_app* _pApplication, AInputEvent* _pEvent);

	private:
		// Timer
		static Timer*			ms_pTimer;

		// Window
		static Window*			ms_pWindow;

		// Android application 
		static android_app*		ms_pApplication;

		// JNI environment
		static JNIEnv*			ms_pEnv;
		
		// Started
		static bool				ms_bActive;

		// Visible?
		static bool				ms_bVisible;

		// Focused?
		static bool				ms_bFocused;

		// Initialized?
		static bool				ms_bInitialized;
		
		// Exec path
		static tinystl::string ms_strExecPath;

		// Storage path
		static tinystl::string ms_strStoragePath;

		// Redraw
		static void redraw();

		// Set paths
		static void setPaths();
};

ENDNAMESPACE
