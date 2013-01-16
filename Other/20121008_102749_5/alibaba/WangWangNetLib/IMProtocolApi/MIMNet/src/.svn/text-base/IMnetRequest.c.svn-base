
#include "IMnetRequest.h"
#include "IMnetMain.h"
#include "PCEvent.h"
#include "IMnetUtility.h"
#include "stdio.h"

void IMnetGetBindInfo(IMnet* pIMnet, AMChar **szBindID, AMInt32 *len)
{
	if(szBindID && len)
	{
		*szBindID = pIMnet->szBindUser;
		*len = pIMnet->nBindUserLen;

		pIMnet->szBindUser = NULL;
		pIMnet->nBindUserLen = 0;
	}
}

/************************************************************************/
// local static function declare.
/************************************************************************/
static IMnetRetCode IMnetSendMsgAddContact(IMnetHandle hIMnetHandle, AMChar* contactID,
										   AMInt32 groupIDHigh, AMInt32 groupIDLow, 
										   AMChar* verifyInfo, AMChar* displayName,
										   SecondProtocolId cmd);

static IMnetRetCode IMnetAddContactACK(IMnetHandle hIMnetHandle, AMInt8 opCode, 
									   AMChar* contactID, AMInt32 groupIDHigh, AMInt32 groupIDLow, const AMChar *szMessage);
/************************************************************************/
// IM Net Request Service
/************************************************************************/
IMnetRetCode IMnetLogin(IMnetHandle hIMnetHandle, AMChar* name, AMChar* password, AMInt32 bIsToken,
						AMInt32 contactStamp, AMInt32 groupStamp, 
						AMInt32 blackListStamp, AMInt32 revBlackListStamp)
{
    IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqCheckVersion checkVersion;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(name == NULL || password == NULL)
		return eInvalidParam;

	if(pIMnet)
	{
		memset(&checkVersion, 0, sizeof(checkVersion));
		memcpy(checkVersion.version, IM_PROTOCOL_VERSION, sizeof(IM_PROTOCOL_VERSION));//sizeof(checkVersion.version));		//yanlong.shiyl
        memcpy(pIMnet->pVarKeeper->userName, name, strlen(name)+1);//sizeof(pIMnet->pVarKeeper->userName));				//yanlong.shiyl
        memcpy(pIMnet->pVarKeeper->password, password, strlen(password)+1);//sizeof(pIMnet->pVarKeeper->password));		//yanlong.shiyl
		
		pIMnet->pVarKeeper->bIsToken = bIsToken;
		pIMnet->pVarKeeper->loginStamp.contactStamp = contactStamp;
		pIMnet->pVarKeeper->loginStamp.groupStamp = groupStamp;
		pIMnet->pVarKeeper->loginStamp.blackListStamp = blackListStamp;
		pIMnet->pVarKeeper->loginStamp.revBlackListStamp = revBlackListStamp;
		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_CHECKVERSION, (void*)&checkVersion, sizeof(checkVersion));
        if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
    else
    {
        retCode = eNotReady;
    }
    
    return retCode;
}

/************************************************************************/
// IMnetReLogin
/************************************************************************/
IMnetRetCode IMnetReLogin(IMnetHandle hIMnetHandle, AMChar* name, AMChar* password, 
						  AMInt8 basicStatus, AMInt8 predefStatus)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqReLogin request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(name == NULL || password == NULL)
		return eInvalidParam;
	
	if(pIMnet)
	{
		//保存最新用户名和密码
		memcpy(pIMnet->pVarKeeper->userName, name, sizeof(pIMnet->pVarKeeper->userName));
		memcpy(pIMnet->pVarKeeper->password, password, sizeof(pIMnet->pVarKeeper->password)); 
		
		//构造Request.
		memset(&request, 0, sizeof(request));
		request.basicStatus = basicStatus;
		request.connectNo = pIMnet->pVarKeeper->connectNo;
		request.predefStatus = predefStatus;
		memcpy(request.version, IM_PROTOCOL_VERSION, sizeof(request.version));
		request.reserved = 1;
		strcpy(request.extData, name);
		memcpy(request.password, password, sizeof(request.password));		
		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_RELOGIN, (void*)&request, sizeof(request));
        if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

static void FreeIMnetLogin2(EventContent* pContent)
{
	ImReqLogin2* pMsg = (ImReqLogin2*)pContent;
	AMFree(pMsg->remark);
	//其他的暂时没有用到.
}

IMnetRetCode IMnetLogin2(IMnetHandle hIMnetHandle, const AMChar *szRemark)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqLogin2 login2;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(pIMnet)
	{
		AMInt32 iRemarkLen = 0;
		memset(&login2, 0, sizeof(login2));
	
		if(szRemark)
			iRemarkLen = strlen(szRemark);

		login2.remark = (AMChar *)AMMalloc(iRemarkLen + 1);
		if(!login2.remark)
			return eNotReady;

		strncpy(login2.remark, szRemark, iRemarkLen);
		login2.remark[iRemarkLen] = 0;

		login2.timestampFlag = 15;
		login2.timestampList[0] = pIMnet->pVarKeeper->loginStamp.groupStamp;
		login2.timestampList[1] = pIMnet->pVarKeeper->loginStamp.contactStamp;
		login2.timestampList[2] = pIMnet->pVarKeeper->loginStamp.blackListStamp;
		login2.timestampList[3] = pIMnet->pVarKeeper->loginStamp.revBlackListStamp;	

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_LOGIN2, 
								(void*)&login2, sizeof(login2), FreeIMnetLogin2);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}

