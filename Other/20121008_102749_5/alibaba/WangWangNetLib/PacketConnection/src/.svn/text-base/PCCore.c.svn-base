#include "PCCore.h"
#include "PCMgr.h"
#include "PCEvent.h"
#include "PCUtility.h"

#include "stdio.h"
#include "string.h"

#ifdef AMOS
#ifdef SOCKET_ASYNC
#include "AMSocket.h"
#endif
#endif

#define MAX_QUEUE_ITEMS			1000  //队列中最多等待的消息数目
#define HEALTH_CHECK_SLEEP_TIME 100   //每次睡眠HEALTH_CHECK_SLEEP_TIME毫秒
#define HEALTH_CHECK_INTERVAL   600 //睡眠HEALTH_CHECK_INTERVAL次后,发送心跳包

/************************************************************************/
// structure definition
/************************************************************************/

/************************************************************************/
// global definition
/************************************************************************/

/************************************************************************/
//local function declare
/************************************************************************/
#ifdef AMOS
	static AMPVoid ReaderRunner(AMPVoid lpParam);
	static AMPVoid SenderRunner(AMPVoid lpParam);
	static AMPVoid CallbackRunner(AMPVoid lpParam);
#else
	#ifdef WIN32
	static AMUInt32 ReaderRunner(void* lpParam);
	static AMUInt32 SenderRunner(void* lpParam);
	static AMUInt32 CallbackRunner(void* lpParam);
	#endif
#endif

#ifdef AMOS
#ifdef SOCKET_ASYNC
static void SocketConnectionCallback(AMInt32 reference, AMInt32 socket, SocketStatus status);
static void SocketSenderCallback(AMInt32 reference, AMInt32 socket, SocketStatus status);
static void SocketReaderCallback(AMInt32 reference, AMInt32 socket, SocketStatus status);
#endif
#endif

static PCRetCode SendNetworkConnectedMsg(PacketConnection* pPC, AMInt32 result);
static AMInt32 IsPCNetworkReady(PCCore* pPCCore);
static AMInt32 IsPCNeedHealthCheck(PCCore* pPCCore);
/************************************************************************/
//function implementation
/************************************************************************/

/*
 *	AddQueue and AddQueueProc are not protected by mutex, or synchronized by semaphore.
 */
void AddQueueProc(Queue* pQueue, Event* evt, AMBool bLow)
{
	QueueItem *pItem = NULL;

	if(pQueue && evt)
	{
		//PCContextGetInstance()->mutexLock(&pQueue->mutexCritical);

		pItem = (QueueItem*)AMMalloc(sizeof(QueueItem));
		if(pItem)
		{
			pItem->pEvent = evt;
			pItem->pNext  = NULL;
		}
		else
		{
			AMAssert(0);
		}

		if(!bLow)
		{
			if(pQueue->pLast != NULL)
				pQueue->pLast->pNext = pItem; 
			pQueue->pLast = pItem;

			if(pQueue->pFirst == NULL)
				pQueue->pFirst = pItem;
		}
		else
		{
			if(pQueue->pLastLow != NULL)
				pQueue->pLastLow->pNext = pItem; 
			pQueue->pLastLow = pItem;

			if(pQueue->pFirstLow == NULL)
				pQueue->pFirstLow = pItem;
		}		
	}
}

void AddQueue(Queue* pQueue, Event* evt)
{
	AddQueueProc(pQueue, evt, AMFALSE);
}

void PullQueue(Queue* pQueue, Event** ppEvt, AMInt32 sync)
{
	QueueItem *pFirstItem = NULL;

	if(pQueue && ppEvt)
	{
		*ppEvt = NULL;

		if(sync)
			PCContextGetInstance()->semaphoreWait(&pQueue->semaphore);		

		PCContextGetInstance()->mutexLock(&pQueue->mutexCritical);
		
		pFirstItem = pQueue->pFirst;
		if(pFirstItem != NULL)
		{		
			*ppEvt = pFirstItem->pEvent;
			pQueue->pFirst = pFirstItem->pNext;
			if(pQueue->pFirst == NULL)
				pQueue->pLast = NULL;
			AMFree(pFirstItem);
		}
		else
		{
			pFirstItem = pQueue->pFirstLow;
			if(pFirstItem != NULL)
			{		
				*ppEvt = pFirstItem->pEvent;
				pQueue->pFirstLow = pFirstItem->pNext;
				if(pQueue->pFirstLow == NULL)
					pQueue->pLastLow = NULL;
				AMFree(pFirstItem);
			}
		}

		PCContextGetInstance()->mutexUnlock(&pQueue->mutexCritical);
	}
}

void QueueCreate(Queue** ppObject)
{
	if(ppObject == NULL)
		return;

	*ppObject = (Queue*)AMMalloc(sizeof(Queue));
	if(*ppObject)
	{
		PCContextGetInstance()->mutexCreate(&(*ppObject)->mutexCritical);
		PCContextGetInstance()->semaphoreCreate(&(*ppObject)->semaphore, 0, MAX_QUEUE_ITEMS);

		(*ppObject)->pFirst = (*ppObject)->pLast = NULL;
		(*ppObject)->pFirstLow = (*ppObject)->pLastLow = NULL;
	}
}

void QueueDestory(Queue** ppObject)
{
	QueueItem* pTemp = NULL;
	if(ppObject == NULL)
		return;

	while((*ppObject)->pFirst)
	{
		pTemp = (*ppObject)->pFirst;
		(*ppObject)->pFirst = (*ppObject)->pFirst->pNext;

        //此处先释放item内部的内存
        EventDestory(&pTemp->pEvent);

        //再释放item本身的内存
		AMFree(pTemp);
	}

	while((*ppObject)->pFirstLow)
	{
		pTemp = (*ppObject)->pFirstLow;
		(*ppObject)->pFirstLow = (*ppObject)->pFirstLow->pNext;

		//此处先释放item内部的内存
		EventDestory(&pTemp->pEvent);

		//再释放item本身的内存
		AMFree(pTemp);
	}

	PCContextGetInstance()->mutexDestory(&(*ppObject)->mutexCritical);
	PCContextGetInstance()->semaphoreDestory(&(*ppObject)->semaphore);

	AMFree(*ppObject);
	*ppObject = NULL;
}

