/* ****************************************************************************

HSS ChannelGroup ver 0.99 - 07/05/2010
	by Thomas Maniero - last modified 07/05/2010

todo:

**************************************************************************** */
#ifndef _HSSCHANNELGROUP_H
#define _HSSCHANNELGROUP_H

#include "hssImpExp.h"

namespace hss
{

    class HSS_CLS_API Speaker;

    /**
    *  %ChannelGroup class.
    *  Every Channel is associated with a ChannelGroup.\n
    *  Operations that you made with a ChannelGroup affects all Channels associated with it.\n
    *  You can create new ChannelGroups with the %Speaker object.\n
    *  The %Speaker object have a special ChannelGroup called the master ChannelGroup that is\n
    *  associated with every new Channels created, you can then change it if you like.
    */
    class HSS_CLS_API ChannelGroup
    {
    private:
        HSS_API_H ChannelGroup();

    public:
        /**
        *  Set ChannelGroup's volume. 
        * \param volume new ChannelGroup's volume. Can vary from 0.f to 1.f. 0.f = silence, 1.f = full volume.
        */
        HSS_API_H void setVolume(float volume);
        /**
        *  Get ChannelGroup's volume. 
        */
        HSS_API_H float getVolume() const;

        /**
        *  Set ChannelGroup's pitch 
        * \param pitch new ChannelGroup's pitch.
        */
        HSS_API_H void setPitch(float pitch);
        /**
        *  Get ChannelGroup's pitch. 
        */
        HSS_API_H float getPitch() const;

        /**
        *  Stop this ChannelGroup. 
        *  Stop a playing or paused ChannelGroup.
        */
        HSS_API_H void stop();
        /**
        *  Set ChannelGroup's pause flag. 
        */
        HSS_API_H void setPause(bool _pause);
        /**
        *  Pause this ChannelGroup. 
        *  Pause a playing ChannelGroup.
        */
        HSS_API_H void pause();
        /**
        *  Unpause this ChannelGroup. 
        *  Resume a previous paused ChannelGroup.
        */
        HSS_API_H void unpause();
        /**
        *  Returns if the ChannelGroup is currently paused or not.
        *  \return true if paused, false if playing or stopped.
        */
        HSS_API_H bool isPaused() const;

        /**
        *  Set ChannelGroup's mute flag. 
        */
        HSS_API_H void setMute(bool _mute);
        /**
        *  Mute this ChannelGroup. 
        */
        HSS_API_H void mute();
        /**
        *  Unmute this ChannelGroup. 
        */
        HSS_API_H void unmute();
        /**
        *  Returns if the ChannelGroup is currently muted or not.
        *  \return true if muted.
        */
        HSS_API_H bool isMuted() const;

        /**
        *  Release this ChannelGroup, this ChannelGroup will be replaced with the MasterChannelGroup on Channels that were using it and then it will be deallocated.
        */
        HSS_API_H void release();
    };

}


#endif
