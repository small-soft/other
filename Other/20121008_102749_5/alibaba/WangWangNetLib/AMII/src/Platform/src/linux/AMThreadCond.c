/*
 * athread_cond.cpp
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */
#ifndef ATHREAD_COND_CPP_
#define ATHREAD_COND_CPP_

#include "AMThreadCond.h"
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include "AMAssert.h"

AMInt32 AMThreadCondCreate(AMThreadCond * cond)
{
	AMInt32 err_code = 0;
    CHECK_PARG_AND_RET(cond);
	
    *cond = (AMPVoid)malloc(sizeof(pthread_cond_t));
	CHECK_AND_RETV(*cond, AME_MALLOC_ERROR);
	err_code =  pthread_cond_init((pthread_cond_t*)*cond, NULL);
	
	if(0 == err_code)
		return AME_COND_SCUESS;
	else
		return AME_COND_ERROR;
}

AMInt32 AMThreadCondDestroy (AMThreadCond * cond)
{
	AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(cond);
	err_code = pthread_cond_destroy((pthread_cond_t*)*cond);
	CHECK_EQUAL_AND_RETV(EBUSY, err_code,  AME_COND_BUSY);
	CHECK_EQUAL_AND_RETV(EINVAL, err_code, AME_COND_ERROR);
	
	free(*cond);
	return AME_COND_SCUESS;
}

AMInt32 AMThreadCondWait (AMThreadCond * cond, AMThreadMutex * mutex)
{
    AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(cond);
	CHECK_PARG_AND_RET(mutex);

    err_code = pthread_cond_wait((pthread_cond_t*)*cond, (pthread_mutex_t*)*mutex);
	CHECK_EQUAL_AND_RETV(0, err_code,  AME_COND_SCUESS);
	CHECK_EQUAL_AND_RETV(EPERM, err_code,  AME_COND_NOT_OWN_MUTEX);
	CHECK_EQUAL_AND_RETV(EINVAL, err_code,  AME_COND_ERROR);
	return AME_COND_MUTEX_DIFF;
}

AMInt32 AMThreadCondTimewait (AMThreadCond * cond,
			    AMThreadMutex * mutex,
			    const struct AMTimeval* abstime)
{
    struct timespec tp;
    AMInt32 err_code = 0;
	CHECK_PARG_AND_RET(cond);
	CHECK_PARG_AND_RET(mutex);
	CHECK_PARG_AND_RET(abstime);
	
    tp.tv_sec = abstime->tv_sec;
    tp.tv_nsec = abstime->tv_usec * 1000;
	err_code = pthread_cond_timedwait((pthread_cond_t*)*cond, (pthread_mutex_t*)*mutex, &tp);
	
	CHECK_EQUAL_AND_RETV(0, err_code,  AME_COND_SCUESS);
	CHECK_EQUAL_AND_RETV(ETIMEDOUT, err_code,  AME_COND_TIMEOUT);
	CHECK_EQUAL_AND_RETV(EPERM, err_code,  AME_COND_NOT_OWN_MUTEX);
	CHECK_EQUAL_AND_RETV(EINVAL, err_code,  AME_COND_ERROR);
	return AME_COND_MUTEX_DIFF;
}

AMInt32 AMThreadCondSignal (AMThreadCond * cond)
{
	AMInt32 err_code;
    CHECK_PARG_AND_RET(cond);

    err_code = pthread_cond_signal((pthread_cond_t*)*cond);
    CHECK_EQUAL_AND_RETV(0, err_code,  AME_COND_SCUESS);
    return AME_COND_ERROR;
}

#endif /* ATHREAD_COND_CPP_ */

