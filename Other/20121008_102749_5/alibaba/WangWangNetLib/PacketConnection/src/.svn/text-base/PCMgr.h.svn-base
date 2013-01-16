#ifndef __PACKET_CONNECTION_MGR_H__
#define __PACKET_CONNECTION_MGR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "PCCore.h"
#include "PCContext.h"
#include "PCStruct.h"

	typedef struct ST_ProtocolEngine {
		PCCore*				pPCCore;			
		PCContext*			pPCContext;	
		AMInt32				nCount;
	}ProtocolEngine;

	typedef struct ST_PacketConnection {
		PCReference			pReference;
		PCServiceID			serviceID;
		
		PCReceiver			pReceiver;
		PCPacker			pPacker;
		PCPackerFree		pPackerFree;
		PCUnpacker			pUnpacker;

		PCContext*			pPCContext;
		ProtocolEngine*		pProtocolEngine; 
		PcNetworkConfig*	pNetwork;
		Semaphore			semaphore;
		
		struct ST_PacketConnection* next;
	}PacketConnection;

	typedef struct {
		//PCContext*			pPCContext;				//single.
		//PcNetworkConfig*		pProtocolNetwork;		//single.
		//ProtocolEngine*		pProtocolEngine;		//single
		PacketConnection*	pFirstPC;					//
		Mutex				mgrCritical;
	}PacketConnectionMgr;

	PacketConnection* PCMgrGetPCHandle(PCServiceID serviceID);
	PacketConnectionMgr* PCMgrGetInstance();

	//type == 0: 主动发起关闭socket.
	//type == 1: 被动关闭socket.
	PCRetCode ProtocolNetworkDestory(PacketConnection* pPC, AMInt32 type);

#if IM_NET_SHUT_SOCKET
	PCRetCode ProtocolNetworkShut(PacketConnection *pPC);
#endif
#ifdef __cplusplus
}
#endif

#endif

