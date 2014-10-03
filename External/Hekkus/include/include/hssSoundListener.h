/* ****************************************************************************

HSS Sound Listener ver 0.1 - 01/01/2010
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSS_SOUND_LISTENER_H
#define _HSS_SOUND_LISTENER_H

#include "hssImpExp.h"

namespace hss
{

    class HSS_CLS_API Channel;
    class HSS_CLS_API Sound;

    enum SoundListenerFunction
    {
        kChannelStartPlaying = 0x0001,
        kChannelStopPlaying  = 0x0002,
        kChannelRequestAudio = 0x0004,

        kSoundStartPlaying   = 0x0010,
        kSoundStopPlaying    = 0x0020,

        kSoundListenerAll    = 0xFFFF
    };

    /**
    *  SoundListener interface class.
    *  Derive this class to implement your event functions.
    */
    class HSS_CLS_API SoundListener
    {
    public:
        /**
        *  Called when the channel starts to play.
        */
        virtual void onChannelStartPlaying(hss::Channel *channel, void *user_data) {}
        /**
        *  Called when the channel stops.
        */
        virtual void onChannelStopPlaying(hss::Channel *channel, void *user_data) {}
        /**
        *  Called when the channel needs more data.
        */
        virtual bool onChannelRequestAudio(hss::Channel *channel, void *samples, int length, void *user_data) { return false; }

        /**
        *  Called when the first sound instance starts to play.
        */
        virtual void onSoundStartPlaying(hss::Sound *sound, void *user_data) {}
        /**
        *  Called when the last sound instance stops.
        */
        virtual void onSoundStopPlaying(hss::Sound *sound, void *user_data) {}
    };

}


#endif
