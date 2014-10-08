/* ****************************************************************************

HSS Channel ver 0.99 - 07/12/2002
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSCHANNEL_DATA_H
#define _HSSCHANNEL_DATA_H

#include "hssImpExp.h"
#include "hssData.h"
#include "hssTypes.h"
#include "hssAudioSpec.h"

namespace hss
{
    const unsigned int VolumeResolution = 15;

    enum ChannelState
    {
        kStateStop       = 0x000,
        kStatePlay       = 0x001,
        kStatePause      = 0x002,
        kStateLoop       = 0x010
    };

    class HSS_CLS_API Speaker;
    class HSS_CLS_API AudioOutInterface;
    class HSS_CLS_API ChannelGroup;

    class HSS_CLS_API ChannelData
    {
        friend class Speaker;
        friend class ChannelGroup;

    private:
        HSS_API_H static void initialize(unsigned int frequency);

    protected:
        HSS_API_H void init(Sound *sound);

    protected:
        unsigned int type_;

        Speaker *speaker_ptr_;
        Sound *sound_ptr_;

        void *user_data_;

        int channel_id_;

        ChannelGroup *cgroup_ptr_;

        float volume_;
        float pan_;

        unsigned int state_;

        AudioSpec audiospec_;
        unsigned int virtual_samplerate_; // virtual frequency
        bool changefreq_;       // change frequency?
        float pitch_;

        // working buffer...
        int24f8_t buflength_;
        int24f8_t bufposition_;
        uint8_t *bufdecoded_;
        int bufdecoded_length_;
        bool bufdecoded_allocated_;

        // global position and lenght, put here for now...
        int24f8_t freqfactor_;
        int56f8_t position_;
        int56f8_t length_;

        unsigned int volume_internal_;
        unsigned int pan_internal_;

    protected:
        HSS_API_H ChannelData(Speaker *speaker_ptr);
        HSS_API_H virtual ~ChannelData();

    protected:
        HSS_API_H void play(bool paused = false);
        HSS_API_H virtual int decode(int64_t pos);
        HSS_API_H virtual void changefreq();
        HSS_API_H virtual void free_resource();

        HSS_API_H virtual void updateVolume();
        HSS_API_H virtual void updatePitch();
        HSS_API_H virtual void updatePan();
        HSS_API_H virtual void updateState();

        HSS_API_H Speaker *getSpeaker();
        HSS_API_H AudioOutInterface *getSpeakerAudioOut();

    protected:
        HSS_API_H void updateSoundLenght();

    public:
        HSS_API_H const AudioSpec &getAudioSpec() const;

        HSS_API_H Sound *getSound() const;

        HSS_API_H void setChannelGroup(ChannelGroup *cgroup);
        HSS_API_H ChannelGroup *getChannelGroup() const;

        HSS_API_H void setVolume(float volume);
        HSS_API_H float getVolume() const;

        HSS_API_H void setPitch(float pitch);
        HSS_API_H float getPitch() const;

        HSS_API_H void setLoop(bool loop);
        HSS_API_H bool getLoop() const;

        HSS_API_H void setPan(float pan);
        HSS_API_H float getPan() const;

        HSS_API_H virtual void setPosition(int64_t position);
        HSS_API_H virtual int64_t getPosition() const;
        HSS_API_H virtual int64_t getLength() const;

        HSS_API_H void setUserData(void *user_data);
        HSS_API_H void *getUserData() const;

        HSS_API_H void stop();
        HSS_API_H void setPause(bool _pause);
        HSS_API_H void pause();
        HSS_API_H void unpause();

        HSS_API_H bool isPlaying() const;
        HSS_API_H bool isPaused() const;
        HSS_API_H bool isStopped() const;
    };

}


#endif
