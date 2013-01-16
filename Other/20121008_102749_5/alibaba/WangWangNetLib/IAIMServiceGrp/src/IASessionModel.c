#include "AIMSessionModel.h"
#include "AIMAccountModel.h"
#include "AIM.h"
#include "AIMUtil.h"
#include "AIMSignature.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMStdlib.h"
//#include "../jni/OldMsgType.h"
//#include "../IAIMServiceJni/OldMsgType.h"
#include "OldMsgType.h"

#define	IM_MSG_HEAD				"\\T"

#define AIMSessionModel_Callback(pSesModel, funcName,  ...)	\
	do \
	{\
	if((pSesModel)->pReference->callback && (pSesModel)->pReference->callback->funcName)\
			(pSesModel)->pReference->callback->funcName((pSesModel)->pReference->callback->pvArg, ## __VA_ARGS__);\
	} while (0)


static AMChar* s_mobileImMessage = AMNULL;
static AMInt32 s_mobileImMessageLength = 0;

AMVoid IASessionModel_SetMobileImMessage(const AMChar* mobileImMessage)
{
	if(AMNULL == s_mobileImMessage && mobileImMessage != AMNULL)
	{
		s_mobileImMessageLength = AMStrlen(mobileImMessage);
		s_mobileImMessage = (AMChar*)AMMalloc(s_mobileImMessageLength + 1);
		AMAssert(AMNULL != s_mobileImMessage);
		AMMemset(s_mobileImMessage, 0, s_mobileImMessageLength + 1);
		strcpy(s_mobileImMessage, mobileImMessage);
		// DPRINT("IASessionModel: s_mobileImMessage=%s", s_mobileImMessage);
	}
}

AMInt32 IASessionModel_IsEndWithMobileImMsg(AMChar* msg)
{
	AMInt32 msgLength = 0;
	if(AMNULL == s_mobileImMessage || AMNULL == msg)
	{
		return 0;
	}

	msgLength = AMStrlen(msg);
	if(msgLength > s_mobileImMessageLength)
	{
		AMInt32 index = 0;
		while(s_mobileImMessageLength - index > 0)
		{
			if(msg[msgLength - index - 1] == s_mobileImMessage[s_mobileImMessageLength - index - 1])
			{
				++index;
			}
			else
			{
				return 0;
			}
		}

		return 1;
	}

	return 0;
}

AMChar* IASessionModel_TruncateWithMobileImMsg(AMChar* msg)
{
	if(AMNULL == s_mobileImMessage || AMNULL == msg)
	{
		return AMNULL;
	}

	if(IASessionModel_IsEndWithMobileImMsg(msg))
	{
		AMInt32 msgLength = AMStrlen(msg);
		if(msgLength >= s_mobileImMessageLength + 2 && msg[msgLength - s_mobileImMessageLength - 2] == '\r' && msg[msgLength - s_mobileImMessageLength - 1] == '\n') {
			int length = msgLength - s_mobileImMessageLength - 2;
			AMChar* newMsg = (AMChar*)AMMalloc(length + 1);
			AMAssert(AMNULL != newMsg);
			AMMemset(newMsg, 0, length + 1);
			memcpy(newMsg, msg, length);
			return newMsg;
		} else if(msg[msgLength - s_mobileImMessageLength - 1] == '\n' || msg[msgLength - s_mobileImMessageLength - 1] == '\r') {
			int length = msgLength - s_mobileImMessageLength - 1;
			AMChar* newMsg = (AMChar*)AMMalloc(length + 1);
			AMAssert(AMNULL != newMsg);
			AMMemset(newMsg, 0, length + 1);
			memcpy(newMsg, msg, length);
			return newMsg;
		}
	}
	return AMNULL;
}


AMVoid				IASessionModel_ListenIMnet(IASessionModel *pCntModel, IMnetHandle pNetModel);
IASessionModel	*	IASessionModel_Create(IAIM *pIM)
{
	IASessionModel	*pRet = 0;
	pRet = (IASessionModel*)AMMalloc(sizeof(IASessionModel));
	AMAssert(0 != pRet);
	AMMemset(pRet, 0, sizeof(IASessionModel));

	construct(OHTable, &pRet->ohtSession, sizeof(IASession), FREEOBJ);
	set_dealloc(OHTable, &pRet->ohtSession, IASession_Destroy);
	set_compare(OHTable, &pRet->ohtSession, IASession_Cmp);
	set_hash_OHTable(&pRet->ohtSession, IASession_Hash);
	
	pRet->pReference = pIM;
	
	return pRet;
}
#define		SQL_CREATE_MST_TABLE	"CREATE TABLE IF NOT EXISTS _msg(\
																		_rid INTEGER PRIMARY KEY AUTOINCREMENT, \
																		_peerid VARCHAR(64),\
																		_type SMALLINT,\
																		_time INTEGER,\
																		_content TEXT,\
																		_unread SMALLINT\
																	);"
#define		SQL_MARKREAD_MSG	"UPDATE _msg SET _unread=0;"
AMInt32				IASessionModel_InitDB(IASessionModel *pSesModel)
{
	AMInt32 rcSqlite = 0;
	AMChar *szErrMsg = 0;

	AMAssert(0 != pSesModel && 0 != pSesModel->pReference && 0 != pSesModel->pReference->pAcnt);

	if (0 != pSesModel->pDB)
	{
		sqlite3_close(pSesModel->pDB);
		pSesModel->pDB = 0;
	}
	rcSqlite = myADB_Open(pSesModel->pReference->pAcnt->szID, &pSesModel->pDB, AMFALSE);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel: Can't open database: %s", sqlite3_errmsg(pSesModel->pDB));
		sqlite3_close(pSesModel->pDB);
		pSesModel->pDB = 0;
		return -1;
	}
	
	rcSqlite = sqlite3_exec(pSesModel->pDB, SQL_CREATE_MST_TABLE, 0, 0, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel: Can't %s for %s\n", SQL_CREATE_MST_TABLE, szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	rcSqlite = sqlite3_exec(pSesModel->pDB, SQL_MARKREAD_MSG, 0, 0, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel: Can't %s for %s\n", SQL_MARKREAD_MSG, szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	return 0;
}

AMInt32				IASessionModel_StoreMsg(IASessionModel *pSesModel, IAIMessage *pMsg, AMBool bSave)
{
	AMInt32 rcSqlite = 0;
	AMChar *szErrMsg = AMNULL, *szSql = AMNULL, *szMsgContent = AMNULL;
	AMBool	bUnread = AMTRUE;

	AMAssert(0 != pSesModel && 0 != pSesModel->pDB && 0 != pMsg);

	if(0 == pSesModel->pDB)//为什么会空？ 还没登录
		return -1;
	
	//记录消息的时间?
	if(pMsg->iServerTime < 1000)// time from epoch(in seconds)
		pMsg->iServerTime = AMGetUpTime(0) + pSesModel->pReference->iTimeDiff;

	if( !bSave || !IAIMessage_NeedSave(pMsg) )
		return 0;
		
	szSql = sqlite3_mprintf(SQL_INSERT_MSG, pMsg->szContactID?pMsg->szContactID:"0", pMsg->eType, pMsg->iServerTime, pMsg->szContent?pMsg->szContent:"0", pMsg->bUnread);
	if(AMNULL == szSql)
		return eAIM_RESULT_MALLOC_ERROR;

	DPRINT("%s >>>>>> szSql: %s\n", __FUNCTION__, szSql);

	rcSqlite = sqlite3_exec(pSesModel->pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel_StoreMsg.............: can not BEGIN TRANSACTION;, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_free(szSql);
		return -1;
	}

	rcSqlite = sqlite3_exec(pSesModel->pDB, szSql, 0, 0, &szErrMsg);
	sqlite3_free(szSql);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel_StoreMsg.............: can not INSERT, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	pMsg->_iRid = sqlite3_last_insert_rowid(pSesModel->pDB);

	rcSqlite = sqlite3_exec(pSesModel->pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel_StoreMsg.............: can not COMMIT TRANSACTION;, for: %s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		return -1;
	}

	return 0;
}

