#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
DefaultLookAndFeel::DefaultLookAndFeel(void)
{
	tickWhenFocused = true;
}

DefaultLookAndFeel::~DefaultLookAndFeel(void)
{

}

void DefaultLookAndFeel::bind( shared_ptr<Component> cmp )
{
	Label* label = dynamic_cast<Label*>(cmp.get());
	if (tickWhenFocused && label != NULL)
	{
		label->addFocusListener(this->shared_from_this());
	}

}

void DefaultLookAndFeel::setTickWhenFocused( bool tickWhenFocused )
{
	this->tickWhenFocused = tickWhenFocused;
}

void DefaultLookAndFeel::setCheckBoxImages( shared_ptr<Image> checked, shared_ptr<Image> unchecked )
{
	if (checked.get() == NULL || unchecked.get() == NULL) {
		chkBoxImages.reset();
	} else {
		chkBoxImages = new VectorArray<shared_ptr<Image> >(2);

		(*chkBoxImages)[0] = checked;
		(*chkBoxImages)[1] = unchecked;
	}

}

void DefaultLookAndFeel::setComboBoxImage( shared_ptr<Image> picker )
{
	 comboImage = picker;
}

void DefaultLookAndFeel::setRadioButtonImages( shared_ptr<Image> selected, shared_ptr<Image> unselected )
{
	if (selected.get() == NULL || unselected.get() == NULL) {
		rButtonImages.reset();
	} else {
		rButtonImages = new VectorArray<shared_ptr<Image> >(2);

		(*rButtonImages)[0] = unselected;
		(*rButtonImages)[1] = selected;
	}

}

shared_ptr<VectorArray<shared_ptr<Image> > > DefaultLookAndFeel::getRadioButtonImages()
{
	return rButtonImages;
}

void DefaultLookAndFeel::drawButton( shared_ptr<Graphics> g, shared_ptr<Button> b )
{
	 shared_ptr<Image> image;
	 drawComponent(g, b, b->getIconFromState(), image, 0);
}

void DefaultLookAndFeel::drawCheckBox( shared_ptr<Graphics> g, shared_ptr<Button> cb )
{
	if (chkBoxImages.get() != NULL) {
		drawComponent(g, cb, cb->getIconFromState(), (*chkBoxImages)[cb->isSelected() ? 1 : 0], 0);
	} else {
		shared_ptr<Style> style = cb->getStyle();

		// checkbox square needs to be the height and width of the font height even
		// when no text is in the check box this is a good indication of phone DPI
		int height = cb->getStyle()->getFont()->getHeight();
		shared_ptr<Image> image;
		drawComponent(g, cb, cb->getIconFromState(), image, height);

		int gradientColor;
		g->setColor(style->getFgColor());
		gradientColor = style->getBgColor();

		int width = height;
		float f = 12.0f;
		int rectWidth = scaleCoordinate(f, 16, width);
		int tX = cb->getX();
		if (cb->isRTL()) {
			tX = tX + cb->getWidth() - style->getPadding(cb->isRTL(), Component::LEFT) - rectWidth;
		} else {
			tX += style->getPadding(cb->isRTL(), Component::LEFT);
		}

		int tY = cb->getY() + style->getPadding(false, Component::TOP) + (cb->getHeight() - style->getPadding(false, Component::TOP) - style->getPadding(false, Component::BOTTOM)) / 2 - height / 2;
		g->translate(tX, tY);
		int x = scaleCoordinate(1.04f, 16, width);
		int y = scaleCoordinate(4.0f, 16, height);
		int rectHeight = scaleCoordinate(12.0f, 16, height);

		// brighten or darken the color slightly
		int destColor = findDestColor(gradientColor);

		g->fillLinearGradient(gradientColor, destColor, x + 1, y + 1, rectWidth - 2, rectHeight - 1, false);
		g->drawRoundRect(x, y, rectWidth, rectHeight, 5, 5);

		if (cb->isSelected()) {
			int color = g->getColor();
			g->setColor(0x111111);
			g->translate(0, 1);
			fillCheckbox(g, width, height);
			g->setColor(color);
			g->translate(0, -1);
			fillCheckbox(g, width, height);
		}
		g->translate(-tX, -tY);
	}

}

void DefaultLookAndFeel::fillCheckbox( shared_ptr<Graphics> g, int width, int height )
{
	int x1 = scaleCoordinate(2.0450495f, 16, width);
	int y1 = scaleCoordinate(9.4227722f, 16, height);
	int x2 = scaleCoordinate(5.8675725f, 16, width);
	int y2 = scaleCoordinate(13.921746f, 16, height);
	int x3 = scaleCoordinate(5.8675725f, 16, width);
	int y3 = scaleCoordinate(11.0f, 16, height);
	g->fillTriangle(x1, y1, x2, y2, x3, y3);

	x1 = scaleCoordinate(14.38995f, 16, width);
	y1 = scaleCoordinate(0, 16, height);
	g->fillTriangle(x1, y1, x2, y2, x3, y3);

}

int DefaultLookAndFeel::round( float x )
{
	int rounded = (int) x;
	if (x - rounded > 0.5f) {
		return rounded + 1;
	}
	return rounded;
}

int DefaultLookAndFeel::scaleCoordinate( float coordinate, float plain, int pixelSize )
{
	 return round(coordinate / plain * pixelSize);
}

void DefaultLookAndFeel::drawLabel( shared_ptr<Graphics> g, shared_ptr<Label> l )
{
	shared_ptr<Image> image; 
	drawComponent(g, l, l->getIcon(), image, 0);
}

