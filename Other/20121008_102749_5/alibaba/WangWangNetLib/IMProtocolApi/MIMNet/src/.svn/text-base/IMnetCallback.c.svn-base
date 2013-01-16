#include "IMnetCallback.h"
#include "IMnetMain.h"
#include "IMnetUtility.h"
#include "IMnet.h"

#include "stdio.h"
#include "stdlib.h"
#include "AMStdlib.h"
#include "AMString.h"
/************************************************************************/
// struct declare
/************************************************************************/


/************************************************************************/
// static function declare
/************************************************************************/
static IMnetRetCode IMnetCallbackHook(IMnetCallback** ppCallback, EventId id, CallbackFuncHook pCallbackFunc);
static IMnetRetCode IMnetCallbackUnhook(IMnetCallback** ppCallback, EventId id, CallbackFuncHook pCallbackFunc);

static IMnetRetCode IMnetCallbackAdd(CallbackBlock** ppCallbackBlock, EventId id, CallbackFuncUnion pCallbackFunc, AMInt32 type);
static IMnetRetCode IMnetCallbackRemove(CallbackBlock** ppCallbackBlock, EventId id, CallbackFuncUnion pCallbackFunc, AMInt32 type);

static void IMnetCallbackDestoryBlock(CallbackBlock* pBlock);
static IMnetRetCode IMnetCallbackHandleBlock(IMnet* pIMNet, CallbackBlock* pBlockFit, Event* pEvent, AMInt32 type);

static IMnetRetCode BuildIMContactEvent(IMnet* pIMnet, AMChar* bindID, AMInt32 bindIDLen,  AMInt32 sendTime, AMUInt8* content, AMInt32 contentLen, Event** ppEvent, AMInt32 online);
static IMnetRetCode BuildIMChatEvent(IMnet* pIMnet, AMChar* bindID, AMInt32 bindIDLen,AMChar* pFromID, AMInt32 FromIDLen,
							  AMInt32 sendTime, AMUInt8 serverTypd, ImMessageText *pMsgText, 
							  Event** ppEvent, AMInt32 online);
static IMnetRetCode BuildIMSubscribeEvent(IMnet* pIMnet,  AMInt32 sendTime, AMUInt8* content, AMInt32 contentLen, Event** ppEvent, AMInt32 online);
static IMnetRetCode BuildIMAutoReply(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
							  AMInt32 sendTime, 
							  AMUInt8* content, AMInt32 contentLen, 
							  Event** ppEvent, AMInt32 online);

static IMnetRetCode BuildU2UMessageNotify(IMnet* pIMnet, 
										  AMChar* pFromID, AMInt32 FromIDLen,
										  AMInt16 cmd, AMInt32 sendTime,
										  AMUInt8* content, AMInt32 contentLen, 
										  Event** ppEvent);
//static IMnetRetCode BuildVideoChatInviteReq(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//											AMInt32 sendTime, 
//											AMUInt8* content, AMInt32 contentLen, 
//											Event** ppEvent);
//static IMnetRetCode BuildVideoChatInviteRsp(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//											AMInt32 sendTime, 
//											AMUInt8* content, AMInt32 contentLen, 
//											Event** ppEvent);
//static IMnetRetCode BuildVideoChatInviteCancel(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//											   AMInt32 sendTime, 
//											   AMUInt8* content, AMInt32 contentLen, 
//											   Event** ppEvent);

/************************************************************************/
// HookCallback Functions.
/************************************************************************/
/************************************************************************/
// HookCheckVersion
/************************************************************************/
IMnetRetCode HookCheckVersion(IMnetHandle hIMnetHandle, Event* pEvt)
{
	IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImRspCheckVersion* pRspCheckVersion = (ImRspCheckVersion*)(pEvt->pContent);
	ImReqLogin reqLogin;
	ImEventCheckVersion upEvent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if( pRspCheckVersion->retCode == CHECK_VERSION_SUCESS ||
		pRspCheckVersion->retCode == CHECK_VERSION_COMPATIBLE )
	{	
		DesEncrypt(
			(AMUInt8*)pIMnet->pVarKeeper->constDesKey,
			(AMUInt8*)pRspCheckVersion->pubKey,
			eDecrypt);

		memset(pIMnet->pVarKeeper->encryptKey, 0, sizeof(pIMnet->pVarKeeper->encryptKey));
		memcpy(pIMnet->pVarKeeper->encryptKey, pRspCheckVersion->pubKey, sizeof(pRspCheckVersion->pubKey));
		pIMnet->pVarKeeper->connectNo = pRspCheckVersion->connectNo;

		memset(&reqLogin, 0, sizeof(reqLogin));
		reqLogin.connectNo = pRspCheckVersion->connectNo;

		reqLogin.tokenFlag = pIMnet->pVarKeeper->bIsToken;
		strcpy(reqLogin.password, pIMnet->pVarKeeper->password);
		strcpy(reqLogin.version, pIMnet->pVarKeeper->constVersion);

		reqLogin.language = 0x804;
		reqLogin.timestampFlag = 15;
		reqLogin.timestampList[0] = pIMnet->pVarKeeper->loginStamp.groupStamp;
		reqLogin.timestampList[1] = pIMnet->pVarKeeper->loginStamp.contactStamp;
		reqLogin.timestampList[2] = pIMnet->pVarKeeper->loginStamp.blackListStamp;
		reqLogin.timestampList[3] = pIMnet->pVarKeeper->loginStamp.revBlackListStamp;	
		

		memcpy(reqLogin.rid, IM_MAGIC, strlen(IM_MAGIC));
		memcpy(reqLogin.encryptKey, pRspCheckVersion->pubKey, sizeof(pRspCheckVersion->pubKey));
		reqLogin.reserved = 1;
		strcpy(reqLogin.extData, pIMnet->pVarKeeper->userName);

		retCode = EventCreate(pIMnet->hPCHandle, &pEvent, IM_REQ_LOGIN, (void*)&reqLogin, sizeof(reqLogin));
		if(retCode == eOK)
			PacketConnectionSend(pEvent);
	}

	if( pRspCheckVersion->retCode == CHECK_VERSION_COMPATIBLE ||
		pRspCheckVersion->retCode == CHECK_VERSION_NONCOMPATIBLE ||
		pRspCheckVersion->retCode == CHECK_VERSION_UNKNOWN )
	{
		upEvent.retCode = pRspCheckVersion->retCode;
		retCode = EventRebuild(pEvt, pEvt->id, (void*)&upEvent, sizeof(upEvent), NULL);
		if(retCode == eOK)
			retCode = eIMnetEventExchange;
	}
	return retCode;
}

/************************************************************************/
// HookPackLoginInd
/************************************************************************/
void FreeImReqPreLogin(EventContent* pContent)
{
    ImReqPreLogin* pReqPreLogin = (ImReqPreLogin*)pContent;
    AMFree(pReqPreLogin->loginBlock);
    pReqPreLogin->loginBlock = NULL;
}

IMnetRetCode HookPackLoginInd(IMnetHandle hIMnetHandle, Event* pEvt)
{
    IMnetRetCode retCode;
	Event* pEvent = NULL;
	ImReqPreLogin reqPreLogin;
	ImPackLoginInd* pIndPackLogin = (ImPackLoginInd*)pEvt->pContent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	memset(&reqPreLogin, 0, sizeof(reqPreLogin));

	reqPreLogin.connectNo = pIndPackLogin->connectNo;
	memset(reqPreLogin.workKey, 0, sizeof(reqPreLogin.workKey));
	reqPreLogin.loginBlock = pIndPackLogin->loginBlock;
	reqPreLogin.loginBlockLen = pIndPackLogin->loginBlockLen;

    retCode = EventCreateEx(pIMnet->hPCHandle, 
							&pEvent, 
#if 1		
							IM_REQ_PRELOGIN1, 
#else
							IM_REQ_PRELOGIN,
#endif
							(void*)&reqPreLogin, 
							sizeof(reqPreLogin), 
							FreeImReqPreLogin);
	if(retCode == eOK)
        PacketConnectionSend(pEvent);

	//don't let this event to next call backers.
	return eIMnetSkip;
}

