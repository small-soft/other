/*
 * AMRtti.cpp
 *
 */

#include "AMRtti.h"

#if 0
CRttiBase* CRuntimeClass::CreateObject()
{
	if (iCreateObjectProc == 0)
	{
		return 0;
	}

	CRttiBase* object = 0;
	object = (*iCreateObjectProc)();

	return object;
}

unsigned char CRuntimeClass::IsDerivedFrom(const CRuntimeClass* aBaseClass) const
{
	const CRuntimeClass* classThis = this;
	while (classThis != 0)
	{
		if (classThis == aBaseClass)
		{
			return 1;
		}

		classThis = classThis->iBaseClass;
	}

	return 0;
}

const struct CRuntimeClass CRttiBase::classCRttiBase = {
	"CRttiBase", sizeof(CRttiBase), 0xFFFF, 0, 0, 0
};

CRuntimeClass* CRttiBase::GetRuntimeClass() const
{
	//return _RUNTIME_CLASS(CRttiBase);
	return RUNTIME_CLASS(CRttiBase);
}

unsigned char CRttiBase::IsKindOf(const CRuntimeClass* aClass) const
{
	CRuntimeClass* classThis = GetRuntimeClass();
	return classThis->IsDerivedFrom(aClass);
}

#endif