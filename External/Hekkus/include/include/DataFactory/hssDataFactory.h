
#ifndef _HSSDATA_FACTORY_H
#define _HSSDATA_FACTORY_H

#include "../hssConfig.h"
#include "../hssTypes.h"

namespace hss
{

    class HSS_CLS_API Sound;

    class HSS_CLS_API DataFactory
    {
    public:
        DataFactory() {}
        virtual ~DataFactory() {}
        
    public:
        virtual int isSupportedFromSignature(char *signbuf, unsigned int size_signbuf, unsigned int flags) = 0;
        virtual Sound *createSound(const void *data, unsigned int flags) = 0;
    };

}

#endif
