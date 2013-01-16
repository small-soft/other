#ifndef __AMIMMESSAGE_H__
#define __AMIMMESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "IAIMessage.h"

	typedef struct IAIMessage
	{
		AMInt64			_iRid;
		AMChar	*		szContactID;
		AIM_MSG_TYPE	eType;
		AMChar	*		szContent;
		AMInt32			iServerTime;
		AMInt32			u2uType;
		AMBool			bUnread;
	}IAIMessage;

	IAIMessage*	IAIMessage_Create();
	IAIMessage*	IAIMessage_Dup(const IAIMessage *pMsg);
	AMVoid		IAIMessage_Destroy(IAIMessage *pMsg);
	AMVoid		IAIMessage_SetCntID(IAIMessage *pMsg, const AMChar * szCntID, AMUInt32 uiLen);
	AMVoid		IAIMessage_SetContent(IAIMessage *pMsg, const AMChar *szContent, AMUInt32 uiLen);
	AMVoid		IAIMessage_SetDateTime(IAIMessage *pMsg, AMInt32 iTime);
	AMInt32		IAIMessage_CmpId(const AMVoid *p1, const AMVoid *p2, AMUInt32 uiSize);
	AMBool		IAIMessage_NeedSave(IAIMessage *pMsg);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif