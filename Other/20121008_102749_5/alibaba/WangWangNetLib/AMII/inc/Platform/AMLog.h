/*
* AMLog.h
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/
#ifndef _AM_LOG_H_
#define _AM_LOG_H_

#include "AMErrno.h"
#include "AMTypes.h"
#include "AMConfig.h"

//log级别标志. 等级是一种包含关系, 值越大等级越高
#define AMLOG_FLAG_DEBUG    1           //调试信息
#define AMLOG_FLAG_INFO     2           //打印信息
#define AMLOG_FLAG_WARNING  4           //警告标志
#define AMLOG_FALG_ERROR    8           //错误标志

#ifdef AM_LOG_DEBUG_ENABLE
#undef AM_LOG_INFO_ENABLE
#define AM_LOG_INFO_ENABLE
#undef AM_LOG_WARNING_ENABLE
#define AM_LOG_WARNING_ENABLE
#undef AM_LOG_ERROR_ENABLE
#define AM_LOG_ERROR_ENABLE
#else
#ifdef AM_LOG_INFO_ENABLE
#undef AM_LOG_WARNING_ENABLE
#define AM_LOG_WARNING_ENABLE
#undef AM_LOG_ERROR_ENABLE
#define AM_LOG_ERROR_ENABLE
#else
#ifdef AM_LOG_WARNING_ENABLE
#undef AM_LOG_ERROR_ENABLE
#define AM_LOG_ERROR_ENABLE
#endif
#endif
#endif

//AMSetLogFlag      设置Log的等级   
//AMLogForError     输出Error Log
//AMLogForWarning   输出Warning Log
//AMLogForInfo      输出Info Log
//AMLogForDebug     输出Debug Log

//Log的总开关关闭
#ifdef AM_LOG_ENABLE
#ifdef __cplusplus 
extern "C" {
#endif
    ADAPTER_API AMInt32 AMSetLogFlag(const AMChar* moduleName, int logFlag);
#ifdef AM_LOG_ERROR_ENABLE
    ADAPTER_API AMVoid  AMLogForError(const AMChar* moduleName, const AMChar* errorStr);
#ifdef AM_LOG_WARNING_ENABLE
    ADAPTER_API AMVoid  AMLogForWarning(const AMChar* moduleName, const AMChar* warningStr);
#ifdef AM_LOG_INFO_ENABLE
    ADAPTER_API AMVoid  AMLogForInfo(const AMChar* moduleName, const AMChar* infoStr);
#ifdef AM_LOG_DEBUG_ENABLE
    ADAPTER_API AMVoid  AMLogForDebug(const AMChar* moduleName, const AMChar* denugInfo);
#else
#define AMLogForDebug 
#endif
#else 
#define AMLogForDebug 
#define AMLogForInfo
#endif
#else
#define AMLogForWarning
#define AMLogForInfo
#define AMLogForDebug 
#endif
#else
#define AMLogForError
#define AMLogForWarning
#define AMLogForInfo
#define AMLogForDebug 
#endif
#else
#define setLogFlag
#define AMLogForError
#define AMLogForWarning
#define AMLogForInfo
#define AMLogForDebug 
#endif

#if defined(__SYMBIAN32__) 
#include "stdarg.h"
int AMprintf(const AMChar* module, const AMChar *fmt, ...);
int AMsprintf(AMChar * buf, const AMChar *fmt, ...);
int AMvsprintf(AMChar *buf, const AMChar *fmt, va_list args);
#endif
    
#ifdef __cplusplus 
    }
#endif

#endif //_AM_LOG_H_
