#ifndef __GUI_RECTANGLE_H__
#define __GUI_RECTANGLE_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Dimension;
	class Rectangle:public Object
	{
	public:
		Rectangle(void);
		Rectangle(int x, int y, const Dimension& size) ;
		Rectangle(int x, int y, shared_ptr<Dimension> size) ;
		Rectangle(int x, int y, int w, int h);
		Rectangle(const Rectangle& rect);
		virtual ~Rectangle(void);
	private:
		int x;
		int y;
		shared_ptr<Dimension> size;
	public:
		shared_ptr<Dimension> getSize() const;
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);
		bool contains(const Rectangle& rect)const;
		bool contains(int rX, int rY, int rWidth, int rHeight)const;
		bool contains(int rX, int rY)const;
		shared_ptr<Rectangle> intersection(int rX, int rY, int rW, int rH) const;
		shared_ptr<Rectangle> intersection(const Rectangle &r)const;
		bool intersects(int x, int y, int width, int height)const;
		bool intersects(const Rectangle& rect)const;
		static bool intersects(int tx, int ty, int tw, int th, int x, int y, int width, int height);
	};
__GUI_END_NAMESPACE

#endif
