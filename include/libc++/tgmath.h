// -*- C++ -*-
//===-------------------------- tgmath.h ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_TGMATH_H
#define _LIBCPP_TGMATH_H

/*
    tgmath.h synopsis

#include <complex.h>
#include <math.h>

*/

#if defined(_LIBCPP_SGX_CONFIG)
/* Include the proper complex.h header.
 * Not a pretty solution, but better than the alternatives.
 */
#include <../libc++/complex.h>
#else
#include <complex.h>
#endif
#include <math.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

#endif  // _LIBCPP_TGMATH_H