/************************************************************************/
// IMnetPostLogin
/************************************************************************/
IMnetRetCode IMnetPostLogin(IMnetHandle hIMnetHandle, AMInt8 basicStatus, AMInt8 predefStatus)
{
    IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqPostLogin postLogin;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(pIMnet)
	{
		memset(&postLogin, 0, sizeof(postLogin));
		IMnetGetBindInfo(pIMnet, &postLogin.bindID, &postLogin.bindIDLen);
		postLogin.basicStatus = basicStatus;
		postLogin.predefStatus = predefStatus;
		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_POSTLOGIN, (void*)&postLogin, sizeof(postLogin));
        if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
    else
    {
        retCode = eNotReady;
    }
    
    return retCode;
}
/************************************************************************/
// IMnetCommonSimple
/************************************************************************/
IMnetRetCode IMnetCommonSimple(IMnetHandle hIMnetHandle, EventId id)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqCommonSimple request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(pIMnet)
	{
		memset(&request, 0, sizeof(request));
		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, id, (void*)&request, sizeof(request));
        if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}
/************************************************************************/
// IMnetSendHealthCheck
/************************************************************************/
IMnetRetCode IMnetSendHealthCheck(IMnetHandle hIMnetHandle)
{
	return IMnetCommonSimple(hIMnetHandle, IM_HEALTH_CHECK);
}

/************************************************************************/
// IMnetLogoff
/************************************************************************/
IMnetRetCode IMnetLogoff(IMnetHandle hIMnetHandle)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	pIMnet->pVarKeeper->bIsToken = 0;
	memset(pIMnet->pVarKeeper->userName, 0, sizeof(pIMnet->pVarKeeper->userName));
	memset(pIMnet->pVarKeeper->password, 0, sizeof(pIMnet->pVarKeeper->password));

	return IMnetCommonSimple(hIMnetHandle, IM_REQ_LOGOFF);
}

/************************************************************************/
// IMnetAddBlack
/************************************************************************/
IMnetRetCode IMnetAddBlack(IMnetHandle hIMnetHandle, AMChar* contactID)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqAddBlack reqAddBlack;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(contactID == NULL)
		return eInvalidParam;
	
	if(pIMnet)
	{
		memset(&reqAddBlack, 0, sizeof(reqAddBlack));
		memcpy(reqAddBlack.contactID, contactID, sizeof(reqAddBlack.contactID));
		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_ADDBLACK, (void*)&reqAddBlack, sizeof(reqAddBlack));
        if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetAddContact
/************************************************************************/
void FreeIMnetAddContact(EventContent* pContent)
{
	ImReqAddContact* pMsg = (ImReqAddContact*)pContent;
	AMFree(pMsg->contactInfo.contactID);
	pMsg->contactInfo.contactID = NULL;
	AMFree(pMsg->szMessage);
	//其他的暂时没有用到.
}

IMnetRetCode IMnetAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMInt32 groupIDHigh, AMInt32 groupIDLow, AMInt32 type, const AMChar *szMsg)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqAddContact reqAddContact;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length = 0, msgLen = 0; 
	
	if(contactID == NULL)
		return eInvalidParam;
	
	length = strlen(contactID); 
	if(szMsg)
		msgLen = strlen(szMsg);
	if(pIMnet != NULL && length != 0)
	{
		memset(&reqAddContact, 0, sizeof(reqAddContact));
		
		IMnetGetBindInfo(pIMnet, &reqAddContact.bindID, &reqAddContact.bindIDLen);

		reqAddContact.contactInfo.contactID = (AMChar*)AMMalloc(length);

		if(szMsg)
			reqAddContact.szMessage = (AMChar *)AMMalloc(msgLen);
		if(reqAddContact.contactInfo.contactID && (!szMsg || reqAddContact.szMessage))
		{
			reqAddContact.contactInfo.contactIDLen = length;
			reqAddContact.uiMsgLen = msgLen;
			memcpy(reqAddContact.contactInfo.contactID, contactID, length);
			memcpy(reqAddContact.szMessage, szMsg, msgLen);
			reqAddContact.type = type;
			
			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_ADDCONTACT, (void*)&reqAddContact, sizeof(reqAddContact), FreeIMnetAddContact);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			AMFree(reqAddContact.szMessage);
			AMFree(reqAddContact.contactInfo.contactID);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

void FreeIMnetGetPeerInfo(EventContent* pContent)
{
	ImReqGetPeerInfo* pMsg = (ImReqGetPeerInfo*)pContent;
	if(pMsg->contactId)
	{
		AMFree(pMsg->contactId);
		pMsg->contactId = NULL;
	}
}


IMnetRetCode IMnetGetPeerInfo(IMnetHandle hIMnetHandle, const AMChar *szContactID)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqGetPeerInfo request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == szContactID)
		return eInvalidParam;

	memset(&request, 0, sizeof(ImReqGetPeerInfo));

	request.contactIdLen = strlen(szContactID);

	request.contactId = (AMChar *)AMMalloc(request.contactIdLen + 1);
	if(request.contactId)
	{
		AMMemset(request.contactId, 0, request.contactIdLen + 1);
		AMMemcpy(request.contactId, szContactID, request.contactIdLen);

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_PEERINFO, (void*)&request, sizeof(request), FreeIMnetGetPeerInfo);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		return eMallocError;
	}

	return retCode;
}

void FreeIMnetGetUserUDBProfile(EventContent* pContent)
{
	ImReqGetUserUDBProfile *pRsq = (ImReqGetUserUDBProfile *)pContent;
	if(pRsq->contactId)
	{
		AMFree(pRsq->contactId);
		pRsq->contactId = NULL;
	}
}

