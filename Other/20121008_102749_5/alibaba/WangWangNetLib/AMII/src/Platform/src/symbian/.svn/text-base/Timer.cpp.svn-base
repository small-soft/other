/*
 ============================================================================
 Name		: Timer.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimer implementation
 ============================================================================
 */

#include "Timer.h"
#include "SymbianMainScheduler.h"

CTimerInternal::CTimerInternal(AMTimerCallback Callback,
        AMPVoid Parg, struct AMTimeval* Delay, struct AMTimeval* Interval) : CActive( EPriorityStandard )
	{
	//iTimer = CPeriodic::NewL( CActive::EPriorityStandard );
	Timer.CreateLocal();
	SymbianMainScheduler::GetInstance()->Add(this);
	callback = Callback;
	parg = Parg;
	
	delay = *Delay;
	interval = *Interval;
	
	StartL( Delay->tv_sec * 1000000 + Delay->tv_usec, Interval->tv_sec * 1000000 + Interval->tv_usec );
	}

CTimerInternal::~CTimerInternal()
	{
	//delete iTimer;
	Cancel();
	Timer.Close();
	// Delete instance variables if any
	}

void CTimerInternal::StartL(TTimeIntervalMicroSeconds32 aDelay, TTimeIntervalMicroSeconds32 aIntervel)
	{
	Cancel(); // Cancel any request, just to be sure
	//TCallBack callback( PeriodicCallBack, this );
	Timer.After( iStatus, aDelay );
	SetActive();
	//iTimer->Start( aDelay, aIntervel, callback );
	}

void CTimerInternal::DoCancel()
	{
	Timer.Cancel();
	}

void CTimerInternal::RunL()
	{
	callback( parg );
	
	Timer.After( iStatus, interval.tv_sec * 1000000 + interval.tv_usec );
	SetActive();
	}
