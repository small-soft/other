#ifndef __GUI_MENU_BAR_H__
#define __GUI_MENU_BAR_H__

#include "inc/Config.h"
#include "inc/Container.h"
#include "inc/ActionListener.h"
#include "inc/Dialog.h"
__GUI_BEGIN_NAMESPACE

class Command;
class Button;
class ListCellRenderer;
class Form;
class List;

class MenuBar : public Container , public ActionListener
{
	AM_DECLARE_DYNAMIC(MenuBar)
public:
	static shared_ptr<MenuBar> newV(shared_ptr<Form> form);
	virtual ~MenuBar(void);
	shared_ptr<MenuBar> shared_from_this();
protected:
	MenuBar();
	void constructV(shared_ptr<Form> form);
private:
	weak_ptr<Form> form;
	shared_ptr<Command> menuCommand;
	shared_ptr<Vector<shared_ptr<Command> > > commands ;//= new Vector();
	shared_ptr<Vector<shared_ptr<Button> > > soft;
	shared_ptr<VectorArray<shared_ptr<Command> > > softCommand;
	shared_ptr<Button> left;
	shared_ptr<Button> right;
	shared_ptr<Button> main;
	shared_ptr<ListCellRenderer> menuCellRenderer;
	shared_ptr<Transition> transitionIn;
	shared_ptr<Transition> transitionOut;
	shared_ptr<Component> commandList;
	shared_ptr<Style> menuStyle;
	int topMargin, bottomMargin;
	// add by jiajing
	shared_ptr<Command> directCommand; 
public:
	void addDirectCommand(shared_ptr<Command> cmd);
	shared_ptr<Command> getDirectCommand();
	void removeCommand(int index);
	void actionPerformed(shared_ptr<ActionEvent> evt);
	virtual void setUnSelectedStyle(shared_ptr<Style> style);
	void setTransitions(shared_ptr<Transition> transitionIn,
		shared_ptr<Transition> transitionOut);
	shared_ptr<Vector<shared_ptr<Button> > > getSoftButtons();
	virtual shared_ptr<String> getUIID();
	void addCommand(shared_ptr<Command> cmd);
	shared_ptr<Command> getCommand(int index);
	int getCommandCount();
	void addCommand(shared_ptr<Command> cmd, int index);
	void removeAllCommands();
	void removeCommand(shared_ptr<Command> cmd);
	void setMenuCellRenderer(shared_ptr<ListCellRenderer> menuCellRenderer);
	shared_ptr<Style> getMenuStyle();
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);
	virtual void refreshTheme();
	void setCommandList(shared_ptr<Component> commandList);
	shared_ptr<Component> getCommandList();
private:
	void updateCommands();
	shared_ptr<Button> createSoftButton();
	void updateSoftButtonStyle(shared_ptr<Button> b);
	void showMenu();

public:
//protected:
	virtual shared_ptr<Dimension> calcPreferredSize();
};

__GUI_END_NAMESPACE

#endif
