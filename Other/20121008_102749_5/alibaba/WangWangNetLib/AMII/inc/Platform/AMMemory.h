/*
* AMMemory.h
*
*  Created on: 2009-11-20
*      Author: qinghua.liqh
*/
#ifndef _AM_MEMORY_H_
#define _AM_MEMORY_H_
#include "AMMemoryConfig.h"

#ifdef AM_MEMEORY_BLOCK_SUPPOER  
//AMMemoryHandle���ڴ�ر�ʶ, ��ʵ�ֶ���.
typedef AMPVoid AMMemoryHandle;
#ifdef __cplusplus 
extern "C" {
#endif
    //�ڴ�ش�������, sizeΪҪ�����Ĵ�С, �ǿձ�ʾ�ɹ�����
    AMMemoryHandle  AMMHandleCreate(AMSize_t size);
    //�ڴ�����ٺ���, �ɹ�����0.
    AMInt32         AMMHandleDestory(AMMemoryHandle handle);
#ifdef __cplusplus 
}
#endif
#endif

#undef AMMallocFunc
#undef AMFree
#undef AMMalloc
#undef AMCalloc
#undef AMRealloc
#undef AMReport


#define AMMalloc		a_malloc_impl
#define AMMallocFunc   a_malloc_impl //denx:��Ϊ����ָ��ʱ��ʹ��
#define AMCalloc		a_calloc_impl
#define AMFree			a_free_impl
#define AMReport    
#define AMRealloc       a_realloc_impl


#define AMMemcpy memcpy
#define AMMemset memset
#define AMMemcmp memcmp

#ifdef __cplusplus 
extern "C" {
#endif
	
//denx add for memory leak check.
#if defined(AM_HAS_MEMORY_CHECK) && !defined(AM_MEMEORY_BLOCK_SUPPOER)
	#undef AMMalloc
	#define AMMalloc(s)		a_malloc_impl(s, __FILE__, __LINE__)
	ADAPTER_API AMPVoid a_malloc_impl(AMSize_t size, const AMChar* file, AMInt32 line);
	
	void PushToTrack(void* p, AMInt32 size, const AMChar* file, AMInt32 line);
	void RemoveFromTrack(void* p);
	void PrintfLeakMemory();

#else
	//end of denx add

    //����ʵ��
    ADAPTER_API AMPVoid  a_malloc_impl(AMSize_t size
	#ifdef AM_MEMEORY_BLOCK_SUPPOER  
        , AMMemoryHandle handle
	#endif
        );
#endif
    
    ADAPTER_API AMPVoid  a_calloc_impl(AMSize_t num, AMSize_t size
		#ifdef AM_MEMEORY_BLOCK_SUPPOER  
			, AMMemoryHandle handle
		#endif
        );
    ADAPTER_API AMVoid    a_free_impl(AMPVoid ptr);
    ADAPTER_API AMPVoid   a_realloc_impl(
		#ifdef AM_MEMEORY_BLOCK_SUPPOER  
			AMMemoryHandle handle,
		#endif
		 AMSize_t size);

    //��������
    //AMPVoid AMMemcpy(AMPVoid dest, const AMVoid* src, AMSize_t count);
    //AMPVoid AMMemset(AMPVoid dest, AMInt32 c, AMSize_t count);
    //AMInt32 AMMemcmp(const AMVoid* buf1, const AMVoid* buf2, AMSize_t count);
#ifdef __cplusplus 
};
#endif

#ifdef __cplusplus
#if defined(AM_HAS_MEMORY_CHECK) && !defined(AM_MEMEORY_BLOCK_SUPPOER)
	# if !defined(__SYMBIAN32__) && !defined(WIN32)
	#include "stdlib.h"
	//denx: ���ط�ʽ
	#define __NO_THROW throw()

	__inline void* operator new(unsigned int s, char* file, int line) {
		void* p = malloc(s);
		if(p) 
			PushToTrack(p, s, file, line);
		return p;
	}

	__inline void* operator new[](unsigned int s, char* file, int line) {
		void* p = malloc(s);
		if(p) 
			PushToTrack(p, s, file, line);
		return p;
	}

	__inline void operator delete(void* p, char* file, int line) {
		RemoveFromTrack(p);
		free(p);
	}

	__inline void operator delete[](void* p, char* file, int line) {
		RemoveFromTrack(p);
		free(p);
	}

	__inline void operator delete[](void* p) __NO_THROW {
		RemoveFromTrack(p);
		free(p);
	}
	
	__inline void operator delete(void *p)	__NO_THROW {
		RemoveFromTrack(p);
		free(p);
	}
	
	//#define new		new(__FILE__, __LINE__)
	#define AMnew		new(__FILE__, __LINE__)
	//���ط�ʽ����
	# endif

	//denx:����һ�ַ���:������ֵ�ú�׺ΪE��,�����Ӹ�ֵ�ú�׺ΪD��.
	#define AMNewE(TYPE, VAR, CONSTRUCT) \
		VAR = new CONSTRUCT; \
		PushToTrack((void*)VAR, sizeof(TYPE), __FILE__, __LINE__);

	#define AMNewD(TYPE, VAR, CONSTRUCT) \
		TYPE* VAR = new CONSTRUCT; \
		PushToTrack((void*)VAR, sizeof(TYPE), __FILE__, __LINE__);

	#define AMNewLD(TYPE, VAR, LEAVE, CONSTRUCT) \
		TYPE* VAR = new (LEAVE) CONSTRUCT; \
		PushToTrack((void*)VAR, sizeof(TYPE), __FILE__, __LINE__);

	#define AMNewLE(TYPE, VAR, LEAVE, CONSTRUCT) \
		VAR = new (LEAVE) CONSTRUCT; \
		PushToTrack((void*)VAR, sizeof(TYPE), __FILE__, __LINE__);

	#define AMDelete(p) \
		RemoveFromTrack(p); \
		delete p;


#else

	#define AMNewE(TYPE, VAR, CONSTRUCT) \
		VAR = new CONSTRUCT; 

	#define AMNewD(TYPE, VAR, CONSTRUCT) \
		TYPE* VAR = new CONSTRUCT; 

	#define AMNewLD(TYPE, VAR, LEAVE, CONSTRUCT) \
		TYPE* VAR = new (LEAVE) CONSTRUCT; 

	#define AMNewLE(TYPE, VAR, LEAVE, CONSTRUCT) \
		VAR = new (LEAVE) CONSTRUCT; 

	#define AMDelete(p) \
		delete p;

#endif
#endif

#endif //_AM_MEMORY_H_