IMnetRetCode IMnetGetUserUDBProfile(IMnetHandle hIMnetHandle, const AMChar *szContactID)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqGetUserUDBProfile request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == szContactID)
		return eInvalidParam;

	memset(&request, 0, sizeof(request));

	request.contactIdLen = strlen(szContactID);

	request.contactId = (AMChar *)AMMalloc(request.contactIdLen + 1);
	if(request.contactId)
	{
		AMMemset(request.contactId, 0, request.contactIdLen + 1);
		AMMemcpy(request.contactId, szContactID, request.contactIdLen);

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GET_USERUDBPROFILE, (void*)&request, sizeof(request), FreeIMnetGetUserUDBProfile);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		return eMallocError;
	}

	return retCode;
}

void FreeIMnetSearchUser(EventContent* pContent)
{
	ImReqSearchUser *pRsq = (ImReqSearchUser *)pContent;
	if(pRsq->keyWord)
	{
		AMFree(pRsq->keyWord);
		pRsq->keyWord = NULL;
	}
	
	if(pRsq->reserve)
	{
		AMFree(pRsq->reserve);
		pRsq->reserve = NULL;
	}
}

IMnetRetCode IMnetSearchUser(IMnetHandle hIMnetHandle, const AMChar *szKeyWord)
{

#ifdef AMOS_DEBUG
	AMPrintf("IMnetSearchUser() start");
#endif

	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqSearchUser request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == szKeyWord)
	{
		return eInvalidParam;
	}

	memset(&request, 0, sizeof(request));

	request.timeStamp = 0;
	request.syncAcc = 0;
	request.searchType = 0;

	request.reserveLen = 0;
	request.reserve = (AMChar *)AMMalloc(request.reserveLen + 1);
	if(request.reserve)
	{
		AMMemset(request.reserve, 0, request.reserveLen + 1);
	}

	request.keyWordLen = strlen(szKeyWord);
	request.keyWord = (AMChar *)AMMalloc(request.keyWordLen + 1);
	if(request.keyWord)
	{
		AMMemset(request.keyWord, 0, request.keyWordLen + 1);
		AMMemcpy(request.keyWord, szKeyWord, request.keyWordLen);

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_SEARCHUSER, (void*)&request, sizeof(request), FreeIMnetSearchUser);
		if(retCode == eOK)
		{
			PacketConnectionSend(pEvent);

#ifdef AMOS_DEBUG
			AMPrintf("IMnetSearchUser() end");
#endif
		}
	}
	else
	{
		return eMallocError;
	}

	return retCode;
}


void FreeIMnetGetPeerVerifyConfig(EventContent* pContent)
{
	ImReqGetPeerVerifyConfig* pMsg = (ImReqGetPeerVerifyConfig*)pContent;
	if(pMsg->contactId)
	{
		AMFree(pMsg->contactId);
		pMsg->contactId = NULL;
	}
}


IMnetRetCode IMnetGetPeerVerifyConfig(IMnetHandle hIMnetHandle, const AMChar *szContactID, AMInt32 iClientId)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqGetPeerVerifyConfig request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == szContactID)
		return eInvalidParam;

	memset(&request, 0, sizeof(ImReqGetPeerVerifyConfig));

	request.contactIdLen = strlen(szContactID);

	request.contactId = (AMChar *)AMMalloc(request.contactIdLen + 1);
	if(request.contactId)
	{
		AMMemset(request.contactId, 0, request.contactIdLen + 1);
		AMMemcpy(request.contactId, szContactID, request.contactIdLen);

		request.clientId = iClientId;
		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GET_PEER_VERIFY_CONFIG, (void*)&request, sizeof(request), FreeIMnetGetPeerVerifyConfig);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		return eMallocError;
	}

	return retCode;
}

/************************************************************************/
// IMnetChangeSignature
/************************************************************************/
void FreeIMnetChangeSignature(EventContent* pContent)
{
	ImReqChangeSignature* pRequest = (ImReqChangeSignature*)pContent;
	AMFree(pRequest->signature);
	pRequest->signature = NULL;
}