void DefaultLookAndFeel::drawRadioButton( shared_ptr<Graphics> g, shared_ptr<Button> rb )
{
	if (rButtonImages.get() != NULL)
	{
		drawComponent(g, rb, rb->getIconFromState(), (*rButtonImages)[rb->isSelected() ? 1 : 0], 0);
	} else
	{
		shared_ptr<Style> style = rb->getStyle();

		// radio button radius needs to be of the size of the font height even
		// when no text is in the radio button this is a good indication of phone DPI
		int height = rb->getStyle()->getFont()->getHeight();

		shared_ptr<Image> nullImage;
		drawComponent(g, rb, rb->getIconFromState(), nullImage, height + rb->getGap());
		g->setColor(style->getFgColor());
		int x = rb->getX();
		if (rb->isRTL())
		{
			x = x + rb->getWidth() - style->getPadding(rb->isRTL(), Component::LEFT) - height;
		}
		else
		{
			x += style->getPadding(rb->isRTL(), Component::LEFT);
		}

		int y = rb->getY();

		// center the RadioButton
		y += max(0, rb->getHeight() / 2 - height / 2);

		g->drawArc(x, y, height, height, 0, 360);
		if (rb->isSelected())
		{
			int color = g->getColor();
			int destColor = findDestColor(color);
			g->fillRadialGradient(color, destColor, x + 3, y + 3, height - 5, height - 5);
		}
	}
}

void DefaultLookAndFeel::drawComboBox( shared_ptr<Graphics> g, shared_ptr<List> cb )
{
	int border = 2;
	shared_ptr<Style> style = cb->getStyle();
	int leftPadding = style->getPadding(cb->isRTL(), Component::LEFT);
	int rightPadding = style->getPadding(cb->isRTL(), Component::RIGHT);

	setFG(g, cb);

	shared_ptr<ListModel> model = cb->getModel();
	shared_ptr<ListCellRenderer> renderer = cb->getRenderer();
	shared_ptr<Object> value = model->getItemAt(model->getSelectedIndex());
	int comboImageWidth;
	if (comboImage.get() != NULL)
	{
		comboImageWidth = comboImage->getWidth();
	} else
	{
		comboImageWidth = style->getFont()->getHeight();
	}

	int cellX = cb->getX() + style->getPadding(false, Component::TOP);
	if(cb->isRTL())
	{
		cellX += comboImageWidth;
	}

	if (model->getSize() > 0)
	{
		shared_ptr<Component> cmp = renderer->getListCellRendererComponent(cb, value, model->getSelectedIndex(), cb->hasFocus());
		cmp->setX(cellX);
		cmp->setY(cb->getY() + style->getPadding(false, Component::TOP));
		cmp->setWidth(cb->getWidth() - comboImageWidth - 2 * rightPadding - leftPadding);
		cmp->setHeight(cb->getHeight() - style->getPadding(false, Component::TOP) - style->getPadding(false, Component::BOTTOM));
		cmp->paint(g);
	}

	g->setColor(style->getBgColor());
	int y = cb->getY();
	int height = cb->getHeight();
	int width = comboImageWidth + border;
	int x = cb->getX();
	if (cb->isRTL())
	{
		x += leftPadding;
	} else
	{
		x += cb->getWidth() - comboImageWidth - rightPadding - border;
	}

	if (comboImage.get() != NULL)
	{
		g->drawImage(comboImage, x, y + height / 2 - comboImage->getHeight() / 2);
	} else
	{
		int color = g->getColor();

		// brighten or darken the color slightly
		int destColor = findDestColor(color);

		g->fillLinearGradient(g->getColor(), destColor, x, y, width, height, false);
		g->setColor(color);
		g->drawRect(x, y, width, height - 1);

		width--;
		height--;

		//g.drawRect(x, y, width, height);
		g->translate(x + 1, y + 1);
		g->setColor(0x111111);
		int x1 = scaleCoordinate(2.5652081, 16, width);
		int y1 = scaleCoordinate(4.4753664, 16, height);
		int x2 = scaleCoordinate(8.2872691, 16, width);
		int y2 = scaleCoordinate(10, 16, height);
		int x3 = scaleCoordinate(13.516078, 16, width);
		int y3 = y1;
		g->fillTriangle(x1, y1, x2, y2, x3, y3);
		g->translate(-1, -1);
		g->setColor(style->getFgColor());
		g->fillTriangle(x1, y1, x2, y2, x3, y3);
		//g.setColor(style.getFgColor());
		//g.fillTriangle(x1 + 2, y1 + 2, x2, y2 - 2, x3 - 2, y3 + 2);

		g->translate(-x, -y);
	}
}

int DefaultLookAndFeel::findDestColor( int color )
{
	// brighten or darken the color slightly
	int sourceR = color >> 16 & 0xff;
	int sourceG = color >> 8 & 0xff;
	int sourceB = color & 0xff;
	if (sourceR > 128 && sourceG > 128 && sourceB > 128) {
		// darken
		sourceR = max(sourceR >> 1, 0);
		sourceG = max(sourceG >> 1, 0);
		sourceB = max(sourceB >> 1, 0);
	} else {
		// special case for black, since all channels are 0 it can't be brightened properly...
		if(color == 0) {
			return 0x222222;
		}

		// brighten
		sourceR = min(sourceR << 1, 0xff);
		sourceG = min(sourceG << 1, 0xff);
		sourceB = min(sourceB << 1, 0xff);
	}
	return ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);

}

void DefaultLookAndFeel::drawList( shared_ptr<Graphics> g, shared_ptr<List> l )
{

}


shared_ptr<Dimension> DefaultLookAndFeel::getButtonPreferredSize( shared_ptr<Button> b )
{
	shared_ptr<Image> image;
	shared_ptr<Vector<shared_ptr<Image> > > images =new  Vector<shared_ptr<Image> >;
	images->addElement(b->getIcon());
	images->addElement(b->getRolloverIcon());
	images->addElement(b->getPressedIcon());
	return getPreferredSize(b, images, image);
}

