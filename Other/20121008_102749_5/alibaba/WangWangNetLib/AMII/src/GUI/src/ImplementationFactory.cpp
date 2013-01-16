
#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
shared_ptr<ImplementationFactory> ImplementationFactory::instance = new ImplementationFactory();
bool ImplementationFactory::useWin32Cancas = true;
ImplementationFactory::ImplementationFactory()
{

}

void ImplementationFactory::setGameCanvasFlag(bool b)
{
	useWin32Cancas = b;
}

shared_ptr<ImplementationFactory> ImplementationFactory::getInstance()
{
	if (instance.get() == NULL)
	{
		instance = new ImplementationFactory();
	}
	return instance;
}

void ImplementationFactory::setImplementationFactory(shared_ptr<ImplementationFactory> i)
{
	instance = i;
}

shared_ptr<LWUITImplementation> ImplementationFactory::createImplementation()
{
	if (useWin32Cancas)
	{
		return new AliImplementation();
	}
	else
	{
		return new AliImplementation();
	}
}

void ImplementationFactory::deinitialize()
{
	instance.reset();
}
__GUI_END_NAMESPACE
