#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

void Transition::init( shared_ptr<Component> source, shared_ptr<Component> destination )
{
	this->source = source;
	this->destination = destination;
	if (source.get() != NULL ) {
		Container* ctner = dynamic_cast<Container*>(source.get());
		if(ctner != NULL)
			ctner->layoutContainer();
	}
	if (destination.get() != NULL)  {
		Container* ctner = dynamic_cast<Container*>(destination.get());
		if(ctner != NULL)
			ctner->layoutContainer();
	}
}

shared_ptr<Component> Transition::getDestination()
{
	  return destination;
}

shared_ptr<Component> Transition::getSource()
{
	return source;
}

void Transition::cleanup()
{
	source.reset();
	destination.reset();
}

shared_ptr<Transition> Transition::copy()
{
	return copy(false);
}

shared_ptr<Transition> Transition::copy( bool reverse )
{
	 return copy();
}

void Transition::cleanSource()
{
	 source.reset();
}

void Transition::initTransition()
{

}
__GUI_END_NAMESPACE