AMVoid				IASessionModel_ClearData(IASessionModel *pSesModel)
{
	AMAssert(0 != pSesModel);

	clear(OHTable, &pSesModel->ohtSession);
}

AMInt32				IASessionModel_CloseDB(IASessionModel *pSesModel)
{
	AMAssert(0 != pSesModel);

	if(pSesModel->pDB)
	{
		sqlite3_close(pSesModel->pDB);
		pSesModel->pDB = 0;
	}
	
	IASessionModel_ClearData(pSesModel);
	
	return 0;
}

AMVoid				IASessionModel_Destroy(IASessionModel *pSesModel)
{
	AMAssert(0 != pSesModel);
	
	destruct(OHTable, &pSesModel->ohtSession);

	if(pSesModel->pDB)
	{
		sqlite3_close(pSesModel->pDB);
		pSesModel->pDB = 0;
	}

	AMFree(pSesModel);
}

AMVoid AIMSessionModel_DeleteMsgById(IASessionModel *pSesModel, AMInt64 i64MsgId)
{
	IASession *pTmpSes = NULL;
	IAIMessage *pMsg = AMNULL;
	AMInt32		iCount = 0;
	pTmpSes = IASession_Create("TMP_ONLY", pSesModel);
	AMAssert( pSesModel && pTmpSes && i64MsgId);

	AIMSession_GetMsgs(pTmpSes, (AMInt32)i64MsgId, 0, AMTRUE, (AMHandle**)&pMsg, &iCount);

	if(iCount)
	{

		AMFree(pTmpSes->szContactID);

		if(pMsg->eType<eMSG_TYPE_CHAT_AUTO+1)//聊天消息
		{
			AMAssert(pMsg->szContactID);
			pTmpSes->szContactID = pMsg->szContactID;
			AIMSession_RemoveMsg(pTmpSes, pMsg->_iRid, pMsg->bUnread);
		}
		else	//系统消息
		{
			pTmpSes->szContactID = SYS_SES_NAME;
			AIMSession_RemoveMsg(pTmpSes, pMsg->_iRid, pMsg->bUnread);
		}

		pTmpSes->szContactID = NULL;
		IAIMSession_ReleaseMsgs(pTmpSes, (AMHandle*)pMsg, iCount);
	}

	IASession_Destroy(pTmpSes);
}
/**
 * 先把消息选出来，如果是有且未读，则交给对应的Session，让Session给markRead.
 */
AMVoid AIMSessionModel_MarkMsgReadById(IASessionModel *pSesModel, AMInt64 i64MsgId)
{
	IASession *pTmpSes = NULL;
	IAIMessage *pMsg = AMNULL;
	AMInt32		iCount = 0;
	pTmpSes = IASession_Create("TMP_ONLY", pSesModel);
	AMAssert( pSesModel && pTmpSes && i64MsgId);

	AIMSession_GetMsgs(pTmpSes, (AMInt32)i64MsgId, 0, AMTRUE, (AMHandle**)&pMsg, &iCount);

	if(iCount)
	{
		if(!pMsg->bUnread)
		{
			IAIMSession_ReleaseMsgs(pTmpSes, (AMHandle*)pMsg, iCount);
			IASession_Destroy(pTmpSes);
			return;
		}

		AMFree(pTmpSes->szContactID);

		if(pMsg->eType<eMSG_TYPE_CHAT_AUTO+1)//聊天消息
		{
			AMAssert(pMsg->szContactID);
			pTmpSes->szContactID = pMsg->szContactID;
			IAIMSession_MarkMsgRead(pTmpSes, pMsg->_iRid);
		}
		else	//系统消息
		{
			pTmpSes->szContactID = SYS_SES_NAME;
			IAIMSession_MarkMsgRead(pTmpSes, pMsg->_iRid);
		}

		pTmpSes->szContactID = NULL;
		IAIMSession_ReleaseMsgs(pTmpSes, (AMHandle*)pMsg, iCount);
	}

	IASession_Destroy(pTmpSes);
}

void IASessionModel_DeleteAllMsg(IASessionModel *pSesModel)
{
	int rcSqlite = 0;
	AMChar *szErrMsg = 0;
	AMChar	*szSql = 0;
	AMAssert(0 != pSesModel && 0 != pSesModel->pDB);
	
	rcSqlite = sqlite3_exec(pSesModel->pDB, "DELETE FROM _msg;", 0, 0, &szErrMsg);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASessionModel_DeleteAllMsg.............: can not DELETE FROM _msg;, for: %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
	}

	DPRINT("IASessionModel_DeleteAllMsg..................OK\n");
}

IAIM		*	IASessionModel_GetReference(IASessionModel *pSesModel)
{
	AMAssert(0 != pSesModel);
	return pSesModel->pReference;
}

AIM_RESULT IAIMSessionModel_OpenSession( AMHandle hSessionModel, const AMChar *szContactID, AMHandle *phSession )
{
	IASessionModel *pSesModel = (IASessionModel *)hSessionModel;
	IASession *pTmpSes = 0, *pSesFind = 0;

	AMAssert(0 != pSesModel && 0 != szContactID);

	if(AMNULL == (pTmpSes = IASession_Create(szContactID, pSesModel)))
	{
		return eAIM_RESULT_MALLOC_ERROR;
	}

	pSesFind = (IASession*)find_OHTable(&pSesModel->ohtSession, pTmpSes, sizeof(IASession));
	if(0 != pSesFind)
	{
		IASession_Destroy(pTmpSes);
		*phSession = pSesFind;
	}
	else
	{
		pTmpSes->pSesModel = pSesModel;
		insert_OHTable(&pSesModel->ohtSession, pTmpSes, sizeof(IASession), DYNAMIC);
		*phSession = pTmpSes;
	}

	return eAIM_RESULT_OK;
}

AMInt32				IASessionModel_OnIncomingSysMsg(IASessionModel *pSesModel, IAIMessage *pMsg)
{
	IASession *pSysSes = AMNULL;
	AIM_NTF_MSG ntfMsg;
	AMAssert(0 != pSesModel && 0 != pMsg);

	IASessionModel_StoreMsg(pSesModel, pMsg, AMTRUE);

	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, SYS_SES_NAME, &pSysSes))
	{
		DPRINT("IASessionModel_OnIncomingSysMsg..................Error!\n");
		AMAssert(0);
	}

	ntfMsg.hSession = pSysSes;
	ntfMsg.hMessage = pMsg;
	
	AIMSessionModel_Callback(pSesModel, OnNtfMesage, &ntfMsg);
	
	return 0;
}

#define MSG_REDIRECTION_NOTE		"\\L#OpenChatDlg?id="

