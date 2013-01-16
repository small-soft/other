#include "CallbackAdapterTest.h"
#include "AIMessage.h"
#include "AMString.h"
#include "OldMsgType.h"
#include "AMTime.h"
#include "AIM.h"

#define		CONN_CB_NETPUZZLE		1
#define		CONN_CB_CANUPDATE		2
#define		CONN_CB_EXEMPT			3
#define		CONN_CB_LOGINFAIL		4
#define		CONN_CB_DISCONECT		5
#define		CONN_CB_LOGINOK			6
#define		CONN_CB_SENDEXCP		7
#define		CONN_CB_RECVEXCP		8
#define		CONN_CB_OTHEREXCP		9
#define		CONN_CB_NETOK			10
#define		CONN_CB_GETUSERINFO		11
#define		CONN_CB_NETCUT			12		//在线的时候被断网了（清华的处理过程不一样）

#define		eLOGIN_NO_ACNT		1
#define		eLOGIN_WRONG_PWD	2
#define		eLOGIN_SYS_BLK		3
#define		eLOGIN_AUTH_LIMIT	4
#define		eLOGIN_TOO_MANY		5
#define		eLOGIN_APP_SEVR		6
#define		eLOGIN_WANGHAO		7
#define		eLOGIN_FORBIDDEN	8
#define		eLOGIN_TIMEOUT		9
#define		eLOGIN_NETPUZZLE	10
#define		eLOGIN_COMPANY		14
#define		eLOGIN_PHONE		15

/**
* @brief			表明所有联系人信息已经完备，（表明登录完全成功）
*/						
#define		CONTACT_LIST_LOADED  	100
/**
* @brief			表明某组添加了某个联系人
*/
#define		CONTACT_ADDED  			101
/**
* @brief			表明某组移除了某个联系人
*/
#define		CONTACT_REMOVED  		102
/**
* @brief			表明绑定帐号的所有联系人信息已经完备，（表明登录完全成功）
*/						
#define		CONTACT_BINDID_LIST_LOADED 	109
/**
* @brief			绑定帐号被踢
*/
#define		CONTACT_BINDID_KICKED	110

extern AMHandle hIM;

AMInt32 JavaCntListener(AMVoid *pArg, AMInt32 iType, AMInt64 i64GrpID,  const AMChar *szCntID)
{
	DPRINT("JavaCntListener.........Called with 0x%x, %d, "I64FORMAT", %s\n", pArg, iType, i64GrpID, szCntID);
	return 0;
}

AMInt32 JavaPreListener(AMVoid *pArg, const AIM_CONTACT_UPDATE_DATA* pPresent, AMInt32 iCnt)
{
	DPRINT("JavaPreListener.........Called with 0x%x, 0x%x, %d\n", pArg, pPresent, iCnt);
	return 0;
}

AMInt32 JavaMsgListener(AMVoid *pArg, IASession *pSes, IAIMessage *pMsg)
{
	DPRINT("JavaMsgListener.........Called with 0x%x, 0x%x, 0x%x\n", pArg, pSes, pMsg);
	return 0;
}

AMInt32 JavaConnListener(AMVoid *pvArg, AMInt32 ucType, AMInt32 iInfo)
{
	DPRINT("JavaConnListener.........Called with 0x%x, %d, %d\n", pvArg, ucType, iInfo);
	return 0;
}


static AMInt32 Adapter_OnIncomingSysMsg(IASessionModel *pSesModel, IAIMessage *pMsg, AMVoid *pvArg)
{
	
	IASession *pSysSes = AMNULL;
	AMAssert(0 != pSesModel && 0 != pMsg);

	IASessionModel_StoreMsg(pSesModel, pMsg, AMFALSE);

	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, SYS_SES_NAME, (AMPVoid*)&pSysSes))
	{
		DPRINT("IASessionModel_OnIncomingSysMsg..................Error!\n");
		AMAssert(0);
	}

	return JavaMsgListener(pvArg, pSysSes, pMsg);
}


