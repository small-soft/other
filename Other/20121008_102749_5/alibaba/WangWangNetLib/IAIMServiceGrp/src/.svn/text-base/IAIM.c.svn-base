#include "AIM.h"
#include "AIMSignature.h"
#include "AIMUtil.h"
#include "IAIMCallback.h"
#include "AIMTransModule.h"
#include "AIMAuthModule.h"

#include "ghttp.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMStdlib.h"

void IAIM_ListenNet(IAIM *pIm);
void IAIM_UnlistenNet(IAIM *pIm);

static AMChar _szIpAddress[MAX_IP_LEN] = {0};
static AMUInt16	_uiIpPort = 0;

AIM_RESULT IAIM_Create( AMHandle *phIM )
{
	IAIM *pIm = AMNULL;

	AMAssert(AMNULL != phIM);

	if(AMNULL == (pIm = AMMalloc(sizeof(IAIM))))
	{
		return eAIM_RESULT_MALLOC_ERROR;
	}

	AMMemset(pIm, 0, sizeof(IAIM));

	pIm->pAcntModel = IAccountModel_Create();
	if(AMNULL == pIm->pAcntModel)
	{
		DPRINT("IAIM_Create...........AccountModel_Create Fail!\n");
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	if(eIMnetOK != IMnetMainCreate(&(pIm->pNetModel), pIm))
	{
		DPRINT("IAIM_Create...........IMnetMainCreate Fail!\n");
		IAccountModel_Destroy(pIm->pAcntModel);
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}
	DPRINT("IAIM_Create...........IMnetMainCreate After!\n");

	pIm->pSesModel = IASessionModel_Create(pIm); 
	if(AMNULL == pIm->pSesModel)
	{
		DPRINT("IAIM_Create...........IASessionModel_Create Fail!\n");
		IMnetMainDestory(pIm->pNetModel);
		IAccountModel_Destroy(pIm->pAcntModel);
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	pIm->pCntModel = IAContactModel_Create(pIm);
	if(AMNULL == pIm->pCntModel)
	{
		DPRINT("IAIM_Create...........IAContactModel_Create Fail!\n");
		IMnetMainDestory(pIm->pNetModel);
		IAccountModel_Destroy(pIm->pAcntModel);
		IASessionModel_Destroy(pIm->pSesModel);
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	if(eAIM_RESULT_OK != AIMTransModule_create(pIm, &pIm->hTransModule))
	{
		DPRINT("%s >>>>>> AIMTransModule_create Fail!\n", __FUNCTION__);
		IAContactModel_Destroy(pIm->pCntModel);
		IMnetMainDestory(pIm->pNetModel);
		IAccountModel_Destroy(pIm->pAcntModel);
		IASessionModel_Destroy(pIm->pSesModel);
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	if(eAIM_RESULT_OK != AIMAuthModule_create(pIm, &pIm->hAuthModule))
	{
		DPRINT("%s >>>>>> AIMAuthModule_create Fail!\n", __FUNCTION__);
		IAContactModel_Destroy(pIm->pCntModel);
		IMnetMainDestory(pIm->pNetModel);
		IAccountModel_Destroy(pIm->pAcntModel);
		IASessionModel_Destroy(pIm->pSesModel);
		AIMTransModule_destroy(pIm->hTransModule);
		AMFree(pIm);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	*phIM = pIm;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_Destroy( AMHandle hIM )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM);
	AMAssert(AMNULL != pIM->pNetModel && AMNULL != pIM->pCntModel && AMNULL != pIM->pSesModel && AMNULL != pIM->pAcntModel);

	IAIM_Logout(pIM);

	AIMAuthModule_destroy(pIM->hAuthModule);
	pIM->hAuthModule = AMNULL;

	AIMTransModule_destroy(pIM->hTransModule);
	pIM->hTransModule = AMNULL;

	IAContactModel_Destroy(pIM->pCntModel);
	pIM->pCntModel = AMNULL;

	IASessionModel_Destroy(pIM->pSesModel);
	pIM->pSesModel = AMNULL;

 	IAccountModel_Destroy(pIM->pAcntModel);
 	pIM->pAcntModel = AMNULL;

	IMnetMainDestory(pIM->pNetModel);
	pIM->pNetModel = AMNULL;

	if(pIM->pAcnt)
	{
		IAccount_Destroy(pIM->pAcnt);
		pIM->pAcnt = AMNULL;
	}

	if (pIM->szRemarkMsg) {
		AMFree(pIM->szRemarkMsg);
		pIM->szRemarkMsg = AMNULL;
	}

	if (pIM->szWebSession)
		AMFree(pIM->szWebSession);

	AMFree(pIM);

	return eAIM_RESULT_OK;
}

#define		XML_REMARK_HEAD		"<p>"
#define		XML_REMARK_TAIL		"</p>"
static AMVoid _AIM_setRemarkMsg (IAIM *pIM, const AMChar *szRemarkMsg) {
	AMAssert(pIM);
	if (pIM->szRemarkMsg) {
		AMFree(pIM->szRemarkMsg);
		pIM->szRemarkMsg = AMNULL;
	}

	if (szRemarkMsg && AMStrlen(szRemarkMsg)) {
		AMChar *szHead = AMStrstr(szRemarkMsg, XML_REMARK_HEAD);
		if (szHead) {
			AMChar *szTail = AMStrstr(szHead+=sizeof(XML_REMARK_HEAD)-1, XML_REMARK_TAIL);
			if (szTail) {
				AMInt32 iMsgLen = szTail - szHead;
				pIM->szRemarkMsg = (AMChar *)AMMalloc(iMsgLen + 1);
				if(pIM->szRemarkMsg) {
					AMMemset(pIM->szRemarkMsg, 0, iMsgLen + 1);
					AMMemcpy(pIM->szRemarkMsg, szHead, iMsgLen);
				}
			}
		}
	}
}

static AMVoid _AIM_setWebSession(IAIM *pIM, const AMChar *szWebSession, AMInt32 iLen) 
{
	AMAssert( pIM );
	if(pIM->szWebSession)
	{
		AMFree(pIM->szWebSession);
		pIM->szWebSession = 0;
	}
	pIM->szWebSession = (AMChar *)AMMalloc(iLen+1);
	AMAssert(pIM->szWebSession);
	AMMemcpy(pIM->szWebSession, szWebSession, iLen);
	pIM->szWebSession[iLen] = 0;
}

AIM_RESULT IAIM_RegisterListener( AMHandle hIM, const AIM_CALLBACK *listener )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != listener);

	pIM->callback = listener;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_UnregisterListener( AMHandle hIM, const AIM_CALLBACK *listener )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != listener);

	if(listener == pIM->callback)
	{
		pIM->callback = NULL;
		return eAIM_RESULT_OK;
	}
	else if(NULL == pIM->callback)
		return eAIM_RESULT_NOT_READY;
	else
		return eAIM_RESULT_PARAM_ERROR;
}

AIM_RESULT IAIM_GetContactModel( AMHandle hIM, AMHandle *phContactModel )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != phContactModel);

	*phContactModel = pIM->pCntModel;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetSessionModel( AMHandle hIM, AMHandle *phSessionModel )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != phSessionModel);

	*phSessionModel = pIM->pSesModel;

	return eAIM_RESULT_OK;
}

#define IAIM_Callback(pIm, funcName,  ...)		\
	do \
	{\
		if(pIm->callback && pIm->callback->funcName)\
			pIm->callback->funcName(pIm->callback->pvArg, ## __VA_ARGS__);\
	} while (0)

AIM_RESULT IAIM_GetAccounts( AMHandle hIM, AMHandle **pphAcntArray, AMInt32 *piCount )
{
	IAIM *pIM = (IAIM *)hIM;
	List *pList = AMNULL;
	ListIter *pIter = AMNULL;
	AMInt32 i = 0;

	AMAssert( pIM && pIM->pAcntModel );
	AMAssert( pphAcntArray && piCount );

	pList = IAccountModel_GetAccountList(pIM->pAcntModel);
	
	*piCount = pList->size;
	if(*piCount <= 0)
		return eAIM_RESULT_OK;

	*pphAcntArray = (AMHandle*)AMMalloc(sizeof(AMHandle) * (*piCount));
	if(!(*pphAcntArray))
		return eAIM_RESULT_MALLOC_ERROR;

	pIter = create(ListIter, pList);
	head(ListIter, pIter);
	do 
	{
		(*pphAcntArray)[i++] = (AMHandle) retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_ReleaseAccounts( AMHandle hIM, AMHandle *phAcntArray, AMInt32 iArraySize)
{
	IAIM *pIM = (IAIM *)hIM;

	if(iArraySize)
		AMFree(phAcntArray);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_RemoveAccount( AMHandle hIM, const AMChar *szAccountID, AMBool bDelete )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szAccountID);

	IAccountModel_RemoveAccount(pIM->pAcntModel, szAccountID, bDelete);

	return eAIM_RESULT_OK;
}

AIM_RESULT AIM_GetIMStatus( AMHandle hIM, AMUChar *pucStatus )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != pucStatus);

	*pucStatus = pIM->ucImStatus;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetCurrentAccount( AMHandle hIM, AMHandle *phAccount )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != phAccount);

	*phAccount = pIM->pAcnt;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetTopGroups( AMHandle hIM, AMHandle **pphGroupArray, AMInt32 *piSize)
{
	IAIM *pIM = (IAIM *)hIM;
	ListIter *pIter = AMNULL;
	AMInt32 i = 0;
	AMAssert( pIM && AMNULL != pphGroupArray && AMNULL != piSize );

	*piSize = pIM->pCntModel->lTopGrp.size;

	AMAssert(*piSize);

	*pphGroupArray = (AMHandle *)AMMalloc(sizeof(AMHandle) * (*piSize));
	if(!(*pphGroupArray))
		return eAIM_RESULT_MALLOC_ERROR;

	pIter = create(ListIter, &pIM->pCntModel->lTopGrp);

	head(ListIter, pIter);
	do 
	{
		(*pphGroupArray)[i++] = (AMHandle) retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_ReleaseTopGroups( AMHandle hIM, AMHandle *phGroupArray, AMInt32 iArraySize )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM );

	if(iArraySize>0)
		AMFree(phGroupArray);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetGroupByID(AMHandle hIM, AMInt64 i64GrpID, AMHandle *phGroup)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM );

	return IAIMContactModel_GetGroupByID(pIM->pCntModel, i64GrpID, phGroup);
}

AIM_RESULT IAIM_GetContactByID(AMHandle hIM, const AMChar *szCntID, AMHandle *phContact)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM );

	return IAIMContactModel_GetContactByID(pIM->pCntModel, szCntID, phContact);
}

AIM_RESULT IAIM_RemoveRecent(AMHandle hIM, const AMChar *szContactID)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM );

	return IAIMContactModel_RemoveRecent(pIM->pCntModel, szContactID);
}

AIM_RESULT IAIM_RemoveStranger(AMHandle hIM, const AMChar *szContactID)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM );

	return IAIMContactModel_RemoveStranger(pIM->pCntModel, szContactID);
}

AIM_RESULT IAIM_OpenSession(AMHandle hIM, const AMChar *szContactID, AMHandle *phSession)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert( pIM && pIM->pSesModel );

	return IAIMSessionModel_OpenSession(pIM->pSesModel, szContactID, phSession);
}

