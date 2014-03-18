// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <libgen.h>
#include <android/window.h>

#include "android_native_app_glue.h"
#include "controller.h"
#include "HardwareDefines.h"
#include "IDisplay.h"
#include "Input.h"
#include "Hardware.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "Platform.h"
#include "Sound.h"
#include "System.h"
#include "Timer.h"
#include "Window.h"

NAMESPACE(SPlay)

Timer*			Platform::ms_pTimer			= NULL;
Window*			Platform::ms_pWindow		= NULL;
android_app*	Platform::ms_pApplication	= NULL;
JNIEnv*			Platform::ms_pEnv			= NULL;
bool			Platform::ms_bActive		= false;
bool			Platform::ms_bVisible		= false;
bool			Platform::ms_bFocused		= false;
bool			Platform::ms_bInitialized	= false;
tinystl::string Platform::ms_strExecPath;
tinystl::string Platform::ms_strStoragePath;

// Initialize platform
bool initializePlatform()
{
	return	Platform::initialize();
}

// Close platform
void closePlatform()
{
	Platform::close();
}

// Get storage path
const tinystl::string& getStoragePath()
{
	return	Platform::getStoragePath();
}

bool Platform::initialize()
{
	GameHeader&	gameHeader	= System::getUpdateableGameHeader();

	gameHeader.iWindowedWidth	= ms_pWindow->getWidth();
	gameHeader.iWindowedHeight	= ms_pWindow->getHeight();

	System::ms_pDisplay	= createDisplay();

	if (NULL == System::ms_pDisplay)
	{
		return	false;
	}

	return	true;
}

void Platform::close()
{
	ms_bInitialized	= false;

	// Delete window
	delete	ms_pWindow;

	ms_pWindow	= NULL;

	// Delete timer
	delete	ms_pTimer;

	ms_pTimer	= NULL;

	// Delete display
	delete	System::ms_pDisplay;

	System::ms_pDisplay	= NULL;

	// Close sound
	closeSound();

	// Delete input
	delete	System::ms_pInput;

	System::ms_pInput	= NULL;
}

void Platform::runLoop(android_app* _pApplication)
{
	app_dummy();

	ANativeActivity*	pActivity	= _pApplication->activity;

	pActivity->vm->AttachCurrentThread(&ms_pEnv, NULL);

	Controller::jniOnLoad(ms_pEnv, pActivity->clazz);
	
	// Setup app command handler
	_pApplication->onAppCmd		= onAppCmd;
	_pApplication->onInputEvent	= onInputEvent;

	ms_pApplication	= _pApplication;

	setPaths();

	// Create the window. The EGL context will be created when the surface created message is received.
	ms_pWindow	= Window::create();
	
	if (NULL == ms_pWindow)
	{
		ANativeActivity_finish(pActivity);
	}

	ms_pTimer	= Timer::create();

	if (NULL == ms_pTimer)
	{
		ANativeActivity_finish(pActivity);
	}

	System::ms_pInput	= Input::create();

	if (NULL == System::ms_pInput)
	{
		ANativeActivity_finish(pActivity);
	}

	else
	{
		Input*	pInput	= reinterpret_cast<Input*>(System::ms_pInput);

		if (false == pInput->onCreate())
		{
			ANativeActivity_finish(pActivity);
		}
	}

	// Initialize sound
	if (false == initializeSound())
	{
		ANativeActivity_finish(pActivity);
	}

	while (true)
	{
		int32_t	iResult;
		int32_t	iEvents;

		android_poll_source*	pPollSource;

		while (ALooper_pollAll(true == ms_bVisible ? 0 : -1, NULL, &iEvents, (void**)&pPollSource) >= 0)
		{
			if (_pApplication->destroyRequested != 0) 
			{
				return;
			}

			if (pPollSource != NULL)
			{
				pPollSource->process(ms_pApplication, pPollSource);
			}
		}

		if (true == ms_pApplication->destroyRequested)
		{
			break;
		}

		if (true == ms_bActive && true == ms_bVisible && true == ms_bFocused && true == ms_bInitialized)
		{
			// Get the elapsed time
			float	fElapsed	= ms_pTimer->getElapsedFloat();

			System::getInput()->update();

			if (false == System::getGame()->update(fElapsed))
			{
				ANativeActivity_finish(pActivity);
			}
			
			else
			{
				redraw();
			}
		}
	}

	Controller::jniOnUnload(ms_pEnv);
	
	pActivity->vm->DetachCurrentThread();
}