shared_ptr<Dimension> DefaultLookAndFeel::getCheckBoxPreferredSize( shared_ptr<Button> cb )
{
	shared_ptr<Image> image;
	shared_ptr<Vector<shared_ptr<Image> > > images = new Vector<shared_ptr<Image> >;
	images->addElement(cb->getIcon());
	images->addElement(cb->getRolloverIcon());
	images->addElement(cb->getPressedIcon());

	if (chkBoxImages.get() != NULL) {
		return getPreferredSize(cb, images, (*chkBoxImages)[0]);
	}
	shared_ptr<Dimension> d = getPreferredSize(cb, images, image);

	// checkbox square needs to be the height and width of the font height even
	// when no text is in the check box this is a good indication of phone DPI
	int checkBoxSquareSize = cb->getStyle()->getFont()->getHeight();

	// allow for checkboxes without a String within them
	d->setHeight(max(checkBoxSquareSize, d->getHeight()));

	d->setWidth(d->getWidth() + checkBoxSquareSize + cb->getGap());
	return d;

}

shared_ptr<Dimension> DefaultLookAndFeel::getLabelPreferredSize( shared_ptr<Label> l )
{
	shared_ptr<Image> image;
	shared_ptr<Vector<shared_ptr<Image> > > images = new Vector<shared_ptr<Image> >;
	
	images->addElement(l->getIcon());
	return getPreferredSize(l, images, image);
}

shared_ptr<Dimension> DefaultLookAndFeel::getPreferredSize( shared_ptr<Label> l, shared_ptr<Vector<shared_ptr<Image> > > icons, shared_ptr<Image> stateImage )
{
	int prefW = 0;
	int prefH = 0;

	shared_ptr<Style> style = l->getStyle();
	int gap = l->getGap();
	for (int i = 0; i < icons->size(); i++) {
		shared_ptr<Image> icon= (*icons)[i];
		if (icon.get() != NULL) {
			prefW = max(prefW, icon->getWidth());
			prefH = max(prefH, icon->getHeight());
		}
	}
	shared_ptr<String> text = l->getText();
	shared_ptr<Font> font = style->getFont();
	if (font.get() == NULL) {
	//	System.out.println("Missing font for " + l);
		font = Font::getDefaultFont();
	}
	if (text.get() != NULL && text->length() > 0) {
		//add the text size
		switch (l->getTextPosition()) {
				case Label::LEFT:
				case Label::RIGHT:
					prefW += font->stringWidth(text);
					prefH = max(prefH, font->getHeight());
					break;
				case Label::BOTTOM:
				case Label::TOP:
					prefW = max(prefW, font->stringWidth(text));
					prefH += font->getHeight();
					break;
		}
	}
	//add the state image(relevant for CheckBox\RadioButton)
	if (stateImage.get() != NULL) {
		prefW += (stateImage->getWidth() + gap);
		prefH = max(prefH, stateImage->getHeight());
	}


	if ((*icons)[0].get() != NULL && text.get() != NULL && text->length() > 0) {
		switch (l->getTextPosition()) {
				case Label::LEFT:
				case Label::RIGHT:
					prefW += gap;
					break;
				case Label::BOTTOM:
				case Label::TOP:
					prefH += gap;
					break;
		}
	}

	if (prefH != 0) {
		prefH += (style->getPadding(false, Component::TOP) + style->getPadding(false, Component::BOTTOM));
	}
	if (prefW != 0) {
		prefW += (style->getPadding(l->isRTL(), Component::RIGHT) + style->getPadding(l->isRTL(), Component::LEFT));
	}
	shared_ptr<Dimension> d=  new Dimension(prefW, prefH);
	return d;

}

shared_ptr<Dimension> DefaultLookAndFeel::getListPreferredSize( shared_ptr<List> l )
{
	shared_ptr<Dimension>  d;
	int width = 0;
	int height = 0;
	int selectedHeight;
	int selectedWidth;
	shared_ptr<ListModel> model = l->getModel();
	int numOfcomponents = max(model->getSize(), l->getMinElementHeight());
	shared_ptr<Object> prototype = l->getRenderingPrototype();

	shared_ptr<Style> unselectedEntryStyle;
	shared_ptr<Style> selectedEntryStyle;
	shared_ptr<Component> cmp;
	shared_ptr<ListCellRenderer> renderer;
	shared_ptr<Object> value;

	if(prototype.get() != NULL) {
		renderer = l->getRenderer();
		cmp = renderer->getListCellRendererComponent(l, prototype, 0, false);
		height = cmp->getPreferredH();
		width = cmp->getPreferredW();
		unselectedEntryStyle = cmp->getStyle();
		cmp = renderer->getListCellRendererComponent(l, prototype, 0, true);

		selectedEntryStyle = cmp->getStyle();
		selectedHeight = max(height, cmp->getPreferredH());
		selectedWidth = max(width, cmp->getPreferredW());
	} else {
		int hightCalcComponents = min(5, numOfcomponents);
		shared_ptr<Object> dummyProto = l->getRenderingPrototype();
		if(model->getSize() > 0 && dummyProto.get() == NULL) {
			dummyProto = model->getItemAt(0);
		}
		renderer = l->getRenderer();
		for (int i = 0; i < hightCalcComponents; i++) {
			if(i < model->getSize()) {
				value = model->getItemAt(i);
			} else {
				value = dummyProto;
			}
			cmp = renderer->getListCellRendererComponent(l, value, i, false);
			unselectedEntryStyle = cmp->getStyle();

			height = max(height, cmp->getPreferredH());
			width =  max(width, cmp->getPreferredW());
		}
		selectedEntryStyle = unselectedEntryStyle;
		selectedHeight = height;
		selectedWidth = width;
		if (model->getSize() > 0) {
			value = model->getItemAt(0);
			cmp = renderer->getListCellRendererComponent(l, value, 0, true);

			selectedHeight = max(height, cmp->getPreferredH());
			selectedWidth = max(width, cmp->getPreferredW());
			selectedEntryStyle = cmp->getStyle();
		}
	}
	if(selectedEntryStyle.get() != NULL) {
		selectedWidth += selectedEntryStyle->getMargin(false, Component::LEFT) + selectedEntryStyle->getMargin(false, Component::RIGHT);
		selectedHeight += selectedEntryStyle->getMargin(false, Component::TOP) + selectedEntryStyle->getMargin(false, Component::BOTTOM);
		width += unselectedEntryStyle->getMargin(false, Component::LEFT) + unselectedEntryStyle->getMargin(false, Component::RIGHT);
		height += unselectedEntryStyle->getMargin(false, Component::TOP) + unselectedEntryStyle->getMargin(false, Component::BOTTOM);
	}

	shared_ptr<Style> lStyle = l->getStyle();
	int verticalPadding = lStyle->getPadding(false, Component::TOP) + lStyle->getPadding(false, Component::BOTTOM);
	int horizontalPadding = lStyle->getPadding(false, Component::RIGHT) + lStyle->getPadding(false, Component::LEFT);

	if (numOfcomponents == 0) {
		d = new Dimension(horizontalPadding, verticalPadding);
		return d;
	}

	// If combobox without ever importing the ComboBox class dependency
	if(l->getOrientation() > List::HORIZONTAL) {
		int boxWidth = l->getStyle()->getFont()->getHeight() + 2;
		d = new Dimension(boxWidth + selectedWidth + horizontalPadding, selectedHeight + verticalPadding);
		return d;
	} else {
		if (l->getOrientation() == List::VERTICAL) {
			d = new Dimension(selectedWidth + horizontalPadding, selectedHeight + (height + l->getItemGap()) * (numOfcomponents - 1) + verticalPadding);
			return d;
		} else {
			d =new Dimension(selectedWidth + (width + l->getItemGap()) * (numOfcomponents - 1) + horizontalPadding, selectedHeight + verticalPadding);
			return d;		
		}
	}

}

