#ifndef _BASE_64_
#define _BASE_64_

#if defined(_WIN32)
   #ifdef UTIL_DLL_EXPORTS
        #define UTIL_API __declspec(dllexport)
   #else
        #define UTIL_API
   #endif
#else
   #define UTIL_API
#endif
/*
	base64 encode.
	RET�� 
		-1: outlen������(outlen ����С�� (inlen / 3 + (inline % 3) == 0 ? 0 : 1) * 4 + 1)
		-2: text����outΪ��.
	     0: inlen <= 0
		>0: ��ȷ���.
*/
UTIL_API int ali_base64_encode(const unsigned char *text, size_t inlen, char* out, size_t outlen);
/*
	base64 decode.
	RET�� 
		-1: outlen������
		-2: data����outΪ��.
	     0: data���Ȳ���4�ı����� ����==0
		>0: ��ȷ���.
*/
UTIL_API int base64_decode(const char *data, unsigned char *out, size_t outlen);
#endif