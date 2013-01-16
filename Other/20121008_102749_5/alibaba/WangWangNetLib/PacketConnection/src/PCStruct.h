#ifndef __PC_STRUCT_H__
#define __PC_STRUCT_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "PacketConnection.h"

	#define PC_MAX_PROTOCOL_LEN		20000
	#define PC_MAX_EXT_LEN          512


	#define PROTOCOL_HEAD_LENGTH		24


	typedef struct {
		AMChar		ip[16]; //xxx.xxx.xxx.xxx
		AMUInt16	port;
		AMInt32		fd;
		AMInt32		sync;
		AMInt32		nCount;
		AMInt32		maxHealthCheckMiss;
	}PcNetworkConfig;

	typedef struct {
		AMInt32					second;
		PCMakeHealthCheckEvent	pMaker;
	}PcHealthCheckConfig;

	typedef struct {
		AMInt32		padding;
	}PcShutdownInd;

	typedef struct {
		Semaphore*	pSemaphore;
	}PcClearVarInd;

#ifdef SOCKET_ASYNC
	typedef struct {
		AMInt32 	indType; //SocketStatus define in AMSocket.h
	}PcSocketInd;
#endif

#ifdef __cplusplus
}
#endif

#endif