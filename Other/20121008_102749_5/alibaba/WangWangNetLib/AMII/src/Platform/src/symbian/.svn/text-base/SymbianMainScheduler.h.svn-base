#ifndef __SYMBIAN_MAIN_SCHEDULER_H__
#define __SYMBIAN_MAIN_SCHEDULER_H__

#include <e32base.h>	// For CActive, link against: euser.lib

class SymbianMainScheduler : public CActive
{
public:
	// cancel and destroy
	~SymbianMainScheduler();
	
	//tow-phased constructor.
	static SymbianMainScheduler* NewL(CActiveScheduler* aMainActiveScheduler, TThreadId aMainThreadId);
	static SymbianMainScheduler* GetInstance() { return iSymbianMainScheduler; }
	
	void Add(CActive* aActive);
	void Close();
	
	CActiveScheduler* GetActiveScheduler() { return iMainActiveScheduler;}
	
	TThreadId GetMainThreadId() { return iMainThreadId; }
		
private:
	// C++ constructor
	SymbianMainScheduler();
	
	// Second-phase constructor
	void ConstructL(CActiveScheduler* aMainActiveScheduler, TThreadId aMainThreadId);
	
private:
	// From CActive
	// Handle completion
	void RunL();

	// How to cancel me
	void DoCancel();

	// Override to handle leaves from RunL(). Default implementation causes
	// the active scheduler to panic.
	TInt RunError(TInt aError);
	
private:	
	static SymbianMainScheduler*	  iSymbianMainScheduler;
    TThreadId 		  		  iMainThreadId;
	CActiveScheduler* 		  iMainActiveScheduler;
	TRequestStatus*			  ipStatus;
	
	RSemaphore 				  iAddBeginSemaphore; 
	RSemaphore				  iAddEndSemaphore;
	
	RSemaphore				  iCloseEndSemaphore;
	
	CActive* 				  iActive;
	TInt		  			  iState;
};

#endif
