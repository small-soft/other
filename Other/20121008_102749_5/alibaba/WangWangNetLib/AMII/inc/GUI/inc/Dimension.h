#ifndef __DIMENSION_H__
#define __DIMENSION_H__

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Dimension
{
public:
	Dimension(void);
	Dimension(const Dimension& d);
	Dimension(int width, int height);
	virtual ~Dimension(void);
private:
	int width;   
    int height;
public:
	void setWidth(int width);
	void setHeight(int height);
	int getWidth()const;
	int getHeight()const;
	bool operator == (const Dimension &d)const;  
	bool operator < (const Dimension &d)const;  
};
__GUI_END_NAMESPACE

#endif
