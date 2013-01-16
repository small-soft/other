#include "PCEvent.h"
#include "stdio.h"
#include "string.h"

PCRetCode EventCreate(PCHandle hHandle, Event** ppEvent, EventId id, void* pContent, AMInt32 size)
{
	EventContent* pEventContent = NULL;

	if(ppEvent == NULL || pContent == NULL || size == 0)
		return eInvalidParam;

	*ppEvent = (Event*)AMMalloc(sizeof(Event));
	if(*ppEvent == NULL)
	{
		return eMallocError;
	}

	pEventContent = (EventContent*)AMMalloc(size);	
	if(pEventContent == NULL)
	{
		AMFree(*ppEvent);
		*ppEvent = NULL;

		return eMallocError;
	}
	memcpy(pEventContent, pContent, size);

	(*ppEvent)->id = id;
	(*ppEvent)->pContent = pEventContent;
	(*ppEvent)->pfnFreeContent = NULL;
	(*ppEvent)->hPCHandle = hHandle;
	return eOK;
}

PCRetCode EventCreateEx(PCHandle hHandle, Event** ppEvent, EventId id, void* pContent, AMInt32 size, FreeContent pfnFreeContent)
{
    PCRetCode retCode = EventCreate(hHandle, ppEvent, id, pContent, size);
    
	(*ppEvent)->pfnFreeContent = pfnFreeContent;

    if(retCode != eOK && pfnFreeContent != NULL)
        pfnFreeContent(pContent);

    return retCode;
}

void EventDestory(Event** ppEvent)
{
	if(ppEvent && *ppEvent != NULL)
	{
        //此处调用各自结构体内函数来进行内存释放
        if((*ppEvent)->pfnFreeContent != NULL)
            (*ppEvent)->pfnFreeContent((*ppEvent)->pContent);

		AMFree((*ppEvent)->pContent);
		AMFree(*ppEvent);
		*ppEvent = NULL;
	}
}


PCRetCode EventRebuild(Event* pEvent, EventId id, void* pContent, AMInt32 size, FreeContent pfnFreeContent)
{
	if(pEvent == NULL || pContent == NULL)
		return eInvalidParam;

	//此处调用各自结构体内函数来进行内存释放
	if(pEvent->pfnFreeContent != NULL)
		pEvent->pfnFreeContent(pEvent->pContent);
	AMFree(pEvent->pContent);

	pEvent->id = id;
	pEvent->pfnFreeContent = pfnFreeContent;
	pEvent->pContent = (EventContent*)AMMalloc(size);	
	memcpy(pEvent->pContent, pContent, size);
	return eOK;
}