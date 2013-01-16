#ifndef __GUI_COMMAND_H__
#define __GUI_COMMAND_H__

#include "inc/ActionListener.h"
#include "inc/Config.h"

//#include "inc/String.h"

__GUI_BEGIN_NAMESPACE
class Image;
class String;
class Command: public Object,public ActionListener
{
public:
	Command(shared_ptr<String> command);
	Command(shared_ptr<String> command, shared_ptr<Image> icon);
	Command(shared_ptr<String> command, int id); 
	Command(shared_ptr<String> command, shared_ptr<Image> icon, int id) ;
	virtual ~Command(void);
private:
	bool disposesDialog;// = true;
	shared_ptr<Image> icon;
	shared_ptr<String> command;
	int commandId;
public:
	int getId();
	shared_ptr<String> getCommandName();
	void setCommandName(shared_ptr<String> command);
	shared_ptr<Image> getIcon();
	virtual void actionPerformed(shared_ptr<ActionEvent> evt) ;
	void setDisposesDialog(bool disposesDialog);
	bool isDisposesDialog();
	virtual shared_ptr<String> toString();
};
__GUI_END_NAMESPACE

#endif