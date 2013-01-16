#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
Dimension::Dimension(void)
{
	width = 0;
	height = 0;
}
Dimension::Dimension(const Dimension& d)
{
	this->width = d.width;
	this->height = d.height;
}
Dimension::Dimension(int width, int height)
{
	this->width = width;
	this->height = height;
}
Dimension::~Dimension(void)
{
}
void Dimension::setWidth(int width) {
   this->width = width;
}
void Dimension::setHeight(int height) {
   this->height = height;
}
int Dimension::getWidth() const 
{
   return width;
}
int Dimension::getHeight()const
{
   return height;
}
bool Dimension::operator==(const Dimension &d)const
{
	 return d.width == width && d.height == height;
}

bool Dimension::operator<( const Dimension &d ) const
{
	return this->width*this->height < d.height *d.width;
}
__GUI_END_NAMESPACE