AIM_RESULT	OnNtfForceDisconnected(AMVoid *pArg)
{
	return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_DISCONECT, 0);
}

AIM_RESULT	OnNtfCheckVersion(AMVoid *pArg, AIM_NTF_CHECK_VERSION *ntfCheckVersion)
{
	switch (ntfCheckVersion->eInfo)
	{
	case eVERSION_OK:
		break;
	case eVERSION_UPDATE:
		return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_CANUPDATE, 0);
		break;
	case eVERSION_EXPIRE:
		return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_EXEMPT, 0);
		break;
	case eVERSION_UNKNOWN:
		break;
	default:
		;
	}
	return eAIM_RESULT_OK;
}
AIM_RESULT	OnNtfDataReady(AMVoid *pArg, AIM_NTF_DATA_READY *ntfDataReady)
{
	switch (ntfDataReady->eInfo)
	{
	case eDATA_GROUP_READY:
		break;
	case eDATA_FRIEND_READY:
		break;
	case eDATA_STRANGER_READY:
		break;
	case eDATA_RECENT_READY:
		break;
	case eDATA_BLACK_READY:
		break;
	case eDATA_ALLREADY:
		return (AIM_RESULT)JavaCntListener(pArg, CONTACT_LIST_LOADED, 0, 0);
		break;
	}
	return eAIM_RESULT_OK;
}
AIM_RESULT	OnNtfNetInfo(AMVoid *pArg, AIM_NTF_NET_STATUS * pNtfNetStatus)
{
	switch (pNtfNetStatus->eStatus)
	{
	case eNET_OK:
		return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETOK, 0);
		break;
	case eNET_PUZZLE:
		return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETPUZZLE, 0);
		break;
	case eNET_CUT:
		return (AIM_RESULT)JavaConnListener(pArg, CONN_CB_NETCUT, 0);
		break;
	}
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfUpdateGroup(AMVoid *pvArg, AIM_NTF_UPDATE_GROUP *pNtfUpdateGroup)
{
	AMInt64 i64GrpId = 0;
	AMChar *szContactId = AMNULL;
	AMInt32 iType = 0;

	if(eAIM_GROUP_ADD == pNtfUpdateGroup->eType)
		iType = CONTACT_ADDED;
	else if(eAIM_GROUP_REMOVE == pNtfUpdateGroup->eType)
		iType = CONTACT_REMOVED;

	IAIMGroup_GetID(pNtfUpdateGroup->hGroup, &i64GrpId);
	IAIMContact_GetID(pNtfUpdateGroup->hContact, (const AMChar **)&szContactId);
	return (AIM_RESULT)JavaCntListener(pvArg, iType, i64GrpId, szContactId);
}

