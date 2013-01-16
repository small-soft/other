#include "charset.h"
#include <string.h>
#include <stdlib.h>

/* UTF-8 encoding of 32 bit Unicode chars
*
* Characters  0x00000000 to 0x0000007f are US-ASCII
* Characters  0x00000080 to 0x000000ff are ISO Latin 1 (ISO 8859-1)
*
* incoming char| outgoing
* bytes | bits | representation
* ==================================================
*     1 |    7 | 0xxxxxxx
*     2 |   11 | 110xxxxx 10xxxxxx
*     3 |   16 | 1110xxxx 10xxxxxx 10xxxxxx
*     4 |   21 | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*     5 |   26 | 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*     6 |   31 | 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*
* The first byte is always in the range 0xC0-0xFD
* Further bytes are all in the range 0x80-0xBF
* No byte is ever 0xFE or 0xFF
*
*/

/*
* Unicode 3.0 Corrigendum #1: UTF-8 Shortest Form
* http://www.unicode.org/versions/corrigendum1.html
*
* C12 
*
* (a) When a process generates data in a Unicode Transformation
* Format, it shall not emit ill-formed code unit sequences.
*
* (b) When a process interprets data in a Unicode Transformation
* Format, it shall treat illegal code unit sequences as an error
* condition.
*
* (c) A conformant process shall not interpret illegal UTF code unit
* sequences as characters.
*
* (d) Irregular UTF code unit sequences shall not be used for
* encoding any other information.
*
*
* My Summary: never encode non-shortest form UTF-8 sequences - they are
* are illegal sequences.  Do not accept them on decoding.
*
*       Table 3.1B. Legal UTF-8 Byte Sequences
*   Code Points         1st Byte  2nd Byte  3rd Byte  4th Byte
*   U+0000..U+007F      00..7F
*   U+0080..U+07FF      C2..DF    80..BF
*   U+0800..U+0FFF      E0        A0..BF    80..BF
*   U+1000..U+FFFF      E1..EF    80..BF    80..BF
*   U+10000..U+3FFFF    F0        90..BF    80..BF    80..BF
*   U+40000..U+FFFFF    F1..F3    80..BF    80..BF    80..BF
*   U+100000..U+10FFFF  F4        80..8F    80..BF    80..BF
*
*/

/**
* @abstract   get a UTF8 string length 
* @param      pUTF8Str a UTF8 string 
* @return     the length of UTF8 string   
*/
unsigned int utf8_strlen(const unsigned char input[])
{
    unsigned int retlen = 0;
    int			 i      = 0;
    int			 length = 0;
    
    i      = 0;
    length = strlen((char *)input);
    while(0 != input[i]) {
        int size = utf8_char_to_utf16(&input[i], length-i, NULL);
        if(size <= 0) {
            return 0;
        }
        retlen++;
        i += size;
    }
    
    return retlen;
}

/**
* @description get the length of changing UTF8 to ASCII coded string 
* @param       pUTF8Str string coded UTF8
* @return      changing length
*/
unsigned int utf8_to_ascii_len(const unsigned char input[])
{
    unsigned int retlen = 0;
    int			 i      = 0;
    int			 length = 0;
    
    i      = 0;
    length = strlen((char *)input);
    while(0 != input[i]) {
        int size = utf8_char_to_utf16(&input[i], length-i, NULL);
        if(size <= 0) {
            return 0;
        } else if (size == 1) {
            retlen++;
        } else {
            retlen += 2;
        }
        i += size;
    }
    
    return retlen;
}

/**
* @abstract get the length when changing UTF8 to UTF16 coded need 
* @param    pUTF8Str utf8 coded string
* @return   the length when changing need
*/
unsigned int utf8_to_utf16_len(const unsigned char *pUTF8Str)
{
    return 2 * utf8_strlen(pUTF8Str);
}

/**
* utf8_char_to_utf16 - Convert an UTF-8 encoded buffer to a Unicode character
* @output: Pointer to the Unicode character or NULL
* @input: UTF-8 string buffer
* @length: buffer size
* 
* If output is NULL, then will calculate the number of bytes that
* will be used from the input buffer and not perform the conversion.
* 
* Return value: bytes used from input buffer or <0 on failure
**/
int utf8_char_to_utf16(const unsigned char input[], int length, unsigned short *output)
{
    unsigned char  in   = 0;
    int	           size = 0;
    unsigned short c    = 0;
    
    if(length < 1) {
        return -1;
    }
    
    in= *input++;
    if((in & 0x80) == 0) { /* First byte 00..7F */
        size = 1;
        c    = (unsigned short)(in & 0x7f);
    } else if((in & 0xe0) == 0xc0) { /* First byte C0..DF */
        size = 2;
        c    = (unsigned short)(in & 0x1f);
    } else if((in & 0xf0) == 0xe0) { /* First byte E0..EF */
        size = 3;
        c    = (unsigned short)(in & 0x0f);
    } else if((in & 0xf8) == 0xf0) { /* First byte F0..F7 */
        size = 4;
        c    = (unsigned short)(in & 0x07);
    } else { /* First byte anything else: 80..BF F8..FF - illegal */
        return -1;
    }
    
    
    if(NULL == output) {
        return size;
    }
    
    if(length < size) {
        return -1;
    }
    
    switch(size) {
    case 4:
        in = (unsigned char)(*input++ & 0x3f);
        c  = (unsigned short)(c << 6);
        c |= in;
        /* FALLTHROUGH */
    case 3:
        in = (unsigned char)(*input++ & 0x3f);
        c  = (unsigned short)(c << 6);
        c |= in;
        /* FALLTHROUGH */
    case 2:
        in = (unsigned char)(*input++ & 0x3f);
        c  = (unsigned short)(c << 6);
        c |= in;
        /* FALLTHROUGH */
    default:
        break;
    }
    
    
    /* check for overlong UTF-8 sequences */
    switch(size) {
    case 2 :
        if(c < 0x00000080) {
            return -2;
        }
        break;
    case 3 :
        if(c < 0x00000800) {
            return -2;
        }
        break;
    case 4 :
        if(c < 0x00010000) {
            return -2;
        }
        break;
        
    default : /* 1 */
        break;
    }
    
    
    /* check for illegal code positions:
    * U+D800 to U+DFFF (UTF-16 surrogates)
    * U+FFFE and U+FFFF
    */
    if ((c > 0xD7FF && c < 0xE000) || c == 0xFFFE || c == 0xFFFF) {
        return -1;
    }
    
    /* Unicode 3.2 only defines U+0000 to U+10FFFF and UTF-8 encodings of it */
    /* of course this makes some 4 byte forms illegal */
    if(c > 0x10ffff) {
        return -1;
    }
    
    *output = c;
    
    return size;
}

