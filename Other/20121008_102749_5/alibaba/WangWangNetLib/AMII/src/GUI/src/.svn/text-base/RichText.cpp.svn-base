#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
class LookAndFeel;

AM_IMPLEMENT_DYNAMIC(RichText, Component)

RichText::Box::Box(int type, bool focusable, shared_ptr<Object> object, shared_ptr<RichText> richText):
						type(type), focusable(focusable), object(object), isSelected(false),
							lineStart(-1), lineEnd(-1)
{
	this->richText = richText;
	this->selStyle = this->richText->getStyle();
}

RichText::Box::Box(shared_ptr<RichText> richText)
{
	this->richText = richText;
}

RichText::PaintBox::PaintBox(int x, int y, shared_ptr<Box> box, shared_ptr<Object> object):
				x(x), y(y), rawBox(box), object(object), width(0), height(0)
{
}

				RichText::PaintBox::PaintBox(shared_ptr<Box> box, shared_ptr<Object> object):
x(0), y(0), rawBox(box), object(object), width(0), height(0)
{
}

RichText::RowBox::RowBox():height(0)
{
	vectPaintBox = new Vector<shared_ptr<PaintBox> >;
}

void RichText::constructV(shared_ptr<String> uid /*= new String(L"RichText")*/) 
{	
//	Component::constructV();
	linesToScroll = 1;
	unsupportedChars = new String(L"\t\r");
	rows = 0;
	widthForRowCalculations = -1;
	rowsGap = 2;
	// to check 
	actionListeners = new Vector<shared_ptr<ActionListener> >;
	isShowMore = true;
	selectedIndex = -1;
	topLineIndex = 0;
	bottomLineIndex = 0;
	maxRowSize = 0;
	moreRows = false;

	setUIID(uid);
	// to check
	vectRawBox = new Vector<shared_ptr<Box> >;
	vectFoucusabelBox = new Vector<shared_ptr<Box> >;
	vectRowBox = new Vector<shared_ptr<RowBox> >;

	shared_ptr<LookAndFeel> laf = UIManager::getInstance()->getLookAndFeel();
	setSmoothScrolling(laf->isDefaultSmoothScrolling());
}

RichText::~RichText(void)
{
}
shared_ptr<RichText> RichText::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<RichText>(cmp);
}
void RichText::initComponent()
{
	this->getSelectedStyle()->setPadding(Component::BOTTOM, 0);
	this->getSelectedStyle()->setPadding(Component::TOP, 0);
	this->getSelectedStyle()->setMargin(Component::BOTTOM, 0);
	this->getSelectedStyle()->setMargin(Component::TOP, 0);
}

void RichText::addBox(int type, shared_ptr<Object> object)
{
	shared_ptr<Style> nullStyle = new Style();
	shared_ptr<ActionListener> nullActionListener; //= new ActionListener();

	insertBox(type, false, object, vectRawBox->size(), nullActionListener, nullStyle);
}

void RichText::addBox(int type, bool focusable, shared_ptr<Object> object)
{
	shared_ptr<Style> nullStyle = new Style();
	shared_ptr<ActionListener> nullActionListener; //= new ActionListener();

	insertBox(type, focusable, object, vectRawBox->size(), nullActionListener, nullStyle);
}

void RichText::addBox(int type, bool focusable, shared_ptr<Object> object,
			shared_ptr<ActionListener> listener)
{
	shared_ptr<Style> nullStyle = new Style();
	insertBox(type, focusable, object, vectRawBox->size(), listener, nullStyle);
}

void RichText::addBox(int type, bool focusable, shared_ptr<Object> object,
			shared_ptr<Style> selStyle)
{
	shared_ptr<ActionListener> nullActionListener;// = new ActionListener();
	insertBox(type, focusable, object, vectRawBox->size(), nullActionListener, selStyle);
}

void RichText::addBox(int type, bool focusable, shared_ptr<Object> object,
					  shared_ptr<ActionListener> listener, shared_ptr<Style> selStyle)
{
	insertBox(type, focusable, object, vectRawBox->size(), listener, selStyle);
}

