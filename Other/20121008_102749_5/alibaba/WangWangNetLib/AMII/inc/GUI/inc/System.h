#ifndef __GUI_SYSTEM_H__
#define __GUI_SYSTEM_H__

#include "inc/String.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class System
{
public:
	System(void);
	virtual ~System(void);
	static long currentTimeMillis();
	static String getString (int n);
};
__GUI_END_NAMESPACE

#endif