/**
* @abstract  exchange UTF8 coded string to UTF16 coded string 
* @param     input a string coded UTF8
* @param     inlen input buffer size
* @param     outlen  output buffer size
* @param     output ret string coded UTF16(out value)
* @return    void   
*/
void utf8_to_utf16(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
    unsigned int   step     = 0; /* vistor pUTF8Str steper */
    unsigned short cvalue   = 0; /* each UTF16 character value */
    int            size     = 0; /* UTF16 character number */
    unsigned int   utf16len = 0;
    
    if (NULL==input || NULL==output || 0==inlen || 0==outlen) {
        return;
    }
    if (outlen < utf8_to_utf16_len(input)) { /* length of string coded UTF16 is short when changing to UTF8  */
        return;
    }
    
    memset(output, 0, outlen);
    step	= 0;
    while (step < inlen) {
        size = utf8_char_to_utf16(&input[step], inlen-step, &cvalue);
        if(size <= 0) { /* skip error code */
            step++ ;
            continue;
        }
        step += size;
        
        if (utf16len+1 < outlen) {
            output[utf16len]   = (unsigned char)((cvalue & 0xFF00) >> 8);
            output[utf16len+1] = (unsigned char)(cvalue & 0x00FF);
            
            utf16len += 2;
        }
    } // end while
}

/**
* UTF8toLatin1 - Convert a UTF-8 string to ISO Latin-1
* @input: UTF-8 string buffer
* @length: buffer size
* @output_length: Pointer to variable to store resulting string length or NULL
* 
* Converts the given UTF-8 string to the ISO Latin-1 subset of
* Unicode (characters 0x00-0xff), discarding any out of range
* characters.
*
* If the output_length pointer is not NULL, the returned string
* length will be stored there.
*
* Return value: pointer to new ISO Latin-1 string or NULL on failure
**/
unsigned char *UTF8toLatin1(const unsigned char input[], int length, int *output_length)
{
    int utf8_byte_length=0;
    int i;
    int j;
    unsigned char *output = NULL;
    
    /* This is a maximal length; since chars may be discarded, the
    * actual length of the resulting can be shorter
    */
    utf8_byte_length= utf8_strlen(input);
    
    output=(unsigned char *)malloc(utf8_byte_length + 1);
    if(!output) {
        return NULL;
    }
    
    i=0; j=0;
    while(i < utf8_byte_length) {
        unsigned short c    = 0;
        int            size = utf8_char_to_utf16(&input[i], length-i, &c);
        
        if (size <= 0) {
            return NULL;
        }
        if(c < 0x100) { /* Discards characters! */
            output[j++] = (unsigned char)c;
        }
        i+= size;
    } 
    output[j]='\0';
    
    if(output_length) {
        *output_length=j;
    }
    
    return output;
}

/**
* @abstract get the length when changing UTF8 to ascii coded string needed 
* @param    pUTF8Str  utf8  coded string
* @param    utf8len   utf8  coded string length
* @param    asciilen  ascii coded string length
* @param    pAsciiStr ascii coded string
* @return   void
*/
void utf8_to_ascii(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[])
{
    unsigned char *pUTF16Str = NULL;
    unsigned int  utf16len   = 0;
    
    if (NULL==input || NULL==output || 0==inlen || 0==outlen) {
        return;
    }
    if (outlen < utf8_to_ascii_len(input)) {
        return;
    }
    
    utf16len  = utf8_to_utf16_len(input);
    pUTF16Str = (unsigned char *)malloc(utf16len + 2);
    if (NULL != pUTF16Str) {
        memset(pUTF16Str, 0, utf16len+2);
        utf8_to_utf16(input, inlen, utf16len, pUTF16Str);
        utf16_to_ascii(pUTF16Str, utf16len, outlen, output);
        free(pUTF16Str);
        pUTF16Str = NULL;
    }
}



