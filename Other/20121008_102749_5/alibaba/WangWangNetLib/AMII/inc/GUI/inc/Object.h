#ifndef __GUI_OBJECT_H__
#define __GUI_OBJECT_H__

#include "..\..\..\inc\stl\AMWeakPtr.h"
#include "..\..\..\inc\stl\AMEnable_shared_from_this.h"
#include "..\..\..\inc\stl\AMSharePtr.h"
#ifdef WIN32
#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;
#else
#include "AMSTL.h"
#endif

#include "AMRtti.h"
#include "inc/Config.h"



__GUI_BEGIN_NAMESPACE

class String;
class Object //: public CRttiBase
{
	AM_DECLARE_DYNAMIC(Object)
	
public:
	Object(void);
	virtual ~Object(void);
	virtual shared_ptr<String> toString();
};
__GUI_END_NAMESPACE

#endif
