#ifndef __GUI_RUNNABLE_H__
#define __GUI_RUNNABLE_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Runnable
{
public:
	typedef void *(* f)(void *);
	Runnable(){
		point = NULL;
	}
	f get()
	{
		return point;
	}
	virtual void run() = 0;
	virtual ~Runnable() {}
protected:
	f point;
};
__GUI_END_NAMESPACE

#endif
