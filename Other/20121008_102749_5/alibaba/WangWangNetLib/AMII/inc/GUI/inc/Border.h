#ifndef __GUI_BORDER_H__
#define __GUI_BORDER_H__

#include "inc/Config.h"
#include "inc/Object.h"
#include "inc/Vector.h"

__GUI_BEGIN_NAMESPACE
class Graphics;
class Component;
class Image;

class Border: public Object, public enable_shared_from_this<Border>
{
public:
	virtual ~Border(void);
	static void deinitialize();
protected:
	Border(void);
private:
	static shared_ptr<Border> defaultBorder;// = Border.createEtchedRaised(0x020202, 0xBBBBBB);
	static shared_ptr<Border> empty;
	static const int TYPE_EMPTY = 0;
	static const int TYPE_LINE = 1;
	static const int TYPE_ROUNDED = 2;
	static const int TYPE_ROUNDED_PRESSED = 3;
	static const int TYPE_ETCHED_LOWERED = 4;
	static const int TYPE_ETCHED_RAISED = 5;
	static const int TYPE_BEVEL_RAISED = 6;
	static const int TYPE_BEVEL_LOWERED = 7;
	static const int TYPE_IMAGE = 8;
public :
	int type;
	shared_ptr<VectorArray<shared_ptr<Image> > >images;

	/**
	* Indicates whether theme colors should be used or whether colors are specified
	* in the border
	*/
	bool themeColors;

	int colorA;
	int colorB;
	int colorC;
	int colorD;
	int thickness;
	int arcWidth;
	int arcHeight;
	bool outline;// = true;
	shared_ptr<Border> pressedBorder;
	shared_ptr<Border> focusBorder;
public :
	static shared_ptr<Border> getEmpty();
	static shared_ptr<Border> createEmpty();
	static shared_ptr<Border> createImageBorder(shared_ptr<Image> top, shared_ptr<Image>bottom, shared_ptr<Image> left, shared_ptr<Image> right,shared_ptr<Image>topLeft, shared_ptr<Image>topRight,
		shared_ptr<Image> bottomLeft, shared_ptr<Image> bottomRight, shared_ptr<Image> background);
	static shared_ptr<Border> createImageBorder(shared_ptr<Image> top, shared_ptr<Image> topLeft, shared_ptr<Image> background) ;
	static shared_ptr<Border> createLineBorder(int thickness);
	static shared_ptr<Border> createLineBorder(int thickness, int color);
	static shared_ptr<Border> createRoundBorder(int arcWidth, int arcHeight);
	static shared_ptr<Border> createRoundBorder(int arcWidth, int arcHeight, bool outline);
	static shared_ptr<Border> createRoundBorder(int arcWidth, int arcHeight, int color) ;
	static shared_ptr<Border> createRoundBorder(int arcWidth, int arcHeight, int color, bool outline);
	static shared_ptr<Border> createEtchedLowered();
	static shared_ptr<Border> createEtchedLowered(int highlight, int shadow);
	static shared_ptr<Border> createEtchedRaised() ;
	static shared_ptr<Border> createEtchedRaised(int highlight, int shadow);
	bool isBackgroundPainter() ;
	static shared_ptr<Border> createBevelLowered();
	static shared_ptr<Border> createBevelLowered(int highlightOuter, int highlightInner,
		int shadowOuter, int shadowInner);
	static shared_ptr<Border> createBevelRaised();
	static shared_ptr<Border> createBevelRaised(int highlightOuter, int highlightInner,
		int shadowOuter, int shadowInner);
	void setPressedInstance( shared_ptr<Border> pressed);
	void setFocusedInstance( shared_ptr<Border> focused);
	shared_ptr<Border> getFocusedInstance();
	shared_ptr<Border> getPressedInstance();
	shared_ptr<Border> createPressedVersion();
	void paintBorderBackground(shared_ptr<Graphics> g, shared_ptr<Component> c);
	void paint(shared_ptr<Graphics> g, shared_ptr<Component> c);
	static void setDefaultBorder( shared_ptr<Border> border);
	static shared_ptr<Border> getDefaultBorder();
	
private :
	int getBackgroundColor(shared_ptr<Component> c);
	void drawImageBorderLine(shared_ptr<Graphics> g, shared_ptr<Image> left, shared_ptr<Image>right, shared_ptr<Image> center, int x, int y, int width);
	void drawImageBorderColumn(shared_ptr<Graphics> g, shared_ptr<Image> top, shared_ptr<Image> bottom, shared_ptr<Image> center, int x, int y, int height);
};

__GUI_END_NAMESPACE

#endif
