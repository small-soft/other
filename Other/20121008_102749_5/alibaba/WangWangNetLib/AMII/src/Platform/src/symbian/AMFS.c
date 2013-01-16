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
        if(filefd == NULL)
            AMLogForError("a_fopen", filename);
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
        if(ret != 0)
            AMLogForError("a_fclose", "fclose() != 0");
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
    if(flag < AM_SEEK_SET || flag > AM_SEEK_SET || NULL == file)
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



