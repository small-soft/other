#ifndef __DEFAULT_LOOK_AND_FEEL_H__
#define __DEFAULT_LOOK_AND_FEEL_H__

#include "inc/FocusListener.h"
#include "inc/LookAndFeel.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class DefaultLookAndFeel: public LookAndFeel,public FocusListener,public enable_shared_from_this<DefaultLookAndFeel>
{
public:
	DefaultLookAndFeel(void);
	virtual ~DefaultLookAndFeel(void);
private:
	shared_ptr<VectorArray<shared_ptr<Image> > > chkBoxImages ;
	shared_ptr<Image> comboImage ;
	shared_ptr<VectorArray<shared_ptr<Image> > > rButtonImages;
	bool tickWhenFocused;// = true;
public:
	virtual void bind(shared_ptr<Component> cmp);
	void setTickWhenFocused(bool tickWhenFocused);
	void setCheckBoxImages(shared_ptr<Image> checked, shared_ptr<Image> unchecked);
	void setComboBoxImage(shared_ptr<Image> picker);
	void setRadioButtonImages(shared_ptr<Image> selected, shared_ptr<Image> unselected);
	virtual shared_ptr<VectorArray<shared_ptr<Image> > > getRadioButtonImages() ;
	virtual shared_ptr<VectorArray<shared_ptr<Image> > > getCheckBoxImages();
	virtual void drawButton(shared_ptr<Graphics> g, shared_ptr<Button> b);
	virtual void drawCheckBox(shared_ptr<Graphics> g, shared_ptr<Button> cb);
	virtual void drawLabel(shared_ptr<Graphics> g, shared_ptr<Label> l);
	virtual void drawRadioButton(shared_ptr<Graphics> g, shared_ptr<Button> rb);
	virtual void drawComboBox(shared_ptr<Graphics> g, shared_ptr<List> cb);
	virtual void drawList(shared_ptr<Graphics> g, shared_ptr<List> l);
	virtual void drawTextArea(shared_ptr<Graphics> g, shared_ptr<TextArea> ta);
	virtual shared_ptr<Dimension> getButtonPreferredSize(shared_ptr<Button> b);
	virtual shared_ptr<Dimension> getCheckBoxPreferredSize(shared_ptr<Button> cb);
	virtual shared_ptr<Dimension> getLabelPreferredSize(shared_ptr<Label> l);
	virtual shared_ptr<Dimension> getListPreferredSize(shared_ptr<List> l);
	virtual shared_ptr<Dimension> getRadioButtonPreferredSize(shared_ptr<Button> rb) ;
	virtual shared_ptr<Dimension> getTextAreaSize(shared_ptr<TextArea> ta, bool pref);
	virtual shared_ptr<Dimension> getComboBoxPreferredSize(shared_ptr<List> cb);
	virtual void drawTabbedPane(shared_ptr<Graphics> g, shared_ptr<TabbedPane> tp); 
	virtual shared_ptr<Component> getTabbedPaneCell( shared_ptr<TabbedPane> tp,
		shared_ptr<String> text, shared_ptr<Image> icon,  bool isSelected,
		bool cellHasFocus,  shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle,
		shared_ptr<Style> tabbedPaneStyle,  int cellOffsetX,
		int cellOffsetY,   shared_ptr<Dimension> cellsPreferredSize,
		shared_ptr<Dimension> contentPaneSize);
	virtual void drawTabbedPaneContentPane(shared_ptr<TabbedPane> tp,
		shared_ptr<Graphics> g, shared_ptr<Rectangle> rect,
		shared_ptr<Dimension> cellsPreferredSize,  int numOfTabs,
		 int selectedTabIndex,  shared_ptr<Dimension> tabsSize,
		 int cellOffsetX,  int cellOffsetY);
	virtual void drawTextField(shared_ptr<Graphics> g, shared_ptr<TextField> ta) ;
	virtual shared_ptr<Dimension> getTextFieldPreferredSize(shared_ptr<TextArea> ta);
	void drawTextFieldCursor(shared_ptr<Graphics> g, shared_ptr<TextArea> ta); 
	virtual void focusGained(shared_ptr<Component> cmp);
	virtual void focusLost(shared_ptr<Component> cmp);
private:
	static void fillCheckbox(shared_ptr<Graphics> g, int width, int height);
	static int round(float x) ;
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Label> l, shared_ptr<Vector<shared_ptr<Image> > > icons, shared_ptr<Image> stateImage);
	int reverseAlignForBidi(shared_ptr<Component> c, int align) ;
	void drawComponent(shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<Image> icon, shared_ptr<Image> stateIcon, int preserveSpaceForState) ;
	int drawLabelStringValign(shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> str, int x, int y,
		int iconStringHGap, int iconHeight, int textSpaceW, int fontHeight, int preserveSpaceForState);
	int drawLabelString(shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> text, int x, int y, int textSpaceW, int preserveSpaceForState);
	void updateCellLook(shared_ptr<TabbedPane> tp, shared_ptr<Component> c, bool selected);
	bool isRTLOrWhitespace(char c);
	int getTextFieldCursorX(shared_ptr<TextArea> ta);
protected:
	static int scaleCoordinate(float coordinate, float plain, int pixelSize);
	int findDestColor(int color);
	int drawLabelText(shared_ptr<Graphics> g, shared_ptr<Label> l, shared_ptr<String> text, int x, int y, int textSpaceW);
	shared_ptr<String> getTextFieldString(shared_ptr<TextArea> ta);
};

class TabbedPaneCellLabel : public Label
{

public:
	void paint(shared_ptr<Graphics> g);

public:
	static shared_ptr<TabbedPaneCellLabel> newV(shared_ptr<TabbedPane> tp, shared_ptr<String> text, bool isSelected, bool cellHasFocus,
		shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle, shared_ptr<Style> tabbedPaneStyle,
		int cellOffsetX, int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize, shared_ptr<Dimension> contentPaneSize );
	virtual ~TabbedPaneCellLabel() {}
protected:
	TabbedPaneCellLabel();

	void constructV(shared_ptr<TabbedPane> tp, shared_ptr<String> text, bool isSelected, bool cellHasFocus,
		shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle, shared_ptr<Style> tabbedPaneStyle,
		int cellOffsetX, int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize, shared_ptr<Dimension> contentPaneSize );

private:
	shared_ptr<TabbedPane> tp;
	bool isSelected;
	bool cellHasFocus;
	shared_ptr<Style> cellStyle;
	shared_ptr<Style> cellSelectedStyle;
	shared_ptr<Style> tabbedPaneStyle;
	int cellOffsetX;
	int cellOffsetY;
	shared_ptr<Dimension> cellsPreferredSize;
	shared_ptr<Dimension> contentPaneSize;
	
};

__GUI_END_NAMESPACE

#endif
