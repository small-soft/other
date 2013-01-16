#include "AIMessage.h"

#include "IAIM.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"

AIM_RESULT IAIMessage_GetID( const AMHandle hMessage, AMInt64 *pID )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(0 != pMsg && AMNULL != pID);

	*pID = pMsg->_iRid;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMessage_GetContactID( const AMHandle hMessage, const AMChar **pszContactID )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(AMNULL != pMsg && AMNULL != pszContactID);

	*pszContactID = pMsg->szContactID;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMessage_GetType( const AMHandle hMessage, AIM_MSG_TYPE *peType )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(0 != pMsg && AMNULL != peType);

	*peType = pMsg->eType;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMessage_GetContent( const AMHandle hMessage, const AMChar **pszContent )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(AMNULL != pMsg && AMNULL != pszContent);

	*pszContent = pMsg->szContent;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMessage_GetTime( const AMHandle hMessage, AMInt32 *pTime )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(0 != pMsg && AMNULL != pTime);

	*pTime = pMsg->iServerTime;

	return eAIM_RESULT_OK;
}


AIM_RESULT IAIMessage_IsRead( const AMHandle hMessage, AMBool *pbRead )
{
	const IAIMessage *pMsg = (const IAIMessage*)hMessage;
	AMAssert(0 != pMsg && AMNULL != pbRead);

	if(AMTRUE == pMsg->bUnread)
		*pbRead = AMFALSE;
	else
		*pbRead = AMTRUE;

	return eAIM_RESULT_OK;
}

IAIMessage*	IAIMessage_Create()
{
	IAIMessage	*pRet = 0;
	pRet = (IAIMessage*)AMMalloc(sizeof(IAIMessage));
	AMAssert(0 != pRet);
	AMMemset(pRet, 0, sizeof(IAIMessage));
	return pRet;
}

IAIMessage*	IAIMessage_Dup(const IAIMessage *pMsg)
{
	IAIMessage *pRet = 0;
	AMAssert(0 != pMsg);
	pRet = IAIMessage_Create();
	if(pMsg->szContactID)
	{
		IAIMessage_SetCntID(pRet, pMsg->szContactID, AMStrlen(pMsg->szContactID));
	}
	if(pMsg->szContent)
	{
		IAIMessage_SetContent(pRet, pMsg->szContent, AMStrlen(pMsg->szContent));
	}
	pRet->_iRid = pMsg->_iRid;
	pRet->iServerTime = pMsg->iServerTime;
	pRet->eType = pMsg->eType;
	return pRet;
}

AMVoid		IAIMessage_Destroy(IAIMessage *pMsg)
{
	AMAssert(0 != pMsg);
	if(pMsg->szContactID)
	{
		AMFree(pMsg->szContactID);
		pMsg->szContactID = 0;
	}
	if(pMsg->szContent)
	{
		AMFree(pMsg->szContent);
		pMsg->szContent = 0;
	}
	AMFree(pMsg);
}


AMVoid		IAIMessage_SetCntID(IAIMessage *pMsg, const AMChar * szCntID, AMUInt32	uiIDLen)
{
	AMAssert(0 != pMsg && 0 != szCntID);
	if(pMsg->szContactID)
	{
		AMFree(pMsg->szContactID);
		pMsg->szContactID = 0;
	}

	pMsg->szContactID = (AMChar *)AMMalloc(uiIDLen + 1);
	AMAssert(0 != pMsg->szContactID);
	AMMemcpy(pMsg->szContactID, szCntID, uiIDLen);
	pMsg->szContactID[uiIDLen] = 0;
}

AMVoid		IAIMessage_SetContent(IAIMessage *pMsg, const AMChar *szContent, AMUInt32 iLen)
{
	AMAssert(0 != pMsg);
	if(pMsg->szContent)
	{
		AMFree(pMsg->szContent);
		pMsg->szContent = 0;
	}

	pMsg->szContent = (AMChar *)AMMalloc(iLen + 1);
	AMAssert(0 != pMsg->szContent);
	AMMemcpy(pMsg->szContent, szContent, iLen);
	pMsg->szContent[iLen] = 0;
}

AMVoid		IAIMessage_SetDateTime(IAIMessage *pMsg, AMInt32 iTime)
{
	AMAssert(AMNULL != pMsg);
	pMsg->iServerTime = iTime;
}

AMInt32		IAIMessage_CmpId(const AMVoid *p1, const AMVoid *p2, AMUInt32 uiSize)
{
	IAIMessage *pMsgA = (IAIMessage*)p1,
				*pMsgB = (IAIMessage*)p2;
	AMAssert(0 != p1 && 0 != p2);
	if(pMsgA->_iRid < pMsgB->_iRid)
		return -1;
	else if(pMsgA->_iRid > pMsgA->_iRid)
		return 1;
	else
		return 0;
}

AMBool IAIMessage_NeedSave(IAIMessage *pMsg)
{
	AMAssert(AMNULL != pMsg);
	if(pMsg->eType < eMSG_TYPE_CHAT_SEND
		|| eMSG_TYPE_CONTACT_ADD_FAIL == pMsg->eType
		|| eMSG_TYPE_OPERATION == pMsg->eType
		|| eMSG_TYPE_FILE == pMsg->eType
		/*|| eMSG_TYPE_CONTACT_ADDED_BY == pMsg->eType*/)
		return AMFALSE;
	return AMTRUE;
}

