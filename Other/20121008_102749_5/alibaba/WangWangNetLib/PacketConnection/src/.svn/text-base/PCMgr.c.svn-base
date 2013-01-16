#include "PCMgr.h"
#include "PCEvent.h"

#include "string.h"

//#define USE_ONE_REAL_SOCKET
//#define USE_ONE_PROTOCOL_ENGINE
#define MAX_HEALTH_CHECK_MISS 2
/************************************************************************/
// Packet Manager
/************************************************************************/
PacketConnection* PCMgrGetPCHandle(PCServiceID serviceID)
{
	PacketConnection* ptemp = PCMgrGetInstance()->pFirstPC;

	while(ptemp)
	{
		if(ptemp->serviceID == serviceID)
			return ptemp;
		else
			ptemp = ptemp->next;
	}
	
	return NULL;
}

PacketConnectionMgr* PCMgrGetInstance()
{
	static PacketConnectionMgr s_PacketConnectionMgr = { NULL, NULL };

	if(s_PacketConnectionMgr.pFirstPC == NULL && s_PacketConnectionMgr.mgrCritical == NULL)
		PCContextGetInstance()->mutexCreate(&s_PacketConnectionMgr.mgrCritical);

	return &s_PacketConnectionMgr;
}

PacketConnection* GetLastPacketConnection(PacketConnection* pFirst)
{
	PacketConnection* plast = NULL;
	PacketConnection* ptemp = pFirst;

	while(ptemp)
	{
		plast = ptemp;
		ptemp = ptemp->next;
	}

	return plast;
}

void PCMgrAddPacketConnection(PacketConnection* pPC)
{
	PacketConnection* last = NULL;
	PacketConnectionMgr* pMgr = NULL;

	pMgr = PCMgrGetInstance();
	if(pMgr == NULL)
		return;

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCMgrAddPacketConnection lock.\n");
#endif
	PCContextGetInstance()->mutexLock(&pMgr->mgrCritical);
	last = GetLastPacketConnection(pMgr->pFirstPC);
	if(last == NULL)
		PCMgrGetInstance()->pFirstPC = pPC;
	else
		last->next = pPC;
	PCContextGetInstance()->mutexUnlock(&pMgr->mgrCritical);

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCMgrAddPacketConnection unlock.\n");
#endif
}

void PCMgrRemovePacketConnection(PacketConnection* pPC)
{
	PacketConnectionMgr* pMgr = NULL;
	PacketConnection* ptemp = NULL;
	PacketConnection* pPre = NULL;

	pMgr = PCMgrGetInstance();

#ifdef AMOS_DEBUG
	AMPrintf("noble:PCMgrRemovePacketConnection lock.\n");
#endif
	PCContextGetInstance()->mutexLock(&pMgr->mgrCritical);
	
	if(pMgr->pFirstPC == NULL)
	{
		PCContextGetInstance()->mutexUnlock(&pMgr->mgrCritical);
#ifdef AMOS_DEBUG
		AMPrintf("noble:PCMgrRemovePacketConnection unlock 1.\n");
#endif
		PCContextGetInstance()->mutexDestory(&pMgr->mgrCritical);
		return;
	}

	//update packet connection mgr.
	if(pMgr->pFirstPC == pPC)
		pMgr->pFirstPC = pPC->next;
	else
	{
		//remove it from packet connection list.
		ptemp = pMgr->pFirstPC;
		while(ptemp)
		{
			pPre = ptemp;
			ptemp = ptemp->next;

			if(ptemp == pPC)
			{
				pPre->next = pPC->next;
				break;
			}
		}
	}
	
	PCContextGetInstance()->mutexUnlock(&pMgr->mgrCritical);
#ifdef AMOS_DEBUG
	AMPrintf("noble:PCMgrRemovePacketConnection unlock 2.\n");
#endif
	if(pMgr->pFirstPC == NULL)
		PCContextGetInstance()->mutexDestory(&pMgr->mgrCritical);
}

