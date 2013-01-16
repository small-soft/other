#include "charset.h"
#include <string.h>
#include <stdlib.h>

/**
 * @abstract   get a ascii string length 
 * @param      pAsciiStr a ASCII string 
 * @return     the length of ASCII string     
 */
unsigned int ascii_strlen(const unsigned char *pAsciiStr)
{
	int i    = 0;
	int ret  = 0;
	int size = strlen((char*)pAsciiStr);
	for (i=0; i<size; ) {
		if (pAsciiStr[i]<0x80) {
			i += 1;
		} else {
		     i += 2;
		}
		
		ret++;
	}

	return ret;
}

/**
 * @abstract  get ASCII string change to utf8 coding need length 
 * @param     pAsciiStr ASCII coded string  
 * @return    length of a UTF8 coding string   
 */
unsigned int ascii_to_utf8_len(const unsigned char *pAsciiStr)
{
	unsigned int   retlen = 0;
	unsigned int   i      = 0;

	if (pAsciiStr == NULL)
	{
		return 0;
	}
	
	while (pAsciiStr[i]!=0)
	{
        if (pAsciiStr[i] < 0x80) { 
			retlen++;
			i++;
		} else {
		     retlen += 3;
			 i += 2;
		}
	}

	return retlen;
}

/**
 * @description get the length when changing ASCII to UTF16 coded string needed 
 * @param       pAsciiStr string coded ASCII
 * @return      length when changing needed
*/
unsigned int ascii_to_utf16_len(const unsigned char input[])
{
	return 2 * ascii_strlen(input);
}

/**
 * @abstract  ge ASCII character to UTF16 character 
 * @param     c Ascii character  
 * @return    UTF16 character   
 */
unsigned short ascii_char_to_utf16(unsigned short c)
{
	int row = 0;
	int col = 0;

	if (c < MIN_ASCII_CODE || c > MAX_ASCII_CODE)
	{
		return 0;
	}
	
	row = (c >> 8) - 0xa0;
	col = (c & 0xFF) - 0xa0;
	
	if (row < 0x0a)
	{
		if (col > 0 && col < 95)
		{
			return (ASCIItoUNItbl[(row-1)*94 + col-1]);
		}
		else
		{
			return 0;
		}
	}
	else if (row >= 0x0a && row <= 0x0f)
	{
		return 0;
	}
	else if (row > 0x0f && row < 0x60)
	{
		if (col>0 && col<95)
		{
			return (ASCIItoUNItbl[(row-7)*94 + col-1]);
		}
	}
	
	return 0;
}

/**
 * @abstract chang ASCII coded string UTF8 coded string 
 * @param    input ascii coded string
 * @param    inlen  ascii coded string length
 * @param    outlen   utf8  coded string length
 * @param    output  UTF8  coded string
 * @return   void
 */
void ascii_to_utf8(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
	unsigned char *pUTF16Str = NULL;
	unsigned int  utf16len   = 0;

	if (NULL==input || NULL==output || 0==inlen || 0==outlen) {
		return;
	}
	if (outlen < ascii_to_utf8_len(input)) {
		return;
	}
	
	utf16len = ascii_strlen(input) * 2;
	pUTF16Str = (unsigned char *)malloc(utf16len + 2);
	if (NULL != pUTF16Str) {
		memset(pUTF16Str, 0, utf16len+2);
		ascii_to_utf16(input, inlen, utf16len, pUTF16Str);
		utf16_to_utf8(pUTF16Str, utf16len, outlen, output);	

		free(pUTF16Str);
		pUTF16Str = NULL;
	}
}

/**
 * @abstract change ascii coded string to UTF16 coded string 
 * @param    input ascii coded string
 * @param    inlen  ascii coded string length
 * @param    outlen  UTF16 coded string length
 * @param    output utf16 coded string
 * @return   void
 */
void ascii_to_utf16(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
	unsigned short step	      = 0;
	unsigned short asciiValue = 0; /* each ASCII value */
	unsigned short uniValue   = 0; /* each UTF16 value */
	unsigned int   size       = 0; /* UTF16 coded string character size */

	if (NULL==input || NULL==output || 0==inlen || 0==outlen) {
		return;
	}

	if (outlen<ascii_to_utf16_len(input)) {
		return;
	}

	for (step=0; step<inlen; ) {
		if (input[step] < 0x80) {
			output[size]   = 0x00;
			output[size+1] = input[step];
			step++;
		} else {
			asciiValue	   = (unsigned short)((input[step] << 8) + input[step+1]);
			uniValue	   = ascii_char_to_utf16(asciiValue);
			output[size]   = (unsigned char)((uniValue & 0xFF00) >> 8);
			output[size+1] = (unsigned char)(uniValue & 0x00FF);
			step += 2;
		}
		
		size += 2;
	} 
}
