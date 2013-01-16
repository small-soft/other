#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
Command::Command( shared_ptr<String> command )
{
	disposesDialog = true;
	commandId = 0;
	this->command = command;
}

Command::Command( shared_ptr<String> command, shared_ptr<Image> icon )
{
	disposesDialog = true;
	commandId = 0;
	this->command = command;
	this->icon = icon;
}

Command::Command( shared_ptr<String>command, int id )
{
	disposesDialog = true;
	this->command = command;
	this->commandId = id;
}

Command::Command( shared_ptr<String> command, shared_ptr<Image> icon, int id )
{
	disposesDialog = true;
	this->command = command;
	this->commandId = id;
	this->icon = icon;
}
Command::~Command(void)
{
}

int Command::getId()
{
	 return commandId;
}

shared_ptr<String> Command::getCommandName()
{
	 return command;
}

void Command::setCommandName( shared_ptr<String> command )
{
	 this->command = command;
}

shared_ptr<Image> Command::getIcon()
{
	return icon;
}

void Command::actionPerformed( shared_ptr<ActionEvent> evt )
{

}

void Command::setDisposesDialog( bool disposesDialog )
{
	 this->disposesDialog = disposesDialog;
}

bool Command::isDisposesDialog()
{
	  return disposesDialog;
}

shared_ptr<String> Command::toString()
{
	 return command;
}
__GUI_END_NAMESPACE
