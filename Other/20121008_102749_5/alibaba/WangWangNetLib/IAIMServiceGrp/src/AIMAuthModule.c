#include "AIMAuthModule.h"
#include "list.h"
#include "AMThreadMutex.h"
#include "AMString.h"
#include "IMnet.h"

#define _AIMAuth_notify(pIm, funcName,  ...)		\
	do \
	{\
	if((pIm)->callback && (pIm)->callback->funcName)\
	(pIm)->callback->funcName((pIm)->callback->pvArg, ## __VA_ARGS__);\
	} while (0)\

typedef	struct 
{
	IAIM		*	pIM;
	List			lstAuth;
	AMThreadMutex	mtxAuth;
	AMInt32			iLastId;
}AIMAuthModule;

enum 
{
	eAUTH_EMPTY,
	eAUTH_SESSION,
	eAUTH_CHECK,
}AIM_AUTH_STATUS;

typedef struct  
{
	AMInt32			iAuth;
	AMChar		*	szSession;
	AMInt32			iStatus;	//
	AMChar		*	szRawPacket;
	AMUInt32		uiPacketLen;
}AIMAuth;

/*
 *	外面传入szSession\szRawPacket， 赋值（不拷贝）给AIMAuth
 */
AIMAuth *_AIMAuth_create(const AMChar *szSession, const AMChar *szRawPacket, AMUInt32 uiLen)
{
	AIMAuth *pAuth = AMNULL;
	pAuth = (AIMAuth *)AMMalloc(sizeof(AIMAuth));
	if(!pAuth)
		return AMNULL;
	AMMemset(pAuth, 0, sizeof(AIMAuth));
	pAuth->szSession = szSession;
	pAuth->szRawPacket = szRawPacket;
	pAuth->uiPacketLen = uiLen;
	pAuth->iStatus = eAUTH_SESSION;

	return pAuth;
}

AMVoid	_AIMAuth_destroy(AMVoid *pvArg)
{
	AIMAuth *pAuth = (AIMAuth *)pvArg;
	AMAssert(pAuth);

	DPRINT("%s >>>>>> id: %d, session: %s, packetLen: %d\n", __FUNCTION__,
		pAuth->iAuth, pAuth->szSession, pAuth->uiPacketLen);

	if(pAuth->szSession)
		AMFree(pAuth->szSession);
	if(pAuth->szRawPacket)
		IMnetPackRelease(pAuth->szRawPacket);

	AMFree(pAuth);
}

AMInt32	_AIMAuth_cmpPtr(const AMVoid *pvArgA, const AIMAuth *pvArgB, AMUInt32 uiSize)
{
	AMAssert(pvArgA && pvArgB);
	return (AMInt32)pvArgA - (AMInt32)pvArgB;
}

AMInt32	_AIMAuth_cmpId(const AMVoid *pvArgA, const AIMAuth *pvArgB, AMUInt32 uiSize)
{
	AIMAuth *pAuthA = (AIMAuth *)pvArgA,
		*pAuthB = (AIMAuth *)pvArgB;
	AMAssert(pAuthA && pAuthB);

	return pAuthA->iAuth - pAuthB->iAuth;
}

AMInt32	_AIMAuth_cmpSession(const AMVoid *pvArgA, const AIMAuth *pvArgB, AMUInt32 uiSize)
{
	AIMAuth *pAuthA = (AIMAuth *)pvArgA,
		*pAuthB = (AIMAuth *)pvArgB;
	AMAssert(pAuthA && pAuthB);

	return AMStrcmp(pAuthA->szSession, pAuthB->szSession);
}

AMInt32	_AIMAuth_setSession(AIMAuth *pAuth, const AMChar *szSession)
{
	AMInt32 iLen = 0;
	AMAssert(pAuth && szSession);
	iLen = AMStrlen(szSession);
	AMAssert(iLen);
	
	if(pAuth->szSession)
	{
		AMFree(pAuth->szSession);
		pAuth->szSession = AMNULL;
	}
#if 1	//dynamic
	pAuth->szSession = szSession;
#else
	pAuth->szSession = (AMChar *)AMMalloc(iLen + 1);
	if(!pAuth->szSession)
		return eAIM_RESULT_MALLOC_ERROR;

	AMStrcpy(pAuth->szSession, szSession);
#endif
	pAuth->iStatus = eAUTH_SESSION;

	return eAIM_RESULT_OK;
}

AMInt32	AIMAuthModule_create(IAIM *pIM, AMHandle *phAuthModule)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)AMMalloc(sizeof(AIMAuthModule));
	
	if(!pAuthModule)
		return eAIM_RESULT_MALLOC_ERROR;

	AMMemset(pAuthModule, 0, sizeof(AIMAuthModule));
	
	if(AMThreadMutexCreate(&pAuthModule->mtxAuth))
	{
		AMFree(pAuthModule);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	pAuthModule->pIM = pIM;
	construct(List, &pAuthModule->lstAuth, sizeof(AIMAuth), FREEOBJ);
	set_dealloc(List, &pAuthModule->lstAuth, _AIMAuth_destroy);

	*phAuthModule = pAuthModule;

	return eAIM_RESULT_OK;
}