void RichText::insertBox(int type, bool focusable, shared_ptr<Object> object,
			   int index, shared_ptr<ActionListener> listener, shared_ptr<Style> selStyle)
{
	if (type != TEXT && type != LINK && type != IMAGE)
	{
	   // to check
	   //throw new IllegalArgumentException("type unkown");
	   return;
	}
	if (object.get() == NULL )
	{
	   // to check 
	   //throw new IllegalArgumentException("object null");
	   return;
	}

	if (index > vectRawBox->size())
	{
	   // to check
	   //throw new IllegalArgumentException("index out of bound");
	   return;
	}

	shared_ptr<Box> box = new Box(type, focusable, object, this->shared_from_this());
	if (focusable)
	{
	   vectFoucusabelBox->addElement(box);
	}
	vectRawBox->insertElementAt(box, index);
	if (listener.get() != NULL)
	{
	   box->setListener(listener);
	}
	if (selStyle.get() != NULL)
	{
	   box->setSelStyle(selStyle);
	}
}

void RichText::setWidth(int width)
{
	Component::setWidth(width);
	initBox();
}

void RichText::initBox()
{
	if (vectRawBox.get() == NULL || widthForRowCalculations != getWidth())
	{
		layoutBox();
		setShouldCalcPreferredSize(true);
	}
}

void RichText::layoutBox()
{
	if (vectRawBox.get() != NULL && vectRawBox->size() == 0)
		return;

	widthForRowCalculations = getWidth();
	vectRowBox->removeAllElements();
	rows = 0;
	curRowX = 0;
	curRowBox = new RichText::RowBox();
	//		selectedIndex = 0;
	/*
	* if(vectFoucusabelBox.size() > 0){ Box box =
	* (Box)vectFoucusabelBox.elementAt(0); box.setSelected(true); }
	*/
	shared_ptr<Style> style = getStyle();
	shared_ptr<Font> font = style->getFont();
	// to check TextArea类不存在
	int charWidth = 10;// = font->charWidth(TextArea::getWidestChar());
	int textAreaWidth = getWidth() - style->getPadding(RIGHT)
		- style->getPadding(LEFT);
	if (textAreaWidth <= 0)
	{
		textAreaWidth = 10 * charWidth;
	}

	// if there is any possibility of a scrollbar we need to reduce the
	// textArea
	// width to accommodate it
	if (this->isScrollVisible())
	{
		textAreaWidth -= UIManager::getInstance()->getLookAndFeel()
			->getVerticalScrollWidth();
	}
	if (textAreaWidth <= 0)
	{
		textAreaWidth = 10 * charWidth;
	}

	/*
	* iteration over the String using indexes, from - the beginning of the
	* row , to - end of a row for each row we will try to search for a
	* "space" character at the end of the row ( row is text area available
	* width) indorder to improve the efficiency we do not search an entire
	* row but we start from minCharactersInRow which indicates what is the
	* minimum amount of characters that can feet in the text area width. if
	* we dont find we will go backwards and search for the first space
	* available, if there is no space in the entire row we will cut the
	* line inorder to fit in.
	*/

	// Don't rely on the fact that short text has no newline character. we
	// always have to parse the text.
	for (int i = 0; i < vectRawBox->size(); i++) {
		shared_ptr<Box> box = vectRawBox->elementAt(i);
		box->setLineStart(-1);
		box->setLineEnd(-1);
		if (box->getType() == TEXT)
		{
			if(!layoutText(box, textAreaWidth))
				break;
		} 
		else if (box->getType() == LINK) 
		{
			if(!layoutText(box, textAreaWidth))
				break;
		}
		else if (box->getType() == IMAGE)
		{
			layoutImage(box, textAreaWidth);
		}
	}
	lineBreak();
}

int RichText::indexOf(shared_ptr<String> t, char c, int offset, int length)
{
	for (int iter = offset; iter < t->size() && iter < offset + length; iter++)
	{
		if ((*t)[iter] == c)
		{
			return iter;
		}
	}
	return -1;
}

bool RichText::fastCharWidthCheck(shared_ptr<String> chrs, int off, int length,
						int width, int charWidth, shared_ptr<Font> f)
{
	if (length * charWidth < width)
	{
	   return true;
	}
	return f->charsWidth(chrs, off, length) < width;
}