void LooperCreate(PacketConnection* pPacketConnection, Looper** ppObject, Runner runner, Runner pre, Runner post, AMInt32 now)
{
	if(pPacketConnection == NULL || ppObject == NULL)
		return;

	AMAssert(NULL != pPacketConnection->pProtocolEngine && pPacketConnection->pProtocolEngine->pPCContext);

	*ppObject = (Looper*)AMMalloc(sizeof(Looper));
	if(*ppObject)
	{
		memset(*ppObject, 0, sizeof(Looper));
		(*ppObject)->pre 	= pre;
		(*ppObject)->runner = runner;
		(*ppObject)->post 	= post;
		pPacketConnection->pProtocolEngine->pPCContext->threadCreate(&((*ppObject)->pHandle), runner, pPacketConnection, pre, post, now);
		pPacketConnection->pProtocolEngine->pPCContext->semaphoreCreate(&(*ppObject)->semaphore, 0, 1);
	}
}

void LooperDestory(Looper** ppLooper)
{
	if(ppLooper != NULL && *ppLooper != NULL)
	{
		(*ppLooper)->runner = NULL;
		PCContextGetInstance()->threadExit(&((*ppLooper)->pHandle));
		PCContextGetInstance()->semaphoreDestory(&(*ppLooper)->semaphore);
		
		AMFree(*ppLooper);
		*ppLooper = NULL;
	}
}

void PCPostMessageProc(Event* pEvt, Queue* pQueue, AMBool bLow)
{
	if(pEvt != NULL)
	{
		PCContextGetInstance()->mutexLock(&pQueue->mutexCritical);
		AddQueueProc(pQueue, pEvt, bLow);
		PCContextGetInstance()->mutexUnlock(&pQueue->mutexCritical);
		PCContextGetInstance()->semaphoreSignal(&pQueue->semaphore);
	}
}

void PCPostMessage(Event* pEvt, Queue* pQueue)
{
	PCPostMessageProc(pEvt, pQueue, AMFALSE);
}

/************************************************************************/
// ReaderEventHandler
/************************************************************************/
PCRetCode ReaderEventHandler(ProtocolEngine* pProtocolEngine, AMInt32 sync
#ifdef SOCKET_ASYNC
		, AMInt32* pIndType
#endif
)
{
	PCRetCode retCode = eOK;
	Event* pEvent = NULL;
	PcClearVarInd* pClearVarInd = NULL;
	PacketConnection* pPacketConnection = NULL;

	AMAssert(NULL != pProtocolEngine && NULL != pProtocolEngine->pPCCore);

	//get Request EVENT from reader queue.
	PullQueue(pProtocolEngine->pPCCore->pReaderQueue, &pEvent, sync);
	if(pEvent != NULL)
	{
		switch(pEvent->id)
		{
		case PC_SHUTDOWN_IND:
		#ifdef AMOS_DEBUG
			AMPrintf("noble:exit reader thread....\n");
		#endif
			retCode = eJumpWhile;
			break;
			
		#ifdef SOCKET_ASYNC
		case PC_SOCKET_IND:
			*pIndType = ((ImSocketInd*)pEvent->pContent)->indType;
			break;
		#endif
			
		case PC_CLEAR_VAR_IND:
		#ifdef AMOS_DEBUG
			AMPrintf("noble:ReaderEventHandler PC_CLEAR_VAR_IND.\n");
		#endif
			pPacketConnection = (PacketConnection*)pEvent->hPCHandle;
			//network need to close
			if(pPacketConnection && pPacketConnection->pNetwork && pPacketConnection->pNetwork->fd>0) 
				PCContextGetInstance()->socketClose(&pPacketConnection->pNetwork->fd);

			pClearVarInd = (PcClearVarInd*)pEvent->pContent;
			PCContextGetInstance()->semaphoreSignal(pClearVarInd->pSemaphore);
			break;

		default:
		#ifdef AMOS_DEBUG
			AMPrintf("noble:ReaderEventHandler default.\n");
		#endif
			break;
		}

		//destory EVENT
		EventDestory(&pEvent);
	#ifdef AMOS_DEBUG
		AMPrintf("noble:ReaderEventHandler after EventDestory.\n");
	#endif
	}
	
	return retCode;
}

