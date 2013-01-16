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

#define  AM_LOG_ENABLE				//�Ƿ�������Log
#define  AM_LOG_DEBUG_ENABLE        //����Debug Log
#define  AM_LOG_INFO_ENABLE 		//����Info Log
#define  AM_LOG_WARNING_ENABLE      //����Warning Log
#define  AM_LOG_ERROR_ENABLE        //����Error Log

#include "AMMemoryConfig.h"         //�ڴ��������
#include "AMSocketConfig.h"
#include "AMThreadConfig.h"

#endif		//_AM_CONFIG_H_
