/*
* AMMemoryTable.c
*
*  Created on: 2012-03-28
*      Author: tom.lih
*/

#include "AMMemory.h"
#include "stdio.h"

#if defined(AM_HAS_MEMORY_CHECK) && !defined(AM_MEMEORY_BLOCK_SUPPOER)
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
	HANDLE 			tableMutex;
	//HANDLE 			removeMutex;
}MemoryTable;

MemoryTable* gpMemoryTable = NULL;

void AddToList(MemoryTable* pTable, MallocInfo* pInfo)
{
	MemoryListItem *pItem = NULL;
	MemoryListItem *pLast = NULL;
	DWORD dwWaitResult; 

	if(pTable == NULL || pInfo == NULL)
		return;
	
	dwWaitResult = WaitForSingleObject( pTable->tableMutex,INFINITE);

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
	
	ReleaseMutex(pTable->tableMutex);
}

void RemoveFromList(MemoryTable* pTable, void* p)
{
	MemoryListItem *pItem = NULL;
	MemoryListItem *pItemPre = NULL;
	DWORD dwWaitResult; 

	if(pTable == NULL || p == NULL)
		return;

	
	dwWaitResult = WaitForSingleObject( pTable->tableMutex,INFINITE);

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

	ReleaseMutex(pTable->tableMutex);
}

void MemoryTableCreate(MemoryTable** ppObject)
{
	if(ppObject == NULL)
		return;

	*ppObject = (MemoryTable*)malloc(sizeof(MemoryTable));
	if(*ppObject)
	{
		(*ppObject)->pFirst = NULL;
		(*ppObject)->tableMutex = CreateMutex( 
			NULL,                       // no security attributes
			FALSE,                      // initially not owned
			NULL);						// name of mutex

		//(*ppObject)->removeMutex = CreateMutex( 
		//	NULL,                       // no security attributes
		//	FALSE,                      // initially not owned
		//	NULL);						// name of mutex
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

	CloseHandle((*ppObject)->tableMutex);
	//CloseHandle((*ppObject)->removeMutex);
	free(*ppObject);
	*ppObject = NULL;
}

void PushToTrack(void* p, AMInt32 size, const AMChar* file, AMInt32 line)
{
	MallocInfo info;
	if(gpMemoryTable == NULL)
	{
		MemoryTableCreate(&gpMemoryTable);
	}

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
	MemoryListItem* pItem = NULL;
	if(gpMemoryTable != NULL)
	{
		printf("+++++++++++++++++++++ Memory Leak +++++++++++++++++++++++++++++\n");
		pItem = gpMemoryTable->pFirst;
		if(pItem != NULL)
		{
			while(pItem)
			{
				printf("Malloc:%s, line:%d, p=0x%8x, size=%d\n",  
					pItem->info.file, pItem->info.line, pItem->info.address, pItem->info.size);
				pItem = pItem->pNext;
			}
		}
		else
		{
			printf("No Memory Leak. haha!!\n");
		}
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

		MemoryTableDestory(&gpMemoryTable);
	}
}
#endif
