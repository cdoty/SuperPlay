// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#if defined SHP
#include <FApp.h>
#else
#include <assert.h>
#endif

#include <stdio.h>

#include "Log.h"

#if defined _DEBUG | defined DEBUG
#if defined __ANDROID__
#define ASSERT_LOG(exp, ...)  if (exp); else {Log::instance()->logError(__VA_ARGS__); assert(false);}

#define WARNING_LOG(exp, ...)  if (exp); else {Log::instance()->logWarning(__VA_ARGS__);}
#elif defined SHP | (defined WEBOS && !defined WIN32)
#define ASSERT_LOG(exp, ...)  if (exp); else {Log::instance()->logError(__VA_ARGS__); AppAssert(false);}

#define WARNING_LOG(exp, ...)  if (exp); else {Log::instance()->logWarning(__VA_ARGS__);}
#elif defined __GNUC__
#define ASSERT_LOG(exp, ...)  if (exp); else {Log::instance()->logError(__VA_ARGS__); assert(false);}

#define WARNING_LOG(exp, ...)  if (exp); else {Log::instance()->logWarning(__VA_ARGS__);}
#else
#define ASSERT_LOG(exp, Format, ...)  if (exp); \
	else {Log::instance()->logError("%s:%d " Format, __FILE__, __LINE__, __VA_ARGS__); assert(false);}

#define WARNING_LOG(exp, Format, ...)  if (exp); \
	else {Log::instance()->logWarning("%s:%d " Format, __FILE__, __LINE__, __VA_ARGS__);}
#endif
#else
#define ASSERT_LOG(exp, Format, ...)
#define WARNING_LOG(exp, Format, ...)
#endif