AIM_RESULT IAIM_CloseSession(AMHandle hIM, AMHandle hSession)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert( pIM && pIM->pSesModel );

	return IAIMSessionModel_CloseSession(pIM->pSesModel, hSession);
}

AIM_RESULT AIM_GetCurrentToken(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(NULL != pIM && NULL != pszToken && NULL != puiLen);

	if(NULL != pIM->pAcnt)
	{
		*pszToken = pIM->pAcnt->szToken;
		*puiLen = pIM->pAcnt->uiTokenLen;
	}
	else
	{
		*pszToken = NULL;
		*puiLen = 0;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT AIM_GetCurrentWebMD5(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(NULL != pIM && NULL != pszToken && NULL != puiLen);

	if(NULL != pIM->pAcnt)
	{
		*pszToken = pIM->pAcnt->szWebMD5;
		*puiLen = pIM->pAcnt->uiWebMD5Len;
	}
	else
	{
		*pszToken = NULL;
		*puiLen = 0;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_Login( AMHandle hIM, const AMChar *szID, const AMChar *szPwd, AMBool bNotPlain, 
					  AIM_ACCOUNT_SETTING setting, AMBool bTest)
{
	return IAIM_LoginEx(hIM, szID, szPwd, bNotPlain, setting, bTest, AMNULL);
}

AIM_RESULT IAIM_LoginEx( AMHandle hIM, const AMChar *szID, const AMChar *szPwd, AMBool bNotPlain, 
					  AIM_ACCOUNT_SETTING setting, AMBool bTest, const AMChar *latestOMVersion)
{
	IAIM *pIM = (IAIM *)hIM;
#ifdef	APM_MACRO_GET_OPERATION_MSG
	AIM_PRIVATE_EVENT getOM;
#endif
	AIMAccount *pFindAcnt = AMNULL;
	static AMChar s_omVersion[128];

	AMAssert(AMNULL != pIM && AMNULL != szID);

	IAIM_Logout(pIM);	//ForcDisc. 这时传的参数是什么？会不会被释放掉？注意！

	AMAssert(eIM_STATUS_IDEL == pIM->ucImStatus || eIM_STATUS_FORCEDISC == pIM->ucImStatus 
				|| eIM_STATUS_LOGOUTED == pIM->ucImStatus || eIM_STATUS_NETFAIL == pIM->ucImStatus
				|| eIM_STATUS_LOGINFAIL == pIM->ucImStatus);

	if(AMNULL != pIM->pAcnt)
	{
		IAccount_Destroy(pIM->pAcnt);
		pIM->pAcnt = AMNULL;
	}

	if(AMNULL == (pFindAcnt = IAccountModel_findHistoryAcnt(pIM->pAcntModel, szID)))
	{
		pIM->pAcnt = IAccount_Create();
		IAccount_SetID(pIM->pAcnt, szID, AMStrlen(szID));
	}
	else
	{
		pIM->pAcnt = IAccount_dup(pFindAcnt);
	}

	if(0 == bNotPlain)
	{
		IAccount_SetToken(pIM->pAcnt, szPwd, AMStrlen(szPwd));
	}
	else if(1 == bNotPlain)
	{
		if(AMNULL != szPwd)
		{
			IAccount_SetToken(pIM->pAcnt, szPwd, AMStrlen(szPwd));
			bNotPlain = 3;
		}
		else
		{
			bNotPlain = (pIM->pAcnt->uiFlag & 0x10 ) ? 3: 1;// 恢复的Token的类型，3为UIDToken，1为PWToken
		}
	}

	pIM->pAcnt->uiFlag &= ~7;	
	pIM->pAcnt->uiFlag |= AMAccount_CaculateFlag(setting.bSavePwd, setting.bMute, setting.bViberate);
	pIM->pAcnt->ePresence = setting.eDefaultPresence;
	pIM->ucTokenFlag = bNotPlain;

	pIM->bTest = bTest;

	IAIM_ListenNet(pIM);

#ifdef	APM_MACRO_GET_OPERATION_MSG
	// New: get operation message
	getOM.iEventType = eAIM_PRIVATE_EVENT_OPERATION_MESSAGE;
	if(latestOMVersion != AMNULL) {
		memset(s_omVersion, 0, sizeof(s_omVersion));
		AMStrcpy(s_omVersion, latestOMVersion);
		getOM.iParam1 = (AMInt32) s_omVersion;
	} else {
		getOM.iParam1 = 0;
	}
	getOM.i64Param2 = (AMInt64) bTest;
	IMnetSendMsg2Callback(pIM->pNetModel, IM_EVENT_PRIVATE, &getOM, sizeof(getOM), AMNULL);
#else
	/**
	*    这里要判断是否有IP和PORT，如果没有，则做Allot；有，则做NetConnectionOpen
	*/
	if(AMFALSE == bTest && 0 == AMStrlen(IP_ADDRESS_REAL))
	{
		AIM_PRIVATE_EVENT allot;

		DPRINT("IAIM_LoginID................Before Allot\n");

		allot.iEventType = eAIM_PRIVATE_EVENT_ALLOT;
		IMnetSendMsg2Callback(pIM->pNetModel, IM_EVENT_PRIVATE, &allot, sizeof(allot), AMNULL);
		IAIM_TransStatus(pIM, eAIM_STATUS_ALLOTED);
	}
	else
	{
		DPRINT("IAIM_LoginID................Before IMnetNetworkConfig...\n");

		IAIM_TransStatus(pIM, eIM_STATUS_NETCONFIGED);

		if(AMTRUE == bTest)
			IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
		else
			IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);
	}
#endif // APM_MACRO_GET_OPERATION_MSG
	return eAIM_RESULT_OK;
}

#define OPERATION_MESSAGE_URL "http://wap.taobao.com/rest/api2.do"
#if defined (ANDROID_BUILD) || defined (IOS_BUILD)
//旺旺Allot地址
#define ALLOT_URL "http://newallot.im.alisoft.com/imlogingw/mobilelogin"
//云聊Allot地址
#else
#define ALLOT_URL "http://newallot.im.alisoft.com/imlogingw/tcp60login"
#endif

static AMChar* _GenerateDestUrl(const AMChar* baseUrl, const UrlParam* param, AMUInt32 size)
{
	AMUInt32 i,len = 0;
	AMChar* p = AMNULL;

	if(baseUrl == AMNULL || param == AMNULL || size == 0){
		return baseUrl;
	}

	len = AMStrlen(baseUrl) + 1; // "?"

	for(i=0; i<size; i++){
		len += (AMUInt32)AMStrlen(param[i].key);
		len += (AMUInt32)AMStrlen(param[i].value);
		len += 2; //key=value&
	}

	p = (AMChar*)AMMalloc(len+1);
	AMAssert(p != AMNULL);
	if(p == AMNULL){
		return AMNULL;
	}
	AMMemset(p, 0, len+1);

	AMStrcpy(p, baseUrl);

	AMStrcat(p, "?");

	for(i=0; i<size; i++){
		if(param[i].value == AMNULL) continue;
		AMStrcat(p, param[i].key);
		AMStrcat(p, "=");
		AMStrcat(p, param[i].value);
		AMStrcat(p, "&");
	}

	p[len-1] = 0;
	return p;
}

static AMChar* s_ttid = AMNULL;

void IAIM_SetTtid(const AMChar* ttid)
{
	if(AMNULL == s_ttid && ttid != AMNULL)
	{
		int length = AMStrlen(ttid);
		s_ttid = (AMChar*)AMMalloc(length + 1);
		AMAssert(AMNULL != s_ttid);
		AMMemset(s_ttid, 0, length + 1);
		strcpy(s_ttid, ttid);
		DPRINT("IAIM_SetTtid: s_ttid=%s", s_ttid);
	}
}

static AMChar* _IAIM_DoGetOperationMessage(const AMChar* version, const AMChar* loginId, const AMChar* latestOMVersion){
	UrlParam param[3];
	AMChar *url = AMNULL;
	AMChar *response = AMNULL;
	static AMChar dataParam[512];

	if(AMNULL == s_ttid)
	{
		return AMNULL;
	}

	if(version == AMNULL){
		return AMNULL;
	}

	if(loginId == AMNULL){
		return AMNULL;
	}

	AMMemset(dataParam, 0, sizeof(dataParam));
	if(AMNULL == latestOMVersion)
	{
		AMSprintf(dataParam, "%%7B%%22ttid%%22%%3A%%22%s%%22%%7D", s_ttid);
	}
	else
	{
		AMSprintf(dataParam, "%%7B%%22ttid%%22%%3A%%22%s%%22,%%22msgv%%22%%3A%%22%s%%22%%7D", s_ttid, latestOMVersion);
	}

	param[0].key = "api";
	param[1].key = "v";
	param[2].key = "data";

	param[0].value = "com.taobao.client.pushmessage";
	param[1].value = "*";
	param[2].value = dataParam;

	url = _GenerateDestUrl(OPERATION_MESSAGE_URL, param, sizeof(param)/sizeof(UrlParam));

	DPRINT("_IAIM_DoGetOperationMessage: url: %s\n", url);

	if(url == AMNULL){
		return AMNULL;
	}

	response = _UrlGet(url, 2000);

	AMFree(url);

	return response;
}

AMChar* s_operaionMessage = AMNULL;

AMChar* IAIM_GetOperationMessage(void)
{
	DPRINT("IAIM_GetOperationMessage: s_operaionMessage=%s\n", s_operaionMessage);
	return s_operaionMessage;
}

AMVoid IAIM_FreeOperationMessage(void)
{
	if(s_operaionMessage != AMNULL)
	{
		AMFree(s_operaionMessage);
		s_operaionMessage = AMNULL;
	}
}

IMnetRetCode IAIM_OnGetOperationMessageRequest(IAIM *pIM, AIM_PRIVATE_EVENT *pEvent)
{
	AMChar *szOMContent = AMNULL, *szOMVersion = AMNULL;
	AMBool bTest = (AMBool) pEvent->i64Param2;

	AMAssert(pIM);

	DPRINT("IAIM_OnGetOperationMessageRequest............................Entering!\n");

	IAIM_FreeOperationMessage();

#ifdef _WIN32
	AMSocketInit();//只有在windows中才需要! 为什么...?
#endif // _WIN32
	s_operaionMessage = _IAIM_DoGetOperationMessage( IM_PROTOCOL_VERSION, pIM->pAcnt->szID, (const AMChar* ) pEvent->iParam1);

	DPRINT("IAIM_OnGetOperationMessageRequest.....................%s\n", s_operaionMessage);

	if(s_operaionMessage)
	{
		DPRINT("IAIM_OnGetOperationMessageRequest...........................OK!\n");
	}
	else
	{
		// failed to get operation message
		DPRINT("IAIM_OnGetOperationMessageRequest.......................failed!\n");
	}

	/**
	*    这里要判断是否有IP和PORT，如果没有，则做Allot；有，则做NetConnectionOpen
	*/
	if(AMFALSE == bTest && 0 == AMStrlen(IP_ADDRESS_REAL))
	{
		AIM_PRIVATE_EVENT allot;

		DPRINT("IAIM_LoginID................Before Allot\n");
		
		allot.iEventType = eAIM_PRIVATE_EVENT_ALLOT;
		IMnetSendMsg2Callback(pIM->pNetModel, IM_EVENT_PRIVATE, &allot, sizeof(allot), AMNULL);
		IAIM_TransStatus(pIM, eAIM_STATUS_ALLOTED);
	}
	else
	{
		DPRINT("IAIM_LoginID................Before IMnetNetworkConfig...\n");

		IAIM_TransStatus(pIM, eIM_STATUS_NETCONFIGED);

		if(AMTRUE == bTest)
			IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
		else
			IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);
	}

	return eIMnetSkip;
}

static AMChar* _IAIM_DoAllot(const AMChar* version, const AMChar* loginId){
	UrlParam param[2];
	AMChar *url = AMNULL;
	AMChar *response = AMNULL;

	if(version == AMNULL){
		return AMNULL;
	}

	if(loginId == AMNULL){
		loginId = "test";
	}

	param[0].key = "ver";
	param[1].key = "loginId";

	param[0].value = version;
	param[1].value = loginId;

	url = _GenerateDestUrl(ALLOT_URL, param, sizeof(param)/sizeof(UrlParam));

	DPRINT("_IAIM_DoAllot..............................url: %s\n", url);

	if(url == AMNULL){
		return AMNULL;
	}

	response = _UrlGet(url, 2000);

	AMFree(url);

	return response;
}

IMnetRetCode IAIM_OnAllotRequest(IAIM *pIM, AIM_PRIVATE_EVENT *pEvent)
{
	AMChar	*pAllotResult = AMNULL, *szPort = AMNULL;
	AIM_NTF_NET_STATUS ntfNetStatus;
	
	AMAssert(pIM);
	
	DPRINT("IAIM_OnAllotRequest............................Entering!\n");

	pAllotResult = _IAIM_DoAllot( IM_PROTOCOL_VERSION, pIM->pAcnt->szID);

	DPRINT("IAIM_OnAllotRequest..........................%s\n", pAllotResult);

	if(pAllotResult && (szPort = AMStrstr(pAllotResult, ":")) && szPort-pAllotResult < MAX_IP_LEN && szPort-pAllotResult > 6)
	{
		_uiIpPort = (AMUInt16)AMAtoi64(szPort+1);
		
		AMMemcpy(_szIpAddress, pAllotResult, szPort-pAllotResult);

		IAIM_TransStatus(pIM, eIM_STATUS_NETCONFIGED);

		IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);

		DPRINT("IAIM_OnAllotRequest....................................OK!\n");
	}
	else
	{
		//110.75.161.60:16000,110.75.161.63:16000
		IAIM_TransStatus(pIM, eIM_STATUS_NETFAIL);

		AMMemset(_szIpAddress, 0, MAX_IP_LEN);

		IAccount_Destroy(pIM->pAcnt);
		pIM->pAcnt = AMNULL;

		ntfNetStatus.eStatus = eNET_PUZZLE;

		IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);

		DPRINT("IAIM_OnAllotRequest..........................................Not Ready2!\n");
	}

	if(pAllotResult)
		AMFree(pAllotResult);

	return eIMnetSkip;
}

IMnetRetCode IAIM_OnPrivateEvent(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMChar	*pAllotResult = AMNULL, *szPort = AMNULL;
	AIM_PRIVATE_EVENT	*pEvent = (AIM_PRIVATE_EVENT*)pEventContent;

	AMAssert(pIM);

	if(eAIM_PRIVATE_EVENT_ALLOT == pEvent->iEventType)
		return IAIM_OnAllotRequest(pIM, pEvent);
	else if(eAIM_PRIVATE_EVENT_OPERATION_MESSAGE == pEvent->iEventType)
		return IAIM_OnGetOperationMessageRequest(pIM, pEvent);
	else if(eAIM_PRIVATE_EVENT_CAPCHA == pEvent->iEventType)
	{
		AIMAuthModule_updateCode(pIM->hAuthModule, pEvent->iParam1);
		return eIMnetSkip;
	}
	else
		return eIMnetOK;
}

#if 1
static AMVoid _FreeAddCntEvnt(EventContent *content)
{
	ImRspAddContact	*pEvnt = (ImRspAddContact*)content;
	if(!pEvnt->bContactInfoUsed)
		AMFree(pEvnt->contactInfo.contactID);
}
#endif // TARGET_VMKIT

AIM_RESULT IAIM_AddContact( AMHandle hIM, const AMChar *szContactID )
{
	IAIM *pIM = (IAIM *)hIM;
	IAContact	*pTmpCnt = AMNULL, *pCntFind = AMNULL;

	AMAssert(AMNULL != pIM && AMNULL != szContactID);	

	DPRINT("IAIM_AddContact..........................................ID: %s!\n", szContactID);

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szContactID, AMStrlen(szContactID));

	pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtRevBlk, pTmpCnt, sizeof(IAContact));//反向黑名单不加？
	if (AMNULL != pCntFind)
	{
#if 1	//always fail when adding a revBlack.
		ImRspAddContact	evnt;
		AMMemset(&evnt, 0, sizeof(evnt));
		evnt.contactInfo.contactIDLen = AMStrlen(szContactID);
		evnt.contactInfo.contactID = _StrDupLen( szContactID, evnt.contactInfo.contactIDLen );
		evnt.retCode = 255;
		IMnetSendMsg2Callback(pIM->pNetModel, 0x01010050, &evnt, sizeof(evnt), _FreeAddCntEvnt);//0x01010050 IM_RSP_ADDCONTACT
#endif // TARGET_VMKIT

		IAContact_Destroy(pTmpCnt);
		return eAIM_RESULT_FAIL;
	}
	
	pCntFind = (IAContact *)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(pCntFind)
	{
		AMBool bBlack = AMFALSE;
		IAIMContact_IsBlack(pCntFind, &bBlack);
		if(bBlack)
		{
			IMnetDeleteBlack(pIM->pNetModel, pCntFind->szID);
			IAContact_Destroy(pTmpCnt);
			return eAIM_RESULT_OK;
		}
	}

	if(pCntFind && pCntFind->szBindUID)
	{
		DPRINT("IAIM_AddContact..........................................Bind ID: %s!\n", pCntFind->szBindUID);
		IMnetPutBindInfo(pIM->pNetModel, pCntFind->szBindUID, AMStrlen(pCntFind->szBindUID));
	}
	else
	{
		IAContact_AutoSetBindUid(pIM, pTmpCnt);
		IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
	}

	IAContact_Destroy(pTmpCnt);

	IMnetAddContact(pIM->pNetModel, (AMChar *)szContactID, 0, 0, 0, AMNULL);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_RemoveContact( AMHandle hIM, const AMChar *szContactID )
{
	IAIM *pIM = (IAIM *)hIM;
	//IAContact *pCnt = AMNULL;
	IAContact	*pCntFind = AMNULL, *pTmpCnt = AMNULL;
	ContactList contactList;

	AMAssert(AMNULL != pIM && AMNULL != szContactID);

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szContactID, AMStrlen(szContactID));
	pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(AMNULL == pCntFind)
		pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	if(AMNULL == pCntFind)
		pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact));
	if(pCntFind && pCntFind->szBindUID)
	{
		IMnetPutBindInfo(pIM->pNetModel, pCntFind->szBindUID, AMStrlen(pCntFind->szBindUID));
	}
	else
	{
		IAContact_AutoSetBindUid(pIM, pTmpCnt);
		IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
	}
	IAContact_Destroy(pTmpCnt);


	contactList.pNext = AMNULL;
	contactList.userID = (AMChar *)szContactID;				//IMnetDeleteContact内部会做数据拷贝的工作
	contactList.userIDLen = AMStrlen(szContactID);
	IMnetDeleteContact(pIM->pNetModel, &contactList);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_AddBlack( AMHandle hIM, const AMChar *szContactID )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szContactID);

	IMnetAddBlack(pIM->pNetModel, (AMChar *)szContactID);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetPeerInfo(AMHandle hIM, const AMChar *szContact)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szContact);

	IMnetGetPeerInfo(pIM->pNetModel, (AMChar *)szContact);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetVerify(AMHandle hIM, const AMChar *szContact)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szContact);

	IMnetGetPeerVerifyConfig(pIM->pNetModel, (AMChar *)szContact, 0);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_GetProfile(AMHandle hIM, const AMChar *szContact)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szContact);

	IMnetGetUserUDBProfile(pIM->pNetModel, (AMChar *)szContact);
	IMnetGetDegree(pIM->pNetModel, (AMChar *)szContact);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_SearchUser(AMHandle hIM, const AMChar *szKeyWord)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szKeyWord);

	DPRINT("IAIM_SearchUser");
	IMnetSearchUser(pIM->pNetModel, (AMChar *)szKeyWord);

	return eAIM_RESULT_OK;
}



AIM_RESULT IAIM_GetDegree( AMHandle hIM, const AMChar *szContact )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != szContact);

	IMnetGetDegree(pIM->pNetModel, (AMChar *)szContact);

	return eAIM_RESULT_OK;
}

static void _AIM_FreeGetPortraitEvent(EventContent *pContent)
{
	AIM_PRIVATE_EVENT	*pRequest = (AIM_PRIVATE_EVENT*)pContent;
	if(pRequest->szParam3)
	{
		AMFree(pRequest->szParam3);
		pRequest->szParam3 = AMNULL;
	}
}


AIM_RESULT	IAIM_GetPortrait( AMHandle hIM, const AMChar *szContact)
{
	IAIM *pIM = (IAIM *)hIM;
	AIM_PRIVATE_EVENT	request;
	AMAssert(AMNULL != pIM && AMNULL != szContact);

	AMMemset(&request, 0, sizeof(request));

	request.szParam3 = (AMChar*) AMMalloc(AMStrlen(szContact) + 1);

	if(request.szParam3)
	{
		AMStrcpy(request.szParam3, szContact);		
		request.iEventType = eAIM_PRIVATE_EVENT_PORTRAIT;
		IMnetSendMsg2CallbackProc(pIM->pNetModel, IM_EVENT_PRIVATE, &request, sizeof(request), _AIM_FreeGetPortraitEvent, AMTRUE);
		return eAIM_RESULT_OK;
	}
	else
		return eAIM_RESULT_MALLOC_ERROR;
}

AIM_RESULT IAIM_GetSignature(AMHandle hIM, const AMChar *szContactIds, AMUInt32 iCount)
{
	IAIM *pIM = (IAIM *)hIM;
	AIM_PRIVATE_EVENT reqGetSignature;
	AMInt32	iLen = 0;
	AMAssert(AMNULL != pIM && AMNULL != szContactIds);
	AMAssert(AMNULL != pIM->pAcnt);

	DPRINT("IAIM_GetUserSignature...............%s\n", szContactIds);

	AMMemset(&reqGetSignature, 0, sizeof(reqGetSignature));
	reqGetSignature.iEventType = eAIM_PRIVATE_EVENT_SIGNATURE;
	iLen = AMStrlen(szContactIds);
	reqGetSignature.szParam3 = (AMChar *)AMMalloc(iLen + 1);
	AMMemcpy(reqGetSignature.szParam3, szContactIds,iLen + 1);
	reqGetSignature.iParam1 = iCount;

	IMnetSendMsg2CallbackProc(pIM->pNetModel, IM_EVENT_PRIVATE, &reqGetSignature, sizeof(reqGetSignature), _AIM_FreeGetPortraitEvent, AMTRUE);
	return eAIM_RESULT_OK;
}


AIM_RESULT IAIM_SubscribePresence( AMHandle hIM, const AMChar **pszContactIds, AMUInt32 uiCount)
{
	IAIM *pIM = (IAIM *)hIM;
	ContactList	*pContactList = AMNULL;
	AMUInt32 i = 0;
	AMAssert(AMNULL != pIM && AMNULL != pszContactIds);
	AMAssert(AMNULL != pIM->pAcnt);

	if(!uiCount)
		return eAIM_RESULT_OK;

	pContactList = (ContactList *)AMMalloc(sizeof(ContactList) * uiCount);
	if(!pContactList)
	{
		return eAIM_RESULT_MALLOC_ERROR;
	}
	AMMemset(pContactList, 0, sizeof(ContactList)*uiCount);
	
	for(i=0; i<uiCount; i++)
	{
		AMAssert(pszContactIds[i]);
		pContactList[i].userID = pszContactIds[i];
		pContactList[i].userIDLen = AMStrlen(pszContactIds[i]);
		pContactList[i].pNext = &pContactList[i+1];
	}

	pContactList[uiCount-1].pNext = AMNULL;

	IMnetSubscribeContactInfo(pIM->pNetModel, pContactList, AMTRUE);

	AMFree(pContactList);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_RemoveBlack( AMHandle hIM, const AMChar *szBlackID )
{
	IAIM *pIM = (IAIM *)hIM;
	IAContact *pCnt = AMNULL;
	AMAssert(0 != pIM && 0 != szBlackID);
	
	IAIM_GetContactByID(hIM, szBlackID, &pCnt);
	
	if(pCnt && AIMContact_isFriend(pIM->pCntModel, pCnt))
		return IAIM_RemoveContact(hIM, szBlackID);
	else
	{
		if(pCnt)
			IMnetPutBindInfo(pIM->pNetModel, pCnt->szBindUID, pCnt->szBindUID ? AMStrlen(pCnt->szBindUID) : 0);
		IMnetDeleteBlack(pIM->pNetModel, (AMChar *)szBlackID);
		return eAIM_RESULT_OK;
	}
}

AIM_RESULT	IAIM_ChangeSrvMode( AMHandle hIM, AMUChar ucStatus)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM);

	if(ucStatus)
		pIM->pAcnt->uiFlag |= 0x20;
	else
		pIM->pAcnt->uiFlag &= ~0x20;

	DPRINT("%s >>>>>> status: %d\n", __FUNCTION__, ucStatus);
	IMnetChangeSrvMode(pIM->pNetModel, ucStatus);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_SendMessage( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg)
{
	return IAIM_SendMessageEx(hIM, szContactID, szMsg, 0);
}

AIM_RESULT IAIM_SendMessageEx( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg, AMInt32 appendMobileImMsg )
{
	IAIM *pIM = (IAIM *)hIM;
	
	AMAssert(AMNULL != pIM && AMNULL != szContactID && AMNULL != szMsg);

	DPRINT("IAIM_SendMsg..................%s, %s",szContactID, szMsg);
	IAIMSessionModel_SendMsg(pIM->pSesModel, (AMChar *)szContactID, (AMChar *)szMsg, appendMobileImMsg);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_SendU2UMessage( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg, AMInt32 msgType )
{
	IAIM *pIM = (IAIM *)hIM;

	AMAssert(AMNULL != pIM && AMNULL != szContactID && AMNULL != szMsg);

	DPRINT("IAIM_SendU2UMessage..................%s, %s",szContactID, szMsg);
	IMnetSendMessageEx(pIM->pNetModel, szContactID, AMStrlen(szContactID), szMsg, AMStrlen(szMsg), 0, msgType, 0);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_SendSessionMsg(AMHandle hIM, AMHandle hSession, const AMChar *szMsg)
{
	IAIM *pIM = (IAIM *)hIM;
	IASession	*pSes = (IASession *) hSession; 

	AMAssert( pIM && pSes && pSes->szContactID && szMsg);

	DPRINT("IAIM_SendMsg..................%s, %s",pSes->szContactID, szMsg);
	IAIMSessionModel_SendMsg(pIM->pSesModel, (AMChar *)pSes->szContactID, (AMChar *)szMsg, 0);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_SendVerify( AMHandle hIM, const AMChar *szContactID, const AMChar *szInfo )
{
	IAIM *pIM = (IAIM *)hIM;
	IAContact	*pTmpCnt = AMNULL;
	AMAssert(0 != pIM && 0 != szContactID);

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szContactID, AMStrlen(szContactID));
	IAContact_AutoSetBindUid(pIM, pTmpCnt);
	IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
	DPRINT("IAIM_SendVerify..................ID: %s",szContactID);
	IMnetSendVerifyInfo(pIM->pNetModel, (AMChar *)szContactID, AMNULL, (AMChar *)szInfo);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_AcceptAddContact( AMHandle hIM, const AMChar *szContactID )
{
	IAIM *pIM = (IAIM *)hIM;
	IAContact	*pCntFind = AMNULL, *pTmpCnt = AMNULL;
	AMAssert(AMNULL != pIM && AMNULL != szContactID);

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szContactID, AMStrlen(szContactID));
	pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact));
	if(pCntFind && pCntFind->szBindUID)
	{
		IMnetPutBindInfo(pIM->pNetModel, pCntFind->szBindUID, AMStrlen(pCntFind->szBindUID));
	}
	else
	{
		IAContact_AutoSetBindUid(pIM, pTmpCnt);
		IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
	}
	IAContact_Destroy(pTmpCnt);

	IMnetAcceptAddContact(pIM->pNetModel, (AMChar *)szContactID, 0, 0);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_RejectAddContact( AMHandle hIM, const AMChar *szContactID, const AMChar *szInfo )
{
	IAIM *pIM = (IAIM *)hIM;
	IAContact	*pCntFind = AMNULL, *pTmpCnt = AMNULL;
	AMAssert(0 != pIM && 0 != szContactID);


	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szContactID, AMStrlen(szContactID));
	pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact));
	if(pCntFind && pCntFind->szBindUID)
	{
		IMnetPutBindInfo(pIM->pNetModel, pCntFind->szBindUID, AMStrlen(pCntFind->szBindUID));
	}
	else
	{
		IAContact_AutoSetBindUid(pIM, pTmpCnt);
		IMnetPutBindInfo(pIM->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID) : 0);
	}
	IAContact_Destroy(pTmpCnt);

	IMnetRejectAddContact(pIM->pNetModel, (AMChar *)szContactID, (AMChar *)szInfo);

	return eAIM_RESULT_OK;
}

AIM_RESULT	IAIM_GetMemo( AMHandle hIM, const AMChar *szContactID)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM && 0 != szContactID);

	return IMnetGetContactMemo(pIM->pNetModel, (AMChar *)szContactID);		 
}

AMVoid			IAIM_StoreClear(IAIM *pIM, AMBool bClear)
{
	AMInt32 iStoreFlag = 0;
	AMAssert(0 != pIM && 0 != pIM->pAcnt);
	iStoreFlag= IAContactModel_Store(pIM->pCntModel, bClear);
	IAccountModel_UpdateStamp(pIM->pAcntModel, pIM->pAcnt, iStoreFlag);
	IAccountModel_Store(pIM->pAcntModel);
	if(AMTRUE == bClear)
		IASessionModel_CloseDB(pIM->pSesModel);
}


AIM_RESULT IAIM_Logout( AMHandle hIM )
{
	IAIM *pIM = (IAIM*)hIM;

	AMAssert(0 != pIM);

	DPRINT("IAIM_Logout..........................%d\n", pIM->ucImStatus);
	if(eIM_STATUS_ALLREADY == pIM->ucImStatus || eIM_STATUS_RELGOINED == pIM->ucImStatus || eIM_STATUS_RENETCONFIGED == pIM->ucImStatus)
	{
		IMnetLogoff(pIM->pNetModel);
		DPRINT("Logoff After\n");
		IAIM_UnlistenNet(pIM);
		DPRINT("IAIM_UnlistenNet After\n");
		IAIM_TransStatus(pIM, eIM_STATUS_LOGOUTED);
		IAIM_StoreClear(pIM, AMTRUE);
		if(pIM->pAcnt)
		{
			IAccount_Destroy(pIM->pAcnt);
			pIM->pAcnt = 0;
		}
		IAIM_TransStatus(pIM, eIM_STATUS_IDEL);
	}
	else if(pIM->ucImStatus >= eIM_STATUS_NETCONFIGED && pIM->ucImStatus < eIM_STATUS_ALLREADY)
	{
		IAIM_UnlistenNet(pIM);
		DPRINT("IAIM_UnlistenNet After\n");
		IAIM_TransStatus(pIM, eIM_STATUS_IDEL);
		IMnetConnectClose(pIM->pNetModel);
		DPRINT("IMnetConnectClose After\n");

		if(pIM->pAcnt)
		{
			IAccount_Destroy(pIM->pAcnt);
			pIM->pAcnt = 0;
		}
	}
	else if(eIM_STATUS_FORCEDISC == pIM->ucImStatus
				||eIM_STATUS_VERSIONEXEMPT == pIM->ucImStatus 
				|| eIM_STATUS_LOGINFAIL == pIM->ucImStatus)
	{
		IAIM_UnlistenNet(pIM);
		DPRINT("IAIM_UnlistenNet After\n");
		IAIM_TransStatus(pIM, eIM_STATUS_IDEL);
		if(pIM->pAcnt)
		{
			IAccount_Destroy(pIM->pAcnt);
			pIM->pAcnt = 0;
		}
	}
	else
	{
		
	}

	return eAIM_RESULT_OK;
}

// AMVoid			IAIM_Cancel(IAIM *pIM)
// {
// 	IAIM_Logout(pIM);
// }

AIM_RESULT IAIM_ChangePresence( AMHandle hIM, AIM_PRESENCE ePresence )
{
	IAIM *pIM = (IAIM*)hIM;
	AMUInt8 basic = getBasicStatus(ePresence),
		predef = getPredefStatus(ePresence);

	AMAssert(0 != pIM);

	DPRINT("IAIM_ChangePresence......................%d, %d\n", basic, predef);

	if(eAIM_PRESENCE_WRONG !=predef)
	{
		IMnetChangeStatus(pIM->pNetModel, basic, predef);
		pIM->pAcnt->ePresence = ePresence;
	}

	return eAIM_RESULT_OK;
}


AIM_RESULT IAIM_ChangeVerify( AMHandle hIM, AMUChar ucType )
{
	IAIM *pIM = (IAIM *)hIM;

	AMAssert(0 != pIM);

	IMnetPutBindInfo(pIM->pNetModel, pIM->pAcnt->szID, AMStrlen(pIM->pAcnt->szID));

	IMnetChangeVerifyType(pIM->pNetModel, ucType);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_ChangeSignature(AMHandle hIM, const AMChar *szSignature)
{
	IAIM *pIM = (IAIM *)hIM;
	AMChar *szSigXML = AMNULL;
	AMInt32 iSigXMLLen = 0, i = 0;
	AMChar	*szSigBgn = AMNULL, *szSigEnd = AMNULL, *szCI = AMNULL;
	AMChar *szSigXMLNew = AMNULL;
	ImEventChangeSignature	chgSigFail;
	AMChar	*szBuff = 0;
	AMChar	szTimeBuf[MAX_INT_NUMBER_LEN] = {0};
	AMAssert(0 != pIM);
	
	DPRINT("IAIM_ChangeSignature.......................%s\n", szSignature);
	if(pIM->pAcnt->szSigXML && (szSigXMLNew = BuildSigXML(pIM->pAcnt->szSigXML, szSignature)))
	{
		DPRINT("IAIM_ChangeSignature........................sigXML: %s", pIM->pAcnt->szSigXML);
	}
	else if(!pIM->pAcnt->bGetSigFail)//如果
	{
		DPRINT("IAIM_ChangeSignature..................... use default!\n");
		szBuff = AMMalloc(sizeof(XML_SIG_TEMPHEAD) + sizeof(XML_SIG_TEMPTAIL) + MAX_INT_NUMBER_LEN);
		AMAssert(AMNULL != szBuff);
		AMMemset(szBuff, 0, sizeof(XML_SIG_TEMPHEAD) + sizeof(XML_SIG_TEMPTAIL) + MAX_INT_NUMBER_LEN);

		AMStrcpy(szBuff, XML_SIG_TEMPHEAD);
		_AIMItoa(AMGetUpTime(AMNULL) + pIM->iTimeDiff, szTimeBuf);
		AMStrcat(szBuff, szTimeBuf);
		AMStrcat(szBuff, XML_SIG_TEMPTAIL);

		AMFree(pIM->pAcnt->szSigXML);
		pIM->pAcnt->szSigXML = szBuff;

		szSigXMLNew = BuildSigXML(pIM->pAcnt->szSigXML, szSignature);
	}

	if(szSigXMLNew)
	{
		DPRINT("IAIM_ChangeSignature.......................%s\n", szSigXMLNew);
		IMnetChangeSignature(pIM->pNetModel, szSigXMLNew);
		AMFree(szSigXMLNew);
	}
	else
	{
		AMMemset(&chgSigFail, 0, sizeof(chgSigFail));
		chgSigFail.retCode = -1;
		IMnetSendMsg2Callback(pIM->pNetModel, IM_EVENT_CHGSIGNATURE, &chgSigFail, sizeof(chgSigFail), AMNULL);
		if(pIM->pAcnt->bGetSigFail)
			IAIM_GetSignature(pIM, pIM->pAcnt->szID, 1);
	}
	
	return eAIM_RESULT_OK;
}

IMnetRetCode IAIM_OnNetworkConfig(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	PcCnfNetworkConfig* pConfig= (PcCnfNetworkConfig*)pEventContent;
	IAIM	*pIM = AMNULL;
	AIM_NTF_NET_STATUS ntfNetStatus;
	AIM_RSP_LOGIN ntfRspLogin;
	DPRINT("IAIM_OnNetworkConfig...............Entering\n");

	pIM = (IAIM *)IMnetGetReference(hIMnetHandle);

	if(eIM_STATUS_NETCONFIGED != pIM->ucImStatus 
		&& eIM_STATUS_RENETCONFIGED != pIM->ucImStatus)//一前一后两个networkConfig....，LoginID的NetOpen后立刻收到recvExcep，又做了一个NetOpen，两个都返回了
		return eOK;

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);//放到 return eOK后面，防止连续两次OnNetworkConfig

	if(pConfig->result > 0)//Net OK
	{
		pIM->ucRetryCnt = 0;
		if(eIM_STATUS_NETCONFIGED == pIM->ucImStatus)
		{
			DPRINT("IAIM_OnNetworkConfig.....................Before IAContactModel_Restore\n");
			if(0 != IAContactModel_Restore(pIM->pCntModel, 0x0F, AMTRUE))//测试本地联系人数据
			{
				pIM->pAcnt->iGroupStamp = pIM->pAcnt->iContactStamp = 0;
				pIM->pAcnt->iBlackStamp = pIM->pAcnt->iRevBlackStamp = 0;
			}

			DPRINT("IAIM_OnNetworkConfig..................data stamps(c,g,b,r): %d,%d,%d,%d\n", pIM->pAcnt->iContactStamp, 
				pIM->pAcnt->iGroupStamp, pIM->pAcnt->iBlackStamp, pIM->pAcnt->iRevBlackStamp);

			if( eIMnetOK == IMnetLogin(pIM->pNetModel, pIM->pAcnt->szID, pIM->pAcnt->szToken
									, pIM->ucTokenFlag, pIM->pAcnt->iContactStamp,pIM->pAcnt->iGroupStamp
									, pIM->pAcnt->iBlackStamp, pIM->pAcnt->iRevBlackStamp))
			{
				IAIM_TransStatus(pIM, eIM_STATUS_LOGINED);
				ntfNetStatus.eStatus = eNET_OK;
				IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);
			}
			else
			{
				if(pIM->pAcnt)
				{
					IAccount_Destroy(pIM->pAcnt);
					pIM->pAcnt = 0;
				}

				IAIM_TransStatus(pIM, eIM_STATUS_LOGINFAIL);

				ntfRspLogin.iRetCode = -1;
				ntfRspLogin.eInfo = eLOGIN_WRONG_PWD;
				
				IAIM_Callback(pIM, OnRspLogin, &ntfRspLogin);
			}
		}
		else if (eIM_STATUS_RENETCONFIGED == pIM->ucImStatus)
		{
			IMnetReLogin(pIM->pNetModel, pIM->pAcnt->szID, pIM->pAcnt->szToken, getBasicStatus(pIM->pAcnt->ePresence),getPredefStatus((pIM->pAcnt->ePresence)));

			IAIM_TransStatus(pIM, eIM_STATUS_RELGOINED);
		}
		else
		{
			DPRINT("IAIM_OnNetworkConfig....................%d\n", pIM->ucImStatus);
		}
	}
	else//network config fail
	{
		if(pIM->ucRetryCnt < IM_NET_RETRY_MAX)
		{
			if(AMTRUE == pIM->bTest)
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
			else
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);

			pIM->ucRetryCnt++;							
			DPRINT("IAIM_OnNetworkConfig................Continuing\n");
		}
		else
		{			
			IAccount_Destroy(pIM->pAcnt);
			pIM->pAcnt = AMNULL;

			AMMemset(IP_ADDRESS_REAL, 0, MAX_IP_LEN);//下一次重新做Allot
		
			if(eIM_STATUS_NETCONFIGED == pIM->ucImStatus)
				ntfNetStatus.eStatus = eNET_PUZZLE;
			else if(eIM_STATUS_RENETCONFIGED == pIM->ucImStatus)
				ntfNetStatus.eStatus = eNET_CUT;

			IAIM_TransStatus(pIM, eIM_STATUS_NETFAIL);

			IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);

			DPRINT("IAIM_OnNetworkConfig................Not Ready, %d\n", pIM->ucImStatus);
		}
	}
	return eIMnetOK;
}

IMnetRetCode IAIM_OnCheckVersion(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventCheckVersion *pEvt = 0;
	AIM_NTF_CHECK_VERSION ntfCheckVersion;
	IAIM *pIM = 0;
	AMAssert(0 != hIMnetHandle);
	AMAssert(0 != pEventContent);
	pEvt = (ImEventCheckVersion *)pEventContent;
	pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	AMAssert(0 != pIM);

	DPRINT("IAIM_OnCheckVersion.........................Entering!\n");

	AMAssert(eIM_STATUS_LOGINED == pIM->ucImStatus);

	//pIM->iRecvExcpCount = 0;

	if(eIM_STATUS_LOGINED != pIM->ucImStatus)
	{
		DPRINT("IAIM_OnCheckVersion..........................Logined!\n");
		return eIMnetOK;
	}

	if(0 == pEvt->retCode)
	{
		ntfCheckVersion.eInfo = eVERSION_OK;
		IAIM_TransStatus(pIM, eIM_STATUS_VERSIONCHECKED);
		DPRINT("IAIM_OnCheckVersion......................OK!\n");
	}
	else if(1 == pEvt->retCode)
	{
		ntfCheckVersion.eInfo = eVERSION_UPDATE;
		IAIM_TransStatus(pIM, eIM_STATUS_VERSIONUPDATE);
		DPRINT("IAIM_OnCheckVersion......................Compatible!\n");
	}
	else
	{
		IMnetConnectClose(pIM->pNetModel);
		IAIM_TransStatus(pIM, eIM_STATUS_VERSIONEXEMPT);

		IAccount_Destroy(pIM->pAcnt);
		pIM->pAcnt = AMNULL;
		ntfCheckVersion.eInfo = eVERSION_UPDATE;
		DPRINT("IAIM_OnCheckVersion......................Exempt!\n");
	}
	IAIM_Callback(pIM, OnNtfCheckVersion, &ntfCheckVersion);
	return eIMnetOK;
}

#ifdef AMOS_DEBUG
static AMChar *szLoginInfo[] = {"", "no acnt", "wrong pwd", "sys blk", "auth wrong", "too much", "appointed server", "forbidden wang", "forbidden", "timeout", "unknown"};
#endif // AMOS_DEBUG

