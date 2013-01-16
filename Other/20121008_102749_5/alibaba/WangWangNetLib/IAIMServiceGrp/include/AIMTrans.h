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
	AMInt32			iTransId;	//��ΪgetAppAddr��sessionId
	AMInt64			lSessionId;
	AMBool			bCanceled;	//�ڹؼ�����˱�־�����Ϊ�棬����ֹ������
	AMBool			bOccupied;	//ռ���еĶ��󣬲������٣������ظ�ռ��
	AMChar		*	szContactId;
	AMChar		*	szFilePath;	//���͵�ʱ�򣬿��ܲ���Ҫ

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