IMnetRetCode IMnetChangeSignature(IMnetHandle hIMnetHandle, AMChar* signature)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqChangeSignature request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length; 
	
	if(signature == NULL)
		return eInvalidParam;
	
	length = strlen(signature); 
	if(pIMnet != NULL)// && length != 0)
	{
		memset(&request, 0, sizeof(request));
		
		request.signature = (AMChar*)AMMalloc(length);
		if(request.signature)
		{
			request.signatureLen = length;
			memcpy(request.signature, signature, length);
			
			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_CHGSIGNATURE, (void*)&request, sizeof(request), FreeIMnetChangeSignature);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetChangeStatus
/************************************************************************/
IMnetRetCode IMnetChangeStatus(IMnetHandle hIMnetHandle, AMInt8 basicStatus, AMInt8 predefStatus)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqChangeStatus request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(pIMnet)
	{
		memset(&request, 0, sizeof(request));
		request.basicStatus = basicStatus;
		request.predefStatus = predefStatus;

		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_CHGSTATUS, (void*)&request, sizeof(request));
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetChangeVerifyType
/************************************************************************/
IMnetRetCode IMnetChangeVerifyType(IMnetHandle hIMnetHandle, AMInt8 type)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqChangeUserVerify request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(pIMnet)
	{
		memset(&request, 0, sizeof(request));

		IMnetGetBindInfo(pIMnet, &request.bindID, &request.bindIDLen);
		request.addcontactFlag	= type;
		request.sendmsgFlag		= 0; //SEND_DEFAULT_FLAG_ZERO = 0;
		request.enableSearch	= 1; //SEND_DEFAULT_FLAG_ONE  = 1;

		
		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_CHGUSERVERIFY, (void*)&request, sizeof(request));
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetDeleteOfflineMsg
/************************************************************************/
IMnetRetCode IMnetDeleteOfflineMsg(IMnetHandle hIMnetHandle, AMInt32 lastTime)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqDeleteOfflineMsg request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(pIMnet)
	{
		memset(&request, 0, sizeof(request));
		request.lastTime = lastTime;
		IMnetGetBindInfo(pIMnet, &request.bindID, &request.bindIDLen);

		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_DELOFFLINEMSG, (void*)&request, sizeof(request));
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetDeleteBlack
/************************************************************************/
void FreeIMnetDeleteBlack(EventContent* pContent)
{
	ImReqDeleteBlack* pRequest = (ImReqDeleteBlack*)pContent;
	AMFree(pRequest->blackId);
	pRequest->blackId = NULL;
}

IMnetRetCode IMnetDeleteBlack(IMnetHandle hIMnetHandle, AMChar* contactID)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqDeleteBlack request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length; 
	
	if(contactID == NULL)
		return eInvalidParam;
	
	length = strlen(contactID); 
	if(pIMnet != NULL && length != 0)
	{
		memset(&request, 0, sizeof(request));
		
		request.blackId = (AMChar*)AMMalloc(length);
		if(request.blackId)
		{
			request.blackIdLen = length;
			memcpy(request.blackId, contactID, length);
			
			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_DELBLACK, (void*)&request, sizeof(request), FreeIMnetDeleteBlack);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetCommonContactList
/************************************************************************/
void FreeIMnetCommonContactList(EventContent* pContent)
{
	ImReqCommonContactList* pRequest = (ImReqCommonContactList*)pContent;
	ContactList* pList = NULL;
	ContactList* pCurrentList = NULL;
	
	//需要释放里面已经申请的内存
	pCurrentList = pRequest->pContactList;
	while(pCurrentList != NULL)
	{
		pList		 = pCurrentList->pNext;
		AMFree(pCurrentList->userID);
		AMFree(pCurrentList);
		pCurrentList = pList;
	}
	pRequest->pContactList = NULL;
}

IMnetRetCode IMnetCommonContactList(IMnetHandle hIMnetHandle, ContactList* pContactList, EventId id)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqCommonContactList request;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	ContactList* pList = NULL;
	AMChar*		 pUserID = NULL;
	ContactList* pCurrentList = pContactList;
	ContactList* pRequestCurrentList = NULL;
	
	if(pContactList == NULL)
		return eInvalidParam;
	
	if(pIMnet != NULL && pContactList != NULL)
	{
		memset(&request, 0, sizeof(request));
		
		IMnetGetBindInfo(pIMnet, &request.bindID, &request.bindIDLen);

		//将外部传入的数据复制一份
		while(pCurrentList)
		{
			pList = NULL;
			pList = (ContactList*)AMMalloc(sizeof(ContactList));
			if(pList == NULL)
			{
				FreeIMnetCommonContactList((EventContent*)&request);
				AMAssert(0);
				return eMallocError;
			}
			memset(pList, 0, sizeof(ContactList));
			
			//预留一个'\0'位.
			pUserID = (AMChar*)AMMalloc(pCurrentList->userIDLen+1);
			if(pUserID == NULL)
			{
				AMFree(pList);
				FreeIMnetCommonContactList((EventContent*)&request);
				AMAssert(0);
				return eMallocError;
			}
			
			memset(pUserID, 0, pCurrentList->userIDLen+1);
			memcpy(pUserID, pCurrentList->userID, pCurrentList->userIDLen);
			pList->userID = pUserID;
			pList->userIDLen = pCurrentList->userIDLen;
			
			if(request.pContactList == NULL)
				request.pContactList = pList;
			else
				pRequestCurrentList->pNext = pList;
			
			pRequestCurrentList = pList;
			
			//下一个待复制的联系人
			pCurrentList = pCurrentList->pNext;
		}
		
		//发送消息
		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, id, (void*)&request, sizeof(request), FreeIMnetCommonContactList);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

/************************************************************************/
// IMnetDeleteContact
/************************************************************************/
IMnetRetCode IMnetDeleteContact(IMnetHandle hIMnetHandle, ContactList* pContactList)
{            
	return IMnetCommonContactList(hIMnetHandle, pContactList, IM_REQ_DELCONTACT);
}

/************************************************************************/
// IMnetSubscribeContactInfo
/************************************************************************/
IMnetRetCode IMnetSubscribeContactInfo(IMnetHandle hIMnetHandle, ContactList* pContactList, AMInt8 type)
{
	if(type == 1)
		return IMnetCommonContactList(hIMnetHandle, pContactList, IM_REQ_SUBSCRIBE_INFO);
	else
		return IMnetCommonContactList(hIMnetHandle, pContactList, IM_REQ_DISUBSCRIBE_INFO);
}

/************************************************************************/
// IMnetSendMessage
/************************************************************************/
void FreeImReqSendIMMessage(EventContent* pContent)
{
    ImReqSendIMMessage* pMsg = (ImReqSendIMMessage*)pContent;
	if(pMsg->bindID)
	{
		AMFree(pMsg->bindID);
		pMsg->bindID = NULL;
	}
	AMFree(pMsg->contactID);
	pMsg->contactID = NULL;
    AMFree(pMsg->message);
    pMsg->message = NULL;
}

IMnetRetCode IMnetSendMessageEx(IMnetHandle hIMnetHandle, 
								AMChar* contactID, AMInt32 contactIDLen,
								AMChar* message, AMInt32 length, AMInt32 type, 
								AMInt32 secondCmd, AMInt32 ackSeq)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqSendIMMessage sendMessage;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(contactID == NULL)
		return eInvalidParam;
	
	if(pIMnet)
	{
		memset(&sendMessage, 0, sizeof(sendMessage));

		IMnetGetBindInfo(pIMnet, &sendMessage.bindID, &sendMessage.bindIDLen);

		sendMessage.type = type;
		sendMessage.secondCmd = secondCmd;
		sendMessage.ackSeq = ackSeq;
		
		sendMessage.contactID = (AMChar*)AMMalloc(contactIDLen);
		if(sendMessage.contactID != NULL)
		{
			memset(sendMessage.contactID, 0, contactIDLen);
			memcpy(sendMessage.contactID, contactID, contactIDLen);
			sendMessage.contactIDLen = contactIDLen;
		}
		else
		{
			AMAssert(0);
			return eMallocError;
		}   
		
		//此处预留8个字节以规避协议打包中再次申请内存.
		sendMessage.messageLen = PROTOCOL_SECOND_HEAD_LENGTH + length;
		sendMessage.message = (AMChar*)AMMalloc(sendMessage.messageLen);
		if(sendMessage.message != NULL)
		{
			if(length != 0)
				memcpy(sendMessage.message+PROTOCOL_SECOND_HEAD_LENGTH, message, length);
		}
		else
		{
			AMFree(sendMessage.contactID);
			AMAssert(0);
			return eMallocError;
		}   

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_SENDIMMESSAGE, (void*)&sendMessage, sizeof(sendMessage), FreeImReqSendIMMessage);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

IMnetRetCode IMnetSendMessage(IMnetHandle hIMnetHandle, AMChar* contactID, 
							  AMChar* message, AMInt32 length, AMInt32 type)
{
	if(contactID == NULL)
		return eInvalidParam;
	else
		return IMnetSendMessageEx(hIMnetHandle, contactID, strlen(contactID), message, length, type, IMM_SP_TEXT, 0);
}

IMnetRetCode IMnetSendFileMessage(IMnetHandle hIMnetHandle, AMChar* contactID, 
								  AMChar* message, AMInt32 length, AMInt32 type)
{
	if(contactID == NULL)
		return eInvalidParam;
	else
		return IMnetSendMessageEx(hIMnetHandle, contactID, strlen(contactID), message, length, type, IMM_SP_OFFIMG, 0);

}

/************************************************************************/
// IMnetNetworkConfig
/************************************************************************/
IMnetRetCode IMnetNetworkConfig(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	if(ip == NULL)
		return eInvalidParam;
	
	if(pIMnet)
	{
		PacketConnectionClose(pIMnet->hPCHandle);

		return PacketConnectionOpen(pIMnet->hPCHandle, ip, port, sync);
	}
	else
	{
		return eNotReady;
	}
}

/************************************************************************/
// 功能简介: 添加一个组
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		AMChar* groupName		:[IN] 添加的组名
//		AMInt32 parentGroupIDup :[IN] 添加的组的父亲的组ID 高32位
//		AMInt32 parentGroupIDLow :[IN] 添加的组的父亲的组ID 低32位
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetAddGroup(IMnetHandle hIMnetHandle, AMChar* groupName, 
						   AMInt32 parentGroupIDHigh, AMInt32 parentGroupIDLow)
{
	IMnetRetCode retCode = eOK;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	return retCode;
}

/************************************************************************/
// 功能简介: 
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		ContactList* pContactList: [IN]用户列表
//		AMInt8 type				 : [IN] 1表示订阅, 0表示取消订阅
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetDeleteGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, AMInt32 groupIDLow)
{
	IMnetRetCode retCode = eOK;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	return retCode;
}

/************************************************************************/
// 功能简介: 
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		AMInt32 groupIDHigh		:[IN] 组id高32位
//		AMInt32 groupIDLow		:[IN] 组id低32位
//		AMChar* groupName		:[IN] 修改后的组名
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetRenameGroup(IMnetHandle hIMnetHandle, AMInt32 groupIDHigh, 
							  AMInt32 groupIDLow, AMChar* groupName)
{
	IMnetRetCode retCode = eOK;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	return retCode;
}

/************************************************************************/
// 功能简介: 
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		AMChar* contactID		:[IN] 目标用户
//		AMChar* displayName		:[IN] 显示名
//		AMChar* verifyInfo		:[IN] 验证信息
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetSendVerifyInfo(IMnetHandle hIMnetHandle, AMChar* contactID, 
								 AMChar* displayName, AMChar* verifyInfo)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	//此处的type定义为1. 表示需要验证
	return IMnetAddContact(hIMnetHandle, contactID, 0, 0, 1, verifyInfo);
}

