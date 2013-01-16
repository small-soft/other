#include "AIMTrans.h"
#include "AIMTransModule.h"
#include "IMnet.h"
#include "AIMUtil.h"

#include "AMStdlib.h"

#define _AIMTrans_notify(pIm, funcName,  ...)		\
	do \
	{\
		if((pIm)->callback && (pIm)->callback->funcName)\
		(pIm)->callback->funcName((pIm)->callback->pvArg, ## __VA_ARGS__);\
	} while (0)\


AMInt32	AIMTransModule_create(IAIM *pIM, AMHandle *phTransModule)
{
	AIMTransModule *pTransModule = AMNULL;

	AMAssert(pIM && phTransModule);
	*phTransModule = AMNULL;

	pTransModule = (AIMTransModule*)AMMalloc(sizeof(AIMTransModule));

	if(!pTransModule)
		return eAIM_RESULT_MALLOC_ERROR;
	
	AMMemset(pTransModule, 0, sizeof(AIMTransModule));

	if(AMThreadMutexCreate(&pTransModule->mtxLock))
	{
		AMFree(pTransModule);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	construct(List, &pTransModule->lstTrans, sizeof(AIMTrans), FREEOBJ);
	set_dealloc(List, &pTransModule->lstTrans, AIMTrans_destroy);

	pTransModule->pIM = pIM;
	
	*phTransModule = pTransModule;

	return eAIM_RESULT_OK;
}

AMVoid		AIMTransModule_destroy(AMHandle hTransModule)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	
	AMAssert(pTransModule);

	destruct(List, &pTransModule->lstTrans);

	AMThreadMutexDestroy(&pTransModule->mtxLock);

	if(pTransModule->pTaskMgr)
		AMTaskMgrDestory(pTransModule->pTaskMgr);

	AMFree(pTransModule);
}
/*
 *	加锁，加入队列，调用getAppAddr
 */
static AMInt32	_AIMTransModule_addTrans(AMHandle hTransModule, AIMTrans *pTrans, AMInt32 *piTransId)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	AIMTrans *pTransFind = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK;
	AMChar szSessionId[MAX_INT_NUMBER_LEN] = {0};

	AMAssert(pTransModule && pTrans && piTransId);

	AMThreadMutexLock(&pTransModule->mtxLock);

	set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpContent);
	if(!find_List(&pTransModule->lstTrans, pTrans, sizeof(AIMTrans)))
	{
		*piTransId = pTrans->iTransId = ++pTransModule->iLastTransId;

		_AIMItoa(pTrans->iTransId, szSessionId);
		push_back(List, &pTransModule->lstTrans, pTrans, DYNAMIC);
		pTrans->pTransModule = hTransModule;
	}
	else
		iRetCode = eAIM_RESULT_DUP;

	AMThreadMutexUnlock(&pTransModule->mtxLock);

	if(!iRetCode)
		IMnetGetAppAddr(pTransModule->pIM->pNetModel, szSessionId, 0);
	
	return iRetCode;
}

/*
 *	创建一个Trans
 *	加锁，加入队列，调用getAppAddr
 */
AMInt32	AIMTransModule_receive(AMHandle hTransModule, const AMChar *szContactId, 
								   const AMChar *szXml, const AMChar *szFileDest, AMInt32 *piTaskId)
{	
	AMInt32 iRetCode = eAIM_RESULT_OK;
	AIMTrans *pTrans = AMNULL;
	
	if(iRetCode = AIMTrans_createReceive(szContactId, szXml, szFileDest, &pTrans))
		return iRetCode;
	
	return _AIMTransModule_addTrans(hTransModule, pTrans, piTaskId);
}
/*
 *	创建一个Trans
 *	加锁，加入队列，调用getAppAddr
 */
AMInt32	AIMTransModule_send(AMHandle hTransModule, const AMChar *szContactId,
								const AMChar *szFile, AMInt32 *piTaskId)
{
	AMInt32 iRetCode = eAIM_RESULT_OK;
	AIMTrans *pTrans = AMNULL;

	if(iRetCode = AIMTrans_createSend(szContactId, szFile, &pTrans))
		return iRetCode;

	return _AIMTransModule_addTrans(hTransModule, pTrans, piTaskId);
}
/*
 *	加锁检查bCanceled 1\ true:	移除pTrans，返回eAIM_RESULT_FAIL
 *	                  2\ flase: 更新进度，并通知，返回eAIM_RESULT_OK
 */
AMInt32	AIMTransModule_update(AMHandle hTransModule, AMHandle hTrans, AMInt32 iProgress)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	AMInt32 iRetCode = 0;
	AIM_NTF_PROGRESS ntfProgress;
	AIMTrans *pTrans = (AIMTrans *)hTrans;

	AMAssert(pTransModule && pTrans);

	DPRINT("%s >>>>>> trans: %d, progress: %d\n", __FUNCTION__, pTrans->iTransId, iProgress);

	AMThreadMutexLock(&pTransModule->mtxLock);
	
	AMAssert(pTrans->bOccupied);
	
	if(!pTrans->bCanceled)
	{
		ntfProgress.iTaskId = pTrans->iTransId;
		ntfProgress.iProgress = iProgress;
	}
	else
	{
		set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpPtr);
		delete_List(&pTransModule->lstTrans, pTrans, sizeof(AIMTrans));
		iRetCode = eAIM_RESULT_CANCEL;
	}	
	AMThreadMutexUnlock(&pTransModule->mtxLock);

	if(!iRetCode)
		_AIMTrans_notify(pTransModule->pIM, OnNtfProgress, &ntfProgress);

	return iRetCode;
}
/*
 *	加锁移除pTrans，并通知结果
 */
AMInt32	AIMTransModule_result(AMHandle hTransModule, AMHandle hTrans, AMInt32 iResult)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	AIM_RSP_FILE rspFile;
	AMBool bCanceled = AMFALSE;
	AIMTrans *pTrans = (AIMTrans *)hTrans;

	AMAssert(pTransModule && pTrans);

	AMThreadMutexLock(&pTransModule->mtxLock);

	AMAssert(pTrans->bOccupied);
	
	bCanceled = pTrans->bCanceled;

	rspFile.iTaskId = pTrans->iTransId;
	rspFile.eResult = iResult;
	set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpPtr);
	delete_List(&pTransModule->lstTrans, pTrans, sizeof(AIMTrans));
	
	AMThreadMutexUnlock(&pTransModule->mtxLock);

	if(!bCanceled)
		_AIMTrans_notify(pTransModule->pIM, OnRspFile, &rspFile);

	return eAIM_RESULT_OK;
}

/*
 *	通知
 *	移除Id为iTransId的Trans
 */
AMInt32	AIMTransModule_resultId(AMHandle hTransModule, AMInt32 iTransId, AMInt32 iResult)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	AIM_RSP_FILE rspFile;
	AIMTrans *pTransTmp = AMNULL, *pTransFind = AMNULL;
	AMBool bCanceled = AMFALSE;
	AMInt32 iRetCode = eAIM_RESULT_OK;

	AMAssert(pTransModule);

	if(iRetCode = AIMTrans_createId(iTransId, &pTransTmp))
		return iRetCode;

	AMThreadMutexLock(&pTransModule->mtxLock);

	set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpId);
	pTransFind = find_List(&pTransModule->lstTrans, pTransTmp, sizeof(AIMTrans));
	AIMTrans_destroy(pTransTmp);

	if(pTransFind)
	{
		bCanceled = pTransFind->bCanceled;
		set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpPtr);
		delete_List(&pTransModule->lstTrans, pTransFind, sizeof(AIMTrans));
	}

	rspFile.iTaskId = pTransFind->iTransId;
	rspFile.eResult = iResult;

	AMThreadMutexUnlock(&pTransModule->mtxLock);

	if(!bCanceled)
		_AIMTrans_notify(pTransModule->pIM, OnRspFile, &rspFile);

	return iRetCode;
}
/*
 *	加锁查找对应trans，设置取消状态
 */
AMInt32	AIMTransModule_cancel(AMHandle hTransModule, AMInt32 iTransId)
{
	AIMTransModule *pTransModule = (AIMTransModule*)hTransModule;
	AIMTrans *pTransTmp = AMNULL, *pTransFind = AMNULL;
	AMBool bCanceled = AMFALSE;
	AMInt32 iRetCode = eAIM_RESULT_OK;

	AMAssert(pTransModule);

	if(iRetCode = AIMTrans_createId(iTransId, &pTransTmp))
		return iRetCode;

	AMThreadMutexLock(&pTransModule->mtxLock);

	set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpId);
	pTransFind = find_List(&pTransModule->lstTrans, pTransTmp, sizeof(AIMTrans));
	AIMTrans_destroy(pTransTmp);

	if(pTransFind)
		pTransFind->bCanceled = AMTRUE;

	AMThreadMutexUnlock(&pTransModule->mtxLock);

	return iRetCode;
}

