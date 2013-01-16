#ifndef __GUI_ANIMATION_H__
#define __GUI_ANIMATION_H__

#include "inc/Config.h"
#include "inc/Object.h"
__GUI_BEGIN_NAMESPACE
class Graphics;


class Animation //: public CRttiBase
{
	AM_DECLARE_DYNAMIC(Animation)
	
public:
	  /**
     * Allows the animation to reduce "repaint" calls when it returns false. It is
     * called once for every frame. Frames are defined by the {@link com.sun.lwuit.Display} class.
     * 
     * @return true if a repaint is desired or false if no repaint is necessary
     */
     virtual bool animate() = 0;

    /**
     * Draws the animation, within a component the standard paint method would be
     * invoked since it bares the exact same signature.
     * 
     * @param g graphics context
     */
     virtual void paint(shared_ptr<Graphics> g) = 0;

	 virtual ~Animation() {}
};

__GUI_END_NAMESPACE

#endif
