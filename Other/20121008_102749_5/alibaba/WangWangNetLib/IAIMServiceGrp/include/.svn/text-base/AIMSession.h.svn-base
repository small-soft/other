#ifndef __AMIMSESSION_H__
#define __AMIMSESSION_H__

#include "IAIMSession.h"
#include "AIMContact.h"
#include "AIMUtil.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct IASession
	{
		AMInt64			_iRid;
		AMChar *		szContactID;	//目前只支持单人会话。szContactID唯一标记一个会话。Select Msg 的时候的唯一标记。
		AMHandle		hPeer;// hContact, hTribe, hMulty
		struct IASessionModel	*pSesModel;
	} IASession;

	IASession *	IASession_Create( const AMChar *szCntID, struct IASessionModel *pSes);
	AMVoid		IASession_Destroy(IASession *pSes);

	AMUInt32	IASession_Hash(const AMVoid *p1, size_t t);
	AMInt32		IASession_Cmp(const AMVoid *p1, const AMVoid *p2, size_t t);

	AIM_RESULT AIMSession_GetMsgs( AMHandle hSession, AMInt32 iOffset, AMInt32 iCount, AMBool bUnread
									, AMHandle **pphMsgArray, AMInt32 *piCount);

	/**
	 * @param iFlag			0 release handle Array, and every msg; 1 release handle array only; 2 release every msg only
	 */
	AIM_RESULT AIMSession_ReleaseMsgs( AMHandle hSession, AMHandle *phHandleArray, AMInt32 iCount, AMInt32 iFlag);

	AIM_RESULT	AIMSession_RemoveMsg(AMHandle hSession, AMInt64 i64MsgId, AMBool bHasUnread);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif