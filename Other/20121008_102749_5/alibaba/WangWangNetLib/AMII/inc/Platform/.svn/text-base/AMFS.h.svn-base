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

//实现的时候可以定位到特定平台
typedef void AMFILE;

#define AM_EOF 		    -1
#define AM_SEEK_SET     0
#define AM_SEEK_CUR     1
#define AM_SEEK_END     2

//目前只是提供下面的一些接口.
#define AMFopen	    a_fopen			    //打开
#define AMFclose 	a_fclose			//关闭
#define AMFread	    a_fread			    //读
#define AMFwrite	a_fwrite			//写
#define AMFgetc	    a_fgetc			    //读一个字符
#define AMFputc	    a_fputc			    //写一个字符
#define AMFseek	    a_fseek			    //移动到..
#define AMFRewind	a_rewind			//移动到头
#define AMFtell	    a_ftell			    //当前位置
#define AMFeof		a_feof			    //是否文件尾
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

#define AMGetcwd    a_getcwd            //得到绝对当前工作目录

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
//下面两个函数在讨论中说要添加Manager参数, 目前还不知道怎么加,
//要是谁要使用这两个函数可以一起看看怎么添加
#define AMFRemove	a_remove			//删除
#define AMFRename	a_rename			//重命名

#ifdef __cplusplus 
extern "C" {
#endif
    ADAPTER_API AMInt32		    a_remove(const AMChar * filename);
    ADAPTER_API AMInt32		    a_rename(const AMChar * oldfilename, const AMChar * newfilename);
#ifdef __cplusplus 
}
#endif
#endif //_AM_FS_H_