/************************************************************************/
// ReaderRecvExceptionHandler
/************************************************************************/
PCRetCode ReaderRecvExceptionHandler(PacketConnection* pPacketConnection, AMInt32 desireLen, AMInt32 realLen)
{
	PCRetCode retCode = eOK;
	Event* pExceptionEvent = NULL;
	PcRecvExceptionInd exceptionInd;

#ifdef SOCKET_ASYNC
	AMInt32 indType = 0;
#endif

	AMAssert(NULL != pPacketConnection && NULL != pPacketConnection->pProtocolEngine );
	AMAssert(NULL != pPacketConnection->pProtocolEngine->pPCCore);
	//shutdown health check
	PCCoreSwitchHealthCheck(pPacketConnection->pProtocolEngine->pPCCore, 0);

	//close network
	PCContextGetInstance()->socketClose((AMUInt32*)&pPacketConnection->pProtocolEngine->pPCCore->socketFd);

	if(pPacketConnection->pProtocolEngine->pPCCore->coreStatus == eIMnetCoreStart)
	{
		//send a exception to up-layer.
		pExceptionEvent = NULL;
		exceptionInd.desireLength	= desireLen;
		exceptionInd.realLength		= realLen;

#ifdef AMOS_DEBUG
		AMPrintf("noble: reader send PC_RECV_EXCEPTION_IND\n");
#endif
		retCode = EventCreate(pPacketConnection, &pExceptionEvent, PC_RECV_EXCEPTION_IND, (void*)&exceptionInd, sizeof(exceptionInd));
		if(retCode == eOK)
			PCPostMessage(pExceptionEvent, pPacketConnection->pProtocolEngine->pPCCore->pCallbackQueue);
		else
		{
		#ifdef AMOS_DEBUG
			AMAssert(0);
		#endif
			return eJumpWhile;
		}
	}
	else
	{
#ifdef AMOS_DEBUG
		AMPrintf("noble: reader do not send PC_RECV_EXCEPTION_IND\n");
#endif
	}

#ifdef AMOS_DEBUG
	AMPrintf("noble: reader wait for ...\n");
#endif
	//等待上层重新建立连接，或者退出程序
	while(IsPCNetworkReady(pPacketConnection->pProtocolEngine->pPCCore) <= 0)
	{
		if( ReaderEventHandler(pPacketConnection->pProtocolEngine, 0
		#ifdef SOCKET_ASYNC
				, &indType
		#endif
				) == eJumpWhile
			)
			return eJumpWhile;
		PCContextGetInstance()->sleep(100);
	}
#ifdef AMOS_DEBUG
	AMPrintf("noble: reader out wait for....\n");
#endif
	return eContinue;
}

/************************************************************************/
// ReaderExceedExceptionHandler
/************************************************************************/
void ReaderExceedExceptionHandler(ProtocolEngine* pProtocolEngine, AMInt32 length)
{
	PCRetCode retCode = eOK;
	Event* pExceptionEvent = NULL;
	PcExceedExceptionInd exceptionInd;
	PacketConnection* pTempPC = NULL;
	PacketConnectionMgr* pTempPCMgr = NULL;

	if(pProtocolEngine->pPCCore->coreStatus == eIMnetCoreStart)
	{
		//send a exception to up-layer.
		pExceptionEvent = NULL;
		exceptionInd.length	= length;
		
		//denx: send this exception to all packet connection.
		pTempPCMgr = PCMgrGetInstance();
		pTempPC = pTempPCMgr->pFirstPC;
		while(pTempPC)
		{
			retCode = EventCreate(pTempPC, &pExceptionEvent, PC_EXCEED_EXCEPTION_IND, (void*)&exceptionInd, sizeof(exceptionInd));
			if(retCode == eOK)
				PCPostMessage(pExceptionEvent, pProtocolEngine->pPCCore->pCallbackQueue);
			else
			{
#ifdef AMOS_DEBUG
				AMAssert(0);
#endif
			}

			pTempPC = pTempPC->next;
		}
	}
}

/************************************************************************/
// PacketExceptionHandler
/************************************************************************/
void PacketExceptionHandler(PacketConnection* pPC, PCRetCode code, EventId id)
{
	PCRetCode retCode = eOK;
	Event* pExceptionEvent = NULL;
	PcUnpackExceptionInd exceptionInd;

	//send a exception to up-layer.
	pExceptionEvent 		= NULL;
	exceptionInd.retCode	= code;
	
	retCode = EventCreate(pPC, &pExceptionEvent, id, (void*)&exceptionInd, sizeof(exceptionInd));
	if(retCode == eOK)
		PCPostMessage(pExceptionEvent, pPC->pProtocolEngine->pPCCore->pCallbackQueue);
	else
	{
	#ifdef AMOS_DEBUG
		AMAssert(0);
	#endif
	}
}

PCRetCode ReaderRecvHead(PacketConnection* pPacketConnection, AMUInt8* pHead, AMInt32 headLen)
{
	AMInt32 length = 0;
	
	memset(pHead, 0, headLen);
	//get byte stream from socket recv.
	length = pPacketConnection->pProtocolEngine->pPCContext->recv(
		pPacketConnection->pProtocolEngine->pPCCore->socketFd, pHead, headLen);
	if(length != headLen)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:recv head length error.\n");
	#endif
		if(ReaderRecvExceptionHandler(pPacketConnection,headLen,length) == eContinue)
			return eContinue;
		else
			return eJumpWhile;
	}
	else
	{
#ifdef AMOS_DEBUG
		AMPrintf("noble:recv head ok.\n");
#endif
	}
	
	return eOK;
}

PCRetCode ReaderRecvBody(PacketConnection* pPacketConnection, AMUInt8* pHead, AMUInt8** ppBodyBuffer, AMInt32* pBodyLength)
{
	AMInt32 length = 0;
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:ReaderRecvBody <<<<.\n");
#endif

	*pBodyLength = getIntValue(pHead, 12);
	
	if(*pBodyLength <0 /*|| *pBodyLength > PC_MAX_PROTOCOL_LEN */)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:reader: bodyLength exceed limited(0~20000) = %d\n", *pBodyLength);
	#endif
		//send a body exceed exception to up-layer.
		ReaderExceedExceptionHandler(pPacketConnection->pProtocolEngine, *pBodyLength);
		return eContinue;
	}

	// 分配Body空间并填充
	*ppBodyBuffer = (AMUInt8*)AMMalloc(*pBodyLength);
	if(*ppBodyBuffer == NULL)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:malloc pBodyBuffer error = %d.\n", *pBodyLength);
		AMAssert(0);
	#endif
		return eJumpWhile;
	}
	memset(*ppBodyBuffer, 0, *pBodyLength);
	
    length = PCContextGetInstance()->recv(
		pPacketConnection->pProtocolEngine->pPCCore->socketFd, *ppBodyBuffer, *pBodyLength);

	if( length != *pBodyLength)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:recv = %d != bodyLength = %d\n", length, *pBodyLength);
	#endif
		//first free memory
		AMFree(*ppBodyBuffer);
		*ppBodyBuffer = NULL;

		//send exception to up.
		if(ReaderRecvExceptionHandler(pPacketConnection,*pBodyLength,length) == eContinue)
			return eContinue;
		else
			return eJumpWhile;
	}
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:ReaderRecvBody >>>>>.\n");
#endif
	return eOK;
}

