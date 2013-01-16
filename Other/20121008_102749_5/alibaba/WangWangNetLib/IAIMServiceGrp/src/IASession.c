#include "AIMSession.h"
#include "AIMessage.h"
#include "AIMSessionModel.h"

#include "AIM.h"
#include "AIMUtil.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMStdlib.h"

#include "sqlite3.h"

IASession *	IASession_Create(const AMChar *szContactID, IASessionModel *pSesModel)
{
	IASession *pRet = 0;
	AMUInt32	ui = 0, uiLen = 0;
	AMAssert(0 != szContactID);
	pRet = (IASession*)AMMalloc(sizeof(IASession));
	AMMemset(pRet, 0, sizeof(IASession));
	uiLen = AMStrlen(szContactID);
	AMAssert(8 < uiLen);
	pRet->szContactID = (AMChar *)AMMalloc(uiLen + 1);
	for(ui = 0; ui < uiLen; ui++)
		pRet->szContactID[ui] = szContactID[ui];
	pRet->szContactID[uiLen] = 0;

	pRet->pSesModel = pSesModel;

	return pRet;
}

AMVoid		IASession_Destroy(IASession *pSes)
{
	AMAssert(0 != pSes);

	if(pSes->szContactID)
	{
		AMFree(pSes->szContactID);
		pSes->szContactID = 0;
	}

	pSes->pSesModel = 0;

	AMFree(pSes);
}

AIM_RESULT IAIMSession_GetContactID( const AMHandle hSession, const AMChar **pszID )
{
	const IASession *pSession = (const IASession *)hSession;
	AMAssert(AMNULL != pSession && AMNULL != pszID);

	*pszID = pSession->szContactID;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMSession_GetPeer( AMHandle hSession, AMHandle *phContact)
{
	const IASession *pSession = (const IASession *)hSession;
	AMAssert(AMNULL != pSession && AMNULL != phContact);

	*phContact = pSession->hPeer;

	return eAIM_RESULT_OK;
}

static AMInt32 IASession_OnSelUnreadCnt(void* pvRet, int iCnt, char **pszValue, char**pszName)
{
	AMInt32 *piRet = (AMInt32*)pvRet;
	*piRet = AMAtoi(pszValue[0]);
	return 0;
}

#define		SQL_SELECT_UNREAD_CNT_MSG_COUNT	"SELECT COUNT(*) FROM _msg WHERE _unread=1 AND _peerid='%q' AND _type<259 ORDER BY _time;"
#define		SQL_SELECT_UNREAD_SYS_MSG_COUNT	"SELECT COUNT(*) FROM _msg WHERE _unread=1 AND _type>258 ORDER BY _time;"
#define		SQL_SELECT_UNREAD_COUNT_ID	"SELECT COUNT(*) FROM _msg WHERE _rid=%lld AND _unread=1;"
AIM_RESULT AIMSession_CountUnreadMsgs( AMHandle hSession, AMInt64 iID, AMInt32 *pCount )
{
	const IASession *pSession = (const IASession *)hSession;
	AMInt32		iRet = 0;
	AMInt32	rcSqlite = 0;
	AMChar	*szSql = AMNULL;
	AMChar *szErrMsg = AMNULL;

	AMAssert(AMNULL != pSession && AMNULL != pCount);
	AMAssert(AMNULL != pSession->pSesModel);
	AMAssert(AMNULL != pSession->pSesModel->pDB);

	if(0 == iID)
	{
		if(0 == AMStrcmp(pSession->szContactID, SYS_SES_NAME))//系统消息
		{
			szSql = sqlite3_mprintf(SQL_SELECT_UNREAD_SYS_MSG_COUNT);
		}
		else//普通聊天消息
		{
			szSql = sqlite3_mprintf(SQL_SELECT_UNREAD_CNT_MSG_COUNT, pSession->szContactID);
		}
	}
	else
	{
		szSql = sqlite3_mprintf(SQL_SELECT_UNREAD_COUNT_ID, iID);
	}

	if(szSql)
	{
		rcSqlite = sqlite3_exec(pSession->pSesModel->pDB, szSql, IASession_OnSelUnreadCnt, &iRet, &szErrMsg);

		sqlite3_free(szSql);

		if(SQLITE_OK != rcSqlite)
		{
			DPRINT("IASession_GetUnreadCnt.............can not %s for %s\n", szSql, szErrMsg);
			sqlite3_free(szErrMsg);
			return eAIM_RESULT_DB_ERROR;
		}

		*pCount = iRet;

		return eAIM_RESULT_OK;
	}
	else
	{
		return eAIM_RESULT_MALLOC_ERROR;
	}	
}

AIM_RESULT IAIMSession_CountUnreadMsgs(AMHandle hSession, AMInt32 *pCount)
{
	return AIMSession_CountUnreadMsgs(hSession, 0, pCount);
}

static AMInt32 AIMSession_OnSelMsgs(void* pvArg, int iCnt, char **pszValue, char**pszName)
{
	AMPVoid *pvArgs = (AMPVoid *)pvArg;
	AMHandle **pphMsgArray = (AMHandle**)pvArgs[0];
	AMInt32 *piCount = (AMInt32*)pvArgs[1];
	IAIMessage	*pMsg = IAIMessage_Create();

	AMAssert(pphMsgArray && *pphMsgArray && piCount && pMsg);

	pMsg->_iRid = AMAtoi64(pszValue[0]);
	IAIMessage_SetCntID(pMsg, pszValue[1], AMStrlen(pszValue[1]));
	pMsg->eType = AMAtoi(pszValue[2]);
	pMsg->iServerTime = AMAtoi(pszValue[3]);
	IAIMessage_SetContent(pMsg, pszValue[4], AMStrlen(pszValue[4]));
	pMsg->bUnread = AMAtoi(pszValue[5]);
	
	(*pphMsgArray)[(*piCount)++] = pMsg;

	return 0;
}

//#ifdef ANDROID_BUILD
#if defined (ANDROID_BUILD) || defined (IOS_BUILD)

#define		SQL_SELECT_SYS_MSG	"SELECT * FROM _msg WHERE _type>258 ORDER BY _unread, _time LIMIT %d OFFSET %d;"
#define		SQL_SELECT_CNT_MSG	"SELECT * FROM _msg WHERE _peerid='%q' AND _type<259 ORDER BY _time LIMIT %d OFFSET %d;"

#define		SQL_SELECT_MSG_ID	"SELECT * FROM _msg WHERE _rid=%d;"

#define		SQL_SELECT_UNREAD_CNT_MSG	"SELECT * FROM _msg WHERE _unread=1 AND _peerid='%q' AND _type<259 ORDER BY _time LIMIT %d OFFSET %d;"
#define		SQL_SELECT_UNREAD_SYS_MSG	"SELECT * FROM _msg WHERE _unread=1 AND _type>258 ORDER BY _time LIMIT %d OFFSET %d;"

#else

#define		SQL_SELECT_SYS_MSG	"SELECT * FROM _msg WHERE _type>258 ORDER BY _unread DESC, _time DESC, _rid DESC LIMIT %d OFFSET %d;"
#define		SQL_SELECT_CNT_MSG	"SELECT * FROM _msg WHERE _peerid='%q' AND _type<259 ORDER BY _time DESC, _rid DESC LIMIT %d OFFSET %d;"

#define		SQL_SELECT_MSG_ID	"SELECT * FROM _msg WHERE _rid=%d;"

#define		SQL_SELECT_UNREAD_CNT_MSG	"SELECT * FROM _msg WHERE _unread=1 AND _peerid='%q' AND _type<259 ORDER BY _time DESC, _rid DESC LIMIT %d OFFSET %d;"
#define		SQL_SELECT_UNREAD_SYS_MSG	"SELECT * FROM _msg WHERE _unread=1 AND _type>258 ORDER BY _time DESC, _rid DESC LIMIT %d OFFSET %d;"

#endif

//本函数具有所有潜规则！
AIM_RESULT AIMSession_GetMsgs( AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMBool bUnread
							  , AMHandle **pphMsgArray, AMInt32 *piCount)
{
	IASession *pSession = (IASession *)hSession;
	AMInt32	rcSqlite = 0;
	AMChar	*szSql = AMNULL;
	AMChar *szErrMsg = AMNULL;
	AMPVoid	pvArgs[2] = {pphMsgArray, piCount};

	AMAssert(AMNULL != pSession && AMNULL != pSession->pSesModel->pDB);
	AMAssert(AMNULL != pphMsgArray && AMNULL != piCount);

	*piCount = 0;
	*pphMsgArray = AMNULL;//ReleaseMsgs要利用free不释放NULL的特点。

	if(iCount > 0)
	{
		if(bUnread)
		{
			if(0 == AMStrcmp(pSession->szContactID, SYS_SES_NAME))//系统消息
			{
				szSql = sqlite3_mprintf(SQL_SELECT_UNREAD_SYS_MSG, iCount, iOffset);
			}
			else//普通聊天消息
			{
				szSql = sqlite3_mprintf(SQL_SELECT_UNREAD_CNT_MSG, pSession->szContactID, iCount, iOffset);
			}
		}
		else
		{
			if(0 == AMStrcmp(pSession->szContactID, SYS_SES_NAME))//系统消息
			{
				szSql = sqlite3_mprintf(SQL_SELECT_SYS_MSG, iCount, iOffset);
			}
			else//普通聊天消息
			{
				szSql = sqlite3_mprintf(SQL_SELECT_CNT_MSG, pSession->szContactID, iCount, iOffset);
			}
		}
	}
	else
	{
		szSql = sqlite3_mprintf(SQL_SELECT_MSG_ID, iOffset);
	}	

	if(!szSql)
		return eAIM_RESULT_MALLOC_ERROR;

	DPRINT("%s >>>>>> sql: %s\n", __FUNCTION__, szSql);

	//iCount may be zero to select a particular message.
	*pphMsgArray = (AMHandle*)AMMalloc(sizeof(AMHandle) * (iCount + 1));
		
	if(!(*pphMsgArray))
		return eAIM_RESULT_MALLOC_ERROR;

	AMMemset(*pphMsgArray, 0, sizeof(AMHandle) * (iCount + 1));

	rcSqlite = sqlite3_exec(pSession->pSesModel->pDB, szSql, AIMSession_OnSelMsgs, pvArgs, &szErrMsg);

	sqlite3_free(szSql);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASession_GetHistory.............can not %s for %s\n", szSql, szErrMsg);
		sqlite3_free(szErrMsg);
		IAIMSession_ReleaseMsgs(hSession, *pphMsgArray, *piCount);
		return eAIM_RESULT_DB_ERROR;
	}

	if(!(*piCount))
		AMFree(*pphMsgArray);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMSession_GetMsgs(AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **pphMsgArray, AMInt32 *piCount)
{
	if(iCount > 0)
		return AIMSession_GetMsgs(hSession, iOffset, iCount, AMFALSE, pphMsgArray, piCount);
	else
	{
		AMAssert(piCount);
		*piCount = 0;
		return eAIM_RESULT_PARAM_ERROR;
	}
}

//iFlag : 0 release handle Array, and every msg; 1 release handle array only; 2 release every msg only
AIM_RESULT AIMSession_ReleaseMsgs( AMHandle hSession, AMHandle *phHandleArray, AMInt32 iCount, AMInt32 iFlag)
{
	IASession *pSession = (IASession *)hSession;

	AMAssert(AMNULL != pSession && iFlag>-1 && iFlag < 3);

	if(iCount && 1 != iFlag)
	{
		AMInt32	 i=0;
		for(i=0; i<iCount; i++)
			IAIMessage_Destroy((IAIMessage*)phHandleArray[i]);
	}

	if(2 != iFlag)
		AMFree(phHandleArray);//利用free不释放NULL的特点。

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMSession_ReleaseMsgs( AMHandle hSession , AMHandle *phMsgArray, AMInt32 iCount)
{
	return AIMSession_ReleaseMsgs( hSession, phMsgArray, iCount, 0);
}

AIM_RESULT IAIMSession_GetUnreadMsgs( AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **pphMsgArray, AMInt32 *piCount )
{
	return AIMSession_GetMsgs(hSession, iOffset, iCount, AMTRUE, pphMsgArray, piCount);
}

AIM_RESULT IAIMSession_ReleaseUnreadMsgs(AMHandle hSession, AMHandle *phMsgArray, AMInt32 iArraySize)
{
	return AIMSession_ReleaseMsgs( hSession, phMsgArray, iArraySize, 0);
}

static AMInt32 ASession_OnSelMsgCount(void* pvCnt, int iCnt, char **pszValue, char**pszName)
{
	AMInt32	*piCnt = (AMInt32*)pvCnt;
	*piCnt = AMAtoi(pszValue[0]);
	return 0;
}

#define		SQL_SELECT_SYS_MSG_NUM	"SELECT COUNT(*) FROM _msg WHERE _type>258;"
#define		SQL_SELECT_CNT_MSG_NUM	"SELECT COUNT(*) FROM _msg WHERE _peerid='%q' AND _type<259;"
AIM_RESULT IAIMSession_CountMsgs( AMHandle hSession, AMInt32 *pCount )
{
	const IASession *pSession = (const IASession *)hSession;
	AMInt32	rcSqlite = 0;
	AMChar	*szSql = AMNULL;
	AMChar *szErrMsg = AMNULL;
	AMInt32 iRet = 0;

	AMAssert(AMNULL != pSession && AMNULL != pSession->pSesModel->pDB);

	if(0 == AMStrcmp(pSession->szContactID, SYS_SES_NAME))//系统消息
	{
		szSql = sqlite3_mprintf(SQL_SELECT_SYS_MSG_NUM);
	}
	else//普通聊天消息
	{
		szSql = sqlite3_mprintf(SQL_SELECT_CNT_MSG_NUM, pSession->szContactID);
	}

	if(szSql)
	{
		rcSqlite = sqlite3_exec(pSession->pSesModel->pDB, szSql, ASession_OnSelMsgCount, &iRet, &szErrMsg);

		sqlite3_free(szSql);

		if(SQLITE_OK != rcSqlite)
		{
			DPRINT("IASession_GetHistoryCount.............can not %s for %s\n", szSql, szErrMsg);
			sqlite3_free(szErrMsg);
			return eAIM_RESULT_DB_ERROR;
		}

		*pCount = iRet;
		return eAIM_RESULT_OK;
	}
	else
		return eAIM_RESULT_MALLOC_ERROR;	
}

#define		SQL_MARK_READ_CNT_MSG	"UPDATE _msg SET _unread=0 WHERE _unread=1 AND _peerid='%q' AND _type<259;"
#define		SQL_MARK_READ_SYS_MSG	"UPDATE _msg SET _unread=0 WHERE _unread=1 AND _type>258;"
#define		SQL_MARK_READ_MSG_ID	"UPDATE _msg SET _unread=0 WHERE _unread=1 AND _rid=%lld;"
//i64Id=0表示标记该Session的所有未读消息为已读，i6rId>0表示只标记对应_rid的消息为已读
//传进来的Msg的跟hSession是需要一致的，否则后面的IAContactModel_DecreaseReadCnt无法处理...	
AIM_RESULT	IAIMSession_MarkMsgRead(AMHandle hSession, AMInt64 i64MsgId)
{
	IASession *pSes = (IASession *)hSession;
	AMInt32	rcSqlite = 0;
	AMChar	*szSql = AMNULL;
	AMChar	*szErrMsg = AMNULL;
	AMInt32 iUnreadCount = 0;
	AIM_RESULT eResult = 0;

	AMAssert(AMNULL != pSes);

	eResult = AIMSession_CountUnreadMsgs(pSes, i64MsgId, &iUnreadCount);

	if(eAIM_RESULT_OK != eResult)
	{
		return eAIM_RESULT_OK;
	}

	if(iUnreadCount <= 0)
		return eAIM_RESULT_OK;

	if(0 == i64MsgId)
	{
		if(0 == AMStrcmp(pSes->szContactID, SYS_SES_NAME))//系统消息
		{
			szSql = sqlite3_mprintf(SQL_MARK_READ_SYS_MSG);
		}
		else//普通聊天消息
		{
			szSql = sqlite3_mprintf(SQL_MARK_READ_CNT_MSG, pSes->szContactID);
		}
	}
	else
	{
		szSql = sqlite3_mprintf(SQL_MARK_READ_MSG_ID, i64MsgId);
	}

	if(!szSql)
		return eAIM_RESULT_MALLOC_ERROR;

	rcSqlite = sqlite3_exec(pSes->pSesModel->pDB, szSql, 0, 0, &szErrMsg);

	sqlite3_free(szSql);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASession_MarkMsgRead.............can not %s for %s\n", szSql, szErrMsg);
		sqlite3_free(szErrMsg);
		return eAIM_RESULT_DB_ERROR;
	}

	if(0 != AMStrcmp(pSes->szContactID, SYS_SES_NAME))
	{
		IAContactModel_DecreaseReadCnt(pSes->pSesModel->pReference->pCntModel, pSes->szContactID, iUnreadCount);
	}

	return eAIM_RESULT_OK;
}

#define			SQL_DELETE_SYS_MSG	"DELETE FROM _msg WHERE _type>258;"
#define			SQL_DELETE_CNT_MSG	"DELETE FROM _msg WHERE _peerid='%q' AND _type<259;"
#define			SQL_DELETE_MSG_ID	"DELETE FROM _msg WHERE _rid=%lld"
//因为需要先MarkRead，所以i64MsgId也需要跟hSession一致
AIM_RESULT		AIMSession_RemoveMsg(AMHandle hSession, AMInt64 i64MsgId, AMBool bHasUnread)
{
	IASession *pSes = (IASession *)hSession;
	AMInt32	rcSqlite = 0;
	AMChar	*szSql = AMNULL;
	AMChar *szErrMsg = AMNULL;

	AMAssert(AMNULL != pSes && AMNULL != pSes->pSesModel->pDB);

	DPRINT("AIMSession_RemoveMsg\t\t\t Entering "I64FORMAT"\n", i64MsgId);
	
	if(bHasUnread)
		IAIMSession_MarkMsgRead(hSession, i64MsgId);

	if(i64MsgId<=0)
	{
		if(0 == AMStrcmp(pSes->szContactID, "systemSes"))//系统消息
		{
			szSql = sqlite3_mprintf(SQL_DELETE_SYS_MSG);
		}
		else//普通聊天消息
		{
			szSql = sqlite3_mprintf(SQL_DELETE_CNT_MSG, pSes->szContactID);
		}
	}
	else
	{
		szSql = sqlite3_mprintf(SQL_DELETE_MSG_ID, i64MsgId);
	}

	DPRINT("AIMSession_RemoveMsg\t\t\t SQL: %s\n", szSql);

	if(!szSql)
		return eAIM_RESULT_MALLOC_ERROR;

	rcSqlite = sqlite3_exec(pSes->pSesModel->pDB, szSql, 0, 0, &szErrMsg);

	sqlite3_free(szSql);

	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IASession_RemoveMsg.............can not %s for %s\n", szSql, szErrMsg);
		sqlite3_free(szErrMsg);
		return eAIM_RESULT_DB_ERROR;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMSession_RemoveMsg(AMHandle hSession, AMInt64 i64MsgId)
{
	DPRINT("IAIMSession_RemoveMsg\t\t\t Entering "I64FORMAT"\n", i64MsgId);
	return AIMSession_RemoveMsg(hSession, i64MsgId, AMTRUE);
}

AMUInt32	IASession_Hash(const AMVoid *p1, size_t t)
{
	AMUInt32 uiRet = 0;
	AMChar *str = ((IASession *)p1)->szContactID;
	AMAssert(0 != str);
	while(*str != 0)
		uiRet = (uiRet << 5) + (*str++);

	return uiRet;
}

AMInt32		IASession_Cmp(const AMVoid *p1, const AMVoid *p2, size_t t)
{
	IASession *pA = (IASession*)p1,
		*pB = (IASession*)p2;
	AMAssert(0 != pA && 0 != pB);
	AMAssert(0 != pA->szContactID && 0 != pB->szContactID);
	return AMStrcmp(pA->szContactID, pB->szContactID);
}