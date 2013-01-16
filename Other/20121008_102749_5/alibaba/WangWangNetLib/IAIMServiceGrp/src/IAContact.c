#include "IAIM.h"	//for AIM_RESULT and AIM_PRESENCE
#include "IAIMGroup.h"	// for ***_GRP_ID
#include "AIMContact.h"
#include "AIMGroup.h"
#include "AIMContactModel.h"
#include "AIM.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"

IAContact	*IAContact_Create()
{
	IAContact * pRet;
	pRet = (IAContact *)AMMalloc(sizeof(IAContact));
	AMAssert(0 != pRet);
	AMMemset(pRet, 0, sizeof(IAContact));

	return pRet;
}

IAContact	*IAContact_Duplicate(const IAContact *pCnt)
{
	IAContact *pRet = IAContact_Create();
	IAContact_SetCntID(pRet, pCnt->szID, AMStrlen(pCnt->szID));
	if(pCnt->szName)
		IAContact_SetNickName(pRet, pCnt->szName, AMStrlen(pCnt->szName));
	if(pCnt->szPinyin)
		IAContact_SetPinyin(pRet, pCnt->szPinyin, AMStrlen(pCnt->szPinyin));
	if(pCnt->szLastMsg)
		IAContact_SetLastMsg(pRet, pCnt->szLastMsg, AMStrlen(pCnt->szLastMsg));
	if(pCnt->szPhone)
		IAContact_SetPhone(pRet, pCnt->szPhone, AMStrlen(pCnt->szPhone));
	if(pCnt->szBindUID)
		IAContact_SetBindUid(pRet, pCnt->szBindUID, AMStrlen(pCnt->szBindUID));
	pRet->iParentGid = pCnt->iParentGid;
	pRet->pParentGrp = pCnt->pParentGrp;
	pRet->uiFlag = pCnt->uiFlag;
	pRet->eType = pCnt->eType;
	pRet->ePresence = pCnt->ePresence;
	return pRet;
}

AMVoid		IAContact_Destroy(IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	if(pCnt->szID)
	{
		AMFree(pCnt->szID);
		pCnt->szID = 0;
	}
	if(pCnt->szName)
	{
		AMFree(pCnt->szName);
		pCnt->szName = 0;
	}
	if(pCnt->szPinyin)
	{
		AMFree(pCnt->szPinyin);
		pCnt->szPinyin = 0;
	}
	if(pCnt->szLastMsg)
	{
		AMFree(pCnt->szLastMsg);
		pCnt->szLastMsg = 0;
	}
	if(pCnt->szSignature)
	{
		AMFree(pCnt->szSignature);
		pCnt->szSignature = AMNULL;
	}
	if(pCnt->szPhone)
	{
		AMFree(pCnt->szPhone);
		pCnt->szPhone = AMNULL;
	}
	if(pCnt->szBindUID)
	{
		AMFree(pCnt->szBindUID);
		pCnt->szBindUID = AMNULL;
	}
	AMFree(pCnt);
}

AIM_RESULT IAIMContact_GetID( const AMHandle hContact, const AMChar **pszID )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pszID);

	*pszID = pCnt->szID;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetType( const AMHandle hContact, AIM_ACCOUNT_TYPE *pType)
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pType);

	*pType = pCnt->eType;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetName(const AMHandle hContact, const AMChar **pszName)
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pszName);

	*pszName = pCnt->szName;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetLastMsg( const AMHandle hContact, const AMChar **pszMsg )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pszMsg);

	*pszMsg = pCnt->szLastMsg;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetSignature(const AMHandle hContact, const AMChar **pszSignature)
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pszSignature);

	*pszSignature = pCnt->szSignature;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetPortrait( AMHandle hContact, const AMChar **pszFilePath)
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pszFilePath);

	*pszFilePath = pCnt->szPortrait;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetPresence( const AMHandle hContact, AIM_PRESENCE *pePresence )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pePresence);

	*pePresence = pCnt->ePresence;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetParentGroup( const AMHandle hContact, AMHandle *phGroup )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != phGroup);

	*phGroup = (AMHandle)pCnt->pParentGrp;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_GetParentGroupID( const AMHandle hContact, AMInt64 *pID )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pID);

	*pID = pCnt->iParentGid;

	return eAIM_RESULT_OK;
}

AMInt32		IAContact_GetFlag(const IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	return pCnt->uiFlag;
}

