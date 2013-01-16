/*
 * AMThread.c
 *
 *  Created on: 2009-11-17
 *      Author: qinghua.liqh
 */
#include "AMThread.h"
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include "AMMemory.h"
#include "AMAssert.h"


struct AMThreadAttr_
{
	AMInt32     prority;			//优先级
	AMInt32     status;				//当前状态.
	AMUInt32  	stackSize;		    //堆栈大小
	AMPVoid		stackAddr;		    //堆栈位置.
};

AMInt32 AMThreadAttrInit (AMThreadAttr * attr)
{
    //AMLogForDebug("AMThread", "AMThreadAttrInit");
    CHECK_PARG_AND_RET(attr);
    //分配空间
    *attr = (AMThreadAttr)malloc(sizeof(struct AMThreadAttr_));
    CHECK_AND_RETV(*attr, AME_MALLOC_ERROR);
    memset(*attr,  0, sizeof(struct AMThreadAttr_));

    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrDestroy (AMThreadAttr * attr)
{
    //AMLogForDebug("AMThread", "AMThreadAttrDestroy");
    CHECK_PARG_AND_RET(attr);

    free(*attr);
    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrGetStackAddr (const AMThreadAttr * attr, void **stackaddr)
{
    //AMLogForDebug("AMThread", "AMThreadAttrGetStackAddr");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    CHECK_PARG_AND_RET(attr_);
    CHECK_PARG_AND_RET(stackaddr);

    *stackaddr = attr_->stackAddr;
    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrGetStackSize (const AMThreadAttr* attr, AMUInt32* stacksize)
{
    //AMLogForDebug("AMThread", "AMThreadAttrGetStackSize");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    CHECK_PARG_AND_RET(attr_);
    CHECK_PARG_AND_RET(stacksize);

    *stacksize = attr_->stackSize;
    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrSetStackAddr (AMThreadAttr * attr, void *stackaddr)
{
    //AMLogForDebug("AMThread", "AMThreadAttrSetStackAddr");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    CHECK_PARG_AND_RET(attr_);
    CHECK_PARG_AND_RET(stackaddr);

    attr_->stackAddr = stackaddr;
    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrSetStackSize (AMThreadAttr * attr, AMUInt32 stacksize)
{
    //AMLogForDebug("AMThread", "AMThreadAttrSetStackSize");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    CHECK_PARG_AND_RET(attr_);

    attr_->stackSize = stacksize;
    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadCreate(AMThread * tid, const AMThreadAttr * attr, AMPVoid (*start) (AMPVoid), AMPVoid arg)
{
    //AMLogForDebug("AMThread", "AMThreadCreate");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    AMInt32 ret_value = AME_THREAD_SCUESS;
    pthread_attr_t pattr;
    
    CHECK_PARG_AND_RET(tid);
    CHECK_PARG_AND_RET(start);

    *tid = malloc(sizeof(pthread_t));
    CHECK_AND_RETV(*tid, AME_MALLOC_ERROR);

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

AMInt32 AMThreadDetach (AMThread tid)
{
    //AMLogForDebug("AMThread", "AMThreadDetach");
    AMInt32 ret_code = pthread_detach(*(pthread_t*)tid);
    CHECK_NOTEQUAL_AND_RETV(ret_code, 0, AME_THREAD_ERROR);

    return AME_THREAD_SCUESS;
}

void AMThreadExit (void *value_ptr)
{
    //AMLogForDebug("AMThread", "AMThreadExit");
    pthread_exit(value_ptr);
}

AMInt32 AMThreadWait (AMThread thread, AMPVoid* value_ptr)
{
    //AMLogForDebug("AMThread", "AMThreadJoin");
    AMInt32 ret_code = pthread_join(*(pthread_t*)thread, value_ptr);
    free(thread);
    CHECK_NOTEQUAL_AND_RETV(ret_code, 0, AME_THREAD_ERROR);

    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrGetPrority (const AMThreadAttr* attr, AMInt32* prority)
{
    //AMLogForDebug("AMThread", "AMThreadAttrGetPrority");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;\
    CHECK_PARG_AND_RET(attr_);
    CHECK_PARG_AND_RET(prority);

    *prority = attr_->prority;

    return AME_THREAD_SCUESS;
}

AMInt32 AMThreadAttrSetPrority (AMThreadAttr* attr, AMInt32 prority)
{
    //AMLogForDebug("AMThread", "AMThreadAttrSetPrority");
    struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
    CHECK_PARG_AND_RET(attr_);

    attr_->prority = prority % AM_THREAD_REALTIME;
    return AME_THREAD_SCUESS;
}
