#include "AMGui.h"


__GUI_BEGIN_NAMESPACE
String::String(GUI_CHAR *str)
{
	if ( str == NULL )
	{
		m_data = new GUI_CHAR[1] ;
		m_data[0] = L'\0' ;
	}
	else
	{
		int length = AMWcslen((GUI_CHAR*)str);
		m_data = new GUI_CHAR[ length + 1];
		AMWcsncpy(m_data, str, length + 1);
	}
	len = AMWcslen((GUI_CHAR*)m_data);
}

String::String(GUI_CHAR *str, int start, int len)
{
	if ( str == NULL )
	{
		m_data = new GUI_CHAR[1] ;
		m_data[0] = L'\0' ;
		this->len = 0;
	}
	else
	{
		m_data = new GUI_CHAR[len + 1];
		memset(m_data, 0, sizeof(GUI_CHAR)* (len + 1));
		AMWcsncpy((AMWChar*)m_data, (const AMWChar*)(str + start), len);
		this->len = len;
	}
}
String::String(const String &rhs)
{
	int length = AMWcslen((GUI_CHAR*)rhs.m_data);
	m_data = new GUI_CHAR[length + 1];
	AMWcsncpy(m_data, rhs.m_data, length + 1);
	this->len = length;
}
String& String::operator =(const String &rhs)
{
	if ( this == &rhs)
		return *this ;
	
	if(m_data)
	{
		freeData();
	/*	delete []m_data;
		m_data = NULL;*/
	}
	
	int length = AMWcslen((GUI_CHAR*)rhs.m_data);
	m_data = new GUI_CHAR[length + 1];
	AMWcsncpy(m_data,rhs.m_data, length + 1);
	this->len = length;
	return *this ;
}

String& String::operator=( const GUI_CHAR *str )
{
	if(m_data)
	{
	/*	delete []m_data;
		m_data = NULL;*/
		freeData();
	}
	
	if ( str == NULL )
	{
		m_data = new GUI_CHAR[1] ;
		m_data[0] = L'\0' ;
	}
	else
	{
		int length = AMWcslen((GUI_CHAR*)str);
		m_data = new GUI_CHAR[length + 1];
		AMWcsncpy(m_data, str, length + 1);
	}
	return *this ;
}
String::~String()
{
	if(m_data)
		//delete []m_data;
		freeData();
	m_data = NULL;
	len = 0;
}
GUI_CHAR String::charAt(int index)
{
	return m_data[index];
}
int String::indexOf(GUI_CHAR ch)
{
	return indexOf(ch, 0);
}
int String::indexOf(GUI_CHAR ch, int fromIndex)
{
	int index;
	for (index = fromIndex; index < len; ++index)
	{
		if (ch == m_data[index])
		{
			return index;
		}
	}
	return -1;
}

int String::indexOf( String& ch )
{
	return -1;
}

int String::indexOf( GUI_CHAR* ch )
{
	return -1;
}
int String::length()
{
	return len;
}
int String::size()
{
	return len;
}
bool String::empty()
{
	return (len == 0);
}
GUI_CHAR* String::toCharArray()
{
	return m_data;
}
String& String::toUpperCase()
{
	int index;
	for (index = 0; index < len; ++index)
	{
		toupper(m_data[index]);
	}
	return *this;
}
String& String::trim()
{
	int index = 0;
	int size = 0;
	while (m_data[index++] == ' ')
	{
		size++;
	}
	m_data += size;
	len -= size;

	index = len - 1;
	size = 0;
	while (m_data[index--] == ' ')
	{
		size++;
	}
	m_data[index++] = L'\0';
	len -= size;
	return *this;
}
String String::substr(int beginIndex)
{
	return substr(beginIndex, len);
}
String String::substr(int beginIndex, int endIndex)
{
	if (beginIndex >= endIndex || endIndex > len)
	{
		return *this;
	}
	int len = endIndex - beginIndex; 
	GUI_CHAR *buf = new GUI_CHAR[len + 1];
	memset(buf, 0, sizeof(GUI_CHAR)*(len + 1));
	AMWcsncpy((AMWChar*)buf, (const AMWChar*)(m_data + beginIndex),len);
	
	String retStr(buf);

	delete buf;
	return retStr;
}

// add by Duan shaopeng

void String::cat(const GUI_CHAR* chars)
{
	int desLen = this->len + AMWcslen((GUI_CHAR*)chars) + 1;
	GUI_CHAR* desData = new GUI_CHAR[desLen];
	memset(desData, 0, sizeof(GUI_CHAR)*(desLen));

	if ( this->m_data != NULL )
	{
		AMWcsncpy(desData, this->m_data, this->len);
		/*delete []m_data;
		this->m_data = NULL;*/
		freeData();
	}
	
	//wcscat_s(desData, desLen, chars);
	AMWcsncat((AMWChar*)desData, (const AMWChar*)chars, desLen);
	
	this->m_data = desData;
	this->len = desLen - 1;
}

bool String::operator < (const String& rhs) const
{
	int res = AMWcscmp(this->m_data, rhs.m_data);
	if ( res < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator > (const String& rhs) const
{
	int res = AMWcscmp(this->m_data, rhs.m_data);
	if ( res > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator == (const String& rhs) const
{
	int res = AMWcscmp(this->m_data, rhs.m_data);
	if ( res == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator != (const String& rhs) const
{
	int res = AMWcscmp(this->m_data, rhs.m_data);
	if ( res != 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

String& String::operator += (const String& rhs)
{
	cat(rhs.m_data);
	return *this;
}

String& String::operator += (const GUI_CHAR* chars)
{
	cat(chars);
	return *this;
}
GUI_CHAR String::operator [] (int index) const
{
	return m_data[index];
}

bool String::endsWith( String suffix )
{
	int len1 = this->len;
	len1--;
	int len2 = suffix.length();	
	len2--;

	while (len1 >=0 && len2 >=0)
	{
		if (m_data[len1--] == suffix[len2--])
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	if (len1 >= -1 && len2 == -1)
	{
		return true;
	}

	return false;
}

void String::freeData()
{	
	int p = int(m_data);
	if(p == 0x0025a900)
	{
		int i = 1;
	}
	delete []m_data;
	m_data = NULL;
}

shared_ptr<String> String::toString()
{
	shared_ptr<String> self = new String(this->m_data);
	return self;
}
String operator + (const String& rhs1,const String& rhs2)
{
	String desString(rhs1);
	desString.cat(rhs2.m_data);
	return desString;
}
String operator + (const String& rhs,const GUI_CHAR* chars)
{
	String desString(rhs);
	desString.cat(chars);
	return desString;
}
String operator + (const GUI_CHAR* chars,const String& rhs)
{
	String desString((GUI_CHAR*)chars);
	desString.cat(rhs.m_data);
	return desString;
}
__GUI_END_NAMESPACE
