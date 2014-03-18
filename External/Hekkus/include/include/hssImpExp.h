
#ifndef _HSSIMPEXP_H
#define _HSSIMPEXP_H


#ifndef HSS_BUILD_DLL
  #ifndef HSS_BUILD_STATIC_LIB
    #define HSS_BUILD_STATIC_LIB
  #endif
#endif

#if (defined(__MACOSX__) || defined(__APPLE__) || defined(__MAC__))
  #if !defined(__MAC__)
    #define  __MAC__
  #endif

  #if defined(__OPENAL__)
    #define __PTHREADS__
  #endif
#endif


#if (defined(BADA) || defined(SHP))
  #if !defined(BADA)
    #define BADA
  #endif
#endif


#if (defined(ANDROID_NDK) || defined(ANDROID)|| defined(__ANDROID__))
  #if !defined(ANDROID)
    #define ANDROID
  #endif
#endif

#if defined(__native_client__)
    #if !defined(__NACL__)
        #define __NACL__
    #endif
#endif

#if defined(HSS_BUILD_STATIC_LIB)

  #define HSS_CLS_API
  #define HSS_API_H
  #define HSS_API_C

#else

  #if ((defined(_WIN64)) && !defined(__SYMBIAN32__))

    #ifdef HSS_EXPORTS
      #define HSS_CLS_API __declspec(dllexport)
      #define HSS_API_H
      #define HSS_API_C
    #else
      #define HSS_CLS_API __declspec(dllimport)
      #define HSS_API_H
      #define HSS_API_C
    #endif

  #endif

  #if defined(__SYMBIAN32__)

    //#if defined(__SYMBIAN6__)
      #ifdef HSS_EXPORTS
        #define HSS_API_H     EXPORT_C
        #define HSS_API_C     EXPORT_C
        #define HSS_CLS_API
      #else
        #define HSS_API_H     IMPORT_C
        #define HSS_API_C     IMPORT_C
        #define HSS_CLS_API
      #endif
    /*#else
      #define HSS_API_H     IMPORT_C
      #define HSS_API_C     EXPORT_C
      #define HSS_CLS_API
    #endif*/

  #endif

#endif

#if defined (__SYMBIAN32__) && !defined (__WINS__)
    #define __HSS_PACKSTRUCT__
#endif
#if defined (__GP2X__) || defined(__MAC__)
    #define __HSS_PACKSTRUCT__
#endif


#endif
