#ifndef __LABEL_H__
#define __LABEL_H__

#include "inc/String.h"

#include "inc/Component.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Image;
class Label :public Component
{
	AM_DECLARE_DYNAMIC(Label)
	
public:
	static shared_ptr<Label> newV(shared_ptr<String> text = new String(L""));
	static shared_ptr<Label> newV(shared_ptr<String> text, shared_ptr<String> uiid);
	static shared_ptr<Label> newV(shared_ptr<Image> icon);
	virtual ~Label();
	shared_ptr<Label> shared_from_this();
protected:
	Label();

	void constructV(shared_ptr<String> text = new String(L""));
	void constructV(shared_ptr<String> text, shared_ptr<String> uiid);
	void constructV(shared_ptr<Image> icon);

private:
	shared_ptr<String> text;// = "";

	shared_ptr<Image> icon;

	int align ;//= LEFT;
	int valign;// = BOTTOM;

	int textPosition;// = RIGHT;

	int gap ;//= 2;

	int shiftText ;//= 0;

	bool tickerRunning ;//= false;

	bool tickerEnabled;// = true;

	long tickerStartTime;

	long tickerDelay;

	bool rightToLeft;

    bool endsWith3Points;// = true;
public:
	virtual int getBaselineResizeBehavior();
	void setText(shared_ptr<String> text);
	virtual void initComponentImpl(); 
	shared_ptr<String> getText();
	void setIcon(shared_ptr<Image> icon);
	virtual void checkAnimation();
	shared_ptr<Image> getIcon();
	void setAlignment(int align);
	void setVerticalAlignment(int valign);
	int getVerticalAlignment();
	int getAlignment();
	void setTextPosition(int textPosition);
	int getTextPosition();
	void setGap(int gap);
	int getGap();
	virtual void paint(shared_ptr<Graphics> g);
	virtual shared_ptr<Dimension> calcPreferredSize();
	int getShiftText();
	void setShiftText(int shiftText);
	bool shouldTickerStart() ;
	virtual shared_ptr<Image> getIconFromState();
	virtual int getAvaliableSpaceForText();
	void startTicker(long delay, bool rightToLeft);
	void stopTicker();
	bool isTickerRunning();
	void setTickerEnabled(bool tickerEnabled) ;
	 bool isTickerEnabled();
	 void setEndsWith3Points(bool endsWith3Points);
	 bool isEndsWith3Points();
	 virtual bool animate();
private:
	void localize();
};

__GUI_END_NAMESPACE

#endif

