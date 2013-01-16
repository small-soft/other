#ifndef __AIM_AUTH_MODULE_H__

#include "AIM.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

AMInt32	AIMAuthModule_create(IAIM *pIM, AMHandle *phAuthModule);
AMVoid	AIMAuthModule_destroy(AMHandle hAuthModule);

AMInt32	AIMAuthModule_checkCode(AMHandle hAuthModule, AMInt32 iAuthId, const AMChar *szCode);
AMInt32	AIMAuthModule_cancelAuth(AMHandle hAuthModule, AMInt32 iAuthId);
AMInt32	AIMAuthModule_updateCode(AMHandle hAuthModule, AMInt32 iAuthId);

IMnetRetCode AIMAuthModule_onNtfNeedAuth(IMnetHandle hIMnetHandle, EventContent* pEventContent);
IMnetRetCode AIMAuthModule_onRspCheckCode(IMnetHandle hIMnetHandle, EventContent* pEventContent);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif //__AIM_AUTH_MODULE_H__