/************************************************************************/
// HookRspLogin
/************************************************************************/
PCRetCode MakeHealthCheckEvent(PCHandle hHandle, Event** ppEvt, PCReference ref)
{
	ImReqHealthCheck request;
	memset(&request, 0, sizeof(request));

	EventCreate(hHandle, ppEvt, IM_HEALTH_CHECK, (void*)&request, sizeof(request));
	
	return eOK;
}

void FreeImReqHelpLogin(EventContent* pContent)
{
	ImReqHelpLogin* pReqHelpLogin = (ImReqHelpLogin*)pContent;
	AMFree(pReqHelpLogin->accountId);
	pReqHelpLogin->accountId = NULL;
}

#if defined (ANDROID_BUILD) || defined (IOS_BUILD)
#define	HEALTH_CHECK_INTERVAL		60
#else
#define HEALTH_CHECK_INTERVAL		280
#endif

IMnetRetCode HookRspLogin(IMnetHandle hIMnetHandle, Event* pEvt)
{
	ImRspLogin* pRspLogin = (ImRspLogin*)pEvt->pContent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	ImReqHelpLogin	reqHelpLogin;
	Event* pEvent = NULL;
	IMnetRetCode retCode = eNotReady;	

	//denx add for debug
	//AMSleep(20*1000);

	if (0 == pRspLogin->retCode || 33 == pRspLogin->retCode) 
	{
		if(33 == pRspLogin->retCode)
			IMnetLogin2(hIMnetHandle, "libww12345");

		//enable and start health checker.
		PacketConnectionStartKeepAlive(pIMnet->hPCHandle, HEALTH_CHECK_INTERVAL, MakeHealthCheckEvent);

		/*
		* 下面要做E客服帐号的HelpLogin操作-----------yanlong.shiyl
		*/

		if(NULL != strstr(pRspLogin->remark, "mul=1"))//是否E客服
		{
			memset(&reqHelpLogin, 0, sizeof(reqHelpLogin));
			reqHelpLogin.accountIdLen = strlen(pIMnet->pVarKeeper->userName);
			reqHelpLogin.accountId = malloc(reqHelpLogin.accountIdLen);
			reqHelpLogin.status = 0;
			if(reqHelpLogin.accountId)
			{
				memcpy(reqHelpLogin.accountId, pIMnet->pVarKeeper->userName, reqHelpLogin.accountIdLen);
				retCode = EventCreateEx(pIMnet->hPCHandle, &pEvent, IM_REQ_HELP_LOGIN, (void*)&reqHelpLogin, sizeof(reqHelpLogin), FreeImReqHelpLogin);
				if(retCode == eOK)
					PacketConnectionSend(pEvent);
			}
		}
	} 
	
	return eOK;
}

/************************************************************************/
// HookRspReLogin
/************************************************************************/
IMnetRetCode HookRspReLogin(IMnetHandle hIMnetHandle, Event* pEvt)
{
	ImRspReLogin* pResponse = (ImRspReLogin*)pEvt->pContent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;

	if (0 == pResponse->retCode) 
	{
		//enable health checker.
		pIMnet->pVarKeeper->connectNo = pResponse->connectNo;
		PacketConnectionStartKeepAlive(pIMnet->hPCHandle, HEALTH_CHECK_INTERVAL, MakeHealthCheckEvent);
	}

	return eOK;
}

/************************************************************************/
// HookNtfIMmessage
/************************************************************************/
IMnetRetCode HookNtfIMmessage(IMnetHandle hIMnetHandle, Event* pEvt)
{
	ImNtfIMMessage* pNotify = (ImNtfIMMessage*)pEvt->pContent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	Event* pEvent = NULL;
	ImEventChatMessage* pChatMessage = NULL;
	IMnetRetCode retCode = eNotReady;

	switch (pNotify->text.childHead.cmd)
	{
	case IMM_SP_TEXT:
	case IMM_SP_OFFIMG:
		retCode = BuildIMChatEvent(pIMnet, pNotify->bindID, pNotify->bindIDLen, pNotify->sendId, pNotify->sendIdLen, 
			pNotify->sendTime, pNotify->serverType, &pNotify->text, 
			&pEvent, 1);

		//ACK在上层发送
		//if(retCode == eOK)
		//{
		//	// 构造二级协议体
		//	pChatMessage = (ImEventChatMessage*)pEvent->pContent;

		//	//发送ACK消息到服务器
		//	//send一级协议
		//	IMnetPutBindInfo(pIMnet, pNotify->bindID, pNotify->bindIDLen);
		//	IMnetSendMessageEx(hIMnetHandle, 
		//		pChatMessage->msg.fromId, 
		//		pChatMessage->msg.fromIdLen, 
		//		NULL, 0, 0, IMM_SP_MSG_ACK, 
		//		pChatMessage->ackSeq);
		//}
		break;

	case IMM_SP_BUZZ:
		break;

	case IMM_SP_P2P:
		break;

	case IMM_SP_AUTO_REPLY:
		retCode = BuildIMAutoReply(pIMnet, pNotify->sendId, pNotify->sendIdLen,
			pNotify->sendTime, pNotify->text.content, pNotify->text.contentLen, 
			&pEvent, 1);
		break;

	case IMM_SP_MSG_ACK:
		break;

	case IMM_SP_CONTACT:
		retCode = BuildIMContactEvent(pIMnet, pNotify->bindID, pNotify->bindIDLen, pNotify->sendTime, pNotify->text.content, pNotify->text.contentLen, 
			&pEvent, 1);
		break;

	case IMM_SP_NOTIFY:
		break;

	case IMM_SP_GROUP_BROADCAST:
		break;

	case IMM_SP_PLUGINS_QUERY:
		break;

	case IMM_SP_PLUGINS_RESPONSE:
		break;

	case IMM_SP_PLUGINS_INVITE:
		break;

	case IMM_SP_CUSTOM_MESSAGE:
		break;

	case IMM_SP_FOCUS_TALK:
		break;

	case IMM_VIDEOCHAT_INVITE_REQUEST:
	case IMM_VIDEOCHAT_INVITE_CANCEL:
	case IMM_VIDEOCHAT_INVITE_RESPONSE:
	case IMM_VIDEOCHAT_FINISH:
		retCode = BuildU2UMessageNotify(pIMnet, pNotify->sendId, pNotify->sendIdLen,
			pNotify->text.childHead.cmd, pNotify->sendTime, 
			pNotify->text.content, pNotify->text.contentLen, 
			&pEvent);
		break;
	//case IMM_VIDEOCHAT_INVITE_REQUEST:
	//	retCode = BuildVideoChatInviteReq(pIMnet, pNotify->sendId, pNotify->sendIdLen,
	//		pNotify->sendTime, pNotify->text.content, pNotify->text.contentLen, 
	//		&pEvent);
	//	break;
	//case IMM_VIDEOCHAT_INVITE_CANCEL:
	//	retCode = BuildVideoChatInviteCancel(pIMnet, pNotify->sendId, pNotify->sendIdLen,
	//		pNotify->sendTime, pNotify->text.content, pNotify->text.contentLen, 
	//		&pEvent);
	//	break;
	//	break;
	//case IMM_VIDEOCHAT_INVITE_RESPONSE:
	//	retCode = BuildVideoChatInviteRsp(pIMnet, pNotify->sendId, pNotify->sendIdLen,
	//		pNotify->sendTime, pNotify->text.content, pNotify->text.contentLen, 
	//		&pEvent);
	//	break;

	default:
#ifdef AMOS_DEBUG
		AMPrintf("HookNtfIMmessage.....................0x%x", pNotify->text.childHead.cmd);
#endif // AMOS_DEBUG
		break;
	}

	if(retCode == eOK && pEvent != NULL)
		PacketConnectionSendtoCallback(pEvent);

	return eIMnetSkip;
}

void FreeImDeleteOfflineMsg(EventContent* pContent)
{
	ImEventToDeleteOfflineMsg* pEvent = (ImEventToDeleteOfflineMsg*)pContent;
	if(pEvent->fromID)
	{
		AMFree(pEvent->fromID);
		pEvent->fromID = NULL;
	}

}

