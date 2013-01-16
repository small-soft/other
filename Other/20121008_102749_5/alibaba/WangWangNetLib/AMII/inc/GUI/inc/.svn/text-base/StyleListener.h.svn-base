#ifndef __STYLE_LISTENER_H__
#define __STYLE_LISTENER_H__

#include "inc/String.h"

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Style;
class StyleListener
{
public:
	 /**
     * Invoked to indicate a change in a propertyName of a Style
     * 
     * @param propertyName the property name that was changed
     * @param source The changed Style object
     */
    virtual void styleChanged(shared_ptr<String> propertyName, shared_ptr<Style> source) = 0;
	virtual ~StyleListener() {}
    
};
__GUI_END_NAMESPACE

#endif
