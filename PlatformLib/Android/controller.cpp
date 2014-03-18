/*
 * Bare-bones wrapper class for "com.bda.controller.Controller".
 * Requires error handling.
 */

/******************************************************************************/

#include "controller.h"

/******************************************************************************/

static jclass mClass;
static jmethodID mMethodGetInstance;
static jmethodID mMethodInit;
static jmethodID mMethodExit;
static jmethodID mMethodGetAxisValue;
static jmethodID mMethodGetInfo;
static jmethodID mMethodGetKeyCode;
static jmethodID mMethodGetState;
static jmethodID mMethodOnPause;
static jmethodID mMethodOnResume;
static jmethodID mMethodSetListener;

/******************************************************************************/

Controller::Controller(jobject controller) : mController(controller)
{
}

void Controller::jniOnLoad(JNIEnv * env, jobject activity)
{
	// get package-aware ClassLoader
	const jclass nativeActivityCls = env->FindClass("android/app/NativeActivity");
	const jmethodID getClassLoaderMth = env->GetMethodID(nativeActivityCls, "getClassLoader", "()Ljava/lang/ClassLoader;");
	const jobject classLoader = env->CallObjectMethod(activity, getClassLoaderMth);

	// load class
	const jstring classString = env->NewStringUTF("com/bda/controller/Controller");
	const jclass classLoaderCls = env->FindClass("java/lang/ClassLoader");
	const jmethodID loadClassMth = env->GetMethodID(classLoaderCls, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;"); 
	const jclass cls = static_cast<jclass>(env->CallObjectMethod(classLoader, loadClassMth, classString));
	env->DeleteLocalRef(classString);

	mClass = static_cast<jclass>(env->NewWeakGlobalRef(cls));

	// cache method ids
	mMethodGetInstance = env->GetStaticMethodID(cls, "getInstance", "(Landroid/content/Context;)Lcom/bda/controller/Controller;");
	mMethodInit = env->GetMethodID(cls, "init", "()Z");
	mMethodExit = env->GetMethodID(cls, "exit", "()V");
	mMethodGetAxisValue = env->GetMethodID(cls, "getAxisValue", "(I)F");
	mMethodGetInfo = env->GetMethodID(cls, "getInfo", "(I)I");
	mMethodGetKeyCode = env->GetMethodID(cls, "getKeyCode", "(I)I");
	mMethodGetState = env->GetMethodID(cls, "getState", "(I)I");
	mMethodOnPause = env->GetMethodID(cls, "onPause", "()V");
	mMethodOnResume = env->GetMethodID(cls, "onResume", "()V");
	mMethodSetListener = env->GetMethodID(cls, "setListener", "(Lcom/bda/controller/ControllerListener;Landroid/os/Handler;)V");
}

void Controller::jniOnUnload(JNIEnv * env)
{
	env->DeleteWeakGlobalRef(mClass);
}

jobject Controller::getInstance(JNIEnv * env, jobject context)
{
	return env->CallStaticObjectMethod(mClass, mMethodGetInstance, context);
}

jboolean Controller::init(JNIEnv * env)
{
	return env->CallBooleanMethod(mController, mMethodInit);
}

void Controller::exit(JNIEnv * env)
{
	env->CallVoidMethod(mController, mMethodExit);
}

jfloat Controller::getAxisValue(JNIEnv * env, jint axis)
{
	return env->CallFloatMethod(mController, mMethodGetAxisValue, axis);
}

jint Controller::getInfo(JNIEnv * env, jint keyCode)
{
	return env->CallIntMethod(mController, mMethodGetInfo, keyCode);
}

jint Controller::getKeyCode(JNIEnv * env, jint keyCode)
{
	return env->CallIntMethod(mController, mMethodGetKeyCode, keyCode);
}

jint Controller::getState(JNIEnv * env, jint state)
{
	return env->CallIntMethod(mController, mMethodGetState, state);
}

void Controller::onPause(JNIEnv * env)
{
	env->CallVoidMethod(mController, mMethodOnPause);
}

void Controller::onResume(JNIEnv * env)
{
	env->CallVoidMethod(mController, mMethodOnResume);
}

void Controller::setListener(JNIEnv * env, jobject listener, jobject handler)
{
	env->CallVoidMethod(mController, mMethodSetListener, listener, handler);
}