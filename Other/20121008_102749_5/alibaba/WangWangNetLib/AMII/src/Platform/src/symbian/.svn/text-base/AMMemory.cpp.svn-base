/*
* AMMemory.c
*
*  Created on: 2009-11-20
*      Author: qinghua.liqh
*/

#include "AMMemory.h"
#include "AMAssert.h"
#include <stdlib.h>
#include <e32def.h>
#include <e32std.h>
#include <e32cmn.h>
#include <e32debug.h>
#include "string.h"

#if defined(AMOS_DEBUG) && !defined(AM_MEMEORY_BLOCK_SUPPOER) && !defined(AM_HAS_MEMORY_CHECK)
typedef struct { 
	AMPVoid address; 
	AMInt32 size; 
	AMInt32 line;
	AMChar  file[64]; 
}MallocInfo; 

//list
typedef struct MemoryListItemTag  
{
	MallocInfo					info;
	struct MemoryListItemTag*	pNext;
}MemoryListItem;

typedef struct
{
	MemoryListItem*	pFirst;
	RMutex			addMutex;
	RMutex			removeMutex;
}MemoryTable;

MemoryTable* gpMemoryTable = NULL;

void AddToList(MemoryTable* pTable, MallocInfo* pInfo)
{
	MemoryListItem *pItem = NULL;
	MemoryListItem *pLast = NULL;
	
	if(pTable == NULL || pInfo == NULL)
		return;
	
	pTable->addMutex.Wait();
	
	pItem = (MemoryListItem*)malloc(sizeof(MemoryListItem));
	if(pItem)
	{
		memset(pItem, 0, sizeof(MemoryListItem));
		memcpy(&pItem->info, pInfo, sizeof(MallocInfo));
		
		//the first item be added.
		if(pTable->pFirst == NULL)
			pTable->pFirst = pItem;
		else
		{
			pLast = pTable->pFirst;
			while(pLast->pNext)
				pLast = pLast->pNext;
			
			pLast->pNext = pItem;
		}
	}
	pTable->addMutex.Signal();
}

void RemoveFromList(MemoryTable* pTable, void* p)
{
	MemoryListItem *pItem = NULL;
	MemoryListItem *pItemPre = NULL;

	if(pTable == NULL || p == NULL)
		return;

	pTable->removeMutex.Wait();
	
	pItem	 = pTable->pFirst;
	pItemPre = NULL;
	while(pItem)
	{
		if(pItem->info.address == p)
		{
			if(pItem == pTable->pFirst)
				pTable->pFirst = pItem->pNext;
			else
				pItemPre->pNext = pItem->pNext;
			
			free(pItem);
			break;
		}
		pItemPre = pItem;
		pItem = pItem->pNext;
	}

	pTable->removeMutex.Signal();
}

void MemoryTableCreate(MemoryTable** ppObject)
{
	if(ppObject == NULL)
		return;

	*ppObject = (MemoryTable*)malloc(sizeof(MemoryTable));
	if(*ppObject)
	{
		(*ppObject)->pFirst = NULL;
		(*ppObject)->addMutex.CreateLocal();
		(*ppObject)->removeMutex.CreateLocal();
	}
}

void MemoryTableDestory(MemoryTable** ppObject)
{
	MemoryListItem* pTemp = NULL;
	if(ppObject == NULL)
		return;

	while((*ppObject)->pFirst)
	{
		pTemp = (*ppObject)->pFirst;
		(*ppObject)->pFirst = (*ppObject)->pFirst->pNext;

        //再释放item本身的内存
		free(pTemp);
	}

	(*ppObject)->addMutex.Close();
	(*ppObject)->removeMutex.Close();
	free(*ppObject);
	*ppObject = NULL;
}

void PushToTrack(void* p, AMInt32 size, const AMChar* file, AMInt32 line)
{
	if(gpMemoryTable == NULL)
	{
		MemoryTableCreate(&gpMemoryTable);
	}
	
	MallocInfo info;
	memset(&info, 0, sizeof(info));
	info.address = p;
	info.size = size;
	info.line = line;
	memcpy(info.file, file, sizeof(info.file) - 1);
	
	AddToList(gpMemoryTable, &info);
}

void RemoveFromTrack(void* p)
{
	if(gpMemoryTable != NULL)
	{
		RemoveFromList(gpMemoryTable, p);
	}
}

