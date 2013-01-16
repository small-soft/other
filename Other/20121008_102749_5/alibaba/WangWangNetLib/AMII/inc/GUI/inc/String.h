#ifndef __GUI_STRING_H__
#define __GUI_STRING_H__

#include "inc/Object.h"
#include "inc/Config.h"
#include "AMTypes.h"
__GUI_BEGIN_NAMESPACE

typedef AMWChar GUI_CHAR;

class String : public Object
{
public:
	String(GUI_CHAR *str = NULL);
	String(GUI_CHAR *str, int start, int len);
	String(const String &rhs);
	String& operator=(const String &rhs);
	String& operator=(const GUI_CHAR *str);
	virtual ~String();
public:
	GUI_CHAR charAt(int index);
	int indexOf(GUI_CHAR ch);
	int indexOf(String& ch);
	int indexOf(GUI_CHAR* ch);
	int indexOf(GUI_CHAR ch, int fromIndex);
	int length();
	int size();
	bool empty();
	GUI_CHAR *toCharArray();
	String& toUpperCase();
	String& trim();
	String substr(int beginIndex);
	String substr(int beginIndex, int endIndex);
	// add by Duan shaopeng
	void cat(const GUI_CHAR* chars);
	bool operator < (const String& rhs) const;
	bool operator > (const String& rhs) const;
	bool operator == (const String& rhs) const;
	bool operator != (const String& rhs) const;
	String& operator += (const String& rhs);
	String& operator += (const GUI_CHAR* chars);
	GUI_CHAR operator [] (int index) const;
	friend String operator + (const String& rhs1,const String& rhs2);
	friend String operator + (const String& rhs,const GUI_CHAR* chars);
	friend String operator + (const GUI_CHAR* chars,const String& rhs);
	bool endsWith(String suffix);
	virtual shared_ptr<String> toString();
private:
	void freeData();
private:
	GUI_CHAR *m_data;
	int len;
};
__GUI_END_NAMESPACE

#endif
