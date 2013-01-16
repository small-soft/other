#include "AIMAccount.h"

#include "IAIM.h"		// for AIM_RESULT and AIM_PRESENCE
#include "AIMUtil.h"	//for DPRINT

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"

const AMChar *szID_Head[] = {
	"cntaobao",
	"cnalichn",
	"cnkoubei",
	"wangwang",
	"chnyahoo",
	"enaliint",
	"cnanonym",
	"cnalimam",
	"cnaliyun",
};

AIMAccount *		IAccount_Create()
{
	AIMAccount *pRet = AMMalloc(sizeof(AIMAccount));
	AMAssert(0 != pRet);
	AMMemset(pRet, 0, sizeof(AIMAccount));

	return pRet;
}

AMVoid			IAccount_SetNameType(AIMAccount *pAcnt, const AMChar *szName, AMUInt32 uiNameLen, AIM_ACCOUNT_TYPE eType)
{
	AMAssert(0 != pAcnt);
	AMAssert(0 != szName  && eType>=0 && eType <= 8);

	if(pAcnt->szName)
	{
		AMFree(pAcnt->szName);
		pAcnt->szName = 0;
	}
	pAcnt->szName = AMMalloc(uiNameLen + 1);
	AMAssert(0 != pAcnt->szName);
	AMMemset(pAcnt->szName, 0, uiNameLen + 1);
	AMMemcpy(pAcnt->szName, szName, uiNameLen);
	
	pAcnt->eType = eType;

	if(pAcnt->szID)
	{
		AMFree(pAcnt->szID);
		pAcnt->szID = 0;
	}
	pAcnt->szID = AMMalloc(uiNameLen + ID_HEAD_LEN + 1);
	AMAssert(0 != pAcnt->szID);
	AMMemset(pAcnt->szID, 0, uiNameLen + ID_HEAD_LEN + 1);
	AMStrcpy(pAcnt->szID, szID_Head[eType]);
	AMMemcpy(pAcnt->szID + ID_HEAD_LEN, szName, uiNameLen);
}

AIM_ACCOUNT_TYPE	IAccount_TellType(const AMChar *szContactId, AMUInt32 uiIdLen)
{
	AMInt32 i=0;
	AMAssert(szContactId);
	if(ID_HEAD_LEN >= uiIdLen)
		return eAIM_ACNTYPE_WRONG;

	for(i=0; i<sizeof(szID_Head)/sizeof(szID_Head[0]); i++)
	{
		if(0 == AMMemcmp(szContactId, szID_Head[i], ID_HEAD_LEN))
			break;
	}

	if(i<sizeof(szID_Head)/sizeof(szID_Head[0]))
		return (AIM_ACCOUNT_TYPE)i;
	else
		return eAIM_ACNTYPE_WRONG;
}

AMInt32			IAccount_SetID(AIMAccount *pAcnt, const AMChar *szID, AMUInt32 uiIdLen)
{
	AMUChar ucType = 0;
	AIM_ACCOUNT_TYPE	eType = eAIM_ACNTYPE_WRONG;
	AMAssert(0 != pAcnt && 0 != szID);

	eType = IAccount_TellType(szID, uiIdLen);

	AMAssert(eAIM_ACNTYPE_WRONG != eType);

	IAccount_SetNameType(pAcnt, szID+8, uiIdLen-8, eType);

	return 0;
}

AMVoid			IAccount_SetBindID(AIMAccount *pAcnt, const AMChar *szBindID, AMUInt32 uiIdLen)
{
	AMAssert(0 != pAcnt && 0 != szBindID);
	if(pAcnt->szBindID)
	{
		AMFree(pAcnt->szBindID);
		pAcnt->szBindID = 0;
	}
	pAcnt->szBindID = (AMChar *)AMMalloc(uiIdLen+1);
	AMAssert(0 != pAcnt->szBindID);
	AMMemcpy(pAcnt->szBindID, szBindID, uiIdLen);
	pAcnt->szBindID[uiIdLen] = 0;
}