#define AIMContactModel_Callback(pCntModel, funcName,  ...)	\
	do \
{\
	if((pCntModel)->pReference->callback && (pCntModel)->pReference->callback->funcName)\
	(pCntModel)->pReference->callback->funcName((pCntModel)->pReference->callback->pvArg, ## __VA_ARGS__);\
} while (0)


IMnetRetCode IAIM_OnLoginStatus(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventLoginStatus *pEvt = (ImEventLoginStatus *)pEventContent;
	IAIM *pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	AMInt32 iRestoreResult = 0;
	AIM_RSP_LOGIN rspLogin;
	AMBool bBindContacts = AMFALSE;
	AIM_NTF_DATA_READY ntfDataReady;
	AMAssert(0 != pIM);
	
	DPRINT("IAIM_OnLoginStatus.........................Entering!\n");
	if(pEvt->bindID && 0 != AMStrcmp(pIM->pAcnt->szID, pEvt->bindID))
	{//XXX auto drop bind id's user option
		bBindContacts = AMTRUE;
		return eAIM_RESULT_OK;
	}

	if(eIM_STATUS_LOGINOKRECVED == pIM->ucImStatus 
		|| eIM_STATUS_GROUPRECVED == pIM->ucImStatus
		|| eIM_STATUS_CONTACTRECVED == pIM->ucImStatus
		|| eIM_STATUS_BLACKRECVED == pIM->ucImStatus
		|| eIM_STATUS_ALLREADY == pIM->ucImStatus
		)
	{//maybe bind user 
		bBindContacts = AMTRUE;
		pIM->pCntModel->uiDirtFlag = pEvt->timestampFlag & 0x0F;
		pIM->pAcnt->uiBindIDLoginRetCode = pEvt->retCode;
		if(pIM->pAcnt->uiBindIDLoginRetCode != 0 && pIM->pAcnt->uiBindIDLoginRetCode != 33)
		{
			ntfDataReady.eInfo = eDATA_BINDID_ALLREADY;
			AIMContactModel_Callback(pIM->pCntModel, OnNtfDataReady, &ntfDataReady);
		}
		return eAIM_RESULT_OK;
	}

	AMAssert(eIM_STATUS_VERSIONCHECKED == pIM->ucImStatus || eIM_STATUS_VERSIONUPDATE == pIM->ucImStatus);

	pIM->iRecvExcpCount = 0;
	
	rspLogin.iRetCode = pEvt->retCode;


	if(0 == pEvt->retCode || 33 == pEvt->retCode)// login OK
	{
		pIM->iTimeDiff = pEvt->serverTime - AMGetUpTime(0);
		
		if(0x01 == (pIM->pAcnt->uiFlag&&0x01))
		{
			if(0 == pIM->ucTokenFlag)
			{
				IAccount_SetToken(pIM->pAcnt, pEvt->pwtoken, pEvt->pwtokenLen);
				pIM->pAcnt->uiFlag &= ~0x10;		//记录token的类型为pwToken
			}
			else if(3 == pIM->ucTokenFlag)
			{
				pIM->pAcnt->uiFlag |= 0x10;			//记录token的类型为UIDToken
			}
		}

		IAccount_SetWebMD5(pIM->pAcnt, pEvt->webmd5pw, pEvt->webmd5pwLen);
		if(pEvt->remark && AMStrstr(pEvt->remark, "mul=1"))
		{
			pIM->pAcnt->uiFlag |= 0x08;
			pIM->pAcnt->uiFlag &= ~0x20;
		}

		AMAssert(pEvt->bindid);
		if(0 != AMMemcmp(pIM->pAcnt->szID, pEvt->bindid, pEvt->bindidLen))
		{
			IAccount_SetPhoneNum(pIM->pAcnt, pIM->pAcnt->szID + ID_HEAD_LEN);
			IAccount_SetID(pIM->pAcnt, pEvt->bindid, pEvt->bindidLen);
		}

		IAccountModel_LoginOK(pIM->pAcntModel, pIM->pAcnt);

		IAIM_TransStatus(pIM, eIM_STATUS_LOGINOKRECVED);

		if(0 == pEvt->retCode)
			IAIM_Callback(pIM, OnRspLogin, &rspLogin);

		IASessionModel_InitDB(pIM->pSesModel);

		iRestoreResult = IAContactModel_Restore(pIM->pCntModel, pEvt->timestampFlag, AMFALSE);

		IMnetGetWebSession(pIM->pNetModel);

		IAIM_GetSignature(pIM, pIM->pAcnt->szID, 1);

		if(0 != iRestoreResult)
		{
			if(0x01 == (iRestoreResult&0x01))
				pIM->pAcnt->iGroupStamp = 0;
			if(0x02 == (iRestoreResult&0x02))
				pIM->pAcnt->iContactStamp = 0;
			if(0x04 == (iRestoreResult&0x04))
				pIM->pAcnt->iBlackStamp = 0;
			if(0x08 == (iRestoreResult&0x08))
				pIM->pAcnt->iRevBlackStamp = 0;
		}

#ifdef ALIM_SUPPORT_TRIBE
		IMnetShallowLoginTribe(pIM->pNetModel);
		IMnetDeepLoginTribe(pIM->pNetModel, "642518600");
#endif // ALIM_TRIBE

		DPRINT("IAIM_OnLoginStatus.......................Login OK\n");
	}
	else
	{
		IAIM_TransStatus(pIM, eIM_STATUS_LOGINFAIL);
		IMnetConnectClose(pIM->pNetModel);

		if(2 == pEvt->retCode)//如果是因为密码错误而登录失败， 则清除保存的密码
			IAccountModel_ClearToken(pIM->pAcntModel, pIM->pAcnt);

		_AIM_setRemarkMsg(pIM, pEvt->remark);
		
		if(pIM->pAcnt)
		{
			IAccount_Destroy(pIM->pAcnt);
			pIM->pAcnt = 0;
		}
		rspLogin.eInfo = pEvt->retCode<=eLOGIN_OTHER?pEvt->retCode:eLOGIN_OTHER;
		IAIM_Callback(pIM, OnRspLogin, &rspLogin);

		DPRINT("IAIM_OnLoginStatus......................Login Failed: %s\n"
			, szLoginInfo[pEvt->retCode<(sizeof(szLoginInfo)/sizeof(szLoginInfo[0])-2)?pEvt->retCode:(sizeof(szLoginInfo)/sizeof(szLoginInfo[0])-2)]);
	}

	return eIMnetOK;
}

IMnetRetCode IAIM_OnForceDisconnect(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventNtfForceDisconnect *pEvt = (ImEventNtfForceDisconnect *)pEventContent;
	AMAssert(0 != pIM);

	AMAssert(eIM_STATUS_ALLREADY >= pIM->ucImStatus && eIM_STATUS_LOGINOKRECVED <= pIM->ucImStatus);

	DPRINT("IAIM_OnForceDisconnect.........................Entering!\n");

	IAContactModel_ClearBindData(pIM, pIM->pCntModel, pIM->pAcnt->szBindID);

	//AMAssert(pIM->ucImStatus >= IM_STATUS_LOGINOKRECVED);//应该是这个，先调整一下状态值大小关系
	if(eIM_STATUS_ALLREADY == pIM->ucImStatus)
	{
		IAIM_StoreClear(pIM, AMFALSE);	//被踢下线的时候，不清空数据
	}

	IMnetConnectClose(pIM->pNetModel);

	IAIM_TransStatus(pIM, eIM_STATUS_FORCEDISC);
	
	IAIM_Callback(pIM, OnNtfForceDisconnected);

	DPRINT("IAIM_OnForceDisconnect......................OK!\n");
	return eIMnetOK;
}

IMnetRetCode IAIM_OnGetUserInfo(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetUserInfo *pEvt = (ImEventGetUserInfo *)pEventContent;
	IAIM *pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	AIM_NTF_USER_INFO ntfUserInfo;
	AMBool bBindContacts = AMFALSE;

	AMAssert(0 != pIM && 0 != pIM->pAcnt);
	DPRINT("IAIM_OnGetUserInfo.........................Entering!\n");
	
	if(pEvt->bindID && 0 != AMStrcmp(pIM->pAcnt->szID, pEvt->bindID))
	{//XXX auto drop bind id's user option
		bBindContacts = AMTRUE;
		return eAIM_RESULT_OK;
	}

	if(eIM_STATUS_ALLREADY == pIM->ucImStatus)
	{//bind id user info, ignore
		bBindContacts = AMTRUE;
		return eAIM_RESULT_OK;
	}

	ntfUserInfo.iRetCode = pEvt->retCode;
	if(!pEvt->retCode)
	{
		pIM->pAcnt->iVerifyType = pEvt->addcontactFlag;

		ntfUserInfo.iActivity = pEvt->activity;
		ntfUserInfo.iActLevel = pEvt->actLevel;
		ntfUserInfo.iAddcontactFlag = pEvt->addcontactFlag;
		ntfUserInfo.iImlevel = pEvt->imlevel;
		ntfUserInfo.iMulsendflag = pEvt->mulsendflag;
		ntfUserInfo.iNeedNextlevel = pEvt->needNextlevel;
		ntfUserInfo.iSendmsgFlag = pEvt->sendmsgFlag;
	}

	IAIM_Callback(pIM, OnNtfUserInfo, &ntfUserInfo);

	return eAIM_RESULT_OK;
}

IMnetRetCode IAIM_OnReLogin(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventReLogin *pEvnt = (ImEventReLogin*)pEventContent;
	IAIM	*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	AIM_NTF_NET_STATUS ntfNetStatus;
	AMAssert(0 != hIMnetHandle && 0 != pIM);

	AMAssert(eIM_STATUS_RELGOINED == pIM->ucImStatus);
	DPRINT("IAIM_OnReLogin.........................Entering!\n");

	if(0 == pEvnt->retCode)
	{
		IAIM_TransStatus(pIM, eIM_STATUS_ALLREADY);
		pIM->iRecvExcpCount = 0;
		DPRINT("IAIM_OnReLogin.......................OK\n");
	}
	else
	{
		IMnetConnectClose(pIM->pNetModel);
		IAIM_TransStatus(pIM, eIM_STATUS_LOGINFAIL);
		
		ntfNetStatus.eStatus = eNET_CUT;
		IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);

		DPRINT("IAIM_OnReLogin.......................Fail\n");
	}

	return eIMnetOK;
}

IMnetRetCode IAIM_OnSendException(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	PcEventSendException *pEnvt = (PcEventSendException*)pEventContent;
	AMAssert(0 != pIM);

// 	IAIM_Logout(pIM);
// 
// 	IAIM_Notify(pIM, CONN_CB_SENDEXCP, pEnvt->id);
// 	DPRINT("IAIM_OnSendException......................\n");
	return eIMnetOK;
}


AIM_RESULT IAIM_ReLogin(AMHandle hIM)
{
	IAIM *pIM = (IAIM *)hIM;

	DPRINT("%s >>>>>> Entering\n", __FUNCTION__);

	if(!pIM || eIM_STATUS_ALLREADY != pIM->ucImStatus)
		return eAIM_RESULT_NOT_READY;

#if IM_NET_SHUT_SOCKET
	IMnetConnectShut(pIM->pNetModel);
#else
	if(AMTRUE == pIM->bTest)
		IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
	else
		IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);
#endif

	return eAIM_RESULT_OK;
}

#define IM_REXCP_RETRY_MAX		25

IMnetRetCode IAIM_OnRecvException(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	PcEventRecvException *pEnvt = (PcEventRecvException*)pEventContent;
	AIMAccount	*pCntFind = 0;
	AIM_NTF_NET_STATUS ntfNetStatus;
	AMAssert(0 != pIM);

	DPRINT("IAIM_OnRecvException.........................Entering %d!\n", pIM->ucImStatus);

	if( eIM_STATUS_FORCEDISC == pIM->ucImStatus 
			|| eIM_STATUS_LOGINFAIL == pIM->ucImStatus //重登录失败也在这里
			|| eIM_STATUS_VERSIONEXEMPT == pIM->ucImStatus
			|| eIM_STATUS_NETFAIL == pIM->ucImStatus )
	{
		DPRINT("IAIM_OnRecvException..........IDEL,ForceDisc,LoginFail,VersionExempt or NetFail, do nothing!\n");
	}
	else if(eIM_STATUS_ALLREADY == pIM->ucImStatus 
				|| eIM_STATUS_RELGOINED == pIM->ucImStatus 
				|| eIM_STATUS_RENETCONFIGED == pIM->ucImStatus)
	{
		++pIM->iRecvExcpCount;

		if(pIM->iRecvExcpCount > IM_REXCP_RETRY_MAX)//在重登录成功之后收到的recvExcep要有限制
		{
			pIM->iRecvExcpCount = 0;

			if(pIM->pAcnt)
			{
				IAccount_Destroy(pIM->pAcnt);
				pIM->pAcnt = AMNULL;
			}

			IAIM_TransStatus(pIM, eIM_STATUS_LOGINFAIL);
			ntfNetStatus.eStatus = eNET_CUT;
			IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);
			DPRINT("IAIM_OnRecvException..................Give Up!\n");
		}
		else
		{
			DPRINT("IAIM_OnRecvException..................To ReLogin as we are at: %d\n", pIM->ucImStatus);

			IAIM_StoreClear(pIM, AMFALSE);
			IAIM_TransStatus(pIM, eIM_STATUS_RENETCONFIGED);

			if(AMTRUE == pIM->bTest)
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
			else
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);
		}
		
	} 
	else /*if(eIM_STATUS_RENETCONFIGED != pIM->ucImStatus && eIM_STATUS_NETCONFIGED != pIM->ucImStatus)*/
	{
		++pIM->iRecvExcpCount;

		if(pIM->iRecvExcpCount > IM_REXCP_RETRY_MAX)//在登陆成功之前收到recvExcep次数有限制
		{
			pIM->iRecvExcpCount = 0;

			if(pIM->pAcnt)
			{
				IAccount_Destroy(pIM->pAcnt);
				pIM->pAcnt = AMNULL;
			}

			IAIM_TransStatus(pIM, eIM_STATUS_LOGINFAIL);
			ntfNetStatus.eStatus = eNET_CUT;
			IAIM_Callback(pIM, OnNtfNetInfo, &ntfNetStatus);
			DPRINT("IAIM_OnRecvException.........................Give Up!\n");
		}
		else
		{
			DPRINT("IAIM_OnRecvException..................To Login as we are at: %d\n", pIM->ucImStatus);

			if(AMTRUE == pIM->bTest)
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_TEST, IP_PORT_TEST, AMFALSE);
			else
				IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS_REAL, IP_PORT_REAL, AMFALSE);

			IAIM_TransStatus(pIM, eIM_STATUS_NETCONFIGED);
		}		
	}

	return eIMnetOK;
}