AMInt32				IASessionModel_OnIncomingChatMsg(IASessionModel *pSesModel, IAIMessage *pMsg)
{
	IAContact	*pCntTmp = 0;
	IAGroup		*pGrpTmp = 0;

	IASession *pSes = 0;
	AIM_NTF_MSG ntfMsg;

	AMChar* truncatedMsg = AMNULL, *szRedirect = AMNULL;

	AMAssert(0 != pSesModel && 0 != pMsg);

	DPRINT("IASessionModel_OnIncomingChatMsg: s_mobileImMessage=%s\n", s_mobileImMessage);
	DPRINT("IASessionModel_OnIncomingChatMsg: content=%s\n", pMsg->szContent);
#if AIM_ANDROID_ALAN
	truncatedMsg = IASessionModel_TruncateWithMobileImMsg(pMsg->szContent);
	if(truncatedMsg != NULL)
	{
		AMFree(pMsg->szContent);
		pMsg->szContent = truncatedMsg;
	}
#endif

	szRedirect = AMStrstr(pMsg->szContent, MSG_REDIRECTION_NOTE);
	if(szRedirect)
		*szRedirect = 0;

	IASessionModel_StoreMsg(pSesModel, pMsg, AMTRUE);

	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, pMsg->szContactID, &pSes))
	{
		DPRINT("IASessionModel_OnIncomingChatMsg..................Error!\n");
		AMAssert(0);
	}

	AMAssert(0 != pSes);

	//更新组未读消息数癿

	if(pMsg->eType != eMSG_TYPE_FILE)//图片的时候，就不更新了?
		IAIMContactModel_GetContactByID(pSesModel->pReference->pCntModel, pMsg->szContactID, &pCntTmp);
	if(pCntTmp)
	{
		pCntTmp->iUnreadCnt++;

		pGrpTmp = pCntTmp->pParentGrp;
		if(0 == pGrpTmp)
		{
			DPRINT("IASessionModel_OnIncomingChatMsg............................Contact is not in any group!\nt");
			pGrpTmp = pSesModel->pReference->pCntModel->pStrangerGrp;	
		}
		pGrpTmp->iUnreadMsgCnt++;
		
		DPRINT("IASessionModel_OnIncomingChatMsg.........................Group "I64FORMAT",  has %d unreadMsg\n", pGrpTmp->iGroupID, pGrpTmp->iUnreadMsgCnt);
	}	
	
	ntfMsg.hMessage = pMsg;
	ntfMsg.hSession = pSes;

	AIMSessionModel_Callback(pSesModel, OnNtfMesage, &ntfMsg);

	return 0;
}

AIM_RESULT IAIMSessionModel_CloseSession( AMHandle hSessionModel, AMHandle hSession )
{
	IASessionModel *pSesModel = (IASessionModel*)hSessionModel;
	IASession *pSes = (IASession *)hSession;
	AMAssert(0 != pSesModel && 0 != pSes);

	delete_OHTable(&pSesModel->ohtSession, pSes, sizeof(IASession));

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMSessionModel_GetSessions( AMHandle hSessionModel, const OHTable **ppOht )
{
	IASessionModel *pSesModel = (IASessionModel*)hSessionModel;
	AMAssert(AMNULL != pSesModel && AMNULL != ppOht);

	*ppOht = &pSesModel->ohtSession;

	return eAIM_RESULT_OK;
}

IMnetRetCode	IASessionModel_OnChatMsg(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventChatMessage *pEvent = (ImEventChatMessage*)pEventContent;
	IAContact	*pTmpCnt = 0, *pCntFind = 0, *pCntEMain = AMNULL;
	IAIMessage	*pIMsg = 0;
	IAIM		*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IASessionModel *pSesModel = pIM->pSesModel;
	AMBool	bTmp = AMFALSE;
	
	while(0 != pEvent)
	{		
		pTmpCnt = IAContact_Create();
		IAContact_SetCntID(pTmpCnt, pEvent->msg.fromId, pEvent->msg.fromIdLen);		

		IAContact_AutoSetBindUid(pSesModel->pReference, pTmpCnt);
		IMnetPutBindInfo(pSesModel->pReference->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID): 0);
		if(pEvent->msg.online)
		{//发送ACK消息到服务器
			IMnetSendMessageEx(hIMnetHandle, 
				pEvent->msg.fromId,
				pEvent->msg.fromIdLen,
				NULL, 0, 0, 4, 
				pEvent->ackSeq);
		}

		pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
		if(0 == pCntFind)
		{
			AMChar *pEcustomFlag = AMStrchr(pTmpCnt->szID, ':');
			if(pEcustomFlag)//if this is a e customer id.
			{
				*pEcustomFlag = 0;
				pCntEMain = (IAContact*)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
				*pEcustomFlag = ':';
			}
			pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
		}
		IAContact_Destroy(pTmpCnt);
		
		if(0 != pCntFind)
		{
			IAIMContact_IsBlack(pCntFind, &bTmp);
			
			if( AMTRUE == bTmp)
			{
				DPRINT("IASessionModel_OnChatMsg..............Msg From Black %s\n", pCntFind->szID);
				return eIMnetSkip;
			}
			else
			{
				IAIMContact_IsStrange(pCntFind, &bTmp);
				if(bTmp && (pIM->pAcnt->uiFlag & 0x40) && !pCntEMain && pEvent->msg.iServerType)//EMain is not a friend.
				{
					DPRINT("IASessionModel_OnChatMsg..............Msg From Stranger Blocked.%s\n", pCntFind->szID);
					return eIMnetSkip;
				}
			}
		}
		else if((pIM->pAcnt->uiFlag & 0x40) && !pCntEMain && pEvent->msg.iServerType)
		{
			DPRINT("IASessionModel_OnChatMsg..............Msg From Stranger Blocked.%s\n", pEvent->msg.fromId);
			return eIMnetSkip;
		}
		else
		{//cant't find in friends and strangers, a new stranger
			pTmpCnt = IAContact_Create();
			IAContact_SetCntID(pTmpCnt, pEvent->msg.fromId, pEvent->msg.fromIdLen);		
			IAContact_SetNickName(pTmpCnt, pEvent->msg.fromId+8, pEvent->msg.fromIdLen-8);		
			IAContact_SetPinyin(pTmpCnt,pEvent->msg.fromId+8, pEvent->msg.fromIdLen-8);
			IAContact_AutoSetBindUid(pIM, pTmpCnt);
			insert_OHTable(&pIM->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact), DYNAMIC);
		}

		pIMsg = IAIMessage_Create();
		pIMsg->bUnread = AMTRUE;
		pIMsg->iServerTime = pEvent->msg.sendTime;
		IAIMessage_SetCntID(pIMsg, pEvent->msg.fromId, pEvent->msg.fromIdLen);
		IAIMessage_SetContent(pIMsg, pEvent->msg.msgContent, pEvent->msg.msgContentLen);
		
		//此处还可以加上是否离线消息，根据pEvent->msg.online;
		if(!pEvent->msg.iType)
			pIMsg->eType = eMSG_TYPE_CHAT_RECV;
		else
		{
#if 0	//测试璿
			IAIM_ReceiveFile(pIM, pIMsg->szContactID, pIMsg->szContent, "hello.jpg", AMNULL);
#endif
			pIMsg->eType = eMSG_TYPE_FILE;
		}

		//加到最近联系人的队餿
		IAContactModel_UpdateRecent(pIM->pCntModel, pIMsg->szContactID, pEvent->msg.msgContent, pEvent->msg.msgContentLen, AMTRUE);

		IASessionModel_OnIncomingChatMsg(pSesModel, pIMsg);

		IAIMessage_Destroy(pIMsg);

		pEvent = pEvent->next;
	}

	return eIMnetSkip;
}

IMnetRetCode	IASessionModel_OnOperationTip(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventOperationTip *pEvnt = (ImEventOperationTip *)pEventContent;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	IAIMessage	*pIMsg = 0;
	IAIM		*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IASessionModel *pSesModel = pIM->pSesModel;
	IASession	*pSes = 0;
	AMBool	bTmp = AMFALSE;

	pTmpCnt = IAContact_Create();

	IAContact_SetCntID(pTmpCnt, pEvnt->contactId, pEvnt->contactIdLen);
	pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
		pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
	IAContact_Destroy(pTmpCnt);

	if(pCntFind)
	{
		IAIMContact_IsBlack(pCntFind, &bTmp);
		if(AMTRUE == bTmp)
		{
			DPRINT("IASessionModel_OnOperationTip..............Msg From Black %s\n", pCntFind->szID);
			return eIMnetSkip;
		}
	}
	else
	{
		return eIMnetSkip;
	}

	pIMsg = IAIMessage_Create();
	pIMsg->bUnread = AMTRUE;
	pIMsg->iServerTime = 0;//pEvnt->ntfTime;
	IAIMessage_SetCntID(pIMsg, pEvnt->contactId, pEvnt->contactIdLen);
	IAIMessage_SetContent(pIMsg, pEvnt->messageType, pEvnt->msgTypeLen);
	pIMsg->eType = eMSG_TYPE_OPERATION;
	
	DPRINT("IASessionModel_OnOperationTip..............From: %s, Content: %s, time: %d\n", pIMsg->szContactID, pIMsg->szContent, pIMsg->iServerTime);

	IASessionModel_OnIncomingChatMsg(pSesModel, pIMsg);

	IAIMessage_Destroy(pIMsg);

	return eIMnetSkip;
}


