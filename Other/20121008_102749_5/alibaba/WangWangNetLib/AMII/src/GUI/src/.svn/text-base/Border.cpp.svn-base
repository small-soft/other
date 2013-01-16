#include "AMGui.h"


__GUI_BEGIN_NAMESPACE
shared_ptr<Border> Border::defaultBorder;// = Border::createEtchedRaised(0x020202, 0xBBBBBB);
shared_ptr<Border> Border::empty;// = new Border();
Border::Border(void):outline(true),themeColors(false)
{
	type = 0;
	colorA = 0;
	colorB = 0;
	colorC = 0;
	colorD = 0;
	thickness = 0;
	arcWidth = 0;
	arcHeight = 0;
}

Border::~Border(void)
{
}

shared_ptr<Border> Border::getEmpty()
{	
	if(empty.get() == NULL)
	{
		empty = new Border(); 
	}
	return empty;
}

shared_ptr<Border> Border::createEmpty()
{
	 return new Border();
}

shared_ptr<Border> Border::createImageBorder(shared_ptr<Image> top, shared_ptr<Image>bottom, shared_ptr<Image> left, shared_ptr<Image> right,shared_ptr<Image>topLeft, shared_ptr<Image>topRight,
											 shared_ptr<Image> bottomLeft, shared_ptr<Image> bottomRight, shared_ptr<Image> background)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_IMAGE;
	b->images = new VectorArray<shared_ptr<Image> >(9);

	(*b->images)[0] = top;
	(*b->images)[1] = bottom;
	(*b->images)[2] = left;
	(*b->images)[3] = right;
	(*b->images)[4] = topLeft;
	(*b->images)[5] = topRight;
	(*b->images)[6] = bottomLeft;
	(*b->images)[7] = bottomRight;
	(*b->images)[8] = background;
	return b;
}

shared_ptr<Border> Border::createImageBorder( shared_ptr<Image> top, shared_ptr<Image> topLeft,shared_ptr<Image> background )
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_IMAGE;
	b->images = new VectorArray<shared_ptr<Image> >(9);

	(*b->images)[0] = top;
	(*b->images)[1] = top->rotate(180);
	(*b->images)[2] = top->rotate(270);
	(*b->images)[3] = top->rotate(90);
	(*b->images)[4] = topLeft;
	(*b->images)[5] = topLeft->rotate(90);
	(*b->images)[6] = topLeft->rotate(270);
	(*b->images)[7] = topLeft->rotate(180);
	(*b->images)[8] = background;
	return b;
}

shared_ptr<Border> Border::createLineBorder( int thickness )
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_LINE;
	b->themeColors = true;
	b->thickness = thickness;
	return b;
}

shared_ptr<Border> Border::createLineBorder(int thickness, int color)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_LINE;
	b->themeColors = false;
	b->thickness = thickness;
	b->colorA = color;
	return b;
}

shared_ptr<Border> Border::createRoundBorder(int arcWidth, int arcHeight)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ROUNDED;
	b->themeColors = true;
	b->arcHeight = arcHeight;
	b->arcWidth = arcWidth;
	return b;
}

shared_ptr<Border> Border::createRoundBorder(int arcWidth, int arcHeight, bool outline)
{
	shared_ptr<Border> b = createRoundBorder(arcWidth, arcHeight);
	b->outline = outline;
	return b;
}

shared_ptr<Border> Border::createRoundBorder(int arcWidth, int arcHeight, int color)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ROUNDED;
	b->themeColors = false;
	b->colorA = color;
	b->arcHeight = arcHeight;
	b->arcWidth = arcWidth;
	return b;
}

shared_ptr<Border> Border::createRoundBorder(int arcWidth, int arcHeight, int color, bool outline)
{
	shared_ptr<Border> b = createRoundBorder(arcWidth, arcHeight, color);
	b->outline = outline;
	return b;
}

shared_ptr<Border> Border::createEtchedLowered()
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ETCHED_LOWERED;
	b->themeColors = true;
	return b;
}

shared_ptr<Border> Border::createEtchedLowered(int highlight, int shadow)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ETCHED_LOWERED;
	b->themeColors = false;
	b->colorA = shadow;
	b->colorB = highlight;
	return b;
}

