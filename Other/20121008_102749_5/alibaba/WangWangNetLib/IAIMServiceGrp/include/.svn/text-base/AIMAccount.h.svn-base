#ifndef __AMIMACCOUNT_H__
#define __AMIMACCOUNT_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "IAIMAccount.h"

#define ID_HEAD_LEN  8

	typedef struct IAccount
	{
		AMInt64			_iRid;
		AIM_ACCOUNT_TYPE	eType;
		AMChar	*		szName;
		AMChar	*		szPwd;
		
		AMChar	*		szToken;
		AMInt32			uiTokenLen;

		AMChar	*		szWebMD5;
		AMInt32			uiWebMD5Len;

		AMChar	*		szPhoneNum;
		AMUInt32		uiFlag;	//blockStranger、Hungup、TokenType、E客服、静音、震动、保存密码（最末位标识是否保存密码，1保存，0不保存）
								//tokenType，0:pwToken， 1:uidToken
		AMChar	*		szID;
		enum AIM_PRESENCE	ePresence;

		AMChar	*		szBindID;
		enum AIM_BIND_STATUS	eBindStatus;
		AMInt32			uiBindIDLoginRetCode;

		AMInt32			iGroupStamp;
		AMInt32			iContactStamp;
		AMInt32			iBlackStamp;
		AMInt32			iRevBlackStamp;

		AMInt8			iVerifyType;
		AMChar		*	szSignature;
		AMChar		*	szSigXML;
		AMBool			bGetSigFail;
	}AIMAccount;

	AIMAccount *	IAccount_Create();
	AMVoid			IAccount_Destroy(AIMAccount *pAcnt);
	AMVoid			IAccount_SetNameType(AIMAccount *pAcnt, const AMChar *szName, AMUInt32 uiLen, AIM_ACCOUNT_TYPE eType);
	AMInt32			IAccount_SetID(AIMAccount *pAcnt, const AMChar *szID, AMUInt32 uiLen);
	AMVoid			IAccount_SetBindID(AIMAccount *pAcnt, const AMChar *szID, AMUInt32 uiLen);
	AMVoid			IAccount_SetPwd(AIMAccount *pAcnt, const AMChar *szPwd, AMUInt32 uiPwdLen);
	AMVoid			IAccount_SetToken(AIMAccount *pAcnt, const AMChar *szToken, AMUInt32 uiTokenLen);
	AMVoid			IAccount_SetWebMD5(AIMAccount *pAcnt, const AMChar *szWebMD5, AMUInt32 uiLen);

	AMVoid			IAccount_SetPhoneNum(AIMAccount *pAcnt, const AMChar *szPhone); //, AMUInt32 uiPhoneLen);
	AMVoid			IAccount_SetSignature(AIMAccount *pAcnt, const AMChar *szSignature, AMUInt32 uiLen);
	AMVoid			IAccount_SetSigXML(AIMAccount *pAcnt, const AMChar *szXML, AMUInt32 uiLen);

	AIM_ACCOUNT_TYPE	IAccount_TellType(const AMChar *szContactId, AMUInt32 uiIdLen);
	
	AIMAccount *	IAccount_dup(const AIMAccount *pAcnt);
	AMInt32			IAccount_cmpID(const AMVoid *pA, const AMVoid *pB, size_t s);

	AMUInt16		IAccount_GetFlag(const AIMAccount *pAcnt);			//需要注意:用户Flag为iFlag的高16位
	AMVoid			IAccount_SetFlag(AIMAccount *pAcnt, AMUInt16	uiFlag);//需要注意:用户Flag为iFlag的高16位
	AMUInt32		AMAccount_CaculateFlag(AMBool bSavePwd, AMBool bMute, AMBool bVibrate);

	/**
	* @brief			本地成功登录过的帐号，判断是否在本地保存密码
	* @param hAccount	帐号
	*/
	AIM_RESULT AIMAccount_IsPwdNull(const AMHandle hAccount, AMBool *pIsNull);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif