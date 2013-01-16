#include "charset.h"

#include <stdlib.h>
#include <string.h>

/**
* @abstract   get a UTF16 string length 
* @param      pUTF16Str a utf16 string 
* @return     the length of UTF8 string     
*/
unsigned int utf16_strlen(const unsigned char *pUTF16Str)
{
	unsigned int retlen = 0; // return length
	unsigned int step   = 0; // cycle var
    
	if (NULL == pUTF16Str) {
		return 0;
	}
	
	for (step=0; (pUTF16Str[step]!=0 || pUTF16Str[step+1]!=0); ) {
		retlen++;
		step += 2;
	}
	
	return retlen;
}

/**
* @abstract  get the length when changing UTF16 to UTF8 coded string needed
* @param     pUTF16Str utf16 string  
* @return    length of a UTF8 coding string   
*/
unsigned int utf16_to_utf8_len(const unsigned char input[])
{
	unsigned int   retlen = 0;
	unsigned int   i      = 0;
	unsigned short cvalue = 0;
	unsigned int   length = 0;
	int			   size   = 0;
	
	if (input == NULL)
	{
		return 0;
	}
	
	i = 0;
	length = utf16_strlen(input) * 2;
	while (input[i]!=0 || input[i+1]!=0)
	{
		cvalue  = (unsigned short)((input[i]<<8) + input[i+1]);
		size    = utf16_char_to_utf8(cvalue, NULL, length-i);
        if (size < 0) { // error code
            return 0; 
        }
		retlen += size;
		i      += 2;
	}
	
	return retlen;
}

/**
 * get the length when changing UTF8 to ASCII coded string needed 
 * @param       pUTF16Str string coded UTF16
 * @return      length when changing needed
 */
unsigned int utf16_to_ascii_len(const unsigned char *pUTF16Str)
{
	unsigned int   retlen = 0;
	unsigned int   i      = 0;
	unsigned short cvalue = 0;
	
	if (pUTF16Str == NULL)
	{
		return 0;
	}
	
	i = 0;
	while (pUTF16Str[i]!=0 || pUTF16Str[i+1]!=0)
	{
		cvalue = (unsigned short)((pUTF16Str[i]<<8) + pUTF16Str[i+1]);
		if(cvalue>0 && cvalue<=0x7F) {
			retlen++;
		} else {
			retlen += 2;
		}
		
		i += 2;
	}
	
	return retlen;
}

/**
 * @abstract  exchange  
 * @param       
 * @return       
 */
unsigned short utf16_char_to_ascii(unsigned short c)
{
	int 			row	= 0;
	int 			col	= 0;
	unsigned short 	i	= 0;
	unsigned short  asciiValue = 0; 
	

	{
		while (i < CODE_NUM)
		{
			if(c == ASCIItoUNItbl[i])
			{
				c=i;
				break;
			}
			else 
			{
				i++;
			}
		}
		
		if (i < CODE_NUM)
		{
			if(c > 0x777E)
			{
				row = 0;
				col = 0;
			}
			else
			{
				if((c/94+1) < 0xA)
				{
					row=c / 94 + 1;
				}
				else 
				{
					row=c / 94 + 7;
				}
				
				col = c % 94 + 1;
			}
			
			asciiValue = (unsigned short)( ((row+0xa0) << 8) | (col+0xa0) );
		}
		else if(c > 0xFF)
		{
			asciiValue = (unsigned short)( ((c>>8) << 8) | (c&0xFF) );
		}
		else 
		{
			asciiValue = (unsigned short)(c & 0xFF);
		}
	}
	
	return asciiValue;
}

/**
* utf16_char_to_utf8 - Convert a Unicode character to UTF-8 encoding
* @c: Unicode character
* @output: UTF-8 string buffer or NULL
* @length: buffer size
* 
* If buffer is NULL, then will calculate the length rather than
* perform it.  This can be used by the caller to allocate space
* and then re-call this function with the new buffer.
* 
* Return value: bytes written to output buffer or <0 on failure
**/
int utf16_char_to_utf8(unsigned short c, unsigned char output[], int length)
{
	int size = 0;
	
	/* check for illegal code positions:
	* U+D800 to U+DFFF (UTF-16 surrogates)
	* U+FFFE and U+FFFF
	*/
	if((c>0xD7FF && c<0xE000) || c == 0xFFFE || c == 0xFFFF) {
		return -1;
	}
	
	/* Unicode 3.2 only defines U+0000 to U+10FFFF and UTF-8 encodings of it */
	if(c > 0x10ffff) {
		return -1;
	}
	
	if (c < 0x00000080) {
		size=1;
	} else if (c < 0x00000800) {
		size=2;
	} else if (c < 0x00010000) {
		size=3;
	} else {
		size=4;
	}
	
	/* when no buffer given, return size */
	if (NULL == output) {
		return size;
	}
	
	if (size > length) {
		return -1;
	}
	
	switch (size) {
    case 4 :
		output[3] = (unsigned char)(0x80 | (c & 0x3F));
		c		  = (unsigned short)(c >> 6);
		/* set bit 4 (bits 7,6,5,4 less 7,6,5 set below) on last byte */
		c |= 0x10000; /* 0x10000 = 0x10 << 12 */
		/* FALLTHROUGH */
    case 3 :
		output[2] = (unsigned char)(0x80 | (c & 0x3F));
		c		  = (unsigned short)(c >> 6);
		/* set bit 5 (bits 7,6,5 less 7,6 set below) on last byte */
		c |= 0x800; /* 0x800 = 0x20 << 6 */
		/* FALLTHROUGH */
    case 2 :
		output[1] = (unsigned char)(0x80 | (c & 0x3F));
		c		  = (unsigned short)(c >> 6);
		/* set bits 7,6 on last byte */
		c |= 0xc0; 
		/* FALLTHROUGH */
    case 1 :
		output[0] = (unsigned char)c;
	}
	
	return size;
}

/**
* @abstract  exchange UTF16 coded string to UTF8 coded string 
* @param     pUTF16Str a string coded UTF16
* @param     utf16len the length of pUTF16Str
* @param     utf8len  the length of pUTF8Str
* @param     pUTF8Str ret string coded UTF8(out value)
* @return    void   
*/
void utf16_to_utf8(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
	unsigned short cvalue  = 0; /* utf16 value */
	unsigned int   step    = 0; /* vistor pUTF16Str steper */	 
	int			   size	   = 0; /*  */
	unsigned int   utf8len = 0; /* utf8 string character number */
	
	if (NULL==input || NULL==output || 0==inlen || 0==outlen)
	{
		return;
	}
	
	if (outlen < utf16_to_utf8_len(input)) { /* utf8 length too short when changing code */
		return;
	}
	
	memset(output, 0, outlen);
	for (step=0; step<inlen; ) {
		/* get utf16 value */
		cvalue   = (unsigned short)( (input[step] << 8) | input[step+1] );
		size     = utf16_char_to_utf8(cvalue, &output[utf8len], outlen-utf8len);//utf16_char_to_utf8(cvalue, &output[utf8len], inlen-step);
        if (size < 0) { // skip error code
            return;
        }
		utf8len += size;
		step    += 2;
	}
}



void utf16_to_ascii(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
	unsigned int	step	    = 0; /* vistor pUTF16Str steper */
	unsigned short	asciivalue  = 0; /* ascii character value */
	unsigned short  uniValue    = 0; /* UTF16 character value */
	unsigned int    asciilen    = 0;
	
    if (NULL==input || NULL==output || 0==inlen || 0==outlen) {
		return;
	}
	if (outlen < utf16_to_ascii_len(input)) {
		return;
	}
	
	for (step=0; step<inlen; step+=2) {
		uniValue   = (unsigned short)((input[step] << 8) | input[step+1]);
		asciivalue = utf16_char_to_ascii(uniValue);
		if (asciivalue < 0x80) {
			output[asciilen] = (unsigned char)asciivalue;
			asciilen++;
		} else {
			output[asciilen]   = (unsigned char)( (asciivalue>>8) & 0xff );
			output[asciilen+1] = (unsigned char)(asciivalue & 0xFF);
			asciilen += 2;
		}
	}
}


