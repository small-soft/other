/*
 ============================================================================
 Name		: Timer.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimer declaration
 ============================================================================
 */

#ifndef TIMER_H
#define TIMER_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib

#include "AMTimer.h"

class CTimerInternal : public CActive
	{
public:
	// Cancel and destroy
	~CTimerInternal();

	// C++ constructor
	CTimerInternal(AMTimerCallback Callback,
	        AMPVoid Parg, struct AMTimeval* Delay, struct AMTimeval* Interval);
	
public:
	// New functions
	// Function for making the initial request
	void StartL(TTimeIntervalMicroSeconds32 aDelay, TTimeIntervalMicroSeconds32 aIntervel);
	
private:
	
	void DoCancel();
	
	void RunL();

private:
	RTimer Timer;
	//CPeriodic* iTimer; // Provides async timing service
	struct AMTimeval delay;
	struct AMTimeval interval;
	AMTimerCallback callback;
	AMPVoid parg;
	};

#endif // TIMER_H