/************************************************************************/
// 功能简介: 
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		AMChar* contactID		:[IN] 目标用户
//		AMChar* rejectReason	:[IN] 拒绝原因
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetRejectAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, AMChar* rejectReason)
{
	return IMnetAddContactACK(hIMnetHandle, 1, contactID, 0, 0, rejectReason);
}

/************************************************************************/
// 功能简介: 
// 参数说明: 
//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
//		AMChar* contactID		:[IN] 目标用户
//		AMInt32 groupIDHigh		:[IN] 用户组ID高32位
//		AMInt32 groupIDLow		:[IN] 用户组ID低32位
// 返回值  : IMnetRetCode: eOK成功,其他失败.
/************************************************************************/
IMnetRetCode IMnetAcceptAddContact(IMnetHandle hIMnetHandle, AMChar* contactID, 
								   AMInt32 groupIDHigh, AMInt32 groupIDLow)
{
	return IMnetAddContactACK(hIMnetHandle, 0, contactID, groupIDHigh, groupIDLow, AMNULL);
}

/************************************************************************/
// IMnetSendMsgAddContact
/************************************************************************/
IMnetRetCode IMnetSendMsgAddContact(IMnetHandle hIMnetHandle, AMChar* contactID,
									AMInt32 groupIDHigh, AMInt32 groupIDLow, 
									AMChar* verifyInfo, AMChar* displayName,
									SecondProtocolId cmd)
{
	AMChar* pMessage = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length = 0;
	AMInt32 contactIDLen = 0;
	AMInt32 verifyInfoLen = 0;
	AMInt32 displayNameLen = 0;
	
	if(contactID == NULL)
		return eInvalidParam;
	else
		contactIDLen = strlen(contactID);
	
	if(verifyInfo == NULL)
		verifyInfoLen = 0;
	else
		verifyInfoLen = strlen(verifyInfo);
	
	if(displayName == NULL)
		displayNameLen = 0;
	else
		displayNameLen = strlen(displayName);
	
	// 构造二级子协议
	MakeXMLString(&pMessage, &length, 
		pIMnet->pVarKeeper->userName, strlen(pIMnet->pVarKeeper->userName), 
		contactID, contactIDLen,
		0, 0, 
		verifyInfo, verifyInfoLen, 
		displayName, displayNameLen, 
		(AMInt32)cmd);
	
	if(pMessage != NULL)
	{
		//send一级协议
		IMnetSendMessageEx(hIMnetHandle, 
			contactID, contactIDLen, 
			pMessage, length, 1, IMM_SP_CONTACT, 0);
	}
	
	FreeXMLString(&pMessage);
	
	return eOK;
}

