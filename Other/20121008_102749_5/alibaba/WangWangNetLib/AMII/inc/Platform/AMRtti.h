/*
 * AMRtti.h
 *
 */

#ifndef _AM_RTTI_H_
#define _AM_RTTI_H_

#ifdef __cplusplus
extern "C" {
#endif

class CRttiBase;
#if 0
struct CRuntimeClass
{
	const char* iClassName;
	int iObjectSize;
	unsigned int iSchema; 
	CRttiBase* (*iCreateObjectProc)(); 
	CRuntimeClass* iBaseClass;
	CRttiBase* CreateObject();
	//0 for false, 1 for true.
	unsigned char IsDerivedFrom(const CRuntimeClass* aBaseClass) const;
	CRuntimeClass* iNextClass;
};

//#define _RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))
//#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)
#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))

#define DECLARE_DYNAMIC(class_name) \
public: \
	static const CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; \

/*
#define _DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; \
*/

#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CRttiBase* CreateObject();

/*
#define _DECLARE_DYNCREATE(class_name) \
	_DECLARE_DYNAMIC(class_name) \
	static CRttiBase* CreateObject();
*/

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); }

/*
#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); }
*/

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CRttiBase* class_name::CreateObject() \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)

#else
#define AM_DECLARE_DYNAMIC(class_name)
#define AM_RUNTIME_CLASS(class_name)
#define AM_IMPLEMENT_DYNAMIC(class_name, base_class_name)
#endif

class CRttiBase
{
#if 0
public:
	virtual CRuntimeClass* GetRuntimeClass() const;
	unsigned char IsKindOf(const CRuntimeClass* aClass) const;
	
public:
	static const CRuntimeClass classCRttiBase;
#endif
};

#ifdef __cplusplus
}
#endif
#endif /* __AM_RTTI_H__*/