void RichText::layoutImage(shared_ptr<Box> box, int textAreaWidth)
{
	Image* img = dynamic_cast<Image*>(box->getObject().get());
	if (img == NULL)
	{
		return;
	}
	shared_ptr<Image> image = dynamic_pointer_cast<Image>(box->getObject());
	int widthImage = image->getWidth();
	int heightImage = image->getHeight();

	if (curRowX > 0 && textAreaWidth - curRowX < widthImage)
	{
		lineBreak();
	}
	shared_ptr<PaintBox> paintBox = new PaintBox(box, image);
	paintBox->setWidth(widthImage);
	curRowBox->addPaintBox(paintBox);
	if (curRowBox->getHeight() < heightImage)
	{
		curRowBox->setHeight(heightImage);
	}
	curRowX += widthImage;
	if (curRowX >= textAreaWidth) 
	{
		lineBreak();
	}
}

bool RichText::layoutText(shared_ptr<Box> box, int textAreaWidth)
{
	String* str = dynamic_cast<String*>(box->getObject().get());
	//if (!(typeid(box->getObject().get()) ==  typeid(shared_ptr<String>)))
	if(str == NULL)
	{
		return true;
	}
	// to check 
	GUI_CHAR* text = (dynamic_pointer_cast<String>(box->getObject()))->toCharArray();
	int textLength = wcslen(text);

	shared_ptr<String> unsupported = getUnsupportedChars();
	shared_ptr<Font> font = this->getStyle()->getFont();
	// to check TextArea类不存在
	int charWidth = 10; //font->charWidth(TextArea::getWidestChar());
	int minCharactersInRow = max(1, (textAreaWidth - curRowX)
		/ charWidth);
	int rowIndex = 0;
	int from = 0;
	int to = from + minCharactersInRow;

	shared_ptr<String> rowText;
	int i, spaceIndex;
	to = max(min(textLength - 1, to), 0);

	while (to < textLength)
	{

		if (to > textLength)
		{
			to = textLength;
		}

		spaceIndex = -1;
		rowText = new String(L"");
		int maxLength = to;

		// search for "space" character at close as possible to the end of
		// the row
		// to check
		shared_ptr<String> txtString= new String(text);
		for (i = to; i < textLength
			&& fastCharWidthCheck(txtString, from, i - from + 1,
			textAreaWidth - curRowX, charWidth, font); i++)
		{
				GUI_CHAR c = text[i];
				if (unsupported->indexOf(c) > -1)
				{
					text[i] = ' ';
					c = ' ';
				}
				// modified by jiajing for allow space
				if (c == '\n')
				{
					spaceIndex = i;
					// newline has been found. We can end the loop here as the
					// line cannot grow more
					if (c == '\n')
						break;
				}
				maxLength++;
		}
		// if we got to the end of the text use the entire row,
		// also if space is next character (in the next row) we can cut the
		// line
		if (i == textLength || text[i] == ' ' || text[i] == '\n') {
			spaceIndex = i;
		}
		//
		// else if (!fastCharWidthCheck(text, from, i - from, textAreaWidth,
		// charWidth, font) ){ maxLength --; i --; }
		//
		// if we found space in the limit width of the row (searched only
		// from minCharactersInRow)
		shared_ptr<String> newLineString = new String(text);
		if (spaceIndex != -1) {
			// make sure that if we have a newline character before the end
			// of the line we should
			// break there instead
			int newLine = indexOf(newLineString, '\n', from, spaceIndex - from);
			if (newLine > -1 && newLine < spaceIndex)
			{
				spaceIndex = newLine;
			}

			rowText = new String(text, from, spaceIndex - from);
			from = spaceIndex + 1;

		} // if there is no space from minCharactersInRow to limit need to
		// search backwards
		else {
			for (i = to; spaceIndex == -1 && i >= from; i--) {
				GUI_CHAR chr = text[i];
				// modified by jiajing for allow space
				if (chr == '\n' || chr == '\t') {
					spaceIndex = i;

					// don't forget to search for line breaks in the
					// remaining part. otherwise we overlook possible
					// line breaks!
					int newLine = indexOf(newLineString, '\n', from, i - from);
					if (newLine > -1 && newLine < spaceIndex) {
						spaceIndex = newLine;
					}
					rowText = new String(text, from, spaceIndex - from);
					from = spaceIndex + 1;
				}

			}
			if (spaceIndex == -1) {
				// from = to + 1;
				if (maxLength <= 0) {
					maxLength = 1;
				}
				spaceIndex = maxLength;
				rowText = new String(text, from, spaceIndex - from);
				from = spaceIndex;
			}
		}
		shared_ptr<PaintBox> paintBox = new PaintBox(box, rowText);
		// to check font->stringWidth的接口不统一
		paintBox->setWidth(font->stringWidth(rowText));
		curRowBox->addPaintBox(paintBox);
		if (curRowBox->getHeight() < font->getHeight())
		{
			curRowBox->setHeight(font->getHeight());
		}
		if (box->getLineStart() == -1)
		{
			box->setLineStart(rows);
		}
		box->setLineEnd(rows);
		if (i == textLength) {
			// to check  font->stringWidth(rowText)接口不统一
			curRowX += font->stringWidth(rowText);
			if (curRowX >= textAreaWidth) {
				// line break
				if(!lineBreak())
					return false;
			}
		} else {
			// line break
			if(!lineBreak())
				return false;
		}
		// rowStrings.addElement(rowText);
		// adding minCharactersInRow doesn't work if what is left is less
		// then minCharactersInRow
		to = from;// +minCharactersInRow;
		rowIndex++;
	
	}
	return true;
}