void FreeIMnetGetDegree(EventContent* pContent)
{
	ImReqGetDegree	*pGetDegree = (ImReqGetDegree*)pContent;
	if(pGetDegree->contactId)
	{
		AMFree(pGetDegree->contactId);
		pGetDegree->contactId = NULL;
	}
}


IMnetRetCode IMnetGetDegree(IMnetHandle hIMnetHandle, AMChar *contactID)
{
	ImReqGetDegree	getDegree;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;
	AMInt32	length = 0;

	if(NULL == contactID || 0 == (length = strlen(contactID)))
		return eInvalidParam;

	if(pIMnet != NULL)
	{
		memset(&getDegree, 0, sizeof(getDegree));

		getDegree.contactId = (AMChar*)AMMalloc(length);
		if(getDegree.contactId)
		{
			memcpy(getDegree.contactId, contactID, length);
			getDegree.contactIdLen = length;

			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GET_DEGREE, (void*)&getDegree, sizeof(getDegree), FreeIMnetGetDegree);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}

void FreeIMnetGetAppAddr(EventContent* pContent)
{
	ImReqGetAppAddr	*pGetAppAddr = (ImReqGetAppAddr*)pContent;
	if(pGetAppAddr->szSessionId)
	{
		AMFree(pGetAppAddr->szSessionId);
		pGetAppAddr->szSessionId = NULL;
	}
}

IMnetRetCode IMnetGetAppAddr(IMnetHandle hIMnetHandle, const AMChar *szSessionId, AMUInt64 ulObjId)
{
	ImReqGetAppAddr	getAppAddr;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;
	AMInt32	length = 0;

	if(NULL == szSessionId || 0 == (length = strlen(szSessionId)))
		return eInvalidParam;

	if(pIMnet != NULL)
	{
		memset(&getAppAddr, 0, sizeof(getAppAddr));

		getAppAddr.szSessionId = (AMChar*)AMMalloc(length);
		if(getAppAddr.szSessionId)
		{
			memcpy(getAppAddr.szSessionId, szSessionId, length);
			getAppAddr.iSessionIdLen = length;

			getAppAddr.uiAppType = 1;
			getAppAddr.uiSubType = 3;
			getAppAddr.ulObjId = ulObjId;

			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GET_APP_ADDR, (void*)&getAppAddr, sizeof(getAppAddr), FreeIMnetGetAppAddr);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}


IMnetRetCode IMnetGetContactMemo(IMnetHandle hIMnetHandle, AMChar *contactID)
{
	ImReqGetContactMemo	getContactMemo;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == contactID || 0 == strlen(contactID))
		return eInvalidParam;
	
	if(pIMnet != NULL)
	{
		memset(&getContactMemo, 0, sizeof(getContactMemo));

		strcpy(getContactMemo.contactID, contactID);

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GETCNTMEMO, (void*)&getContactMemo, sizeof(getContactMemo), NULL);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}

void FreeIMnetChangeSrvMode(EventContent* pContent)
{
	ImReqHelpChangeSrvMode	*pChgSrvMode = (ImReqHelpChangeSrvMode*)pContent;
	if(pChgSrvMode->accountId)
	{
		AMFree(pChgSrvMode->accountId);
		pChgSrvMode->accountId = NULL;
	}
}

IMnetRetCode IMnetChangeSrvMode(IMnetHandle hIMnetHandle, AMUChar ucStatus)
{
	ImReqHelpChangeSrvMode	chgSrvMode;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	memset(&chgSrvMode, 0, sizeof(chgSrvMode));

	if(pIMnet && pIMnet->pVarKeeper && pIMnet->pVarKeeper->userName)
	{
		chgSrvMode.accountIdLen = strlen(pIMnet->pVarKeeper->userName);
		chgSrvMode.accountId = malloc(chgSrvMode.accountIdLen);
		chgSrvMode.status = ucStatus;
		if(chgSrvMode.accountId)
		{
			memcpy(chgSrvMode.accountId, pIMnet->pVarKeeper->userName, chgSrvMode.accountIdLen);

			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_HELP_CHG_SRV_MODE
						, (void*)&chgSrvMode, sizeof(chgSrvMode), FreeIMnetChangeSrvMode);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
			retCode = eMallocError;
	}
	else
		retCode = eNotReady;
	
	return retCode;
}

IMnetRetCode IMnetGetWebSession(IMnetHandle hIMnetHandle)
{
	ImReqGetWebSession	getWebSession;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	memset(&getWebSession, 0, sizeof(getWebSession));

	if(pIMnet != NULL)
	{
		memset(&getWebSession, 0, sizeof(getWebSession));

		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GETWEB_SESSION, (void*)&getWebSession, sizeof(getWebSession), NULL);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}

void FreeIMnetCheckAuthCode(EventContent* pContent)
{
	ImReqCheckAuthCode	*pCheckAuthCode = (ImReqCheckAuthCode*)pContent;
	if(pCheckAuthCode->szSession)
		AMFree(pCheckAuthCode->szSession);
	if(pCheckAuthCode->szCode)
		AMFree(pCheckAuthCode->szCode);
}

IMnetRetCode IMnetCheckAuthCode(IMnetHandle hIMnetHandle, const AMChar *szSession, const AMChar *szCode)
{
	ImReqCheckAuthCode	checkAuthCode;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	memset(&checkAuthCode, 0, sizeof(checkAuthCode));

	if(pIMnet && pIMnet->pVarKeeper && pIMnet->pVarKeeper->userName)
	{
		checkAuthCode.uiSessionLen = strlen(szSession);
		checkAuthCode.uiCodeLen = strlen(szCode);

		checkAuthCode.szSession = (AMChar *)AMMalloc(checkAuthCode.uiSessionLen + 1);
		checkAuthCode.szCode = (AMChar *)AMMalloc(checkAuthCode.uiCodeLen + 1);
		checkAuthCode.uiMode = 0;
		if(checkAuthCode.szSession && checkAuthCode.szCode)
		{
			strcpy(checkAuthCode.szSession, szSession);
			strcpy(checkAuthCode.szCode, szCode);
			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_CHECK_AUTHCODE
				, (void*)&checkAuthCode, sizeof(checkAuthCode), FreeIMnetCheckAuthCode);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			if(checkAuthCode.szSession)
				AMFree(checkAuthCode.szSession);
			if(checkAuthCode.szCode)
				AMFree(checkAuthCode.szCode);
			retCode = eMallocError;
		}
	}
	else
		retCode = eNotReady;

	return retCode;
}

