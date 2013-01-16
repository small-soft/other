#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
bool CommonTransitions::defaultLinearMotion = false;
CommonTransitions::CommonTransitions( int type )
{
	 transitionType = type;
	 linearMotion = defaultLinearMotion;
	 forward = false;
	 drawDialogMenu = false;
	 firstFinished = false;

	 slideType = 0;
	 speed = 0;
	 position = 0;
//	 transitionType = 0;
}
CommonTransitions::~CommonTransitions(void)
{
}

shared_ptr<CommonTransitions> CommonTransitions::createEmpty()
{
	shared_ptr<CommonTransitions> t = new CommonTransitions(TYPE_EMPTY);
	return t;
}

shared_ptr<CommonTransitions> CommonTransitions::createSlide( int type, bool forward, int duration, bool drawDialogMenu )
{
	shared_ptr<CommonTransitions> t = new CommonTransitions(TYPE_SLIDE);
	t->slideType = type;
	t->forward = forward;
	if ((type==SLIDE_HORIZONTAL) && (UIManager::getInstance()->getLookAndFeel()->isRTL())) {
		t->forward=!t->forward;
	}
	t->speed = duration;
	t->position = 0;
	t->drawDialogMenu = drawDialogMenu;
	return t;

}

shared_ptr<CommonTransitions> CommonTransitions::createFade(int duration)
{
	shared_ptr<CommonTransitions> t = new CommonTransitions(TYPE_FADE);
	t->speed = duration;
	return t;
}


void CommonTransitions::initTransition()
{
	firstFinished = false;
	if(transitionType == TYPE_EMPTY) {
		return;
	}

	shared_ptr<Component> source = getSource();
	shared_ptr<Component> destination = getDestination();
	position = 0;
	int w = source->getWidth();
	int h = source->getHeight();

	// a transition might occur with illegal source or destination values (common with 
	// improper replace() calls, this may still be valid and shouldn't fail
	if(w <= 0 || h <= 0) {
		return;
	}
	if (buffer.get() == NULL) {
		buffer = Image::createImage(w, h);
	} else {
		// this might happen when screen orientation changes or a MIDlet moves
		// to an external screen
		if(buffer->getWidth() != w || buffer->getHeight() != h) {
			buffer = Image::createImage(w, h);
			rgbBuffer.reset();

			// slide motion might need resetting since screen size is different
			motion.reset();
		}
	}
	if(transitionType == TYPE_FADE) {
		if(linearMotion) {
			motion = Motion::createLinearMotion(0, 256, speed);
		} else {
			motion = Motion::createSplineMotion(0, 256, speed);
		}
		motion->start();

		shared_ptr<Graphics> g = buffer->getGraphics();
		g->translate(-source->getAbsoluteX(), -source->getAbsoluteY());

		if(getSource()->getParent().get() != NULL){
			getSource()->getComponentForm()->paintComponent(g);
		}
		//getSource().paintBackgrounds(g);
		g->setClip(0, 0, buffer->getWidth()+source->getAbsoluteX(), buffer->getHeight()+source->getAbsoluteY());
		paint(g, getDestination(), 0, 0);
		if(g->isAlphaSupported()) {
			secondaryBuffer = buffer;
			buffer = Image::createImage(w, h);
		} else {
			rgbBuffer = new RGBImage(buffer->getRGBCached(), buffer->getWidth(), buffer->getHeight());
		}

		paint(g, getSource(), 0, 0);
		g->translate(source->getAbsoluteX(), source->getAbsoluteY());

	} else {
		if (transitionType == TYPE_SLIDE) {
			int dest;
			int startOffset = 0;
			if (slideType == SLIDE_HORIZONTAL) {
				dest = w;
				shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(destination);
				if(dlg.get() != NULL) {
					startOffset = w - dlg->getContentPane()->getWidth();
					if(forward) {
						startOffset -= dlg->getContentPane()->getStyle()->getMargin(destination->isRTL(), Component::LEFT);
					} else {
						startOffset -= dlg->getContentPane()->getStyle()->getMargin(destination->isRTL(), Component::RIGHT);
					}
				} else {
					shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(source);
					if(dlg.get() != NULL) {
						dest = dlg->getContentPane()->getWidth();
						if(forward) {
							dest += dlg->getContentPane()->getStyle()->getMargin(source->isRTL(), Component::LEFT);
						} else {
							dest += dlg->getContentPane()->getStyle()->getMargin(source->isRTL(), Component::RIGHT);
						}
					} 
				}
			} else {
				dest = h;
				shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(destination);
				if(dlg.get() != NULL) {
					startOffset = h - dlg->getContentPane()->getHeight() -
						dlg->getTitleComponent()->getHeight();
					if(forward) {
						startOffset -= dlg->getContentPane()->getStyle()->getMargin(false, Component::BOTTOM);
					} else {
						startOffset -= dlg->getContentPane()->getStyle()->getMargin(false, Component::TOP);
						startOffset -= dlg->getTitleStyle()->getMargin(false, Component::TOP);
						if(!drawDialogMenu && dlg->getCommandCount() > 0) {
							shared_ptr<Container> p = dlg->getSoftButton(0)->getParent();
							if(p.get() != NULL) {
								startOffset -= p->getHeight();
							}
						}
					}
				} else {
					shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(source);
					if(dlg.get() != NULL) {
						dest = dlg->getContentPane()->getHeight() +
							dlg->getTitleComponent()->getHeight();
						if(forward) {
							dest += dlg->getContentPane()->getStyle()->getMargin(false, Component::BOTTOM);
						} else {
							dest += dlg->getContentPane()->getStyle()->getMargin(false, Component::TOP);
							dest += dlg->getTitleStyle()->getMargin(false, Component::TOP);
							if(dlg->getCommandCount() > 0) {
								shared_ptr<Container> p =dlg->getSoftButton(0)->getParent();
								if(p.get() != NULL) {
									dest += p->getHeight();
								}
							}
						}
					} 
				}
			}

			if(linearMotion) {
				motion = Motion::createLinearMotion(startOffset, dest, speed);
			} else {
				motion = Motion::createSplineMotion(startOffset, dest, speed);
			}

			// make sure the destination is painted fully at least once 
			// we must use a full buffer otherwise the clipping will take effect
			shared_ptr<Graphics> g = buffer->getGraphics();

			// If this is a dialog render the tinted frame once since 
			// tinting is expensive
			shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(getSource());
			if(dlg.get() != NULL) {
				paint(g, getDestination(), 0, 0);
			} else {
				shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(getDestination());
				if(dlg.get() != NULL) {
					paint(g, getSource(), 0, 0);
				} else {
					paint(g, source, -source->getAbsoluteX(), -source->getAbsoluteY());
				}
			}
			motion->start();
		}
	}

}

