#ifndef IM_NET_MAIN_H
#define IM_NET_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IMnetStruct.h"
#include "IMnetRequest.h"
#include "IMnetCallback.h"

	/************************************************************************/
	// structure definition
	/************************************************************************/
	typedef struct ST_IMnet{
		IMnetReference	pReference;				//µ÷ÓÃÕßID
		IMnetCallback*	pIMnetCallback;			
		PCHandle		hPCHandle;
		VarKeeper*		pVarKeeper;
		Mutex			regCritical; //for callback reg and unreg.
		AMInt32			iBlockMsg;	// 1 to block msg of server_type=1.

		AMChar*			szBindUser;		//temp store bind user info while send net packet; free before pack
		AMInt32			nBindUserLen;
	}IMnet;


#define  _GET_SIGNATURE_

#ifdef __cplusplus
}
#endif

#endif

