/*
 * athread_cond.cpp
 *
 *  Created on: 2009-11-16
 *      Author: qinghua.liqh
 */
#ifndef ATHREAD_COND_CPP_
#define ATHREAD_COND_CPP_
#include "AMThreadCond.h"
#include <estlib.h>
#include "AMMemory.h"

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondCreate (AMThreadCond * cond)
{
	if(NULL == cond)
		return AME_ARG_AINVALID;
	
    //RCondVar * pCondVar  = new RCondVar();
	AMNewD(RCondVar, pCondVar, RCondVar());
    if(NULL == pCondVar)
    	return AME_MALLOC_ERROR;
    
    if(pCondVar->CreateLocal() != KErrNone)
    {
    	//delete pCondVar;
    	AMDelete(pCondVar);
    	return AME_COND_ERROR;
    }
    
    *cond = pCondVar;
    return AME_COND_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondDestroy (AMThreadCond * cond)
{
	if(NULL != cond && *cond != NULL)
	{
		((RCondVar*)*cond)->Close();
		//delete *cond;
		AMDelete(*cond);
		*cond = NULL;
		return AME_COND_SCUESS;
	}
	
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondWait (AMThreadCond * cond, AMThreadMutex * mutex)
{
	if(NULL != cond && *cond != NULL && NULL != mutex && *mutex != NULL)
	{
		TInt ret_code = 0;
		TRAPD(err_code, ret_code = ((RCondVar*)*cond)->Wait(*((RMutex*)*mutex)));
		if(err_code != KErrNone)
		{
			return AME_COND_ERROR;
		}
		switch(ret_code)
		{
		case KErrNone :
			return AME_COND_SCUESS;
		case KErrInUse:
			return AME_COND_MUTEX_DIFF;
		case KErrGeneral:
			return AME_COND_ERROR;
		}
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondTimewait (AMThreadCond * cond,
			    AMThreadMutex * mutex,
			    const struct AMTimeval* abstime)
{
	
	if(NULL != cond && *cond != NULL && NULL != mutex && *mutex != NULL && abstime != NULL)
	{
		TInt iTimeout = abstime->tv_sec * 1000 + abstime->tv_usec /1000;
		if(iTimeout < 0)
			return AME_ARG_AINVALID;
		
		TInt ret_code = 0;
		TRAPD(err_code, ret_code = ((RCondVar*)*cond)->TimedWait(*((RMutex*)*mutex), iTimeout));
		if(err_code != KErrNone)
		{
			return AME_COND_ERROR;
		}
		switch(ret_code)
		{
		case KErrNone :
			return AME_COND_SCUESS;
		case KErrTimedOut:
			return AME_COND_TIMEOUT;
		case KErrInUse:
			return AME_COND_MUTEX_DIFF;
		case KErrGeneral:
			return AME_COND_ERROR;
		}
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCondSignal (AMThreadCond * cond)
{
	if(NULL != cond && *cond != NULL)
	{
		((RCondVar*)*cond)->Signal();
		return AME_COND_SCUESS;
	}
	
	return AME_ARG_AINVALID;
}

#endif /* ATHREAD_COND_CPP_ */
