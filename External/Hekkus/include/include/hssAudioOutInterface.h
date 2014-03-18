/* ****************************************************************************

HSS Driver Interface ver 0.2 - 21/02/2004
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSDRIVER_H
#define _HSSDRIVER_H

#include "hssImpExp.h"
#include "hssErrorDefs.h"
#include "hssAudioSpec.h"

namespace hss
{

    typedef void (*AudioOutCallback)(void *userdata, void *samples, int len);

    class HSS_CLS_API AudioOutInterface 
    {
    private:
        AudioOutInterface();

    public:
        HSS_API_H const AudioSpec &getAudioSpec() const;

        HSS_API_H void enterCriticalSection();
        HSS_API_H void leaveCriticalSection();

        HSS_API_H int addCallback(AudioOutCallback callback, void *userdata);
        HSS_API_H void removeCallback(AudioOutCallback callback);
        HSS_API_H void removeCallback(int idx);
        HSS_API_H void processCallbacks(void *samples, int len);
    };

}


#endif
