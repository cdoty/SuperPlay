/* ****************************************************************************

HSS Engine ver 0.99.5 - 02/12/2004
    by Thomas Maniero - last modified 08/12/2011

todo:

**************************************************************************** */
#ifndef _HSSFILE_H
#define _HSSFILE_H

#include "hssImpExp.h"
#include "hssTypes.h"
#include "hssErrorDefs.h"
#include "hssConfig.h"

#if defined(__SYMBIAN32__)
    #include <f32file.h>
#elif defined(BADA)
	#include <FBase.h>
	#include <FIo.h>
#elif (defined(__ANDROID__) || defined(__OSFILE__))
	#include "../external/oafile/appfile.h"
#else
    #include <stdio.h>
#endif


#define PF_SEEK_CUR 0
#define PF_SEEK_SET 1
#define PF_SEEK_END 2


namespace hss
{

    class HSS_CLS_API FileInterface
    {
    public:
        HSS_API_H FileInterface() {}
        HSS_API_H virtual ~FileInterface() {}

        HSS_API_H virtual bool open(const char *filename, bool unicode_filename, long length = 0, bool copy_to_memory = false) = 0;
        HSS_API_H virtual bool close() = 0;

        HSS_API_H virtual long read(void *buf, long length) = 0;

        HSS_API_H virtual bool seek(long offset, int origin) = 0;
        HSS_API_H virtual long tell() = 0;
        HSS_API_H virtual long size() = 0;
    };


    class HSS_CLS_API FileMemory : public FileInterface
    {
    private:
        char *m_buffer;
        int m_position, m_length;

    public:
        HSS_API_H FileMemory();
        HSS_API_H virtual ~FileMemory();

        HSS_API_H virtual bool open(const char *filename, bool unicode_filename, long length = 0, bool copy_to_memory = false);
        HSS_API_H virtual bool close();

        HSS_API_H virtual long read(void *buf, long length);

        HSS_API_H virtual bool seek(long offset, int origin);
        HSS_API_H virtual long tell();
        HSS_API_H virtual long size();
    };


    class HSS_CLS_API FileMulti : public FileInterface
    {
    private:
#if defined(__SYMBIAN32__)
        RFs   m_fsession;
        RFile m_file;
        bool m_open;
#elif defined(BADA)
        Osp::Io::File *m_file;
#elif (defined(__ANDROID__) || defined(__OSFILE__))
        AFILE *m_file;
#else
        FILE *m_file;
#endif

    public:
        HSS_API_H FileMulti();
        HSS_API_H virtual ~FileMulti();

        HSS_API_H virtual bool open(const char *filename, bool unicode_filename, long length = 0, bool copy_to_memory = false);
        HSS_API_H virtual bool close();

        HSS_API_H virtual long read(void *buf, long length);

        HSS_API_H virtual bool seek(long offset, int origin);
        HSS_API_H virtual long tell();
        HSS_API_H virtual long size();
    };


    class HSS_CLS_API File
    {
    private:
        FileInterface *m_file;

    public:
        HSS_API_H File();
        HSS_API_H ~File();

        HSS_API_H bool open(const char *filename, bool unicode_filename, long length = 0, bool copy_to_memory = false);
        HSS_API_H bool close();

        HSS_API_H long read(void *buf, long length);

        HSS_API_H bool seek(long offset, int origin);
        HSS_API_H long tell();
        HSS_API_H long size();
    };

}


#endif
