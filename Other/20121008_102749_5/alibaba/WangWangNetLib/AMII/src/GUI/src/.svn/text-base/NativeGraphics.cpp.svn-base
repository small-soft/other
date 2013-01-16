#include "inc\NativeGraphics.h"
#include "AMGDI.h"
__GUI_BEGIN_NAMESPACE
NativeGraphics::NativeGraphics(void* g)
{
	this->g = g;
}

NativeGraphics::~NativeGraphics(void)
{
	AMGraphicsDestroy(g);
	g = NULL;
}

void* NativeGraphics::getNative()
{
	return g;
}
__GUI_END_NAMESPACE