AIM_RESULT	OnNtfUpdateContact(AMVoid *pArg, AIM_NTF_UPDATE_CONTACT *pNtfUpdateContact)
{
	AIM_CONTACT_UPDATE_DATA	*pPresent = 0;
	AMInt32 i=0;
	IAIM *pIM = (IAIM*)(((AMPVoid*)pArg)[1]);
	pPresent = (AIM_CONTACT_UPDATE_DATA*)AMMalloc(sizeof(AIM_CONTACT_UPDATE_DATA) * pNtfUpdateContact->iCount);
	AMMemset(pPresent, 0, sizeof(AIM_CONTACT_UPDATE_DATA) * pNtfUpdateContact->iCount);

	switch(pNtfUpdateContact->eType)
	{
	case eAIM_CONTACT_PRESENCE_FIRST:
		DPRINT("OnNtfUpdateContact..........................Presence First!\n");
		for(i=0; i<pNtfUpdateContact->iCount; i++)
		{
			pPresent[i].ucType = eAIM_CONTACT_PRESENCE;
			IAIMContact_GetPresence(pNtfUpdateContact->phContacts[i], (AIM_PRESENCE*)&pPresent[i].ucStatus);
		}
		break;
	case eAIM_CONTACT_PRESENCE:
		DPRINT("OnNtfUpdateContact..........................Presence!\n");
		for(i=0; i<pNtfUpdateContact->iCount; i++)
		{
			pPresent[i].iFlag = 1;
			pPresent[i].ucType = eAIM_CONTACT_PRESENCE;
			IAIMContact_GetPresence(pNtfUpdateContact->phContacts[i], (AIM_PRESENCE*)&pPresent[i].ucStatus);
		}
		break;
	case eAIM_CONTACT_SIGNATURE:
		DPRINT("OnNtfUpdateContact..........................Signature!\n");
		for(i=0; i<pNtfUpdateContact->iCount; i++)
		{
			pPresent[i].iFlag = 1;
			pPresent[i].ucType = eAIM_CONTACT_SIGNATURE;
			IAIMContact_GetSignature(pNtfUpdateContact->phContacts[i], (const AMChar **)&pPresent[i].szSignature);
		}
		break;
	case eAIM_CONTACT_PORTRAIT:
		DPRINT("OnNtfUpdateContact..........................Portrait!\n");
#ifdef ALIM_SUPPORT_PORTRAIT_NOTIFY	// notify the event
		for(i=0; i<pNtfUpdateContact->iCount; i++)
		{
			pPresent[i].iFlag = 1;
			pPresent[i].ucType = eAIM_CONTACT_PORTRAIT;
		}
#else // get the portrait data. 
		IAIMContact_GetID(pNtfUpdateContact->phContacts	[0], (const AMChar **)&pPresent[0].szID);
		IAIM_GetPortrait(pIM, pPresent[0].szID);

		pNtfUpdateContact->iCount = 0;//如果是头像事件，则不向上发送了
#endif
	default:
		pNtfUpdateContact->iCount = 0;
	}

	for(i=0; i<pNtfUpdateContact->iCount; i++)
	{
		IAIMContact_GetID(pNtfUpdateContact->phContacts	[i], (const AMChar **)&pPresent[i].szID);
	}		

	if(pNtfUpdateContact->iCount)
	{
		JavaPreListener(pArg, pPresent, pNtfUpdateContact->iCount);
	}
	AMFree(pPresent);
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfMesage(AMVoid *pvArg, AIM_NTF_MSG *pNtfMsg)
{
	return (AIM_RESULT)JavaMsgListener(pvArg, (IASession*)pNtfMsg->hSession, (IAIMessage*)pNtfMsg->hMessage);
}

AIM_RESULT	OnNtfAddedBy(AMVoid *pvArg, AIM_NTF_ADDED_BY *pNtfAddedBy)
{
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfAcceptedBy(AMVoid *pvArg, AIM_NTF_ACCEPTED_BY * pNtfAcceptedBy)
{
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfRejectedBy(AMVoid *pvArg, AIM_NTF_REJECTED_BY * pNtfRejectedBy)
{
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfRequestFrom(AMVoid *pvArg, AIM_NTF_REQUEST_FROM *pNtfRequestFrom)
{
	return eAIM_RESULT_OK;
}
AIM_RESULT	OnNtfHelpLogin(AMVoid *pvArg, AIM_NTF_HELP_LOGIN *pNtfHelpLogin)
{
	IAIMessage	*pMsg = AMNULL;	
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);

	AMAssert(AMNULL != pIM && AMNULL != pNtfHelpLogin);

	pMsg = IAIMessage_Create();
	if(!pNtfHelpLogin->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)HELP_LOGIN_OK;
		IAIMessage_SetCntID(pMsg, pNtfHelpLogin->szParentId, AMStrlen(pNtfHelpLogin->szParentId));

		IAIMessage_SetContent(pMsg, " ", 1);
		pMsg->szContent[0] = '0' + pNtfHelpLogin->uiMulStatus;
		DPRINT("OnNtfHelpLogin................HELP_LOGIN_OK %s, %s!\n", pMsg->szContactID, pMsg->szContent);
	}
	else
	{
		pMsg->eType = (AIM_MSG_TYPE)HELP_LOGIN_FAIL;
		DPRINT("OnNtfHelpLogin................HELP_LOGIN_FAIL! %d\n", pNtfHelpLogin->iRetCode);
	}

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	DPRINT("OnNtfHelpLogin.........................OK!\n");

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfUserInfo(AMVoid *pvArg, AIM_NTF_USER_INFO *pNtfUserInfo)
{	
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	DPRINT("OnNtfUserInfo.........................Entering!\n");
	AMAssert(pIM && pIM->pAcnt);
	AMAssert(pNtfUserInfo);
	return (AIM_RESULT)JavaConnListener(pvArg, CONN_CB_GETUSERINFO, pNtfUserInfo->iImlevel<<8 | pIM->pAcnt->iVerifyType);
}

AIM_RESULT	OnNtfNeedAuth(AMVoid *pvArg, AIM_NTF_NEED_AUTH *pNtfNeedAuth)
{
	if(pNtfNeedAuth)
	{
		AMPrintf("%s >>>>>> autId: %d\n", __FUNCTION__, pNtfNeedAuth->iAuthId);
		if(pNtfNeedAuth->pvData && pNtfNeedAuth->iDataLen)
		{
			AMFILE *pFile = AMFopen("checkImg.jpg", "wb");
			AMFwrite(pNtfNeedAuth->pvData, 1, pNtfNeedAuth->iDataLen, pFile);
			AMFclose(pFile);
		}
	}
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnNtfProgress(AMVoid *pvArg, AIM_NTF_PROGRESS *pNtfProgress)
{
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspLogin(AMVoid *pvArg, AIM_RSP_LOGIN * pRspLogin)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	if(!pRspLogin->iRetCode)
		return (AIM_RESULT)JavaConnListener(pvArg, CONN_CB_LOGINOK, pIM->iTimeDiff + AMGetUpTime(NULL));
	else
		return (AIM_RESULT)JavaConnListener(pvArg, CONN_CB_LOGINFAIL, pRspLogin->eInfo);
}

AIM_RESULT	OnRspChgVerify(AMVoid *pvArg, AIM_RSP_CHG_VERIFY *pRspChgVerify)
{
	IAIMessage	*pMsg = AMNULL;
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	if(0 == pRspChgVerify->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)CHG_VERIFY_OK;
	}else
	{
		pMsg->eType = (AIM_MSG_TYPE)CHG_VERIFY_FAILE;
	}

	IAIMessage_SetContent(pMsg, "0", 1);
	pMsg->szContent[0] = '0' + pIM->pAcnt->iVerifyType;

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspChgSrvMode(AMVoid *pvArg, AIM_RSP_CHG_SRV_MODE *pRspChgSrvMode)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = AMNULL;

	AMAssert(AMNULL != pIM && AMNULL != pRspChgSrvMode);

	pMsg = IAIMessage_Create();
	if(!pRspChgSrvMode->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)CHG_SERV_MODE_OK;
		IAIMessage_SetCntID(pMsg, pIM->pAcnt->szID, AMStrlen(pIM->pAcnt->szID));
		DPRINT("IASessionModel_OnHelpChgSrvMode........CHG_SERV_MODE_OK %s, %s\n", pMsg->szContactID, pMsg->szContent);
	}
	else
	{
		pMsg->eType = (AIM_MSG_TYPE)CHG_SERV_MODE_FAIL;
		DPRINT("IASessionModel_OnHelpChgSrvMode........CHG_SERV_MODE_FAIL %d!\n", pRspChgSrvMode->iRetCode);
	}

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	DPRINT("IASessionModel_OnHelpChgSrvMode.........................OK!\n");

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspChgSignature(AMVoid *pvArg, AIM_RSP_CHG_SIGNATURE *pRspChgSignature)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = 0;

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	if(!pRspChgSignature->iRetCode)
	{
		pMsg->eType	= (AIM_MSG_TYPE)CHG_SIGNATURE_OK;
		IAIMessage_SetContent(pMsg, pIM->pAcnt->szSignature, AMStrlen(pIM->pAcnt->szSignature));
		DPRINT("IAIM_OnChgSignature..............%s\n", pIM->pAcnt->szSignature);
	}
	else
	{
		pMsg->eType	= (AIM_MSG_TYPE)CHG_SIGNATURE_FAIL;
		DPRINT("IAIM_OnChgSignature...................Faile!\n");
	}

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspAddContact(AMVoid *pvArg, AIM_RSP_ADD_CONTACT *pRspAddContact)
{
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspDelContact(AMVoid *pvArg, AIM_RSP_DEL_CONTACT *pRspDelContact)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage *pMsg = AMNULL;
	if(!pRspDelContact->iRetCode && pRspDelContact->szContactId)
	{
		pMsg = IAIMessage_Create();
		pMsg->bUnread = AMTRUE;
		pMsg->eType = (AIM_MSG_TYPE)REMOVE_CNT_SUCESS;

		IAIMessage_SetCntID(pMsg, pRspDelContact->szContactId, AMStrlen(pRspDelContact->szContactId));

		Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);
		IAIMessage_Destroy(pMsg);
	}
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspAccept(AMVoid *pvArg, AIM_RSP_ACCEPT *pRspAccept)
{
	return eAIM_RESULT_OK;
}
AIM_RESULT	OnRspAddBlack(AMVoid *pvArg, AIM_RSP_ADD_BLACK *pRspAddBlack)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage *pMsg = AMNULL;

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	IAIMessage_SetCntID(pMsg, pRspAddBlack->szBlackId, AMStrlen(pRspAddBlack->szBlackId));

	if(!pRspAddBlack->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)ADD_BLK_SUCCESS;
	}
	else
	{
		pMsg->eType = (AIM_MSG_TYPE)ADD_BLK_FAILED;
	}

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspDelBlack(AMVoid *pvArg, AIM_RSP_DEL_BLACK *pRspDelBlack)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage *pMsg = AMNULL;

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	IAIMessage_SetCntID(pMsg, pRspDelBlack->szBlackId, AMStrlen(pRspDelBlack->szBlackId));

	if(!pRspDelBlack->iRetCode)
	{
		pMsg->eType = (AIM_MSG_TYPE)REMOVE_BLK_SUCESS;
	}
	else
	{
		pMsg->eType = (AIM_MSG_TYPE)REMOVE_BLK_FAILED;
	}

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);
	
	return eAIM_RESULT_OK;
}
AIM_RESULT	OnRspGetVerify(AMVoid *pvArg, AIM_RSP_GET_VERIFY *pRspGetVerify)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = 0;
	AMChar		szBuf[20] = {0};

	AMAssert(NULL != pIM && NULL != pIM->pAcnt);

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = (AIM_MSG_TYPE)GET_PEER_ADD_VERIFY;
	IAIMessage_SetCntID(pMsg, pRspGetVerify->szContactId, AMStrlen(pRspGetVerify->szContactId));

	_AIMItoa(pRspGetVerify->iRetCode, szBuf);
	IAIMessage_SetContent(pMsg, szBuf, AMStrlen(szBuf));
	DPRINT("IASessionModel_OnPeerVerifyConfig..............%s\n", pMsg->szContent);	

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	return eAIM_RESULT_OK;
}

