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
#ifdef AMOS_DEBUG
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

