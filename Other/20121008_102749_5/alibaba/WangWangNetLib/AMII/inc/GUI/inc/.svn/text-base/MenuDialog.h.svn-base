#ifndef __GUI_MENU_DIALOG_H__
#define __GUI_MENU_DIALOG_H__

#include "inc/Config.h"
#include "inc/Dialog.h"
__GUI_BEGIN_NAMESPACE
class MenuDialog :public Dialog
{
	AM_DECLARE_DYNAMIC(MenuDialog)
public:
	static shared_ptr<MenuDialog > newV();
	virtual ~MenuDialog();
private:
	MenuDialog();
	void constructV();
public:
	void keyReleased(int keyCode);
	void pointerReleased(int x, int y);
};
__GUI_END_NAMESPACE

#endif