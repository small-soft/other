/*
 * AMThread.c
 *
 *  Created on: 2009-11-17
 *      Author: qinghua.liqh
 */
#include <pthread.h>
#include <stdlib.h>
#include "AMThread.h"


struct AMThreadAttr_
{
	AMInt32     prority;			//优先级
	AMInt32     status;				//当前状态.
	AMUInt32  	stackSize;		    //堆栈大小
	AMPVoid		stackAddr;		    //堆栈位置.
};

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrCreate(AMThreadAttr * attr)
{
    if(NULL == attr)
        return AME_THREAD_ERROR;

    *attr = malloc(sizeof(struct AMThreadAttr_));
    memset(*attr,  0, sizeof(struct AMThreadAttr_));
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrDestroy (AMThreadAttr * attr)
{
    if(NULL == attr)
        return AME_THREAD_ERROR;

    free(*attr);
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackAddr (const AMThreadAttr * attr, void **stackaddr)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    if(NULL == attr_ || stackaddr == NULL)
        return AME_THREAD_ERROR;

    *stackaddr = attr_->stackAddr;
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackSize (const AMThreadAttr* attr, AMUInt32* stacksize)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    if(NULL == attr_ || stacksize == NULL)
        return AME_THREAD_ERROR;


    *stacksize = attr_->stackSize;
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackAddr (AMThreadAttr * attr, void *stackaddr)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    if(NULL == attr_ || NULL == stackaddr)
         return AME_THREAD_ERROR;

    attr_->stackAddr = stackaddr;
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackSize (AMThreadAttr * attr, AMUInt32 stacksize)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    if(NULL == attr_)
         return AME_THREAD_ERROR;

    attr_->stackSize = stacksize;
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCreate(AMThread * tid, const AMThreadAttr * attr, void *(*start) (void *), void *arg)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    AMInt32 ret_value = AME_THREAD_SCUESS;
    pthread_attr_t pattr;
    
    if(NULL == tid || NULL == start)
         return AME_THREAD_ERROR;

    *tid = malloc(sizeof(pthread_t));
    if(*tid == NULL)
        return AME_THREAD_ERROR;

    pthread_attr_init(&pattr);
    if(NULL != attr)
    {
        if(attr_->stackAddr != NULL)
            pthread_attr_setstackaddr(&pattr, attr_->stackAddr);
         if(attr_->stackSize > 0)
             pthread_attr_setstacksize(&pattr, attr_->stackSize);
    }

    if(pthread_create(*tid, &pattr, start, arg) != 0)
        ret_value = AME_THREAD_ERROR;


    pthread_attr_destroy(&pattr);
    return ret_value;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadDetach (AMThread tid)
{
    AMInt32 ret_code = pthread_detach(*(pthread_t*)tid);
    if(ret_code != 0)
        return AME_THREAD_ERROR;

	free(tid);
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT void AMThreadExit (void *value_ptr)
{
    pthread_exit(value_ptr);
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadWait (AMThread thread, void **value_ptr)
{
    AMInt32 ret_code = pthread_join(*(pthread_t*)thread, value_ptr);
    free(thread);
    if(ret_code != 0)
        return AME_THREAD_ERROR;

    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetPrority (const AMThreadAttr* attr, AMInt32* prority)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    return attr_->prority;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetPrority (AMThreadAttr* attr, AMInt32 prority)
{
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    attr_->prority = prority % AM_THREAD_REALTIME;
    return AME_THREAD_SCUESS;
}