shared_ptr<Border> Border::createEtchedRaised()
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ETCHED_RAISED;
	b->themeColors = true;
	return b;
}
shared_ptr<Border> Border::createEtchedRaised(int highlight, int shadow)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_ETCHED_RAISED;
	b->themeColors = false;
	b->colorA = highlight;
	b->colorB = shadow;
	return b;
}

bool Border::isBackgroundPainter()
{
	return type == TYPE_ROUNDED || type == TYPE_ROUNDED_PRESSED || (type == TYPE_IMAGE);
}

shared_ptr<Border> Border::createBevelLowered()
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_BEVEL_LOWERED;
	b->themeColors = true;
	return b;
}

shared_ptr<Border> Border::createBevelLowered(int highlightOuter, int highlightInner, int shadowOuter, int shadowInner)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_BEVEL_LOWERED;
	b->themeColors = false;
	b->colorA = highlightOuter;
	b->colorB = highlightInner;
	b->colorC = shadowOuter;
	b->colorD = shadowInner;
	return b;
}
shared_ptr<Border> Border::createBevelRaised()
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_BEVEL_RAISED;
	b->themeColors = true;
	return b;
}
shared_ptr<Border> Border::createBevelRaised(int highlightOuter, int highlightInner, int shadowOuter, int shadowInner)
{
	shared_ptr<Border> b = new Border();
	b->type = TYPE_BEVEL_RAISED;
	b->themeColors = false;
	b->colorA = highlightOuter;
	b->colorB = highlightInner;
	b->colorC = shadowOuter;
	b->colorD = shadowInner;
	return b;
}
void Border::setPressedInstance( shared_ptr<Border> pressed)
{
	pressedBorder = pressed;
}

void Border::setFocusedInstance( shared_ptr<Border> focused)
{
	focusBorder = focused;
}
shared_ptr<Border> Border::getFocusedInstance()
{
	if(focusBorder.get() != NULL) 
	{
		return focusBorder;
	}
	return this->shared_from_this();
}
shared_ptr<Border> Border::getPressedInstance()
{
	if(pressedBorder.get() != NULL) 
	{
		return  pressedBorder;
	}
	return this->shared_from_this();;
}

shared_ptr<Border> Border::createPressedVersion()
{
	shared_ptr<Border> res;
	if(pressedBorder.get() != NULL) 
	{
		return pressedBorder;
	}
	switch(type) 
	{
	case TYPE_LINE:
		res = createLineBorder(thickness + 1, colorA);
	case TYPE_ETCHED_LOWERED: 
		{
			res = createEtchedRaised(colorA, colorB);
			res->themeColors = themeColors;
			break;
		}
	case TYPE_ETCHED_RAISED: 
		{
			res = createEtchedLowered(colorA, colorB);
			res->themeColors = themeColors;
			break;
		}
	case TYPE_BEVEL_RAISED: 
		{
			res = createBevelLowered(colorA, colorB, colorC, colorD);
			res->themeColors = themeColors;
			break;
		}
	case TYPE_BEVEL_LOWERED: 
		{
			res = createBevelRaised(colorA, colorB, colorC, colorD);
			res->themeColors = themeColors;
			break;
		}
	case TYPE_ROUNDED: 
		{
			res = createRoundBorder(arcWidth, arcHeight, colorA);
			res->themeColors = themeColors;
			res->type = TYPE_ROUNDED_PRESSED;
			break;
		}
	case TYPE_ROUNDED_PRESSED: 
		{
			res = createRoundBorder(arcWidth, arcHeight, colorA);
			res->themeColors = themeColors;
			break;
		}
	}
	if(res.get() == NULL){
			res = this->shared_from_this();
	}
	return res;
}