/************************************************************************/
// protocol engine
/************************************************************************/
PCRetCode ProtocolEngineCreate(PacketConnection* pPC)
{
#ifdef USE_ONE_PROTOCOL_ENGINE
	static 
#endif
	ProtocolEngine* sp_ProtocolEngine = NULL;

	if(pPC == NULL)
		return eInvalidParam;

	sp_ProtocolEngine = pPC->pProtocolEngine;
	if(sp_ProtocolEngine == NULL)
	{
		sp_ProtocolEngine = (ProtocolEngine*)AMMalloc(sizeof(ProtocolEngine));
		if(sp_ProtocolEngine)
		{
			memset(sp_ProtocolEngine, 0, sizeof(ProtocolEngine));
			sp_ProtocolEngine->nCount ++ ;
			sp_ProtocolEngine->pPCContext = PCContextGetInstance();
			sp_ProtocolEngine->pPCCore = PCCoreCreate(PCContextGetInstance());
				 
			pPC->pProtocolEngine = sp_ProtocolEngine;

			//start core.
			PCCoreRun(pPC);
		}
		else
			return eMallocError;
	}
	else
	{
		sp_ProtocolEngine->nCount++;	
	}

#ifdef AMOS_DEBUG
	AMPrintf("noble:ProtocolEngineCreate OK.\n");
#endif
	return eOK;
}

PCRetCode ProtocolEngineDestory(ProtocolEngine** ppProtocolEngine)
{
	if(ppProtocolEngine!=NULL && *ppProtocolEngine!=NULL)
	{
		(*ppProtocolEngine)->nCount--;

		if((*ppProtocolEngine)->nCount == 0)
		{
			PCCoreStop(*ppProtocolEngine);

			//destory subsystem.
			PCCoreDestory(*ppProtocolEngine);

			AMFree(*ppProtocolEngine);
		}

		*ppProtocolEngine = NULL;
	}
	return eOK;
}

/************************************************************************/
// protocol network
/************************************************************************/
PCRetCode ProtocolNetworkCreate(PcNetworkConfig** ppProtocolNetwork, AMChar* ip, AMUInt16 port, AMInt32 sync)
{
#ifdef USE_ONE_REAL_SOCKET
	static 
#endif
	PcNetworkConfig* sp_PcNetworkConfig = NULL;
	
	if(ppProtocolNetwork == NULL)
		return eInvalidParam;

	if(sp_PcNetworkConfig == NULL)
	{
		sp_PcNetworkConfig = (PcNetworkConfig*)AMMalloc(sizeof(PcNetworkConfig));
		if(sp_PcNetworkConfig)
		{
			memset(sp_PcNetworkConfig, 0, sizeof(PcNetworkConfig));
			sp_PcNetworkConfig->maxHealthCheckMiss = MAX_HEALTH_CHECK_MISS;
			sp_PcNetworkConfig->nCount ++ ;
			strcpy(sp_PcNetworkConfig->ip, ip);
			sp_PcNetworkConfig->port = port;
			sp_PcNetworkConfig->sync = sync;
		}
		else
			return eMallocError;
	}
	else
	{
		sp_PcNetworkConfig->nCount ++ ;
	}

	*ppProtocolNetwork = sp_PcNetworkConfig;

	return eOK;
}

#if IM_NET_SHUT_SOCKET
PCRetCode ProtocolNetworkShut(PacketConnection *pPC)
{
	PcNetworkConfig** ppNetwork = NULL;

	if(pPC)
		ppNetwork = &pPC->pNetwork;
	else
		return eInvalidParam;

	if(ppNetwork != NULL && *ppNetwork != NULL)
	{
		if((*ppNetwork)->fd > 0)
		{
			PCContextGetInstance()->socketClose((AMUInt32*)&((*ppNetwork)->fd));
		}

	}
	return eOK;
}
#endif
//type == 0: 主动发起关闭socket.
//type == 1: 被动关闭socket.
PCRetCode ProtocolNetworkDestory(PacketConnection* pPC, AMInt32 type)
{
	PcNetworkConfig** ppNetwork = NULL;

	if(pPC)
		ppNetwork = &pPC->pNetwork;
	else
		return eInvalidParam;

#ifdef AMOS_DEBUG
	AMPrintf("noble:ProtocolNetworkDestory <<<< network = 0x%x\n", *ppNetwork);
#endif

	if(ppNetwork != NULL && *ppNetwork != NULL)
	{
		(*ppNetwork)->nCount--;

		if((*ppNetwork)->nCount < 0)
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:ProtocolNetworkDestory >>>> %d end\n", (*ppNetwork)->nCount);
		#endif	
			return eOK;
		}
		else if((*ppNetwork)->nCount == 0)
		{
			if(type == 0)
			{			
				if((*ppNetwork)->fd > 0)
				{
					//close socket.
					PCContextGetInstance()->socketClose((AMUInt32*)&((*ppNetwork)->fd));
				#ifdef AMOS_DEBUG
					AMPrintf("noble:ProtocolNetworkDestory socketclose %d\n", (*ppNetwork)->fd);
				#endif
				}

				//clear this hHandle using in the engine.
				PCCoreClear(pPC, &pPC->semaphore, ePCClearNetwork);
			}
		#ifdef AMOS_DEBUG
			AMPrintf("noble:ProtocolNetworkDestory free network = 0x%x\n", *ppNetwork);
		#endif
			AMFree(*ppNetwork);
		}
		
		*ppNetwork = NULL;
	}

