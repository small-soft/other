#ifndef __GUI_RICH_TEXT_H__
#define __GUI_RICH_TEXT_H__


#include "inc/component.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class ActionListener;
class Font;

class RichText : public Component
{
	AM_DECLARE_DYNAMIC(RichText)
	
public:
	static const int TEXT = 0;
	static const int LINK = 1;
	static const int IMAGE = 2;
	shared_ptr<RichText> shared_from_this();
	class Box
	{
	private:
		int lineStart;
		int lineEnd;
		int type;
		bool focusable;
		bool isSelected;
		shared_ptr<Object> object;
		shared_ptr<ActionListener> listener;
		shared_ptr<Style> selStyle;
		shared_ptr<RichText> richText;
	public:
		Box(int type, bool focusable, shared_ptr<Object> object, shared_ptr<RichText> richText);
		Box(shared_ptr<RichText> richText);
		virtual ~Box() {}
		void setLineStart(int line) 
		{
			lineStart = line;
		}

		void setLineEnd(int line) 
		{
			lineEnd = line;
		}

		int getLineStart() 
		{
			return lineStart;
		}

		int getLineEnd() 
		{
			return lineEnd;
		}

		int getType() 
		{
			return type;
		}

		shared_ptr<Object> getObject() 
		{
			return object;
		}

		bool Focusable() 
		{
			return focusable;
		}

		void setSelected(bool b) 
		{
			isSelected = b;
		}

		bool getSelected() 
		{
			return this->isSelected;
		}

		shared_ptr<ActionListener> getListener() 
		{
			return this->listener;
		}

		void setListener(shared_ptr<ActionListener> listener) {
			this->listener = listener;
		}

		void setSelStyle(shared_ptr<Style> style) {
			this->selStyle = style;
		}

		shared_ptr<Style> getSelStyle() {
			return this->selStyle;
		}
	};

	class PaintBox 
	{
	private:
		shared_ptr<Box> rawBox;
		shared_ptr<Object> object;
		int x;
		int y;
		int width;
		int height;

	public:
		PaintBox(int x, int y, shared_ptr<Box> box, shared_ptr<Object> object);
		PaintBox(shared_ptr<Box> box, shared_ptr<Object> object);
		virtual ~PaintBox() {}
		void setX(int x)
		{
			this->x = x;
		}

		void setY(int y)
		{
			this->y = y;
		}

		int getX()
		{
			return x;
		}

		int getY()
		{
			return y;
		}

		shared_ptr<Box> getRawBox()
		{
			return rawBox;
		}

		shared_ptr<Object> getObject()
		{
			return object;
		}

		int getWidth()
		{
			return width;
		}

		void setWidth(int width)
		{
			this->width = width;
		}

		int getHeight()
		{
			return height;
		}

		void setHeight(int height)
		{
			this->height = height;
		}
	};

	class RowBox 
	{
	private:
		int height;
		int y;
		shared_ptr<Vector<shared_ptr<PaintBox> > >  vectPaintBox;
	public:
		RowBox();
		virtual ~RowBox() {}
		void addPaintBox(shared_ptr<PaintBox> box)
		{
			vectPaintBox->addElement(box);
		}

		shared_ptr<PaintBox> getPaintBoxAt(int index)
		{
			return  vectPaintBox->elementAt(index);
		}

		int getPaintBoxCount()
		{
			return vectPaintBox->size();
		}

		void setHeight(int height)
		{
			this->height = height;
		}

		int getHeight()
		{
			return height;
		}

		void setY(int y)
		{
			this->y = y;
		}

		int getY() 
		{
			return y;
		}
	};

private:
	int linesToScroll;
	/**
	* Unsupported characters is a String that contains characters that cause
	* issues when rendering on some problematic fonts. The rendering engine can
	* thus remove them when drawing.
	*/
	shared_ptr<String> unsupportedChars; 
	int rows;
	shared_ptr<Vector<shared_ptr<Box> > > vectRawBox;
	shared_ptr<Vector<shared_ptr<Box> > > vectFoucusabelBox;
	shared_ptr<Vector<shared_ptr<RowBox> > > vectRowBox;
	int widthForRowCalculations;
	int rowsGap;
	shared_ptr<Vector<shared_ptr<ActionListener> > > actionListeners;
	bool focused; 
	// add by jiajing
	bool isShowMore;
	// private int calcHeight;
	int curRowX;
	shared_ptr<RowBox> curRowBox;
	int selectedIndex;
	int topLineIndex;
	int bottomLineIndex;
	int maxRowSize;
	bool moreRows;

public:
	static shared_ptr<RichText> newV(shared_ptr<String> uid = new String(L"RichText"));
	virtual ~RichText(void);
protected:
	RichText();
	void constructV(shared_ptr<String> uid);
public:
	void setIsShowMore(bool b) { this->isShowMore = b; }
	bool getIsShowMore() { return isShowMore; }
	void setMaxRowSize(int n){ maxRowSize = n; }
	bool hasMoreRows(){ return moreRows; }
	int getRowsGap() { return rowsGap; }

	shared_ptr<String> getUnsupportedChars() { return unsupportedChars; }

	virtual void addBox(int type, shared_ptr<Object> object);
	virtual void addBox(int type, bool focusable, shared_ptr<Object> object);
	virtual void addBox(int type, bool focusable, shared_ptr<Object> object,
		shared_ptr<ActionListener> listener);
	virtual void addBox(int type, bool focusable, shared_ptr<Object> object,
		shared_ptr<Style> selStyle);
	virtual void addBox(int type, bool focusable, shared_ptr<Object> object,
		shared_ptr<ActionListener> listener, shared_ptr<Style> selStyle);
	virtual void setWidth(int width);
	/**
	* Add an action listener which is invoked when the text area was modified
	* not during modification. A text <b>field</b> might never fire an action
	* event if it is edited in place and the user never leaves the text field!
	* 
	* @param a
	*            shared_ptr<ActionListener>
	*/
	virtual void addActionListener(shared_ptr<ActionListener> a);

	/**
	* Removes an action listener
	* 
	* @param a
	*            shared_ptr<ActionListener>
	*/
	virtual void removeActionListener(shared_ptr<ActionListener> a);

	/**
	* Notifies listeners of a change to the text area
	*/
	virtual void fireActionEvent();
	virtual void paint(shared_ptr<Graphics> g);
	virtual bool isScrollableY();
	virtual void focusGainedInternal();
	virtual void focusLostInternal();
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);
	virtual void pointerReleased(int x, int y);
	virtual void pointerPressed(int x, int y);

protected:
	virtual void initComponent();
	virtual shared_ptr<Dimension> calcPreferredSize();
	virtual shared_ptr<Dimension> calcScrollSize();
	virtual void onClick();
private:
	void insertBox(int type, bool focusable, shared_ptr<Object> object,
		int index, shared_ptr<ActionListener> listener, shared_ptr<Style> selStyle);
	void initBox();
	void layoutBox();
	int indexOf(shared_ptr<String> t, char c, int offset, int length);
	bool fastCharWidthCheck(shared_ptr<String> chrs, int off, int length,
		int width, int charWidth, shared_ptr<Font> f);
	void layoutImage(shared_ptr<Box> box, int textAreaWidth);
	bool layoutText(shared_ptr<Box> box, int textAreaWidth);
	bool lineBreak();
	bool isBoxInScreen(shared_ptr<Box> box);
	shared_ptr<Box> getFocusBox();
	shared_ptr<Box> pointerSelectBox(int x, int y);
};

__GUI_END_NAMESPACE

#endif
