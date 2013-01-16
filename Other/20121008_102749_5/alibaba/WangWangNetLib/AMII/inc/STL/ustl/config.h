// @file config.h
//
// Manually constructed configuration file for Symbian OS
//
// Copyright (c) Penrillian, Smartphone Software Innovators <http://www.penrillian.com>
//
// This file is free software, distributed under the MIT License.

#ifndef CONFIG_H_01E33670634DAAC779EE5FF41CCBB36F
#define CONFIG_H_01E33670634DAAC779EE5FF41CCBB36F
// Namespace - no reason not to have the correct one.
#define ustl std

// Define to the one symbol short name of this package.
#define USTL_NAME	"ustl"
// Define to the full name and version of this package.
#define USTL_STRING	"ustl 1.0"
// Define to the version of this package.
#define USTL_VERSION	0x010000
// Define to the address where bug reports for this package should be sent.
#define USTL_BUGREPORT	"support@penrillian.com"

/// Define to 1 if you want stream operations to throw exceptions on
/// insufficient data or insufficient space. All these errors should
/// be preventable in output code; the input code should verify the
/// data in a separate step. It slows down stream operations a lot,
/// but it's your call. By default only debug builds throw.
///
#undef WANT_STREAM_BOUNDS_CHECKING

#if !defined(WANT_STREAM_BOUNDS_CHECKING) && !defined(NDEBUG)
//    #define WANT_STREAM_BOUNDS_CHECKING 1
#endif

/// Define to 1 if you want to build without libstdc++
#define WITHOUT_LIBSTDCPP 1

/// Define to 1 if you don't want the standard streams.
/// You will not be able to run bvt tests if you do this.
///
#define WITHOUT_CIN_COUT_CERR 1

/// Define GNU extensions if unavailable.
#ifndef __GNUC__
    /// GCC (and some other compilers) define '__attribute__'; ustl is using this
    /// macro to alert the compiler to flag inconsistencies in printf/scanf-like
    /// function calls.  Just in case '__attribute__' isn't defined, make a dummy.
    /// 
    #ifndef __attribute__
	#define __attribute__(p)
    #endif
#endif
#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define DLL_EXPORT		__attribute__((visibility("default")))
    #define DLL_LOCAL		__attribute__((visibility("hidden")))
#else
    #define DLL_EXPORT
    #define DLL_LOCAL
#endif
#if defined(__GNUC__) && (__GNUC__ >= 3) && defined(__i386__)
    /// GCC 3+ supports the prefetch directive, which some CPUs use to improve caching
    #define prefetch(p,rw,loc)	__builtin_prefetch(p,rw,loc)
#else
    #define prefetch(p,rw,loc)
#endif
#if !defined(__GNUC__) || (__GNUC__ < 3)
    /// __alignof__ returns the recommended alignment for the type
    #define __alignof__(v)	(sizeof( v) > sizeof(void*) ? sizeof(void*):sizeof(v)) // min(sizeof(v), sizeof(void*))
#endif

/// Define to 1 if you have the `atexit' function.
#undef HAVE_ATEXIT

/// Define to 1 if you have the <assert.h> header file.
#define HAVE_ASSERT_H 1

/// Define to 1 if you have the <ctype.h> header file.
#define HAVE_CTYPE_H 1

/// Define to 1 if you have the <errno.h> header file.
#define HAVE_ERRNO_H 1

/// Define to 1 if you have the <fcntl.h> header file.
#define HAVE_FCNTL_H 1

/// Define to 1 if you have the <float.h> header file.
#undef HAVE_FLOAT_H
#define HAVE_FLOAT_H 1  
/// Define to 1 if you have the <inttypes.h> header file.
#undef HAVE_INTTYPES_H

/// Define to 1 if you have the <limits.h> header file.
#define HAVE_LIMITS_H 1

/// Define to 1 if you have the <locale.h> header file.
#define HAVE_LOCALE_H 1

/// Define to 1 if your system has a working `malloc' function.
#define HAVE_MALLOC 1

// Define to 1 if you have the <malloc.h> header file.
#undef HAVE_MALLOC_H

// Define to 1 if you have the <alloca.h> header file.
#undef HAVE_ALLOCA_H

// Define to 1 if you have the `memchr' function.
#define HAVE_MEMCHR 1

// Define to 1 if you have the `memmove' function.
#define HAVE_MEMMOVE 1

// Define to 1 if you have the <memory.h> header file.
#undef HAVE_MEMORY_H

// Define to 1 if you have the `memset' function.
#define HAVE_MEMSET 1

// Define to 1 if the system has the type `ptrdiff_t'.
#define HAVE_PTRDIFF_T 1

// Define to 1 if you have the <signal.h> header file.
#undef HAVE_SIGNAL_H
#define HAVE_SIGNAL_H 1  
// Define to 1 if you have the __va_copy function
#undef HAVE_VA_COPY

// Define to 1 if `stat' has the bug that it succeeds when given the
// zero-length file name argument.
#undef HAVE_STAT_EMPTY_STRING_BUG

// Define to 1 if you have the <stdarg.h> header file.
#define HAVE_STDARG_H 1

// Define to 1 if you have the <stddef.h> header file.
#define HAVE_STDDEF_H 1

// Define to 1 if you have the <stdint.h> header file.
#define HAVE_STDINT_H 1

// Define to 1 if you have the <stdio.h> header file.
#define HAVE_STDIO_H 1

// Define to 1 if you have the <stdlib.h> header file.
#define HAVE_STDLIB_H 1

// Define to 1 if you have the `strerror' function.
#define HAVE_STRERROR 1

// Define to 1 if you have the <strings.h> header file.
#undef HAVE_STRINGS_H

