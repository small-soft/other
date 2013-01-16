#ifndef __DEFAULT_LIST_CELL_RENDERER_H__
#define __DEFAULT_LIST_CELL_RENDERER_H__

#include "inc/ListCellRenderer.h"
#include "inc/Label.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class DefaultListCellRenderer: public Label, public ListCellRenderer
{
	AM_DECLARE_DYNAMIC(DefaultListCellRenderer)
	
public:
	DefaultListCellRenderer(bool showNumbers = showNumbersDefault);
	virtual ~DefaultListCellRenderer(void);
private:
	bool showNumbers;
	static bool showNumbersDefault;// = true;
	shared_ptr<Label> focusComponent;// = new Label();
public:
	virtual void refreshTheme();
	shared_ptr<Component> getListCellRendererComponent(shared_ptr<List> list, shared_ptr<Object> value, int index, bool isSelected);
	shared_ptr<Component> getListFocusComponent(shared_ptr<List> list);
	virtual void repaint();
	bool isShowNumbers();
	void setShowNumbers(bool showNumbers);
	int getSelectionTransparency();
	void setSelectionTransparency(int selectionTransparency);
	static void setShowNumbersDefault(bool def);
	static bool isShowNumbersDefault();
};

__GUI_END_NAMESPACE

#endif
