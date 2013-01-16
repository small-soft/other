#ifndef __GUI_TRANSITION_H__
#define __GUI_TRANSITION_H__

#include "inc/Animation.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Component;
//abstract class
class Transition:public Animation
{
private:
	shared_ptr<Component> source;
	shared_ptr<Component> destination;
public:
	void init(shared_ptr<Component> source, shared_ptr<Component> destination);
	virtual void initTransition();
	shared_ptr<Component> getDestination();
	shared_ptr<Component> getSource();
	virtual void cleanup();
	virtual shared_ptr<Transition> copy();
	virtual shared_ptr<Transition> copy(bool reverse);
	virtual ~Transition() {}
protected:
	 void cleanSource();
};
__GUI_END_NAMESPACE

#endif
