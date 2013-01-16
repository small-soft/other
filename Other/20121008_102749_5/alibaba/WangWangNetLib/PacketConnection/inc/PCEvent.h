#ifndef __PC_EVENT_H__
#define __PC_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "PacketConnection.h"

	PCRetCode EventCreate(PCHandle hHandle, Event** ppEvent, EventId id, void* pContent, AMInt32 size);
    PCRetCode EventCreateEx(PCHandle hHandle, Event** ppEvent, EventId id, void* pContent, AMInt32 size, FreeContent pfnFreeContent);

	void EventDestory(Event** ppEvent);

	PCRetCode EventRebuild(Event* pEvent, EventId id, void* pContent, AMInt32 size, FreeContent pfnFreeContent);

#ifdef __cplusplus
}
#endif
#endif

