#include "AMString.h"
#include <e32std.h>
#include <string.h>
#include <utf.h>

AMInt32  AMWcstol(const AMWChar *nptr, AMWChar **endptr, AMInt32 base)
{
    TLex lex((const TUint16*) nptr );
    TUint id;
    
    TRadix radix;
    if(base == 2)
    	radix = EBinary;
    else if(base == 8)
    	radix = EOctal;
    else if(base == 10)
    	radix = EDecimal;
    else if(base == 16)
        radix = EHex;
    else 
    	radix = EDecimal;
            
    lex.Val(id, radix);
    
    return id;
}

AMInt32  AMWtoi(const AMWChar *nptr)
{
    TLex lex( (const TUint16*)nptr );
    TInt id;
    lex.Val(id);
    return id;
}

AMInt32  AMWcsncpy(AMWChar *strDest, const AMWChar *strSource, AMSize_t count)
{
	if( !strDest || !strSource )
		return 0;
	
	for( TInt i = 0; i < count; ++i )
		{
		strDest[i] = strSource[i];
		}
	
	return 0;
}

AMWChar* AMWcscat(AMWChar *strDestination, const AMWChar *strSource)
{
	if( !strDestination || !strSource )
		return 0;
	
	while( NULL != *strDestination )
		{
		++strDestination;
		}
	
	while( NULL != *strSource )
		{
		*strDestination++ = *strSource++;
		}
	
	return 0;
}

AMWChar* AMWcsncat(AMWChar *strDest, const AMWChar *strSource, AMSize_t count )
{
	if( !strDest || !strSource )
		return 0;

	if( wcslen((wchar_t*)strDest) + wcslen((wchar_t*)strSource) >= count )
		return 0;
	
	while( NULL != *strDest )
		{
		++strDest;
		}

	*strDest++ = *strSource++;
	
	return 0;
}

AMWChar* AMWcsstr(const AMWChar *string, const AMWChar *strCharSet)
{
	if( !string || !strCharSet )
		return 0;
	
	while( NULL != *string )
		{
		const AMWChar* temp = string;
		const AMWChar* search = strCharSet;
		while( NULL != *temp && NULL != *search && *temp == *search )
			{
			++temp;
			++search;
			}
		
		if( NULL == *search )
			{
			return const_cast<AMWChar*>(string);
			}
		
		++string;
		}

	return 0;
}

AMInt32 AMUnicodeToAnsi(const AMWChar* inUniBuf, AMInt32 inUniBufLen, 
						AMChar* inOutBuf, AMInt32 inOutBufLen)
	{
	TPtrC p( (const TUint16*)inUniBuf, inUniBufLen );
	HBufC8* buf = CnvUtfConverter::ConvertFromUnicodeToUtf8L( p );
	for( TInt i = 0; i < buf->Length(); ++i )
		{
		inOutBuf[i] = (*buf)[i];
		}
	TInt ret = buf->Length();
	delete buf;
	return ret;
	}

AMInt32 AMAnsiToUnicode(const AMChar* inAnsiBuf, AMInt32 inAnsiBufLen, 
						AMWChar* inOutBuf, AMInt32 inOutBufLen)
	{
	TPtrC8 p( (const AMUChar*)inAnsiBuf, inAnsiBufLen );
	HBufC* buf = CnvUtfConverter::ConvertToUnicodeFromUtf8L( p );
	for( TInt i = 0; i < buf->Length(); ++i )
		{
		inOutBuf[i] = (*buf)[i];
		}
	TInt ret = buf->Length();
	delete buf;
	return ret;
	}

AMInt32  AMWcslen(const AMWChar *string)
{
	TPtrC16 p( string );
	
	return p.Length();
}

AMInt32 AMWcscmp(const AMWChar* str1, const AMWChar* str2)
{
	TPtrC16 p1( str1 );
	TPtrC16 p2( str2 );
	
	return p1.Compare( p2 );
}
