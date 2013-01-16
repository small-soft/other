#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

MenuDialog::MenuDialog(void)
{
}

MenuDialog::~MenuDialog(void)
{
}
shared_ptr<MenuDialog > MenuDialog::newV()
{
	shared_ptr<MenuDialog > dlg = new MenuDialog();
	dlg->constructV();
	return dlg;
}

void MenuDialog::constructV()
{
	Dialog::constructV();
}

void MenuDialog::keyReleased( int keyCode )
{

	if (keyCode == leftSK && UIManager::getInstance()->getLookAndFeel()->isReverseSoftButtons()) {
		keyCode = Display::getInstance()->getKeyCode(Display::GAME_FIRE);
	}
	else if(keyCode == rightSK && !UIManager::getInstance()->getLookAndFeel()->isReverseSoftButtons()){
		keyCode = Display::getInstance()->getKeyCode(Display::GAME_FIRE);
	}
	else if (Display::getInstance()->getGameAction(keyCode) == Display::GAME_RIGHT) {
		shared_ptr<List> list = dynamic_pointer_cast<List>(this->getMenuBar()->getCommandList());
		if(list.get()!= NULL)
			shared_ptr<Command> c = dynamic_pointer_cast<Command> (list->getSelectedItem());

		/*	if (c instanceof ParentCommand)
		keyCode = Display.getInstance().getKeyCode(
		Display.GAME_FIRE);*/
	}
	Dialog::keyReleased(keyCode);

}

void MenuDialog::pointerReleased( int x, int y )
{
	//to do
}

__GUI_END_NAMESPACE