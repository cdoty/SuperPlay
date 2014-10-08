/* ****************************************************************************

HSS typedef header - 07/11/2002
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSTYPES_H
#define _HSSTYPES_H

#if defined(__SYMBIAN32__)

    #include <e32std.h>
    #include <stdint.h>

    #ifndef NULL
        #define NULL 0
    #endif

#elif (defined(BADA) || defined(SGH))

    #include <stdint.h>

    #ifndef NULL
    	#define NULL 0
    #endif

#elif (defined(__APPLE__) || defined(__MAC__))

    #include <stdint.h>

	#ifndef NULL
		#define NULL 0
	#endif

#elif defined(__ANDROID__)

    #include <stdint.h>

    #ifndef NULL
    	#define NULL 0
    #endif

#elif defined(__native_client__) || defined(__FLASHPLAYER__) || defined(__EMSCRIPTEN__)

    #include <stdint.h>

    #ifndef NULL
        #define NULL 0
    #endif

#elif ((defined(_WIN32) || defined(_WIN64)) && !defined(__WINS__))

#if (_MSC_VER >= 1600)  // vs >= 10.0
    #include <stdint.h>
#else
    typedef signed __int8     int8_t;
    typedef signed __int16    int16_t;
    typedef signed __int32    int32_t;
    typedef signed __int64    int64_t;

    typedef unsigned __int8   uint8_t;
    typedef unsigned __int16  uint16_t;
    typedef unsigned __int32  uint32_t;
    typedef unsigned __int64  uint64_t;
#endif

    #ifndef NULL
        #define NULL 0
    #endif

#elif defined(__PSP__)

    #include <psptypes.h>

    #ifndef NULL
        #define NULL 0
    #endif

#elif defined(__GP2X__)

    typedef signed char int8_t;
    typedef signed short int int16_t;
    typedef signed int int32_t;

    #if defined(__GNUC__)
        typedef long long int64_t;
    #else
        typedef long int int64_t;
    #endif

    typedef unsigned char  uint8_t;
    typedef unsigned short int uint16_t;
    typedef unsigned int uint32_t;

    #if defined(__GNUC__)
        typedef long long uint64_t;
    #else
        typedef long int uint64_t;
    #endif

    #ifndef NULL
        #define NULL 0
    #endif

#elif defined(__linux__)

    #include <stdint.h>

    #ifndef NULL
        #define NULL 0
    #endif

#endif

typedef int32_t int24f8_t;
typedef int64_t int56f8_t;
typedef int32_t int16f16_t;

#endif
