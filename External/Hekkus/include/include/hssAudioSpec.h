/* ****************************************************************************

HSS AudioSpec ver 0.1 - 21/02/2006
    by Thomas Maniero - last modified 19/09/2012

todo:

**************************************************************************** */
#ifndef _HSSAUDIOSPEC_H
#define _HSSAUDIOSPEC_H

namespace hss
{

    enum AudioFormat
    {
        kAudioUndefined = 0,

        kAudio8         = 0x0001,
        kAudio16        = 0x0002,
        kAudioSigned    = 0x0010,
        kAudioUnsigned  = 0x0020,

        kAudioU8        = (kAudioUnsigned | kAudio8),
        kAudioS8        = (kAudioSigned | kAudio8),
        kAudioU16       = (kAudioUnsigned | kAudio16),
        kAudioS16       = (kAudioSigned | kAudio16)
    };

    /**
    *  AudioSpec struct.
    *  This struct is used to store Audio data specifications.
    */
    struct AudioSpec
    {
        // frequenza campionamento
        unsigned int samplerate;
        // formato audio
        unsigned int format;
        // numero canali, 1 mono, 2 stereo
        unsigned int channels;

        AudioSpec() : samplerate(0), format(kAudioUndefined), channels(0) {}
        AudioSpec(unsigned int _samplerate, unsigned int _format, unsigned int _channels) : samplerate(_samplerate), format(_format), channels(_channels) {}
    };

}


#endif
