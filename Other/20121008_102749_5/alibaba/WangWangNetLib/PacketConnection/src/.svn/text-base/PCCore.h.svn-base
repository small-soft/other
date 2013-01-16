#ifndef __PC_CORE_H__
#define __PC_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "PCContext.h"

	//queue
	typedef struct QueueItemTag  
	{
		Event*					pEvent;
		struct QueueItemTag*	pNext;
	}QueueItem;

	typedef struct  
	{
		Mutex		mutexCritical;
		Semaphore	semaphore;
		QueueItem*	pFirst;
		QueueItem*	pLast;
		QueueItem*	pFirstLow;
		QueueItem*	pLastLow;
	}Queue;

	typedef struct  
	{
		ThreadHandle	pHandle;
		Runner			pre;
		Runner			runner;
		Runner			post;
		Semaphore		semaphore;
	}Looper;

	
	typedef enum {
		eIMnetCoreStop = 0,
		eIMnetCoreStart
	}IMnetCoreStatus;

	typedef struct{
		// Reader/Sender/Callback Queue
		Queue*					pReaderQueue;
		Queue*					pSenderQueue;
		Queue*					pCallbackQueue;

		// Reader/Sender/Callback Looper
		Looper*					pReaderLooper;
		Looper*					pSenderLooper;
		Looper*					pCallbackLooper;

		AMInt32					needHealthCheck;
		AMInt32					socketFd;
		
		IMnetCoreStatus			coreStatus; 

	}PCCore;

	typedef enum {
		ePCClearPCHandle,
		ePCClearNetwork
	}PCClearType;

	typedef	struct ST_ProtocolEngine ST_ProtocolEngine;
	typedef struct ST_PacketConnection ST_PacketConnection;
	PCCore* PCCoreCreate();
	void PCCoreDestory(/*struct*/ ST_ProtocolEngine* pProtocolEngine);

	void PCCoreRun(/*struct*/ ST_PacketConnection* pPacketConnection);
	void PCCoreStop(/*struct*/ ST_ProtocolEngine* pProtocolEngine);
	void PCCoreClear(/*struct */ST_PacketConnection* pPacketConnection, Semaphore* pSemaphore, PCClearType type);

	void PCPostMessage(Event* pEvt, Queue* pQueue);
	void PCCoreSwitchHealthCheck(PCCore* pPCCore, AMInt32 value);

	void PCPostMessageProc(Event* pEvt, Queue* pQueue, AMBool bLow);

#ifdef __cplusplus
}
#endif

#endif