void Platform::onAppCmd(android_app* _pApplication, int32_t _iCommand)
{
	switch (_iCommand)
	{
		// onStart
		case APP_CMD_START:
			ms_bActive	= true;

			ANativeActivity_setWindowFlags(_pApplication->activity, AWINDOW_FLAG_KEEP_SCREEN_ON, 0);

			break;

		// onResume
		case APP_CMD_RESUME:
			ms_bVisible	= true;

			if (ms_pTimer != NULL)
			{
				ms_pTimer->start();
			}

			if (System::ms_pInput != NULL)
			{
				Input*	pInput	= reinterpret_cast<Input*>(System::ms_pInput);

				pInput->onResume();
			}

			break;

		// onPause
		case APP_CMD_PAUSE:
			// Pause the game when pausing
			Hardware::setPaused(true);

			ms_bVisible	= false;
			ms_bFocused	= false;

			if (System::ms_pInput != NULL)
			{
				Input*	pInput	= reinterpret_cast<Input*>(System::ms_pInput);

				pInput->onPause();
			}

			break;

		// onStop
		case APP_CMD_STOP:
			ms_bActive		= false;

			ANativeActivity_setWindowFlags(_pApplication->activity, 0, AWINDOW_FLAG_KEEP_SCREEN_ON);

			break;

		// onDestroy
		case APP_CMD_DESTROY:
			ms_bInitialized	= false;

			if (System::ms_pInput != NULL)
			{
				Input*	pInput	= reinterpret_cast<Input*>(System::ms_pInput);

				pInput->onDestroy();
			}

			System::close();

			break;

		// onWindowFocusChanged(true)
		case APP_CMD_GAINED_FOCUS:
			ms_bFocused	= true;

			if (ms_pTimer != NULL)
			{
				ms_pTimer->start();
			}

			break;

		// onWindowFocusChanged(false)
		case APP_CMD_LOST_FOCUS:
			ms_bFocused	= false;

			// Pause the game when pausing
			Hardware::setPaused(true);

			break;

		// onConfigurationChanged
		case APP_CMD_CONFIG_CHANGED:
			break;
		
		// onSurfaceCreated 
		case APP_CMD_INIT_WINDOW:
			if (NULL == ms_pWindow || false == ms_pWindow->acquireContext())
			{
				ANativeActivity_finish(_pApplication->activity);

				break;
			}

			else if (false == ms_bInitialized)
			{
				if (false == System::initialize())
				{
					ANativeActivity_finish(_pApplication->activity);
				}

				else
				{
					ms_bInitialized	= true;
				}
			}

			ms_bVisible	= true;

			break;

		// onSurfaceChanged
		case APP_CMD_WINDOW_RESIZED:
			break;

		// onSurfaceDestroyed
		case APP_CMD_TERM_WINDOW:
			if (ms_pWindow != NULL)
			{
				ms_pWindow->releaseContext();
			}

			ms_bVisible	= false;

			break;

		case APP_CMD_LOW_MEMORY:
			break;

		case APP_CMD_SAVE_STATE:
			break;
	}
}

int32_t Platform::onInputEvent(android_app* _pApplication, AInputEvent* _pEvent)
{
	int32_t	iEventType		= AInputEvent_getType(_pEvent);
	int32_t	iEventSource	= AInputEvent_getSource(_pEvent);

	Input*	pInput	= static_cast<Input*>(System::getInput());

	if (pInput != NULL)
	{
		if (iEventSource & AINPUT_SOURCE_CLASS_JOYSTICK)
		{
			pInput->handleJoystickEvent(_pEvent);
		}

		else if (AINPUT_EVENT_TYPE_KEY == iEventType)
		{
			pInput->handleKeyEvent(_pEvent);
		}
	}
}

void Platform::redraw()
{
	System::getDisplay()->render();
}

void Platform::setPaths()
{
	ANativeActivity*	pActivity	= ms_pApplication->activity;

	if (pActivity->internalDataPath != NULL && strlen(pActivity->internalDataPath) > 0)
	{
		ms_strStoragePath	= pActivity->internalDataPath;
	}

	else
	{
		jclass		activityClass	= ms_pEnv->GetObjectClass(pActivity->clazz);
		jmethodID	getFilesDir		= ms_pEnv->GetMethodID(activityClass, "getFilesDir", "()Ljava/io/File;");
		jobject		fileObject		= ms_pEnv->CallObjectMethod(pActivity->clazz, getFilesDir);
		jclass		fileClass		= ms_pEnv->GetObjectClass(fileObject);
		jmethodID	getAbsolutePath	= ms_pEnv->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
		jobject		pathObject		= ms_pEnv->CallObjectMethod(fileObject, getAbsolutePath);
		
		ms_strStoragePath			= ms_pEnv->GetStringUTFChars((jstring)pathObject, NULL);

		ms_pEnv->DeleteLocalRef(pathObject);
		ms_pEnv->DeleteLocalRef(fileClass);
		ms_pEnv->DeleteLocalRef(fileObject);
		ms_pEnv->DeleteLocalRef(activityClass);
	}

	ms_strExecPath	= dirname(ms_strStoragePath.c_str());
}

ENDNAMESPACE