/************************************************************************/
// HookGetOfflineMsg
/************************************************************************/
IMnetRetCode HookGetOfflineMsg(IMnetHandle hIMnetHandle, Event* pEvt)
{
	IMnetRetCode retCode;
	ImRspGetOfflineMsg* pResponse = (ImRspGetOfflineMsg*)pEvt->pContent;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	OfflineMsgList* pTemp = NULL;
	OfflineMsgList* pTempLast = NULL;
	Event* pChatEvent = NULL;
	Event* pSubscribeEvent = NULL;
	Event* pContactEvent = NULL;
	Event *pImageEvent = NULL;
	Event *pDeleteOfflineEvent = NULL;
	ImEventToDeleteOfflineMsg deleteOffline;

	//search last.
	pTemp = pResponse->offlineMsgList;
	while(pTemp)
	{
		pTempLast = pTemp;
		pTemp = pTemp->pNext;
	}

	if(pTempLast != NULL)
	{
		// 发送删除消息到服务器
		//retCode = IMnetDeleteOfflineMsg(hIMnetHandle, pTempLast->offlineMsgInfo.sendTime);
		//if(retCode != eOK)
		//	return retCode;
		deleteOffline.sendtime = pTempLast->offlineMsgInfo.sendTime;
		deleteOffline.fromIDLen = pTempLast->offlineMsgInfo.fromIdLen;
		deleteOffline.fromID = (AMChar *)AMMalloc(deleteOffline.fromIDLen + 1);
		AMMemcpy(deleteOffline.fromID, pTempLast->offlineMsgInfo.fromId, deleteOffline.fromIDLen);
		deleteOffline.fromID[deleteOffline.fromIDLen] = 0;
		retCode = EventCreateEx(pIMnet->hPCHandle, &pDeleteOfflineEvent, IM_EVENT_DELETE_OFFLINE_MESSAGE, 
			(void*)&deleteOffline, sizeof(deleteOffline), 
			FreeImDeleteOfflineMsg);
		PacketConnectionSendtoCallback(pDeleteOfflineEvent);



		//开始重新构造给上面的EVENT
		pTemp = pResponse->offlineMsgList;
		while(pTemp)
		{
			switch (pTemp->offlineMsgInfo.type)
			{
			case 0: //0: 普通聊天信息
				BuildIMChatEvent(pIMnet, pResponse->bindID, pResponse->bindIDLen, pTemp->offlineMsgInfo.fromId,
					pTemp->offlineMsgInfo.fromIdLen, pTemp->offlineMsgInfo.sendTime, 
					pTemp->offlineMsgInfo.serverType, &pTemp->offlineMsgInfo.text, 
					&pChatEvent, 0);
				break;

			case 1: //1: 订阅消息
				BuildIMSubscribeEvent(pIMnet, pTemp->offlineMsgInfo.sendTime, pTemp->offlineMsgInfo.text.content, 
					pTemp->offlineMsgInfo.text.contentLen, &pSubscribeEvent, 0);
				break;

			case 2: //2: 添加联系人通知消息
				BuildIMContactEvent(pIMnet, pResponse->bindID, pResponse->bindIDLen, pTemp->offlineMsgInfo.sendTime, 
					pTemp->offlineMsgInfo.text.content, 
					pTemp->offlineMsgInfo.text.contentLen, &pContactEvent, 0);

				if(pContactEvent != NULL)
					PacketConnectionSendtoCallback(pContactEvent);
				break;

			default:
				break;
			}
			pTemp = pTemp->pNext;
		}

		if(pChatEvent != NULL)
			PacketConnectionSendtoCallback(pChatEvent);
		if(pSubscribeEvent != NULL)
			PacketConnectionSendtoCallback(pSubscribeEvent);
	}

	return eIMnetSkip;
}

/************************************************************************/
// BuildIMContactEvent
/************************************************************************/
void FreeImEventContactAdded(EventContent* pContent)
{
	ImEventContactAdded* pImEventContactAdded = (ImEventContactAdded*)pContent;
	AMFree(pImEventContactAdded->fromID);
	pImEventContactAdded->fromID = NULL;
}

void FreeImEventContactAskAddVerify(EventContent* pContent)
{
	ImEventContactAskAddVerify* pImEventContactAskAddVerify = (ImEventContactAskAddVerify*)pContent;
	
	AMFree(pImEventContactAskAddVerify->fromID);
	pImEventContactAskAddVerify->fromID = NULL;
	AMFree(pImEventContactAskAddVerify->dispName);
	pImEventContactAskAddVerify->dispName = NULL;
	AMFree(pImEventContactAskAddVerify->verifyInfo);
	pImEventContactAskAddVerify->verifyInfo = NULL;
}

void FreeImEventContactAskAddYes(EventContent* pContent)
{
	ImEventContactAskAddYes* pImEventContactAskAddYes = (ImEventContactAskAddYes*)pContent;

	AMFree(pImEventContactAskAddYes->fromID);
	pImEventContactAskAddYes->fromID = NULL;
}

void FreeImEventContactAskAddNo(EventContent* pContent)
{
	ImEventContactAskAddNo* pImEventContactAskAddNo = (ImEventContactAskAddNo*)pContent;

	AMFree(pImEventContactAskAddNo->fromID);
	pImEventContactAskAddNo->fromID = NULL;
	AMFree(pImEventContactAskAddNo->msg);
	pImEventContactAskAddNo->msg = NULL;
}

