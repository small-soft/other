#ifndef IM_NET_REQUEST_H
#define IM_NET_REQUEST_H

#ifdef __cplusplus
extern "C" {
#endif
#include "IMnetStruct.h"

	/************************************************************************/
	// 功能简介: 发送心跳包
	// 参数说明: 
	//		IMnetHandle hIMnetHandle:[IN] IMnet模块句柄
	// 返回值  : IMnetRetCode: eOK成功,其他失败.
	/************************************************************************/
	IMnetRetCode IMnetSendHealthCheck(IMnetHandle hIMnetHandle);

	IMnetRetCode IMnetNetworkConfig(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync);


#ifdef __cplusplus
}
#endif

#endif

