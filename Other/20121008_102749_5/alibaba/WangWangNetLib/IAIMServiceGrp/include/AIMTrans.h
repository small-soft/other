#ifndef __AIM_TRANS_H__
#define __AIM_TRANS_H__

#include "AIM.h"

typedef enum 
{
	eAIM_TYPE_SEND,
	eAIM_TYPE_RECV,
}AIM_TYPE_TRANS;

typedef struct 
{
	AIM_TYPE_TRANS	eType;
	AMInt32			iTransId;	//作为getAppAddr的sessionId
	AMInt64			lSessionId;
	AMBool			bCanceled;	//在关键点检查此标志，如果为真，则终止操作。
	AMBool			bOccupied;	//占用中的对象，不可销毁，不可重复占用
	AMChar		*	szContactId;
	AMChar		*	szFilePath;	//发送的时候，可能不需要

	AMFILE		*	pFile;
	AMUInt32		uiFileSize;
	AMChar			szDigest[36];	//2 byte as extend.
	AMChar		*	szFileName;
	AMChar		*	szExtend;
	AMUInt64		ulObjId;

	AMHandle	*	pTransModule;
}AIMTrans;

AMInt32		AIMTrans_createId(AMInt32 iId, AIMTrans **ppTrans);
AMVoid		AIMTrans_destroy(AIMTrans *pTrans);
AMInt32		AIMTrans_cmpContent(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize);
AMInt32		AIMTrans_cmpPtr(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize);
AMInt32		AIMTrans_cmpId(const AMVoid *pvA, const AMVoid *pvB, AMUInt32 uiSize);

AMInt32		AIMTrans_createSend(const AMChar *szContactId, const AMChar *szFile, AIMTrans **ppTrans);

AMInt32		AIMTrans_createReceive(const AMChar *szContactId, const AMChar *szXML, const AMChar *szDestFile, AIMTrans **ppTrans);

AMInt32		AIMTrans_work(AIMTrans *pTrans, const AMChar *szIp, AMUInt32 uiPort);

#endif //__AIM_TRANS_H__