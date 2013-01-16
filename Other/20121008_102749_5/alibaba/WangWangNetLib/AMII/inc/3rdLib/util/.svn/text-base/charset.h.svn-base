#ifndef _WORD_H_
#define _WORD_H_

#if defined(_WIN32)
   #ifdef UTIL_DLL_EXPORTS
        #define UTIL_API __declspec(dllexport)
   #else
        #define UTIL_API
   #endif
#else
   #define UTIL_API
#endif

extern const unsigned short ASCIItoUNItbl[];
//int ok?
extern const int CODE_NUM;
#define MIN_ASCII_CODE 	0xA1A1
#define MAX_ASCII_CODE 	0xF7FE

#define UTF8_VALID1(p) \
( 0 == ((p)[0] & 0x80) )

#define UTF8_VALID2(p) \
( 0xc0==( (p)[0]&0xe0 ) &&  (0x80== ( (p)[1]&0xc0) )  )

#define UTF8_VALID3(p) \
( (0xe0==( (p)[0]&0xf0) ) &&  (0x80==( (p)[1]&0xc0) ) && (0x80== ( (p)[2]&0xc0) ) )

#define UTF8_VALID4(p) \
( (0xf0==( (p)[0]&0xf8) ) &&  (0x80==( (p)[1]&0xc0) ) && (0x80==( (p)[2]&0xc0) ) && (0x80==( (p)[3]&0xc0) ) )

#ifdef __cplusplus
extern "C" {
#endif

UTIL_API unsigned int ascii_strlen	(const unsigned char input[]);
UTIL_API unsigned int utf16_strlen	(const unsigned char input[]);
UTIL_API unsigned int utf8_strlen		(const unsigned char input[]);

UTIL_API unsigned int ascii_to_utf8_len	(const unsigned char input[]);
UTIL_API unsigned int ascii_to_utf16_len(const unsigned char input[]);
UTIL_API unsigned int utf16_to_utf8_len	(const unsigned char input[]);
UTIL_API unsigned int utf16_to_ascii_len(const unsigned char input[]);
UTIL_API unsigned int utf8_to_ascii_len	(const unsigned char input[]);
UTIL_API unsigned int utf8_to_utf16_len	(const unsigned char input[]);

UTIL_API unsigned short	utf16_char_to_ascii(unsigned short c);
UTIL_API unsigned short	ascii_char_to_utf16(unsigned short c);
UTIL_API int  utf16_char_to_utf8(unsigned short c, unsigned char output[], int length);
UTIL_API int	 utf8_char_to_utf16(const unsigned char input[], int length, unsigned short *output);

UTIL_API void utf16_to_utf8	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
UTIL_API void utf8_to_utf16	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
UTIL_API void utf8_to_ascii	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
UTIL_API void ascii_to_utf8	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
UTIL_API void utf16_to_ascii	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
UTIL_API void ascii_to_utf16	(const unsigned char input[], unsigned int inlen, unsigned int outlen, unsigned char output[]);
#ifdef __cplusplus
};
#endif

#endif //_WORD_H_


