/*
* AMConfig.h
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/
#ifndef		_AM_CONFIG_H_
#define		_AM_CONFIG_H_

#if defined(_WIN32)
   #ifdef ADAPTER_DLL_EXPORT
        #define ADAPTER_API __declspec(dllexport)
   #else
        #define ADAPTER_API
   #endif
#else
   #define ADAPTER_API
#endif

#define  AM_LOG_ENABLE				//是否启用总Log
#define  AM_LOG_DEBUG_ENABLE        //启动Debug Log
#define  AM_LOG_INFO_ENABLE 		//启动Info Log
#define  AM_LOG_WARNING_ENABLE      //启动Warning Log
#define  AM_LOG_ERROR_ENABLE        //启动Error Log

#include "AMMemoryConfig.h"         //内存管理配置
#include "AMSocketConfig.h"
#include "AMThreadConfig.h"

#endif		//_AM_CONFIG_H_
