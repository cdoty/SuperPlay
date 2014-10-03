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
        friend class Speaker;
        friend class Sound;

    protected:
        int num_out_callbacks_;
        AudioOutCallback out_callbacks_[8];
        void *out_userdata_[8];

        AudioSpec audiospec_;

    protected:
        HSS_API_H virtual int open(AudioSpec *spec, unsigned int samples, AudioOutCallback callback, void *userdata) = 0;
        HSS_API_H virtual int close() = 0;

        HSS_API_H virtual void enterCriticalSectionImpl() = 0;
        HSS_API_H virtual void leaveCriticalSectionImpl() = 0;

        HSS_API_H virtual void suspend() = 0;
        HSS_API_H virtual void resume() = 0;

    protected:
        HSS_API_H virtual int setProperty(int property, long value)  { return kErrorPropertyNotSupported; }
        HSS_API_H virtual int getProperty(int property, long &value) { return kErrorPropertyNotSupported; }

    protected:
        AudioOutInterface();
        virtual ~AudioOutInterface();

    public:
        HSS_API_H const AudioSpec &getAudioSpec() const;

        HSS_API_H void enterCriticalSection();
        HSS_API_H void leaveCriticalSection();

        HSS_API_H int addCallback(AudioOutCallback callback, void *userdata);
        HSS_API_H void removeCallback(AudioOutCallback callback);
        HSS_API_H void removeCallback(int idx);
        HSS_API_H void removeCallbacks();
        HSS_API_H void processCallbacks(void *samples, int len);
    };

}


#endif