IMnetRetCode BuildIMContactEvent(IMnet* pIMnet, AMChar* bindID, AMInt32 bindIDLen,  AMInt32 sendTime, AMUInt8* content, AMInt32 contentLen, Event** ppEvent, AMInt32 online)
{
	IMnetRetCode retCode;
	MessageXML	 xml;
	AMInt32		 opcode;
	ImEventContactAdded			imEventContactAdded; 
	ImEventContactAskAddVerify	imEventContactAskAddVerify;
	ImEventContactAskAddYes		imEventContactAskAddYes;
	ImEventContactAskAddNo		imEventContactAskAddNo;
	ImEventContactIgnoreAdded	imEventContactIgnoreAdded;
	ImEventContactIgnoreDeled	imEventContactIgnoreDeled;

	memset(&xml, 0, sizeof(xml));
	//此函数内部申请内存, 最后用FreeMessageXml来释放
	XMLStringToMessageXML((AMChar*)content, contentLen, &xml);

	opcode = atoi(xml.result);
	switch(opcode)
	{
	case IMM_CONTACT_ADDED: //不需验证的添加
		memset(&imEventContactAdded, 0, sizeof(imEventContactAdded));
		imEventContactAdded.fromIDLen = xml.fromUIDLen;
		imEventContactAdded.online = online;
		imEventContactAdded.bindID = (AMChar*)AMMalloc(bindIDLen+1);
		if(imEventContactAdded.bindID)
		{
			memset(imEventContactAdded.bindID, 0, (bindIDLen+1)*sizeof(AMChar));
			memcpy(imEventContactAdded.bindID, bindID, bindIDLen);
		}
		else
		{
			retCode = eMallocError;
			break;
		}
		imEventContactAdded.fromID = (AMChar*)AMMalloc(xml.fromUIDLen);
		if(imEventContactAdded.fromID)
		{
			memcpy(imEventContactAdded.fromID, xml.fromUID, xml.fromUIDLen);
			retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_ADDED, 
				(void*)&imEventContactAdded, sizeof(imEventContactAdded), 
				FreeImEventContactAdded);
		}
		else
		{
			retCode = eMallocError;
		}
		break;

	case IMM_CONTACT_IGNOREUSER_ADDED: //阻止用户添加（黑名单）
		memset(&imEventContactIgnoreAdded, 0, sizeof(imEventContactIgnoreAdded));
		imEventContactIgnoreAdded.online = online;

		retCode = EventCreate(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_IGNORE_ADDED, 
			(void*)&imEventContactIgnoreAdded, sizeof(imEventContactIgnoreAdded));
		break;

	case IMM_CONTACT_IGNOREUSER_DELED: //取消阻止用户
		memset(&imEventContactIgnoreDeled, 0, sizeof(imEventContactIgnoreDeled));
		imEventContactIgnoreDeled.online = online;

		retCode = EventCreate(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_IGNORE_DELED, 
			(void*)&imEventContactIgnoreDeled, sizeof(imEventContactIgnoreDeled));
		break;

	case IMM_CONTACT_ASKADD_REQ: //发出添加请求验证
		memset(&imEventContactAskAddVerify, 0, sizeof(ImEventContactAskAddVerify));
		imEventContactAskAddVerify.fromIDLen = xml.fromUIDLen;
		imEventContactAskAddVerify.dispNameLen = xml.dispNameLen;
		imEventContactAskAddVerify.verifyInfoLen = xml.msgLen;
		String2Long(xml.pgID, &imEventContactAskAddVerify.groupIDHigh, &imEventContactAskAddVerify.groupIDLow);
		imEventContactAskAddVerify.online = online;

		imEventContactAskAddVerify.bindID = (AMChar*)AMMalloc(bindIDLen+1);
		if(imEventContactAskAddVerify.bindID)
		{
			memset(imEventContactAskAddVerify.bindID, 0, (bindIDLen+1)*sizeof(AMChar));
			memcpy(imEventContactAskAddVerify.bindID, bindID, bindIDLen);
		}
		else
		{
			retCode = eMallocError;
			break;
		}

		imEventContactAskAddVerify.fromID = (AMChar*)AMMalloc(xml.fromUIDLen);
		if(imEventContactAskAddVerify.fromID)
		{
			memcpy(imEventContactAskAddVerify.fromID, xml.fromUID, xml.fromUIDLen);

			imEventContactAskAddVerify.dispName = (AMChar*)AMMalloc(xml.dispNameLen);
			if(imEventContactAskAddVerify.dispName)
			{
				memcpy(imEventContactAskAddVerify.dispName, xml.dispName, xml.dispNameLen);
				
				imEventContactAskAddVerify.verifyInfo = (AMChar*)AMMalloc(xml.msgLen);
				if(imEventContactAskAddVerify.verifyInfo)
				{
					memcpy(imEventContactAskAddVerify.verifyInfo, xml.msg, xml.msgLen);
				
					retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_ADD_CNT_VERIFY,
						(void*)&imEventContactAskAddVerify, sizeof(imEventContactAskAddVerify), 
						FreeImEventContactAskAddVerify);
				}
				else
				{
					retCode = eMallocError;
					AMFree(imEventContactAskAddVerify.fromID);
					AMFree(imEventContactAskAddVerify.dispName);
				}
			}
			else
			{	
				retCode = eMallocError;
				AMFree(imEventContactAskAddVerify.fromID);
			}
		}
		else
		{
			retCode = eMallocError;
		}
		break;

	case IMM_CONTACT_ASKADD_YES: //答复请求验证，同意
		memset(&imEventContactAskAddYes, 0, sizeof(imEventContactAskAddYes));
		imEventContactAskAddYes.fromIDLen = xml.fromUIDLen;
		String2Long(xml.pgID, &imEventContactAskAddYes.groupIDHigh, &imEventContactAskAddYes.groupIDLow);
		imEventContactAskAddYes.online = online;

		imEventContactAskAddYes.fromID = (AMChar*)AMMalloc(xml.fromUIDLen);
		if(imEventContactAskAddYes.fromID)
		{
			memcpy(imEventContactAskAddYes.fromID, xml.fromUID, xml.fromUIDLen);

			retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_ASKADD_YES, 
				(void*)&imEventContactAskAddYes, sizeof(imEventContactAskAddYes), 
				FreeImEventContactAskAddYes);
		}
		else
			retCode = eMallocError;
		break;

	case IMM_CONTACT_ASKADD_NO: //答复请求验证，拒绝
		memset(&imEventContactAskAddNo, 0, sizeof(imEventContactAskAddNo));
		imEventContactAskAddNo.fromIDLen = xml.fromUIDLen;
		imEventContactAskAddNo.msgLen = xml.msgLen;
		imEventContactAskAddNo.online = online;

		imEventContactAskAddNo.fromID = (AMChar*)AMMalloc(xml.fromUIDLen);
		if(imEventContactAskAddNo.fromID)
		{
			memcpy(imEventContactAskAddNo.fromID, xml.fromUID, xml.fromUIDLen);

			imEventContactAskAddNo.msg = (AMChar*)AMMalloc(xml.msgLen);
			if(imEventContactAskAddNo.msg)
			{
				memcpy(imEventContactAskAddNo.msg, xml.msg, xml.msgLen);

				retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_CONTACT_ASKADD_NO, 
					(void*)&imEventContactAskAddNo, sizeof(imEventContactAskAddNo), 
					FreeImEventContactAskAddNo);
			}
			else
			{
				retCode = eMallocError;
				AMFree(imEventContactAskAddNo.fromID);
			}
		}
		else
			retCode = eMallocError;

		break;

	default:
		break;

	}

	FreeMessageXml(&xml);
	return retCode;
}

/************************************************************************/
// BuildIMChatEvent
/************************************************************************/
void FreeImEventChatMessage(EventContent* pContent)
{
	ImEventChatMessage* pImEventChatMessage = (ImEventChatMessage*)pContent;
	ImEventChatMessage* ptemp = NULL;
	AMInt32 i = 0;

	while(pImEventChatMessage)
	{
		AMFree(pImEventChatMessage->msg.fromId);
		pImEventChatMessage->msg.fromId = NULL;

		AMFree(pImEventChatMessage->msg.msgContent);
		pImEventChatMessage->msg.msgContent = NULL;

		ptemp = pImEventChatMessage->next;

		if(i++)
			AMFree(pImEventChatMessage);

		pImEventChatMessage = ptemp;
	}
}

IMnetRetCode BuildIMChatEvent(IMnet* pIMnet, 		
							  AMChar* bindID, AMInt32 bindIDLen,
							  AMChar* pFromID, AMInt32 FromIDLen, AMInt32 sendTime, 
							  AMUInt8 serverType, ImMessageText *pMsgText, 
							  Event** ppEvent, AMInt32 online)
{
	AMInt32 ackSeq = pMsgText->childHead.ackSeq,
		contentLen = pMsgText->contentLen;
	AMUInt8* content = pMsgText->content;

	ImEventChatMessage* pLastChatMessage = NULL;
	ImEventChatMessage* pTempChatMessage = NULL;
	ImEventChatMessage chatMessage;
	IMnetRetCode retCode;

	memset(&chatMessage, 0, sizeof(chatMessage));
	chatMessage.msg.online = online;
	chatMessage.msg.sendTime = sendTime;
	chatMessage.ackSeq = ackSeq;
	chatMessage.msg.iServerType = serverType;
	if(pMsgText->childHead.cmd == IMM_SP_OFFIMG)
		chatMessage.msg.iType = 1;

	chatMessage.msg.fromId = (AMChar*)AMMalloc(FromIDLen);
	if(chatMessage.msg.fromId != NULL)
	{
		memset(chatMessage.msg.fromId, 0, FromIDLen);
		memcpy(chatMessage.msg.fromId, pFromID, FromIDLen);
		chatMessage.msg.fromIdLen = FromIDLen;
	}
	else
	{
		AMAssert(0);
		retCode = eMallocError;
	}

	if(bindID && bindIDLen > 0)
	{
		chatMessage.msg.bindID = (AMChar*)AMMalloc(bindIDLen);
		if(chatMessage.msg.bindID == NULL)
		{
			AMFree(chatMessage.msg.fromId);
			AMAssert(0);
			retCode = eMallocError;
			return retCode;
		}
		memset(chatMessage.msg.bindID, 0, bindIDLen);
		memcpy(chatMessage.msg.bindID, bindID, bindIDLen);
		chatMessage.msg.bindIDLen = bindIDLen;	
	}

	chatMessage.msg.msgContent = (AMChar*)AMMalloc(contentLen);
	if(chatMessage.msg.msgContent != NULL)
	{
		memset(chatMessage.msg.msgContent, 0, contentLen);
		memcpy(chatMessage.msg.msgContent, content, contentLen);
		chatMessage.msg.msgContentLen = contentLen;	

		if((*ppEvent) == NULL)
		{
			retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_CHAT_MESSAGE, 
				(void*)&chatMessage, sizeof(chatMessage), 
				FreeImEventChatMessage);
		}
		else
		{
			//将ImEventChatMessage挂载在前一个的next上面.
			pLastChatMessage = (ImEventChatMessage*)((*ppEvent)->pContent);
			while(pLastChatMessage->next)
				pLastChatMessage = pLastChatMessage->next;

			pTempChatMessage = (ImEventChatMessage*)AMMalloc(sizeof(ImEventChatMessage));
			if(pTempChatMessage != NULL)
			{
				memset(pTempChatMessage, 0, sizeof(ImEventChatMessage));
				memcpy(pTempChatMessage, &chatMessage, sizeof(ImEventChatMessage));
				pLastChatMessage->next = pTempChatMessage;
				retCode = eOK;
			}
			else
			{
				FreeImEventChatMessage((*ppEvent)->pContent);
				AMAssert(0);
				retCode = eMallocError;
			}
		}
	}
	else
	{
		AMFree(chatMessage.msg.fromId);
		if(chatMessage.msg.bindID)
			AMFree(chatMessage.msg.bindID);
		AMAssert(0);
		retCode = eMallocError;
	}

	return retCode;
}

