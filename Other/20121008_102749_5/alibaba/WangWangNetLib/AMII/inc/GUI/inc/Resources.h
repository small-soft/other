#ifndef _RESOURCES_H
#define _RESOURCES_H

#include "AMFS.h"
#include "inc\InputStream.h"
#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE

class Resources
{
public:
	static const unsigned char MAGIC_THEME_LEGACY = (unsigned char)0xF7;
	static const unsigned char MAGIC_ANIMATION_LEGACY = (unsigned char)0xF8;
	static const unsigned char MAGIC_INDEXED_IMAGE_LEGACY = (unsigned char)0xF4;
	static const unsigned char MAGIC_FONT_LEGACY = (unsigned char)0xF6;
	static const unsigned char MAGIC_INDEXED_FONT_LEGACY = (unsigned char)0xFB;
	static const unsigned char MAGIC_IMAGE_LEGACY = (unsigned char)0xF3;


	static const unsigned char MAGIC_FONT = (unsigned char)0xFC;
	static const unsigned char MAGIC_IMAGE = (unsigned char)0xFD;
	static const unsigned char MAGIC_L10N = (unsigned char)0xF9;
	static const unsigned char MAGIC_DATA = (unsigned char)0xFA;
	static const unsigned char MAGIC_HEADER = (unsigned char)0xFF;
	static const unsigned char MAGIC_THEME = (unsigned char)0xF2;

private:
	short majorVersion;
	short minorVersion;

public:
	static const int BORDER_TYPE_EMPTY = 0;
	static const int BORDER_TYPE_LINE = 1;
	static const int BORDER_TYPE_ROUNDED = 2;
	static const int BORDER_TYPE_ETCHED_LOWERED = 4;
	static const int BORDER_TYPE_ETCHED_RAISED = 5;
	static const int BORDER_TYPE_BEVEL_RAISED = 6;
	static const int BORDER_TYPE_BEVEL_LOWERED = 7;
	static const int BORDER_TYPE_IMAGE = 8;

private:
	shared_ptr<VectorArray<String> > metaData;

	Map<String, unsigned char> resourceTypes;
	Map<String, shared_ptr<Object> > resources;

	shared_ptr<DataInputStream> input; 
public:
	Resources();
	Resources(shared_ptr<InputStream> input);
	void clear();
	void startingEntry(String id, unsigned char magic);
	void openFile(shared_ptr<InputStream> input);

private:
	void readHeader();

public:
	int getMajorVersion();
	int getMinorVersion();
	shared_ptr<VectorArray<String> > getMetaData();
	shared_ptr<VectorArray<String> > getResourceNames();
	shared_ptr<VectorArray<String> > getDataResourceNames();
	void setResource(String id, unsigned char type, shared_ptr<Object> value);

public:
	shared_ptr<VectorArray<String> > getL10NResourceNames();
	shared_ptr<VectorArray<String> > getFontResourceNames();
	shared_ptr<VectorArray<String> > getThemeResourceNames();
	shared_ptr<VectorArray<String> > getImageResourceNames();
	shared_ptr<VectorArray<String> > getAnimationResourceNames();
	unsigned char getResourceType(String name);

private:
	shared_ptr<VectorArray<String> > getResourceTypeNames(unsigned char b);
	static shared_ptr<VectorArray<String> > toStringArray(shared_ptr<Vector<String> > v);

public:
	bool isL10N(String name);
	bool isTheme(String name);
	bool isFont(String name);
	bool isAnimation(String name);
	bool isData(String name);
	bool isImage(String name);

public:
	static shared_ptr<Resources> open(String resource);
	static shared_ptr<Resources> open(shared_ptr<InputStream> resource);

	shared_ptr<Image> getImage(String id);
	//shared_ptr<StaticAnimation> getAnimation(String id);
	shared_ptr<InputStream> getData(String id);
	shared_ptr<Map< String, shared_ptr<Object> > > getL10N(String id, String locale);
	Enumeration<String> listL10NLocales(String id);
	shared_ptr<Font> getFont(String id);
	shared_ptr<Map<String, shared_ptr<Object> > > getTheme(String id);
	shared_ptr<Border> confirmBorder(shared_ptr<Map<String, shared_ptr<Object> > > h, String key);
	shared_ptr<Border> createImageBorder(shared_ptr<Vector<String>  > value);
	shared_ptr<Object> getResourceObject(String res);
	shared_ptr<Image> createImage();
	shared_ptr<VectorArray<unsigned char> > createData();
	shared_ptr<Font> loadFont(shared_ptr<DataInputStream> input, String id, bool packed);
	shared_ptr<Font> loadBitmapFont(shared_ptr<DataInputStream> input, String id, shared_ptr<Font> font);
	shared_ptr<Map<String, shared_ptr<Object> > > loadTheme(String id, bool newerVersion);

private:
	shared_ptr<Object> createBorder(shared_ptr<DataInputStream> input, int type);
	shared_ptr<Object> createBorder(shared_ptr<DataInputStream> input, bool newerVersion);
	shared_ptr<VectorArray<String> > readImageBorder(shared_ptr<DataInputStream> input);
	shared_ptr<Map<String, shared_ptr<Map<String, shared_ptr<Object> > > > > loadL10N();
	shared_ptr<Image> createPackedImage8();
};
__GUI_END_NAMESPACE
#endif
