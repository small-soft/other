/*
 * AMThreadMutex.c
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */
#include "AMThreadMutex.h"
#include <pthread.h>

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexCreate (AMThreadMutex * mutex)
{
    AMInt32 err_code = 0;
    pthread_mutexattr_t pattr;
    if(mutex == NULL)
        return AME_ARG_AINVALID;

    *mutex = (AMPVoid)malloc(sizeof(pthread_mutex_t));
	pthread_mutexattr_init(&pattr);
	pthread_mutexattr_settype(&pattr, PTHREAD_MUTEX_RECURSIVE_NP); 
	err_code =  pthread_mutex_init(*mutex, NULL);
    pthread_mutexattr_destroy(&pattr);
	if(0 == err_code)
		return AME_MUTEX_SCUESS;
	else
		return AME_MUTEX_ERROR;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexDestroy (AMThreadMutex * mutex)
{
    if(mutex == NULL)
        return AME_ARG_AINVALID;

	pthread_mutex_destroy(*mutex);
	free(*mutex);
	return AME_MUTEX_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexLock (AMThreadMutex * mutex)
{
    if(mutex == NULL)
        return AME_ARG_AINVALID;
	pthread_mutex_lock(*mutex);
	return AME_MUTEX_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexUnlock (AMThreadMutex * mutex)
{
    if(mutex == NULL)
        return AME_ARG_AINVALID;
	pthread_mutex_unlock(*mutex);
	return AME_MUTEX_SCUESS;
}

#ifdef AMTHREAD_MUTEX_SUPPORT_TRY_LOCK
AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexTryLock (AMThreadMutex * mutex)
{
    AMInt32 err_code;
    if(mutex == NULL)
        return AME_ARG_AINVALID;
    err_code = pthread_mutex_lock(*mutex);

    if(err_code == EBUSY)
       return AME_MUTEX_BUSY;
    else
       return AME_MUTEX_SCUESS;
}
#endif
