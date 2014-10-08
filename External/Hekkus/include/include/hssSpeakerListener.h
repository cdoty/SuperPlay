/* ****************************************************************************

HSS Speaker Listener ver 0.1 - 12/12/2012
    by Thomas Maniero - last modified 12/12/2012

todo:

**************************************************************************** */
#ifndef _HSS_SPEAKER_LISTENER_H
#define _HSS_SPEAKER_LISTENER_H

#include "hssImpExp.h"

namespace hss
{

    class HSS_CLS_API Speaker;

    enum SpeakerListenerFunction
    {
        kSpeakerSuspend      = 0x0001,
        kSpeakerResume       = 0x0002,

        kSpeakerBeforeMixing = 0x0010,
        kSpeakerMixing       = 0x0020,
        kSpeakerAfterMixing  = 0x0040,

        kSpeakerListenerAll  = 0xFFFF
    };

    /**
    *  SpeakerListener interface class.
    *  Derive this class to implement your event functions.
    */
    class HSS_CLS_API SpeakerListener
    {
    public:
        /**
        *  Called when the speaker object suspend.
        */
        virtual void onSpeakerSuspend(hss::Speaker *speaker, void *user_data) {}
        /**
        *  Called when the speaker object resume.
        */
        virtual void onSpeakerResume(hss::Speaker *speaker, void *user_data) {}

        /**
        *  Called before the speaker starts to mix sounds.
        */
        virtual void onSpeakerBeforeMixing(hss::Speaker *speaker, void *user_data) {}
        /**
        *  Called after the speaker mix sounds, you can read or even modify the mixer data.
        */
        virtual void onSpeakerMixing(hss::Speaker *speaker, void *samples, int length, void *user_data) {}
        /**
        *  Called after the speaker mix sounds.
        */
        virtual void onSpeakerAfterMixing(hss::Speaker *speaker, void *user_data) {}
    };

}


#endif
