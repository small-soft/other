#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "inc/String.h"
#include "inc/Component.h"
#include "inc/Config.h"
#include "inc/FlowLayout.h"

__GUI_BEGIN_NAMESPACE
class Layout;
class Transition;

class Container : public Component
{
	AM_DECLARE_DYNAMIC(Container)
public:
	static shared_ptr<Container> newV(shared_ptr<Layout> layout = new FlowLayout());
protected:
	Container();
	void constructV(shared_ptr<Layout> layout = new FlowLayout());
public:
	virtual ~Container(void);
	shared_ptr<Container> shared_from_this();
private:
	shared_ptr<Layout> layout;
	shared_ptr<Vector<shared_ptr<Component> > > components;// = new java.util.Vector();
	bool shouldLayout;// = true;
	bool scrollableX;
	bool scrollableY;
	shared_ptr<Vector<shared_ptr<Component> > > cmpTransitions;
	int scrollIncrement;// = 20;
public :
	virtual shared_ptr<Layout> getLayout();
	virtual void setLayout(shared_ptr<Layout> layout);
	void invalidate();
	int getLayoutWidth();
	void applyRTL(bool rtl);
	int getLayoutHeight();
	virtual void addComponent(shared_ptr<Component> cmp) ;
	virtual void addComponent(int constraints, shared_ptr<Component> cmp);
	virtual void addComponent(int index, int constraints, shared_ptr<Component> cmp);
	virtual void addComponent(shared_ptr<Component> cmp,int index);
	virtual void replaceAndWait( shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t);
	virtual void replace(shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t);
	virtual void replace(shared_ptr<Component> current, shared_ptr<Component> next);
	virtual void removeComponent(shared_ptr<Component> cmp);
	void removeComponentImpl(shared_ptr<Component> cmp);

	void flushReplace();
	virtual void removeAll();
	void revalidate();
	virtual void paint(shared_ptr<Graphics> g);
	void paintIntersecting(shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int w, int h, bool above) ;

	void layoutContainer();
	void doLayout();
	int getComponentCount();
	shared_ptr<Component> getComponentAt(int index);
	virtual int getComponentIndex(shared_ptr<Component> cmp);
	bool contains(shared_ptr<Component> cmp);
	virtual void scrollComponentToVisible(shared_ptr<Component> c);
	virtual bool moveScrollTowards(int direction, shared_ptr<Component> next);
	shared_ptr<Component> getComponentAt(int x, int y);
	virtual void pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual void pointerPressed(int x, int y) ;
	virtual void refreshTheme() ;
	virtual bool isScrollableX();
	virtual bool isScrollableY();
	virtual void setScrollableX(bool scrollableX);
	virtual void setScrollableY(bool scrollableY);
	virtual void setScrollable(bool scrollable) ;
	virtual void setCellRenderer(bool cellRenderer);
	void setScrollIncrement(int scrollIncrement);
	int getScrollIncrement();
public:
	virtual void repaint(shared_ptr<Component>cmp);
	virtual void initComponentImpl();
	virtual void setShouldCalcPreferredSize(bool shouldCalcPreferredSize);
	virtual void deinitializeImpl();
//	virtual shared_ptr<Form> getComponentForm() ;
protected:
	virtual shared_ptr<Dimension> calcPreferredSize();
private:
	shared_ptr<Container> getScrollableParent();
	void insertComponentAt(int index, shared_ptr<Component> cmp);
	void replaceComponents( shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t, bool wait);
	bool isParentOf(shared_ptr<Component> c);
	bool requestFocusChild();
};

__GUI_END_NAMESPACE

#endif
