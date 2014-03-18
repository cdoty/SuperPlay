/* ****************************************************************************

HSS error defs header - 12/03/2004
    by Thomas Maniero - last modified 12/05/2005

todo:

**************************************************************************** */
#ifndef _HSSERRDEFS_H
#define _HSSERRDEFS_H

namespace hss
{

    enum
    {
        // no error
        kOk                    =  0,
        // generic error
        kFail                  = -1,
        // output format not supported
        kErrorOutputFormat     = -2,
        // sound system already initialized
        kErrorAlreadyAllocated = -3,
        // sound system not initialized
        kErrorNotAllocated     = -4,
        // error initializing thread output device
        kErrorThread           = -5,
        // error initializing driver output device
        kErrorDriver           = -6,
        // not enough memory
        kErrorOutOfMemory      = -7,
        // file format not supported
        kErrorWrongFileFormat  = -8,
        // file not found
        kErrorFileNotFound     = -9,
        // error loading file
        kErrorBadFile          = -10,
        // playing the sound failed
        kErrorPlay             = -11,
        // bad buffer size (too low?)
        kErrorBufferLength     = -12,

        kPlayFree         = 0x10000000,
        kPlayPaused       = 0x20000000,

        kLoadDefault        = 0x0000,
        kLoadCopyToMemory   = 0x0001,
        kLoadAndDecode      = 0x0002,
        kLoadMemoryBuffer   = 0x0004,
        kLoadStreamFromDisk = 0x0008,
        kLoadUseUnicode     = 0x0010,
        kCreateSoundStream  = 0x0100
    };

}


#endif
