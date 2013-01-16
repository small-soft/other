#ifndef __PACKET_CONNECTION_H__
#define __PACKET_CONNECTION_H__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef AMOS
#include "AMThread.h"
#include "AMThreadMutex.h"
#include "AMMemory.h"
#include "AMAssert.h"

	typedef AMThread		ThreadHandle;
	typedef AMThreadMutex	Mutex;

	typedef struct {
		AMInt32		nInit;
		AMInt32		nMax;
	}Semaphore;
#else
	#ifdef WIN32
	#include "malloc.h"
	#include "assert.h"

	#define AMMalloc				malloc
	#define AMFree					free
	#define AMAssert(express)		assert(express)
	#define AMPrintf				printf

		typedef char                AMChar;
		typedef unsigned char       AMUChar;
		typedef char                AMInt8;
		typedef unsigned char       AMUInt8;
		typedef short               AMInt16;
		typedef unsigned short      AMUInt16;
		typedef int                 AMInt32;
		typedef unsigned int        AMUInt32;
		typedef void*				AMPVoid;

		typedef void*				ThreadHandle;
		typedef void*				Mutex;
		typedef void*				Semaphore;
	#endif
#endif

#undef NULL
#define NULL	0


#define EVENT_CUSTOMIZE_01_MIN		(0x00000100)
#define EVENT_CUSTOMIZE_MAX			(0x00001000)

/************************************************************************/
// 数据类型定义
/************************************************************************/
typedef void* PCHandle;
typedef AMInt32 PCServiceID;
typedef void* PCReference;
typedef void* EventContent;
typedef AMInt32 PCRetCode;
typedef AMInt32 EventId;

#define		eOK							0x0001
#define		eNotReady					0x0002
#define		eMallocError				0x0003
#define		eInvalidParam				0x0004
#define		eJumpWhile					0x0005
#define		eContinue					0x0006
#define		eTypeError					0x0007
#define		eAlreadyExist				0x0008
#define		eInternalError				0x0009
#define		eInvalidPacker				0x000A
#define		eInvalidPackerFree			0x000B
#define		eInalidUnpacker				0x000C
#define		eNetworkError				0x000D
#define		eUnsupportFeature			0x000E

	enum {
	#define MACRO_STRING_DEF(str) #str
	#undef MACRO_DEF
	#define MACRO_DEF(id, value, structDef)				id = value,
	#undef MACRO_DEFS
	#define MACRO_DEFS(id, value, structDef)			id = value,
	#undef MACRO_DEFR
	#define MACRO_DEFR(id, value, structDef)			id = value,
	#undef MACRO_DEF_EXTERN
	#define MACRO_DEF_EXTERN(id, value, structDef)		id = value,
	#include "PCEventDef.h"
	};

	typedef struct {
		AMInt32		sd;	//send函数返回值
		EventId		id; //发送失败的消息ID
	}PcSendExceptionInd,
		PcEventSendException;

	typedef struct {
		AMInt32		desireLength;
		AMInt32		realLength;
	}PcRecvExceptionInd,
		PcEventRecvException;

	typedef struct {
		AMInt32		length;
	}PcExceedExceptionInd,
		PcEventExceedException;

	typedef struct {
		PCRetCode	retCode;
	}PcPackExceptionInd,
		PcEventPackException,
		PcUnpackExceptionInd,
		PcEventUnpackException;

	typedef struct {
		AMInt32	result; //connect code. //result<0:错误; result>0:正确 result=0:超时
	}PcCnfNetworkConfig,
		PcEventNetworkConfig;


	//Event结构内部内存释放接口定义
	typedef void (*FreeContent)(EventContent* pContent);

	typedef struct ST_Event {
		EventId				id;
		EventContent*		pContent;
		FreeContent			pfnFreeContent;
		PCHandle			hPCHandle;	
	}Event;

	typedef	struct {
		AMChar *	szKey;
		AMInt32		iKeyLen;
		AMChar *	szValue;
		AMInt32		iValueLen;
	} StrStrPair;

	typedef PCRetCode (*PCReceiver)(PCHandle hHandle, Event* pEvent, PCReference ref);
	typedef PCRetCode (*PCPacker)(PCHandle hHandle, Event* pEvt, AMUInt8** ppBuffer, AMInt32* pLength, PCReference ref);
	typedef void (*PCPackerFree)(AMInt8* pBuffer, PCReference ref);
	typedef PCRetCode (*PCUnpacker)(PCHandle hHandle, Event** ppEvt, EventId cmd, AMUInt8* pBuffer, AMInt32 Length, PCReference ref);
	typedef PCRetCode (*PCMakeHealthCheckEvent)(PCHandle hHandle, Event** ppEvt, PCReference ref);
	/************************************************************************/
	// extern function declare.
	/************************************************************************/
	PCRetCode PacketConnectionCreate(PCHandle* phHandle, PCServiceID nSID, PCReference pReference);
	PCRetCode PacketConnectionDestory(PCHandle hHandle);
	
	PCRetCode PacketConnectionSetPacker(PCHandle hHandle, PCPacker pPacker, PCPackerFree pPackerFree);
	PCRetCode PacketConnectionSetUnpacker(PCHandle hHandle, PCUnpacker pUnpacker);
	
	PCRetCode PacketConnectionOpen(PCHandle hHandle, AMChar* ip, AMUInt16 port, AMInt32 sync);
	PCRetCode PacketConnectionClose(PCHandle hHandle);

