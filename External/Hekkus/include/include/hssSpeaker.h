/* ****************************************************************************

HSS Engine ver 0.99 - 18/06/2002
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSSPEAKER_H
#define _HSSSPEAKER_H

#include "hssImpExp.h"
#include "hssChannel.h"
#include "hssAudioOutInterface.h"
#include "hssErrorDefs.h"

namespace hss
{  

    class HSS_CLS_API ChannelGroup;

    enum
    {
        kPropertyBufferLenght        = 0,
        kPropertyOtherAudio,
        kPropertyOtherAudioIsPlaying,
        kPropertyOutputSamplerate,
        kPropertyOutputBitrate,
        kPropertyParentInstance
    };

    enum
    {
        kPropertyEnable  = 1,
        kPropertyTrue    = 1,
        kPropertyDisable = 0,
        kPropertyFalse   = 0
    };

    /**
    *  StreamParameters struct.
    *  Use this struct to create a Sound stream using createSount.
    */
    struct StreamParameters
    {
        AudioSpec audiospec;
        unsigned int buffer_length_ms;
        int length_ms;

        StreamParameters() : audiospec(), buffer_length_ms(0), length_ms(-1) {}
        StreamParameters(const AudioSpec &_audiospec, unsigned int _buffer_length_ms, int _length_ms = -1) : audiospec(_audiospec), buffer_length_ms(_buffer_length_ms), length_ms(_length_ms) {}
    };

    /**
    *  Basic sound class.
    *  Use this class to open/close/supend/resume sound output and to play sounds.
    */
    class HSS_CLS_API Speaker
    {
    private:
        HSS_API_H Speaker();

    public:
        /**
        *  Create a new Speaker objects.
        *  \return the created Speaker object, NULL on failure.
        */
        HSS_API_H static Speaker *createSpeaker(void *parent_instance = NULL);

        /**
        *  Sets a property.
        *  This function must be called before to open the Speaker object or it will fail.
        *  \param property property to set.
        *  \param value new property's value.
        *  \return hss::kOk on success, error code on failure.
        */
        HSS_API_H int setProperty(int property, long value);
        /**
        *  Returns the value of the property requested
        *  \param property
        *  \return Value of the property.
        */
        HSS_API_H long getProperty(int property);

        /**
         *  Initialize the Hekkus Sound System with default output specifications.
         *  Open sound output at samplerate, setup a thread for sound update and alloc specified channels.\n
         *  <B>Symbian Series 60 phones supports only 8000hz and 16000hz 16bit mono output.</B>
         *  \return hss::kOk on success, error code on failure.
         */
        HSS_API_H int open(unsigned int samplerate, unsigned int flags = 0);
        /**
         *  Initialize the Hekkus Sound System.
         *  Open sound output at samplerate, setup a thread for sound update and alloc specified channels.\n
         *  <B>Symbian Series 60 phones supports only 8000hz and 16000hz 16bit mono output.</B>
         *  \param samplerate output rate in hz.
         *  \param bps select 16 or 8 bit output.
         *  \param stereo enable stereo output (true == stereo, false == mono).
         *  \return hss::kOk on success, error code on failure.
         */
        HSS_API_H int open(unsigned int samplerate, unsigned int bps, bool stereo, unsigned int flags = 0);
        /**
        *  Shut down the Hekkus Sound System.
        *  All sounds are stopped, thread are deallocated.
        *  \n You have however manually deallocated all Sounds and Musics previous allocated.
        *  \return hss::kOk on success, error code on failure.
        */
        HSS_API_H int close();

        /**
        *  Get the Speaker's AudioOutInterface.
        */
        HSS_API_H AudioOutInterface *getAudioOutInterface();

        /**
        *  Suspend sound output.
        *  Suspend all sounds, thread and sound output.
        *  Call it when your app are minimized or lose focus.
        */
        HSS_API_H void suspend();
        /**
        *  Resume sound output.
        *  Resume all sounds, thread and sound output.
        *  Call it when your app regain focus after a suspend call.
        */
        HSS_API_H void resume();

        /**
        *  Create and load a new Sound.
        *  \param name_or_buffer source name, can be a file name string or a memory buffer containg the sound to load.
        *  \param flags hss::kLoadDefault, hss::kLoadCopyToMemory, hss::kLoadAndDecode.
        *  \param size in case of a buffer you need to provide its size in bytes.
        *  \return the Sound created or NULL on failure.
        */
        HSS_API_H Sound *createSound(const void *name_or_buffer, unsigned int flags = 0, unsigned int size = 0);
        /**
        *  Release a previously created Sound.
        *  \param sound the Sound to release.
        *  \return hss::kOk on success, error code on failure.
        */
        HSS_API_H int releaseSound(Sound *sound);

        /**
        *  Play a Sound on the first Sound channel available.
        *  Play a Sound using the sample's default volume and loop settings.
        *  If all the Sound channels are playing this sound will discarded and not played.
        *  \param sound Pointer to the Sound to be played.
        *  \param channelAndFlags Specify the channel that will play the sound. Use hss::kPlayFree
        *    if you want the first channel available. You can 'or' hss::kPlayPaused if you want to start
        *    the sound paused.
        *  \return Channel pointer on success, 0 on failure.
        */
        HSS_API_H Channel *playSound(Sound *sound, unsigned int channelAndFlags = kPlayFree);
        /**
        *  Stop all playing and paused Sound channels.
        *  All stopped channels will be available for other play.
        */
        HSS_API_H void stopSounds();
        /**
        *  Stop all sound instances that are playing.
        */
        HSS_API_H void stopSoundInstances(const Sound *sound);
        /**
        *  Pause all playing Sound channels.
        */
        HSS_API_H void pauseSounds();
        /**
        *  Unpause all paused Sound channels.
        */
        HSS_API_H void unpauseSounds();
        /**
        *  Pause all sound instances.
        */
        HSS_API_H void pauseSoundInstances(const Sound *sound);
        /**
        *  Unpause all sound instances.
        */
        HSS_API_H void unpauseSoundInstances(const Sound *sound);

        /**
        *  Get the number of playing channels.
        *  \return the number of playing channels.
        */
        HSS_API_H unsigned int getNumChannelsPlaying() const;
        /**
        *  Get the number of Sound instances playing.
        *  \return the number of Sound instances playing.
        */
        HSS_API_H unsigned int getNumInstancesPlaying(const Sound *sound) const;

        /**
        *  Get the master ChannelGroup.
        */
        HSS_API_H ChannelGroup *getMasterChannelGroup();

        /**
        *  Create a new ChannelGroup.
        *  \return the ChannelGroup created or NULL on failure.
        */
        HSS_API_H ChannelGroup *createChannelGroup();
        /**
        *  Release a previously created ChannelGroup.
        *  \param cgroup the ChannelGroup to release.
        *  \return hss::kOk on success, error code on failure.
        */
        HSS_API_H int releaseChannelGroup(ChannelGroup *cgroup);

        HSS_API_H void update();

        /**
        *  Shut down the Hekkus Sound System.
        *  All sounds are stopped, thread are deallocated.
        *  \n You have however to manually deallocate all Sounds previously created.
        */
        HSS_API_H void release();
    };

}


#endif