shared_ptr<Dimension> DefaultLookAndFeel::getRadioButtonPreferredSize( shared_ptr<Button> rb )
{
	shared_ptr<Image> image;
	shared_ptr<Vector<shared_ptr<Image> > > images = new Vector<shared_ptr<Image> >;
	images->addElement(rb->getIcon());
	images->addElement(rb->getRolloverIcon());
	images->addElement(rb->getPressedIcon());
	if (rButtonImages.get() != NULL) {
		return getPreferredSize(rb, images, (*rButtonImages)[0]);
	}
	shared_ptr<Dimension> d = getPreferredSize(rb, images, image);

	// radio button radius needs to be of the size of the font height even
	// when no text is in the radio button this is a good indication of phone DPI
	int height = rb->getStyle()->getFont()->getHeight();

	// allow for radio buttons without a String within them
	d->setHeight(max(height, d->getHeight()));

	d->setWidth(d->getWidth() + height + rb->getGap());
	return d;

}

//shared_ptr<Dimension> DefaultLookAndFeel::getTextAreaSize( shared_ptr<TextArea> ta, bool pref )
//{
//	shared_ptr<Dimension> d;
//	return d;
//}

int DefaultLookAndFeel::reverseAlignForBidi( shared_ptr<Component> c, int align )
{
	if(c->isRTL()) {
		switch(align) {
				case Component::RIGHT:
					return Component::LEFT;
				case Component::LEFT:
					return Component::RIGHT;
		}
	}
	return align;

}