AMVoid	AIMAuthModule_destroy(AMHandle hAuthModule)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)hAuthModule;

	AMAssert(pAuthModule);

	AMThreadMutexDestroy(&pAuthModule->mtxAuth);

	destruct(List, &pAuthModule->lstAuth);
	
	AMFree(pAuthModule);
}

/*
 *	不加锁，根据id查找List。使用者考虑加锁的情况
 */
AIMAuth * _AIMAuthModule_findId(AIMAuthModule *pAuthModule, AMInt32 iAuthId)
{
	AIMAuth authTmp;
	AMAssert(pAuthModule && iAuthId);
	
	authTmp.iAuth = iAuthId;
	set_compare(List, &pAuthModule->lstAuth, _AIMAuth_cmpId);
	return find_List(&pAuthModule->lstAuth, &authTmp, sizeof(AIMAuth));
}

static _AIMAuthModule_findSession(AIMAuthModule *pAuthModule, const AMChar *szSession)
{
	AIMAuth authTmp;
	AMAssert(pAuthModule && szSession);

	authTmp.szSession = szSession;
	set_compare(List, &pAuthModule->lstAuth, _AIMAuth_cmpSession);
	return find_List(&pAuthModule->lstAuth, &authTmp, sizeof(AIMAuth));
}

AMInt32	AIMAuthModule_checkCode(AMHandle hAuthModule, AMInt32 iAuthId, const AMChar *szCode)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)hAuthModule;
	AIMAuth *pAuthFind = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK;
	AMAssert(pAuthModule && iAuthId && szCode);

	AMThreadMutexLock(&pAuthModule->mtxAuth);

	pAuthFind = _AIMAuthModule_findId(pAuthModule, iAuthId);

	if(pAuthFind && eAUTH_SESSION == pAuthFind->iStatus)
	{
		pAuthFind->iStatus = eAUTH_CHECK;
		IMnetCheckAuthCode(pAuthModule->pIM->pNetModel, pAuthFind->szSession, szCode);
	}
	else
		iRetCode = eAIM_RESULT_NOT_READY;

	AMThreadMutexUnlock(&pAuthModule->mtxAuth);

	return iRetCode;
}

AMInt32	AIMAuthModule_cancelAuth(AMHandle hAuthModule, AMInt32 iAuthId)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)hAuthModule;
	AIMAuth tmpAuth;
	AMInt32 iRetCode = eAIM_RESULT_OK;
	
	tmpAuth.iAuth = iAuthId;

	AMAssert(pAuthModule && iAuthId);

	AMThreadMutexLock(&pAuthModule->mtxAuth);

	set_compare(List, &pAuthModule->lstAuth, _AIMAuth_cmpId);
	delete_List(&pAuthModule->lstAuth, &tmpAuth, sizeof(AIMAuth));

	AMThreadMutexUnlock(&pAuthModule->mtxAuth);

	return iRetCode;
}

#define SESSION_PREFIX_AIM	"AIM"
#define LEN_SESSION		32
static AMChar	*_genSession()
{
	AMInt32	iGMTime = AMGetUpTime(AMNULL);
	AMChar *szSession = AMNULL;
	AMInt32 iUsed = 0, i = 0;

	szSession = (AMChar *)AMMalloc(LEN_SESSION + 1);
	if(!szSession)
		return AMNULL;
	AMMemset(szSession, 0, LEN_SESSION + 1);
	AMStrcpy(szSession, SESSION_PREFIX_AIM);
	iUsed = sizeof(SESSION_PREFIX_AIM) + _AIMItoa(iGMTime, szSession + sizeof(SESSION_PREFIX_AIM) - 1) -1;

	for(i=iUsed; i<LEN_SESSION; i++)
		szSession[i] = '0';

	return szSession;
}
#define URL_CHECK_IMAGE	"http://checkcode.alisoft.com/alisoft/checkcode?sessionID="
//#define URL_CHECK_IMAGE	"http://ccv2.china.alibaba.com/service/checkcode?sessionID="

