#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
ActionEvent::ActionEvent( shared_ptr<Object> source ) : consumed(false),source(source),keyEvent(-1),y(-1)
{
}
ActionEvent::ActionEvent( shared_ptr<Object> source, int keyEvent ) : consumed(false),source(source),keyEvent(keyEvent),y(-1)
{
}
ActionEvent::ActionEvent( shared_ptr<Object> source, int x, int y ) : consumed(false),source(source),keyEvent(x),y(y)
{
}
ActionEvent::~ActionEvent(void)
{
}
shared_ptr<Object> ActionEvent::getSource()
{
	return source;
}
int ActionEvent::getKeyEvent()
{
	return keyEvent;
}
shared_ptr<Command> ActionEvent::getCommand()
{	
	shared_ptr<Command> command = dynamic_pointer_cast<Command>(source);

	return command;
}
void ActionEvent::consume()
{
	 consumed = true;
}
bool ActionEvent::isConsumed()
{
	return consumed;
}
int ActionEvent::getX()
{
	 return keyEvent;
}
int ActionEvent::getY()
{
	  return y;
}
__GUI_END_NAMESPACE
