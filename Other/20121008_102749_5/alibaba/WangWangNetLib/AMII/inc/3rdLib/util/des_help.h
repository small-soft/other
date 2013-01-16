#ifndef _DES_HELP_
#define _DES_HELP_

#if defined(_WIN32)
   #ifdef UTIL_DLL_EXPORTS
        #define UTIL_API __declspec(dllexport)
   #else
        #define UTIL_API
   #endif
#else
   #define UTIL_API
#endif

UTIL_API unsigned char* des_decrypt(unsigned char* key, unsigned char* in_buffer, int in_len);
UTIL_API unsigned char* des_encrypt(unsigned char* key, unsigned char* in_buffer, int in_len);

UTIL_API unsigned char* des_decrypt_ex(unsigned char* key, unsigned char* in_buffer, int in_len);
UTIL_API unsigned char* des_encrypt_ex(unsigned char* key, unsigned char* in_buffer, int in_len);

#endif