void FreeRawPacket(EventContent* pContent)
{
	ImRawPacket	*pRawPacket = (ImRawPacket*)pContent;
	if(pRawPacket->szPacket)
	{
		AMFree(pRawPacket->szPacket);
		pRawPacket->szPacket = NULL;
	}
}

IMnetRetCode IMnetSendRawPacket(IMnetHandle hIMnetHandle, const AMChar *szPacket, AMUInt32 uiLen)
{
	ImRawPacket	rawPacket;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	memset(&rawPacket, 0, sizeof(rawPacket));

	if(pIMnet && pIMnet->pVarKeeper && pIMnet->pVarKeeper->userName)
	{
		rawPacket.uiPacketLen = uiLen;
		
		rawPacket.szPacket = (AMChar *)AMMalloc(uiLen);
		if(rawPacket.szPacket)
		{
			memcpy(rawPacket.szPacket, szPacket, uiLen);
			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_RAW_PACKET
				, (void*)&rawPacket, sizeof(rawPacket), FreeRawPacket);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else		
			retCode = eMallocError;
	}
	else
		retCode = eNotReady;

	return retCode;
}

/************************************************************************/
// IMnetAddContactACK
/************************************************************************/
void FreeIMnetAddContactACK(EventContent* pContent)
{
	ImReqAddContactACK* pMsg = (ImReqAddContactACK*)pContent;
	if(pMsg->bindID)
	{
		AMFree(pMsg->bindID);
		pMsg->bindID = NULL;
	}
	AMFree(pMsg->contactID);
	pMsg->contactID = NULL;
	AMFree(pMsg->szMessage);
	pMsg->szMessage = NULL;
}

IMnetRetCode IMnetAddContactACK(IMnetHandle hIMnetHandle, AMInt8 opCode, 
								AMChar* contactID, AMInt32 groupIDHigh, AMInt32 groupIDLow, const AMChar *szMessage)
{
	ImReqAddContactACK ack;
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length = 0, msgLen = 0; 
	
	if(contactID == NULL)
		return eInvalidParam;
	
	length = strlen(contactID);
	if(szMessage)
		msgLen = strlen(szMessage);
	if(pIMnet != NULL && length != 0)
	{
		memset(&ack, 0, sizeof(ack));
		
		IMnetGetBindInfo(pIMnet, &ack.bindID, &ack.bindIDLen);

		ack.contactID = (AMChar*)AMMalloc(length);
		if(szMessage)
			ack.szMessage = (AMChar *)AMMalloc(msgLen);
		if(ack.contactID && (!szMessage || ack.szMessage))
		{
			memcpy(ack.contactID, contactID, length);
			ack.contactIDLen = length;
			ack.uiMsgLen = msgLen;
			ack.groupIDHigh = groupIDHigh;
			ack.groupIDLow = groupIDLow;
			ack.opcode = opCode;
			if(szMessage)
				memcpy(ack.szMessage, szMessage, msgLen);

			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_ADDCNTACK, (void*)&ack, sizeof(ack), FreeIMnetAddContactACK);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			AMAssert(0);
			AMFree(ack.contactID);
			AMFree(ack.szMessage);
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}
	
	return retCode;
}

