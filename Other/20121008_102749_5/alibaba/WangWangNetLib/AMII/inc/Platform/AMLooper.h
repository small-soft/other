#ifndef _AME_LOOPER_LOOPER_
#define _AME_LOOPER_LOOPER_
/*
 * @defgroup AMLooper模块
 * @{
 */
#include "AMLooperConfig.h"

struct AMLooper;

#ifdef __cplusplus 
extern "C" {
#endif
    //建立looper
    ADAPTER_API AMInt32 AMLooperCreate(struct AMLooper** looper);
    //关闭looper
    ADAPTER_API AMInt32 AMLooperClose(struct AMLooper* looper);
    //执行looper
    ADAPTER_API AMInt32 AMLooperLoop(struct AMLooper* looper);
    //创建线程是提供的回调函数, 参数要求是Looper*
    ADAPTER_API AMPVoid AMLooperCallback(AMPVoid v);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif
