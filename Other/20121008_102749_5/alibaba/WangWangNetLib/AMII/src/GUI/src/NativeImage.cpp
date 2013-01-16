#include "inc\NativeImage.h"
#include "AMGDI.h"
__GUI_BEGIN_NAMESPACE
NativeImage::NativeImage(void* i)
{
	this->i = i;
}

NativeImage::~NativeImage(void)
{
	AMImageDestroy(i);
	i = NULL;
}

void* NativeImage::getNative()
{
	return i;
}
__GUI_END_NAMESPACE