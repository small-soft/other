/*
* AMTypes.h
*
*  Created on: 2009-11-19
*      Author: qinghua.liqh
*/
#ifndef _AM_TYPES_H_
#define _AM_TYPES_H_

/*
 * @defgroup 基本类型定义, AMII层只能用这些基本类型.
 * @{
 */
#if (!defined(__SYMBIAN32__)) && defined(_WIN32)        //windows and wince
typedef void                AMVoid;
typedef char                AMChar;
typedef unsigned char       AMUChar;
typedef char                AMInt8;
typedef unsigned char       AMUInt8;
typedef short               AMInt16;
typedef unsigned short      AMUInt16;
typedef int                 AMInt32;
typedef unsigned int        AMUInt32;
typedef __int64             AMInt64;        
typedef unsigned __int64    AMUInt64;
typedef float               AMFloat;
typedef double              AMDouble;
typedef void*               AMPVoid;
typedef AMUInt32            AMSize_t;

#pragma warning(disable:4985;disable:4005;disable:4047)
#define __func__ __FUNCTION__

#include "wctype.h"
typedef wchar_t				AMWChar;
#else 
//#ifdef ANDROID_BUILD
#if defined (ANDROID_BUILD) || defined (IOS_BUILD)
#include <stdio.h>
#include <string.h>         //avoid warning , like sprintf, strcpy.
#endif
typedef void                AMVoid;
typedef char                AMChar;
typedef unsigned char       AMUChar;
typedef char                AMInt8;
typedef unsigned char       AMUInt8;
typedef short               AMInt16;
typedef unsigned short      AMUInt16;
typedef int                 AMInt32;
typedef unsigned int        AMUInt32;
typedef long long           AMInt64;
typedef unsigned long long  AMUInt64;
typedef float               AMFloat;
typedef double              AMDouble;
typedef void*               AMPVoid;
typedef AMUInt32            AMSize_t;

#include "stddef.h"
typedef wchar_t      		AMWChar;
#endif

//下面是, 险峰在做地图的时候加的, 我不建议放在这里. 担心移除后地图那边编译不过, 
//AMII层不能使用
#define	 AMC8  AMChar
#define  AMU8  AMUChar
#define	 AMU16 AMUInt16
#define	 AMU32 AMUInt32
#define	 AMI8  AMInt8
#define	 AMI16 AMInt16
#define	 AMI32 AMInt32
#define	 AMF32 AMFloat
#define  AMD64 AMDouble
#define	 AMPV  AMPVoid


typedef AMPVoid AMHandle;

/** AMBool类型 */
typedef AMUChar               AMBool;
#define AMTRUE                1
#define AMFALSE               0

#ifndef AMNULL
#ifdef __cplusplus
#define AMNULL    0
#else
#define AMNULL    ((void *)0)
#endif
#endif

/** @} */
#endif  //end of _AM_TYPES_H_
