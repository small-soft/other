#ifndef __IASESSION_H__
#define __IASESSION_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define		SYS_SES_NAME		"systemSes"
/**
 * @brief					Get the contacts of this session
 * @param phContact			[in/out] return the contact handle of this session. do not modify or free it.
 */
	AIM_RESULT IAIMSession_GetPeer( AMHandle hSession, AMHandle *phContact);

/**
 * @brief					count the history messages of this session
 */
	AIM_RESULT IAIMSession_CountMsgs(AMHandle hSession, AMInt32 *pCount);

/**
 * @brief					Get the history messages of this session¡£
 * @param iOffset			specify the first message of the result.
 * @param iCount			specify the max count of the result.
 * @param pphMsgArray		[in/out] return an array of message handles, which should be release by IAIMSession_ReleaseMsgs
 * @param piCount			[in/out] return the array size.
 * @more					messages are ordered firstly by "read" attribute(unread messages come first), 
 *							then by time attribute(recent messages come first).  
 */
	AIM_RESULT IAIMSession_GetMsgs(AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **pphMsgArray, AMInt32 *piCount);

/**
 * @brief					release the array returned by IAIMSession_GetMsgs
 */
	AIM_RESULT IAIMSession_ReleaseMsgs(AMHandle hSession, AMHandle *phMsgArray, AMInt32 iArraySize);

/**
 * @brief					count unread messages of this session
 */
	AIM_RESULT IAIMSession_CountUnreadMsgs(AMHandle hSession, AMInt32 *pCount);

/**
* @brief					Get unread messages of this session
* @param iOffset			specify the first message of the result.
* @param iCount				specify the max count of the result.
* @param pphMsgArray		[in/out] return an array of message handles, which should be release by IAIMSession_ReleaseUnreadMsg
* @param piCount			[in/out] return the array size.
* @more						recent message comes first.
*/
	AIM_RESULT IAIMSession_GetUnreadMsgs(AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMHandle **pphMsgArray, AMInt32 *piCount);

/**
 * @brief					release the array returned by IAIMSession_GetUnreadMsg
 */
	AIM_RESULT IAIMSession_ReleaseUnreadMsgs(AMHandle hSession, AMHandle *phMsgArray, AMInt32 iArraySize);

/**
 * @brief					mark all unread messages of this session as read.
 * @param i64MsgId			the id of the message to mark. 0 to mark all msg of this session read.
 * @more					if i64MsgId is not 0, be sure it belongs to this session.
 */
	AIM_RESULT IAIMSession_MarkMsgRead(AMHandle hSession, AMInt64 i64MsgId);

/**
* @brief					delete all history messages of this session.
* @param i64MsgId			the id of the message to remove. 0 to remove all msg of this session.
* @more						if i64MsgId is not 0, be sure it belongs to this session.
*/
	AIM_RESULT IAIMSession_RemoveMsg(AMHandle hSession, AMInt64 i64MsgId);	

#ifdef __cplusplus
};
#endif

#endif // __IASESSION_H__
