/* ****************************************************************************

HSS Channel ver 0.99 - 07/12/2002
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSCHANNEL_H
#define _HSSCHANNEL_H

#include "hssImpExp.h"
#include "hssData.h"

namespace hss
{

    class HSS_CLS_API Speaker;
    class HSS_CLS_API AudioOutInterface;
    class HSS_CLS_API ChannelGroup;

    /**
    *  %Sound channel class.
    *  When a sound are played the Sound class assign it to a Channel.\n
    *  Use this class to modify the state of a playing or paused hssMusic or hssSound.
    */
    class HSS_CLS_API Channel
    {
    private:
        HSS_API_H Channel();

    public:
        /**
        *  Get Channel's Audio Specifications. 
        */
        HSS_API_H const AudioSpec &getAudioSpec() const;

        /**
        *  Get Channel's associated Sound. 
        */
        HSS_API_H Sound *getSound() const;

        /**
        *  Set Channel's ChannelGroup. 
        * \param cgroup new Channel's ChannelGroup.
        */
        HSS_API_H void setChannelGroup(ChannelGroup *cgroup);
        /**
        *  Get Channel's ChannelGroup. 
        */
        HSS_API_H ChannelGroup *getChannelGroup() const;

        /**
        *  Set Channel's volume. 
        * \param volume new Channel's volume. Can vary from 0.f to 1.f. 0.f = silence, 1.f = full volume.
        */
        HSS_API_H void setVolume(float volume);
        /**
        *  Get Channel's volume. 
        */
        HSS_API_H float getVolume() const;

        /**
        *  Set Channel's pitch 
        * \param pitch new Channel's pitch.
        */
        HSS_API_H void setPitch(float pitch);
        /**
        *  Get Channel's pitch. 
        */
        HSS_API_H float getPitch() const;

        /**
        *  Set Channel's loop flag. 
        * \param loop new Channel's loop properties. false = disable loop, true = enable loop.
        */
        HSS_API_H void setLoop(bool loop);
        /**
        *  Get Channel's loop flag. 
        * \return false = loop disabled, true = loop enabled.
        */
        HSS_API_H bool getLoop() const;

        /**
        *  Set Channel's pan value. 
        * \param pan new pan value.
        */
        HSS_API_H void setPan(float pan);
        /**
        *  Get Channel's pan value. 
        * \return the pan value.
        */
        HSS_API_H float getPan() const;

        /**
        *  Set Channel's position.
        * \param position new position:\n for SFXs pass the new position in bytes\n
                                          for the Modules pass the new position in rows.
        */
        HSS_API_H void setPosition(unsigned int position);
        /**
        *  Get Channel's sound position.
        * \return for SFXs return the bytes played so far\n
                  for Modules return the rows played so far.
        */
        HSS_API_H unsigned int getPosition() const;

        /**
        *  Get Channel's sound lenght.
        * \return for SFXs return the lenght in bytes\n
                  for Modules return the lenght in rows.
        */
        HSS_API_H unsigned int getLength() const;

        /**
        *  Set Channel's user data.
        * \param user_data pointer to data that you want to retrieve from this Channel.
        */
        HSS_API_H void setUserData(void *user_data);
        /**
        *  Get Channel's user data.
        */
        HSS_API_H void *getUserData() const;

        /**
        *  Stop this Channel. 
        *  Stop a playing or paused Channel.
        */
        HSS_API_H void stop();
        /**
        *  Set Channel's pause flag. 
        */
        HSS_API_H void setPause(bool _pause);
        /**
        *  Pause this Channel. 
        *  Pause a playing Channel.
        */
        HSS_API_H void pause();
        /**
        *  Unpause this Channel. 
        *  Resume a previous paused Channel.
        */
        HSS_API_H void unpause();

        /**
        *  Returns if the Channel is currently playing or not.
        *  \return true if playing, false if paused or stopped.
        */
        HSS_API_H bool isPlaying() const;
        /**
        *  Returns if the Channel is currently paused or not.
        *  \return true if paused, false if playing or stopped.
        */
        HSS_API_H bool isPaused() const;
        /**
        *  Returns if the Channel is currently stopped or not.
        *  \return true if stopped, false if playing or paused.
        */
        HSS_API_H bool isStopped() const;
    };

}


#endif
