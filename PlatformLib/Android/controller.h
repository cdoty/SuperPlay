#ifndef COM_BDA_CONTROLLER_CONTROLLER
#define COM_BDA_CONTROLLER_CONTROLLER

/******************************************************************************/

#include <jni.h>

/******************************************************************************/

class Controller
{
public:
	static const jint ACTION_DOWN = 0;
	static const jint ACTION_UP = 1;
	static const jint ACTION_FALSE = 0;
	static const jint ACTION_TRUE = 1;
	static const jint ACTION_DISCONNECTED = 0;
	static const jint ACTION_CONNECTED = 1;
	static const jint ACTION_CONNECTING = 2;
	static const jint ACTION_VERSION_MOGA = 0;
	static const jint ACTION_VERSION_MOGAPRO = 1;

	static const jint KEYCODE_DPAD_UP = 19;
	static const jint KEYCODE_DPAD_DOWN = 20;
	static const jint KEYCODE_DPAD_LEFT = 21;
	static const jint KEYCODE_DPAD_RIGHT = 22;
	static const jint KEYCODE_BUTTON_A = 96;
	static const jint KEYCODE_BUTTON_B = 97;
#ifdef BUILD_LEGACY_API
	// SDK 1.2.7b and earlier
	static const jint KEYCODE_BUTTON_X = 98;
	static const jint KEYCODE_BUTTON_Y = 99;
#else
	// SDK 1.2.7c and later
	static const jint KEYCODE_BUTTON_X = 99;
	static const jint KEYCODE_BUTTON_Y = 100;
#endif
	static const jint KEYCODE_BUTTON_L1 = 102;
	static const jint KEYCODE_BUTTON_R1 = 103;
	static const jint KEYCODE_BUTTON_L2 = 104;
	static const jint KEYCODE_BUTTON_R2 = 105;
	static const jint KEYCODE_BUTTON_THUMBL = 106;
	static const jint KEYCODE_BUTTON_THUMBR = 107;
	static const jint KEYCODE_BUTTON_START = 108;
	static const jint KEYCODE_BUTTON_SELECT = 109;

	static const jint INFO_KNOWN_DEVICE_COUNT = 1;
	static const jint INFO_ACTIVE_DEVICE_COUNT = 2;

	static const jint AXIS_X = 0;
	static const jint AXIS_Y = 1;
	static const jint AXIS_Z = 11;
	static const jint AXIS_RZ = 14;
	static const jint AXIS_LTRIGGER = 17;
	static const jint AXIS_RTRIGGER = 18;

	static const jint STATE_CONNECTION = 1;
	static const jint STATE_POWER_LOW = 2;
	static const jint STATE_SUPPORTED_VERSION = 3;	// Controller Version
	static const jint STATE_SELECTED_VERSION = 4;	// Service Controller Version

public:
	Controller(jobject controller);

	static void jniOnLoad(JNIEnv * env, jobject activity);
	static void jniOnUnload(JNIEnv * env);

	static jobject getInstance(JNIEnv * env, jobject context);
	jboolean init(JNIEnv * env);
	void exit(JNIEnv * env);
	jfloat getAxisValue(JNIEnv * env, jint axis);
	jint getInfo(JNIEnv * env, jint info);
	jint getKeyCode(JNIEnv * env, jint keyCode);
	jint getState(JNIEnv * env, jint state);
	void onPause(JNIEnv * env);
	void onResume(JNIEnv * env);
	void setListener(JNIEnv * env, jobject listener, jobject handler);

private:
	const jobject mController;
};

/******************************************************************************/

#endif // __HEADER