AMVoid			IAccount_SetPwd(AIMAccount *pAcnt, const AMChar *szPwd, AMUInt32 uiPwdLen)
{
	AMAssert(0 != pAcnt && 0 != szPwd);
	if(pAcnt->szPwd)
	{
		AMFree(pAcnt->szPwd);
		pAcnt->szPwd = 0;
	}
	pAcnt->szPwd = (AMChar *)AMMalloc(uiPwdLen+1);
	AMAssert(0 != pAcnt->szPwd);
	AMMemcpy(pAcnt->szPwd, szPwd, uiPwdLen);
	pAcnt->szPwd[uiPwdLen] = 0;
}

AMVoid			IAccount_SetSignature(AIMAccount *pAcnt, const AMChar *szSignature, AMUInt32 uiLen)
{
	AMAssert(0 != pAcnt);
	if(pAcnt->szSignature)
	{
		AMFree(pAcnt->szSignature);
		pAcnt->szSignature = 0;
	}

	if(0 == szSignature)
		return ;

	pAcnt->szSignature = (AMChar *)AMMalloc(uiLen+1);
	AMAssert(0 != pAcnt->szSignature);
	AMMemcpy(pAcnt->szSignature, szSignature, uiLen);
	pAcnt->szSignature[uiLen] = 0;
}

AMVoid			IAccount_SetSigXML(AIMAccount *pAcnt, const AMChar *szXML, AMUInt32 uiLen)
{
	AMAssert(0 != pAcnt);
	if(pAcnt->szSigXML)
	{
		AMFree(pAcnt->szSigXML);
		pAcnt->szSigXML = 0;
	}

	if(0 == uiLen)
		return ;

	pAcnt->szSigXML = (AMChar *)AMMalloc(uiLen+1);
	AMAssert(0 != pAcnt->szSigXML);
	AMMemcpy(pAcnt->szSigXML, szXML, uiLen);
	pAcnt->szSigXML[uiLen] = 0;
}

AMVoid			IAccount_SetPhoneNum(AIMAccount *pAcnt, const AMChar *szPhone)//, AMUInt32 uiPhoneLen)
{
	AMUInt32 uiPhoneLen = 0;
	AMAssert(0 != pAcnt && 0 != szPhone);
	if(pAcnt->szPhoneNum)
	{
		AMFree(pAcnt->szPhoneNum);
		pAcnt->szPhoneNum = 0;
	}
	uiPhoneLen = AMStrlen(szPhone);
	pAcnt->szPhoneNum = (AMChar *)AMMalloc(uiPhoneLen+1);
	AMAssert(0 != pAcnt->szPhoneNum);
	AMMemcpy(pAcnt->szPhoneNum, szPhone, uiPhoneLen);
	pAcnt->szPhoneNum[uiPhoneLen] = 0;
}

AMVoid			IAccount_SetToken(AIMAccount *pAcnt, const AMChar *szToken, AMUInt32 uiTokenLen)
{
	AMAssert(0 != pAcnt && 0 != szToken);
	if(pAcnt->szToken)
	{
		AMFree(pAcnt->szToken);
		pAcnt->szToken = 0;
		pAcnt->uiTokenLen = 0;
	}
	pAcnt->szToken = (AMChar *)AMMalloc(uiTokenLen+1);
	AMAssert(0 != pAcnt->szToken);
	AMMemcpy(pAcnt->szToken, szToken, uiTokenLen);
	pAcnt->szToken[uiTokenLen] = 0;
	pAcnt->uiTokenLen = uiTokenLen;
}

AMVoid			IAccount_SetWebMD5(AIMAccount *pAcnt, const AMChar *szToken, AMUInt32 uiTokenLen)
{
	AMAssert(0 != pAcnt && 0 != szToken);
	if(pAcnt->szWebMD5)
	{
		AMFree(pAcnt->szWebMD5);
		pAcnt->szWebMD5 = 0;
		pAcnt->uiWebMD5Len = 0;
	}
	pAcnt->szWebMD5 = (AMChar *)AMMalloc(uiTokenLen+1);
	AMAssert(0 != pAcnt->szWebMD5);
	AMMemcpy(pAcnt->szWebMD5, szToken, uiTokenLen);
	pAcnt->szWebMD5[uiTokenLen] = 0;
	pAcnt->uiWebMD5Len = uiTokenLen;
}


