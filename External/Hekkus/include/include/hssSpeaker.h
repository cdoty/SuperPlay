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

#include "hssSpeakerListener.h"
#include "Array.h"
#include "DataFactory/hssDataFactory.h"


namespace hss
{
    /**
    *  Create a new Speaker objects.
    *  \param platform_data some platforms need additional data to be able to initialize the sound system.<BR>
    * <B>Android</B>: please pass a JavaVM* object instance, you can get it from the function jint JNI_OnLoad(JavaVM*, void*).<BR>
    * <B>Native Client</B>: please pass a pp::Instance* object instance.<BR>
    * Other platforms don't need additional data so the parameter is ignored.
    *  \return the created Speaker object, NULL on failure.
    */
    HSS_API_H Speaker *createSpeaker(void *platform_data = NULL);

    class HSS_CLS_API ChannelGroup;

    struct SpeakerListenerItem
    {
        hss::SpeakerListener *listener;
        void *user_data;
    };

    enum
    {
        kPropertyBufferLenght        = 0,
        kPropertyOtherAudio,
        kPropertyOtherAudioIsPlaying,
        kPropertyOutputSamplerate,
        kPropertyOutputBitrate,
        kPropertyPlatformData
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
        friend class Sound;
        friend class Channel;
        friend class ChannelData;
        friend class ChannelGroup;
        friend Speaker *createSpeaker(void *platform_data);

    private:
        AudioOutInterface *audio_out_;
        //AudioInInterface *m_audio_in;
        bool open_;

        int num_channels_;
        Channel *channels_;
        Channel **playing_channels_;

        ChannelGroup *master_cgroup_;

        AudioSpec audiospec_;
        int buffer_length_;

        Array<DataFactory*> data_factories_;

        Array<SpeakerListenerItem> listeners_;

    private:
        HSS_API_H AudioOutInterface *createAudioOutInterface();

        HSS_API_H static void audioCallback(void *userdata, void *samples, int len);
        HSS_API_H void updateChannels(void *samples, int len);
        HSS_API_H Channel *getChannel(int chl) const;

        HSS_API_H void createDataFactories();
        HSS_API_H void releaseDataFactories();

        HSS_API_H void processListeners(unsigned int flag_functions, void *stream = 0, int length = 0);

    private:
        HSS_API_H Speaker();
        HSS_API_H virtual ~Speaker();

    private:
        HSS_API_H int initialize(void *platform_data);
        HSS_API_H void finalize();

    public:
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
        *  \param property property to get.
        *  \param value the value of the property.
        *  \return hss::kOk on success, error code on failure.
        */
        HSS_API_H int getProperty(int property, long &value);

        /**
        *  Add a listener to this Speaker.
        * \param listener listener pointer to add.
        * \param user_data pointer with data that will be passed to listener event functions.
        */
        HSS_API_H void addListener(SpeakerListener *listener, void *user_data);
        /**
        *  Remove a listener from this Speaker.
        * \param listener listener pointer to remove.
        */
        HSS_API_H void removeListener(SpeakerListener *listener);

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
