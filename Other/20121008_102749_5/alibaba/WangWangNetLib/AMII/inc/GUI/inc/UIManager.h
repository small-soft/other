#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "inc/Map.h"
#include "inc/Object.h"
#include "inc/EventDispatcher.h"
#include "inc/Config.h"
#include "inc/String.h"
__GUI_BEGIN_NAMESPACE

class LookAndFeel;
class Style;
class Image;
class String;
class ActionListener;
class Font;



class UIManager: public Object
{
public:
	virtual ~UIManager();
	static void deinitialize();
private:
	UIManager();
private:
	shared_ptr<LookAndFeel> current;// = new DefaultLookAndFeel();

	shared_ptr<Map<String,shared_ptr<Style> > > styles;// = new Hashtable();
	shared_ptr<Map<String,shared_ptr<Style> > > selectedStyles;// = new Hashtable();

	shared_ptr<Map<String,shared_ptr<Object> > > themeProps;

	static shared_ptr<UIManager> instance;// = new UIManager();

	shared_ptr<Style> defaultStyle;// = new Style();
	shared_ptr<Style> defaultSelectedStyle;// = new Style();

	/**
	* This member is used by the resource editor
	*/
	static bool accessible;// = true;

	/**
	* Useful for caching theme images so they are not loaded twice in case 
	* an image reference is used it two places in the theme (e.g. same background
	* to title and menu bar).
	*/
	shared_ptr<Map<String,shared_ptr<Image> > > imageCache;// = new Hashtable();

	/**
	* The resource bundle allows us to implicitly localize the UI on the fly, once its
	* installed all internal application strings query the resource bundle and extract
	* their values from this table if applicable.
	*/
	shared_ptr<Map<String,shared_ptr<Object> > > resourceBundle;

	/**
	* This EventDispatcher holds all listeners who would like to register to
	* Theme refreshed event
	*/
	shared_ptr<EventDispatcher<ActionListener> >  themelisteners;
public:
	static shared_ptr<UIManager> getInstance();
	shared_ptr<LookAndFeel> getLookAndFeel();
	void setLookAndFeel(shared_ptr<LookAndFeel> plaf);
	void setComponentStyle(const  String& id, shared_ptr<Style> style);
	void setComponentSelectedStyle(const  String& id, shared_ptr<Style> style);
	shared_ptr<Style> getComponentStyle(const  String& id);
	shared_ptr<Style> getComponentSelectedStyle(const String& id);
	shared_ptr<Style> getComponentCustomStyle(const String& id, const String& type);
	void setThemeProps(shared_ptr<Map<String,shared_ptr<Object> > > themeProps);
	void addThemeProps(shared_ptr<Map<String,shared_ptr<Object> > > themeProps);
	void setThemePropsImpl(shared_ptr<Map<String,shared_ptr<Object> > > themeProps);
	shared_ptr<Map<String,shared_ptr<Object> > > getResourceBundle();
	void setResourceBundle(shared_ptr<Map<String,shared_ptr<Object> > > resourceBundle) ;
	shared_ptr<String> localize(const String& key, const String& defaultValue);
	shared_ptr<String>localize(GUI_CHAR* key, GUI_CHAR* defaultValue);
	void addThemeRefreshListener(shared_ptr<ActionListener> l);
	void removeThemeRefreshListener(shared_ptr<ActionListener> l);
	shared_ptr<String> getThemeName();

private:
	shared_ptr<Style> getComponentStyleImpl(const String& id, bool selected, const String& prefix);
	void resetThemeProps();

	void buildTheme(shared_ptr<Map<String,shared_ptr<Object> > > themeProps);
	shared_ptr<Style> createStyle(const String& id, const String& prefix, bool selected);
	//void toIntArray(const String& str,int arry[4]) ;
	static shared_ptr<Image> parseImage(const String& value);
	static shared_ptr<Font> parseFont(const String& fontStr);

	shared_ptr<Vector<unsigned char> > transToVec(const char *str);
};

__GUI_END_NAMESPACE

#endif