bool RichText::lineBreak()
{
	if(rows >= maxRowSize && maxRowSize > 0)
	{
		moreRows = true;
		return false;
	}
	if (!vectRowBox->contains(curRowBox))
	{
		vectRowBox->addElement(curRowBox);
	}
	curRowX = 0;
	curRowBox = new RowBox();
	rows++;

	return true;
}

shared_ptr<Dimension> RichText::calcPreferredSize()
{
	int prefW = this->getWidth();
	int prefH = 0;

	// if this is a text field the preferred size should be the text width
	for (int i = 0; i < vectRowBox->size(); i++)
	{
		shared_ptr<RowBox> box = vectRowBox->elementAt(i);
		prefH += box->getHeight() + getRowsGap();
	}
	shared_ptr<Dimension> dimension = new Dimension(prefW + getStyle()->getPadding(Component::RIGHT)
		+ getStyle()->getPadding(Component::LEFT), prefH
		+ getStyle()->getPadding(Component::TOP)
		+ getStyle()->getPadding(Component::BOTTOM));
	return dimension;
}

shared_ptr<Dimension> RichText::calcScrollSize()
{
	return calcPreferredSize();
}

/**
* Add an action listener which is invoked when the text area was modified
* not during modification. A text <b>field</b> might never fire an action
* event if it is edited in place and the user never leaves the text field!
* 
* @param a
*            actionListener
*/
void RichText::addActionListener(shared_ptr<ActionListener> a)
{
	if (actionListeners.get() == NULL)
	{
		actionListeners = new Vector<shared_ptr<ActionListener> >();
	}
	if (!actionListeners->contains(a))
	{
		actionListeners->addElement(a);
	}
}

/**
* Removes an action listener
* 
* @param a
*            shared_ptr<ActionListener>
*/
void RichText::removeActionListener(shared_ptr<ActionListener> a)
{
	if (actionListeners.get() == NULL)
	{
		actionListeners = new Vector<shared_ptr<ActionListener> >();
	}
	actionListeners->removeElement(a);
}

/**
* Notifies listeners of a change to the text area
*/
void RichText::fireActionEvent()
{
	if (actionListeners.get() != NULL)
	{
		shared_ptr<ActionEvent> evt = new ActionEvent(this->shared_from_this());
		for (int iter = 0; iter < actionListeners->size(); iter++)
		{
			shared_ptr<ActionListener> a = actionListeners->elementAt(iter);
			a->actionPerformed(evt);
		}
	}
}