void DefaultLookAndFeel::drawComponent( shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<Image> icon, shared_ptr<Image> stateIcon, int preserveSpaceForState )
{
	setFG(g, l);

	int gap = l->getGap();
	int stateIconSize = 0;
	int stateIconYPosition = 0;
	shared_ptr<String> text = l->getText();
	shared_ptr<Style> style = l->getStyle();

	int leftPadding = style->getPadding(l->isRTL(), Component::LEFT);
	int rightPadding = style->getPadding(l->isRTL(), Component::RIGHT);

	shared_ptr<Font> font = style->getFont();
	if(font.get() == NULL)
		font = Font::getDefaultFont();
	int fontHeight = 0;
	if (text.get() == NULL) {
		text = new String(L"");
	}
	if(text->length() > 0){
		fontHeight = font->getHeight();
	}

	if (stateIcon.get() != NULL) {
		stateIconSize = stateIcon->getWidth(); //square image width == height
		stateIconYPosition = l->getY() + l->getStyle()->getPadding(false, Component::TOP) +
			(l->getHeight() - l->getStyle()->getPadding(false, Component::TOP) -
			l->getStyle()->getPadding(false, Component::BOTTOM)) / 2 - stateIconSize / 2;
		preserveSpaceForState = stateIconSize + gap;
		int tX = l->getX();
		if (l->isRTL()) {
			tX = tX + l->getWidth() - style->getPadding(l->isRTL(), Component::LEFT) - stateIcon->getWidth();
		} else {
			tX += style->getPadding(l->isRTL(), Component::LEFT);
		}

		g->drawImage(stateIcon, tX, stateIconYPosition);
	}

	//default for bottom left alignment
	int x = l->getX() + l->getStyle()->getPadding(l->isRTL(), Component::LEFT) + preserveSpaceForState;
	int y = l->getY() + l->getStyle()->getPadding(false, Component::TOP);

	int align = reverseAlignForBidi(l, l->getAlignment());

	int textPos= reverseAlignForBidi(l, l->getTextPosition());

	//set initial x,y position according to the alignment and textPosition
	if (align == Component::LEFT) {
		switch (textPos) {
				case Label::LEFT:
				case Label::RIGHT:
					y = y + (l->getHeight() - (l->getStyle()->getPadding(false, Component::TOP) + l->getStyle()->getPadding(false, Component::BOTTOM) + max(((icon.get() != NULL) ? icon->getHeight() : 0), fontHeight))) / 2;
					break;
				case Label::BOTTOM:
				case Label::TOP:
					y = y + (l->getHeight() - (l->getStyle()->getPadding(false, Component::TOP) + l->getStyle()->getPadding(false, Component::BOTTOM) + ((icon.get() != NULL) ? icon->getHeight() + gap : 0) + fontHeight)) / 2;
					break;
		}
	} else if (align == Component::CENTER) {
		switch (textPos) {
				case Label::LEFT:
				case Label::RIGHT:
					x = x + (l->getWidth() - (preserveSpaceForState +
						leftPadding +
						rightPadding +
						((icon.get() != NULL) ? icon->getWidth() : 0) +
						font->stringWidth(text))) / 2;
					x = max(x, l->getX() + leftPadding + preserveSpaceForState);
					y = y + (l->getHeight() - (style->getPadding(false, Component::TOP) +
						style->getPadding(false, Component::BOTTOM) +
						max(((icon.get() != NULL) ? icon->getHeight() : 0),
						fontHeight))) / 2;
					break;
				case Label::BOTTOM:
				case Label::TOP:
					x = x + (l->getWidth() - (preserveSpaceForState + leftPadding +
						rightPadding +
						max(((icon.get() != NULL) ? icon->getWidth() : 0),
						font->stringWidth(text)))) / 2;
					x = max(x, l->getX() + leftPadding + preserveSpaceForState);
					y = y + (l->getHeight() - (style->getPadding(false, Component::TOP) +
						style->getPadding(false, Component::BOTTOM) +
						((icon.get() != NULL) ? icon->getHeight() + gap : 0) +
						fontHeight)) / 2;
					break;
		}
	} else if (align == Component::RIGHT) {
		switch (textPos) {
				case Label::LEFT:
				case Label::RIGHT:
					x = l->getX() + l->getWidth() - rightPadding -
						( ((icon.get() != NULL) ? (icon->getWidth() + gap) : 0) +
						font->stringWidth(text));
					if(l->isRTL()) {
						x = max(x - preserveSpaceForState, l->getX() + leftPadding);
					} else {
						x = max(x, l->getX() + leftPadding + preserveSpaceForState);
					}
					y = y + (l->getHeight() - (style->getPadding(false, Component::TOP) +
						style->getPadding(false, Component::BOTTOM) +
						max(((icon.get() != NULL) ? icon->getHeight() : 0),
						fontHeight))) / 2;
					break;
				case Label::BOTTOM:
				case Label::TOP:
					x = l->getX() + l->getWidth() - rightPadding -
						(max(((icon.get() != NULL) ? (icon->getWidth()) : 0),
						font->stringWidth(text)));
					x = max(x, l->getX() + leftPadding + preserveSpaceForState);
					y = y + (l->getHeight() - (style->getPadding(false, Component::TOP) +
						style->getPadding(false, Component::BOTTOM) +
						((icon.get() != NULL) ? icon->getHeight() + gap : 0) + fontHeight)) / 2;
					break;
		}
	}


	int textSpaceW = l->getWidth() - style->getPadding(false, Label::RIGHT) - style->getPadding(false, Label::LEFT);

	if (icon.get() != NULL && (textPos == Label::RIGHT || textPos == Label::LEFT)) {
		textSpaceW = textSpaceW - icon->getWidth();
	}

	if (stateIcon.get() != NULL) {
		textSpaceW = textSpaceW - stateIcon->getWidth();
	} else {
		textSpaceW = textSpaceW - preserveSpaceForState;
	}

	if (icon.get() == NULL) { // no icon only String 
		drawLabelString(g, l, text, x, y, textSpaceW, preserveSpaceForState);
	} else {
		//int strHeight = l.getStyle().getFont().getHeight();
		int strWidth = l->getStyle()->getFont()->stringWidth(text);
		int iconWidth = icon->getWidth();
		int iconHeight = icon->getHeight();
		int iconStringWGap;
		int iconStringHGap;

		switch (textPos) {
				case Label::LEFT:
					if (iconHeight > fontHeight) {
						iconStringHGap = (iconHeight - fontHeight) / 2;
						//drawLabelStringValign(g, l, text, x, y, iconStringHGap, iconHeight);
						strWidth = drawLabelStringValign(g, l, text, x, y, iconStringHGap, iconHeight, textSpaceW, fontHeight, preserveSpaceForState);

						g->drawImage(icon, x + strWidth + gap, y);
					} else {
						iconStringHGap = (fontHeight - iconHeight) / 2;
						//drawLabelString(g, l, text, x, y);
						strWidth = drawLabelString(g, l, text, x, y, textSpaceW, preserveSpaceForState);

						g->drawImage(icon, x + strWidth + gap, y + iconStringHGap);
					}
					break;
				case Label::RIGHT:
					if (iconHeight > fontHeight) {
						iconStringHGap = (iconHeight - fontHeight) / 2;
						g->drawImage(icon, x, y);
						//drawLabelStringValign(g, l, text, x+ iconWidth + gap, y, iconStringHGap, iconHeight);
						drawLabelStringValign(g, l, text, x + iconWidth + gap, y, iconStringHGap, iconHeight, textSpaceW, fontHeight, preserveSpaceForState);
					} else {
						iconStringHGap = (fontHeight - iconHeight) / 2;
						g->drawImage(icon, x, y + iconStringHGap);
						//drawLabelString(g, l, text, x + iconWidth + gap, y);
						drawLabelString(g, l, text, x + iconWidth + gap, y, textSpaceW, preserveSpaceForState);
					}
					break;
				case Label::BOTTOM:
					if (iconWidth > strWidth) { //center align the smaller

						iconStringWGap = (iconWidth - strWidth) / 2;
						g->drawImage(icon, x, y);
						//drawLabelString(g, l, text, x + iconStringWGap, y + iconHeight + gap);
						drawLabelString(g, l, text, x + iconStringWGap, y + iconHeight + gap, textSpaceW, preserveSpaceForState);
					} else {
						iconStringWGap = (min(strWidth, textSpaceW) - iconWidth) / 2;
						g->drawImage(icon, x + iconStringWGap, y);

						//drawLabelString(g, l, text, x, y + iconHeight + gap);
						drawLabelString(g, l, text, x, y + iconHeight + gap, textSpaceW, preserveSpaceForState);
					}
					break;
				case Label::TOP:
					if (iconWidth > strWidth) { //center align the smaller

						iconStringWGap = (iconWidth - strWidth) / 2;
						//                        drawLabelString(g, l, text, x + iconStringWGap, y);
						drawLabelString(g, l, text, x + iconStringWGap, y, textSpaceW, preserveSpaceForState);
						g->drawImage(icon, x, y + fontHeight + gap);
					} else {
						iconStringWGap = (min(strWidth, textSpaceW) - iconWidth) / 2;
						//                        drawLabelString(g, l, text, x, y);
						drawLabelString(g, l, text, x, y, textSpaceW, preserveSpaceForState);
						g->drawImage(icon, x + iconStringWGap, y + fontHeight + gap);
					}
					break;
		}
	}

}

int DefaultLookAndFeel::drawLabelStringValign( shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> str, int x, int y, int iconStringHGap, int iconHeight, int textSpaceW, int fontHeight, int preserveSpaceForState )
{

	switch (l->getVerticalAlignment()) {
			case Component::TOP:
				return drawLabelString(g, l, str, x, y, textSpaceW, preserveSpaceForState);
			case Component::CENTER:
				return drawLabelString(g, l, str, x, y + iconHeight / 2 - fontHeight / 2, textSpaceW, preserveSpaceForState);
			default:
				return drawLabelString(g, l, str, x, y + iconStringHGap, textSpaceW, preserveSpaceForState);
	}

}

int DefaultLookAndFeel::drawLabelString( shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> text, int x, int y, int textSpaceW, int preserveSpaceForState )
{
	shared_ptr<Style> style = l->getStyle();

	int cx = g->getClipX();
	int cy = g->getClipY();
	int cw = g->getClipWidth();
	int ch = g->getClipHeight();

	g->clipRect(x, cy, textSpaceW, ch);

	if (l->isTickerRunning()) {
		if (l->getShiftText() > 0) {
			if (l->getShiftText() > textSpaceW) {
				l->setShiftText(x - l->getX() - style->getFont()->stringWidth(text));
			}
		} else if (l->getShiftText() + style->getFont()->stringWidth(text) < 0) {
			l->setShiftText(textSpaceW);
		}
	}
	int drawnW = drawLabelText(g, l, text, x, y, textSpaceW);

	g->setClip(cx, cy, cw, ch);

	return drawnW;

}

int DefaultLookAndFeel::drawLabelText( shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> text, int x, int y, int textSpaceW )
{
	shared_ptr<Font> f = l->getStyle()->getFont();
	if ((!l->isTickerRunning()) || l->isRTL()) {
		int txtW = f->stringWidth(text);

		//if there is no space to draw the text add ->.. at the end
		if (txtW > textSpaceW && textSpaceW > 0) {
			// Handling of adding 3 points and in fact all text positioning when the text is bigger than
			// the allowed space is handled differently in RTL, this is due to the reverse algorithm
			// effects - i.e. when the text includes both Hebrew/Arabic and English/numbers then simply
			// trimming characters from the end of the text (as done with LTR) won't do.
			// Instead we simple reposition the text, and draw the 3 points, this is quite simple, but
			// the downside is that a part of a letter may be shown here as well.

			if (l->isRTL()) {
				if ((!l->isTickerRunning()) && (l->isEndsWith3Points())) {
					shared_ptr<String> points = new String(L"...");
					int pointsW = f->stringWidth(points);
					g->drawString(points, l->getShiftText() + x, y);
					g->clipRect(pointsW+l->getShiftText() + x, y, textSpaceW - pointsW, f->getHeight());
				}
				x = x - txtW + textSpaceW;
			} else {
				if (l->isEndsWith3Points()) {
					String points(L"...");
					int index = 1;
					shared_ptr<String> tmp = new String(L"...");
					//weak_ptr
					
					int pointsW = f->stringWidth(tmp);
					tmp = new String(text->substr(0, index));
					while (f->stringWidth(tmp) + pointsW < textSpaceW) {
						index++;
						if (index >= text->length()) {
							break;
						}
						tmp =new String(text->substr(0, index));
					}
					tmp = new String(text->substr(0, index) + points);
					text = tmp;
				}
			}
		}
	}

	g->drawString(text, l->getShiftText() + x, y);
	return min(f->stringWidth(text), textSpaceW);

}

shared_ptr<Dimension> DefaultLookAndFeel::getComboBoxPreferredSize( shared_ptr<List> cb )
{
	 return getListPreferredSize(cb);
}

//shared_ptr<Component> DefaultLookAndFeel::getTabbedPaneCell( shared_ptr<TabbedPane> tp, shared_ptr<String> text, shared_ptr<Image> icon, bool isSelected, bool cellHasFocus, shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle, shared_ptr<Style> tabbedPaneStyle, int cellOffsetX, int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize, shared_ptr<Dimension> contentPaneSize )
//{
//
//}

void DefaultLookAndFeel::updateCellLook( shared_ptr<TabbedPane> tp, shared_ptr<Component> c, bool selected )
{
	c->getStyle()->setFgColor(tp->getStyle()->getFgColor());
	c->getStyle()->setBgTransparency(tp->getStyle()->getBgTransparency());
	c->getStyle()->setFont(tp->getStyle()->getFont());

}

void DefaultLookAndFeel::drawTabbedPaneContentPane( shared_ptr<TabbedPane> tp, shared_ptr<Graphics> g, 
					shared_ptr<Rectangle> rect, shared_ptr<Dimension> cellsPreferredSize, int numOfTabs,
					int selectedTabIndex, shared_ptr<Dimension> tabsSize, int cellOffsetX, int cellOffsetY )
{
	int tPBorder = tp->getTabbedPaneBorderWidth();
	if(tPBorder < 1)
	{
		return;
	}
	int x = rect->getX();
	int y = rect->getY();
	int w = rect->getSize()->getWidth();
	int h = rect->getSize()->getHeight();
	int listPreferredW = cellsPreferredSize->getWidth();
	int listPreferredH = cellsPreferredSize->getHeight();
	int maxTabWidth = tabsSize->getWidth();
	int maxTabHeight = tabsSize->getHeight();

	g->setColor(tp->getStyle()->getBgColor());
	g->fillRect(x, y, w, h, tp->getStyle()->getBgTransparency());

	// paint borders for TOP tab placement
	g->setColor(tp->getStyle()->getFgColor());
	int tabP = tp->getTabPlacement();

	if (tabP == TabbedPane::TOP || tabP == TabbedPane::BOTTOM)
	{
		g->fillRect(x, y, tPBorder, h);// west border

		g->fillRect(x + w - tPBorder, y, tPBorder, h);// east border

		int relativeY = y;
		if (tabP == TabbedPane::BOTTOM)
		{
			relativeY = y + h - tPBorder;
			g->fillRect(x, y, w, tPBorder);// north border

		} else
		{
			g->fillRect(x, y + h - tPBorder, w, tPBorder);// south border

		}

		if(tp->isRTL())
		{
			if (listPreferredW < w)
			{
				g->fillRect(x, relativeY, w - listPreferredW, tPBorder);
			}
			for (int i = 0; i < numOfTabs; i++)
			{
				if (i != selectedTabIndex)
				{
					g->fillRect((x - cellOffsetX + w - (maxTabWidth * (i+1))), relativeY, maxTabWidth + tPBorder, tPBorder);
				}
			}

		} else
		{
			if (listPreferredW < w)
			{
				g->fillRect(listPreferredW - tPBorder, relativeY, w - listPreferredW, tPBorder);
			}
			for (int i = 0; i < numOfTabs; i++)
			{
				if (i != selectedTabIndex) {
					g->fillRect((x - cellOffsetX + (maxTabWidth * i)), relativeY, maxTabWidth + tPBorder, tPBorder);
				}
			}
		}
	}
	else
	{//if (tabP == LEFT || tabP == RIGHT) {

		g->fillRect(x, y, w, tPBorder);// north border

		g->fillRect(x, y + h - tPBorder, w, tPBorder);// south border

		int relativeX = x;
		if (!tp->isRTL() && tabP == TabbedPane::RIGHT ||
			tp->isRTL() && tabP == TabbedPane::LEFT)
		{
				g->fillRect(x, y, tPBorder, h);// west border

				relativeX = x + w - tPBorder;
		}
		else
		{
			g->fillRect(x + w - tPBorder, y, tPBorder, h);// east border

		}

		if (listPreferredH < h)
		{
			g->fillRect(relativeX, y + listPreferredH - tPBorder, tPBorder, h - listPreferredH + tPBorder);
		}
		for (int i = 0; i < numOfTabs; i++)
		{
			if (i != selectedTabIndex)
			{
				g->fillRect(relativeX, (y - cellOffsetY + (maxTabHeight * i)), tPBorder, maxTabHeight + tPBorder);
			}
		}

	}
}

bool DefaultLookAndFeel::isRTLOrWhitespace( char c )
{
	return (Display::getInstance()->isRTL(c)) || c == ' ';

}


//shared_ptr<Dimension> DefaultLookAndFeel::getTextFieldPreferredSize( shared_ptr<TextArea> ta )
//{
//	shared_ptr<Dimension> d;
//	return d;
//}
void DefaultLookAndFeel::focusGained( shared_ptr<Component> cmp )
{
	Label *label = dynamic_cast<Label*>(cmp.get());
	if(label != NULL) {
		if (label->shouldTickerStart()) {
			label->startTicker(getTickerSpeed(), true);
		}
	}
}

void DefaultLookAndFeel::focusLost( shared_ptr<Component> cmp )
{
	Label *label = dynamic_cast<Label*>(cmp.get());
	if(label != NULL)  {
		if (label->isTickerRunning()) {
			label->stopTicker();
		}
	}
}

shared_ptr<Component> DefaultLookAndFeel::getTabbedPaneCell( shared_ptr<TabbedPane> tp, shared_ptr<String> text, shared_ptr<Image> icon, bool isSelected, bool cellHasFocus, shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle, shared_ptr<Style> tabbedPaneStyle, int cellOffsetX, int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize, shared_ptr<Dimension> contentPaneSize )
{
	shared_ptr<Label> cell = TabbedPaneCellLabel::newV(tp,text,isSelected, cellHasFocus, cellStyle, cellSelectedStyle, tabbedPaneStyle, cellOffsetX, cellOffsetY, cellsPreferredSize, contentPaneSize);
	cell->setUIID(new String(L"Tab"));
	cell->setCellRenderer(true);

	shared_ptr<Border> nullBorder;
	cell->getStyle()->setBorder(nullBorder);

	cell->getStyle()->setMargin(0, 0, 0, 0);
	cell->setIcon(icon);
	updateCellLook(tp, static_pointer_cast<Component>(cell), isSelected);
	if (isSelected)
	{
		cellStyle->setBgColor(cellStyle->getBgColor());
	}

	cell->setAlignment(Label::CENTER);
	return cell;

}

shared_ptr<Dimension> DefaultLookAndFeel::getTextAreaSize( shared_ptr<TextArea> ta, bool pref )
{
	shared_ptr<Dimension> d;
	return d;
}

void DefaultLookAndFeel::drawTextField( shared_ptr<Graphics> g, shared_ptr<TextField> ta )
{

}

void DefaultLookAndFeel::drawTextFieldCursor( shared_ptr<Graphics> g, shared_ptr<TextArea> ta )
{

}

void DefaultLookAndFeel::drawTextArea( shared_ptr<Graphics> g, shared_ptr<TextArea> ta )
{

}

void DefaultLookAndFeel::drawTabbedPane( shared_ptr<Graphics> g, shared_ptr<TabbedPane> tp )
{

}

shared_ptr<Dimension> DefaultLookAndFeel::getTextFieldPreferredSize( shared_ptr<TextArea> ta )
{
	//to-do
	shared_ptr<Dimension> dim;
	return dim;
}

shared_ptr<VectorArray<shared_ptr<Image> > > DefaultLookAndFeel::getCheckBoxImages()
{
	return chkBoxImages;
}

void TabbedPaneCellLabel::paint( shared_ptr<Graphics> g )
{
	int tPBorder = tp->getTabbedPaneBorderWidth();
	int focusMarkWidth = tPBorder * 2;
	int tabP = tp->getTabPlacement();
	// Initialize forground colors before calling to super.paint()
	if (isSelected && cellHasFocus)
	{
		focusMarkWidth = tPBorder * 3;
		this->getStyle()->setFgColor(cellSelectedStyle->getFgColor());
	}
	else
	{
		this->getStyle()->setFgColor(cellStyle->getFgColor());
	}

	Label::paint(g);

	if (!isSelected)
	{
		g->setColor(0);
		g->fillRect(getX(), getY(), getWidth(), getHeight(), (unsigned char) 0x2f);
	}
	// coloring back the focus mark line
	g->setColor(getStyle()->getFgColor());
	if (tabP == TabbedPane::TOP || tabP == TabbedPane::BOTTOM)
	{
		if (tabP == TabbedPane::TOP)
		{
			if (isSelected)
			{
				g->fillRect(getX(), getY() + tPBorder, getWidth(), focusMarkWidth);// north

			}
			g->setColor(tabbedPaneStyle->getFgColor());
			g->fillRect(getX(), getY(), getWidth(), tPBorder);//north line

			g->fillRect(getX(), getY(), tPBorder, getHeight());// west line

		} else {
			if (isSelected) {
				g->fillRect(getX(), getY() + getHeight() - focusMarkWidth, getWidth(), focusMarkWidth);// south

			}
			g->setColor(tabbedPaneStyle->getFgColor());
			g->fillRect(getX(), getY() + getHeight() - tPBorder, getWidth(), tPBorder);//south line

			g->fillRect(getX(), getY(), tPBorder, getHeight());// west line

		}
		int x = getX() - cellOffsetX + getWidth();
		if (x == contentPaneSize->getWidth()) {
			g->fillRect(x + cellOffsetX - tPBorder, getY(), tPBorder, getHeight());// east line

		}
		if (cellsPreferredSize->getWidth() < contentPaneSize->getWidth() && (getX() + getWidth() == cellsPreferredSize->getWidth())) {
			g->fillRect(getX() + getWidth() - tPBorder, getY(), tPBorder, getHeight());
		}
	} else { // LEFT or RIGHT

		if (isSelected) {
			g->fillRect(getX(), getY() + tPBorder, getWidth(), focusMarkWidth);// north

		}
		g->setColor(tabbedPaneStyle->getFgColor());
		g->fillRect(getX(), getY(), getWidth(), tPBorder);
		int y = getY() - cellOffsetY + getHeight();
		if (y == contentPaneSize->getHeight()) {
			g->fillRect(getX(), y + cellOffsetY - tPBorder, getWidth(), tPBorder);
		}
		if (cellsPreferredSize->getHeight() < contentPaneSize->getHeight() && (getY() + getHeight() == cellsPreferredSize->getHeight())) {
			g->fillRect(getX(), getY() + getHeight() - tPBorder, getWidth(), tPBorder);//south line

		}
		if (!tp->isRTL() && tabP == TabbedPane::LEFT || 
			tp->isRTL() && tabP == TabbedPane::RIGHT) {
				g->fillRect(getX(), getY(), tPBorder, getHeight());// west border
		} else {
			g->fillRect(getX() + getWidth() - tPBorder, getY(), tPBorder, getHeight());// east border
		}
	}
}

TabbedPaneCellLabel::TabbedPaneCellLabel()
{

}

void TabbedPaneCellLabel::constructV( shared_ptr<TabbedPane> tp, shared_ptr<String> text, bool isSelected, 
									 bool cellHasFocus, shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle, 
									 shared_ptr<Style> tabbedPaneStyle, int cellOffsetX, int cellOffsetY, 
									 shared_ptr<Dimension> cellsPreferredSize, shared_ptr<Dimension> contentPaneSize )
{
	Label::constructV(text);
	this->tp = tp;
	this->isSelected = isSelected;
	this->cellHasFocus = cellHasFocus;
	this->cellStyle = cellStyle;
	this->cellSelectedStyle = cellSelectedStyle;
	this->tabbedPaneStyle = tabbedPaneStyle;
	this->cellOffsetX = cellOffsetX;
	this->cellOffsetY = cellOffsetY;
	this->cellsPreferredSize = cellsPreferredSize;
	this->contentPaneSize = contentPaneSize;
}

shared_ptr<TabbedPaneCellLabel> TabbedPaneCellLabel::newV( shared_ptr<TabbedPane> tp, shared_ptr<String> text, 
														  bool isSelected, bool cellHasFocus, shared_ptr<Style> cellStyle, 
														  shared_ptr<Style> cellSelectedStyle, shared_ptr<Style> tabbedPaneStyle, 
														  int cellOffsetX, int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize, 
														  shared_ptr<Dimension> contentPaneSize )
{
	shared_ptr<TabbedPaneCellLabel> self = new TabbedPaneCellLabel();
	self->constructV(tp, text, isSelected, cellHasFocus, cellStyle, cellSelectedStyle,  tabbedPaneStyle, 
										cellOffsetX, cellOffsetY, cellsPreferredSize, contentPaneSize );
	return self;
}
__GUI_END_NAMESPACE
