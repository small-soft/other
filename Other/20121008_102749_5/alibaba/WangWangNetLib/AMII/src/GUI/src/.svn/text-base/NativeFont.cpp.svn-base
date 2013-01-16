#include "inc\NativeFont.h"
#include "AMGDI.h"

__GUI_BEGIN_NAMESPACE
NativeFont::NativeFont(void* f)
{
	this->f = f;
}

NativeFont::~NativeFont(void)
{
	AMFontDestroy(f);
	f = NULL;
}

void* NativeFont::getNative()
{
	return f;
}
__GUI_END_NAMESPACE