void RichText::paint(shared_ptr<Graphics> g)
{
	shared_ptr<LookAndFeel> look = UIManager::getInstance()->getLookAndFeel();

	look->setFG(g, this->shared_from_this());
	int line = vectRowBox->size();
	int oX = g->getClipX();
	int oY = g->getClipY();
	int oWidth = g->getClipWidth();
	int oHeight = g->getClipHeight();
	shared_ptr<Font> f = getStyle()->getFont();
	int fontHeight = f->getHeight();
	int drawLine = 0;
	int firstLine = 0;

	int y = getY() + getStyle()->getPadding(Component::TOP);

	for (int i = 0; i < line; i++)
	{
		shared_ptr<RowBox> rowBox = vectRowBox->elementAt(i);
		rowBox->setY(y - getY());
		int rowHeight = rowBox->getHeight() + getRowsGap();
		if (i == 0)
		{
			rowHeight -= getRowsGap();
		}
		int x = getX() + getStyle()->getPadding(Component::LEFT);

		if (Rectangle::intersects(x, y, getWidth(), rowBox->getHeight(), oX,
			oY, oWidth, oHeight))
		{

				for (int j = 0; j < rowBox->getPaintBoxCount(); j++)
				{
					shared_ptr<PaintBox> paintBox = rowBox->getPaintBoxAt(j);
					paintBox->setX(x - getX());
					paintBox->setY(y - getY());
					paintBox->setHeight(rowHeight);
					int type = paintBox->getRawBox()->getType();
					if (paintBox->getRawBox()->getSelected())
					{
						g->setColor(paintBox->getRawBox()->getSelStyle()
							->getFgColor());
					}
					else
					{
						g->setColor(this->getStyle()->getFgColor());
					}
					if (type == TEXT)
					{
						//  to check g->drawString 接口不统一
						g->drawString(dynamic_pointer_cast<String>(paintBox->getObject()), x, y);
					} 
					else if (type == LINK)
					{
						shared_ptr<String> displayText = dynamic_pointer_cast<String>(paintBox->getObject());
						g->drawString(displayText, x, y);
						g->drawLine(x, y + f->getHeight(), x
							+ paintBox->getWidth(), y + fontHeight);
					} 
					else if (type == IMAGE)
					{
						g->drawImage(dynamic_pointer_cast<Image>( paintBox->getObject()), x, y);
					}
					x += paintBox->getWidth();
				}

				if (drawLine == 0)
				{
					topLineIndex = firstLine = i;
				}
				drawLine++;
				bottomLineIndex = i;
		}
		y += rowHeight;

	}

	if(this->hasMoreRows())
	{
		// to check to do ExLookAndFeel不存在
		shared_ptr<Image> moreImage; // = ((shared_ptr<ExLookAndFeel>)UIManager::getInstance()->getLookAndFeel())->getMoreImage();
		g->drawImage(moreImage, getX() + getWidth() -
			moreImage->getWidth()-5-getStyle()->getPadding(Component::RIGHT),
			getY() + getHeight() - moreImage->getHeight() - getRowsGap());
	}
	// bottomLineIndex = topLineIndex + drawLine - 1;
	/*
	* if( ta.getIsShowMore() && moreImage!= null && firstLine + drawLine <
	* line){ g.drawImage(moreImage, ta.getX() + ta.getWidth() -
	* moreImage.getWidth()-5-ta.getStyle().getPadding(Component.RIGHT),
	* ta.getY() + ta.getHeight() - moreImage.getHeight()); }
	*/
}

bool RichText::isScrollableY()
{
	return isFocusable() && getScrollDimension()->getHeight() > getHeight();
	//	return true;
}

bool RichText::isBoxInScreen(shared_ptr<Box> box)
{
	return (box->getLineStart() >= topLineIndex &&
		box->getLineStart() <= bottomLineIndex) ||
		(box->getLineEnd() >= topLineIndex &&
		box->getLineEnd() <= bottomLineIndex) ;
}