IMnetRetCode IAIM_OnExceedException(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
// 	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
// 	PcEventRecvException *pEnvt = (PcEventRecvException*)pEventContent;
// 	IAccount	*pAcntFind = 0, *pAcntTmp = 0; 
// 	AMAssert(0 != pIM);
// 
// 	if(0 != pIM->pAcnt)//Logout
// 	{
// 		pAcntFind = IAccountModel_findHistoryAcnt(pIM->pAcntModel, pIM->pAcnt->szID);
// 		AMAssert(0 != pAcntFind);
// 		if(0 != pAcntFind)
// 		{
// 			IAccount_Destroy(pIM->pAcnt);
// 			pIM->pAcnt = IAccount_dup(pCntFind);
// 			pIM->bIsToken = AMTRUE;
// 		}
// 		IMnetNetworkConfig(hIMnetHandle, IP_ADDRESS, IP_PORT, AMFALSE);
// 		pIM->ucStatus = IM_STATUS_RENETCONFIGED;
// 	}
// 	DPRINT("IAIM_OnExceedException......................\n");
	return eIMnetOK;
}

IMnetRetCode IAIM_OnOtherException(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	PcEventPackException *pEvnt = (PcEventPackException*)pEventContent;

	DPRINT("IAIM_OnOtherException......................Entering!\n");
	switch (pEvnt->retCode)
	{
	case eIMnetUnsupportedFeature:
	case eIMnetInvalidLRC:
	case eIMnetBodyDataZero:
	case eIMnetPropertyError:
	case eIMnetInvalidCmd:
	case eIMnetInvalidStarter:
	case eIMnetInvalidCC:
		return eIMnetOK;
	}

	AMAssert(0 != pIM);
// 	if(eIM_STATUS_ALLREADY == pIM->ucImStatus || eIM_STATUS_RELGOINED == pIM->ucImStatus || eIM_STATUS_RENETCONFIGED == pIM->ucImStatus)
// 	{
// 		IAIM_StoreClear(pIM, AMFALSE);
// 		IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS, IP_PORT, 0);
// 		IAIM_TransStatus(pIM, eIM_STATUS_RENETCONFIGED);
// 	} 
// 	else
// 	{
// 		IMnetConnectOpen(pIM->pNetModel, IP_ADDRESS, IP_PORT, 0);
// 		IAIM_TransStatus(pIM, eIM_STATUS_NETCONFIGED);
// 	}
// 	IAIM_Notify(pIM, CONN_CB_OTHEREXCP, 0);
	DPRINT("IAIM_OnOtherException......................Leaving\n");
	return eIMnetSkip;
}

IMnetRetCode AIM_onGetWebSession(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventGetWebSession *pEvnt = (ImEventGetWebSession*)pEventContent;

	if(0 == pEvnt->retCode)
		_AIM_setWebSession(pIM, pEvnt->session, pEvnt->sessionLen);

	return eIMnetSkip;
}

IMnetRetCode _AIM_onLogin2(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventLogin2 *pEvnt = (ImEventLogin2*)pEventContent;
	AIM_RSP_LOGIN rspLogin;

	DPRINT("%s >>>>>> retCode:%d\n", __FUNCTION__, pEvnt->retCode);

	rspLogin.iRetCode = pEvnt->retCode;
	rspLogin.eInfo = eLOGIN_CONFIRM;

	if(pEvnt->retCode)
	{
		_AIM_setRemarkMsg(pIM, pEvnt->remark);
		pIM->ucImStatus = eIM_STATUS_LOGINFAIL;
		IMnetLogoff(hIMnetHandle);
	}

	IAIM_Callback(pIM, OnRspLogin, &rspLogin);

	return eIMnetSkip;
}

void IAIM_ListenConnection(IAIM *pIm)
{
	IMnetMainRegister(pIm->pNetModel, PC_EVENT_NETWORK_CONFIG, IAIM_OnNetworkConfig);
	IMnetMainRegister(pIm->pNetModel, IM_EVENT_CHECKVERSION, IAIM_OnCheckVersion);
	IMnetMainRegister(pIm->pNetModel, IM_EVENT_LOGIN_STATUS, IAIM_OnLoginStatus);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_FORCEDISCONNECT, IAIM_OnForceDisconnect);
	IMnetMainRegister(pIm->pNetModel, IM_EVENT_RELOGIN, IAIM_OnReLogin);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_GETUSERINFO, IAIM_OnGetUserInfo);

//	IMnetMainRegister(pIm->pNetModel, PC_EVENT_SEND_EXCEPTION, IAIM_OnSendException);
	IMnetMainRegister(pIm->pNetModel, PC_EVENT_RECV_EXCEPTION_IND, IAIM_OnRecvException);
// 	IMnetMainRegister(pIm->pNetModel, PC_EVENT_EXCEED_EXCEPTION_IND, IAIM_OnExceedException);
// 	IMnetMainRegister(pIm->pNetModel, PC_EVENT_PACK_EXCEPTION_IND, IAIM_OnOtherException);
// 	IMnetMainRegister(pIm->pNetModel, PC_EVENT_UNPACK_EXCEPTION_IND, IAIM_OnOtherException);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_PRIVATE, IAIM_OnPrivateEvent);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_GET_APP_ADDR, AIMTransModule_onGetAppAddr);

	IMnetMainRegister(pIm->pNetModel, IM_NTF_NEED_AUTHCODE, AIMAuthModule_onNtfNeedAuth);
	IMnetMainRegister(pIm->pNetModel, IM_EVENT_CHECK_AUTHCODE, AIMAuthModule_onRspCheckCode);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_GETWEBSESSION, AIM_onGetWebSession);

	IMnetMainRegister(pIm->pNetModel, IM_EVENT_LOGIN2, _AIM_onLogin2);

	return ;
}

void IAIM_UnlistenConnection(IAIM *pIm)
{
	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_NETWORK_CONFIG, IAIM_OnNetworkConfig);
	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_CHECKVERSION, IAIM_OnCheckVersion);
	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_LOGIN_STATUS, IAIM_OnLoginStatus);
	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_FORCEDISCONNECT, IAIM_OnForceDisconnect);
	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_RELOGIN, IAIM_OnReLogin);

	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_GETUSERINFO, IAIM_OnGetUserInfo);

//	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_SEND_EXCEPTION, IAIM_OnSendException);
	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_RECV_EXCEPTION_IND, IAIM_OnRecvException);
// 	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_EXCEED_EXCEPTION_IND, IAIM_OnExceedException);
// 	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_PACK_EXCEPTION_IND, IAIM_OnOtherException);
// 	IMnetMainUnregister(pIm->pNetModel, PC_EVENT_UNPACK_EXCEPTION_IND, IAIM_OnOtherException);

	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_PRIVATE, IAIM_OnPrivateEvent);

	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_GET_APP_ADDR, AIMTransModule_onGetAppAddr);

	IMnetMainUnregister(pIm->pNetModel, IM_NTF_NEED_AUTHCODE, AIMAuthModule_onNtfNeedAuth);
	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_CHECK_AUTHCODE, AIMAuthModule_onRspCheckCode);

	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_GETWEBSESSION, AIM_onGetWebSession);

	IMnetMainUnregister(pIm->pNetModel, IM_EVENT_LOGIN2, _AIM_onLogin2);
	return ;
}

void IAIM_ListenNet(IAIM *pIm)
{
	AMAssert(0 != pIm);
	IAIM_ListenConnection(pIm);
	IAContactModel_ListenIMnet(pIm->pCntModel, pIm->pNetModel);
	IASessionModel_ListenIMnet(pIm->pSesModel, pIm->pNetModel);
}

void IAIM_UnlistenNet(IAIM *pIm)
{
	AMAssert(0 != pIm);
	IAIM_UnlistenConnection(pIm);
	IAContactModel_UnlistenIMnet(pIm->pCntModel, pIm->pNetModel);
	IASessionModel_UnlistenIMnet(pIm->pSesModel, pIm->pNetModel);
}

static AMInt32 IAIM_OnSelReply(void* pvList, int iCnt, char **pszValue, char**pszName)
{
	List	*pList = (List *)pvList;
	IAIMessage *pMsg = IAIMessage_Create();

	pMsg->_iRid = AMAtoi(pszValue[0]);
	IAIMessage_SetContent(pMsg, pszValue[1], AMStrlen(pszValue[1]));

	insert_List(pList, pMsg, sizeof(IAIMessage), DYNAMIC);

	return 0;
}

