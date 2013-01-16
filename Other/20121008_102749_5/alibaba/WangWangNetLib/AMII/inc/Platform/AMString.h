/*
* AMString.h
*
*  Created on: 2009-11-19
*      Author: qinghua.liqh
*/
#ifndef _AM_STRING_H_
#define _AM_STRING_H_
#include "AMErrno.h"
#include "AMTypes.h"


#define AMStrlen strlen
#define AMStrcmp strcmp
#define AMStrncmp strncmp
#define AMStrcat strcat
#define AMStrcpy strcpy
#define AMStrncpy strncpy
#define AMStrchr strchr         //Find a character in a string.
#define AMStrrchr strrchr
#define AMStrstr strstr         //Find a substring.
#define AMcstol	 strtol
#define AMToupper toupper
#define AMTolower tolower


//字符串函数.
//函数返回值请参考对应函数标准函数
/*
AMSize_t AMStrlen(const AMChar *);
AMInt32  AMStrcmp(const AMChar *, const AMChar *);
AMChar*  AMStrcat(AMChar *, const AMChar *);
AMChar   AMStrcpy(AMChar *, const AMChar *);
AMChar*  AMStrchr(const AMChar *, AMInt32);
AMChar*  AMStrstr(const AMChar *, const AMChar *);
*/
#if (!defined(__SYMBIAN32__)) && defined(_WIN32)        //windows and wince
#define AMWcstol 	wcstol
#define AMWtoi   	_wtoi
#define AMWcscpy	wcscpy
#define AMWcsncpy 	wcsncpy
#define AMWcscat 	wcscat
#define AMWcsstr	wcsstr
#define AMWcsncat	wcsncat
#define AMWcslen	wcslen
#define AMWcscmp	wcscmp
#else
AMInt32  AMWcstol(const AMWChar *nptr, AMWChar **endptr, AMInt32 base);
AMInt32  AMWtoi(const AMWChar *nptr);
AMInt32  AMWcsncpy(AMWChar *strDest, const AMWChar *strSource, AMSize_t count);
AMWChar* AMWcscat(AMWChar *strDestination, const AMWChar *strSource);
AMWChar* AMWcsstr(const AMWChar *string, const AMWChar *strCharSet);
AMWChar* AMWcsncat(AMWChar *strDest, const AMWChar *strSource, AMSize_t count );
AMInt32  AMWcslen(const AMWChar *string);
AMWChar* AMWcscpy(AMWChar* strDest, const AMWChar* strSource);
AMInt32 AMWcscmp(const AMWChar* str1, const AMWChar* str2);
#endif


//字符函数
#define AMIsalnum isalnum;
#define AMIsalpha isalpha
#define AMIscntrl iscntrl
#define AMIsdigit isdigit
#define AMIsgraph isgraph
#define AMIslower islower
#define AMIsprint isprint
#define AMIspunct ispunct
#define AMIsspace isspace
#define AMIsupper isupper
#define AMIsxdigit isxdigit
#define AMTolower tolower
#define AMToupper toupper


//返回值为*inOutBufLen
AMInt32 AMUnicodeToAnsi(const AMWChar* inUniBuf, AMInt32 inUniBufLen, 
						AMChar* inOutBuf, AMInt32 inOutBufLen);

AMInt32 AMAnsiToUnicode(const AMChar* inAnsiBuf, AMInt32 inAnsiBufLen, 
						AMWChar* inOutBuf, AMInt32 inOutBufLen);

AMInt32 AMUTF8ToUnicode(const AMChar* inUtf8Buf, AMInt32 inUtf8BufLen, 
						AMWChar* inOutBuf, AMInt32 inOutBufLen);

AMInt32 AMUnicodeToUTF8(const AMWChar* inUniBuf, AMInt32 inUniBufLen, 
						AMChar* inOutBuf, AMInt32 inOutBufLen);

AMInt32 AMAnsiToUTF8(const AMChar* inAnsiBuf, AMInt32 inAnsiBufLen,
					 AMChar* inOutBuf, AMInt32 inOutBufLen);

AMInt32 AMUtf8ToANSI(const AMChar* inUtf8Buf, AMInt32 inUtf8BufLen, 
					 AMChar* inOutBuf, AMInt32 inOutBufLen);





#endif //_AM_STRING_H_