/************************************************************************/
// BuildIMSubscribeEvent
/************************************************************************/
void FreeImEventNtfSubscribeMsg(EventContent* pContent)
{
	ImEventNtfSubscribeMsg* pImEventNtfSubscribeMsg = (ImEventNtfSubscribeMsg*)pContent;
	ImEventNtfSubscribeMsg* pTemp = NULL;
	AMInt32 i = 0;
	while(pImEventNtfSubscribeMsg)
	{
		AMFree(pImEventNtfSubscribeMsg->message);
		pImEventNtfSubscribeMsg->message = NULL;

		pTemp = pImEventNtfSubscribeMsg->next;
		if(i++)
			AMFree(pImEventNtfSubscribeMsg);

		pImEventNtfSubscribeMsg = pTemp;
	}
}

IMnetRetCode BuildIMSubscribeEvent(IMnet* pIMnet,  AMInt32 sendTime, AMUInt8* content, AMInt32 contentLen, Event** ppEvent, AMInt32 online)
{
	ImEventNtfSubscribeMsg subscribeMsg;
	ImEventNtfSubscribeMsg* pLast = NULL;
	ImEventNtfSubscribeMsg* pTemp = NULL;
 	IMnetRetCode retCode;
// 	AMChar* pTitle = NULL;
// 	AMInt32 TitleLen = 0;
// 	AMChar* pDatetime = NULL;
// 	AMInt32 DatetimeLen = 0;
// 	AMChar* pContent = NULL;
// 	AMInt32 ContentLen = 0;

	//订阅消息的格式如下：<title>||<datetime>||<content>，这三个部分都以双竖线分隔。
	//其中datetime要特殊说明一下，格式是4位年，2位月，2位日，2位时，2位分，2位秒，中间没有分隔符号
	memset(&subscribeMsg, 0, sizeof(subscribeMsg));
	subscribeMsg.online = online;

// 	pTitle = (AMChar*)content;
// 	pDatetime = strstr((AMChar*)content, "||") + 2;
// 	pContent = strstr(pDatetime, "||") + 2;
// 
// 	TitleLen = (AMInt32)(pDatetime-pTitle) - 2;
// 	ContentLen = (AMInt32)(pTitle+contentLen-pContent);
// 
// 	memcpy(subscribeMsg.datetime, pDatetime, 4);
// 	subscribeMsg.datetime[4] = '-';
// 	memcpy(&subscribeMsg.datetime[5], pDatetime+4, 2);
// 	subscribeMsg.datetime[7] = '-';
// 	memcpy(&subscribeMsg.datetime[8], pDatetime+6, 2);
// 	subscribeMsg.datetime[10] = ' ';
// 	memcpy(&subscribeMsg.datetime[11], pDatetime+8, 2);
// 	subscribeMsg.datetime[13] = ':';
// 	memcpy(&subscribeMsg.datetime[14], pDatetime+10, 2);
// 	subscribeMsg.datetime[16] = ':';
// 	memcpy(&subscribeMsg.datetime[17], pDatetime+12, 2);
// 
// 	subscribeMsg.title = (AMChar*)AMMalloc(TitleLen+1);
// 	if(subscribeMsg.title != NULL)
// 	{
// 		memset(subscribeMsg.title, 0, TitleLen+1);
// 		memcpy(subscribeMsg.title, pTitle, TitleLen);
// 		subscribeMsg.titleLen = TitleLen;
// 	}
// 	else
// 	{
// 		if(*ppEvent)
// 			FreeImEventNtfSubscribeMsg((*ppEvent)->pContent);
// 		AMAssert(0);
// 		retCode = eMallocError;
// 	}
// 
// 	subscribeMsg.content = (AMChar*)AMMalloc(ContentLen+1);
// 	if(subscribeMsg.content != NULL)
// 	{
// 		memset(subscribeMsg.content, 0, ContentLen+1);
// 		memcpy(subscribeMsg.content, pContent, ContentLen);
// 		subscribeMsg.contentLen = ContentLen;
// 	}
// 	else
// 	{
// 		AMFree(subscribeMsg.title);
// 		if(*ppEvent)
// 			FreeImEventNtfSubscribeMsg((*ppEvent)->pContent);
// 		AMAssert(0);
// 		retCode = eMallocError;
// 	}

	subscribeMsg.message = (AMChar*)AMMalloc(contentLen+1);
	if(subscribeMsg.message != NULL)
	{
		memset(subscribeMsg.message, 0, contentLen+1);
		memcpy(subscribeMsg.message, content, contentLen);
		subscribeMsg.messageLen = contentLen;
	}
	else
	{
		if(*ppEvent)
			FreeImEventNtfSubscribeMsg((*ppEvent)->pContent);
		AMAssert(0);
		retCode = eMallocError;
	}


	if((*ppEvent) == NULL)
	{
		retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_SUBCRIBE_MSG, 
			(void*)&subscribeMsg, sizeof(subscribeMsg), 
			FreeImEventNtfSubscribeMsg);
	}
	else
	{
		//将ImEventNtfSubscribeMsg挂载在前一个的next上面.
		pLast = (ImEventNtfSubscribeMsg*)((*ppEvent)->pContent);
		while(pLast->next)
			pLast = pLast->next;

		pTemp = (ImEventNtfSubscribeMsg*)AMMalloc(sizeof(ImEventNtfSubscribeMsg));
		if(pTemp != NULL)
		{
			memset(pTemp, 0, sizeof(ImEventNtfSubscribeMsg));
			memcpy(pTemp, &subscribeMsg, sizeof(ImEventNtfSubscribeMsg));
			pLast->next = pTemp;
			retCode = eOK;
		}
		else
		{
			FreeImEventNtfSubscribeMsg((*ppEvent)->pContent);
			AMAssert(0);
			retCode = eMallocError;
		}
	}

	return retCode;
}

/************************************************************************/
// BuildIMAutoReply
/************************************************************************/
void FreeImEventAutoReply(EventContent* pContent)
{
	ImEventAutoReply* pImEventAutoReply = (ImEventAutoReply*)pContent;
	ImEventAutoReply* pTemp = NULL;

	AMInt32 i = 0;
	while(pImEventAutoReply)
	{
		AMFree(pImEventAutoReply->msg.fromId);
		pImEventAutoReply->msg.fromId = NULL;

		AMFree(pImEventAutoReply->msg.msgContent);
		pImEventAutoReply->msg.msgContent = NULL;

		pTemp = pImEventAutoReply->next;
		if(i++)
			AMFree(pImEventAutoReply);

		pImEventAutoReply = pTemp;
	}
}

IMnetRetCode BuildIMAutoReply(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
							  AMInt32 sendTime, 
							  AMUInt8* content, AMInt32 contentLen, 
							  Event** ppEvent, AMInt32 online)
{
	ImEventAutoReply autoReply;
	IMnetRetCode retCode;

	memset(&autoReply, 0, sizeof(autoReply));
	autoReply.msg.online = online;
	autoReply.msg.sendTime = sendTime;

	autoReply.msg.fromId = (AMChar*)AMMalloc(FromIDLen);
	if(autoReply.msg.fromId != NULL)
	{
		memset(autoReply.msg.fromId, 0, FromIDLen);
		memcpy(autoReply.msg.fromId, pFromID, FromIDLen);
		autoReply.msg.fromIdLen = FromIDLen;
	}
	else
	{
		AMAssert(0);
		retCode = eMallocError;
	}

	autoReply.msg.msgContent = (AMChar*)AMMalloc(contentLen);
	if(autoReply.msg.msgContent != NULL)
	{
		memset(autoReply.msg.msgContent, 0, contentLen);
		memcpy(autoReply.msg.msgContent, content, contentLen);
		autoReply.msg.msgContentLen = contentLen;	

		retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_AUTO_REPLY, 
			(void*)&autoReply, sizeof(autoReply), 
			FreeImEventAutoReply);
	}
	else
	{
		AMFree(autoReply.msg.fromId);
		AMAssert(0);
		retCode = eMallocError;
	}

	return retCode;
}