#if IM_NET_SHUT_SOCKET
	PCRetCode PacketConnectionShut(PCHandle hHandler);
#endif

	PCRetCode PacketConnectionStartKeepAlive(PCHandle hHandle, AMInt32 second, PCMakeHealthCheckEvent pMakeHealthCheck);
	PCRetCode PacketCOnnectionStopKeepAlive(PCHandle hHandle);

	PCRetCode PacketConnectionSend(Event* pEvt);
	PCRetCode PacketConnectionSetReceiver(PCHandle hHandle, PCReceiver pReceiver);

	PCReference PacketConnectionGetRef(PCHandle hHandle);
	AMInt32 PacketConnectionIsKeepAlive(PCHandle hHandle); 
	PCRetCode PacketConnectionSendtoCallback(Event* pEvt);
	PCRetCode PacketConnectionSendtoCallbackProc(Event* pEvt, AMBool bLow);


#ifdef AMOS
#include "AMSocket.h"	
#endif

#ifdef AMOS
	typedef AMPVoid (*Runner)(AMPVoid lpParam);
#else
#ifdef WIN32
	typedef AMUInt32 (*Runner)(void* lpParam);
#endif
#endif

	typedef AMInt32 (*pIMnetSocketCreate)(AMChar* ip, AMUInt16 port
#ifdef AMOS
#ifdef SOCKET_ASYNC
		, AMInt32 reference, AMInt32 iap, void* connCB, void* senderCB, void* readerCB
#endif
#endif
		);

	typedef void (*pIMnetSocketClose)(AMUInt32* pSocket);
	typedef AMInt32 (*pIMnetSend)(AMUInt32 socketFd, AMUInt8* buffer, AMInt32 length);
	typedef AMInt32 (*pIMnetRecv)(AMUInt32 socketFd, AMUInt8* buffer, AMInt32 length);

	// 单位为毫秒
	typedef void (*pIMnetSleep)(AMUInt32 time);

	typedef AMInt32 (*pThreadCreate)(ThreadHandle* pThread, Runner runner, void* pModule, Runner pre, Runner post, AMInt32 now);
	typedef AMInt32 (*pThreadExit)(ThreadHandle* pHandle);

	typedef void (*pMutexLock)(Mutex* pMutex);
	typedef void (*pMutexUnlock)(Mutex* pMutex);
	typedef void (*pMutexCreate)(Mutex* pMutex);
	typedef void (*pMutexDestory)(Mutex* pMutex);

	typedef void (*pSemaphoreWait)(Semaphore* pSemaphore);
	typedef void (*pSemaphoreSignal)(Semaphore* pSemaphore);
	typedef void (*pSemaphoreCreate)(Semaphore* pSemaphore, AMInt32 initCount, AMInt32 maxCount);
	typedef void (*pSemaphoreDestory)(Semaphore* pSemaphore);

	typedef struct{
		pIMnetSocketCreate		socketCreate;
		pIMnetSocketClose		socketClose;
		pIMnetSend				send;
		pIMnetRecv				recv;
		pIMnetSleep				sleep;
		pThreadCreate			threadCreate;
		pThreadExit				threadExit;

		pMutexLock				mutexLock;
		pMutexUnlock			mutexUnlock;
		pMutexCreate			mutexCreate;
		pMutexDestory			mutexDestory;

		pSemaphoreWait			semaphoreWait;
		pSemaphoreSignal		semaphoreSignal;
		pSemaphoreCreate		semaphoreCreate;
		pSemaphoreDestory		semaphoreDestory;
	}PCContext;

	PCContext* PCContextGetInstance();
#ifdef __cplusplus
}
#endif

#endif