void Border::paintBorderBackground(shared_ptr<Graphics> g, shared_ptr<Component> c)
{
	int originalColor = g->getColor();
	int x = c->getX();
	int y = c->getY();
	int width = c->getWidth();
	int height = c->getHeight();
	switch(type) 
	{
	case TYPE_ROUNDED_PRESSED:
		{
			x++;
			y++;
			width -= 2;
			height -= 2;
		}
	case TYPE_ROUNDED:
		{
			width--;
			height--;
			// rounded is also responsible for drawing the background
			shared_ptr<Style> s = c->getStyle();
			shared_ptr<Image> bgImage = s->getBgImage();
			if((bgImage.get() != NULL && s->getBackgroundType() == Style::BACKGROUND_IMAGE_SCALED) || s->getBackgroundType() > 1) 
			{
				shared_ptr<Image> i;
				// we need to draw a background image!
				i = Image::createImage(width, height);
				shared_ptr<Graphics> imageG = i->getGraphics();
				imageG->setColor(0);
				imageG->fillRoundRect(0, 0, width, height, arcWidth, arcHeight);
				shared_ptr<VectorArray<int> > rgb = i->getRGBCached();
				int transColor = (*rgb)[0];
				shared_ptr<VectorArray<int> > imageRGB;
				if(s->getBackgroundType() == Style::BACKGROUND_IMAGE_SCALED) 
				{
					imageRGB = s->getBgImage()->scaled(width, height)->getRGBCached();
				} 
				else
				{
					shared_ptr<Image> bgPaint = Image::createImage(width, height);
					shared_ptr<Painter> p = s->getBgPainter();

					// might occur during temporary conditions in the theme switching
					if(p.get() == NULL) 
					{
						return;
					}
					shared_ptr<Rectangle> rect = new Rectangle(0, 0, width, height);
					p->paint(bgPaint->getGraphics(), rect);
					imageRGB = bgPaint->getRGB();
				}
				for(int iter = 0 ; iter < rgb->size() ; iter++) 
				{
					if((*rgb)[iter] == transColor) 
					{
						(*imageRGB)[iter] = 0;
					}
				}
				i = Image::createImageFromRGBWithRect(imageRGB, width, height);
				g->drawImage(i, x, y);
			} 
			else
			{
				int foreground = g->getColor();
				g->setColor(s->getBgColor());

				// Its opaque much easier job!
				if(s->getBgTransparency() == ((unsigned char)0xff)) 
				{
					g->fillRoundRect(x, y , width, height, arcWidth, arcHeight);
				}
				else 
				{
					if(g->isAlphaSupported()) 
					{
						int alpha = g->getAlpha();
						g->setAlpha(s->getBgTransparency() & 0xff);
						g->fillRoundRect(x, y , width, height, arcWidth, arcHeight);
						g->setAlpha(alpha);
					}
					else
					{
						// if its transparent we don't need to do anything, if its
						// translucent... well....
						if(s->getBgTransparency() != 0) 
						{
							shared_ptr<Image> i = Image::createImage(width, height);
							shared_ptr<VectorArray<int> > imageRgb;
							if(g->getColor() != 0xffffff) 
							{
								shared_ptr<Graphics> imageG = i->getGraphics();
								imageG->setColor(g->getColor());
								imageG->fillRoundRect(0, 0 , width, height, arcWidth, arcHeight);
								imageRgb = i->getRGBCached();
							}
							else 
							{
								// background color is white we need to remove a different color
								// black is the only other "reliable" color on the device
								shared_ptr<Graphics> imageG = i->getGraphics();
								imageG->setColor(0);
								imageG->fillRect(0, 0, width, height);
								imageG->setColor(g->getColor());
								imageG->fillRoundRect(0, 0 , width, height, arcWidth, arcHeight);
								imageRgb = i->getRGBCached();
							}
							int removeColor = (*imageRgb)[0];
							int size = width * height;
							int alphaInt = ((s->getBgTransparency() & 0xff) << 24) & 0xff000000;
							for(int iter = 0 ; iter < size ; iter++) 
							{
								if(removeColor == (*imageRgb)[iter]) 
								{
									(*imageRgb)[iter] = 0;
									continue;
								}
								if(((*imageRgb)[iter] & 0xff000000) != 0) 
								{
									(*imageRgb)[iter] = ((*imageRgb)[iter] & 0xffffff) | alphaInt;
								}   
							}
							shared_ptr<RGBImage> rgbImage = new RGBImage(imageRgb, width, height);
							g->drawImage(dynamic_pointer_cast<Image>(rgbImage), x, y);
						} 
					}
				}
				g->setColor(foreground);
			}
			break;
		}
	case TYPE_IMAGE:
		{
			int clipX = g->getClipX();
			int clipY = g->getClipY();
			int clipWidth = g->getClipWidth();
			int clipHeight = g->getClipHeight();
			shared_ptr<Image> topLeft = (*images)[4]; 
			shared_ptr<Image> topRight = (*images)[5];
			shared_ptr<Image> bottomLeft = (*images)[6];
			shared_ptr<Image> center = (*images)[8];
			x += topLeft->getWidth();
			y += topLeft->getHeight();
			height -= (topLeft->getHeight() + bottomLeft->getHeight());
			width -= (topLeft->getWidth() + topRight->getWidth());
			g->clipRect(x, y, width, height);
			if(center.get() != NULL)
			{
				int centerWidth = center->getWidth();
				int centerHeight = center->getHeight();
				for(int xCount = x ; xCount < x + width ; xCount += centerWidth) 
				{
					for(int yCount = y ; yCount < y + height ; yCount += centerHeight) 
					{
						g->drawImage(center, xCount, yCount);
					}
				}
			}
			shared_ptr<Image> top = (*images)[0];  shared_ptr<Image> bottom = (*images)[1];
			shared_ptr<Image> left = (*images)[2]; shared_ptr<Image> right = (*images)[3];
			shared_ptr<Image> bottomRight = (*images)[7];

			g->setClip(clipX, clipY, clipWidth, clipHeight);

			x = c->getX();
			y = c->getY();
			width = c->getWidth();
			height = c->getHeight();

			g->drawImage(topLeft, x, y);
			g->drawImage(bottomLeft, x, y + height - bottomLeft->getHeight());
			g->drawImage(topRight, x + width - topRight->getWidth(), y);
			g->drawImage(bottomRight, x + width - bottomRight->getWidth(), y + height - bottomRight->getHeight());

			g->setClip(clipX, clipY, clipWidth, clipHeight);
			drawImageBorderLine(g, topLeft, topRight, top, x, y, width);
			g->setClip(clipX, clipY, clipWidth, clipHeight);
			drawImageBorderLine(g, bottomLeft, bottomRight, bottom, x, y + height - bottom->getHeight(), width);
			g->setClip(clipX, clipY, clipWidth, clipHeight);
			drawImageBorderColumn(g, topLeft, bottomLeft, left, x, y, height);
			g->setClip(clipX, clipY, clipWidth, clipHeight);
			drawImageBorderColumn(g, topRight, bottomRight, right, x + width - right->getWidth(), y, height);

			g->setClip(clipX, clipY, clipWidth, clipHeight);
			break;
		}
	}
	g->setColor(originalColor);
}

