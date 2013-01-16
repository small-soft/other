#ifndef _AME_LOOPER_LOOPER_
#define _AME_LOOPER_LOOPER_
/*
 * @defgroup AMLooperģ��
 * @{
 */
#include "AMLooperConfig.h"

struct AMLooper;

#ifdef __cplusplus 
extern "C" {
#endif
    //����looper
    ADAPTER_API AMInt32 AMLooperCreate(struct AMLooper** looper);
    //�ر�looper
    ADAPTER_API AMInt32 AMLooperClose(struct AMLooper* looper);
    //ִ��looper
    ADAPTER_API AMInt32 AMLooperLoop(struct AMLooper* looper);
    //�����߳����ṩ�Ļص�����, ����Ҫ����Looper*
    ADAPTER_API AMPVoid AMLooperCallback(AMPVoid v);
#ifdef __cplusplus 
}
#endif
/** @} */
#endif