AIMAccount *		IAccount_dup(const AIMAccount *pAcnt)
{
	AIMAccount *pRet = 0;
	AMAssert(0 != pAcnt);
	pRet = IAccount_Create();
	IAccount_SetNameType(pRet, pAcnt->szName, AMStrlen(pAcnt->szName), pAcnt->eType);

	if(pAcnt->szPwd)
		IAccount_SetPwd(pRet, pAcnt->szPwd, AMStrlen(pAcnt->szPwd));
	if(pAcnt->szToken)
		IAccount_SetToken(pRet, pAcnt->szToken, AMStrlen(pAcnt->szToken));
	if(pAcnt->szPhoneNum)
		IAccount_SetPhoneNum(pRet, pAcnt->szPhoneNum);

	pRet->iGroupStamp = pAcnt->iGroupStamp;
	pRet->iContactStamp = pAcnt->iContactStamp;
	pRet->iBlackStamp = pAcnt->iBlackStamp;
	pRet->iRevBlackStamp = pAcnt->iRevBlackStamp;
	pRet->uiFlag = pAcnt->uiFlag;
	pRet->ePresence = pAcnt->ePresence;
	return pRet;
}

AMVoid			IAccount_Destroy(AIMAccount *pAcnt)
{
	AMAssert(0 != pAcnt);
	DPRINT("IAccount_Destroy..............%s\n", pAcnt->szID?pAcnt->szID:"0");
	if(pAcnt->szID)
	{
		AMFree(pAcnt->szID);
		pAcnt->szID = 0;
	}
	if(pAcnt->szBindID)
	{
		AMFree(pAcnt->szBindID);
		pAcnt->szBindID = 0;
	}
	if(pAcnt->szName)
	{
		AMFree(pAcnt->szName);
		pAcnt->szName = 0;
	}
	if(pAcnt->szPwd)
	{
		AMFree(pAcnt->szPwd);
		pAcnt->szPwd = 0;
	}
	if(pAcnt->szToken)
	{
		AMFree(pAcnt->szToken);
		pAcnt->szToken = 0;
	}
	if(pAcnt->szWebMD5)
	{
		AMFree(pAcnt->szWebMD5);
		pAcnt->szWebMD5 = 0;
	}
	if(pAcnt->szPhoneNum)
	{
		AMFree(pAcnt->szPhoneNum);
		pAcnt->szPhoneNum = 0;
	}
	if(pAcnt->szSignature)
	{
		AMFree(pAcnt->szSignature);
		pAcnt->szSignature = AMNULL;
	}
	if(pAcnt->szSigXML)
	{
		AMFree(pAcnt->szSigXML);
		pAcnt->szSigXML = AMNULL;
	}
	AMFree(pAcnt);
}

AIM_RESULT IAIMAccount_GetId( AMHandle hAccount, const AMChar **pszId )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	*pszId = pAcnt->szID;

	return eAIM_RESULT_OK;
}