void PrintfLeakMemory()
{
	if(gpMemoryTable != NULL)
	{
		TInt freeMemory,iBlock,iSize;
		RHeap iHeap=User::Heap();
		freeMemory=iHeap.Available(iBlock);
		iSize=iHeap.Size();
		RDebug::Printf("+++++++++++++++++++++ Memory Leak +++++++++++++++++++++++++++++");
		MemoryListItem* pItem = gpMemoryTable->pFirst;
		if(pItem != NULL)
		{
			while(pItem)
			{
				RDebug::Printf("Malloc:%s, line:%d, p=0x%8x, size=%d",  
						pItem->info.file, pItem->info.line, pItem->info.address, pItem->info.size);
				pItem = pItem->pNext;
			}
		}
		else
		{
			RDebug::Printf("No Memory Leak. haha!!");
		}
		RDebug::Printf("---------------------------------------------------------------");
		RDebug::Printf("heap left=%d(Bytes), heap max=%d(Bytes)", freeMemory, iSize);
		RDebug::Printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		
		MemoryTableDestory(&gpMemoryTable);
	}
}
#endif

#ifndef AM_MEMEORY_BLOCK_SUPPOER
#if defined(AMOS_DEBUG) && !defined(AM_MEMEORY_BLOCK_SUPPOER) && !defined(AM_HAS_MEMORY_CHECK)
ADAPTER_API AMPVoid a_malloc_impl(AMSize_t size, const AMChar* file, AMInt32 line)
#else
ADAPTER_API AMPVoid a_malloc_impl(AMSize_t size)
#endif
{
	AMPVoid p = NULL;
    p = malloc(size);
    
#ifdef AMOS_DEBUG
    PushToTrack(p, size, file, line);
	if(p == NULL)
		User::LeaveNoMemory();
#endif
	return p;
}

ADAPTER_API AMPVoid a_calloc_impl(AMSize_t num, AMSize_t size)
{
    return calloc(num, size);
}
ADAPTER_API AMVoid a_free_impl(AMPVoid ptr)
{
#ifdef AMOS_DEBUG
	RemoveFromTrack(ptr); 
#endif
    free(ptr);
}

//denx add for memory leak check
#if defined(AMOS_DEBUG) && !defined(AM_MEMEORY_BLOCK_SUPPOER) && !defined(AM_HAS_MEMORY_CHECK)
#if 0
void* new(AMUInt32 size, const AMChar *file, AMInt32 line)
{
	void *p = new(size);  

#ifdef AMOS_DEBUG
    PushToTrack(p, size, file, line);
	if(p == NULL)
		User::LeaveNoMemory();
#endif
	
	return p; 
}

void operator delete(void* p) __NO_THROW
{
#ifdef AMOS_DEBUG
	RemoveFromTrack(p); 
#endif
	delete(p);
}

void operator delete[](void* p) __NO_THROW
{
#ifdef AMOS_DEBUG
	RemoveFromTrack(p); 
#endif
	delete(p);
}
#endif
#endif


#else
AMPVoid a_malloc_impl(AMSize_t size, AMMemoryHandle block)
{
    return malloc(size);
}

AMPVoid a_calloc_impl(AMSize_t num, AMSize_t size, AMMemoryHandle block)
{
    return calloc(num, size);
}
AMVoid a_free_impl(AMPVoid ptr)
{
    free(ptr);
}
#endif

#ifdef AM_HAS_MEMORY_CHECK
#ifndef AM_MEMEORY_BLOCK_SUPPOER
AMPVoid  a_malloc_check_impl(AMSize_t size)
{
    return null;
}
AMPVoid  a_calloc_check_impl(AMSize_t num, AMSize_t size)
{
    return null;
}
AMVoid  a_free_check_impl(AMPVoid ptr)
{

}
AMVoid    a_mm_report_impl()
{

}
#else
AMPVoid  a_malloc_check_impl(AMSize_t size, AMMemoryHandle block)
{
    return NULL;
}
AMPVoid  a_calloc_check_impl(AMSize_t num, AMSize_t size , AMMemoryHandle block)
{
    return NULL;
}
AMVoid   a_free_check_impl(AMPVoid ptr)
{
}
AMVoid   a_mm_report_impl()
{

}
#endif
#endif