PCRetCode ReaderMergeToPacketBuffer(AMUInt8** ppPacketBuffer, 
										  AMUInt8* pHead,		AMInt32 headLength, 
										  AMUInt8* pBodyBuffer, AMInt32 bodyLength)
{
	// 分配包大小并填充
	*ppPacketBuffer = (AMUInt8*)AMMalloc(headLength+bodyLength);
	if(*ppPacketBuffer == NULL)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:malloc pPacketBuffer error.\n");
		AMAssert(0);
	#endif
		return eJumpWhile;
	}
	
	memset(*ppPacketBuffer, 0, headLength+bodyLength);
	memcpy(*ppPacketBuffer, pHead, headLength);
	memcpy((*ppPacketBuffer)+headLength, pBodyBuffer, bodyLength);
	
	return eOK;
}

PCRetCode ReaderUnpackPacketBuffer(PacketConnection* pPacketConnection, AMUInt8* pPacketBuffer, AMInt32 length)
{
	PCRetCode retCode = eOK;
	AMInt32 cmd = 0;
	Event* pEvent = NULL;

#ifdef AMOS_DEBUG
	AMPrintf("noble:ReaderUnpackPacketBuffer <<<<.\n");
#endif

	cmd      = getIntValue(pPacketBuffer, 16);
	
	//denx:这里如果收到了心跳包的回复，则心跳包计数+1
	if(cmd == 0x01000001 /*IM_HEALTH_CHECK_ACK*/)
		++pPacketConnection->pNetwork->maxHealthCheckMiss;
	
	if(pPacketConnection->pUnpacker)
	{
		retCode = pPacketConnection->pUnpacker(
			(PCHandle)pPacketConnection, &pEvent, (EventId)cmd, 
			pPacketBuffer, length, pPacketConnection->pReference);
	}
	else
		retCode = eInalidUnpacker;

	if(retCode != eOK )
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:unpack procedure error. PCRetCode=%d. cmd=0x%08x\n", retCode, cmd);
	#endif
		//send a unpack exception to up-layer.
		PacketExceptionHandler(pPacketConnection, retCode, PC_UNPACK_EXCEPTION_IND);
	}
	else
	{
		//被踢下线，关闭socket.
		//if(cmd == PC_NTF_FORCEDISCONNECT)
		//	pProtocolEngine->pPCContext->socketClose((AMUInt32*)&pProtocolEngine->pPCCore->socketFd);
	}
	
	//send to Callback Queue.
	if(pEvent)
	{
		PCPostMessage(pEvent, pPacketConnection->pProtocolEngine->pPCCore->pCallbackQueue);
	}
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:ReaderUnpackPacketBuffer >>>>>>.\n");
#endif

	return eOK;
}

/************************************************************************/
// socket收到的消息在此处理
/************************************************************************/
#ifdef AMOS
	AMPVoid ReaderRunner(AMPVoid lpParam)
#else
	#ifdef WIN32
		AMUInt32 ReaderRunner(void* lpParam)
	#endif
#endif
{
	AMUInt8 head[PROTOCOL_HEAD_LENGTH];
	AMUInt8* pPacketBuffer = NULL;
	AMUInt8* pBodyBuffer = NULL;
	AMInt32 bodyLength = 0;
	AMInt32 isExit = 0;
	
#ifdef SOCKET_ASYNC
	AMInt32 indType = -1;
	AMInt32 recvFlag = 0;
#endif
	
	PCRetCode retCode = eOK;
	PacketConnection* pPacketConnection = (PacketConnection*)lpParam;
	
	while(1)
	{
#ifdef SOCKET_ASYNC
		indType = -1;
		
		//get Request EVENT from reader queue.
		retCode = ReaderEventHandler(pIMnet, 1, &indType);
		if(retCode == eJumpWhile)
		{
			isExit = 1;
			goto ReaderEnd;
		}
		else
		{
			switch(indType)
			{				
			case eSocketRecv:
			case eSocketOverflowWarning:
				if(recvFlag == 0)
				{
					//recv head.
					memset(head, 0, sizeof(head));
					
					retCode = ReaderRecvHead(pIMnet, head, PROTOCOL_HEAD_LENGTH);
					if(retCode == eJumpWhile)
					{
						isExit = 1;
						goto ReaderEnd;
					}
					else if(retCode == eContinue)
						recvFlag = 0;
					else
						recvFlag = 1;
				}	
				else if(recvFlag == 1)
				{
					//recv body.
					retCode = ReaderRecvBody(pIMnet, head, &pBodyBuffer, &bodyLength);
					if(retCode == eJumpWhile)
					{
						isExit = 1;
						goto ReaderEnd;
					}
					else if(retCode == eContinue)
						recvFlag = 0;
					else
						recvFlag = 3;
				}
				break;
								
			default:
				continue;
				break;
			}
		}
#else
		while(IsPCNetworkReady(pPacketConnection->pProtocolEngine->pPCCore) <= 0)
		{
			pPacketConnection->pProtocolEngine->pPCContext->sleep(100);
			
			//get Request EVENT from reader queue.
			if(ReaderEventHandler(pPacketConnection->pProtocolEngine, 0) == eJumpWhile)
				goto ReaderEnd;
		}

		//recv head.
		retCode = ReaderRecvHead(pPacketConnection, head, PROTOCOL_HEAD_LENGTH);
		if(retCode == eJumpWhile)
			goto ReaderEnd;
		else if(retCode == eContinue)
			continue;
		
		//get Request EVENT from reader queue.
		if(ReaderEventHandler(pPacketConnection->pProtocolEngine, 0) == eJumpWhile)
			goto ReaderEnd;

		//recv body.
		retCode = ReaderRecvBody(pPacketConnection, head, &pBodyBuffer, &bodyLength);
		if(retCode == eJumpWhile)
			goto ReaderEnd;
		else if(retCode == eContinue)
			continue;
#endif
		
#ifdef SOCKET_ASYNC
		if(recvFlag == 3)
#endif
		{
#ifdef SOCKET_ASYNC
			recvFlag = 0;
#endif
			// merge
			retCode = ReaderMergeToPacketBuffer(&pPacketBuffer, 
					head, PROTOCOL_HEAD_LENGTH, pBodyBuffer, bodyLength);
			AMFree(pBodyBuffer);
			pBodyBuffer = NULL;
			if(retCode == eJumpWhile)
			{
				isExit = 1;
				goto ReaderEnd;
			}
	
			//unpack
			ReaderUnpackPacketBuffer(pPacketConnection, pPacketBuffer, PROTOCOL_HEAD_LENGTH+bodyLength);
			AMFree(pPacketBuffer);
			pPacketBuffer = NULL;
		}
	}

ReaderEnd:
	pPacketConnection->pProtocolEngine->pPCContext->semaphoreSignal(
		&pPacketConnection->pProtocolEngine->pPCCore->pReaderLooper->semaphore);
	
#ifdef AMOS
	return (AMPVoid)isExit;
#else
	#ifdef WIN32
		return isExit;
	#endif
#endif
}

