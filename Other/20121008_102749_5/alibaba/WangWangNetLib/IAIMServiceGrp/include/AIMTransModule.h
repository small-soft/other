#ifndef __AIM_TRANSMODULE_H__
#define __AIM_TRANSMODULE_H__


#include "AIM.h"
#include "AMTask.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*
 *	AIMTransModule
 */


typedef struct  
{
	IAIM		*	pIM;
	AMThreadMutex	mtxLock;
	List			lstTrans;
	AMInt32			iLastTransId;
	AMTaskMgr	*	pTaskMgr;
}AIMTransModule;


AMInt32		AIMTransModule_create(IAIM *pIM, AMHandle *phTransModule);
AMVoid		AIMTransModule_destroy(AMHandle hTransModule);

/*
 *	创建一个TransTask
 */
AMInt32	AIMTransModule_receive(AMHandle hTransModule, const AMChar *szContactId, 
								   const AMChar *szXml, const AMChar *szFileDest, AMInt32 *piTaskId);

AMInt32	AIMTransModule_send(AMHandle hTransModule, const AMChar *szContactId,
								const AMChar *szFile, AMInt32 *piTaskId);

AMInt32	AIMTransModule_cancel(AMHandle hTransModule, AMInt32 iTaskId);

IMnetRetCode AIMTransModule_onGetAppAddr(IMnetHandle hIMnetHandle, EventContent* pEventContent);

AMInt32	AIMTransModule_result(AMHandle hTransModule, AMHandle hTrans, AMInt32 iResult);

AMInt32	AIMTransModule_update(AMHandle hTransModule, AMHandle hTrans, AMInt32 iProgress);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif //__AIM_TRANS_H__