static AMChar	*_getCheckImg(const AMChar *szSession, AMUInt32 *piLen)
{
	AMChar szUrl[sizeof(URL_CHECK_IMAGE) + sizeof(SESSION_PREFIX_AIM) + MAX_INT_NUMBER_LEN] = URL_CHECK_IMAGE;
	AMAssert(szSession && piLen);
	*piLen = 0;
	AMStrcat(szUrl + sizeof(URL_CHECK_IMAGE) - 1, szSession);
	return _UrlGetProc(szUrl, 2000, piLen);
}

static AMInt32	_AIMAuth_getAuthImg(AMChar **pszSession, AMChar **pszImg, AMInt32 *piLen)
{
	AMInt32 iRetCode = eAIM_RESULT_OK, iImgLen = 0;
	AMChar *szSession = AMNULL, *szImgData = AMNULL;
	AMAssert(pszSession && pszImg && piLen);

	*pszSession = *pszImg = *piLen = 0;
	
	szSession = _genSession();
	if(szSession)
	{
		szImgData = _getCheckImg(szSession, &iImgLen);
		if(!szImgData || !iImgLen)
		{
			AMFree(szSession);
			iRetCode = eAIM_RESULT_NET;
		}
	}
	else
		iRetCode = eAIM_RESULT_MALLOC_ERROR;
	
	if(eAIM_RESULT_OK == iRetCode)
	{
		*pszSession = szSession;
		*pszImg = szImgData;
		*piLen = iImgLen;
	}

	return iRetCode;
}

AMInt32	AIMAuthModule_updateCode(AMHandle hAuthModule, AMInt32 iAuthId)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)hAuthModule;
	AIMAuth tmpAuth, *pAuthFind = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK, iImgLen = 0;
	AMChar *szSessin = AMNULL, *szImgData = AMNULL;
	AIM_NTF_NEED_AUTH ntfNeedAuth;

	AMAssert(pAuthModule && iAuthId);

	iRetCode = _AIMAuth_getAuthImg(&szSessin, &szImgData, &iImgLen);

	DPRINT("%s >>>>>> session: %s, imgLen: %d\n", __FUNCTION__, szSessin, iImgLen);

	if(eAIM_RESULT_OK == iRetCode)
	{
		tmpAuth.iAuth = iAuthId;

		AMThreadMutexLock(&pAuthModule->mtxAuth);

		set_compare(List, &pAuthModule->lstAuth, _AIMAuth_cmpId);

		pAuthFind = _AIMAuthModule_findId(pAuthModule, iAuthId);

		if(pAuthFind)
			_AIMAuth_setSession(pAuthFind, szSessin);
		else
			iRetCode = eAIM_RESULT_NOT_READY;

		AMThreadMutexUnlock(&pAuthModule->mtxAuth);
	}

	AMMemset(&ntfNeedAuth, 0, sizeof(ntfNeedAuth));
	ntfNeedAuth.iAuthId = iAuthId;
	ntfNeedAuth.iRetCode = iRetCode;
	if(eAIM_RESULT_OK == iRetCode)
	{
		ntfNeedAuth.pvData = szImgData;
		ntfNeedAuth.iDataLen = iImgLen;
	}

	if(eAIM_RESULT_NOT_READY != iRetCode)
		_AIMAuth_notify(pAuthModule->pIM, OnNtfNeedAuth, &ntfNeedAuth);

	if(ntfNeedAuth.pvData)
		AMFree(ntfNeedAuth.pvData);

	return eAIM_RESULT_OK;
}

static AMInt32 _AIMAuthModule_addAuth(AMHandle hAuthModule, const AMChar *szSession, 
									  const AMChar *szRawPacket, AMInt32 iPacketLen, AMInt32 *piId)
{
	AIMAuthModule *pAuthModule = (AIMAuthModule *)hAuthModule;
	AIMAuth *pTmpAuth = AMNULL;
	
	AMAssert(piId);

	pTmpAuth = _AIMAuth_create(szSession, szRawPacket, iPacketLen);

	if(pTmpAuth)
	{
		AMThreadMutexLock(&pAuthModule->mtxAuth);
		*piId = pTmpAuth->iAuth = ++pAuthModule->iLastId;
		push_back_List(&pAuthModule->lstAuth, pTmpAuth, sizeof(AIMAuth), DYNAMIC);
		AMThreadMutexUnlock(&pAuthModule->mtxAuth);

		return eAIM_RESULT_OK;
	}
	
	return eAIM_RESULT_MALLOC_ERROR;
}

IMnetRetCode AIMAuthModule_onNtfNeedAuth(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImNtfNeedAuthCode *pNeedAuth = (ImNtfNeedAuthCode *)pEventContent;
	AMInt32 iRetCode = eAIM_RESULT_OK, iImgLen = 0, iAuthId = 0;
	AMChar *szSessin = AMNULL, *szImgData = AMNULL;
	AIM_NTF_NEED_AUTH ntfNeedAuth;


	DPRINT("%s >>>>>> Entering\n", __FUNCTION__);

	iRetCode = _AIMAuth_getAuthImg(&szSessin, &szImgData, &iImgLen);

	_AIMAuthModule_addAuth(pIM->hAuthModule, szSessin, pNeedAuth->szPacket, pNeedAuth->uiPacketLen, &iAuthId);
	
	AMMemset(&ntfNeedAuth, 0, sizeof(ntfNeedAuth));
	ntfNeedAuth.iAuthId = iAuthId;
	ntfNeedAuth.iRetCode = iRetCode;
	if(eAIM_RESULT_OK == iRetCode)
	{
		ntfNeedAuth.pvData = szImgData;
		ntfNeedAuth.iDataLen = iImgLen;
		pNeedAuth->szPacket = AMNULL;
	}

	_AIMAuth_notify(pIM, OnNtfNeedAuth, &ntfNeedAuth);

	if(ntfNeedAuth.pvData)
		AMFree(ntfNeedAuth.pvData);

	DPRINT("%s >>>>>> id: %d, code: %d, session: %s, imgLen: %d\n", __FUNCTION__, 
		ntfNeedAuth.iAuthId, ntfNeedAuth.iRetCode, szSessin, iImgLen);

	return eIMnetSkip;
}

IMnetRetCode AIMAuthModule_onRspCheckCode(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	AIMAuthModule *pAuthModule = AMNULL;
	ImRspCheckAuthCode *pCheckAuth = (ImRspCheckAuthCode *)pEventContent;
	AIMAuth *pAuthFind = AMNULL;
	AMChar *szImgData = AMNULL, *szSession = 0;
	AMInt32 iImgLen = 0, iRetCode = eAIM_RESULT_OK;
	AIM_RSP_CHECK_CODE rspCheckCode;

	AMAssert(pIM);
	pAuthModule = (AIMAuthModule *)pIM->hAuthModule;

	DPRINT("%s >>>>>> session: %s, retCode %d\n", __FUNCTION__, pCheckAuth->szSession, pCheckAuth->retCode);

	AMThreadMutexLock(&pAuthModule->mtxAuth);

	pAuthFind = _AIMAuthModule_findSession(pAuthModule, pCheckAuth->szSession);
	if(pAuthFind)
	{
		rspCheckCode.iAuthId = pAuthFind->iAuth;
		rspCheckCode.iRetCode = pCheckAuth->retCode;

		_AIMAuth_notify(pIM, OnRspCheckCode, &rspCheckCode);

		if(!pCheckAuth->retCode)
		{
			IMnetSendRawPacket(hIMnetHandle, pAuthFind->szRawPacket, pAuthFind->uiPacketLen);
			set_compare(List, &pAuthModule->lstAuth, _AIMAuth_cmpPtr);
			delete_List(&pAuthModule->lstAuth, pAuthFind, sizeof(AIMAuth));
		}
		else
		{
			AIM_NTF_NEED_AUTH ntfNeedAuth;

			ntfNeedAuth.iAuthId = pAuthFind->iAuth;

			ntfNeedAuth.iRetCode  = _AIMAuth_getAuthImg(&szSession, &ntfNeedAuth.pvData, &ntfNeedAuth.iDataLen);
			_AIMAuth_setSession(pAuthFind, szSession);
			
			_AIMAuth_notify(pIM, OnNtfNeedAuth, &ntfNeedAuth);
		}
	}
	else
	{
		iRetCode = eAIM_RESULT_NOT_READY;
	}

	AMThreadMutexUnlock(&pAuthModule->mtxAuth);

	return eIMnetSkip;
}


