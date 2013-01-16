#ifndef __COMMON_TRANSITIONS_H__
#define __COMMON_TRANSITIONS_H__

#include "inc/Transition.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Motion;
class RGBImage;
class Image;
class CommonTransitions:public Transition
{
private:
	CommonTransitions(int type);
public:
	virtual ~CommonTransitions(void);
private:
	shared_ptr<Motion> motion;
	static const int TYPE_EMPTY = 0;
	static const int TYPE_SLIDE = 1;
	static const int TYPE_FADE = 2;
public:
	/**
	* Slide the transition horizontally
	* @see #createSlide
	*/
	static const int SLIDE_HORIZONTAL = 0;

	/**
	* Slide the transition vertically
	* @see #createSlide
	*/
	static const int SLIDE_VERTICAL = 1;

private:
	int slideType;
	int speed;
	int position;
	int transitionType;
	shared_ptr<Image> buffer;
	shared_ptr<Image> secondaryBuffer;

	static bool defaultLinearMotion;// = false;
	bool linearMotion;// = defaultLinearMotion;

	/**
	* The transition is a special case where we "keep" an allocated buffer
	*/
	shared_ptr<RGBImage> rgbBuffer;
	bool forward;
	bool drawDialogMenu;

	bool firstFinished;
public:
	 static shared_ptr<CommonTransitions> createEmpty() ;
	 static shared_ptr<CommonTransitions> createSlide(int type, bool forward, int duration, bool drawDialogMenu = false);
	 static shared_ptr<CommonTransitions> createFade(int duration);
	 
	 virtual void initTransition() ;

	 virtual bool animate();
	 virtual void paint(shared_ptr<Graphics> g);

	 virtual shared_ptr<Transition> copy(bool reverse);

	 virtual void cleanup();
	 shared_ptr<Motion> getMotion() ;
	 void setMotion(shared_ptr<Motion> motion);
	  bool isLinearMotion();
	  void setLinearMotion(bool linearMotion);
	  static bool isDefaultLinearMotion();
	  static void setDefaultLinearMotion(bool aDefaultLinearMotion);
private:
	void paintAlpha(shared_ptr<Graphics> graphics);
	void paintSlideAtPosition(shared_ptr<Graphics> g, int slideX, int slideY);
	void paint(shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y);
};

__GUI_END_NAMESPACE

#endif