AIM_RESULT IAIMContact_IsBlack( const AMHandle hContact, AMBool *pbBlack )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pbBlack);

	if((pCnt->uiFlag & 0x01) == 0x01)
	{
		*pbBlack = AMTRUE;
	}
	else
	{
		*pbBlack = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AMBool		IAContact_IsRevBlack(const IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	if((pCnt->uiFlag & 0x02) == 0x02)
		return AMTRUE;

	return AMFALSE;
}

AIM_RESULT IAIMContact_IsStrange( const AMHandle hContact, AMBool *pbStrange )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pbStrange);

	if((pCnt->uiFlag & 0x04) == 0x04)
	{
		AMAssert(STRANG_GRP_ID == pCnt->iParentGid);
		*pbStrange = AMTRUE;
	}
	else
	{
		*pbStrange = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMContact_IsRecent( const AMHandle hContact, AMBool *pbRecent )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pbRecent);

	if((pCnt->uiFlag & 0x08) == 0x08)
	{
		*pbRecent = AMTRUE;
	}
	else
	{
		*pbRecent = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AMBool	AIMContact_isFriend( AMHandle hCntModel, AMHandle hContact )
{
	const IAContactModel *pCntModel = (IAContactModel *)hCntModel;
	const IAContact *pCnt = (IAContact *)hContact;
	AMAssert(pCntModel && pCnt);
	
	if(find_OHTable(&pCntModel->ohtFriends, pCnt, sizeof(IAContact)))
		return AMTRUE;

	return AMFALSE;
}

AMVoid		IAContact_MarkBlack(IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	pCnt->uiFlag |= 0x01;
}

AMVoid		IAContact_MarkRevBlk(IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	pCnt->uiFlag |= 0x02;
}

AMVoid		IAContact_MarkStrang(IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	pCnt->iParentGid = STRANG_GRP_ID;
	pCnt->uiFlag |= 0x04;
}

AMVoid		IAContact_MarkRecent(IAContact *pCnt)
{
	AMAssert(0 != pCnt);
	pCnt->uiFlag |= 0x08;
}

AMVoid		IAContact_SetCntID(IAContact *pCnt, const AMChar *szID, AMUInt32 uiIdLen)
{
	AMAssert(0 != pCnt && 0 != szID && 0 < uiIdLen);
	if(pCnt->szID)
	{
		AMFree(pCnt->szID);
		pCnt->szID = 0;
	}
	pCnt->szID = (AMChar *)AMMalloc(uiIdLen + 1);
	AMAssert(0 != pCnt->szID);
	AMMemcpy(pCnt->szID, szID, uiIdLen);
	pCnt->szID[uiIdLen] = 0;
}

AMVoid		IAContact_SetNickName(IAContact *pCnt, const AMChar *sNick, AMUInt32 uiNickLen)
{
	AMAssert(0 != pCnt);
	if(pCnt->szName)
	{
		AMFree(pCnt->szName);
		pCnt->szName = 0;
	}
	if(0 == sNick)
		return;
	pCnt->szName = (AMChar *)AMMalloc(uiNickLen + 1);
	AMAssert(0 != pCnt->szName);
	AMMemcpy(pCnt->szName, sNick, uiNickLen);
	pCnt->szName[uiNickLen] = 0;
}

AMVoid		IAContact_SetPinyin(IAContact *pCnt, const AMChar *szPinyin, AMUInt32 uiLen)
{
	AMAssert(0 != pCnt);
	if(pCnt->szPinyin)
	{
		AMFree(pCnt->szPinyin);
		pCnt->szPinyin = 0;
	}
	
	if(AMNULL == szPinyin || 0 == uiLen)
		return;

	pCnt->szPinyin = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(AMNULL != pCnt->szPinyin);
	AMMemcpy(pCnt->szPinyin, szPinyin, uiLen);
	pCnt->szPinyin[uiLen] = 0;
}

AMVoid		IAContact_SetPhone(IAContact *pCnt, const AMChar *sPhone, AMUInt32 uiPhoneLen)
{
	AMAssert(0 != pCnt);
	if(pCnt->szPhone)
	{
		AMFree(pCnt->szPhone);
		pCnt->szPhone = 0;
	}

	if(AMNULL == sPhone || 0 == uiPhoneLen)
		return;

	pCnt->szPhone = (AMChar *)AMMalloc(uiPhoneLen + 1);
	AMAssert(AMNULL != pCnt->szPhone);
	AMMemcpy(pCnt->szPhone, sPhone, uiPhoneLen);
	pCnt->szPhone[uiPhoneLen] = 0;
}

AMVoid IAContact_SetBindUid(IAContact *pCnt, const AMChar *sUid, AMUInt32 uiUidLen)
{
	AMAssert(0 != pCnt);
	if(pCnt->szBindUID)
	{
		AMFree(pCnt->szBindUID);
		pCnt->szBindUID = AMNULL;
	}

	if(AMNULL == sUid || 0 == uiUidLen)
		return;

	pCnt->szBindUID = (AMChar *)AMMalloc(uiUidLen + 1);
	AMAssert(AMNULL != pCnt->szBindUID);
	AMMemcpy(pCnt->szBindUID, sUid, uiUidLen);
	pCnt->szBindUID[uiUidLen] = 0;
}


AMVoid		IAContact_SetLastMsg(IAContact *pCnt, const AMChar *szMsg, AMUInt32 uiLen)
{
	AMAssert(0 != pCnt);
	if(pCnt->szLastMsg)
	{
		AMFree(pCnt->szLastMsg);
		pCnt->szLastMsg = 0;
	}
	if(0 == szMsg)
		return ;

	pCnt->szLastMsg = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(AMNULL != pCnt->szLastMsg);
	AMMemcpy(pCnt->szLastMsg, szMsg, uiLen);
	pCnt->szLastMsg[uiLen] = 0;
}

AMInt32		IAContact_SetSignature(IAContact *pCnt, const AMChar *szSignature, AMUInt32 uiLen)
{
	AMAssert(0 != pCnt);

	if(AMNULL == pCnt->szSignature && (AMNULL == szSignature || 0 == uiLen))
		return -1;

	if(AMNULL != pCnt->szSignature && AMNULL != szSignature && 0 == AMStrcmp(pCnt->szSignature, szSignature))
		return -1;

	if(pCnt->szSignature)
	{
		AMFree(pCnt->szSignature);
		pCnt->szSignature = 0;
	}

	pCnt->szSignature = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(AMNULL != pCnt->szSignature);
	AMMemcpy(pCnt->szSignature, szSignature, uiLen);
	pCnt->szSignature[uiLen] = 0;

	return 0;
}


AMInt32		IAContact_SetPortrait(IAContact *pCnt, const AMChar *szPortrait, AMUInt32 uiLen)
{
	AMAssert(0 != pCnt);

	if(AMNULL == pCnt->szPortrait && (AMNULL == szPortrait || 0 == uiLen))
		return -1;

	if(pCnt->szPortrait)
	{
		AMFree(pCnt->szPortrait);
		pCnt->szPortrait = AMNULL;
	}

	pCnt->szPortrait = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(AMNULL != pCnt->szPortrait);
	AMMemcpy(pCnt->szPortrait, szPortrait, uiLen);
	pCnt->szPortrait[uiLen] = 0;

	return 0;
}

AMInt32		IAContact_CmpID(const AMVoid *p1, const AMVoid *p2, size_t t)
{
	IAContact *pA = (IAContact *)p1,
		*pB = (IAContact *)p2;
	AMAssert(0 != p1 && 0 != p2);
	AMAssert(0 != pA->szID && 0 != pB->szID);
	return AMStrcmp(pA->szID, pB->szID);
}

AMInt32		IAContact_CmpPinyin(const AMVoid *p1, const AMVoid *p2, size_t t)
{
	IAContact *pA = (IAContact *)p1,
		*pB = (IAContact *)p2;
	AMAssert(0 != pA && 0 != pB);
	AMAssert(0 != pA->szPinyin && 0 != pB->szPinyin);
	return AMStrcmp(pA->szPinyin, pB->szPinyin);
}

AMUInt32	IAContact_Hash(const AMVoid *p,size_t t)
{
	AMUInt32 uiRet = 0;
	AMChar *str = ((IAContact *)p)->szID;
	AMAssert(0 != str);
	while(*str != 0)
		uiRet = (uiRet << 5) + (*str++);

	return uiRet;
}

AIM_RESULT IAIMContact_IsOnline( const AMHandle hContact, AMBool *pbOnline )
{
	const IAContact *pCnt = (const IAContact *)hContact;
	AMAssert(AMNULL != pCnt && AMNULL != pbOnline);

	if(eAIM_PRESENCE_OFFLINE == pCnt->ePresence || eAIM_PRESENCE_INVISIBLE == pCnt->ePresence)
	{
		*pbOnline = AMFALSE;
	}
	else
	{
		*pbOnline = AMTRUE;
	}

	return eAIM_RESULT_OK;
}

AMChar* AIM_GetBindIDForContact(AMHandle hIM, IAContact *pCnt)
{
	IAIM* pIm = (IAIM*)hIM;

	AMAssert(0 != pIm);


	if(pIm->pAcnt->szBindID == AMNULL)
		return pIm->pAcnt->szID;
	if(pCnt->szBindUID)
	{
		return pCnt->szBindUID;
	}
	else
	{
		if(AMStrlen(pCnt->szID) > 8 && 0 != AMStrncmp(pCnt->szID, "cnaliyun", 8))
		{
			return pIm->pAcnt->szBindID;
		}
	}
	return pIm->pAcnt->szID;
}

AMVoid		IAContact_AutoSetBindUid(AMHandle hIM, IAContact *pCnt)
{
	AMChar* szBindID = AIM_GetBindIDForContact(hIM, pCnt);

	if(pCnt->szBindUID)
	{
		AMFree(pCnt->szBindUID);
		pCnt->szBindUID = AMNULL;
	}

	if(AMNULL != szBindID)
		IAContact_SetBindUid(pCnt, szBindID, AMStrlen(szBindID));
}