/************************************************************************/
// SenderSendExceptionHandler
/************************************************************************/
void SenderSendExceptionHandler(PacketConnection* pPC, AMInt32 sd, EventId id)
{
	PCRetCode retCode = eOK;
	Event* pExceptionEvent = NULL;
	PcSendExceptionInd exceptionInd;

	//send a exception to up-layer.
	pExceptionEvent = NULL;
	exceptionInd.sd	= sd;
	exceptionInd.id = id;

	retCode = EventCreate(pPC, &pExceptionEvent, PC_SEND_EXCEPTION_IND, (void*)&exceptionInd, sizeof(exceptionInd));
	if(retCode == eOK)
		PCPostMessage(pExceptionEvent, pPC->pProtocolEngine->pPCCore->pCallbackQueue);
	else
	{
#ifdef AMOS_DEBUG
		AMAssert(0);
#endif
	}
}

void SenderPacket(Event* pEvent)
{
	AMChar* pBuffer = NULL;
	AMInt32 length = 0;
	AMInt32 sd = 0;
	PCRetCode retCode = eOK;
	PacketConnection* pPacketConnection;
	
	pPacketConnection = (PacketConnection*)pEvent->hPCHandle;
	pBuffer = NULL;
	length = 0;
	//pack EVENT
#ifdef AMOS_DEBUG
	AMPrintf("noble:SenderPacket. <<<<< \n");
#endif

	if(pPacketConnection->pPacker)
		retCode = pPacketConnection->pPacker(pPacketConnection, pEvent, (AMUInt8**)&pBuffer, &length, pPacketConnection->pReference);
	else
		retCode = eInvalidPacker;
	
	//send to socket
	if(retCode == eOK)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:SenderPacket. before network check. \n");
	#endif
		if(IsPCNetworkReady(pPacketConnection->pProtocolEngine->pPCCore) > 0)
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:SenderPacket. before send. \n");
		#endif
			sd = pPacketConnection->pProtocolEngine->pPCContext->send(
				pPacketConnection->pProtocolEngine->pPCCore->socketFd, (AMUInt8*)pBuffer, length);
			if(sd <= 0)
			{
			#ifdef AMOS_DEBUG
				AMPrintf("noble:send error. sd=%d, cmd=0x%x\n", sd, pEvent->id);
			#endif
				// send exception to uplayer.
				SenderSendExceptionHandler(pPacketConnection, sd, pEvent->id);
			}
			else
			{
				if(pEvent->id == 0x01000001 /*IM_HEALTH_CHECK*/&& (--pPacketConnection->pNetwork->maxHealthCheckMiss) <= 0 )
				{
					//denx:发出的心跳包未得到回馈的次数已经超过了设置的maxHealthCheckMiss
					//close network
				#ifdef AMOS_DEBUG
					AMPrintf("noble:SenderPacket. .....................Uncheck Exceeded! Close Socket!\n");
				#endif // AMOS_DEBUG
					PCContextGetInstance()->socketClose((AMUInt32*)&pPacketConnection->pProtocolEngine->pPCCore->socketFd);
				}
			#ifdef AMOS_DEBUG
				AMPrintf("noble:SenderPacket. send ok. \n");
			#endif
			}
		}
		else
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:socket isn't ready.. socket = %d\n", pPacketConnection->pProtocolEngine->pPCCore->socketFd);
		#endif
		}

	#ifdef AMOS_DEBUG
		AMPrintf("noble:SenderPacket. before packfree. \n");
	#endif
		if(pPacketConnection->pPackerFree)
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:SenderPacket. packfree 1111");
		#endif
			pPacketConnection->pPackerFree((AMInt8*)pBuffer, pPacketConnection->pReference);
		#ifdef AMOS_DEBUG
			AMPrintf("noble:SenderPacket. packfree 2222");
		#endif		
		}
		else
		{
		
		#ifdef AMOS_DEBUG
			AMPrintf("noble:SenderPacket. packfree 3333");
		#endif		
			retCode = eInvalidPackerFree;
		}

#ifdef AMOS_DEBUG
		AMPrintf("noble:SenderPacket. packfree OK.");
#endif

		pBuffer = NULL;
	}	
	
	//dengxiang: don't use "else" to link "if(retCode == eOK)"
	if(retCode != eOK)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:pack procedure has error. PCRetCode=%d.\n", retCode);
	#endif
		// send exception to uplayer.
		PacketExceptionHandler(pPacketConnection, retCode, PC_PACK_EXCEPTION_IND);
	}

