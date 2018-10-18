/* STLport configuration file
 * It is internal STLport header - DO NOT include it directly */

#define _STLP_SGX_CONFIG                1

/* Use new C headers in STLport instead */
#define _STLP_HAS_NO_NEW_C_HEADERS      1

//#define _STLP_USE_NATIVE_STDEXCEPT    1
//#define _STLP_NO_EXCEPTION_HEADER     1

/* Disable wcstombs, wctomb */
#define _STLP_NO_NATIVE_WIDE_STREAMS    1

/* Use separated C/C++ Runtime directories */
#define _STLP_NATIVE_C_INCLUDE_PATH                 tlibc
#define _STLP_NATIVE_CPP_RUNTIME_INCLUDE_PATH       stdc++

/* No I/O operations that involve OCalls allowed */
#define _STLP_NO_IOSTREAMS              1

/* Do not use secure routines in CRT */
#define _CRT_SECURE_NO_DEPRECATE        1

/* Do not support move semantic (C++11) */
#define _STLP_NO_MOVE_SEMANTIC          1
