#ifndef __AMSESSIONMODEL_H__
#define __AMSESSIONMODEL_H__

#include "hashtable.h"
#include "IMnet.h"
#include "AIMSession.h"
#include "AIMessage.h"
#include "sqlite3.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	typedef struct IASessionModel
	{
		OHTable		ohtSession;
		struct IAIM	*	pReference;
		sqlite3	*	pDB;
	}IASessionModel;

	AMVoid				IASessionModel_SetMobileImMessage(const AMChar* mobileImMessage);

	IASessionModel	*	IASessionModel_Create(struct IAIM *pIM);
	AMInt32				IASessionModel_InitDB(IASessionModel *pSesModel);
	AMInt32				IASessionModel_CloseDB(IASessionModel *pSesModel);
	AMVoid				IASessionModel_ClearData(IASessionModel *pSesModel);

	struct IAIM		*	IASessionModel_GetReference(IASessionModel *pSesModel);

	AMVoid				IASessionModel_Destroy(IASessionModel *pSesModel);

	AMVoid				IASessionModel_DeleteAllMsg(IASessionModel *pSesModel);

	AMVoid				AIMSessionModel_DeleteMsgById(IASessionModel *pSesModel, AMInt64 i64MsgId);//删除之前先要markread.
	AMVoid				AIMSessionModel_MarkMsgReadById(IASessionModel *pSesModel, AMInt64 i64MsgId);

	AMInt32				IASessionModel_StoreMsg(IASessionModel *pSesModel, IAIMessage *pMsg, AMBool bSave);

	AMInt32				IASessionModel_OnIncomingChatMsg(IASessionModel *pSesModel, IAIMessage *pMsg);
	AMInt32				IASessionModel_OnIncomingSysMsg(IASessionModel *pSesModel, IAIMessage *pMsg);

	AMVoid				IASessionModel_ListenIMnet(IASessionModel *pSesModel, IMnetHandle pNetModel);
	AMVoid				IASessionModel_UnlistenIMnet(IASessionModel *pSesModel, IMnetHandle pNetModel);

	/**
	* @brief				打开会话。（会话是历史消息的容器，负责历史消息的释放）
	* @param szContactID	指明会话的对象。一般为某个联系人的ID；若为SYS_SES_NAME，则打开系统消息会话
	* @param bCreate		指明如果该会话不存在是，是否创建。		
	*/
	AIM_RESULT IAIMSessionModel_OpenSession(AMHandle hSessionModel, const AMChar *szContactID, AMHandle *phSession);//"systemSes"
	/**
	* @brief				关闭会话。（释放历史消息）
	*/
	AIM_RESULT IAIMSessionModel_CloseSession(AMHandle hSessionModel, AMHandle hSession);

	/**
	* @brief				返回所有已经打开的会话
	*/
	AIM_RESULT IAIMSessionModel_GetSessions(AMHandle hSessionModel, const OHTable **ppOht);

	/**
	* @brief				发送消息
	* @param szCntID		消息的目的联系人的ID
	* @param szContent		消息内容
	*/
	AIM_RESULT IAIMSessionModel_SendMsg(AMHandle hSessionModel, const AMChar *szCntID, const AMChar *szContent, AMInt32 appendMobileImMsg);


#ifdef __cplusplus
};
#endif // __cplusplus

#endif