void Border::paint(shared_ptr<Graphics> g, shared_ptr<Component> c)
{
	int originalColor = g->getColor();
	int x = c->getX();
	int y = c->getY();
	int width = c->getWidth();
	int height = c->getHeight();
	if(!themeColors) 
	{
		g->setColor(colorA);
	}
	switch(type) 
	{
	case TYPE_LINE:
		width--;
		height--;
		for(int iter = 0 ; iter < thickness ; iter++) 
		{
			g->drawRect(x + iter, y + iter, width, height);
			width -= 2; 
			height -= 2;
		}
		break;
	case TYPE_ROUNDED_PRESSED:
		x++;
		y++;
		width -= 2;
		height -= 2;
	case TYPE_ROUNDED:
		width--;
		height--;

		if(outline) 
		{
			g->drawRoundRect(x, y , width, height, arcWidth, arcHeight);
		}
		break;
	case TYPE_ETCHED_LOWERED:
	case TYPE_ETCHED_RAISED:
		g->drawRect(x, y, width - 2, height - 2);

		if(themeColors) {
			if(type == TYPE_ETCHED_LOWERED) 
			{
				g->lighterColor(40);
			}
			else 
			{
				g->darkerColor(40);
			}
		}
		else 
		{
			g->setColor(colorB);
		}
		g->drawLine(x + 1, y + height - 3, x + 1, y +1);
		g->drawLine(x + 1, y + 1, x + width - 3, y + 1);

		g->drawLine(x, y + height - 1, x + width - 1, y + height - 1);
		g->drawLine(x + width - 1, y + height - 1, x + width - 1, y);
		break;
	case TYPE_BEVEL_RAISED:
		if(themeColors) 
		{
			g->setColor(getBackgroundColor(c));
			g->lighterColor(50);
		} 
		else
		{
			g->setColor(colorA);
		}
		g->drawLine(x, y, x, y + height - 2);
		g->drawLine(x + 1, y, x + width - 2, y);

		if(themeColors) 
		{
			g->darkerColor(25);
		} 
		else 
		{
			g->setColor(colorB);
		}
		g->drawLine(x + 1, y + 1, x + 1, y + height - 3);
		g->drawLine(x + 2, y + 1, x + width - 3, y + 1);

		if(themeColors) 
		{
			g->darkerColor(50);
		}
		else 
		{
			g->setColor(colorC);
		}
		g->drawLine(x, y + height - 1, x + width - 1, y + height - 1);
		g->drawLine(x + width - 1, y, x + width - 1, y + height - 2);

		if(themeColors) 
		{
			g->darkerColor(25);
		} 
		else 
		{
			g->setColor(colorD);
		}
		g->drawLine(x + 1, y + height - 2, x + width - 2, y + height - 2);
		g->drawLine(x + width - 2, y + 1, x + width - 2, y + height - 3);
		break;
	case TYPE_BEVEL_LOWERED:
		if(themeColors) 
		{
			g->setColor(getBackgroundColor(c));
			g->darkerColor(50);
		} 
		else
		{
			g->setColor(colorD);
		}
		g->drawLine(x, y, x, y + height - 1);
		g->drawLine(x + 1, y, x + width - 1, y);

		if(themeColors)
		{
			g->lighterColor(25);
		}
		else 
		{
			g->setColor(colorC);
		}
		g->drawLine(x + 1, y + 1, x + 1, y + height - 2);
		g->drawLine(x + 2, y + 1, x + width - 2, y + 1);

		if(themeColors)
		{
			g->lighterColor(50);
		} 
		else
		{
			g->setColor(colorC);
		}
		g->drawLine(x + 1, y + height - 1, x + width - 1, y + height - 1);
		g->drawLine(x + width - 1, y + 1, x + width - 1, y + height - 2);

		if(themeColors) {
			g->lighterColor(25);
		} 
		else
		{
			g->setColor(colorA);
		}
		g->drawLine(x + 2, y + height - 2, x + width - 2, y + height - 2);
		g->drawLine(x + width - 2, y + 2, x + width - 2, y + height - 3);
		break;
	case TYPE_IMAGE:
		break;
	}
	g->setColor(originalColor);
}

