#ifndef IM_NET_CALLBACK_H
#define IM_NET_CALLBACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "IMnet.h"

	struct ST_IMnet;
/************************************************************************/
// IMnetCallback
//		|		 ------------
//      |------> [ id        ]
//               [ pFirstCB  ]  --> [CallbackItem] --> [CallbackItem] --> NULL
//               [ pNext     ]
//               -------------
//                    |
//		   	     ------------
//               [ id        ]
//               [ pFirstCB  ]  --> [CallbackItem] --> [CallbackItem] --> NULL
//               [ pNext     ]
//               -------------
//                    |
//                   NULL
/************************************************************************/
	typedef IMnetRetCode (*CallbackFuncHook)(IMnetHandle hIMnetHandle, Event* pEvt);

	typedef union
	{
		CallbackFunc		pCallback;
		CallbackFuncHook	pCallbackHook;
	}CallbackFuncUnion;

	typedef struct CallbackItemTag
	{
		union
		{
			CallbackFunc		pCallback;
			CallbackFuncHook	pCallbackHook;
		};
		
		struct CallbackItemTag* pNext;
	}CallbackItem;

	typedef struct CallbackEventItemTag
	{
		EventId						 id;
		CallbackItem*				 pFirstCB;
		struct CallbackEventItemTag* pNext;
	}CallbackBlock;

	typedef struct
	{
		CallbackBlock*	pHookFirst;
		CallbackBlock*  pRegisterFirst;
	}IMnetCallback;

	IMnetCallback* IMnetCallbackCreate();
	void IMnetCallbackDestory(IMnetCallback* pCallback);

	IMnetRetCode IMnetCallbackHandle(struct ST_IMnet* pIMnet, Event* pEvent);
	IMnetRetCode IMnetCallbackRegister(IMnetCallback** ppCallback, EventId id, CallbackFunc pCallbackFunc);
	IMnetRetCode IMnetCallbackUnregister(IMnetCallback** ppCallback, EventId id, CallbackFunc pCallbackFunc);

#ifdef __cplusplus
}
#endif

#endif
