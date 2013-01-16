#ifndef NATIVEGRAPHICS_H
#define NATIVEGRAPHICS_H

#include "inc/Config.h"
#include "inc/Object.h"
__GUI_BEGIN_NAMESPACE
class NativeGraphics:public Object
{
public:
	NativeGraphics(void *g = NULL);
	virtual ~NativeGraphics(void);
private:
	void *g;
public:
	void* getNative();
};
__GUI_END_NAMESPACE
#endif