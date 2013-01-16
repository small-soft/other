#ifndef __ALIJNILOG_H__
#define __ALIJNILOG_H__

#include <android/log.h>

#define JNI_DEBUG

#ifdef JNI_DEBUG
#define JNI_LOGD(tag, string)		__android_log_print(ANDROID_LOG_DEBUG, tag, string)
#define JNI_LOGE(tag, string)		__android_log_print(ANDROID_LOG_ERROR, tag, string)
#else
#define JNI_LOGD(tag, string)
#define JNI_LOGE(tag, string)
#endif


#endif //__ALIJNILOG_H__