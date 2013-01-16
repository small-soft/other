#ifndef _DES_HELP_
#define _DES_HELP_

#if defined(_WIN32)
	#ifdef DLL_UTIL_EXPORTS
		#ifndef DLL_UTIL_API
		#define DLL_UTIL_API __declspec(dllexport)
		#endif
	#else
		#ifndef DLL_UTIL_API
		#define DLL_UTIL_API __declspec(dllimport)
		#endif
	#endif
#else 
#define DLL_UTIL_API
#endif

DLL_UTIL_API unsigned char* des_decrypt(unsigned char* key, unsigned char* in_buffer, int in_len);
DLL_UTIL_API unsigned char* des_encrypt(unsigned char* key, unsigned char* in_buffer, int in_len);

#endif