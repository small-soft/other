#ifndef __AMIM_H__
#define	__AMIM_H__

#include "IAIM.h"
#include "AIMAccountModel.h"
#include "AIMContactModel.h"
#include "AIMSessionModel.h"
#include "IMnet.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef	enum {
		eIM_STATUS_IDEL					=0x00,
		eIM_STATUS_FORCEDISC			=0x01,
		eIM_STATUS_LOGINFAIL			=0x02,
		eIM_STATUS_LOGOUTED				=0x03,

		eAIM_STATUS_ALLOTED				=0x04,
		eIM_STATUS_NETCONFIGED			=0x04,
		eIM_STATUS_LOGINED				=0x05,
		eIM_STATUS_RENETCONFIGED		=0x06,
		eIM_STATUS_RELGOINED			=0x07,
		eIM_STATUS_VERSIONCHECKED		=0x08,
		eIM_STATUS_VERSIONUPDATE		=0x09,

		eIM_STATUS_LOGINOKRECVED		=0x0A,

		eIM_STATUS_GROUPRECVED			=0x0B,
		eIM_STATUS_CONTACTRECVED		=0x0C,
		eIM_STATUS_BLACKRECVED			=0x0D,
		eIM_STATUS_ALLREADY				=0x0E,

		eIM_STATUS_VERSIONEXEMPT		=0x0F,
		eIM_STATUS_NETFAIL				=0x10
	}AIM_IM_STATUS;

	typedef struct IAIM
	{
		IAccountModel	*pAcntModel;
		IAContactModel	*pCntModel;
		IASessionModel	*pSesModel;
		AMHandle		hTransModule;
		AMHandle		hAuthModule;

		IMnetHandle		pNetModel;

		AIMAccount		*pAcnt;
		AMUChar			ucTokenFlag;

		AIM_CALLBACK *	callback;

		AMInt32			iTimeDiff;

		AMUChar			ucImStatus;
		AMUChar			ucRetryCnt;

		AMBool			bTest;

		AMInt32			iRecvExcpCount;

		AMChar		*	szRemarkMsg;//
		AMChar		*	szWebSession;
		AMChar		*	szPhoneNum;
		AMInt32			phoneNumStatus;
		AMInt32			phoneNumRetCode;
	} IAIM;


	void IAIM_ListenConnection(IAIM *pIm);
	void IAIM_UnlistenConnection(IAIM *pIm);
	void IAIM_TransStatus(IAIM *pIm, AMUChar status);

// 	/**
// 	* @brief				取消。即当IM处于登录状态（NetConfiged--AllReady之间）时，将其状态转化为IDEL
// 	*/
// 	AMVoid			IAIM_Cancel(IAIM *pIM);

	/**
	* @brief				获取好友加好友状态/发送消息状态(好友不存在或不在线，都不返回)
	*/
	AIM_RESULT		IAIM_GetPeerInfo(AMHandle hIM, const AMChar *szContact);

	//iFlag : 0 release handle Array, and every msg; 1 release handle array only; 2 release every msg only
	AIM_RESULT AIM_ReleasePredefMsgs(AMHandle hIM, AMHandle *phMsgArray, AMInt32 iSize, AMInt32 iFlag);

	AIM_RESULT AIM_GetCurrentWebMD5(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen);

	AIM_RESULT AIM_GetCurrentToken(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen);

	AIM_RESULT AIM_GetCurSigXML(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen);

	AIM_RESULT AIM_GetIMStatus( AMHandle hIM, AMUChar *pucStatus );

	void IAIM_SetTtid(const AMChar* ttid);

	AMChar* IAIM_GetOperationMessage(void);
	AMVoid IAIM_FreeOperationMessage(void);

	AIM_RESULT AIM_GetCurSigXML(AMHandle hIM, const AMChar **pszToken, AMUInt32 *puiLen);

#ifdef __cplusplus
};
#endif
#endif