#ifndef __GUI_PAINTER_H__
#define __GUI_PAINTER_H__


#include "inc/Rectangle.h"
#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Graphics;
class Painter
{
public:
	virtual ~Painter() {}
	virtual void paint(shared_ptr<Graphics> g, shared_ptr<Rectangle> rect)=0;
};
__GUI_END_NAMESPACE

#endif