IMnetRetCode IMnetSendMsg2Callback(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer)
{
	return IMnetSendMsg2CallbackProc(hIMnetHandle, id, pMsg, uiSize, freer, AMFALSE);
}

IMnetRetCode IMnetSendMsg2CallbackProc(IMnetHandle hIMnetHandle, EventId id, AMVoid *pMsg, AMUInt32 uiSize, FreeContent freer, AMBool bLow)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if(NULL == pIMnet || NULL == pMsg)
		return eInvalidParam;
		
    retCode=0;
	retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, id, pMsg, uiSize, freer);
	if(eOK != retCode)
	{
		return retCode;
	}
	
	PacketConnectionSendtoCallbackProc(pEvent, bLow);
	
	return eOK;
}

#ifdef _GET_SIGNATURE_
AMVoid	FreeGetSigParam(EventContent *pContent)
{
	GetSigParam* pRequest = (GetSigParam*)pContent;
	AMFree(pRequest->szContactIDs);
}

#if 0
AMPVoid _GetSignatureXML(AMPVoid pvArg);

IMnetRetCode IMnetGetSignature(IMnetHandle hIMnetHandle, const AMChar *szToken, AMUChar ucTest,
							   const AMChar * szContactIDs, AMInt32 iCount)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMThread	hThread = NULL;
	GetSigParam	request;
	AMInt32 iLen = 0;
	
	if(NULL == hIMnetHandle || NULL == szToken || NULL == szContactIDs)
		return eInvalidParam;
	
	if(iCount > 0)
	{
		memset(&request, 0, sizeof(request));
		iLen = strlen(szContactIDs);
		request.szContactIDs = (AMChar *)malloc(iLen+1);
		if(NULL == request.szContactIDs)
		{
			return eMallocError;
		}
		strcpy(request.szContactIDs, szContactIDs);

		request.iCount= iCount;
		request.hIMnetHandle = hIMnetHandle;
		request.szAccount = pIMnet->pVarKeeper->userName;
		request.szToken = szToken;
		request.ucTest = ucTest;

		//发送消息
		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, 0, (void*)&request, sizeof(request), FreeGetSigParam);
		if(retCode == eOK)
		{		
			AMThreadCreate(&hThread, NULL, _GetSignatureXML, pEvent);
			AMThreadDetach(hThread);
		}
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}
#endif

#endif // _GET_SIGNATURE_

IMnetRetCode IMnetShallowLoginTribe(IMnetHandle hIMnetHandle)
{
	return IMnetCommonSimple(hIMnetHandle, IM_REQ_SHALLOW_LOGINTRIBE);
}

AMVoid	FreeIMnetDeepLoginTribe(EventContent *pContent)
{
	ImReqDeepLoginTribe	*pReqDeepLogin = (ImReqDeepLoginTribe*)pContent;
	AMFree(pReqDeepLogin->tribeId);
	pReqDeepLogin->tribeId = NULL;
}

IMnetRetCode IMnetDeepLoginTribe(IMnetHandle hIMnetHandle, const AMChar *szTribeId)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	AMInt32 length = 0; 
	ImReqDeepLoginTribe		reqDeepLogin;

	if(szTribeId == NULL || 0 == (length = strlen(szTribeId)))
		return eInvalidParam;
	 
	if(pIMnet != NULL)
	{
		memset(&reqDeepLogin, 0, sizeof(reqDeepLogin));

		reqDeepLogin.tribeId = (AMChar*)AMMalloc(length);
		if(reqDeepLogin.tribeId)
		{
			reqDeepLogin.tribeIdLen	= length;
			memcpy(reqDeepLogin.tribeId, szTribeId, length);

			retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_DEEP_LOGINTRIBE, (void*)&reqDeepLogin, sizeof(reqDeepLogin), FreeIMnetDeepLoginTribe);
			if(retCode == eOK)
				PacketConnectionSend(pEvent);
		}
		else
		{
			retCode = eMallocError;
		}
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}
IMnetRetCode IMnetGetWebBinding(IMnetHandle hIMnetHandle)
{
	ImReqGetWebBinding	req;
	IMnetRetCode	retCode;
	Event*	pEvent = NULL;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	memset(&req, 0, sizeof(req));

	if(pIMnet != NULL)
	{
		retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_GETWEBBINDING, (void*)&req, sizeof(req), NULL);
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}

IMnetRetCode IMnetPutBindInfo(IMnetHandle hIMnetHandle, const AMChar *szBindID, const AMInt32 len)
{
	IMnetRetCode	retCode;
	IMnet *	pIMnet = (IMnet*)hIMnetHandle;

	if(pIMnet != NULL)
	{
		if(pIMnet->szBindUser)
		{
			AMFree(pIMnet->szBindUser);
			pIMnet->szBindUser = NULL;
		}

		if(szBindID && len > 0)
		{
			pIMnet->szBindUser = (AMInt8*)AMMalloc(len+1);
			if(pIMnet->szBindUser == NULL)
				retCode = eMallocError;
			(pIMnet->szBindUser)[len]=0;
			memcpy(pIMnet->szBindUser, szBindID, len*sizeof(AMChar));
			pIMnet->nBindUserLen = len;
		}
		retCode = eOK;
	}
	else
	{
		retCode = eNotReady;
	}

	return retCode;
}