AIM_RESULT IAIM_GetPredefMsgs(AMHandle hIM, AMHandle **pphMsgArray, AMInt32 *piSize)
{
	IAIM		*pIm = (IAIM*)hIM;
	AMInt32		rcSqlite	= 0;
	AMChar		*szErrMsg	= 0;
	sqlite3		*pDB = 0;
	List		lst;

	AMAssert( pIm && pphMsgArray && piSize);

	*piSize = 0;

	if(!pIm->pAcnt)
		return eAIM_RESULT_NOT_READY;

	rcSqlite = myADB_Open(pIm->pAcnt->szID, &pDB, AMFALSE);

	if(rcSqlite)
	{
		DPRINT("IAIM_RestoreReply: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		pDB = 0;
		return eAIM_RESULT_DB_ERROR;
	}

	AMMemset(&lst, 0, sizeof(List));
	construct(List, &lst, sizeof(IAIMessage), NOFREE);

	rcSqlite  = sqlite3_exec(pDB, "SELECT * FROM _fastreply;",
								IAIM_OnSelReply, &lst, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_RestoreReply:.......Can't SELECT * FROM _fastreply;, for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);

		lst.objfree = FREEOBJ;//设置成FREEOBJ，应该可以销毁对象....未试验..
		destruct(List, &lst);//或者需要用Iter销毁各个对象。

		return eAIM_RESULT_DB_ERROR;
	}

	sqlite3_close(pDB);

	*piSize = lst.size;
	if(lst.size)
	{
		*pphMsgArray = (AMHandle *)AMMalloc(sizeof(AMHandle) * lst.size);
		if(*pphMsgArray)
		{
			ListIter *pIter = AMNULL;
			AMInt32	i = 0;
			pIter = create(ListIter, &lst);
			head(ListIter, pIter);
			do 
			{
				(*pphMsgArray)[i++] = (AMHandle)retrieve(ListIter, pIter);
			} while (!next(ListIter, pIter));
			destroy(ListIter, pIter);
		}
		else
		{
			destruct(List, &lst);//NOFREE
			return eAIM_RESULT_MALLOC_ERROR;
		}
	}

	destruct(List, &lst);//NOFREE

	DPRINT("IAIM_RestoreReply................OK\n");

	return eAIM_RESULT_OK;
}

//iFlag : 0 release handle Array, and every msg; 1 release handle array only; 2 release every msg only
AIM_RESULT AIM_ReleasePredefMsgs(AMHandle hIM, AMHandle *phMsgArray, AMInt32 iSize, AMInt32 iFlag)
{
	IAIM		*pIm = (IAIM*)hIM;
	AMInt32		i = 0;

	AMAssert( pIm && phMsgArray );
	AMAssert( iFlag > -1 && iFlag < 3 );

	if(iSize)
	{
		if(1 != iFlag)
			for(i=0; i<iSize; i++)
				IAIMessage_Destroy((IAIMessage*)phMsgArray[i]);

		if(2 != iFlag)
			AMFree(phMsgArray);
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_ReleasePredefMsgs(AMHandle hIM, AMHandle *phMsgArray, AMInt32 iSize)
{
	return AIM_ReleasePredefMsgs(hIM, phMsgArray, iSize, 0);
}

#define		IM_INSERT_REPLY	"INSERT INTO _fastreply VALUES(NULL, '%q');"
AIM_RESULT IAIM_AddPredefMsg( AMHandle hIM, const AMChar *szBody, AMInt64 *pi64ID )
{
	IAIM *pIm = (IAIM *)hIM;
	AMInt32	rcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	sqlite3	*pDB = 0;
	AMChar	*szSql = 0;
	AMInt64 iRet = 0;

	AMAssert( pIm && pIm->pAcnt );

	rcSqlite = myADB_Open(pIm->pAcnt->szID, &pDB, AMFALSE);
	if(rcSqlite)
	{
		DPRINT("IAIM_AddFastReply: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	rcSqlite = sqlite3_exec(pDB, "CREATE TABLE IF NOT EXISTS _fastreply(_rid INTEGER PRIMARY KEY AUTOINCREMENT,\
								 _reply TEXT);",
								 0, 0, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_AddFastReply.............: can not CREATE TABLE _fastreply;, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	szSql = sqlite3_mprintf(IM_INSERT_REPLY, szBody);

	if(AMNULL == szSql)
	{
		sqlite3_close(pDB);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	rcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_AddFastReply.............: can not BEGIN TRANSACTION;, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
	sqlite3_free(szSql);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_AddFastReply.............: can not INSERT, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	iRet = sqlite3_last_insert_rowid(pDB);

	rcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_AddFastReply.............: can not COMMIT TRANSACTION;, for: %s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	sqlite3_close(pDB);

	if(AMNULL != pi64ID)
	{
		*pi64ID = iRet;
	}

	return eAIM_RESULT_OK;
}

#define IM_DELETE_REPLY		"DELETE FROM _fastreply WHERE _rid=%lld;"
#define IM_DELETE_REPLY_ALL	"DELETE FROM _fastreply;"
AIM_RESULT IAIM_RemovePredefMsg( AMHandle hIM, AMInt64 id )
{
	IAIM *pIm = (IAIM *)hIM;
	AMInt32	rcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	sqlite3	*pDB = 0;
	AMChar	*szSql = 0;

	AMAssert( pIm && pIm->pAcnt );

	rcSqlite = myADB_Open(pIm->pAcnt->szID, &pDB, AMFALSE);
	if(rcSqlite)
	{
		DPRINT("IAIM_RemoveFastReply: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	if(id)
		szSql = sqlite3_mprintf(IM_DELETE_REPLY, id);
	else
		szSql = sqlite3_mprintf(IM_DELETE_REPLY_ALL);

	if(szSql)
	{
		rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);

		sqlite3_free(szSql);

		if(SQLITE_OK != rcSqlite)
		{
			DPRINT("IAIM_RemoveFastReply.............: can not DELETE, for: %s\n", szErrMsg);
			sqlite3_free(szErrMsg);
			AMFree(szSql);
			return eAIM_RESULT_DB_ERROR;
		}

		sqlite3_close(pDB);

		return eAIM_RESULT_OK;
	}
	else
	{
		return eAIM_RESULT_MALLOC_ERROR;
	}
}

#define SQL_UPDATE_REPLY		"UPDATE _fastreply SET _reply='%q' WHERE _rid=%lld;"
AIM_RESULT IAIM_UpdatePredefMsg( AMHandle hIM, AMInt64 iID, const AMChar *szBody )
{
	IAIM *pIm = (IAIM *)hIM;
	AMInt32	rcSqlite	= 0;
	AMChar	*szErrMsg	= 0;
	sqlite3	*pDB = 0;
	AMChar	*szSql = 0;

	AMAssert(AMNULL != pIm && AMNULL != szBody);

	AMAssert(pIm->pAcnt);

	rcSqlite = myADB_Open(pIm->pAcnt->szID, &pDB, AMFALSE);
	if(rcSqlite)
	{
		DPRINT("IAIM_ModifyFastReply: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		pDB = AMNULL;
		return eAIM_RESULT_DB_ERROR;
	}

	szSql = sqlite3_mprintf(SQL_UPDATE_REPLY, szBody, iID);
	if(AMNULL == szSql)
	{
		sqlite3_close(pDB);
		return eAIM_RESULT_MALLOC_ERROR;
	}

	rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);

	sqlite3_free(szSql);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAIM_ModifyFastReply.............: can not Update, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return eAIM_RESULT_DB_ERROR;
	}

	sqlite3_close(pDB);

	return eAIM_RESULT_OK;
}

#define IM_DELETE_REPLY		"DELETE FROM _fastreply WHERE _rid=%lld;"
#define IM_DELETE_REPLY_ALL	"DELETE FROM _fastreply;"

AIM_RESULT IAIM_DeleteAllMsg( AMHandle hIM )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);

	IASessionModel_DeleteAllMsg(pIM->pSesModel);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_DeleteMsgById( AMHandle hIM, AMInt64 i64ID )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);

	AIMSessionModel_DeleteMsgById(pIM->pSesModel, i64ID);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIM_MarkMsgReadById( AMHandle hIM, AMInt64 i64ID )
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);

	AIMSessionModel_MarkMsgReadById( pIM->pSesModel, i64ID );

	return eAIM_RESULT_OK;
}

void IAIM_TransStatus(IAIM *pIm, AMUChar status)
{
#ifdef TRACE_STATUS
	AMChar	szBuff[20] ={0};
	AMPrintf("\n\n\n\nFrom %d----->%d\n\n\n\n", pIm->ucImStatus, status);
	AMSprintf(szBuff, "%d--->%d\n", pIm->ucImStatus, status);
	AMFwrite(szBuff, 1, 19, pIm->fStatus);
#endif // TRACE_STATUS
	AMAssert(0 != pIm);
	pIm->ucImStatus = status;
}

AIM_RESULT IAIM_UpdateSetting(AMHandle hIM, AIM_ACCOUNT_SETTING *pSetting, AMBool bBlockStranger)
{
	IAIM *pIM = (IAIM *)hIM;
	AMChar *szSql = AMNULL;
	AMChar *szErrMsg = AMNULL;
	AMInt32 iRcSqlite = 0;

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);
	
	if(pSetting)
	{
		pIM->pAcnt->uiFlag &= ~7;
		pIM->pAcnt->uiFlag |= AMAccount_CaculateFlag(pSetting->bSavePwd, pSetting->bMute, pSetting->bViberate);
		pIM->pAcnt->ePresence = pSetting->eDefaultPresence;
	}
	else
	{
		if(bBlockStranger)
			pIM->pAcnt->uiFlag |= 0x40;
		else
			pIM->pAcnt->uiFlag &= ~0x40;
	}
	
	return IAccountModel_UpdateFlag(pIM->pAcntModel, pIM->pAcnt);
}

AIM_RESULT AIM_GetCurSigXML(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(NULL != pIM && NULL != pszToken && NULL != puiLen);

	if(NULL != pIM->pAcnt)
	{
		*pszToken = pIM->pAcnt->szSigXML;
		*puiLen = pIM->pAcnt->szSigXML?AMStrlen(pIM->pAcnt->szSigXML):0;
	}
	else
	{
		*pszToken = NULL;
		*puiLen = 0;
	}

	return eAIM_RESULT_OK;
}


/*
 *	@brief		start a task to receive file
 */
AIM_RESULT IAIM_ReceiveFile(AMHandle hIM, const AMChar *szContactId, const AMChar *szObjXml
							, const AMChar *szFileName, AMInt32 *piTransId)
{
	IAIM *pIM = (IAIM *)hIM;
	AMInt32 iTaskId = 0, iRetCode = eAIM_RESULT_OK;
	
	AMAssert( pIM && pIM->pAcnt );

	if(!szContactId || !szObjXml )
		return eAIM_RESULT_PARAM_ERROR;
		
	iRetCode = AIMTransModule_receive(pIM->hTransModule, szContactId, szObjXml, szFileName, &iTaskId);

	if(piTransId)
		*piTransId = iTaskId;

	return iRetCode;
}

/*
 *	@brief		cancel the download task
 */
AIM_RESULT IAIM_CancelTrans(AMHandle hIM, AMInt32 iTaskId)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert( pIM && pIM->pAcnt );

	return AIMTransModule_cancel(pIM->hTransModule, iTaskId);
}

/*
 *	@brief		start a task to send file.
 */
AIM_RESULT IAIM_SendFile(AMHandle hIM, const AMChar *szContactId, const AMChar *szFileName, AMInt32 *piTransId)
{
	IAIM *pIM = (IAIM *)hIM;
	AMInt32 iTaskId = 0, iRetCode = eAIM_RESULT_OK;

	AMAssert( pIM && pIM->pAcnt );

	if(!szContactId || !szFileName)
		return eAIM_RESULT_PARAM_ERROR;

	iRetCode = AIMTransModule_send(pIM->hTransModule, szContactId, szFileName, &iTaskId);

	if(piTransId)
		*piTransId = iTaskId;

	return iRetCode;
}

/*
 *	@brief				validate the auth code.
 */
AIM_RESULT IAIM_CheckAuthCode(AMHandle hIM, AMInt32 iAuthId, const AMChar *szCode)
{
	IAIM *pIm = (IAIM *)hIM;
	AMAssert(pIm && pIm->pAcnt);
	return AIMAuthModule_checkCode(pIm->hAuthModule, iAuthId, szCode);
}

/*
 *	@brief				update the auth code.
 */
AIM_RESULT IAIM_UpdateAuthCode(AMHandle hIM, AMInt32 iAuthId)
{
	IAIM *pIm = (IAIM *)hIM;
	AIM_PRIVATE_EVENT reqUpdateAuth;
	AMAssert(pIm && pIm->pAcnt);
	reqUpdateAuth.iEventType = eAIM_PRIVATE_EVENT_CAPCHA;
	reqUpdateAuth.iParam1 = iAuthId;

	return IMnetSendMsg2Callback(pIm->pNetModel, IM_EVENT_PRIVATE, &reqUpdateAuth, sizeof(AIM_PRIVATE_EVENT), AMNULL);
}

/*
 *	@brief				cancel the auth code.
 */
AIM_RESULT IAIM_CancelAuthCode(AMHandle hIM, AMInt32 iAuthId)
{
	IAIM *pIm = (IAIM *)hIM;
	AMAssert(pIm && pIm->pAcnt);
	return AIMAuthModule_cancelAuth(pIm->hAuthModule, iAuthId);
}


void IAIM_BindIDLogin(AMHandle hIM)
{
	IAIM *pIM = (IAIM *)hIM;
	AMAssert(0 != pIM && 0 != pIM->pNetModel);

	pIM->pAcnt->eBindStatus = eAIM_BIND_GETING;
	IMnetGetWebBinding(pIM->pNetModel);
}