///************************************************************************/
//// BuildVideoChatInviteReq
///************************************************************************/
//void FreeVideoChatInvite(EventContent* pContent)
//{
//	ImEventVideoChatInvite* pImEventVCInvite = (ImEventVideoChatInvite*)pContent;
//
//	if(pImEventVCInvite->fromId)
//	{
//		AMFree(pImEventVCInvite->fromId);
//		pImEventVCInvite->fromId = NULL;
//	}
//	if (pImEventVCInvite->phone)
//	{
//		AMFree(pImEventVCInvite->phone);
//		pImEventVCInvite->phone = NULL;
//	}
//}
//
//IMnetRetCode BuildVideoChatInviteReq(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//									 AMInt32 sendTime, 
//									 AMUInt8* content, AMInt32 contentLen, 
//									 Event** ppEvent)
//{
//	//content is phone number
//
//	ImEventVideoChatInvite invite;
//	IMnetRetCode retCode;
//
//	memset(&invite, 0, sizeof(invite));
//
//	invite.fromId = (AMChar*)AMMalloc(FromIDLen);
//	if(invite.fromId != NULL)
//	{
//		memset(invite.fromId, 0, FromIDLen);
//		memcpy(invite.fromId, pFromID, FromIDLen);
//		invite.fromIdLen = FromIDLen;
//	}
//	else
//	{
//		AMAssert(0);
//		retCode = eMallocError;
//		return retCode;
//	}
//
//	invite.phone = (AMChar*)AMMalloc(contentLen);
//	if(invite.phone != NULL)
//	{
//		memset(invite.phone, 0, contentLen);
//		memcpy(invite.phone, content, contentLen);
//		invite.phoneLen = contentLen;
//	}
//	else
//	{
//		AMFree(invite.fromId);
//		AMAssert(0);
//		retCode = eMallocError;
//		return retCode;
//	}
//
//	retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_VIDEO_CHAT_INVITE, 
//		(void*)&invite, sizeof(invite), 
//		FreeVideoChatInvite);
//	return retCode;
//}
//
///************************************************************************/
//// BuildVideoChatInviteRsp
///************************************************************************/
//void FreeVideoChatInviteRsp(EventContent* pContent)
//{
//	ImEventVideoChatInviteRsp* pImEventVCInvite = (ImEventVideoChatInviteRsp*)pContent;
//
//	if(pImEventVCInvite->fromId)
//	{
//		AMFree(pImEventVCInvite->fromId);
//		pImEventVCInvite->fromId = NULL;
//	}
//	if (pImEventVCInvite->phone)
//	{
//		AMFree(pImEventVCInvite->phone);
//		pImEventVCInvite->phone = NULL;
//	}
//}
//
//IMnetRetCode BuildVideoChatInviteRsp(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//									 AMInt32 sendTime, 
//									 AMUInt8* content, AMInt32 contentLen, 
//									 Event** ppEvent)
//{
//	//content is phone number
//
//	ImEventVideoChatInviteRsp invite;
//	IMnetRetCode retCode;
//	AMChar* s = NULL;
//	AMChar* s2 = NULL;
//
//	memset(&invite, 0, sizeof(invite));
//
//	invite.fromId = (AMChar*)AMMalloc(FromIDLen);
//	if(invite.fromId != NULL)
//	{
//		memset(invite.fromId, 0, FromIDLen);
//		memcpy(invite.fromId, pFromID, FromIDLen);
//		invite.fromIdLen = FromIDLen;
//	}
//	else
//	{
//		AMAssert(0);
//		retCode = eMallocError;
//	}
//
//	//parse code
//	invite.code = AMAtoi(content);
//
//	//parse phone num
//	s = AMStrstr(content, ";");
//	s++;
//	s2 = AMStrstr(content, ";");
//	if(s)
//		invite.phoneLen = s2 - s;
//	else
//		invite.phoneLen = contentLen - (s - content);
//	invite.phone = (AMChar*)AMMalloc(invite.phoneLen);
//	if(invite.phone != NULL)
//	{
//		memset(invite.phone, 0, invite.phoneLen);
//		memcpy(invite.phone, s, invite.phoneLen);
//	}
//	else
//	{
//		AMFree(invite.fromId);
//		AMAssert(0);
//		retCode = eMallocError;
//	}
//
//	retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_VIDEO_CHAT_INVITE_RSP, 
//		(void*)&invite, sizeof(invite), 
//		FreeVideoChatInviteRsp);
//	return retCode;
//}
//
//IMnetRetCode BuildVideoChatInviteCancel(IMnet* pIMnet, AMChar* pFromID, AMInt32 FromIDLen,
//									 AMInt32 sendTime, 
//									 AMUInt8* content, AMInt32 contentLen, 
//									 Event** ppEvent)
//{
//	//content is phone number
//
//	ImEventVideoChatInviteCancel invite;
//	IMnetRetCode retCode;
//
//	retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_VIDEO_CHAT_INVITE_CACNEL, 
//		(void*)&invite, sizeof(invite), 
//		NULL);
//	return retCode;
//}

/************************************************************************/
// BuildU2UMessageNotify
/************************************************************************/
void FreeU2UMessage(EventContent* pContent)
{
	ImEventU2UMessage* pMsg = (ImEventU2UMessage*)pContent;

	if(pMsg->fromId)
	{
		AMFree(pMsg->fromId);
		pMsg->fromId = NULL;
	}
	if (pMsg->msg)
	{
		AMFree(pMsg->msg);
		pMsg->msg = NULL;
	}
}


IMnetRetCode BuildU2UMessageNotify(IMnet* pIMnet, 
								   AMChar* pFromID, AMInt32 FromIDLen,
								   AMInt16 cmd, AMInt32 sendTime,
								   AMUInt8* content, AMInt32 contentLen, 
								   Event** ppEvent)
{
	ImEventU2UMessage msg;
	IMnetRetCode retCode;

	memset(&msg, 0, sizeof(msg));

	msg.cmd = cmd;

	msg.fromId = (AMChar*)AMMalloc(FromIDLen);
	if(msg.fromId != NULL)
	{
		memset(msg.fromId, 0, FromIDLen);
		memcpy(msg.fromId, pFromID, FromIDLen);
		msg.fromIdLen = FromIDLen;
	}
	else
	{
		AMAssert(0);
		retCode = eMallocError;
		return retCode;
	}

	msg.msg = (AMChar*)AMMalloc(contentLen);
	if(msg.msg != NULL)
	{
		memset(msg.msg, 0, contentLen);
		memcpy(msg.msg, content, contentLen);
		msg.msgLen = contentLen;
	}
	else
	{
		AMFree(msg.fromId);
		AMAssert(0);
		retCode = eMallocError;
		return retCode;
	}

	retCode = EventCreateEx(pIMnet->hPCHandle, ppEvent, IM_EVENT_U2U_Message, 
		(void*)&msg, sizeof(msg), 
		FreeU2UMessage);
	return retCode;
}


/************************************************************************/
// HookAddContact
/************************************************************************/
void FreeImEventAddContact(EventContent* pContent)
{
	ImEventAddContact* pImEventAddContact = (ImEventAddContact*)pContent;
	
	AMFree(pImEventAddContact->contactInfo.contactID);
	pImEventAddContact->contactInfo.contactID = NULL;
	AMFree(pImEventAddContact->contactInfo.nickName);
	pImEventAddContact->contactInfo.nickName = NULL;
	AMFree(pImEventAddContact->contactInfo.importance);
	pImEventAddContact->contactInfo.importance = NULL;
}

