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

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondCreate (AMThreadCond * cond)
{
    AMInt32 err_code = 0;
    if(cond == NULL)
        return AME_ARG_AINVALID;
    *cond = (AMPVoid)malloc(sizeof(pthread_cond_t));
	err_code =  pthread_cond_init(*cond, NULL);
	if(0 == err_code)
		return AME_COND_SCUESS;
	else
		return AME_COND_ERROR;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondDestroy (AMThreadCond * cond)
{
    if(cond == NULL)
        return AME_ARG_AINVALID;

	pthread_cond_destroy(*cond);
	free(*cond);
	return AME_COND_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondWait (AMThreadCond * cond, AMThreadMutex * mutex)
{
    AMInt32 err_code;
    if(cond == NULL || mutex == NULL)
        return AME_ARG_AINVALID;

    err_code = pthread_cond_wait(*cond, *mutex);
	if(0 == err_code)
		return AME_COND_SCUESS;
    else if(EPERM  == err_code)
        return AME_COND_NOT_OWN_MUTEX;
	else if(EINVAL == err_code)
		return AME_COND_ERROR;
	else
		return AME_COND_MUTEX_DIFF;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondTimewait (AMThreadCond * cond,
			    AMThreadMutex * mutex,
			    const struct AMTimeval* abstime)
{
    struct timespec tp;
    AMInt32 err_code;

    if(cond == NULL || mutex == NULL)
        return AME_ARG_AINVALID;

    tp.tv_sec = abstime->tv_sec;
    tp.tv_nsec = abstime->tv_usec * 1000;
	err_code = pthread_cond_timedwait(*cond, *mutex, &tp);;
	if(0 == err_code)
		return AME_COND_SCUESS;
    else if(ETIMEDOUT == err_code)
        return AME_COND_TIMEOUT;
    else if(EPERM  == err_code)
        return AME_COND_NOT_OWN_MUTEX;
	else if(EINVAL == err_code)
		return AME_COND_ERROR;
	else
		return AME_COND_MUTEX_DIFF;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondSignal (AMThreadCond * cond)
{
    AMInt32 err_code;
    if(cond == NULL)
        return AME_ARG_AINVALID;

    err_code = pthread_cond_signal(*cond);
    if(0 == err_code)
        return AME_COND_SCUESS;
    else 
        return AME_COND_ERROR;
}

#endif /* ATHREAD_COND_CPP_ */
