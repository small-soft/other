#include "AMString.h"
#include <windows.h>

AMInt32 AMUnicodeToAnsi( const AMWChar* inUniBuf, AMInt32 inUniBufLen, AMChar* inOutBuf, AMInt32 inOutBufLen )
{
	return WideCharToMultiByte(CP_ACP,NULL, inUniBuf, inUniBufLen, inOutBuf, inOutBufLen, NULL, FALSE);
}

AMInt32 AMAnsiToUnicode( const AMChar* inAnsiBuf, AMInt32 inAnsiBufLen, AMWChar* inOutBuf, AMInt32 inOutBufLen )
{
	return MultiByteToWideChar(CP_ACP,NULL, inAnsiBuf, inAnsiBufLen, inOutBuf, inOutBufLen);
}

AMInt32 AMUTF8ToUnicode( const AMChar* inUtf8Buf, AMInt32 inUtf8BufLen, AMWChar* inOutBuf, AMInt32 inOutBufLen )
{
	return MultiByteToWideChar(CP_UTF8, 0, inUtf8Buf, inUtf8BufLen, inOutBuf, inOutBufLen);
}

AMInt32 AMUnicodeToUTF8( const AMWChar* inUniBuf, AMInt32 inUniBufLen, AMChar* inOutBuf, AMInt32 inOutBufLen )
{
	return WideCharToMultiByte( CP_UTF8, 0, inUniBuf, inUniBufLen, inOutBuf, inOutBufLen, NULL, NULL );
}

AMInt32 AMAnsiToUTF8(const AMChar* inAnsiBuf, AMInt32 inAnsiBufLen, AMChar* inOutBuf, AMInt32 inOutBufLen)
{
	AMInt32 ret = 0;
	AMWChar* temp = NULL;
	temp = (AMWChar*)malloc(inAnsiBufLen * 4);
	memset(temp, 0, inAnsiBufLen * 4);

	AMAnsiToUnicode(inAnsiBuf, inAnsiBufLen, temp, inAnsiBufLen * 4);
	ret = AMUnicodeToUTF8(temp, inAnsiBufLen * 4, inOutBuf, inOutBufLen);

	free(temp);
	return ret;
}

AMInt32 AMUtf8ToANSI(const AMChar* inUtf8Buf, AMInt32 inUtf8BufLen, AMChar* inOutBuf, AMInt32 inOutBufLen)
{
	AMInt32 ret = 0;
	AMWChar* temp = NULL;
	temp = (AMWChar*)malloc(inUtf8BufLen * 4);
	memset(temp, 0, inUtf8BufLen * 4);

	AMUTF8ToUnicode(inUtf8Buf, inUtf8BufLen, temp, inUtf8BufLen * 4);
	ret = AMUnicodeToAnsi(temp, inUtf8BufLen * 4, inOutBuf, inOutBufLen);
	
	free(temp);
	return ret;
}
//end of denx add