IMnetRetCode	IASessionModel_OnAutoReply(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventAutoReply *pEvent = (ImEventAutoReply*)pEventContent;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	IAIMessage	*pIMsg = 0;
	IAIM		*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IASessionModel *pSesModel = pIM->pSesModel;
	IASession	*pSes = 0;
	AMBool	bTmp = AMFALSE;

	while(pEvent)
	{
		pTmpCnt = IAContact_Create();

		IAContact_SetCntID(pTmpCnt, pEvent->msg.fromId, pEvent->msg.fromIdLen);
		pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
		if(0 == pCntFind)
			pCntFind = (IAContact*)find_OHTable(&pIM->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));
		IAContact_Destroy(pTmpCnt);

		if(AMNULL != pCntFind	)
		{
			IAIMContact_IsBlack(pCntFind, &bTmp);
			if(AMTRUE == bTmp)
			{
				DPRINT("IASessionModel_OnAutoReply..............Msg From Black %s\n", pCntFind->szID);
				return eIMnetSkip;
			}
		}		

		pIMsg = IAIMessage_Create();
		pIMsg->bUnread = AMTRUE;
		pIMsg->iServerTime = pEvent->msg.sendTime;
		IAIMessage_SetCntID(pIMsg, pEvent->msg.fromId, pEvent->msg.fromIdLen);
		IAIMessage_SetContent(pIMsg, pEvent->msg.msgContent, pEvent->msg.msgContentLen);
		pIMsg->eType = eMSG_TYPE_CHAT_AUTO;

		//加到最近联系人的队餿
		IAContactModel_UpdateRecent(pIM->pCntModel, pIMsg->szContactID, pEvent->msg.msgContent, pEvent->msg.msgContentLen, AMTRUE);

		DPRINT("IASessionModel_OnAutoReply..............From: %s, Content: %s, time: %d\n", pIMsg->szContactID, pIMsg->szContent, pIMsg->iServerTime);

		IASessionModel_OnIncomingChatMsg(pSesModel, pIMsg);

		IAIMessage_Destroy(pIMsg);

		pEvent = pEvent->next;
	}

	return eIMnetSkip;
}

