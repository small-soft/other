/*
* AMLog.c
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/
#include "AMLog.h"
#include "AMFS.h"
#include "AMAssert.h"
#include "string.h"

#ifdef ANDROID_BUILD
#include <jni.h>
#include <android/log.h>

/*
#define GET_LOG_ENV(errorStr) 	NDKLogForInfo(moduleName, errorStr);\
						struct ThreadEnv* threadEnv = NULL;\
						NDKCheckNotEqual((threadEnv = NDKGetThreadEnv()), NULL);\
						JNIEnv *env = threadEnv->env;
*/

#ifdef AM_LOG_ERROR_ENABLE
AMVoid  AMLogForError(const AMChar* moduleName, const AMChar* errorStr)
{
	/*
	GET_LOG_ENV(errorStr);
	(*env)->CallStaticIntMethod(env, threadEnv->LogClass, threadEnv->LogE, 
		(*env)->NewStringUTF(env, moduleName), (*env)->NewStringUTF(env, errorStr));
	*/
#ifdef ANDROID_HUADONG
	printf("Error(%s): %s\n", moduleName, errorStr);	
#else
	__android_log_print(ANDROID_LOG_ERROR, moduleName, errorStr);
#endif
}
#endif//end of AM_LOG_ERROR_ENABLE

#ifdef AM_LOG_WARNING_ENABLE
AMVoid  AMLogForWarning(const AMChar* moduleName, const AMChar* warningStr)
{
	/*
	GET_LOG_ENV(warningStr);
	(*env)->CallStaticIntMethod(env, threadEnv->LogClass, threadEnv->LogV, 
		(*env)->NewStringUTF(env, moduleName), (*env)->NewStringUTF(env, warningStr));
	*/
#ifdef ANDROID_HUADONG
	printf("Warning(%s): %s\n", moduleName, warningStr);	
#else
	__android_log_print(ANDROID_LOG_WARN, moduleName, warningStr);
#endif
}
#endif//end of AM_LOG_WARNING_ENABLE

#ifdef AM_LOG_INFO_ENABLE
AMVoid  AMLogForInfo(const AMChar* moduleName, const AMChar* infoStr)
{
	/*
	GET_LOG_ENV(infoStr);
	(*env)->CallStaticIntMethod(env, threadEnv->LogClass, threadEnv->LogI, 
		(*env)->NewStringUTF(env, moduleName), (*env)->NewStringUTF(env, infoStr));
	*/
#ifdef ANDROID_HUADONG
	printf("Info(%s): %s\n", moduleName, infoStr);	
#else
	__android_log_print(ANDROID_LOG_INFO, moduleName, infoStr);
#endif
}
#endif//end of AM_LOG_INFO_ENABLE

#ifdef AM_LOG_DEBUG_ENABLE
AMVoid  AMLogForDebug(const AMChar* moduleName, const AMChar* denugInfo)
{
	/*
	GET_LOG_ENV(denugInfo);
	(*env)->CallStaticIntMethod(env, threadEnv->LogClass, threadEnv->LogD, 
		(*env)->NewStringUTF(env, moduleName), (*env)->NewStringUTF(env, denugInfo));
	*/
#ifdef ANDROID_HUADONG
	printf("Debug(%s): %s\n", moduleName, denugInfo);	
#else
	__android_log_print(ANDROID_LOG_DEBUG, moduleName, denugInfo);
#endif
}
#endif//end of AM_LOG_DEBUG_ENABLE

#else//else of ANDROID_BUILD

#ifdef AM_LOG_ERROR_ENABLE
AMVoid  AMLogForError(const AMChar* moduleName, const AMChar* errorStr)
{
}
#endif

#ifdef AM_LOG_WARNING_ENABLE
AMVoid  AMLogForWarning(const AMChar* moduleName, const AMChar* warningStr)
{
}
#endif

#ifdef AM_LOG_INFO_ENABLE
AMVoid  AMLogForInfo(const AMChar* moduleName, const AMChar* infoStr)
{
}
#endif

#ifdef AM_LOG_DEBUG_ENABLE
AMVoid  AMLogForDebug(const AMChar* moduleName, const AMChar* denugInfo)
{
}
#endif

#endif