#ifdef AMOS_DEBUG
	AMPrintf("noble:SenderPacket..>>>>>> \n");
#endif
}
/************************************************************************/
// 发送给socket的消息在此处理
/************************************************************************/
#ifdef AMOS
	AMPVoid SenderRunner(AMPVoid lpParam)
#else
	#ifdef WIN32
	AMUInt32 SenderRunner(void* lpParam)
	#endif
#endif
{
	Event* pEvent = NULL;
	AMInt32 isExit = 0;
	PcNetworkConfig* pConfig = NULL;
	
	ProtocolEngine* pProtocolEngine = ((PacketConnection*)lpParam)->pProtocolEngine;
	PacketConnection* pPacketConnection;

	AMInt32	iBarkTime = 0, iNowTime = 0, iMissCount = 0;
	PcHealthCheckConfig hcConfig = {0, NULL}; 
	Event* pHealthCheckEvent = NULL;
	Event* pHealthCheckSelfEvent = NULL;

	PcClearVarInd* pClearVarInd = NULL;

	while(1)
	{
		//get Request EVENT from sender queue.
		PullQueue(pProtocolEngine->pPCCore->pSenderQueue, &pEvent, 1);
		if(pEvent != NULL)
		{
			pPacketConnection = (PacketConnection*)pEvent->hPCHandle;
			switch(pEvent->id)
			{
			case PC_SHUTDOWN_IND: //关闭当前模块
			#ifdef AMOS_DEBUG
				AMPrintf("noble:exit sender thread....\n");
			#endif
				isExit = 1;
				break;

			case PC_CLEAR_VAR_IND:
			#ifdef AMOS_DEBUG
				AMPrintf("noble:sender PC_CLEAR_VAR_IND....\n");
			#endif
				//network need to close
				if(pPacketConnection && pPacketConnection->pNetwork && pPacketConnection->pNetwork->fd>0) 
					PCContextGetInstance()->socketClose(&pPacketConnection->pNetwork->fd);

				pClearVarInd = (PcClearVarInd*)pEvent->pContent;
				pProtocolEngine->pPCContext->semaphoreSignal(pClearVarInd->pSemaphore);
				break;

			case PC_SET_HEALTH_CHECK_CONFIG:

				if(iBarkTime == 0)
					memcpy(&hcConfig, (PcHealthCheckConfig*)pEvent->pContent, sizeof(hcConfig));

				if( IsPCNetworkReady(pProtocolEngine->pPCCore) > 0 && 
					IsPCNeedHealthCheck(pProtocolEngine->pPCCore) > 0 )
				{
					iNowTime = AMGetUTCTime(AMNULL);
					if( iBarkTime+hcConfig.second < iNowTime || iNowTime < iBarkTime)
					{
						if(hcConfig.pMaker != NULL)
						{
							hcConfig.pMaker(pEvent->hPCHandle, &pHealthCheckEvent, pPacketConnection->pReference);

							SenderPacket(pHealthCheckEvent);
							EventDestory(&pHealthCheckEvent);

							iBarkTime = iNowTime;
						}
						iMissCount = 0;
					}
				}

				//send PC_SET_HEALTH_CHECK_CONFIG to self.
				EventCreate(pEvent->hPCHandle, &pHealthCheckSelfEvent, 
					PC_SET_HEALTH_CHECK_CONFIG, (void*)&hcConfig, sizeof(hcConfig));
				PCPostMessage(pHealthCheckSelfEvent, pProtocolEngine->pPCCore->pSenderQueue);
				pProtocolEngine->pPCContext->sleep(HEALTH_CHECK_SLEEP_TIME);
				break;

			case PC_SET_NETWORK_CONFIG: //预处理网络连接
				pConfig = (PcNetworkConfig*)pEvent->pContent;
				
				if(pConfig->nCount <= 1)
				{
				#ifdef AMOS_DEBUG
					AMPrintf("noble:sender socket create. ip = %s:%d\n", pConfig->ip, pConfig->port);
				#endif
					pProtocolEngine->pPCCore->socketFd = 
						pProtocolEngine->pPCContext->socketCreate(
								pConfig->ip, pConfig->port
							#ifdef AMOS
							#ifdef SOCKET_ASYNC
								, 
								(AMInt32)pIMnet,
								AMSocketIAPGet(),
								SocketConnectionCallback,
								SocketSenderCallback,
								SocketReaderCallback
							#endif
							#endif
						);
				#ifdef AMOS_DEBUG
					AMPrintf("noble:sender socket create over %d \n", pProtocolEngine->pPCCore->socketFd);
				#endif
				}

				if(pPacketConnection->pNetwork != NULL)
					pPacketConnection->pNetwork->fd = pProtocolEngine->pPCCore->socketFd;

				if(pConfig->sync)
				{
					//tell pcmgr PacketConnectionOpen
					pPacketConnection->pProtocolEngine->pPCContext->semaphoreSignal(&(pPacketConnection->semaphore));
				}
				else
				{
				#ifdef SOCKET_ASYNC
					if(pProtocolEngine->pPCCore->socketFd <= 0)
				#endif
					{
						SendNetworkConnectedMsg(pPacketConnection, pProtocolEngine->pPCCore->socketFd);
					}
				}
				break;
				
			default:
				SenderPacket(pEvent);
				break;
			}
		}
		
		//destory EVENT
		if(pEvent != NULL)
			EventDestory(&pEvent);

		if(isExit == 1)
			goto SenderEnd;
	}
		
SenderEnd:
	pProtocolEngine->pPCContext->semaphoreSignal(&pProtocolEngine->pPCCore->pSenderLooper->semaphore);
	
#ifdef AMOS
	return (AMPVoid)isExit;
#else
	#ifdef WIN32
		return isExit;
	#endif
#endif
}

