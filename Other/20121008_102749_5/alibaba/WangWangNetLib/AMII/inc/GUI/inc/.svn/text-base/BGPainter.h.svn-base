#ifndef __BG_PAINTER_H__
#define __BG_PAINTER_H__

#include "inc/Config.h"
#include "inc/Painter.h"
#include "inc/Component.h"
__GUI_BEGIN_NAMESPACE
class Form;
class Rectangle;
class Painter;
class Style;
class Graphics;


class BGPainter:public Object,public Painter
{	
public:
	BGPainter(shared_ptr<Component> componet);
	BGPainter(shared_ptr<Form> parent, shared_ptr<Painter> p);
	virtual ~BGPainter(void);
private:
	weak_ptr<Component> componet;
	weak_ptr<Form> parent;
	shared_ptr<Form> previousTint;
	bool ignorCoordinates;
	shared_ptr<Painter> painter;
	shared_ptr<Rectangle> bgRect;
public:
	void setBgRect(shared_ptr<Rectangle> rect);
	void setIgnorCoordinates(bool ignorCoordinates);
	void setPreviousForm(shared_ptr<Form> previous);
	shared_ptr<Form> getPreviousForm();
	void setParent(shared_ptr<Form> parent);
	virtual void paint(shared_ptr<Graphics> g, shared_ptr<Rectangle> rect);
private:
	void drawGradientBackground(shared_ptr<Style> s, shared_ptr<Graphics> g, int x, int y, int width, int height);

};
__GUI_END_NAMESPACE

#endif
