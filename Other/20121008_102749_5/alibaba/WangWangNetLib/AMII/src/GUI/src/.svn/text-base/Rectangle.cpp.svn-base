#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
	Rectangle::Rectangle(void)
	{
		size = new Dimension();
	}

	Rectangle::Rectangle(int x, int y, const Dimension& size )
	{
		this->x = x;
		this->y = y;
		this->size = new Dimension(size);
	}

	Rectangle::Rectangle( int x, int y, int w, int h )
	{
		this->x = x;
		this->y = y;
		this->size = new Dimension(w, h);
	}

	Rectangle::Rectangle(const Rectangle& rect )
	{
		this->x = rect.getX();
		this->y = rect.getY();
		this->size = new Dimension(rect.getSize()->getWidth(), rect.getSize()->getHeight());
	}

	Rectangle::Rectangle( int x, int y, shared_ptr<Dimension>  size )
	{
		this->x = x;
		this->y = y;
		this->size = size;
	}
	Rectangle::~Rectangle(void)
	{
	}
	shared_ptr<Dimension> Rectangle::getSize() const
	{
		return size;
	}

	int Rectangle::getX()const
	{
		return x;
	}
	int Rectangle::getY() const
	{
		return y;
	}
	void Rectangle::setX( int x )
	{
		this->x = x;
	}
	void Rectangle::setY( int y )
	{
		this->y = y;
	}
	bool Rectangle::contains( const Rectangle& rect )const
	{
		return contains(rect.x, rect.y, rect.size->getWidth(), rect.size->getHeight());
	}

	bool Rectangle::contains( int rX, int rY, int rWidth, int rHeight )const
	{
		return x <= rX && y <= rY && x + size->getWidth() >= rX + rWidth &&
			y + size->getHeight() >= rY + rHeight;
	}

	bool Rectangle::contains( int rX, int rY )const
	{
		return x <= rX && y <= rY && x + size->getWidth() >= rX &&
			y + size->getHeight() >= rY;
	}

	shared_ptr<Rectangle> Rectangle::intersection( int rX, int rY, int rW, int rH )const
	{
		int tx1 = this->x;
		int ty1 = this->y;
		int rx1 = rX;
		int ry1 = rY;
		long tx2 = tx1; tx2 += this->size->getWidth();
		long ty2 = ty1; ty2 += this->size->getHeight();
		long rx2 = rx1; rx2 += rW;
		long ry2 = ry1; ry2 += rH;
		if (tx1 < rx1) {
			tx1 = rx1;
		}
		if (ty1 < ry1) {
			ty1 = ry1;
		}
		if (tx2 > rx2) {
			tx2 = rx2;
		}
		if (ty2 > ry2) {
			ty2 = ry2;
		}
		tx2 -= tx1;
		ty2 -= ty1;
		// tx2,ty2 will never overflow (they will never be
		// larger than the smallest of the two source w,h)
		// they might underflow, though...
		if (tx2 < 0) {
			tx2 = 0;
		}
		if (ty2 < 0) {
			ty2 = 0;
		}
		shared_ptr<Rectangle> ret = new Rectangle(tx1, ty1, (int) tx2, (int) ty2);
		return ret;
	}

	shared_ptr<Rectangle> Rectangle::intersection(const Rectangle &r )const
	{
		return intersection(r.x, r.y, r.size->getWidth(), r.size->getHeight());
	}

	bool Rectangle::intersects( int x, int y, int width, int height )const
	{
		int tw = size->getWidth();
		int th = size->getHeight();
		return intersects(this->x, this->y, tw, th, x, y, width, height);
	}

	bool Rectangle::intersects(const Rectangle& rect )const
	{
		return intersects(rect.getX(), rect.getY(),
			rect.getSize()->getWidth(), rect.getSize()->getHeight());
	}

	bool Rectangle::intersects( int tx, int ty, int tw, int th, int x, int y, int width, int height )
	{
		int rw = width;
		int rh = height;
		if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
			return false;
		}
		int rx = x;
		int ry = y;
		rw += rx;
		rh += ry;
		tw += tx;
		th += ty;
		return ((rw < rx || rw > tx) &&
			(rh < ry || rh > ty) &&
			(tw < tx || tw > rx) &&
			(th < ty || th > ry));

	}
__GUI_END_NAMESPACE
