
/*
 *  CallbackAdapter.h
 * 
 *  Created on  : 2012-06-11
 *  Author      : tom.lih
 */

#ifndef __CALLBACKADAPTER_H__
#define __CALLBACKADAPTER_H__

#include "list.h"
#include "vector.h"

#include "IAIMCallback.h"

typedef struct {
	AMUChar	ucType;		//0表示状态，1表示签名, 2表示头像
	AMChar	*szID;		//IAContact的ContactID的引用，不需要释放
	AMUChar	ucStatus;
	AMChar	*szSignature;	//IAContact的szSignature的引用，不需要释放
	AMInt32	iFlag;			//当前最低位标识是否是主动获取的
}AIM_CONTACT_UPDATE_DATA;

typedef struct {
	AMChar  * szContactIds;
	AMChar  * szNickName;
	AMUInt8   age;
	AMUInt8   gender;
	AMChar  * szCity;
	AMUInt8	  basicStatus;
}AIM_SEARCH_USER_DATA;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	AIM_RESULT	OnNtfForceDisconnected(AMVoid *);
	AIM_RESULT	OnNtfCheckVersion(AMVoid *, AIM_NTF_CHECK_VERSION *);
	AIM_RESULT	OnNtfDataReady(AMVoid *, AIM_NTF_DATA_READY *);
	AIM_RESULT	OnNtfNetInfo(AMVoid *, AIM_NTF_NET_STATUS *);
	AIM_RESULT	OnNtfUpdateGroup(AMVoid *, AIM_NTF_UPDATE_GROUP *);
	AIM_RESULT	OnNtfUpdateContact(AMVoid *, AIM_NTF_UPDATE_CONTACT *);
	AIM_RESULT	OnNtfMesage(AMVoid *, AIM_NTF_MSG *);
	AIM_RESULT	OnNtfAddedBy(AMVoid *, AIM_NTF_ADDED_BY *);
	AIM_RESULT	OnNtfAcceptedBy(AMVoid *, AIM_NTF_ACCEPTED_BY *);
	AIM_RESULT	OnNtfRejectedBy(AMVoid *, AIM_NTF_REJECTED_BY *);
	AIM_RESULT	OnNtfRequestFrom(AMVoid *, AIM_NTF_REQUEST_FROM *);
	AIM_RESULT	OnNtfHelpLogin(AMVoid *, AIM_NTF_HELP_LOGIN *);
	AIM_RESULT	OnNtfUserInfo(AMVoid *, AIM_NTF_USER_INFO *);
	AIM_RESULT	OnNtfProgress(AMVoid *, AIM_NTF_PROGRESS *);
	AIM_RESULT	OnNtfNeedAuth(AMVoid *, AIM_NTF_NEED_AUTH *);

	AIM_RESULT	OnRspLogin(AMVoid *, AIM_RSP_LOGIN *);
	AIM_RESULT	OnRspChgVerify(AMVoid *, AIM_RSP_CHG_VERIFY *);
	AIM_RESULT	OnRspChgSrvMode(AMVoid *, AIM_RSP_CHG_SRV_MODE *);
	AIM_RESULT	OnRspChgSignature(AMVoid *, AIM_RSP_CHG_SIGNATURE *);
	AIM_RESULT	OnRspAddContact(AMVoid *, AIM_RSP_ADD_CONTACT *);
	AIM_RESULT	OnRspDelContact(AMVoid *, AIM_RSP_DEL_CONTACT *);
	AIM_RESULT	OnRspAccept(AMVoid *, AIM_RSP_ACCEPT *);
	AIM_RESULT	OnRspAddBlack(AMVoid *, AIM_RSP_ADD_BLACK *);
	AIM_RESULT	OnRspDelBlack(AMVoid *, AIM_RSP_DEL_BLACK *);
	AIM_RESULT	OnRspGetVerify(AMVoid *, AIM_RSP_GET_VERIFY *);
	AIM_RESULT	OnRspGetProfile(AMVoid *, AIM_RSP_GET_PROFILE *);
	AIM_RESULT	OnRspGetDegree(AMVoid *, AIM_RSP_GET_DEGREE *);
	AIM_RESULT	OnRspGetMemo(AMVoid *, AIM_RSP_GET_MEMO *);
	AIM_RESULT	OnRspGetSignature(AMVoid *, AIM_RSP_GET_SIGNATURE *);
	AIM_RESULT	OnRspGetPortrait(AMVoid *, AIM_RSP_GET_PROTRAIT *);
	AIM_RESULT	OnRspSendMsg(AMVoid *, AIM_RSP_SEND_MSG *);
	AIM_RESULT	OnRspChgPresence(AMVoid *, AIM_RSP_CHG_PRESENCE *);
	AIM_RESULT	OnRspFile(AMVoid *, AIM_RSP_FILE *);
	AIM_RESULT	OnRspCheckCode(AMVoid *, AIM_RSP_CHECK_CODE *);
	AIM_RESULT	OnRspSearchUser(AMVoid *, AIM_RSP_SEARCH_USER *);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __CALLBACKADAPTER_H__