void RichText::focusGainedInternal()
{
	if(focused)
	{
		setHandlesInput(true);
		return;
	}
	focused = true;
	Component::focusGainedInternal();
	setHandlesInput(true);
	int game = Display::getInstance()->getGameAction(Display::getInstance()->getLastKeyCode());
	if (game == Display::GAME_DOWN)
	{
		selectedIndex = -1;
	} 
	else if (game == Display::GAME_UP) 
	{
		selectedIndex = vectFoucusabelBox->size();
	}
}

/**
* @inheritDoc
*/
void RichText::focusLostInternal()
{
	focused = false;
	Component::focusLostInternal();
	setHandlesInput(false);
	shared_ptr<Box> selBox = getFocusBox();
	if (selBox.get() != NULL)
	{
		selBox->setSelected(false);
	}
	selectedIndex = -1;
}

shared_ptr<RichText::Box> RichText::getFocusBox()
{
	shared_ptr<Box> selBox;
	if (selectedIndex < vectFoucusabelBox->size() && selectedIndex >= 0)
		selBox =  vectFoucusabelBox->elementAt(selectedIndex);
	if(/*!this.isScrollVisible()&&*/ selBox.get() != NULL )
	{
		if(!isBoxInScreen(selBox))
		{
			shared_ptr<RichText::Box> nullBox; 
			return nullBox;
		}
	}
	return selBox;
}

void RichText::keyPressed(int keyCode)
{
	Component::keyPressed(keyCode);

	int action = Display::getInstance()->getGameAction(keyCode);

	// scroll the TextArea
	shared_ptr<Rectangle> rect = new Rectangle(getScrollX(), getScrollY(), getWidth(),
		getHeight());
	shared_ptr<RichText::Box> selBox = getFocusBox();

	shared_ptr<RichText> richTextSp = this->shared_from_this();

	if (action == Display::GAME_DOWN) {
		shared_ptr<RowBox> upRow;
		shared_ptr<RowBox> nextRow;
		if (topLineIndex + 1 < vectRowBox->size())
			upRow = vectRowBox->elementAt(topLineIndex + 1);

		if (bottomLineIndex + 1 < vectRowBox->size())
			nextRow =  vectRowBox->elementAt(bottomLineIndex + 1);

		if (selectedIndex + 1 >= 0
			&& selectedIndex + 1 < vectFoucusabelBox->size())
		{

				shared_ptr<Box> box = vectFoucusabelBox->elementAt(selectedIndex + 1);
				if (isBoxInScreen(box)) {
					if (selBox.get() != NULL)
					{
						selBox->setSelected(false);
					}
					box->setSelected(true);
					selectedIndex++;
					repaint();
					return;
				}
				if (box->getLineStart() == bottomLineIndex + 1) {
					if (selBox.get() != NULL)
					{
						selBox->setSelected(false);
					}
					box->setSelected(true);
					selectedIndex++;
					if (upRow.get() != NULL && isScrollableY())
					{
						rect->setY(upRow->getY());

						scrollRectToVisible(rect, static_pointer_cast<Component>(richTextSp));
						return;
					}
				}
		}
		if (isScrollableY()) {
			if (upRow.get() != NULL && nextRow.get() != NULL)
			{
				rect->setY(upRow->getY());
				scrollRectToVisible(rect, static_pointer_cast<Component>(richTextSp));
			} 
			else if (getScrollY() + getHeight() < calcScrollSize()->getHeight())
			{
					rect->setY(calcScrollSize()->getHeight() - getHeight());
					scrollRectToVisible(rect, static_pointer_cast<Component>(richTextSp));
			}
		} else{
			
			setHandlesInput(false);
		}
	} 
	else if (action == Display::GAME_UP)
	{
		shared_ptr<RowBox> upRow;
		if (topLineIndex - 1 >= 0)
		{
			upRow =  vectRowBox->elementAt(topLineIndex - 1);
		}
		if (selectedIndex - 1 >= 0
			&& selectedIndex - 1 < vectFoucusabelBox->size())
		{
				shared_ptr<Box> box = vectFoucusabelBox->elementAt(selectedIndex - 1);
				if (isBoxInScreen(box)) {
					if (selBox.get() != NULL)
						selBox->setSelected(false);
					box->setSelected(true);
					selectedIndex--;
					repaint();
					return;
				}
				if (box->getLineEnd() == topLineIndex - 1) {
					if (selBox.get() != NULL)
						selBox->setSelected(false);
					box->setSelected(true);
					selectedIndex--;
					if (upRow.get() != NULL && isScrollableY())
					{
						rect->setY(upRow->getY());
						scrollRectToVisible(rect, static_pointer_cast<Component>(richTextSp));
						return;
					}
				}
		}
		if(selBox.get() != NULL  && selectedIndex == 0 )
		{
			selBox->setSelected(false);
			selectedIndex = -1;
			repaint();
		}
		if (isScrollableY()) {
			if (upRow.get() != NULL ) {
				rect->setY(upRow->getY());
				scrollRectToVisible(rect, static_pointer_cast<Component>(richTextSp));
			}
		} else{			
			setHandlesInput(false);
		}
	} 

}

void RichText::keyReleased(int keyCode)
{
	int action = Display::getInstance()->getGameAction(keyCode);

	if (action ==Display::GAME_FIRE)
	{
		shared_ptr<RichText::Box> selBox = getFocusBox();
		if(selBox.get() != NULL){
			if (selBox->getListener().get() != NULL ) {
				shared_ptr<ActionEvent> evt = new ActionEvent(this->shared_from_this(), keyCode);
				selBox->getListener()->actionPerformed(evt);
			}
		}
		else{
			onClick();
		}

	}
}

void RichText::onClick()
{
}

shared_ptr<RichText::Box> RichText::pointerSelectBox(int x, int y)
{
	shared_ptr<RichText::RowBox> rowBox;
	int i = topLineIndex;

	for (; i <= bottomLineIndex; i++) {
		rowBox = vectRowBox->elementAt(i);
		if (rowBox->getY() < y && rowBox->getY() + rowBox->getHeight() > y)
		{
			for (int j = 0; j < rowBox->getPaintBoxCount(); j++)
			{
				shared_ptr<PaintBox> paintBox = rowBox->getPaintBoxAt(j);
				if (paintBox->getX() <= x
					&& paintBox->getX() + paintBox->getWidth() > x)
				{
						return paintBox->getRawBox();
				}
			}
			break;
		}
	}
	shared_ptr<RichText::Box> nullBox;
	return nullBox ;
}

void RichText::pointerReleased(int x, int y)
{
	// prevent a drag operation from going into edit mode
	if (isDragActivated())
	{
		Component::pointerReleased(x, y);
	} 
	else 
	{
		Component::pointerReleased(x, y);
		/*
		* if(isEditable()){ onClick(); }
		*/
		shared_ptr<RichText::Box> box = pointerSelectBox(x - this->getAbsoluteX(), y
			- this->getAbsoluteY());
		if (box.get() != NULL  && box->Focusable())
		{
			shared_ptr<RichText::Box> selBox = getFocusBox();
			if(selBox.get() != NULL )
			{
				selBox->setSelected(false);
			}
			box->setSelected(true);
			selectedIndex = vectFoucusabelBox->indexOf(box);
			repaint();
			if (box->getListener().get() != NULL )
			{
				shared_ptr<ActionEvent> evt = new ActionEvent(this->shared_from_this(), 0);
				box->getListener()->actionPerformed(evt);
				return;
			}
		}
		// to check Form中不存在getLastPointFocused
		RichText* richtext = dynamic_cast<RichText*>(Display::getInstance()->getCurrent()->getLastPointFocused().get());
		//if (typeid(Display::getInstance()->getCurrent()->getLastPointFocused()) == typeid(shared_ptr<RichText>))
		if(richtext != NULL)
		{
			onClick();
		}
	}
}

void RichText::pointerPressed(int x, int y)
{
	Component::pointerPressed(x, y);
	if (this->isScrollVisible())
	{
		pointerPressedVerticalScroll(x, y);
	}
}

shared_ptr<RichText> RichText::newV( shared_ptr<String> uid /*= new String(L"RichText")*/ )
{
	RichText* rt = new RichText();
	rt->constructV(uid);
	return rt;
}

RichText::RichText()
{

}
__GUI_END_NAMESPACE
