#ifndef IM_NET_REQUEST_H
#define IM_NET_REQUEST_H

#ifdef __cplusplus
extern "C" {
#endif
#include "IMnetStruct.h"

	/************************************************************************/
	// ���ܼ��: ����������
	// ����˵��: 
	//		IMnetHandle hIMnetHandle:[IN] IMnetģ����
	// ����ֵ  : IMnetRetCode: eOK�ɹ�,����ʧ��.
	/************************************************************************/
	IMnetRetCode IMnetSendHealthCheck(IMnetHandle hIMnetHandle);

	IMnetRetCode IMnetNetworkConfig(IMnetHandle hIMnetHandle, AMChar* ip, AMUInt16 port, AMInt32 sync);


#ifdef __cplusplus
}
#endif

#endif