AIM_RESULT IAIMAccount_GetName( AMHandle hAccount, const AMChar **pszName )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	*pszName = pAcnt->szName;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_GetType( AMHandle hAccount, AIM_ACCOUNT_TYPE *pType )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	*pType = pAcnt->eType;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsPwdNULL( AMHandle hAccount, AMBool *pIsAMNULL )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if((pAcnt->uiFlag & 0x01) == 0 || 0 == pAcnt->szToken/*|| (pAcnt->uiFlag & 0x10)*/)//0x10使UIDToken登录的帐号不保存密码
	{
		*pIsAMNULL = AMTRUE;
	}
	else
	{
		*pIsAMNULL = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsSavePwd( AMHandle hAccount, AMBool *pIsSave )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(0x01 == (pAcnt->uiFlag&0x01))
	{
		*pIsSave = AMTRUE;
	}
	else
	{
		*pIsSave = AMFALSE;
	}
	
	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsVibrate( AMHandle hAccount, AMBool *pIsVibrate )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(0x02 == (pAcnt->uiFlag&0x02))
	{
		*pIsVibrate = AMTRUE;
	}
	else
	{
		*pIsVibrate = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsMute( AMHandle hAccount, AMBool *pIsMute )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(0x04 == (pAcnt->uiFlag&0x04))
	{
		*pIsMute = AMTRUE;
	}
	else
	{
		*pIsMute = AMFALSE;
	}
	
	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsHungup( AMHandle hAccount, AMBool *pbHungup)
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(0x20 == (pAcnt->uiFlag&0x20))
	{
		*pbHungup = AMTRUE;
	}
	else
	{
		*pbHungup = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_IsECustomer( AMHandle hAccount, AMBool *pbECustomer)
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(0x08 == (pAcnt->uiFlag&0x08))
	{
		*pbECustomer = AMTRUE;
	}
	else
	{
		*pbECustomer = AMFALSE;
	}

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_SetSavePwd( AMHandle hAccount, AMBool bSave )
{
	AIMAccount *pAcnt = (AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(AMTRUE == bSave)
		pAcnt->uiFlag |= 0x01;
	else
		pAcnt->uiFlag &= ~0x01;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_SetVibrate( AMHandle hAccount, AMBool bVibrate )
{
	AIMAccount *pAcnt = (AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(AMTRUE == bVibrate)
		pAcnt->uiFlag |= 0x02;
	else
		pAcnt->uiFlag &= ~0x02;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_SetMute( AMHandle hAccount, AMBool bMute )
{
	AIMAccount *pAcnt = (AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if(AMTRUE == bMute)
		pAcnt->uiFlag |= 0x04;
	else
		pAcnt->uiFlag &= ~0x04;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_GetPresence( const AMHandle hAccount, AIM_PRESENCE *pPresence )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	*pPresence = pAcnt->ePresence;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMAccount_GetSetting( AMHandle hAccount, AIM_ACCOUNT_SETTING *pSetting )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt && AMNULL != pSetting);

	IAIMAccount_GetPresence(hAccount, &pSetting->eDefaultPresence);
	IAIMAccount_IsSavePwd(hAccount, &pSetting->bSavePwd);
	IAIMAccount_IsMute(hAccount, &pSetting->bMute);
	IAIMAccount_IsVibrate(hAccount, &pSetting->bViberate);

	return eAIM_RESULT_OK;
}

AMUInt32		AMAccount_CaculateFlag(AMBool bSavePwd, AMBool bMute, AMBool bVibrate)
{
	AMUInt32 uiRet = 0;

	if(AMTRUE == bSavePwd)
		uiRet |= 0x01;

	if(AMTRUE == bMute)
		uiRet |= 0x02;

	if(AMTRUE == bVibrate)
		uiRet |= 0x04;

	return uiRet;
}


AMUInt16		IAccount_GetFlag(const AIMAccount *pAcnt)
{
	AMAssert(0 != pAcnt);
	return (pAcnt->uiFlag>>16)&0xFFFF;
}

AMVoid			IAccount_SetFlag(AIMAccount *pAcnt, AMUInt16	uiFlag)
{
	AMAssert(0 != pAcnt);
	pAcnt->uiFlag |= uiFlag<<16;
}

AMInt32			IAccount_cmpID(const AMVoid *pA, const AMVoid *pB, size_t s)
{
	AIMAccount *pAcntA, *pAcntB;
	AMAssert(0 != pA && 0 != pB);
	pAcntA = (AIMAccount *)pA;
	pAcntB = (AIMAccount *)pB;
	AMAssert(pAcntA->szID != 0 && pAcntB->szID != 0);
	DPRINT("IAccount_cmpID.................%s, %s\n", pAcntA->szID, pAcntB->szID);
	return AMStrcmp(pAcntA->szID, pAcntB->szID);
}

AIM_RESULT AIMAccount_IsPwdNull( const AMHandle hAccount, AMBool *pIsNull )
{
	const AIMAccount *pAcnt = (const AIMAccount *)hAccount;
	AMAssert(0 != pAcnt);

	if((pAcnt->uiFlag & 0x01) == 0 || 0 == pAcnt->szToken/*|| (pAcnt->uiFlag & 0x10)*/)//0x10使UIDToken登录的帐号不保存密码
	{
		*pIsNull = AMTRUE;
	}
	else
	{
		*pIsNull = AMFALSE;
	}

	return eAIM_RESULT_OK;
}