#ifndef __IMPLEMENTATION_FACTORY_H__
#define __IMPLEMENTATION_FACTORY_H__

#include "inc/LWUITImplementation.h"
#include "inc/Config.h"
class NativeImage;
class NativeFont;
class NativeGraphics;
__GUI_BEGIN_NAMESPACE
class ImplementationFactory
{
private:
	static shared_ptr<ImplementationFactory> instance;
	static bool useWin32Cancas;
	
protected:
	ImplementationFactory();

public:
	static void deinitialize();
	static void setGameCanvasFlag(bool b);
	static shared_ptr<ImplementationFactory> getInstance();
	static void setImplementationFactory(shared_ptr<ImplementationFactory> i);
	
public:
	shared_ptr<LWUITImplementation> createImplementation();
};


__GUI_END_NAMESPACE

#endif
