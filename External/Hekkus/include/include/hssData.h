/* ****************************************************************************

HSS Data ver 0.99 - 07/12/2002
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSDATA_H
#define _HSSDATA_H

#include "hssImpExp.h"
#include "hssAudioSpec.h"

namespace hss
{
    class HSS_CLS_API SoundListener;

    /**
    *  Sound class.
    *  Use this class to hold a sound.\n
    *  You can play n times this wave with hss::Speaker::playSound(), 
    *  from one call to another you can vary the Sound's properties like
    *  volume or loop flag, this affects only the next hssEngine::playSound() call.
    * \n\n
    *  Supports 8bit/16bit uncompressed and Microsoft ADPCM compressed mono/stero WAVs.
    *  Supports ProTracker modules (.mod) with up to 32 channels.
    */
    class HSS_CLS_API Sound
    {   
    private:
        HSS_API_H Sound();

    public:
        /**
        *  Get Sound's Audio Specifications. 
        */
        HSS_API_H const AudioSpec &getAudioSpec() const;

        /**
        *  Add a listener to this Sound. 
        * \param listener listener pointer to add.
        * \param user_data pointer with data that will be passed to listener event functions.
        */
        HSS_API_H void addListener(SoundListener *listener, void *user_data);
        /**
        *  Remove a listener from this Sound. 
        * \param listener listener pointer to remove.
        */
        HSS_API_H void removeListener(SoundListener *listener);

        /**
        *  Get Sound's lenght.
        * \return for SFXs return the lenght in bytes\n
        for Modules return the lenght in rows.
        */
        HSS_API_H unsigned int getLength();

        /**
        *  Set Sound's volume. 
        * \param volume new Sound's volume. Can vary from 0.f to 1.f. 0.f = silence, 1.f = full volume.
        */
        HSS_API_H void setVolume(float volume);
        /**
        *  Get Sound's volume. 
        */
        HSS_API_H float getVolume() const;

        /**
        *  Set Sound's pitch 
        * \param pitch new Sound's pitch.
        */
        HSS_API_H void setPitch(float pitch);
        /**
        *  Get Sound's pitch. 
        */
        HSS_API_H float getPitch() const;

        /**
        *  Set Sound's loop flag. 
        * \param loop new Sound's loop property. false = disable loop, true = enable loop.
        */
        HSS_API_H void setLoop(bool loop);
        /**
        *  Get Sound's loop flag. 
        * \return false = loop disabled, true = loop enabled.
        */
        HSS_API_H bool getLoop() const;

        /**
        *  Set Sound's pan value. 
        *  Value can vary between -1.f (completely left output) to 1.f (completely right output)\n
        *  Value of 0.f will result in no panning at all (same output on left and right channel).
        */
        HSS_API_H void setPan(float pan);
        /**
        *  Get Sound's pan value. 
        * \return the pan value.
        */
        HSS_API_H float getPan() const;

        /**
        *  Sets the maximum number of times a sample can play back at once.
        */
        HSS_API_H void setMaxPlaybacks(int mpb);
        /**
        *  Gets the maximum number of times a sample can play back at once. 
        */
        HSS_API_H int getMaxPlaybacks() const;

        /**
        *  Release this Sound, this function will stop all its playing instancies and deallocate the object.
        */
        HSS_API_H void release();
    };

}


#endif
