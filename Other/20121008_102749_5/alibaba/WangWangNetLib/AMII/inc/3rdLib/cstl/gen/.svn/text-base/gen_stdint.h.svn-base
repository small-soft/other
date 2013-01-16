#ifndef STDINT_H_
#define STDINT_H_
#if (!defined(__SYMBIAN32__)) && defined(_WIN32)
#define int8_t char
#define uint8_t unsigned char
#define int16_t short int
#define uint16_t unsigned short int
#define int32_t int
#define uint32_t unsigned int
#define int64_t long
#define uint64_t unsigned long
//#include "stdint.h"
#define __func__  __FUNCTION__
#else

#ifdef __GNUC__
#define HAVE_STDINT_H 1
#endif

#if HAVE_STDINT_H
  #include <stdint.h>
#else
#define int8_t char
#define uint8_t unsigned char
#define int16_t short int
#define uint16_t unsigned short int
#define int32_t int
#define uint32_t unsigned int
#endif

#endif
#endif
