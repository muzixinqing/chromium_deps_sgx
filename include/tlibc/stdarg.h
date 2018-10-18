/*	$OpenBSD: stdarg.h,v 1.14 2010/12/30 05:01:36 tedu Exp $	*/
/*	$NetBSD: stdarg.h,v 1.12 1995/12/25 23:15:31 mycroft Exp $	*/

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdarg.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _STDARG_H_
#define _STDARG_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

typedef __va_list   va_list;

#if defined (_TLIBC_WIN_)
#define __va_size(type)     (((sizeof(type) + sizeof(void*) - 1) / sizeof(void*)) * sizeof(void*))
#ifdef _TLIBC_X86_
#ifdef __cplusplus
#define __va_addr(type)     (&reinterpret_cast<const char &>(type))
#else
#define __va_addr(type)     ((char *)&(type))
#endif /* __cplusplus */
#define va_start(ap, last)  ((ap) = (va_list)(__va_size(last) + __va_addr(last)))
#else /* _TLIBC_X64_ */
#ifdef __cplusplus
extern "C" void __cdecl __va_start(va_list *, ...);
#else
void __cdecl __va_start(va_list *, ...);
#endif /* __cplusplus */
#define va_start(ap, last) ( __va_start(&ap, last) )
#endif /* _TLIBC_X64_ */
#define va_copy(dst, src)   ((dst) = (src))
#define va_arg(ap, type)    (*(type *)((ap) += __va_size(type), (ap) - __va_size(type)))
#define va_end(ap)          ((ap) = (va_list)0)
#elif defined(_TLIBC_GNU_)
#define va_start(ap, last)  __builtin_va_start((ap), last)
#define va_end              __builtin_va_end
#define va_arg              __builtin_va_arg
#define va_copy(dst, src)   __builtin_va_copy((dst),(src))
#endif

#endif /* !_STDARG_H_ */
