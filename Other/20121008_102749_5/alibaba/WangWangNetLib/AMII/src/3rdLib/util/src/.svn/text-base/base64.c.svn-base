#include <stdlib.h>
#include "base64.h"

static const char base64_strs[] =  
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/=";

/*
	base64 encode.
	RET： 
		-1: outlen不够长(outlen 不能小于 (inlen / 3 + (inline % 3) == 0 ? 0 : 1) * 4 + 1)
		-2: text或者out为空.
	     0: inlen <= 0
		>0: 正确结果.
*/
UTIL_API int ali_base64_encode(const unsigned char *text, size_t inlen, char* out, size_t outlen)
{
    char *point;
    size_t real_outlen;
    
	if(NULL == text || NULL == out)
		return -2;

    real_outlen = (inlen*4)/3;
    if ((inlen % 3) > 0) /* got to pad */
		real_outlen += 4 - (inlen % 3);

    for (point=out; inlen>=3; inlen-=3, text+=3) 
	{
		*(point++) = base64_strs[ (*text)>>2 ]; 
		*(point++) = base64_strs[ ((*text)<<4 & 0x30) | (*(text+1))>>4 ]; 
		*(point++) = base64_strs[ ((*(text+1))<<2 & 0x3c) | (*(text+2))>>6 ];
		*(point++) = base64_strs[ (*(text+2)) & 0x3f ];
    }

    /* Now deal with the trailing bytes */
    if (inlen > 0)
	{
		/* We always have one trailing byte */
		*(point++) = base64_strs[ (*text)>>2 ];
		*(point++) = base64_strs[ (((*text)<<4 & 0x30) |
				     (inlen==2?(*(text+1))>>4:0)) ]; 
		*(point++) = (inlen==1?'=':base64_strs[ (*(text+1))<<2 & 0x3c ]);
		*(point++) = '=';
    }
    /* Null-terminate */
    *point = '\0';

    return real_outlen;
}

/* VALID_B64: fail if 'ch' is not a valid base64 character */
#define VALID_B64(ch) (((ch) >= 'A' && (ch) <= 'Z') || \
                       ((ch) >= 'a' && (ch) <= 'z') || \
                       ((ch) >= '0' && (ch) <= '9') || \
                       (ch) == '/' || (ch) == '+' || (ch) == '=')

/* DECODE_B64: decodes a valid base64 character. */
#define DECODE_B64(ch) ((ch) >= 'a' ? ((ch) + 26 - 'a') : \
                        ((ch) >= 'A' ? ((ch) - 'A') : \
                         ((ch) >= '0' ? ((ch) + 52 - '0') : \
                          ((ch) == '+' ? 62 : 63))))
/*
	base64 decode.
	RET： 
		-1: outlen不够长
		-2: data或者out为空.
	     0: data长度不是4的倍数， 或者==0
		>0: 正确结果.
*/
UTIL_API int base64_decode(const char *data, unsigned char *out, size_t outlen)
{
    size_t inlen;
    const unsigned char *in;
	unsigned char *outp = out;

	if(NULL == data || NULL == out)
		return -2;

	inlen = strlen(data);
    if (inlen == 0 || (inlen % 4) != 0) 
		return 0;

	if(outlen < (inlen % 4) * 3 + 1)
		return -1;

    for (in = (const unsigned char *)data; *in; in += 4) {
        unsigned int tmp;
        if (!VALID_B64(in[0]) || !VALID_B64(in[1]) || !VALID_B64(in[2]) ||
            !VALID_B64(in[3]) || in[0] == '=' || in[1] == '=' ||
            (in[2] == '=' && in[3] != '=')) {
            return 0;
        }
        tmp = (DECODE_B64(in[0]) & 0x3f) << 18 |
            (DECODE_B64(in[1]) & 0x3f) << 12;
        *outp++ = (tmp >> 16) & 0xff;
        if (in[2] != '=') {
            tmp |= (DECODE_B64(in[2]) & 0x3f) << 6;
            *outp++ = (tmp >> 8) & 0xff;
            if (in[3] != '=') {
                tmp |= DECODE_B64(in[3]) & 0x3f;
                *outp++ = tmp & 0xff;
            }
        }
    }

    return (int)(outp - *out);
}