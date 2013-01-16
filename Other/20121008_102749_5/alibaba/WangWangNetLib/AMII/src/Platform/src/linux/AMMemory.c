/*
* AMMemory.c
*
*  Created on: 2009-11-20
*      Author: dengxiang
*/

#include "AMMemory.h"
#include "AMAssert.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef AM_MEMEORY_BLOCK_SUPPOER
#if defined(AM_HAS_MEMORY_CHECK) && !defined(AM_MEMEORY_BLOCK_SUPPOER)
ADAPTER_API AMPVoid a_malloc_impl(AMSize_t size, const AMChar* file, AMInt32 line)
#else
ADAPTER_API AMPVoid a_malloc_impl(AMSize_t size)
#endif
{
	AMPVoid p = NULL;
	p = malloc(size);

#ifdef AM_HAS_MEMORY_CHECK
	PushToTrack(p, size, file, line);
	if(p == NULL)
		AMAssert(0);
#endif
	return p;
}

ADAPTER_API AMPVoid a_calloc_impl(AMSize_t num, AMSize_t size)
{
	return calloc(num, size);
}
ADAPTER_API AMVoid a_free_impl(AMPVoid ptr)
{
#ifdef AM_HAS_MEMORY_CHECK
	RemoveFromTrack(ptr); 
#endif
	free(ptr);
}

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



