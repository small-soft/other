#ifndef __ACTION_EVENT_H__
#define __ACTION_EVENT_H__

#include "inc/Config.h"
#include "inc/Object.h"
__GUI_BEGIN_NAMESPACE
class Command;

class ActionEvent:public Object
{
public:
	ActionEvent(shared_ptr<Object> source);
	ActionEvent(shared_ptr<Object> source, int keyEvent);
	ActionEvent(shared_ptr<Object> source, int x, int y);
	virtual ~ActionEvent(void);
private:
	bool consumed;
	shared_ptr<Object> source;
	int keyEvent;// = -1;
	int y ;//= -1;
public :
	shared_ptr<Object> getSource();
	int getKeyEvent();
	shared_ptr<Command> getCommand();
	void consume();
	bool isConsumed();
	int getX();
	int getY();
};
__GUI_END_NAMESPACE

#endif