bool CommonTransitions::animate()
{
	if(motion.get() == NULL) {
		return false;
	}
	position = motion->getValue();

	// after the motion finished we need to paint one last time otherwise
	// there will be a "bump" in sliding
	if(firstFinished) {
		return false;
	}
	bool finished = motion->isFinished();
	if(finished) {
		if(!firstFinished) {
			firstFinished = true;
		}
	}
	return true;

}

void CommonTransitions::paint( shared_ptr<Graphics> g )
{
	switch (transitionType) {
				case TYPE_SLIDE:
					// if this is an up or down slide
					if (slideType == SLIDE_HORIZONTAL) {
						paintSlideAtPosition(g, position, 0);
					} else {
						paintSlideAtPosition(g, 0, position);
					}
					return;
				case TYPE_FADE:
					paintAlpha(g);
					return;
	}
}

void CommonTransitions::paint( shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y )
{	
//	g = Display::getInstance()->getImplementation()->getLWUITGraphics();
	int cx = g->getClipX();
	int cy = g->getClipY();
	int cw = g->getClipWidth();
	int ch = g->getClipHeight();
	shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(cmp);
	if(dlg.get() != NULL) {
		if(transitionType != TYPE_FADE) {
			shared_ptr<Dialog> dlgSrc = dynamic_pointer_cast<Dialog>(getSource());
			shared_ptr<Dialog> dlgDest = dynamic_pointer_cast<Dialog>(getDestination());
			if(!(dlgSrc.get() != NULL && dlgDest.get() != NULL &&  cmp == getDestination())) {
					shared_ptr<Painter> p = cmp->getStyle()->getBgPainter();
					shared_ptr<Painter> nullPainter;
					cmp->getStyle()->setBgPainter(nullPainter);
					g->translate(x, y);
		
					g->setClip(0, 0, cmp->getWidth(), cmp->getHeight());
					dlg->getTitleComponent()->paintComponent(g, false);
					g->setClip(0, 0, cmp->getWidth(), cmp->getHeight());
					dlg->getContentPane()->paintComponent(g, false);
					g->translate(-x, -y);
					if(drawDialogMenu && dlg->getCommandCount() > 0) {
						shared_ptr<Component> menuBar = dlg->getSoftButton(0)->getParent();
						if(menuBar.get() != NULL) {
							g->setClip(0, 0, cmp->getWidth(), cmp->getHeight());
							menuBar->paintComponent(g, false);
						}
					}

					g->setClip(cx, cy, cw, ch);
					cmp->getStyle()->setBgPainter(p);
					return;
			}
		} 
		cmp->paintComponent(g, false);
		return;
	}
	//g.clipRect(cmp.getAbsoluteX(), cmp.getAbsoluteY(), cmp.getWidth(), cmp.getHeight());
	g->translate(x, y);
	//g.clipRect(cmp.getAbsoluteX(), cmp.getAbsoluteY(), cmp.getWidth(), cmp.getHeight());
	cmp->paintComponent(g, false);
	g->translate(-x, -y);

	g->setClip(cx, cy, cw, ch);

}
void CommonTransitions::paintAlpha( shared_ptr<Graphics> graphics )
{
	// this will always be invoked on the EDT so there is no race condition risk
	if(rgbBuffer.get() != NULL || secondaryBuffer.get() != NULL) {
		shared_ptr<Component> src = getSource();
		int w = src->getWidth();
		int h = src->getHeight();
		int position = this->position;
		if (position > 255) {
			position = 255;
		} else {
			if (position < 0) {
				position = 0;
			}
		}
		if(secondaryBuffer.get() != NULL) {
			shared_ptr<Component> dest = getDestination();                
			int x = dest->getAbsoluteX();
			int y = dest->getAbsoluteY();

			graphics->drawImage(buffer, x, y);
			graphics->setAlpha(position);
			graphics->drawImage(secondaryBuffer, x, y);
			graphics->setAlpha(0xff);
		} else {
			int alpha = position << 24;
			int size = w * h;
			shared_ptr<VectorArray<int>> bufferArray = rgbBuffer->getRGB();
			for (int iter = 0 ; iter < size ; iter++) {
				(*bufferArray)[iter] = (((*bufferArray)[iter] & 0xFFFFFF) | alpha);
			}
			shared_ptr<Component>  dest = getDestination();                
			int x = dest->getAbsoluteX();
			int y = dest->getAbsoluteY();
			graphics->drawImage(buffer, x, y);
			graphics->drawImage(rgbBuffer, x, y);
		}
	} 

}
shared_ptr<Transition> CommonTransitions::copy( bool reverse )
{
	shared_ptr<CommonTransitions> retVal;
	if(transitionType == TYPE_FADE)
	{
		retVal = CommonTransitions::createFade(speed);
	}
	else if(transitionType == TYPE_SLIDE)
	{
		bool fwd=forward;

		// prevent double reversing of forward due to bidi when copying a transition
		if ((slideType==SLIDE_HORIZONTAL) && (UIManager::getInstance()->getLookAndFeel()->isRTL()))
		{
			fwd=!fwd;
		}
		if(reverse)
		{
			retVal = CommonTransitions::createSlide(slideType, !fwd, speed, drawDialogMenu);
		} else {
			retVal = CommonTransitions::createSlide(slideType, fwd, speed, drawDialogMenu);
		}
	}
	else if(transitionType == TYPE_EMPTY)
	{
		retVal = CommonTransitions::createEmpty();
	}
	retVal->linearMotion = linearMotion;
	return retVal;
}

