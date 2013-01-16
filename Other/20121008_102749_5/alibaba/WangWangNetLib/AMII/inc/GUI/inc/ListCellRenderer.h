#ifndef __LIST_CELL_RENDERER_H__
#define __LIST_CELL_RENDERER_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Component;
class List;
class ListCellRenderer
{
public:
	 virtual shared_ptr<Component> getListCellRendererComponent(shared_ptr<List> list, shared_ptr<Object> value, int index, bool isSelected) = 0;
	 virtual shared_ptr<Component> getListFocusComponent(shared_ptr<List> list) = 0;
	 virtual ~ListCellRenderer() {}
};
__GUI_END_NAMESPACE

#endif

