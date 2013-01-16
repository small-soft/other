#include "SymbianMainScheduler.h"
#include "AMMemory.h"

SymbianMainScheduler* 	  SymbianMainScheduler::iSymbianMainScheduler = NULL;

SymbianMainScheduler::SymbianMainScheduler() :
	CActive(EPriorityIdle) // Standard priority
{
}

void SymbianMainScheduler::ConstructL(CActiveScheduler* aMainActiveScheduler, TThreadId aMainThreadId)
{
	iMainActiveScheduler = aMainActiveScheduler;
	iMainThreadId 	     = aMainThreadId;
	ipStatus			 = &iStatus;
	
	iAddBeginSemaphore.CreateLocal(1);
	iAddEndSemaphore.CreateLocal(1);
	iAddEndSemaphore.Wait(); //denx:先消耗掉一个位置。
	
	iCloseEndSemaphore.CreateLocal(1);
	iCloseEndSemaphore.Wait(); //denx:先消耗掉一个位置。
	
	iActive = NULL;
	iState = 0;
	CActiveScheduler::Add(this);
}

SymbianMainScheduler::~SymbianMainScheduler()
{
	Cancel(); // Cancel any request, if outstanding
	iAddBeginSemaphore.Close();
	iAddEndSemaphore.Close();
	iCloseEndSemaphore.Close();
}

SymbianMainScheduler* SymbianMainScheduler::NewL(CActiveScheduler* aMainActiveScheduler, TThreadId aMainThreadId)
{
	if(aMainActiveScheduler == NULL)
		return 0;
	
	if(iSymbianMainScheduler == NULL)
	{
		//iSymbianMainScheduler = new (ELeave) SymbianMainScheduler();
		AMNewLE(SymbianMainScheduler, iSymbianMainScheduler, ELeave, SymbianMainScheduler());
		
		CleanupStack::PushL(iSymbianMainScheduler);
		iSymbianMainScheduler->ConstructL(aMainActiveScheduler, aMainThreadId);
		CleanupStack::Pop();
		return iSymbianMainScheduler;
	}
	else
	{
		return iSymbianMainScheduler;
	}
}

void SymbianMainScheduler::Add(CActive* aActive)
{
	iAddBeginSemaphore.Wait();
	RThread th;
	TThreadId currentTH = th.Id();
	TThreadId mainTH = iMainThreadId;
	
	if(currentTH == mainTH)
	{
		iMainActiveScheduler->Add(aActive);
	}
	else
	{
		th.Open(mainTH);
		
		Cancel();
		*ipStatus = KRequestPending;
		TRequestStatus* status = ipStatus;
				
		if(aActive != NULL)
		{
			iActive = aActive;
			th.RequestComplete(status, KErrNone);
			SetActive();
			iAddEndSemaphore.Wait();
		}
	}
	
	iAddBeginSemaphore.Signal();
}

void SymbianMainScheduler::Close()
{
	RThread th;
	TThreadId currentTH = th.Id();
	TThreadId mainTH = iMainThreadId;
	
	if(currentTH == mainTH)
	{
		CActiveScheduler::Stop();
	}
	else
	{
		th.Open(mainTH);
		
		Cancel();
		*ipStatus = KRequestPending;
		TRequestStatus* status = ipStatus;

		iState = 1;
		th.RequestComplete(status, KErrNone);
		SetActive();
		iCloseEndSemaphore.Wait();
	}
}

void SymbianMainScheduler::RunL()
{
	TInt temp = iStatus.Int();
	
	if(temp == KErrNone)
	{
		if(iActive != NULL)
		{
			iMainActiveScheduler->Add(iActive);
		}
		
		if(iState == 1)
		{
			iState = 0;
			CActiveScheduler::Stop();
			iCloseEndSemaphore.Signal();
		}
	}
	
	if(iActive != NULL)
	{
		iActive = NULL;
		iAddEndSemaphore.Signal();
	}
}

TInt SymbianMainScheduler::RunError(TInt aError)
{
	return aError;
}

void SymbianMainScheduler::DoCancel()
{
}
