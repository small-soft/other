#ifndef __IAIMHISTORYMGR_H__
#define __IAIMHISTORYMGR_H__

#include "AMTypes.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef enum AIM_RESULT		AIM_RESULT;

	/**
	* @brief			得到该会话的历史消息数目
	*/
	AIM_RESULT IAIMHistoryMgr_CountHistoryMsg(AMHandle hHistoryMgr, const AMChar *szContactId, AMInt32 *pCount);

	/**
	* @brief			得到该会话的历史消息的List。
	* @param iOffset	iOffset指明结果List中的第一个消息在该会话所有历史消息中的时间序位置
	* @param iCount	表明结果中消息的最大数量
	* @param phMessages	历史消息的数组。可以用ReleaseHistory释放（IAContactModel_CloseChatSession时也会释放）
	* @param piCount	历史消息数组的大小
	*/
	AIM_RESULT IAIMSession_GetHistoryMsg(AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **phMessages, AMInt32 *piCount);

	/**
	* @brief			释放GetHistory后产生的历史消息。（每次GetHistory会自动释放上次Gethistory的历史消息）
	*/
	AIM_RESULT IAIMSession_ReleaseHistoryMsg(AMHandle hSession);

	/**
	* @brief			当i64MsgId为0时，得到该会话的未读消息数目
	*/
	AIM_RESULT IAIMSession_CountUnreadMsg(AMHandle hSession, AMInt32 iMsgId, AMInt32 *pCount);

	/**
	* @brief			得到该会话的所有未读消息组成的List
	* @param pMessages	未读消息的数组，需要用ReleaseUnreadMsg显示释放该数组和其中的IAIMessage（IAContactModel_CloseChatSession时也会释放）
	* @param piCount	未读消息数组的大小
	*/
	AIM_RESULT IAIMSession_GetUnreadMsg(AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **pMessages, AMInt32 *piCount);

	/**
	* @brief			释放GetUnreadMsg后产生的未读消息。（每次GetUnreadMsg会自动释放上次GetUnreadMsg的未读消息）
	*/
	AIM_RESULT IAIMSession_ReleaseUnreadMsg(AMHandle hSession);

	/**
	* @brief			标记该会话的所有未读消息为已读
	*/
	AIM_RESULT IAIMSession_MarkMsgRead(AMHandle hSession);

	/**
	* @brief			删除该会话的历史消息
	*/
	AIM_RESULT IAIMSession_RemoveMsg(AMHandle hSession);


#ifdef __cplusplus
};
#endif // __cplusplus

#endif //__IAIMHISTORYMGR_H__