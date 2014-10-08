#ifndef _HSSBUFFERLENDEF_H
#define _HSSBUFFERLENDEF_H

#include "hssImpExp.h"

#if defined(BADA)

    #define BUFFER_LENGTH 100

#elif defined(__ANDROID__)

    #define BUFFER_LENGTH 140

#elif defined(__SYMBIAN32__)

#if defined(__WINS__)
    #define BUFFER_LENGTH  250
#else
    #if defined(__SYMBIAN6__)
        #define BUFFER_LENGTH  100
    #else
        #if defined(__WINSCW__)
            #define BUFFER_LENGTH   200
        #else
            #define BUFFER_LENGTH   60
        #endif
    #endif
#endif

#elif defined(__native_client__)

#define BUFFER_LENGTH  100

#elif defined(__FLASHPLAYER__)

#define BUFFER_LENGTH  140

#elif defined(__EMSCRIPTEN__)

#define BUFFER_LENGTH  80

#elif defined(__linux__)

#define BUFFER_LENGTH  140

#elif ((defined(_WIN32) || defined(_WIN64) || defined(__MAC__)) && !defined(__SYMBIAN32__))

#if defined(__OPENAL__)
    #define BUFFER_LENGTH 100
#elif defined(__MAC__)
    #define BUFFER_LENGTH 10
#else
    #define BUFFER_LENGTH 180
#endif

#elif defined(__PSP__)

    #define BUFFER_LENGTH  60

#elif defined(__GP2X__)

    #define BUFFER_LENGTH  200

#endif

#define MIN_BUFFER_LENGTH 10


#define MUSIC_DEFAULT   8
#define SOUND_DEFAULT  64


#endif
