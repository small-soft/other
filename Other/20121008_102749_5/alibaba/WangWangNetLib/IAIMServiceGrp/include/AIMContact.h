#ifndef __AMIMCONTACT_H__
#define __AMIMCONTACT_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "IAIMContact.h"

	typedef struct IAContact
	{
		AMInt64					_iRid;
		AIM_ACCOUNT_TYPE		eType;
		AMInt64					iParentGid;
		AMChar				*	szID;
		AMChar				*	szName;
		AMChar 				*	szLastMsg;
		AMChar 				*	szSignature;
		AMChar 				*	szPortrait;
		AMChar 				*	szPinyin;

		AIM_PRESENCE			ePresence;
		struct IAGroup		*	pParentGrp;
		AMUInt32				uiFlag;				//	3		2		1		0
													//	_rect	_strg	_revblk	_blk
		AMInt32					iUnreadCnt;

		AMChar				*	szPhone;
		AMChar				*	szBindUID;
	}IAContact;

	IAContact *	IAContact_Create();
	IAContact *	IAContact_Duplicate(const IAContact *pCnt);
	AMVoid		IAContact_Destroy(IAContact *pCnt);
	AMVoid		IAContact_SetCntID(IAContact *pCnt, const AMChar *szID, AMUInt32 uiIdLen);
	AMVoid		IAContact_SetNickName(IAContact *pCnt, const AMChar *sNick, AMUInt32 uiNickLen);
	AMVoid		IAContact_SetPinyin(IAContact *pCnt, const AMChar *szPinyin, AMUInt32 uiLen);
	AMVoid		IAContact_SetLastMsg(IAContact *pCnt, const AMChar *szMsg, AMUInt32 uiLen);
	AMVoid		IAContact_SetPhone(IAContact *pCnt, const AMChar *sPhone, AMUInt32 uiPhoneLen);
	AMVoid		IAContact_SetBindUid(IAContact *pCnt, const AMChar *sUid, AMUInt32 uiUidLen);
	AMVoid		IAContact_AutoSetBindUid(AMHandle hIM, IAContact *pCnt);
	AMInt32		IAContact_SetSignature(IAContact *pCnt, const AMChar *szSignature, AMUInt32 uiLen);
	AMInt32		IAContact_SetPortrait(IAContact *pCnt, const AMChar *szPortrait, AMUInt32 uiLen);
	AMVoid		IAContact_MarkBlack(IAContact *pCnt);
	AMVoid		IAContact_MarkRevBlk(IAContact *pCnt);
	AMVoid		IAContact_MarkStrang(IAContact *pCnt);
	AMVoid		IAContact_MarkRecent(IAContact *pCnt);

	AMInt32		IAContact_CmpID(const AMVoid *p1, const AMVoid *p2, size_t t);
	AMInt32		IAContact_CmpPinyin(const AMVoid *p1, const AMVoid *p2, size_t t);
	AMUInt32	IAContact_Hash(const AMVoid *p,size_t t);

	/**
	* @brief				判断联系人是否在反向黑名单中
	*/
	AMBool		IAContact_IsRevBlack(const IAContact *pCnt);

	/**
	* @brief				由联系人的当前状态得到其是否在线
	*/
	AIM_RESULT IAIMContact_IsOnline(const AMHandle hContact, AMBool *pbOnline);

	/**
	* @brief				得到联系人所在组的ID
	*/
	AIM_RESULT IAIMContact_GetParentGroupID(const AMHandle hContact, AMInt64 *pllID);


	AMBool	AIMContact_isFriend( AMHandle pCntModel, AMHandle pCnt );

	AMChar* AIM_GetBindIDForContact(AMHandle hIM, IAContact *pCnt);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif //__AMIMCONTACT_H__