/*
* AMFs.c
*
*  Created on: 2009-11-24
*      Author: qinghua.liqh
*/
#include "AMFS.h"
#include "stdio.h"
#include "AMLog.h"


#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
#include <windows.h>
#else
#include "sys/unistd.h"
#endif


ADAPTER_API AMFILE* a_fopen(const AMChar* filename, const AMChar* flags)
{
    if(NULL == filename || NULL == flags)
        return NULL;
    else
    {
        FILE* filefd = fopen(filename, flags);
#ifdef _DEBUG
        //if(filefd == NULL)
        //    AMLogForError("a_fopen", filename);
#endif

        return filefd;
    }
}

ADAPTER_API AMInt32 a_fclose(AMFILE* file)
{
    if(file == NULL)
        return AME_ARG_AINVALID;
    else
    {
        int ret = fclose(file);
#ifdef _DEBUG
        //if(ret != 0)
        //    AMLogForError("a_fclose", "fclose() != 0");
#endif
        return ret;
    }
}

ADAPTER_API AMSize_t a_fread(AMPVoid buffer, AMSize_t size, AMSize_t count, AMFILE* file)
{
    if(NULL == file)
        return AME_ARG_AINVALID;
    else
    {
       AMSize_t readCount =  fread(buffer, size, count, file);
       return readCount;
    }
}

ADAPTER_API AMSize_t a_fwrite(const AMVoid* buffer, AMSize_t size, AMSize_t count, AMFILE * file)
{
    if(NULL == buffer || NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        AMSize_t writeCount = fwrite(buffer, size, count, file);
        return writeCount;
    }
}

ADAPTER_API AMInt32 a_fgetc(AMFILE * file)
{
    if(NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        AMInt32 c = fgetc(file);
        return c;
    }
}

ADAPTER_API AMInt32 a_fputc(AMInt32 c, AMFILE * file)
{
    if(NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        AMInt32 retc = fputc(c, file);
        return retc;
    }
}

ADAPTER_API AMInt32 a_fseek(AMFILE * file, AMInt32 offset, AMInt32 flag)
{
    if(flag < AM_SEEK_SET || flag > AM_SEEK_END || NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        AMInt32 ret = fseek(file, offset, flag);
#ifdef _DEBUG
        if(ret != 0)
             AMLogForError("a_fseek", "fseek() != 0");
#endif
        return ret;
    }
}

ADAPTER_API AMInt32 a_ftell(AMFILE * file)
{
    if(NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        AMInt32 pos = ftell(file);
#ifdef _DEBUG
        if(pos == -1)
             AMLogForError("a_ftell", "a_ftell() == -1");
#endif
        return pos;
    }
}

ADAPTER_API AMInt32 a_feof(AMFILE * file)
{
    if(NULL == file)
        return AME_ARG_AINVALID;
    else
    {
        return feof((FILE*)file);
    }
}

ADAPTER_API AMInt32 a_ferrno(AMFILE * file)
{
	if(NULL == file)
		return AME_ARG_AINVALID;
	else
	{
		return ferror((FILE*)file);
	}
}

ADAPTER_API AMVoid a_clearerr(AMFILE * file)
{
	if(NULL == file)
		return;
	else
	{
		clearerr((FILE*)file);
	}
}

ADAPTER_API AMChar* a_getcwd (AMChar* buffer, AMInt32 size)
{
    if(NULL == buffer)
        return NULL;
    else
    {
#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
        int index, i;
        AMChar* pwd = NULL;
        WCHAR wbuffer[256];
        GetModuleFileName(NULL, wbuffer, 256); 
        WideCharToMultiByte(CP_ACP, 0, wbuffer, wcslen(wbuffer), buffer, size, NULL, NULL);
        index = strlen(buffer);
        for(i = index; i > 0; i--)
        {
            if(buffer[i - 1] == '\\' || buffer[i - 1] == '/')
            {
                buffer[i - 1] = 0;
                break;
            }
        }
        return  buffer;
#else
        AMChar* pwd = getcwd(buffer, size);
#endif

#ifdef _DEBUG
        if(pwd == NULL)
             AMLogForError("a_getcwd", "a_getcwd() == NULL");
#endif
        return pwd;
    }
}

AMInt32 a_remove(const AMChar * filename)
{
    if(NULL == filename)
        return AME_ARG_AINVALID;
    else
    {
        return _unlink(filename);
    }
}

AMInt32 a_rename(const AMChar * oldfilename, const AMChar * newfilename)
{
	if(NULL == oldfilename || NULL == newfilename)
        return AME_ARG_AINVALID;
    else
    {
        return rename(oldfilename, newfilename);
    }
}

AMInt32   a_flen(AMChar* buffer)
{
    AMInt32 ret  = -1;
    AMInt32 value = 0;
    AMFILE* file = AMFopen(buffer, "rb");
    if(file == AMNULL)
        return -1;
    if((value = AMFseek(file, 0, AM_SEEK_END)) == 0)
    {
        ret = AMFtell(file);
    }
	AMFclose(file);
    return ret;
}