PCRetCode SendNetworkConnectedMsg(PacketConnection* pPC, AMInt32 result)
{
	PCRetCode retCode;
	Event* pEventTemp = NULL;
	PcCnfNetworkConfig confirm;
	
	pEventTemp = NULL;
	memset(&confirm, 0, sizeof(confirm));
	confirm.result = result;
	
	retCode = EventCreate(pPC, &pEventTemp, PC_CNF_NETWORK_CONFIG, (void*)&confirm, sizeof(confirm));
	if(retCode == eOK)
		PCPostMessage(pEventTemp, pPC->pProtocolEngine->pPCCore->pCallbackQueue);
	
	return retCode;
}

/************************************************************************/
// 处理RSP,NTF到来的 EVENT消息
/************************************************************************/
#ifdef AMOS
	AMPVoid CallbackRunner(AMPVoid lpParam)
#else
	#ifdef WIN32
	AMUInt32 CallbackRunner(void* lpParam)
	#endif
#endif
{
	Event* pEvent = NULL;
	AMInt32 isExit = 0;
	ProtocolEngine* pProtocolEngine = ((PacketConnection*)lpParam)->pProtocolEngine;
	PacketConnection* pPacketConnection;
	PcClearVarInd* pClearVarInd = NULL;

	while(1)
	{
		//get Request EVENT from callback queue.
		PullQueue(pProtocolEngine->pPCCore->pCallbackQueue, &pEvent, 1);
		if(pEvent != NULL)
		{
			pPacketConnection = (PacketConnection*)pEvent->hPCHandle;

			switch(pEvent->id)
			{
			case PC_SHUTDOWN_IND:
			#ifdef AMOS_DEBUG
				AMPrintf("noble:exit callback thread....\n");
			#endif
				isExit = 1;
				break;
				
			case PC_CLEAR_VAR_IND:
			#ifdef AMOS_DEBUG
				AMPrintf("noble:callback PC_CLEAR_VAR_IND....\n");
			#endif
				//network need to close
				if(pPacketConnection && pPacketConnection->pNetwork && pPacketConnection->pNetwork->fd>0) 
					PCContextGetInstance()->socketClose(&pPacketConnection->pNetwork->fd);

				pClearVarInd = (PcClearVarInd*)pEvent->pContent;
				PCContextGetInstance()->semaphoreSignal(pClearVarInd->pSemaphore);
				break;

			default:
			#ifdef AMOS_DEBUG
				AMPrintf("noble:callback event <<<<< 0x%x... start\n", pEvent->id);
			#endif
				if(pEvent->id == PC_RECV_EXCEPTION_IND)
					ProtocolNetworkDestory(pEvent->hPCHandle, 1);

				if(pPacketConnection && pPacketConnection->pReceiver)
					pPacketConnection->pReceiver(pPacketConnection, pEvent, pPacketConnection->pReference);
	
			#ifdef AMOS_DEBUG
				AMPrintf("noble:callback event >>>>> 0x%x end \n", pEvent->id);
			#endif
				break;
			}
			
			//destory EVENT
			EventDestory(&pEvent);

			if(isExit == 1)
				goto CallbackEnd;
		}
	}
	
CallbackEnd:
	PCContextGetInstance()->semaphoreSignal(&pProtocolEngine->pPCCore->pCallbackLooper->semaphore);
	
#ifdef AMOS
	return (AMPVoid)isExit;
#else
	#ifdef WIN32
		return isExit;
	#endif
#endif
}

/************************************************************************/
// PCCore* PCCreate()
/************************************************************************/
PCCore* PCCoreCreate()
{
	PCCore* pPCCore = NULL;
	
	pPCCore = (PCCore*)AMMalloc(sizeof(PCCore));
	memset(pPCCore, 0, sizeof(PCCore));

	if(pPCCore)
	{
		QueueCreate(&pPCCore->pReaderQueue);
		QueueCreate(&pPCCore->pSenderQueue);
		QueueCreate(&pPCCore->pCallbackQueue);
	}

	return pPCCore;
}

void PCCoreRun(struct ST_PacketConnection* pPacketConnection)
{
	PCCore* pPCCore = pPacketConnection->pProtocolEngine->pPCCore;
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:create reader thread.\n");
#endif
	LooperCreate(pPacketConnection, &pPCCore->pReaderLooper, ReaderRunner, 0, 0, 0);

#ifdef AMOS_DEBUG
	AMPrintf("noble:create sender thread.\n");
#endif
	LooperCreate(pPacketConnection, &pPCCore->pSenderLooper, SenderRunner, 0, 0, 0);

#ifdef AMOS_DEBUG
	AMPrintf("noble:create callback thread.\n");
#endif
	LooperCreate(pPacketConnection, &pPCCore->pCallbackLooper, CallbackRunner, 0, 0, 0);

	pPCCore->coreStatus = eIMnetCoreStart;
}

void LoopStop(Queue* pQueue, Semaphore* pSemaphore)
{
	Event* pEvent = NULL;
	PcShutdownInd indShutdown;

	memset(&indShutdown, 0, sizeof(indShutdown));
	
	//send out shutdown signal to close loop
	EventCreate(NULL, &pEvent, PC_SHUTDOWN_IND, (void*)&indShutdown, sizeof(indShutdown));
	PCPostMessage(pEvent, pQueue);
	PCContextGetInstance()->semaphoreWait(pSemaphore);
}

