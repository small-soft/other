/*
 * AMThreadMutex.c
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */
#include "AMThreadMutex.h"
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include "AMAssert.h"

#define  PTHREAD_MUTEX_RECURSIVE_NP 0
AMInt32 AMThreadMutexCreate (AMThreadMutex * mutex)
{
    AMInt32 err_code = 0;
    pthread_mutexattr_t pattr;
    CHECK_PARG_AND_RET(mutex);

    *mutex = (AMPVoid)malloc(sizeof(pthread_mutex_t));
	CHECK_AND_RETV(*mutex, AME_MALLOC_ERROR);
	
	pthread_mutexattr_init(&pattr);
	pthread_mutexattr_settype(&pattr, PTHREAD_MUTEX_RECURSIVE_NP); 
	err_code =  pthread_mutex_init((pthread_mutex_t*)*mutex, &pattr);
    pthread_mutexattr_destroy(&pattr);
	
	CHECK_EQUAL_AND_RETV(0,err_code, AME_MUTEX_SCUESS);

	free(*mutex);
	return AME_MUTEX_ERROR;
}

AMInt32 AMThreadMutexDestroy (AMThreadMutex * mutex)
{
	AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(mutex);
	
	err_code = pthread_mutex_destroy((pthread_mutex_t*)*mutex);
	CHECK_EQUAL_AND_RETV(EBUSY,err_code,  AME_MUTEX_BUSY);
	CHECK_EQUAL_AND_RETV(EINVAL,err_code, AME_MUTEX_ERROR);
	// 成功, 则释放空间
	free(*mutex);
	return AME_MUTEX_SCUESS;
}

AMInt32 AMThreadMutexLock (AMThreadMutex * mutex)
{
	//AMLogForDebug("AMThread", __func__);
	AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(mutex);
	
	err_code = pthread_mutex_lock((pthread_mutex_t*)*mutex);
	CHECK_EQUAL_AND_RETV(0,err_code,  AME_MUTEX_SCUESS);
	CHECK_EQUAL_AND_RETV(EBUSY,err_code,  AME_MUTEX_BUSY);
	return AME_MUTEX_ERROR;
}

AMInt32 AMThreadMutexUnlock (AMThreadMutex * mutex)
{
	AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(mutex);
	
	err_code = pthread_mutex_unlock((pthread_mutex_t*)*mutex);
	CHECK_EQUAL_AND_RETV(0, err_code,  AME_MUTEX_SCUESS);
	return AME_MUTEX_ERROR;
}

#ifdef AMTHREAD_MUTEX_SPPORT_TRY_LOCK
AMInt32 AMThreadMutexTryLock (AMThreadMutex * mutex)
{
	AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(mutex);
	
	err_code = pthread_mutex_trylock((pthread_mutex_t*)*mutex);
	CHECK_EQUAL_AND_RETV(0,err_code,  AME_MUTEX_SCUESS);
	CHECK_EQUAL_AND_RETV(EBUSY,err_code,  AME_MUTEX_BUSY);
	return AME_MUTEX_ERROR;
}
#endif
