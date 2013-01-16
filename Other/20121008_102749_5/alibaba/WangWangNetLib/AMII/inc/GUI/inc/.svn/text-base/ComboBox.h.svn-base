/**
* A combo box is a list that allows only one selection at a time, when a user clicks
* the combo box a popup button with the full list of elements allows the selection of
* a single element. The combo box is driven by the list model and allows all the renderer
* features of the List as well. 
* 
* @see List
* @author 
*/

#ifndef __GUI_COMBO_BOX_H__
#define __GUI_COMBO_BOX_H__

#include "inc/List.h"
#include "inc/Config.h"
#include "inc/Dialog.h"
#include "inc/Style.h"

__GUI_BEGIN_NAMESPACE
class ComboBox : public List
{
	AM_DECLARE_DYNAMIC(ComboBox)
	
public:
	static shared_ptr<ComboBox> newV(shared_ptr<ListModel> model  = new DefaultListModel());
	static shared_ptr<ComboBox> newV(shared_ptr<Vector<shared_ptr<Object> > > items);
	static shared_ptr<ComboBox> newV(shared_ptr<VectorArray<shared_ptr<Object> > > items);

	virtual ~ComboBox(void);
	shared_ptr<ComboBox> shared_from_this();
protected:
	ComboBox();
	
	void constructV(shared_ptr<VectorArray<shared_ptr<Object> > > items);
	void constructV(shared_ptr<Vector<shared_ptr<Object> > > items);
	void constructV(shared_ptr<ListModel> model);

public:
	/**
	* @inheritDoc
	*/
	virtual int getBaseline(int width, int height);

	/**
	* @inheritDoc
	*/
	virtual void setSelectedIndex(int selection);

	/**
	* @inheritDoc
	*/
	virtual void setSelectedIndex(int selection, bool scroll);

	/**
	* @inheritDoc
	*/
	virtual void pointerHover(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y);

	/**
	* @inheritDoc
	*/
	virtual void pointerHoverReleased(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y);
	
	/**
	* @inheritDoc
	*/
	virtual void keyReleased(int keyCode);

	/**
	* Prevent the combo box from losing selection in some use cases
	*/
	virtual void selectElement(int selectedIndex);

	/**
	* @inheritDoc
	*/
	virtual void pointerReleased(int x, int y);

	/**
	* @inheritDoc
	*/
	virtual void paint(shared_ptr<Graphics> g);

	/**
	* @inheritDoc
	*/
	virtual int getOrientation();

//protected:
	/**
	* @inheritDoc
	*/
	virtual void laidOut();
	
	/**
	* @inheritDoc
	*/
	virtual shared_ptr<Rectangle> getVisibleBounds();
	
	/**
	* @inheritDoc
	*/
	virtual void fireClicked();

	/**
	* Creates the list object used within the popup dialog. This method allows subclasses
	* to customize the list creation for the popup dialog shown when the combo box is pressed.
	* 
	* @return a newly created list object used when the user presses the combo box.
	*/
	virtual shared_ptr<List> createPopupList();

	/**
	* @inheritDoc
	*/
	virtual shared_ptr<Dimension> calcPreferredSize();

private:
	shared_ptr<Dialog> popupDialog;
	shared_ptr<Style> popupDialogStyle;
	shared_ptr<List> l;
};

__GUI_END_NAMESPACE

#endif