void PCCoreStop(struct ST_ProtocolEngine* pProtocolEngine)
{
	pProtocolEngine->pPCCore->coreStatus = eIMnetCoreStop;
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreStop <<<<< reader\n");
#endif

	//close looper.
	LoopStop(pProtocolEngine->pPCCore->pReaderQueue, 
		&pProtocolEngine->pPCCore->pReaderLooper->semaphore);

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreStop <<<<< sender\n");
#endif

	LoopStop(pProtocolEngine->pPCCore->pSenderQueue, 
		&pProtocolEngine->pPCCore->pSenderLooper->semaphore);
	
#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreStop <<<<< callback\n");
#endif

	LoopStop(pProtocolEngine->pPCCore->pCallbackQueue, 
		&pProtocolEngine->pPCCore->pCallbackLooper->semaphore);

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreStop <<<<< quit\n");
#endif

}

void PCCoreClear(ST_PacketConnection* pPacketConnection, Semaphore* pSemaphore, PCClearType type)
{
	Event* pEvent1 = NULL;
	Event* pEvent2 = NULL;
	Event* pEvent3 = NULL;

	PcClearVarInd request;
	ProtocolEngine* pProtocolEngine = pPacketConnection->pProtocolEngine;

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreClear <<<<< PCClearType = %d start...\n", type);
#endif

	memset(&request, 0, sizeof(request));
	//denx add for sync
	pProtocolEngine->pPCContext->semaphoreCreate(pSemaphore, 0, 2);
	request.pSemaphore = pSemaphore;

	EventCreate(pPacketConnection, &pEvent1, PC_CLEAR_VAR_IND, (void*)&request, sizeof(request));
	EventCreate(pPacketConnection, &pEvent2, PC_CLEAR_VAR_IND, (void*)&request, sizeof(request));
	PCPostMessage(pEvent1, pProtocolEngine->pPCCore->pReaderQueue);
	PCPostMessage(pEvent2, pProtocolEngine->pPCCore->pSenderQueue);
	
	PCContextGetInstance()->semaphoreWait(pSemaphore);
	PCContextGetInstance()->semaphoreWait(pSemaphore);
	PCContextGetInstance()->semaphoreDestory(pSemaphore);

	if(type == ePCClearPCHandle)
	{
	#ifdef AMOS_DEBUG
		AMPrintf("noble:PCCoreClear <<<<< ePCClearPCHandle...\n");
	#endif

		pProtocolEngine->pPCContext->semaphoreCreate(pSemaphore, 0, 1);
		request.pSemaphore = pSemaphore;
		EventCreate(pPacketConnection, &pEvent3, PC_CLEAR_VAR_IND, (void*)&request, sizeof(request));
		PCPostMessage(pEvent3, pProtocolEngine->pPCCore->pCallbackQueue);

	#ifdef AMOS_DEBUG
		AMPrintf("noble:PCCoreClear <<<<< ePCClearPCHandle before wait..\n");
	#endif
		PCContextGetInstance()->semaphoreWait(pSemaphore);
		PCContextGetInstance()->semaphoreDestory(pSemaphore);
	}

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCCoreClear >>>>> end...\n");
#endif
}

void PCCoreDestory(struct ST_ProtocolEngine* pProtocolEngine)
{	
	QueueDestory(&pProtocolEngine->pPCCore->pReaderQueue);
	QueueDestory(&pProtocolEngine->pPCCore->pSenderQueue);
	QueueDestory(&pProtocolEngine->pPCCore->pCallbackQueue);
	
	//VarKeeperDestory(&pIMnetCore->pVarKeeper);

	LooperDestory(&pProtocolEngine->pPCCore->pReaderLooper);
	LooperDestory(&pProtocolEngine->pPCCore->pSenderLooper);
	LooperDestory(&pProtocolEngine->pPCCore->pCallbackLooper);

	AMFree(pProtocolEngine->pPCCore);
}

AMInt32 IsPCNetworkReady(PCCore* pPCCore)
{
	if(pPCCore == NULL)
		return -1;
	else
		return pPCCore->socketFd;
}


AMInt32 IsPCNeedHealthCheck(PCCore* pPCCore)
{
	if(pPCCore == NULL)
		return -1;
	else
		return pPCCore->needHealthCheck;
}

void PCCoreSwitchHealthCheck(PCCore* pPCCore, AMInt32 value)
{
	if(pPCCore != NULL)
		pPCCore->needHealthCheck = value;
}

#ifdef AMOS
#ifdef SOCKET_ASYNC
void SocketConnectionCallback(AMInt32 reference, AMInt32 socket, SocketStatus status)
{
	IMnet* pIMnet = (IMnet*)reference;
	
	switch(status)
	{
	case eSocketConnecting:
		break;
		
	case eSocketConnected:
		SendNetworkConnectedMsg(pIMnet, 1);
		break;
		
	case eSocketConnectFail:
	case eSocketClose:
	case eSocketShutdown:
		SendNetworkConnectedMsg(pIMnet, -1);
		break;
	
	default:
		SendNetworkConnectedMsg(pIMnet, -1);
		break;
	}
}

void SocketSenderCallback(AMInt32 reference, AMInt32 socket, SocketStatus status)
{
	IMnet* pIMnet = (IMnet*)reference;
	switch(status)
	{	
	case eSocketSendOK:
		break;
		
	case eSocketSendFail:
#ifdef AMOS_DEBUG
		AMPrintf("noble:SocketSenderCallback: Send Fail.");
#endif
		break;
			
	default:
#ifdef AMOS_DEBUG
		AMPrintf("noble:SocketSenderCallback: default.");
#endif
		break;
	}
}

void SocketReaderCallback(AMInt32 reference, AMInt32 socket, SocketStatus status)
{
	IMnet* pIMnet = (IMnet*)reference;
	Event* pEvent = NULL;
	ImSocketInd indication;
	PCRetCode retCode;
	
	memset(&indication, 0, sizeof(indication));
	indication.indType = status;
	retCode = EventCreate(&pEvent, PC_SOCKET_IND, (void*)&indication, sizeof(indication));
	if(retCode == eOK)
	{
		IMnetPostMessage(pIMnet, pEvent, IMnetReaderQueue);
	}
}
#endif
#endif