// Define to 1 if you have the <string.h> header file.
#define HAVE_STRING_H 1

// Define to 1 if you have the `strrchr' function.
#define HAVE_STRRCHR 1

// Define to 1 if you have the `strsignal' function.
#undef HAVE_STRSIGNAL

// Define to 1 if you have the `strtol' function.
#define HAVE_STRTOL 1

// Define to 1 if you have the <sys/stat.h> header file.
#define HAVE_SYS_STAT_H 1

// Define to 1 if you have the <sys/types.h> header file.
#define HAVE_SYS_TYPES_H 1

// Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible.
#define HAVE_SYS_WAIT_H 1

// Define to 1 if you have the <time.h> header file.
#define HAVE_TIME_H 1

// Define to 1 if you have the <unistd.h> header file.
#define HAVE_UNISTD_H 1

// Define to 1 if you have the <math.h> header file.
#define HAVE_MATH_H 1

// Define to 1 if you have the rintf function. Will use rint otherwise.
#define HAVE_RINTF 0

// STDC_HEADERS is defined to 1 on sane systems.
#if defined(HAVE_ASSERT_H) && defined(HAVE_CTYPE_H) &&\
    defined(HAVE_ERRNO_H) && defined(HAVE_FLOAT_H) &&\
    defined(HAVE_LIMITS_H) && defined(HAVE_LOCALE_H) &&\
    defined(HAVE_MATH_H) && defined(HAVE_SIGNAL_H) &&\
    defined(HAVE_STDARG_H) && defined(HAVE_STDDEF_H) &&\
    defined(HAVE_STDIO_H) && defined(HAVE_STDLIB_H) &&\
    defined(HAVE_STRING_H) && defined(HAVE_TIME_H)
#define STDC_HEADERS 1
#endif

// STDC_HEADERS is defined to 1 on unix systems.
#if defined(HAVE_FCNTL_H) && defined(HAVE_SYS_STAT_H) && defined(HAVE_UNISTD_H)
#define STDUNIX_HEADERS 1
#endif

// Define to 1 if you have the <byteswap.h> header file.
#if (__GNUC__ >= 3) // gcc 2.95 somehow doesn't recognize 'asm volatile' in libc byteswap.h
#undef HAVE_BYTESWAP_H
#endif

// Define to 1 if `lstat' dereferences a symlink specified with a trailing slash.
#undef LSTAT_FOLLOWS_SLASHED_SYMLINK

// Define to 1 if your compiler treats char as a separate type along with
// signed char and unsigned char. This will create overloads for char.
#undef HAVE_THREE_CHAR_TYPES

// Define as the return type of signal handlers (`int' or `void').
#undef RETSIGTYPE

// Define to 1 if you have 64 bit types available
#undef HAVE_INT64_T

// Define to 1 if you have the long long type
#undef HAVE_LONG_LONG

// Define to 1 if you want unrolled specializations for fill and copy
#undef WANT_UNROLLED_COPY

// Define to 1 if you want to use MMX/SSE/3dNow! processor instructions
#undef WANT_MMX

// Define to byte sizes of types
// This is true for both WINS and ARMI on Symbian 8...
#define SIZE_OF_CHAR 1
#define SIZE_OF_SHORT 2
#define SIZE_OF_INT 4
#define SIZE_OF_LONG  4
#define SIZE_OF_LONG_LONG 0
#define SIZE_OF_POINTER  4
#define SIZE_OF_SIZE_T  4
#define SIZE_OF_BOOL  1
// #define SIZE_T_IS_LONG 1  // Penrillian 29/6/07

// Byte order macros, converted in utypes.h
#define USTL_LITTLE_ENDIAN	4321
#define USTL_BIG_ENDIAN		1234
#define USTL_BYTE_ORDER		USTL_LITTLE_ENDIAN

// Extended CPU capabilities
#undef CPU_HAS_FPU
#undef CPU_HAS_EXT_DEBUG
#undef CPU_HAS_TIMESTAMPC
#undef CPU_HAS_MSR
#undef CPU_HAS_CMPXCHG8
#undef CPU_HAS_APIC
#undef CPU_HAS_SYSCALL
#undef CPU_HAS_MTRR
#undef CPU_HAS_CMOV
#undef CPU_HAS_FCMOV
#if WANT_MMX
#undef CPU_HAS_MMX
#undef CPU_HAS_FXSAVE
#undef CPU_HAS_SSE 
#undef CPU_HAS_SSE2
#undef CPU_HAS_SSE3
#undef CPU_HAS_EXT_3DNOW
#undef CPU_HAS_3DNOW
#endif

// GCC vector extensions
#if defined(CPU_HAS_MMX) || defined(CPU_HAS_SSE)
    #undef HAVE_VECTOR_EXTENSIONS
#endif

#if CPU_HAS_SSE && defined(__GNUC__)
    #define __sse_align	__attribute__((aligned(16)))
#else
    #define __sse_align	
#endif

// Define to empty if `const' does not conform to ANSI C.
//#undef const

// Define as `__inline' if that's what the C compiler calls it, or to nothing
// if it is not supported.
//#undef inline

// Define to `long' if <sys/types.h> does not define.
//#undef off_t

// Define to `unsigned' if <sys/types.h> does not define.
//#undef size_t

// ---------------------------------------------------
// New additions: Penrillian 13/4/06

// Missing from Symbian's limits.h:
#define PATH_MAX 256

// Define to 1 if wchar_t is typedef'd to another integer type.
#define WCHAR_T_IS_TYPEDEF 1

#endif	// CONFIG_H_01E33670634DAAC779EE5FF41CCBB36F