typedef struct 
{
	AIMTrans *	pTrans;
	AMChar		szServerIp[32];
	AMUInt16	uiPort;
}AIMTransArg;

static AIMTransArg *AIMTransArg_create(const AIMTrans *pTrans, const AMChar *szIp, AMUInt16 uiPort)
{
	AIMTransArg *pArg = AMNULL;
	AMAssert(pTrans && szIp && uiPort);
	pArg = (AIMTransArg *)AMMalloc(sizeof(AIMTransArg));
	if(!pArg)
		return AMNULL;
	AMMemset(pArg, 0, sizeof(AIMTransArg));

	pArg->pTrans = pTrans;
	AMStrcpy(pArg->szServerIp, szIp);
	pArg->uiPort = uiPort;

	return pArg;	
}

static AMPVoid _AIMTransProc(AMPVoid procArg)
{
	AIMTransArg *pTransArg = (AIMTransArg *)procArg;
	AMAssert(pTransArg);
	return AIMTrans_work(pTransArg->pTrans, pTransArg->szServerIp, pTransArg->uiPort);
}

/*
 *	加锁查找对应trans，设置occupy标志，去锁，执行send/recv
 */
IMnetRetCode AIMTransModule_onGetAppAddr(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetAppAddr *pGetAppAddr = (ImEventGetAppAddr *)pEventContent;
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	AIMTransModule *pTransModule = AMNULL;
	AIMTrans *pTransTmp = AMNULL, *pTransFind = AMNULL;
	AMInt32 iSessionId = AMNULL;
	AMBool bOccupied = AMFALSE;

	AMAssert(pIM && pIM->pAcnt);
	pTransModule = (AIMTransModule *)pIM->hTransModule;
	AMAssert(pTransModule);

	DPRINT("%s >>>>>> retCode %d\n", __FUNCTION__, pGetAppAddr->retCode);

	iSessionId = AMAtoi(pGetAppAddr->szSessionId);
	DPRINT("%s >>>>>> iSessionId %d\n", __FUNCTION__, iSessionId);
	if(!iSessionId)
		return eIMnetSkip;

	if(pGetAppAddr->retCode)
	{
		AIMTransModule_resultId(pTransModule, iSessionId, pGetAppAddr->retCode);
		return eIMnetSkip;
	}

	if(AIMTrans_createId(iSessionId, &pTransTmp))
	{
		DPRINT("%s >>>>>> AIMTrans_createId Fail\n", __FUNCTION__);
		return eIMnetSkip;
	}	

	AMThreadMutexLock(&pTransModule->mtxLock);
	if(pTransModule->lstTrans.size)
	{
		set_compare(List, &pTransModule->lstTrans, AIMTrans_cmpId);
		pTransFind = find_List(&pTransModule->lstTrans, pTransTmp, sizeof(AIMTrans));
		if(pTransFind)
		{
			bOccupied = pTransFind->bOccupied;
			pTransFind->bOccupied = AMTRUE;
			if(!pTransFind->ulObjId)	//获取的时候，必须用二级协议里面的objId.
				pTransFind->ulObjId = pGetAppAddr->ulObjId;
		}
	}
	AMThreadMutexUnlock(&pTransModule->mtxLock);

	AIMTrans_destroy(pTransTmp);

	if(!pTransFind)
		AIMTransModule_resultId(pTransModule, iSessionId, eAIM_TRANS_TARGET);
	else if(!bOccupied)
	{
		AMThreadMutexLock(&pTransModule->mtxLock);
		if(!pTransModule->pTaskMgr)
			pTransModule->pTaskMgr = AMTaskMgrCreate(1);
		AMThreadMutexUnlock(&pTransModule->mtxLock);

		if(!pTransModule->pTaskMgr)
			AIMTransModule_resultId(pTransModule, iSessionId, eAIM_TRANS_MEMORY);
		else
		{
			AIMTransArg *pArg = AIMTransArg_create(pTransFind, pGetAppAddr->szServerIp, pGetAppAddr->uiServerPort);
			if(pArg)
				AMTaskMgrRun(pTransModule->pTaskMgr, _AIMTransProc, pArg, AMFree);
			else
				AIMTransModule_resultId(pTransModule, iSessionId, eAIM_TRANS_MEMORY);
		}
	}
	else
		AMAssert(0);

	return eIMnetSkip;
}

