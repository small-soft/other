/*
* AMFS.h
*
*  Created on: 2009-11-24
*      Author: qinghua.liqh
*/
#ifndef _AM_FS_H_
#define _AM_FS_H_
#include "AMErrno.h"
#include "AMTypes.h"

#if defined(ANDROID_BUILD)
#include <android/log.h>
#endif

//ʵ�ֵ�ʱ����Զ�λ���ض�ƽ̨
typedef void AMFILE;

#define AM_EOF 		    -1
#define AM_SEEK_SET     0
#define AM_SEEK_CUR     1
#define AM_SEEK_END     2

//Ŀǰֻ���ṩ�����һЩ�ӿ�.
#define AMFopen	    a_fopen			    //��
#define AMFclose 	a_fclose			//�ر�
#define AMFread	    a_fread			    //��
#define AMFwrite	a_fwrite			//д
#define AMFgetc	    a_fgetc			    //��һ���ַ�
#define AMFputc	    a_fputc			    //дһ���ַ�
#define AMFseek	    a_fseek			    //�ƶ���..
#define AMFRewind	a_rewind			//�ƶ���ͷ
#define AMFtell	    a_ftell			    //��ǰλ��
#define AMFeof		a_feof			    //�Ƿ��ļ�β
#define AMFflush 	a_fflush            //flush
#define AMFLen	    a_flen				//flush
#define AMClearerr	a_clearerr
#define AMFErrno	a_ferrno

#if (!defined(__SYMBIAN32__)) && defined(_WIN32)        //windows and wince
#define AMPrintf	printf
//int printf(const char *, ...);
#include "stdio.h"
#define AMSprintf	sprintf
#define AMSscanf	sscanf

#elif defined(ANDROID_BUILD)
#define AMPrintf(format...)	 __android_log_print(ANDROID_LOG_INFO, "printf", format)
#define AMSprintf	sprintf
#define AMSscanf	sscanf

#elif defined(__SYMBIAN32__)
#define AMPrintf    AMprintf
#define AMSprintf   AMsprintf
#else
#define AMPrintf	printf
#define AMSprintf	sprintf
#define AMSscanf	sscanf
#endif

#define AMGetcwd    a_getcwd            //�õ����Ե�ǰ����Ŀ¼

#ifdef __cplusplus 
extern "C" {
#endif
    ADAPTER_API AMFILE*		    a_fopen(const AMChar* filename, const AMChar* flags);							
    ADAPTER_API AMInt32		    a_fclose(AMFILE* file);
    ADAPTER_API AMSize_t		a_fread(AMPVoid buffer, AMSize_t size, AMSize_t count, AMFILE* file);
    ADAPTER_API AMSize_t		a_fwrite(const AMVoid* buffer, AMSize_t size, AMSize_t count, AMFILE * file);
    ADAPTER_API AMInt32		    a_fgetc(AMFILE * file);
    ADAPTER_API AMInt32		    a_fputc(AMInt32 c, AMFILE * file);
    ADAPTER_API AMInt32		    a_fseek(AMFILE * file, AMInt32 offset, AMInt32 flag);
    ADAPTER_API AMInt32		    a_ftell(AMFILE * file);
    ADAPTER_API AMInt32		    a_feof(AMFILE * file);
    ADAPTER_API AMInt32     	a_fflush(AMFILE * file);
    ADAPTER_API AMInt32 		a_printf(const AMChar * format, ...);
    ADAPTER_API AMInt32 		a_sprintf(AMChar* buffer, const AMChar * format, ...);
    ADAPTER_API AMChar*         a_getcwd (AMChar* buffer, AMInt32  size);
	ADAPTER_API AMInt32         a_flen(AMChar* buffer);
	ADAPTER_API AMInt32			a_ferrno(AMFILE * file);
	ADAPTER_API AMVoid			a_clearerr(AMFILE * file);
#ifdef __cplusplus 
}
#endif
//��������������������˵Ҫ���Manager����, Ŀǰ����֪����ô��,
//Ҫ��˭Ҫʹ����������������һ�𿴿���ô���
#define AMFRemove	a_remove			//ɾ��
#define AMFRename	a_rename			//������

#ifdef __cplusplus 
extern "C" {
#endif
    ADAPTER_API AMInt32		    a_remove(const AMChar * filename);
    ADAPTER_API AMInt32		    a_rename(const AMChar * oldfilename, const AMChar * newfilename);
#ifdef __cplusplus 
}
#endif
#endif //_AM_FS_H_