IMnetRetCode HookAddContact(IMnetHandle hIMnetHandle, Event* pEvt)
{
	ImRspAddContact* pImRspAddContact = (ImRspAddContact*)pEvt->pContent;
	ImEventAddContact upEvent;
	IMnetRetCode retCode = eIMnetSkip;
	AMChar* pMessage = NULL;
	AMInt32 length = 0;
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	
	//构建上层所需要的Event数据结构
	memset(&upEvent, 0, sizeof(upEvent));

	//XXX
	upEvent.bindID = pImRspAddContact->bindID;
	upEvent.bindIDLen = pImRspAddContact->bindIDLen;
	memcpy(&upEvent.contactInfo, &pImRspAddContact->contactInfo, sizeof(pImRspAddContact->contactInfo));
	
	upEvent.timestamp = pImRspAddContact->timestamp;
	upEvent.info = (AddContactInfoCode)pImRspAddContact->retCode;
	if(upEvent.info >= eIMADDCONTACTRESULT_OTHERERROR)
		upEvent.info = eIMADDCONTACTRESULT_OTHERERROR;

	upEvent.retCode = eIMADDCONTACT_FAILED;
	if(pImRspAddContact->retCode == 0)
	{
		upEvent.retCode = eIMADDCONTACT_SUCCESS;
		if(pImRspAddContact->type == 1)
			upEvent.retCode = eIMADDCONTACT_WAITAUTH;
	}
	else if(pImRspAddContact->retCode == 5)
	{
		upEvent.retCode = eIMADDCONTACT_NEEDVERIFY;
	}
	
	if(upEvent.retCode != eIMADDCONTACT_WAITAUTH)
	{
		pImRspAddContact->bContactInfoUsed = 1;
		retCode = EventRebuild(pEvt, pEvt->id, (void*)&upEvent, sizeof(upEvent), FreeImEventAddContact);
		if(retCode == eOK)
			retCode = eIMnetEventExchange;
	}

	//发送添加好友的消息到服务器
#if 0
	if(upEvent.retCode == eIMADDCONTACT_SUCCESS)
	{
		// 构造二级子协议
		MakeXMLString(&pMessage, &length, 
			pIMnet->pVarKeeper->userName, 
			strlen(pIMnet->pVarKeeper->userName), 
			upEvent.contactInfo.contactID, upEvent.contactInfo.contactIDLen,
			0, 0, 0, 0, 0, 0, IMM_CONTACT_ADDED);

		if(pMessage != NULL)
		{
			//send一级协议
			IMnetSendMessageEx(hIMnetHandle, 
				upEvent.contactInfo.contactID, 
				upEvent.contactInfo.contactIDLen, 
				pMessage, length, 1, IMM_SP_CONTACT, 0);
		}

		FreeXMLString(&pMessage);
	}
#endif

	return retCode;
}

/************************************************************************/
// HookRspAddCntAck
/************************************************************************/
IMnetRetCode HookRspAddCntAck(IMnetHandle hIMnetHandle, Event* pEvt)
{
	IMnet* pIMnet = (IMnet*)hIMnetHandle;
	ImRspAddContactACK* pAck = (ImRspAddContactACK*)pEvt->pContent;
	IMnetRetCode retCode = eIMnetOK;
	Event* pEvent = NULL;
	AMChar* pMessage = NULL;
	AMInt32 length = 0;

	//发送添加好友的消息到服务器
#if 0
	if(pAck->retCode == eIMADDCONTACT_SUCCESS)
	{
		// 构造二级子协议
		MakeXMLString(&pMessage, &length,							
			pIMnet->pVarKeeper->userName, 
			strlen(pIMnet->pVarKeeper->userName), 
			pAck->contactID, pAck->contactIDLen,
			pAck->groupIDHigh, pAck->groupIDLow,
			0, 0, 0, 0, IMM_CONTACT_ASKADD_YES);

		if(pMessage != NULL)
		{
			//send一级协议
			IMnetSendMessageEx(hIMnetHandle, 
				pAck->contactID, 
				pAck->contactIDLen, 
				pMessage, length, 1, IMM_SP_CONTACT, 0);
		}

		FreeXMLString(&pMessage);
	}
#endif
	return retCode;
}


/************************************************************************/
//HookNtfSubscribemsg
/************************************************************************/
// IMnetRetCode HookNtfSubscribemsg(IMnetHandle hIMnetHandle, Event* pEvt)
// {
// 	IMnet* pIMnet = (IMnet*)hIMnetHandle;
// 	ImNtfSubscribeMsg* pMsg = (ImNtfSubscribeMsg*)pEvt->pContent;
// 	IMnetRetCode retCode;
// 	Event* pEvent = NULL;
// 
// 	retCode = BuildIMSubscribeEvent(pIMnet, (AMUInt8*)pMsg->message, pMsg->messageLen, &pEvent, 1);
// 	if(retCode == eOK)
// 		PacketConnectionSendtoCallback(pEvent);
// 
// 	return eIMnetSkip;
// }

/************************************************************************/
// extern interface.
/************************************************************************/
/************************************************************************/
// IMnetCallback
//		|		 ------------
//      |------> [ id        ]
//               [ pFirstCB  ]  --> [CallbackItem] --> [CallbackItem] --> NULL
//               [ pNext     ]
//               -------------
//                    |
//				 ------------
//               [ id        ]
//               [ pFirstCB  ]  --> [CallbackItem] --> [CallbackItem] --> NULL
//               [ pNext     ]
//               -------------
//                    |
//                   NULL
/************************************************************************/
IMnetCallback* IMnetCallbackCreate()
{
	IMnetCallback* p = NULL;

	IMnetCallbackHook(&p, IM_PACK_LOGIN_IND,	HookPackLoginInd);
	
	IMnetCallbackHook(&p, IM_RSP_CHECKVERSION,	HookCheckVersion);
	IMnetCallbackHook(&p, IM_RSP_LOGIN,			HookRspLogin);
	IMnetCallbackHook(&p, IM_RSP_RELOGIN,		HookRspReLogin);

	IMnetCallbackHook(&p, IM_NTF_IMMESSAGE,		HookNtfIMmessage);
	IMnetCallbackHook(&p, IM_RSP_GETOFFLINEMSG, HookGetOfflineMsg);
	IMnetCallbackHook(&p, IM_RSP_ADDCONTACT,	HookAddContact);
	IMnetCallbackHook(&p, IM_RSP_ADDCNTACK,		HookRspAddCntAck);

	return p;
}

/************************************************************************/
// IMnetCallbackDestory
/************************************************************************/
void IMnetCallbackDestory(IMnetCallback* pCallback)
{
	//释放所有的注册函数
	if(pCallback)
	{
		IMnetCallbackDestoryBlock(pCallback->pHookFirst);
		IMnetCallbackDestoryBlock(pCallback->pRegisterFirst);
		AMFree(pCallback);
	}
}

void IMnetCallbackDestoryBlock(CallbackBlock* pBlock)
{
	CallbackBlock*  pBlockTemp	= NULL;
	CallbackItem*	pItem		= NULL;
	CallbackItem*	pItemTemp	= NULL;

	while(pBlock)
	{
		pItem = pBlock->pFirstCB;
		while(pItem)
		{
			pItemTemp = pItem;
			pItem = pItem->pNext;
			AMFree(pItemTemp);
		}
		pBlockTemp = pBlock;
		pBlock = pBlock->pNext;
		AMFree(pBlockTemp);
	}
}

/************************************************************************/
// IMnetCallbackHandle
/************************************************************************/
IMnetRetCode IMnetCallbackHandle(IMnet* pIMNet, Event* pEvent)
{
	IMnetRetCode retCode = eOK;

	if(pIMNet == NULL || pEvent == NULL)
		return eInvalidParam;

	//hook call
	if(pEvent->id >= EVENT_CUSTOMIZE_MAX) //此定义参看IMnetEventDef.h文件描述
		retCode = IMnetCallbackHandleBlock(pIMNet, pIMNet->pIMnetCallback->pHookFirst, pEvent, 0);
	//register call
	if(retCode != eIMnetSkip)
		IMnetCallbackHandleBlock(pIMNet, pIMNet->pIMnetCallback->pRegisterFirst, pEvent, 1);

	return eOK;
}

IMnetRetCode IMnetCallbackHandleBlock(IMnet* pIMNet, CallbackBlock* pBlockFit, Event* pEvent, AMInt32 type)
{
	IMnetRetCode retCode;
	CallbackItem* pItemFit = NULL;

	
	while(pBlockFit)
	{
		if(pBlockFit->id == pEvent->id)
		{
			pItemFit = pBlockFit->pFirstCB;
			while(pItemFit)
			{
				if(type == 0) // hook
					retCode = pItemFit->pCallbackHook(pIMNet, pEvent);
				else //register
					retCode = pItemFit->pCallback(pIMNet, pEvent->pContent);
				
				if(retCode == eIMnetSkip || retCode == eIMnetEventExchange)
				{
					//碰到此类返回，将不会回调剩下的注册函数
					return retCode;
				}

				pItemFit = pItemFit->pNext;
			}

			return eOK;
		}
		pBlockFit = pBlockFit->pNext;
	}
	return eOK;
}