void CommonTransitions::cleanup()
{
	Transition::cleanup();
	buffer.reset();
	rgbBuffer.reset();
	secondaryBuffer.reset();
}

void CommonTransitions::paintSlideAtPosition( shared_ptr<Graphics> g, int slideX, int slideY )
{
	shared_ptr<Component> source = getSource();

	// if this is the first form we can't do a slide transition since we have no source form
	if (source.get() == NULL) { 
		return;           
	}

	shared_ptr<Component> dest = getDestination();                
	int w = source->getWidth();
	int h = source->getHeight();

	if (slideType == SLIDE_HORIZONTAL) {
		h = 0;
	} else {
		w = 0;
	}

	if(forward) {
		w = -w;
		h = -h;
	} else {
		slideX = -slideX;
		slideY = -slideY;
	}
	g->setClip(source->getAbsoluteX()+source->getScrollX(), source->getAbsoluteY()+source->getScrollY(), source->getWidth(), source->getHeight());

	// dialog animation is slightly different... 
	shared_ptr<Dialog> dlg = dynamic_pointer_cast<Dialog>(source);
	if(dlg.get() != NULL) {
		g->BitBlt(buffer, 0, 0);
		paint(g, source, -slideX, -slideY);
		return;
	} 
	dlg = dynamic_pointer_cast<Dialog>(dest);
	if(dlg.get() != NULL) {
		g->BitBlt(buffer, 0, 0);
		paint(g, dest, -slideX - w, -slideY - h);
		return;
	} 

	//g.setClip(source.getAbsoluteX(), source.getAbsoluteY(), source.getWidth(), source.getHeight());

	//g.clipRect(dest.getAbsoluteX(), dest.getAbsoluteY(), source.getWidth(), source.getHeight());
	if(source->getParent().get() != NULL){
		source->paintBackgrounds(g);
		paint(g, source, slideX , slideY );
	}else{
		g->drawImage(buffer, slideX, slideY);        
	}
	paint(g, dest, slideX + w, slideY + h);

}

shared_ptr<Motion> CommonTransitions::getMotion()
{
	 return motion;
}

void CommonTransitions::setMotion( shared_ptr<Motion> motion )
{
	   this->motion = motion;
}

bool CommonTransitions::isLinearMotion()
{
	return linearMotion;
}

void CommonTransitions::setLinearMotion( bool linearMotion )
{
	 this->linearMotion = linearMotion;
}

bool CommonTransitions::isDefaultLinearMotion()
{
	 return defaultLinearMotion;
}

void CommonTransitions::setDefaultLinearMotion( bool aDefaultLinearMotion )
{
	 defaultLinearMotion = aDefaultLinearMotion;
}
__GUI_END_NAMESPACE
