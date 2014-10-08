/* ****************************************************************************

HSS Utility class - 12/03/2003
    by Thomas Maniero - last modified 06/06/2005

todo:

**************************************************************************** */
#ifndef _HSSUTILITY_H
#define _HSSUTILITY_H

#include "hssImpExp.h"
#include "hssTypes.h"

#define MAX_PATHNAME 2048

#define PLATFORM_UNKNOW    0x0001

#define PLATFORM_SYMBIAN   0x0002

#define PLATFORM_WINDOWS   0x0004
#define SUBPLATFORM_WINNT  0x1000
#define SUBPLATFORM_WIN9X  0x2000
#define SUBPLATFORM_METRO  0x4000

#define PLATFORM_WINCE     0x0008

#define PLATFORM_MACOSX    0x0010
#define PLATFORM_IPHONE    0x4000

#define PLATFORM_BADA      0x0020

namespace hss
{

    class HSS_CLS_API Utility
    {
    public:
        static HSS_API_H unsigned int fullPathName(char pathname[MAX_PATHNAME], bool &inout_unicode_filename, const char *filename);

        static HSS_API_H uint16_t btol16(uint16_t big);
        static HSS_API_H uint32_t btol32(uint32_t big);

        static HSS_API_H int8_t getDigit(int8_t a);
        static HSS_API_H int8_t getUpAlpha(int8_t a);

        static HSS_API_H unsigned int getPlatform();
        static HSS_API_H unsigned int getOSVersion();
    };

}


#endif