/************************************************************************/
// IMnetCallbackRegister
/************************************************************************/
IMnetRetCode IMnetCallbackRegister(IMnetCallback** ppCallback, EventId id, CallbackFunc pCallbackFunc)
{	
	CallbackFuncUnion func;
	if(ppCallback == NULL || pCallbackFunc == NULL)
		return eInvalidParam;

	//if null, create callback cross lists.
	if(*ppCallback == NULL)
	{
		*ppCallback = (IMnetCallback*)AMMalloc(sizeof(IMnetCallback));
		if(*ppCallback == NULL)
			return eMallocError;

		(*ppCallback)->pHookFirst = NULL;
		(*ppCallback)->pRegisterFirst = NULL;
	}
	
	func.pCallback = pCallbackFunc;
	return IMnetCallbackAdd(&(*ppCallback)->pRegisterFirst, id, func, 1);
}

/************************************************************************/
// IMnetCallbackUnregister
/************************************************************************/
IMnetRetCode IMnetCallbackUnregister(IMnetCallback** ppCallback, EventId id, CallbackFunc pCallbackFunc)
{
	CallbackFuncUnion func;
	if(ppCallback == NULL || pCallbackFunc == NULL)
		return eInvalidParam;

	if(*ppCallback == NULL) //empty list.
		return eOK;

	func.pCallback = pCallbackFunc;
	IMnetCallbackRemove(&(*ppCallback)->pRegisterFirst, id, func, 1);

	if((*ppCallback)->pRegisterFirst == NULL && (*ppCallback)->pHookFirst == NULL)
	{
		AMFree(*ppCallback);
		*ppCallback = NULL;
	}

	return eOK;
}

/************************************************************************/
// IMnetCallbackHook
/************************************************************************/
IMnetRetCode IMnetCallbackHook(IMnetCallback** ppCallback, EventId id, CallbackFuncHook pCallbackFunc)
{	
	CallbackFuncUnion func;

	if(ppCallback == NULL || pCallbackFunc == NULL)
		return eInvalidParam;

	//if null, create callback cross lists.
	if(*ppCallback == NULL)
	{
		*ppCallback = (IMnetCallback*)AMMalloc(sizeof(IMnetCallback));
		if(*ppCallback == NULL)
			return eMallocError;

		(*ppCallback)->pHookFirst = NULL;
		(*ppCallback)->pRegisterFirst = NULL;
	}

	func.pCallbackHook = pCallbackFunc;
	return IMnetCallbackAdd(&(*ppCallback)->pHookFirst, id, func, 0);
}

/************************************************************************/
// IMnetCallbackUnhook
/************************************************************************/
IMnetRetCode IMnetCallbackUnhook(IMnetCallback** ppCallback, EventId id, CallbackFuncHook pCallbackFunc)
{
	CallbackFuncUnion func;
	if(ppCallback == NULL || pCallbackFunc == NULL)
		return eInvalidParam;

	if(*ppCallback == NULL) //empty list.
		return eOK;

	func.pCallbackHook = pCallbackFunc;
	IMnetCallbackRemove(&(*ppCallback)->pHookFirst, id, func, 0);

	if((*ppCallback)->pRegisterFirst == NULL && (*ppCallback)->pHookFirst == NULL)
	{
		AMFree(*ppCallback);
		*ppCallback = NULL;
	}

	return eOK;
}

/************************************************************************/
// 列表操作-Add
/************************************************************************/
IMnetRetCode IMnetCallbackAdd(CallbackBlock** ppCallbackBlock, EventId id, CallbackFuncUnion pCallbackFunc, AMInt32 type)
{
	CallbackBlock*  pBlock		= NULL;
	CallbackBlock*  pBlockFit	= NULL;

	CallbackItem*	pItem		= NULL;
	CallbackItem*	pItemFit	= NULL;

	if(ppCallbackBlock == NULL)
		return eInvalidParam;

	//search EventId.
	pBlockFit = *ppCallbackBlock;
	if(pBlockFit != NULL)
	{
		while(pBlockFit->id != id && pBlockFit->pNext)
			pBlockFit = pBlockFit->pNext;
	}

	if( pBlockFit == NULL || 
		(pBlockFit->pNext == NULL && pBlockFit->id != id) )
	{
		//create the first block.
		pBlock = (CallbackBlock*)AMMalloc(sizeof(CallbackBlock));
		if(pBlock == NULL)
		{
			return eMallocError;
		}
		pBlock->id	    = id;
		pBlock->pNext    = NULL;
		pBlock->pFirstCB = NULL;

		if(*ppCallbackBlock == NULL)
		{
			pBlockFit = pBlock;
			*ppCallbackBlock = pBlockFit;
		}
		else 
		{
			pBlockFit->pNext = pBlock;
			pBlockFit = pBlockFit->pNext;
		}
	}

	//search callback.
	pItemFit = pBlockFit->pFirstCB;
	if(pItemFit != NULL)
	{
		if(type == 0) //hook
		{
			if(pItemFit->pCallbackHook == pCallbackFunc.pCallbackHook)
				return eOK;
		}
		else //register
		{
			if(pItemFit->pCallback == pCallbackFunc.pCallback)
				return eOK;
		}

		while(pItemFit->pNext)
		{
			pItemFit = pItemFit->pNext;
			if(type == 0) //hook
			{
				if(pItemFit->pCallbackHook == pCallbackFunc.pCallbackHook)
					return eOK;
			}
			else //register
			{
				if(pItemFit->pCallback == pCallbackFunc.pCallback)
					return eOK;
			}
		}
	}

	//create item.
	pItem = (CallbackItem*)AMMalloc(sizeof(CallbackItem));
	if(pItem == NULL)
	{
		if(pBlock)
		{
			AMFree(pBlock);
			pBlock = NULL;
		}
		return eMallocError;
	}

	//fill item.
	if(type == 0)
		pItem->pCallbackHook = pCallbackFunc.pCallbackHook;
	else
		pItem->pCallback = pCallbackFunc.pCallback;

	pItem->pNext = NULL;

	//add new item.
	if(pItemFit == NULL)
		pBlockFit->pFirstCB = pItem;
	else
		pItemFit->pNext = pItem;
	return eOK;
}

/************************************************************************/
// 列表操作-Remove
/************************************************************************/
IMnetRetCode IMnetCallbackRemove(CallbackBlock** ppCallbackBlock, EventId id, CallbackFuncUnion pCallbackFunc, AMInt32 type)
{
	CallbackBlock* pBlockFit = NULL;
	CallbackBlock* pBlockPre = NULL;

	CallbackItem* pItemFit = NULL;
	CallbackItem* pItemPre = NULL;

	if(ppCallbackBlock == NULL)
		return eInvalidParam;

	pBlockFit = *ppCallbackBlock;
	while(pBlockFit)
	{
		if(pBlockFit->id == id)
		{
			pItemFit = pBlockFit->pFirstCB;
			while(pItemFit)
			{
				if( (type == 0 && pItemFit->pCallbackHook == pCallbackFunc.pCallbackHook) ||
					(type == 1 && pItemFit->pCallback == pCallbackFunc.pCallback) )
				{
					if(pItemFit == pBlockFit->pFirstCB) //the first item
						pBlockFit->pFirstCB = pItemFit->pNext;
					else
						pItemPre->pNext = pItemFit->pNext;

					AMFree(pItemFit);					
					break;
				}
				pItemPre = pItemFit;
				pItemFit = pItemFit->pNext;
			}	
			
			if(pBlockFit->pFirstCB == NULL)
			{
				if(pBlockFit == *ppCallbackBlock) //the first block
					*ppCallbackBlock = pBlockFit->pNext;
				else
					pBlockPre->pNext = pBlockFit->pNext;
				AMFree(pBlockFit);
				break;
			}
			else
			{
				return eOK;
			}
		}

		pBlockPre = pBlockFit;
		pBlockFit = pBlockFit->pNext;
	}

	return eOK;
}