#define UID_KEYWROD_ID	"uid"
AIM_RESULT	OnRspGetProfile(AMVoid *pvArg, AIM_RSP_GET_PROFILE *pRspGetProfile)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = 0;
	AMInt32 iContentLen = 0, i = 0, iPos = 0, iLen = 0;;
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = (AIM_MSG_TYPE)GET_PEER_UDB_PROFILE;
	IAIMessage_SetCntID(pMsg, pRspGetProfile->szContactId, AMStrlen(pRspGetProfile->szContactId));

	iContentLen = pRspGetProfile->iTotalLen + 4 + AMStrlen(pRspGetProfile->szContactId) + sizeof(UID_KEYWROD_ID);
	iContentLen +=  pRspGetProfile->iCount*2;

	pMsg->szContent = (AMChar *)AMMalloc(iContentLen);
	if(AMNULL == pMsg->szContent)
	{
		IAIMessage_Destroy(pMsg);
		return eAIM_RESULT_NOT_READY;
	}
	AMMemset(pMsg->szContent, 0, iContentLen);

	for(i=0; i<pRspGetProfile->iCount; i++)
	{
		if(AMNULL != pRspGetProfile->pszValues[i])
		{
			iLen = AMStrlen(pRspGetProfile->pszKeys[i]);
			AMMemcpy(pMsg->szContent+iPos, pRspGetProfile->pszKeys[i], iLen);
			iPos += iLen;
			pMsg->szContent[iPos++] = '\1';
			iLen = AMStrlen(pRspGetProfile->pszValues[i]);
			AMMemcpy(pMsg->szContent+iPos, pRspGetProfile->pszValues[i], iLen);
			iPos += iLen;
			pMsg->szContent[iPos++] = '\1';
		}
	}

	AMMemcpy(pMsg->szContent+iPos, UID_KEYWROD_ID, sizeof(UID_KEYWROD_ID)-1);//加上"uid\1'contactId'"
	iPos += sizeof(UID_KEYWROD_ID)-1;
	pMsg->szContent[iPos++] = '\1';

	AMStrcat(pMsg->szContent+iPos, pRspGetProfile->szContactId);//不需要尾巴了

	DPRINT("IASessionModel_OnPeerVerifyConfig.................%s\n", pMsg->szContent);	

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspGetDegree(AMVoid *pvArg, AIM_RSP_GET_DEGREE *pRspGetDegree)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = AMNULL;
	AMChar		*pBuf = AMNULL;
	AMInt32		iLen = 0;

	AMAssert(AMNULL != pIM && AMNULL != pRspGetDegree);

	DPRINT("IASessionModel_OnGetDegree.........................Entering!\n");

	pMsg = IAIMessage_Create();
	if(pRspGetDegree->szContactId)
		IAIMessage_SetCntID(pMsg, pRspGetDegree->szContactId, AMStrlen(pRspGetDegree->szContactId));

	if(0 == pRspGetDegree->iRetCode)//成功
	{
		pMsg->eType = (AIM_MSG_TYPE)GET_DEGREE_OK;
		pBuf = (AMChar *)AMMalloc(MAX_INT_NUMBER_LEN*3);
		if(AMNULL == pBuf)
		{
			IAIMessage_Destroy(pMsg);
			return eAIM_RESULT_MALLOC_ERROR;
		}
		AMMemset(pBuf, 0, MAX_INT_NUMBER_LEN*3);
		iLen += _AIMItoa(pRspGetDegree->iUserLevel, pBuf);
		pBuf[iLen++] = ',';
		iLen += _AIMItoa(pRspGetDegree->iTotalDegree, pBuf+iLen);
		pBuf[iLen++] = ',';
		iLen += _AIMItoa(pRspGetDegree->iNeedDegree, pBuf+iLen);
		pMsg->szContent	= pBuf;
	}
	else//失败
	{
		DPRINT("IASessionModel_OnGetDegree.......................Fail!\n");
		pMsg->eType = (AIM_MSG_TYPE)GET_DEGREE_FAIL;
	}

	DPRINT("IASessionModel_OnGetDegree.......................%s\n", pMsg->szContent);	

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	DPRINT("IASessionModel_OnGetDegree.........................OK!\n");

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspGetMemo(AMVoid *pvArg, AIM_RSP_GET_MEMO *pRspGetMemo)
{
	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	IAIMessage	*pMsg = AMNULL;
	AMChar		*pBuf = AMNULL;
	AMInt32		iLen = 0;

	AMAssert(AMNULL != pIM && AMNULL != pRspGetMemo);

	DPRINT("IASessionModel_OnGetCntMemo.........................Entering!\n");

	pMsg = IAIMessage_Create();
	if(pRspGetMemo->szContactId)
		IAIMessage_SetCntID(pMsg, pRspGetMemo->szContactId, AMStrlen(pRspGetMemo->szContactId));

	if(0 == pRspGetMemo->iRetCode)//成功
	{
		pMsg->eType = (AIM_MSG_TYPE)GET_CNTMEMO_OK;
		IAIMessage_SetContent(pMsg, pRspGetMemo->szMemo, AMStrlen(pRspGetMemo->szMemo));
	}
	else//失败
	{
		pMsg->eType = (AIM_MSG_TYPE)GET_CNTMEMO_FAIL;
	}

	DPRINT("IASessionModel_OnGetCntMemo.......................%s\n", pMsg->szContent);	

	Adapter_OnIncomingSysMsg(pIM->pSesModel, pMsg, pvArg);

	IAIMessage_Destroy(pMsg);

	DPRINT("IASessionModel_OnGetCntMemo.........................OK!\n");

	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspGetSignature(AMVoid *pvArg, AIM_RSP_GET_SIGNATURE *rspGetSignature)
{	
	AIM_CONTACT_UPDATE_DATA	*pPresent = 0;
	AMInt32 i=0;

	IAIM *pIM = (IAIM*)(((AMPVoid*)pvArg)[1]);
	if(!rspGetSignature->iRetCode)
	{
		pPresent = (AIM_CONTACT_UPDATE_DATA	*)AMMalloc(sizeof(AIM_CONTACT_UPDATE_DATA) * rspGetSignature->iCount);
		AMMemset(pPresent, 0, sizeof(AIM_CONTACT_UPDATE_DATA) * rspGetSignature->iCount);
		for(i=0; i<rspGetSignature->iCount; i++)
		{
			pPresent[i].iFlag = 0;
			pPresent[i].szID = rspGetSignature->pszContactIds[i];
			pPresent[i].szSignature = rspGetSignature->pszValues[i];
			pPresent[i].ucType = eAIM_CONTACT_SIGNATURE;
		}

		JavaPreListener(pvArg, pPresent, rspGetSignature->iCount);
		AMFree(pPresent);
	}
	else
	{
		AMAssert(pIM && pIM->pAcnt);
		AMAssert(rspGetSignature->pszContactIds);
		DPRINT("OnRspGetSignature................Fail: %s\n", *(rspGetSignature->pszContactIds));
		if(0 == AMStrcmp(pIM->pAcnt->szID, *(rspGetSignature->pszContactIds)))
		{
			DPRINT("OnRspGetSignature................Fail: %s\n", *(rspGetSignature->pszContactIds));
			//pIM->pAcnt->bGetSigFail = AMTRUE;
		}
		else
		{
			DPRINT("OnRspGetSignature.....................Acnt %s\n", pIM->pAcnt->szID);
		}
	}
	return eAIM_RESULT_OK;
}

AIM_RESULT	OnRspGetPortrait(AMVoid *pvArg, AIM_RSP_GET_PROTRAIT *rspGetPortrait)
{
	AIM_CONTACT_UPDATE_DATA	*pPresent = 0;
	AMInt32 i=0;
	if(!rspGetPortrait->iRetCode)
	{
		pPresent = (AIM_CONTACT_UPDATE_DATA	*)AMMalloc(sizeof(AIM_CONTACT_UPDATE_DATA));
		pPresent->szID = rspGetPortrait->szContactId;
		pPresent->szSignature = rspGetPortrait->szValue;
		pPresent->ucType = 2;

		JavaPreListener(pvArg, pPresent, 1);
		AMFree(pPresent);
	}	
	return eAIM_RESULT_OK;
}

// AIM_RESULT	OnRspSendMsg(AMVoid *, AIM_RSP_SEND_MSG *);
// AIM_RESULT	OnRspChgPresence(AMVoid *, AIM_RSP_CHG_PRESENCE *);
AIM_RESULT	OnRspFile(AMVoid *pvArg, AIM_RSP_FILE *a)
{
	return eAIM_RESULT_OK;
}