#ifdef AMOS_DEBUG
	AMPrintf("noble:ProtocolNetworkDestory >>>> end\n");
#endif
	return eOK;
}


/************************************************************************/
// packet connection
/************************************************************************/
PCRetCode PacketConnectionCreate(PCHandle* phHandle, PCServiceID nSID, PCReference pReference)
{
	PacketConnection* plast = NULL;
	PacketConnection* pPC;
	
	if(phHandle == NULL)
		return eInvalidParam;

	pPC = (PacketConnection*)AMMalloc(sizeof(PacketConnection));
	if(pPC != NULL)
	{
		memset(pPC, 0, sizeof(PacketConnection));
		
		pPC->pReference = pReference;
		pPC->serviceID = nSID;

		pPC->pPCContext = PCContextGetInstance();
		ProtocolEngineCreate(pPC);
		
		//add to pc mgr.
		PCMgrAddPacketConnection(pPC);

		*phHandle = (PCHandle*)pPC;		

	#ifdef AMOS_DEBUG
		AMPrintf("noble:PacketConnectionCreate ok \n");
	#endif
		return eOK;
	}
	else
	{
		return eMallocError;
	}
}

PCRetCode PacketConnectionDestory(PCHandle hHandle)
{
	PacketConnection* pPre = NULL;
	PacketConnection* ptemp = NULL;

	PacketConnection* pPC = NULL;
	if(hHandle != NULL)
	{
		pPC = (PacketConnection*)hHandle;

#ifdef AMOS_DEBUG
		AMPrintf("noble:PacketConnectionDestory <<<< PC = 0x%x start\n", pPC);
#endif
		//clear this hHandle using in the engine.
		PCCoreClear(pPC, &pPC->semaphore, ePCClearPCHandle);

		//stop engine.
		ProtocolEngineDestory(&pPC->pProtocolEngine);

		PCMgrRemovePacketConnection(pPC);
	
#ifdef AMOS_DEBUG
		AMPrintf("noble:PacketConnectionDestory free = 0x%x\n", pPC);
#endif
		AMFree((void*)pPC);
		pPC = NULL;

#ifdef AMOS_DEBUG
		AMPrintf("noble:PacketConnectionDestory >>>> end\n");
#endif
		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

/************************************************************************/
// packet connection send
/************************************************************************/
PCRetCode PacketConnectionSend(Event* pEvt)
{
	PacketConnection* pPC = NULL;
	
	if(pEvt != NULL && pEvt->hPCHandle != NULL)
	{
		pPC = (PacketConnection*)(pEvt->hPCHandle);

		PCPostMessage(pEvt, pPC->pProtocolEngine->pPCCore->pSenderQueue);

		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

PCRetCode PacketConnectionSendtoCallbackProc(Event* pEvt, AMBool bLow)
{
	PacketConnection* pPC = NULL;

	if(pEvt != NULL && pEvt->hPCHandle != NULL)
	{
		pPC = (PacketConnection*)(pEvt->hPCHandle);

		PCPostMessageProc(pEvt, pPC->pProtocolEngine->pPCCore->pCallbackQueue, bLow);

		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

PCRetCode PacketConnectionSendtoCallback(Event* pEvt)
{
	return PacketConnectionSendtoCallbackProc(pEvt, AMFALSE);
}

PCRetCode PacketConnectionSetReceiver(PCHandle hHandle, PCReceiver pReceiver)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(pPC != NULL)
	{
		pPC->pReceiver = pReceiver;
		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

PCRetCode PacketConnectionSetPacker(PCHandle hHandle, PCPacker pPacker, PCPackerFree pPackerFree)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(pPC != NULL)
	{
		pPC->pPacker = pPacker;
		pPC->pPackerFree = pPackerFree;
		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

PCRetCode PacketConnectionSetUnpacker(PCHandle hHandle, PCUnpacker pUnpacker)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(pPC != NULL)
	{
		pPC->pUnpacker = pUnpacker;
		return eOK;
	}
	else
	{
		return eInvalidParam;
	}
}

/************************************************************************/
// packet connection open.
/************************************************************************/
PCRetCode PacketConnectionOpen(PCHandle hHandle, AMChar* ip, AMUInt16 port, AMInt32 sync)
{
	PCRetCode retCode;
	Event* pEvent = NULL;
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(ip == NULL || pPC == NULL)
		return eInvalidParam;

	if(pPC)
	{
		if(pPC->pNetwork != NULL)
			return eAlreadyExist;

		ProtocolNetworkCreate(&(pPC->pNetwork), ip, port, sync);

		retCode = EventCreate(hHandle, &pEvent, PC_SET_NETWORK_CONFIG, (void*)(pPC->pNetwork), sizeof(PcNetworkConfig));
		if(retCode == eOK)
		{
			PacketConnectionSend(pEvent);

			//denx add for network sync
			if(sync)
			{
				pPC->pProtocolEngine->pPCContext->semaphoreCreate(&(pPC->semaphore), 0, 1);
				pPC->pProtocolEngine->pPCContext->semaphoreWait(&(pPC->semaphore));
				pPC->pProtocolEngine->pPCContext->semaphoreDestory(&(pPC->semaphore));	


				if(pPC->pNetwork->fd <= 0 )
					return eNetworkError;
			}
		}
		else
		{
			return retCode;
		}

	}
	else
	{
		return eNotReady;
	}

	return eOK;
}

#if IM_NET_SHUT_SOCKET
PCRetCode PacketConnectionShut(PCHandle hHandle)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(pPC != NULL && pPC->pNetwork != NULL)
	{
		ProtocolNetworkShut(pPC);
	}

	return eOK;
}
#endif

/************************************************************************/
// packet connection close.
/************************************************************************/
PCRetCode PacketConnectionClose(PCHandle hHandle)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;
	
	if(pPC != NULL && pPC->pNetwork != NULL)
	{
		ProtocolNetworkDestory(pPC, 0);
	}

	return eOK;
}

/************************************************************************/
// PacketConnectionGetRef
/************************************************************************/
PCReference PacketConnectionGetRef(PCHandle hHandle)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;
	return pPC->pReference;
}

/************************************************************************/
// PacketConnectionStartKeepAlive
/************************************************************************/
PCRetCode PacketConnectionStartKeepAlive(PCHandle hHandle, AMInt32 second, PCMakeHealthCheckEvent pMakeHealthCheck)
{
	PCRetCode retCode;
	Event* pEvent = NULL;
	PcHealthCheckConfig request;
	PacketConnection* pPC = (PacketConnection*)hHandle;
	
	if(second == 0 || pPC == NULL || pMakeHealthCheck == NULL)
		return eInvalidParam;

	memset(&request, 0, sizeof(request));
	request.pMaker = pMakeHealthCheck;
	request.second = second;
	
	retCode = EventCreate(hHandle, &pEvent, PC_SET_HEALTH_CHECK_CONFIG, (void*)&request, sizeof(request));
	if(retCode == eOK)
	{
		PCCoreSwitchHealthCheck(pPC->pProtocolEngine->pPCCore, 1);
		return PacketConnectionSend(pEvent);
	}
	else
	{
		return retCode;
	}
}

PCRetCode PacketCOnnectionStopKeepAlive(PCHandle hHandle)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;

	if(pPC != NULL && pPC->pProtocolEngine != NULL && pPC->pProtocolEngine->pPCCore != NULL)
	{
		PCCoreSwitchHealthCheck(pPC->pProtocolEngine->pPCCore, 0);
	}
	return eOK;
}

AMInt32 PacketConnectionIsKeepAlive(PCHandle hHandle)
{
	PacketConnection* pPC = (PacketConnection*)hHandle;
	
	if(pPC != NULL && pPC->pProtocolEngine != NULL && pPC->pProtocolEngine->pPCCore != NULL)
	{
		return pPC->pProtocolEngine->pPCCore->needHealthCheck;
	}
	else
	{
		return 0;
	}
}

