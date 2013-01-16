#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
BGPainter::BGPainter( shared_ptr<Form> parent, shared_ptr<Painter> p )
{
	ignorCoordinates = false;
	this->painter = p;
	this->parent = parent;
}

BGPainter::BGPainter( shared_ptr<Component> componet )
:componet(componet)
{
	ignorCoordinates = false;
}
BGPainter::~BGPainter(void)
{
}

void BGPainter::setBgRect( shared_ptr<Rectangle> rect )
{
	this->bgRect = rect;
}

void BGPainter::setIgnorCoordinates( bool ignorCoordinates )
{
	this->ignorCoordinates = ignorCoordinates;
}

void BGPainter::setPreviousForm( shared_ptr<Form> previous )
{
	 previousTint = previous;
}

shared_ptr<Form> BGPainter::getPreviousForm()
{
	return previousTint;
}

void BGPainter::setParent( shared_ptr<Form> parent )
{
	this->parent = parent;
}

void BGPainter::paint( shared_ptr<Graphics> g, shared_ptr<Rectangle> rect )
{
	if (painter.get() != NULL) {
		//modified by jiajing
		if (previousTint.get() != NULL) {
			if(bgRect.get()!= NULL){
				g->setClip(bgRect->getX(), bgRect->getY(), bgRect->getSize()->getWidth(), bgRect->getSize()->getHeight());    

			}
			previousTint->paint(g); 
			previousTint.reset();
		}
	} else {
		shared_ptr<Style> s = componet->getStyle();
		int x = rect->getX();
		int y = rect->getY();
		int width = rect->getSize()->getWidth();
		int height = rect->getSize()->getHeight();
		if (width <= 0 || height <= 0) {
			return;
		}
		shared_ptr<Image> bgImage = s->getBgImage();
		if (bgImage.get() == NULL) {
			if(s->getBackgroundType() >= Style::BACKGROUND_GRADIENT_LINEAR_VERTICAL) {
				drawGradientBackground(s, g, x, y, width, height);
				return;
			}
			int colo = s->getBgColor();
			g->setColor(colo);
		//	g->setBgColor(colo);
			g->fillRect(x, y, width, height, s->getBgTransparency());
		} else {
		//	printf("bgImage 1:%d\n",System::currentTimeMillis());
			int iW = bgImage->getWidth();
			int iH = bgImage->getHeight();
			int type = s->getBackgroundType();
			switch (type) {
						case Style::BACKGROUND_IMAGE_SCALED:
							if (iW != width || iH != height) {
								bgImage = bgImage->scaled(width, height);
								s->setBgImage(bgImage, true);
							}
							g->drawImage(s->getBgImage(), x, y);
							break;
						case Style::BACKGROUND_IMAGE_TILE_BOTH:
							for (int xPos = 0; xPos <= width; xPos += iW) {
								for (int yPos = 0; yPos <= height; yPos += iH) {
									g->drawImage(s->getBgImage(), x + xPos, y + yPos);
								}
							}
							break;
						case Style::BACKGROUND_IMAGE_TILE_HORIZONTAL:
							for (int xPos = 0; xPos <= width; xPos += iW) {
								g->drawImage(s->getBgImage(), x + xPos, y);
							}
							break;
						case Style::BACKGROUND_IMAGE_TILE_VERTICAL:
							for (int yPos = 0; yPos <= height; yPos += iH) {
								g->drawImage(s->getBgImage(), x, y + yPos);
							}
							break;
						case Style::BACKGROUND_IMAGE_ALIGNED:
							switch (s->getBackgroundAlignment()) {
						case Style::BACKGROUND_IMAGE_ALIGN_BOTTOM:
							g->drawImage(s->getBgImage(), x + width - iW, y + (height - iH));
							break;
						case Style::BACKGROUND_IMAGE_ALIGN_TOP:
							g->drawImage(s->getBgImage(), x + width - iW, y);
							break;
						case Style::BACKGROUND_IMAGE_ALIGN_LEFT:
							g->drawImage(s->getBgImage(), x, y + (height / 2 - iH / 2));
							break;
						case Style::BACKGROUND_IMAGE_ALIGN_RIGHT:
							g->drawImage(s->getBgImage(), x + width - iW, y + (height / 2 - iH / 2));
							break;
						case Style::BACKGROUND_IMAGE_ALIGN_CENTER:
							g->drawImage(s->getBgImage(), x + (width / 2 - iW / 2), y + (height / 2 - iH / 2));
							break;
							}
						default:
						//	g->drawImage(s->getBgImage(), x, y + (height / 2 - iH / 2));
							break;
			}
		//	printf("bgImage 2:%d\n",System::currentTimeMillis());
		}
	}

}

void BGPainter::drawGradientBackground( shared_ptr<Style> s, shared_ptr<Graphics> g, int x, int y, int width, int height )
{
	switch (s->getBackgroundType()) {
				case Style::BACKGROUND_GRADIENT_LINEAR_HORIZONTAL:
					g->fillLinearGradient(s->getBackgroundGradientStartColor(), s->getBackgroundGradientEndColor(),
						x, y, width, height, true);
					return;
				case Style::BACKGROUND_GRADIENT_LINEAR_VERTICAL:
					g->fillLinearGradient(s->getBackgroundGradientStartColor(), s->getBackgroundGradientEndColor(),
						x, y, width, height, false);
					return;
				case Style::BACKGROUND_GRADIENT_RADIAL:
					g->fillRectRadialGradient(s->getBackgroundGradientStartColor(), s->getBackgroundGradientEndColor(),
						x, y, width, height, s->getBackgroundGradientRelativeX(), s->getBackgroundGradientRelativeY(),
						s->getBackgroundGradientRelativeSize());
					return;
	}
	g->setColor(s->getBgColor());
	g->fillRect(x, y, width, height, s->getBgTransparency());
}
__GUI_END_NAMESPACE
