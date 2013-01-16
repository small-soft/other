/*
 * AMThreadMutex.c
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */
#include "AMThreadMutex.h"
#include <estlib.h>
#include "AMMemory.h"

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexCreate (AMThreadMutex * mutex)
{
	if(NULL == mutex)
		return AME_ARG_AINVALID;
	
    //RMutex* pMutex = new RMutex();
	AMNewD(RMutex, pMutex, RMutex());
	
    if(NULL == pMutex)
    	return AME_MALLOC_ERROR;
    
    if(pMutex->CreateLocal() != KErrNone)
    {
    	//delete pMutex;
    	AMDelete(pMutex);
    	return AME_MUTEX_ERROR;
    }
    
    *mutex = pMutex;
    return AME_MUTEX_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexDestroy (AMThreadMutex * mutex)
{
	if(NULL != mutex && *mutex != NULL)
	{
		((RMutex*)*mutex)->Close();
		//delete *mutex;
		AMDelete(*mutex);
		
		*mutex = NULL;
		return AME_MUTEX_SCUESS;
	}
	
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexLock (AMThreadMutex * mutex)
{
	if(NULL != mutex && *mutex != NULL)
	{
		((RMutex*)*mutex)->Wait();
		return AME_MUTEX_SCUESS;
	}
	
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexUnlock (AMThreadMutex * mutex)
{
	if(NULL != mutex && *mutex != NULL)
	{
		((RMutex*)*mutex)->Signal();
		return AME_MUTEX_SCUESS;
	}
	
	return AME_ARG_AINVALID;
}

#ifdef AMTHREAD_MUTEX_SUPPORT_TRY_LOCK
AMTHREAD_DLL_EXPORT AMInt32 AMThreadMutexTryLock (AMThreadMutex * mutex)
{
	if(NULL != mutex && *mutex != NULL)
	{
		return AME_UNIMPL_METHOD;
	}
	
	return AME_ARG_AINVALID;
}
#endif