IMnetRetCode	IASessionModel_OnAddedByContact(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventContactAdded *pEvent = (ImEventContactAdded*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	IAContactModel	*pCntModel = pIM->pCntModel;
	IAIMessage	*pMsg = 0;
	IAContact	*pCntFind = AMNULL, *pTmpCnt = AMNULL;
	AIM_NTF_ADDED_BY ntfAddedBy;

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, pEvent->fromID, pEvent->fromIDLen);
	set_compare(List, &pIM->pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
	pCntFind = find_List(&pIM->pCntModel->pBlkGrp->lChildCnt, pTmpCnt, sizeof(IAContact));
	set_compare(List, &pIM->pCntModel->pBlkGrp->lChildCnt, IAContact_CmpPinyin);

	if(pCntFind)	//如果是黑名单，则不处玿
	{
		IAContact_Destroy(pTmpCnt);
		return eIMnetOK;
	}

	//add by pw 2011-7-24, add in temp contacts
	pCntFind = find_OHTable(&pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
	{
		IAContact_SetBindUid(pTmpCnt, pEvent->bindID, pEvent->bindIDLen);
		insert_OHTable(&pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact), DYNAMIC);
	}
	else
		IAContact_Destroy(pTmpCnt);

		
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = eMSG_TYPE_CONTACT_ADDED_BY;
	IAIMessage_SetCntID(pMsg, pEvent->fromID, pEvent->fromIDLen);

	DPRINT("IASessionModel_OnAddedByContact.................By %s\n", pMsg->szContactID);

	IASessionModel_OnIncomingSysMsg(pIM->pSesModel, pMsg);

	IAIMessage_Destroy(pMsg);

	ntfAddedBy.szContactId = pEvent->fromID;

	AIMSessionModel_Callback(pIM->pSesModel, OnNtfAddedBy, &ntfAddedBy);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnAddCntVerify(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventContactAskAddVerify *pEvent = (ImEventContactAskAddVerify*)pEventContent;
	IAIM	*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IASessionModel *pSesModel = pIM->pSesModel;
	IAIMessage *pMsg = 0;
	AMInt32 i = 0;
	IAContact	*pCntFind = AMNULL, *pTmpCnt = AMNULL;
	AIM_NTF_REQUEST_FROM ntfRequestFrom;

	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, pEvent->fromID, pEvent->fromIDLen);
	set_compare(List, &pIM->pCntModel->pBlkGrp->lChildCnt, IAContact_CmpID);
	pCntFind = find_List(&pIM->pCntModel->pBlkGrp->lChildCnt, pTmpCnt, sizeof(IAContact));
	set_compare(List, &pIM->pCntModel->pBlkGrp->lChildCnt, IAContact_CmpPinyin);

	if(pCntFind)	//如果是黑名单，则不处玿
	{
		IAContact_Destroy(pTmpCnt);
		return eIMnetOK;
	}

	//add by pw 2011-7-24, add in temp contacts
	pCntFind = find_OHTable(&pIM->pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
	{
		IAContact_SetBindUid(pTmpCnt, pEvent->bindID, pEvent->bindIDLen);
		insert_OHTable(&pIM->pCntModel->ohtTmps, pTmpCnt, sizeof(IAContact), DYNAMIC);
	}
	else
		IAContact_Destroy(pTmpCnt);



	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	IAIMessage_SetCntID(pMsg, pEvent->fromID, pEvent->fromIDLen);

	IAIMessage_SetContent(pMsg, pEvent->verifyInfo, pEvent->verifyInfoLen);

	pMsg->eType = eMSG_TYPE_CONTACT_REQ_FROM;

	DPRINT("IASessionModel_OnAddCntVerify.........From %s, Info %s\n", pMsg->szContactID, pMsg->szContent);

	IASessionModel_OnIncomingSysMsg(pSesModel, pMsg);

	ntfRequestFrom.szContactId = pMsg->szContactID;
	ntfRequestFrom.szVerifyInfo = pMsg->szContent;
	AIMSessionModel_Callback(pIM->pSesModel, OnNtfRequestFrom, &ntfRequestFrom);

	IAIMessage_Destroy(pMsg);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnAskAddNo(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventContactAskAddNo *pEvent = (ImEventContactAskAddNo*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	IAIMessage	*pIMsg = 0;
	AIM_NTF_REJECTED_BY ntfRejectedBy;

	pIMsg = IAIMessage_Create();
	pIMsg->bUnread = AMTRUE;
	pIMsg->eType = eMSG_TYPE_CONTACT_REJECTED_BY;
	IAIMessage_SetCntID(pIMsg, pEvent->fromID, pEvent->fromIDLen);
	IAIMessage_SetContent(pIMsg, pEvent->msg, pEvent->msgLen);

	DPRINT("IASessionModel_OnAskAddNo..................From %s, Info %s\n", pIMsg->szContactID, pIMsg->szContent);

	IASessionModel_OnIncomingSysMsg(pIM->pSesModel, pIMsg);

	ntfRejectedBy.szContactId = pIMsg->szContactID;
	ntfRejectedBy.szInfo = pIMsg->szContent;
	AIMSessionModel_Callback(pIM->pSesModel, OnNtfRejectedBy, &ntfRejectedBy);

	IAIMessage_Destroy(pIMsg);

	return eIMnetOK;
}
extern IMnetRetCode	IAContactModel_OnAddContact(IMnetHandle hIMnetHandle, EventContent* pEventContent);
//不会再发辿IM_EVENT_ADDCONTACT 给ContactModle, 此处需要做添加好友的处理?/此处还需要做状态订閿
IMnetRetCode	IASessionModel_OnAskAddYes(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventContactAskAddYes *pEvent = (ImEventContactAskAddYes*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	
	ContactList		cntList;
	ImEventAddContact	MyEvent;
	AIMAccount	*pAcntFind = 0;

	AIM_NTF_ACCEPTED_BY ntfAcceptedBy;

	ntfAcceptedBy.szContactId= pEvent->fromID;
	AIMSessionModel_Callback(pIM->pSesModel, OnNtfAcceptedBy, &ntfAcceptedBy);
	
	//转发添加好友成功消息给ContactModel
	AMMemset(&MyEvent, 0, sizeof(ImEventAddContact));
	MyEvent.retCode = 0;
	MyEvent.contactInfo.contactID = pEvent->fromID;
	MyEvent.contactInfo.contactIDLen = pEvent->fromIDLen;
	MyEvent.contactInfo.nickName = pEvent->fromID+ID_HEAD_LEN;
	MyEvent.contactInfo.nickNameLen = pEvent->fromIDLen-ID_HEAD_LEN;

	AMAssert(0 != pIM && 0 != pIM->pAcnt && 0 != pIM->pAcnt->szID);//时间憿
	pAcntFind = IAccountModel_findHistoryAcnt(pIM->pAcntModel, pIM->pAcnt->szID);
	AMAssert(0 != pAcntFind);
	MyEvent.timestamp = pAcntFind->iContactStamp;// + 1?

	AMMemset(&cntList, 0, sizeof(ContactList));
	cntList.userID = pEvent->fromID;
	cntList.userIDLen = pEvent->fromIDLen;
	IMnetSubscribeContactInfo(pIM->pNetModel, &cntList, 1);
	
	return IAContactModel_OnAddContact(hIMnetHandle, (EventContent* )&MyEvent); 
}

IMnetRetCode	IASessionModel_OnSubMsg(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventNtfSubscribeMsg *pEvent = (ImEventNtfSubscribeMsg*)pEventContent;
	IAIM	*pIM	= (IAIM*)IMnetGetReference(hIMnetHandle);
	IAIMessage	*pMsg = 0;
	AMInt32	i = 0;
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = eMSG_TYPE_SUBSCRIBE;

	while(pEvent)
	{
		IAIMessage_SetContent(pMsg, pEvent->message, pEvent->messageLen);

		DPRINT("IASessionModel_OnSubMsg............. Content %s\n", pMsg->szContent);

		IASessionModel_OnIncomingSysMsg(pIM->pSesModel, pMsg);

		pEvent = pEvent->next;
	}
	IAIMessage_Destroy(pMsg);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnSysMsg(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventNtfSystemMessage *pEvent = (ImEventNtfSystemMessage*)pEventContent;
	IAIM *pIM = (IAIM*)IMnetGetReference(hIMnetHandle);

	IAIMessage	*pMsg = 0;
	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMTRUE;
	pMsg->eType = eMSG_TYPE_SYSTEM;
	
	DPRINT("%s >>>>>> cmd: %d, Style: %s, Msg: %s\n", 
		__FUNCTION__, pEvent->cmdId, pMsg->szContactID, pMsg->szContent);

	if(!pEvent->style || !pEvent->message)//空的消息不处玿
		return eIMnetOK;

	IAIMessage_SetCntID(pMsg, pEvent->style, pEvent->styleLen);
	IAIMessage_SetContent(pMsg, pEvent->message, pEvent->messageLen);

	
	IASessionModel_OnIncomingSysMsg(pIM->pSesModel, pMsg);

	IAIMessage_Destroy(pMsg);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnChangeUserVerify(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventChanageUserVerify *pEvnt = (ImEventChanageUserVerify*)pEventContent;
	IAIM *pIM = (IAIM*)IMnetGetReference(hIMnetHandle);

	AIM_RSP_CHG_VERIFY rspChgVerify;

	AMAssert(0 != pIM && 0 != pIM->pAcnt);

	DPRINT("IASessionModel_OnChangeUserVerify....................%d\n", pEvnt->addcontactFlag);

	rspChgVerify.iRetCode = pEvnt->retCode;
	if(!pEvnt->retCode)
	{
		pIM->pAcnt->iVerifyType = pEvnt->addcontactFlag;
		rspChgVerify.iVerifyConfig = pEvnt->addcontactFlag;
	}

	AIMSessionModel_Callback(pIM->pSesModel, OnRspChgVerify, &rspChgVerify);

	return eIMnetOK;
}

IMnetRetCode IASessionModel_OnChgSignature(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventChangeSignature *pEvnt = (ImEventChangeSignature*)pEventContent;
	AIM_SIGNATURE	sigStruct;

	AIM_RSP_CHG_SIGNATURE rspChgSignature;
	rspChgSignature.iRetCode = pEvnt->retCode;
	rspChgSignature.szSigNature = AMNULL;
	if(!pEvnt->retCode)
	{
		AMMemset(&sigStruct, 0, sizeof(sigStruct));
		SigXML2SigStruct(pEvnt->signature, &sigStruct);
		IAccount_SetSignature(pIM->pAcnt, sigStruct.szSignature[sigStruct.iCI], AMStrlen(sigStruct.szSignature[sigStruct.iCI]));
		IAccount_SetSigXML(pIM->pAcnt, pEvnt->signature, pEvnt->signatureLen);
		rspChgSignature.szSigNature = pIM->pAcnt->szSignature;
	}

	AIMSessionModel_Callback(pIM->pSesModel, OnRspChgSignature, &rspChgSignature);

	return eIMnetOK;
}

AIM_RESULT IAIMSessionModel_SendMsg( AMHandle hSessionModel, const AMChar *szCntID, const AMChar *szContent, AMInt32 appendMobileImMsg )
{
	/************************************************************************/
	/* 如果这个人根本不存在，怎么办？                                       */
	/************************************************************************/
	IASessionModel *pSesModel = (IASessionModel *)hSessionModel;
	IAIMessage	*pMsg = 0;
	IASession	*pTmpSes = 0, *pSesFind = 0;
	AMChar	*szTmp = 0;
	AMInt32	iMsgLen = 0;
	IAContact	*pTmpCnt = 0, *pCntFind = 0;
	AMBool	bTmp = AMFALSE;

	AMAssert(0 != pSesModel && 0 != szCntID && 0 != szContent);
	
	pTmpCnt = IAContact_Create();
	IAContact_SetCntID(pTmpCnt, szCntID, AMStrlen(szCntID));
	
	if(0 == pSesModel->pReference->pAcnt || 0 == AMStrcmp(pTmpCnt->szID, pSesModel->pReference->pAcnt->szID))//发给自己?
	{
		IAContact_Destroy(pTmpCnt);
		return eAIM_RESULT_OK;
	}

	pCntFind = (IAContact*)find_OHTable(&pSesModel->pReference->pCntModel->ohtFriends, pTmpCnt, sizeof(IAContact));
	if(0 == pCntFind)
		pCntFind = (IAContact*)find_OHTable(&pSesModel->pReference->pCntModel->ohtOthers, pTmpCnt, sizeof(IAContact));

	IAContact_Destroy(pTmpCnt);

	if(0 != pCntFind)
	{
		IAIMContact_IsBlack(pCntFind, &bTmp);
		if(AMTRUE == bTmp)
		{
			return eAIM_RESULT_OK;					//应用逻辑上不允许往黑名单中的人发送消忿.......
		}
		bTmp = IAContact_IsRevBlack(pCntFind);
	}

	pMsg = IAIMessage_Create();
	pMsg->bUnread = AMFALSE;
	pMsg->eType = eMSG_TYPE_CHAT_SEND;
	IAIMessage_SetCntID(pMsg, szCntID, AMStrlen(szCntID));

	if(AMNULL == AMStrstr(szContent, "\\T"))
	{
		iMsgLen = AMStrlen(szContent) + sizeof(IM_MSG_HEAD) ;	
		pMsg->szContent = (AMChar*)AMMalloc(iMsgLen+1);		
		AMAssert(0 != pMsg->szContent);
		AMMemset(pMsg->szContent, 0, iMsgLen+1);
		strcpy(pMsg->szContent, IM_MSG_HEAD);
		strcat(pMsg->szContent, szContent);
	}
	else
	{
		iMsgLen = AMStrlen(szContent);	
		pMsg->szContent = (AMChar*)AMMalloc(iMsgLen+1);		
		AMAssert(0 != pMsg->szContent);
		AMMemset(pMsg->szContent, 0, iMsgLen+1);
		AMStrcpy(pMsg->szContent, szContent);
	}	

	if(!bTmp)//不是反向黑名勿
	{
		pTmpCnt = IAContact_Create();
		IAContact_SetCntID(pTmpCnt, szCntID, AMStrlen(szCntID));
		IAContact_AutoSetBindUid(pSesModel->pReference, pTmpCnt);
		IMnetPutBindInfo(pSesModel->pReference->pNetModel, pTmpCnt->szBindUID, pTmpCnt->szBindUID ? AMStrlen(pTmpCnt->szBindUID): 0);
		DPRINT("IASessionModel_SendMsg...........bindID: %s", pTmpCnt->szBindUID ? pTmpCnt->szBindUID : "null");
		IAContact_Destroy(pTmpCnt);

		if(appendMobileImMsg)
		{
			int length = iMsgLen + s_mobileImMessageLength + 1;
			AMChar* content = (AMChar*)AMMalloc(length + 1);	
			AMAssert(AMNULL != content);
			AMMemset(content, 0, length + 1);
			AMStrcpy(content, pMsg->szContent);
			strcat(content, "\n");
			strcat(content, s_mobileImMessage);

			IMnetSendMessage(pSesModel->pReference->pNetModel, (AMChar*)szCntID, content, length, 1);

			AMFree(content);
			content = AMNULL;
		}
		else
		{
			IMnetSendMessage(pSesModel->pReference->pNetModel, (AMChar*)szCntID, (AMChar*)pMsg->szContent, iMsgLen, 1);
		}
	}
	
	IASessionModel_StoreMsg(pSesModel, pMsg, AMTRUE);
	
	IAIMessage_Destroy(pMsg);

	DPRINT("IASessionModel_SendMsg...........Last IAContactModel_UpdateRecent");
	IAContactModel_UpdateRecent(pSesModel->pReference->pCntModel, szCntID, 0, 0, AMFALSE);

	return eAIM_RESULT_OK;
}

IMnetRetCode IASessionModel_OnPeerVerifyConfig(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventGetUserVerifyConfig *pEvnt = (ImEventGetUserVerifyConfig*)pEventContent;
	
	AIM_RSP_GET_VERIFY rspGetVerify;
	AMMemset(&rspGetVerify, 0, sizeof(rspGetVerify));

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);
	
	rspGetVerify.iRetCode = pEvnt->retCode;
	rspGetVerify.szContactId = pEvnt->contactId;
	rspGetVerify.szLongId = pEvnt->retLongId;
	rspGetVerify.szShowName = pEvnt->retShowName;
	
	AIMSessionModel_Callback(pIM->pSesModel, OnRspGetVerify, &rspGetVerify);

	return eAIM_RESULT_OK;
}

IMnetRetCode IASessionModel_OnGetUserUDBProfile(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventGetUserUDBProfile *pEvnt = (ImEventGetUserUDBProfile*)pEventContent;
	IAIMessage	*pMsg = 0;	
	StrStrPair	*pTmpItem = AMNULL, *pItemFind = AMNULL;
	OHTableIter	*pIter = AMNULL;
	StrStrPair	*pPair = AMNULL;
	AMInt32	iPos = 0, i = 0, j = 0, iContentLen = 0;

	AIM_RSP_GET_PROFILE rspGetProfile;

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);
	AMMemset(&rspGetProfile, 0, sizeof(rspGetProfile));

	DPRINT("IASessionModel_OnGetUserUDBProfile................Entering!\n");
	
	rspGetProfile.iRetCode= pEvnt->retCode;
	rspGetProfile.iTotalLen = pEvnt->iTotalLength;
	rspGetProfile.szContactId = pEvnt->contactId;
	if(!pEvnt->retCode)
	{
		AMAssert(pEvnt->pOhtData);
		if(pEvnt->pOhtData && pEvnt->pOhtData->num_elem > 0)
		{	
			rspGetProfile.pszKeys = (AMChar**)AMMalloc(sizeof(AMChar*)*pEvnt->pOhtData->num_elem);
			rspGetProfile.pszValues = (AMChar**)AMMalloc(sizeof(AMChar*)*pEvnt->pOhtData->num_elem);

			AMAssert(rspGetProfile.pszKeys && rspGetProfile.pszValues);

			AMMemset(rspGetProfile.pszKeys, 0, sizeof(AMChar*)*pEvnt->pOhtData->num_elem);
			AMMemset(rspGetProfile.pszValues, 0, sizeof(AMChar*)*pEvnt->pOhtData->num_elem);

			pIter = create(OHTableIter, pEvnt->pOhtData);
			head(OHTableIter, pIter);
			do 
			{
				pPair = (StrStrPair*)retrieve(OHTableIter, pIter);
				if(AMNULL != pPair->szValue)
				{
					rspGetProfile.pszKeys[rspGetProfile.iCount] = pPair->szKey;
					rspGetProfile.pszValues[rspGetProfile.iCount++] = pPair->szValue;
				}
			} while (!next(OHTableIter, pIter));
			destroy(OHTableIter, pIter);
		}		
	}

	AIMSessionModel_Callback(pIM->pSesModel, OnRspGetProfile, &rspGetProfile);

	if(rspGetProfile.pszValues)
		AMFree(rspGetProfile.pszValues);
	if(rspGetProfile.pszKeys)
		AMFree(rspGetProfile.pszKeys);
	
	DPRINT("IASessionModel_OnPeerVerifyConfig..............OK!\n");	

	return eIMnetOK;
}

IMnetRetCode IASessionModel_OnSearchUser(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	DPRINT("IASessionModel_OnSearchUser start"); 

	IAIM *pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	ImEventSearchUser *pEvnt = (ImEventSearchUser*)pEventContent;
	IAIMessage	*pMsg = 0;	
	
	AIM_RSP_SEARCH_USER rspGetProfile;

	AMAssert(AMNULL != pIM && AMNULL != pIM->pAcnt);
	AMMemset(&rspGetProfile, 0, sizeof(rspGetProfile));

	rspGetProfile.iRetCode = pEvnt->retCode;
	//rspGetProfile.iUserCount = pEvnt->userCount;

	DPRINT("pEvnt->retCode = %d", pEvnt->retCode);
	DPRINT("pEvnt->userCount = %d", pEvnt->userCount);
	DPRINT("pEvnt->propertyNum = %d", pEvnt->propertyNum);
	DPRINT("pEvnt->timestamp = %d", pEvnt->timestamp);

	if(!pEvnt->retCode && pEvnt->userList)
	{
		rspGetProfile.pszContactIds = (AMChar**)AMMalloc(sizeof(AMChar *) * pEvnt->userCount);
		rspGetProfile.pszNickNames = (AMChar**)AMMalloc(sizeof(AMChar *) * pEvnt->userCount);
		rspGetProfile.pszCitys = (AMChar**)AMMalloc(sizeof(AMChar *) * pEvnt->userCount);
		
		rspGetProfile.pAges = (AMUInt8*)AMMalloc(sizeof(AMUInt8) * pEvnt->userCount);
		rspGetProfile.pGenders = (AMUInt8*)AMMalloc(sizeof(AMUInt8) * pEvnt->userCount);
		rspGetProfile.pBasicStatus = (AMUInt8*)AMMalloc(sizeof(AMUInt8) * pEvnt->userCount);

		AMAssert(rspGetProfile.pszContactIds && rspGetProfile.pszNickNames && rspGetProfile.pszCitys);
		AMAssert(rspGetProfile.pAges && rspGetProfile.pGenders && rspGetProfile.pBasicStatus);
		
		AMMemset(rspGetProfile.pszContactIds, 0, sizeof(AMChar *) * pEvnt->userCount);
		AMMemset(rspGetProfile.pszNickNames, 0, sizeof(AMChar *) * pEvnt->userCount);
		AMMemset(rspGetProfile.pszCitys, 0, sizeof(AMChar *) * pEvnt->userCount);

		AMMemset(rspGetProfile.pAges, 0, sizeof(AMUInt8) * pEvnt->userCount);
		AMMemset(rspGetProfile.pGenders, 0, sizeof(AMUInt8) * pEvnt->userCount);
		AMMemset(rspGetProfile.pBasicStatus, 0, sizeof(AMUInt8) * pEvnt->userCount);

		while(pEvnt->userList){
			DPRINT("pEvnt->userList->num = %d", pEvnt->userList->num);
			DPRINT("pEvnt->userList->userInfo.contactID = %s", pEvnt->userList->userInfo.contactID);
			DPRINT("pEvnt->userList->userInfo.nickName = %s", pEvnt->userList->userInfo.nickName);
			DPRINT("pEvnt->userList->userInfo.city = %s", pEvnt->userList->userInfo.city);

			DPRINT("pEvnt->userList->userInfo.age = %d", pEvnt->userList->userInfo.age);
			DPRINT("pEvnt->userList->userInfo.gender = %d", pEvnt->userList->userInfo.gender);
			DPRINT("pEvnt->userList->userInfo.basicStatus = %d", pEvnt->userList->userInfo.basicStatus);

			
			rspGetProfile.pszContactIds[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.contactID;
			rspGetProfile.pszNickNames[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.nickName;
			rspGetProfile.pszCitys[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.city;

			rspGetProfile.pAges[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.age;
			rspGetProfile.pGenders[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.gender;
			rspGetProfile.pBasicStatus[rspGetProfile.iUserCount] = pEvnt->userList->userInfo.basicStatus;

			rspGetProfile.iUserCount++;
			pEvnt->userList = pEvnt->userList->pNext;
		}

	}

	AIMSessionModel_Callback(pIM->pSesModel, OnRspSearchUser, &rspGetProfile);

	if(rspGetProfile.pszContactIds)
	{
		AMFree(rspGetProfile.pszContactIds);
	}

	if(rspGetProfile.pszNickNames)
	{
		AMFree(rspGetProfile.pszNickNames);
	}

	if(rspGetProfile.pszCitys)
	{
		AMFree(rspGetProfile.pszCitys);
	}

	if(rspGetProfile.pAges)
	{
		AMFree(rspGetProfile.pAges);
	}

	if(rspGetProfile.pGenders)
	{
		AMFree(rspGetProfile.pGenders);
	}

	if(rspGetProfile.pBasicStatus)
	{
		AMFree(rspGetProfile.pBasicStatus);
	}

	DPRINT("IASessionModel_OnSearchUser..............OK!\n");	
	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnGetCntMemo(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetContactMemo	*pGetMemo = (ImEventGetContactMemo*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);

	AIM_RSP_GET_MEMO rspGetMemo;

	AMAssert(AMNULL != pIM && AMNULL != pGetMemo);
	AMMemset(&rspGetMemo, 0, sizeof(rspGetMemo));

	DPRINT("IASessionModel_OnGetCntMemo.........................Entering!\n");

	rspGetMemo.iRetCode = pGetMemo->retCode;
	rspGetMemo.szContactId = _StrDupLen(pGetMemo->contactID, pGetMemo->contactIDLen);
	rspGetMemo.szMemo = _StrDupLen(pGetMemo->memo, pGetMemo->memoLen);

	AIMSessionModel_Callback(pIM->pSesModel, OnRspGetMemo, &rspGetMemo);

	AMFree(rspGetMemo.szContactId);
	AMFree(rspGetMemo.szMemo);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnGetDegree(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventGetDegree	*pGetDegree = (ImEventGetDegree*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);
	AIM_RSP_GET_DEGREE rspGetDegree;

	AMAssert(AMNULL != pIM && AMNULL != pGetDegree);
	AMMemset(&rspGetDegree, 0, sizeof(rspGetDegree));

	DPRINT("IASessionModel_OnGetCntMemo.........................Entering!\n");

	rspGetDegree.iRetCode = pGetDegree->retCode;
	rspGetDegree.szContactId = _StrDupLen(pGetDegree->contactId, pGetDegree->contactIdLen);
	rspGetDegree.iNeedDegree = pGetDegree->needDegree;
	rspGetDegree.iTotalDegree = pGetDegree->totalDegree;
	rspGetDegree.iUserLevel = pGetDegree->userLevel;

	AIMSessionModel_Callback(pIM->pSesModel, OnRspGetDegree, &rspGetDegree);

	AMFree(rspGetDegree.szContactId);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnHelpLogin(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventHelpLogin *pHelpLogin = (ImEventHelpLogin*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);

	AIM_NTF_HELP_LOGIN ntfHelpLogin;

	AMMemset(&ntfHelpLogin, 0, sizeof(ntfHelpLogin));

	ntfHelpLogin.iRetCode = pHelpLogin->retCode;
	if(!pHelpLogin->retCode)
	{
		ntfHelpLogin.szParentId = AMMalloc(pHelpLogin->parentIdLen + 1);
		AMMemcpy(ntfHelpLogin.szParentId, pHelpLogin->parentId, pHelpLogin->parentIdLen);
		ntfHelpLogin.szParentId[pHelpLogin->parentIdLen] = 0;
		ntfHelpLogin.uiMulStatus = pHelpLogin->mulStatus;
	}
	
	AIMSessionModel_Callback(pIM->pSesModel, OnNtfHelpLogin, &ntfHelpLogin);

	if(ntfHelpLogin.szParentId)
		AMFree(ntfHelpLogin.szParentId);

	return eIMnetOK;
}

IMnetRetCode	IASessionModel_OnHelpChgSrvMode(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventHelpChgSrvMode *pChgMode = (ImEventHelpChgSrvMode*)pEventContent;
	IAIM	*pIM = (IAIM*)IMnetGetReference(hIMnetHandle);

	AIM_RSP_CHG_SRV_MODE rspChgSrvMode;

	rspChgSrvMode.iRetCode = pChgMode->retCode;

	AIMSessionModel_Callback(pIM->pSesModel, OnRspChgSrvMode, &rspChgSrvMode);

	return eIMnetOK;
}

//add by pw; 2011-7-12 for video chat
IMnetRetCode	IASessionModel_OnU2UMessage(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventU2UMessage *pEvent = (ImEventU2UMessage*)pEventContent;
	IAIMessage	*pIMsg = 0;
	IAIM		*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IASessionModel *pSesModel = pIM->pSesModel;
	IASession	*pSysSes = 0;
	AIM_NTF_MSG ntfMsg;

	pIMsg = IAIMessage_Create();
	pIMsg->bUnread = AMTRUE;
	//pIMsg->iServerTime = pEvent->msg.sendTime;
	IAIMessage_SetCntID(pIMsg, pEvent->fromId, pEvent->fromIdLen);
	IAIMessage_SetContent(pIMsg, pEvent->msg, pEvent->msgLen);
	pIMsg->eType = (AIM_MSG_TYPE)U2U_Message;
	pIMsg->u2uType = pEvent->cmd;

	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pSesModel, pIMsg->szContactID, (AMPVoid*)&pSysSes))
	{
		DPRINT("IASessionModel_OnU2UMessage..................Error!\n");
		AMAssert(0);
	}

	ntfMsg.hSession = pSysSes;
	ntfMsg.hMessage = pIMsg;

	AIMSessionModel_Callback(pSesModel, OnNtfMesage, &ntfMsg);

	IAIMessage_Destroy(pIMsg);

	return eIMnetSkip;
}

IMnetRetCode	IASessionModel_OnDeleteOfflineMsg(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	ImEventToDeleteOfflineMsg *pEvent = (ImEventToDeleteOfflineMsg*)pEventContent;
	IAIM		*pIM = (IAIM *)IMnetGetReference(hIMnetHandle);
	IAContact	*pCnt = 0;
	IAContactModel	*pCntModel = 0;

	pCnt = IAContact_Create();
	IAContact_SetCntID(pCnt, pEvent->fromID, pEvent->fromIDLen);
	IAContact_AutoSetBindUid(pIM, pCnt);

	IMnetPutBindInfo(pIM->pNetModel, pCnt->szBindUID, pCnt->szBindUID ? AMStrlen(pCnt->szBindUID) : 0);

	IMnetDeleteOfflineMsg(hIMnetHandle, pEvent->sendtime);

	return eIMnetSkip;
}




AMVoid				IASessionModel_ListenIMnet(IASessionModel *pSesModel, IMnetHandle pNetModel)
{
	AMAssert(0 != pSesModel && 0 != pNetModel);
	IMnetMainRegister(pNetModel, IM_EVENT_CHAT_MESSAGE, IASessionModel_OnChatMsg);//还要做通知
	IMnetMainRegister(pNetModel, IM_EVENT_AUTO_REPLY, IASessionModel_OnAutoReply);//还要做通知
	IMnetMainRegister(pNetModel, IM_EVENT_U2U_Message, IASessionModel_OnU2UMessage);//二级协议
	IMnetMainRegister(pNetModel, IM_EVENT_DELETE_OFFLINE_MESSAGE, IASessionModel_OnDeleteOfflineMsg);//删除离线消息

	IMnetMainRegister(pNetModel, IM_EVENT_SUBCRIBE_MSG, IASessionModel_OnSubMsg);//仅通知?
	IMnetMainRegister(pNetModel, IM_EVENT_SYSTEMMESSAGE, IASessionModel_OnSysMsg);//仅通知?

	IMnetMainRegister(pNetModel, IM_EVENT_CONTACT_ADDED, IASessionModel_OnAddedByContact);//通知,不做其他?

	IMnetMainRegister(pNetModel, IM_EVENT_CONTACT_ASKADD_NO, IASessionModel_OnAskAddNo);//通知，不做其他？
	IMnetMainRegister(pNetModel, IM_EVENT_CONTACT_ASKADD_YES, IASessionModel_OnAskAddYes);//需要更新好友列表么?

	IMnetMainRegister(pNetModel, IM_EVENT_CONTACT_ADD_CNT_VERIFY, IASessionModel_OnAddCntVerify);
	IMnetMainRegister(pNetModel, IM_EVENT_CHGUSERVERIFY, IASessionModel_OnChangeUserVerify);	
	IMnetMainRegister(pNetModel, IM_EVENT_CHGSIGNATURE, IASessionModel_OnChgSignature);
	IMnetMainRegister(pNetModel, IM_EVENT_GETPEERVERIFYCONFIG, IASessionModel_OnPeerVerifyConfig);

	IMnetMainRegister(pNetModel, IM_EVENT_GETUSERUDBPROFILE, IASessionModel_OnGetUserUDBProfile);
	IMnetMainRegister(pNetModel, IM_EVENT_SEARCHUSER, IASessionModel_OnSearchUser);
	IMnetMainRegister(pNetModel, IM_EVENT_GETDEGREE, IASessionModel_OnGetDegree);
	IMnetMainRegister(pNetModel, IM_EVENT_GETCNTMEMO, IASessionModel_OnGetCntMemo);
	IMnetMainRegister(pNetModel, IM_EVENT_HELP_LOGIN, IASessionModel_OnHelpLogin);
	IMnetMainRegister(pNetModel, IM_EVENT_HELP_CHG_SRV_MODE, IASessionModel_OnHelpChgSrvMode);
	IMnetMainRegister(pNetModel, IM_NTF_OPERATIONTIP, IASessionModel_OnOperationTip);
}


AMVoid				IASessionModel_UnlistenIMnet(IASessionModel *pSesModel, IMnetHandle pNetModel)
{
	AMAssert(0 != pSesModel && 0 != pNetModel);
	IMnetMainUnregister(pNetModel, IM_EVENT_CHAT_MESSAGE, IASessionModel_OnChatMsg);//还要做通知
	IMnetMainUnregister(pNetModel, IM_EVENT_AUTO_REPLY, IASessionModel_OnAutoReply);//还要做通知
	IMnetMainUnregister(pNetModel, IM_EVENT_U2U_Message, IASessionModel_OnU2UMessage);//二级协议
	IMnetMainUnregister(pNetModel, IM_EVENT_DELETE_OFFLINE_MESSAGE, IASessionModel_OnDeleteOfflineMsg);//删除离线消息

	IMnetMainUnregister(pNetModel, IM_EVENT_SUBCRIBE_MSG, IASessionModel_OnSubMsg);//仅通知?
	IMnetMainUnregister(pNetModel, IM_EVENT_SYSTEMMESSAGE, IASessionModel_OnSysMsg);//仅通知?

	IMnetMainUnregister(pNetModel, IM_EVENT_CONTACT_ADDED, IASessionModel_OnAddedByContact);//通知,不做其他?

	IMnetMainUnregister(pNetModel, IM_EVENT_CONTACT_ASKADD_NO, IASessionModel_OnAskAddNo);//通知，不做其他？
	IMnetMainUnregister(pNetModel, IM_EVENT_CONTACT_ASKADD_YES, IASessionModel_OnAskAddYes);//需要更新好友列表么?

	IMnetMainUnregister(pNetModel, IM_EVENT_CONTACT_ADD_CNT_VERIFY, IASessionModel_OnAddCntVerify);
	IMnetMainUnregister(pNetModel, IM_EVENT_CHGUSERVERIFY, IASessionModel_OnChangeUserVerify);
	IMnetMainUnregister(pNetModel, IM_EVENT_CHGSIGNATURE, IASessionModel_OnChgSignature);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETPEERVERIFYCONFIG, IASessionModel_OnPeerVerifyConfig);

	IMnetMainUnregister(pNetModel, IM_EVENT_GETUSERUDBPROFILE, IASessionModel_OnGetUserUDBProfile);
	IMnetMainUnregister(pNetModel, IM_EVENT_SEARCHUSER, IASessionModel_OnSearchUser);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETDEGREE, IASessionModel_OnGetDegree);
	IMnetMainUnregister(pNetModel, IM_EVENT_GETCNTMEMO, IASessionModel_OnGetCntMemo);
	IMnetMainUnregister(pNetModel, IM_EVENT_HELP_LOGIN, IASessionModel_OnHelpLogin);
	IMnetMainUnregister(pNetModel, IM_EVENT_HELP_CHG_SRV_MODE, IASessionModel_OnHelpChgSrvMode);
	IMnetMainUnregister(pNetModel, IM_NTF_OPERATIONTIP, IASessionModel_OnOperationTip);
}