void Border::setDefaultBorder( shared_ptr<Border> border)
{
	defaultBorder = border;
}
shared_ptr<Border> Border::getDefaultBorder()
{	
	if(defaultBorder.get() == NULL){
		defaultBorder = Border::createEtchedRaised(0x020202, 0xBBBBBB);
	}
	return defaultBorder;
}

int Border::getBackgroundColor(shared_ptr<Component> c)
{
	return c->getStyle()->getBgColor();
}

void Border::drawImageBorderLine(shared_ptr<Graphics> g, shared_ptr<Image> left, shared_ptr<Image>right, shared_ptr<Image> center, int x, int y, int width)
{
	int currentWidth = width - right->getWidth();
	if(currentWidth > 0) 
	{
		x += left->getWidth();
		int destX = x + currentWidth;
		g->clipRect(x, y, currentWidth - left->getWidth(), center->getHeight());
		int centerWidth = center->getWidth();
		for(; x < destX ; x += centerWidth) 
		{
			g->drawImage(center, x, y);
		}
	}
}
void Border::drawImageBorderColumn(shared_ptr<Graphics> g, shared_ptr<Image> top, shared_ptr<Image> bottom, shared_ptr<Image> center, int x, int y, int height)
{
	int currentHeight = height - bottom->getHeight();
	if(currentHeight > 0) 
	{
		y += top->getHeight();
		int destY = y + currentHeight;
		g->clipRect(x, y, center->getWidth(), currentHeight - top->getHeight());
		int centerHeight = center->getHeight();
		for(; y < destY ; y += centerHeight) 
		{
			g->drawImage(center, x, y);
		}
	}
}

void Border::deinitialize()
{
	defaultBorder.reset();
	empty.reset();
}
__GUI_END_NAMESPACE
