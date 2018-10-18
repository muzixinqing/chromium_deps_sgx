/*	$OpenBSD: math.h,v 1.27 2010/12/14 11:16:15 martynas Exp $	*/
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/*
 * from: @(#)fdlibm.h 5.1 93/09/24
 */

#ifndef _MATH_H_
#define _MATH_H_

#include <sys/_types.h>
#include <sys/cdefs.h>
#include <sys/limits.h>

#include <float.h>

typedef __float_t       float_t;
typedef __double_t      double_t;

#if defined(ANDROID)
#define FP_INFINITE    0x01
#define FP_NAN         0x02
#define FP_NORMAL      0x04
#define FP_SUBNORMAL   0x08
#define FP_ZERO        0x10
#else
#define FP_NAN         0x00
#define FP_INFINITE    0x01
#define FP_ZERO        0x02
#define FP_SUBNORMAL   0x03
#define FP_NORMAL      0x04
#endif

#if defined(ANDROID)
#define FP_ILOGB0       (-INT_MAX)
#define FP_ILOGBNAN     (INT_MAX)
#elif defined(_TLIBC_WIN_)
#define FP_ILOGB0       (-INT_MAX - 1)
#define FP_ILOGBNAN     (INT_MAX)
#elif defined(_TLIBC_GNU_)
#define FP_ILOGB0       (-INT_MAX - 1)
#define FP_ILOGBNAN     (-INT_MAX - 1)
#endif

#ifdef _TLIBC_WIN_
#ifdef __LONG_DOUBLE_SIZE__
#if __LONG_DOUBLE_SIZE__ != 64
#error "ERROR: Only 64-bit long-double is supported at this time."
#endif
#endif
#endif

#define fpclassify(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __fpclassifyf(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __fpclassify(x) \
    :   __fpclassifyl(x))
#define isfinite(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __isfinitef(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __isfinite(x) \
    :   __isfinitel(x))
#define isnormal(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __isnormalf(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __isnormal(x) \
    :   __isnormall(x))
#define signbit(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __signbitf(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __signbit(x) \
    :   __signbitl(x))
#define isinf(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __isinff(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __isinf(x) \
    :   __isinfl(x))
#define isnan(x) \
    ((sizeof (x) == sizeof (float)) ? \
        __isnanf(x) \
    : (sizeof (x) == sizeof (double)) ? \
        __isnan(x) \
    :   __isnanl(x))

#define isgreater(x, y)         (!isunordered((x), (y)) && (x) > (y))
#define isgreaterequal(x, y)    (!isunordered((x), (y)) && (x) >= (y))
#define isless(x, y)            (!isunordered((x), (y)) && (x) < (y))
#define islessequal(x, y)       (!isunordered((x), (y)) && (x) <= (y))
#define islessgreater(x, y)     (!isunordered((x), (y)) && ((x) > (y) || (y) > (x)))
#define isunordered(x, y)       (isnan(x) || isnan(y))

__BEGIN_DECLS

#define HUGE_VAL    ((double)(1e+300 * 1e+300))
#define HUGE_VALF   ((float)HUGE_VAL)
#define HUGE_VALL   ((long double)HUGE_VAL)
#define INFINITY    HUGE_VALF
#define NAN         ((float)(INFINITY * 0.0F))

/*
 * ANSI/POSIX
 */
double _TLIBC_CDECL_ acos(double);
double _TLIBC_CDECL_ asin(double);
double _TLIBC_CDECL_ atan(double);
double _TLIBC_CDECL_ atan2(double, double);
double _TLIBC_CDECL_ cos(double);
double _TLIBC_CDECL_ sin(double);
double _TLIBC_CDECL_ tan(double);

double _TLIBC_CDECL_ cosh(double);
double _TLIBC_CDECL_ sinh(double);
double _TLIBC_CDECL_ tanh(double);

double _TLIBC_CDECL_ exp(double);
double _TLIBC_CDECL_ frexp(double, int *);
double _TLIBC_CDECL_ ldexp(double, int);
double _TLIBC_CDECL_ log(double);
double _TLIBC_CDECL_ log10(double);
double _TLIBC_CDECL_ modf(double, double *);

double _TLIBC_CDECL_ pow(double, double);
double _TLIBC_CDECL_ sqrt(double);

double _TLIBC_CDECL_ ceil(double);
double _TLIBC_CDECL_ fabs(double);
double _TLIBC_CDECL_ floor(double);
double _TLIBC_CDECL_ fmod(double, double);

/*
 * C99
 */
double _TLIBC_CDECL_ acosh(double);
double _TLIBC_CDECL_ asinh(double);
double _TLIBC_CDECL_ atanh(double);

double _TLIBC_CDECL_ exp2(double);  
double _TLIBC_CDECL_ expm1(double);
int    _TLIBC_CDECL_ ilogb(double);
double _TLIBC_CDECL_ log1p(double);
double _TLIBC_CDECL_ log2(double);
double _TLIBC_CDECL_ logb(double);
double _TLIBC_CDECL_ scalbn(double, int);
double _TLIBC_CDECL_ scalbln(double, long int); 

double _TLIBC_CDECL_ cbrt(double);
double _TLIBC_CDECL_ hypot(double, double);

double _TLIBC_CDECL_ erf(double);
double _TLIBC_CDECL_ erfc(double);
double _TLIBC_CDECL_ lgamma(double);
double _TLIBC_CDECL_ tgamma(double);

double _TLIBC_CDECL_ nearbyint(double);
double _TLIBC_CDECL_ rint(double);
long int _TLIBC_CDECL_ lrint(double); 
long long int _TLIBC_CDECL_ llrint(double); 
double _TLIBC_CDECL_ round(double);  
long int _TLIBC_CDECL_ lround(double); 
long long int _TLIBC_CDECL_ llround(double);
double _TLIBC_CDECL_ trunc(double);

double _TLIBC_CDECL_ remainder(double, double);
double _TLIBC_CDECL_ remquo(double, double, int *); 

double _TLIBC_CDECL_ copysign(double, double);
double _TLIBC_CDECL_ nan(const char *);
double _TLIBC_CDECL_ nextafter(double, double);

double _TLIBC_CDECL_ fdim(double, double); 
double _TLIBC_CDECL_ fmax(double, double); 
double _TLIBC_CDECL_ fmin(double, double); 

double _TLIBC_CDECL_ fma(double, double, double);

/*
 * Float versions of C99 functions
 */

float _TLIBC_CDECL_ acosf(float);
float _TLIBC_CDECL_ asinf(float);
float _TLIBC_CDECL_ atanf(float);
float _TLIBC_CDECL_ atan2f(float, float);
float _TLIBC_CDECL_ cosf(float);
float _TLIBC_CDECL_ sinf(float);
float _TLIBC_CDECL_ tanf(float);

float _TLIBC_CDECL_ acoshf(float);
float _TLIBC_CDECL_ asinhf(float);
float _TLIBC_CDECL_ atanhf(float);
float _TLIBC_CDECL_ coshf(float);
float _TLIBC_CDECL_ sinhf(float);
float _TLIBC_CDECL_ tanhf(float);

float _TLIBC_CDECL_ expf(float);
float _TLIBC_CDECL_ exp2f(float); 
float _TLIBC_CDECL_ expm1f(float); 
float _TLIBC_CDECL_ frexpf(float, int *);
int   _TLIBC_CDECL_ ilogbf(float);
float _TLIBC_CDECL_ ldexpf(float, int);
float _TLIBC_CDECL_ logf(float);
float _TLIBC_CDECL_ log10f(float);
float _TLIBC_CDECL_ log1pf(float);
float _TLIBC_CDECL_ log2f(float);
float _TLIBC_CDECL_ logbf(float);
float _TLIBC_CDECL_ modff(float, float *);
float _TLIBC_CDECL_ scalbnf(float, int);
float _TLIBC_CDECL_ scalblnf(float, long int);

float _TLIBC_CDECL_ cbrtf(float);
float _TLIBC_CDECL_ fabsf(float);
float _TLIBC_CDECL_ hypotf(float, float);
float _TLIBC_CDECL_ powf(float, float);
float _TLIBC_CDECL_ sqrtf(float);

float _TLIBC_CDECL_ erff(float);
float _TLIBC_CDECL_ erfcf(float);
float _TLIBC_CDECL_ lgammaf(float);
float _TLIBC_CDECL_ tgammaf(float);

float _TLIBC_CDECL_ ceilf(float);
float _TLIBC_CDECL_ floorf(float);
float _TLIBC_CDECL_ nearbyintf(float);

float _TLIBC_CDECL_ rintf(float);
long int _TLIBC_CDECL_ lrintf(float); 
long long int _TLIBC_CDECL_ llrintf(float); 
float _TLIBC_CDECL_ roundf(float); 
long int _TLIBC_CDECL_ lroundf(float);
long long int _TLIBC_CDECL_ llroundf(float);
float _TLIBC_CDECL_ truncf(float);

float _TLIBC_CDECL_ fmodf(float, float);
float _TLIBC_CDECL_ remainderf(float, float);
float _TLIBC_CDECL_ remquof(float, float, int *);

float _TLIBC_CDECL_ copysignf(float, float);
float _TLIBC_CDECL_ nanf(const char *);
float _TLIBC_CDECL_ nextafterf(float, float);

float _TLIBC_CDECL_ fdimf(float, float);
float _TLIBC_CDECL_ fmaxf(float, float);
float _TLIBC_CDECL_ fminf(float, float);

float _TLIBC_CDECL_ fmaf(float, float, float);

/*
 * Long double versions of C99 functions
 */

/* Macros defining long double functions to be their double counterparts
 * (long double is synonymous with double in this implementation).
 */

#ifndef _TLIBC_WIN_
long double _TLIBC_CDECL_ acosl(long double);
long double _TLIBC_CDECL_ asinl(long double);
long double _TLIBC_CDECL_ atanl(long double);
long double _TLIBC_CDECL_ atan2l(long double, long double);
long double _TLIBC_CDECL_ cosl(long double);
long double _TLIBC_CDECL_ sinl(long double);
long double _TLIBC_CDECL_ tanl(long double);

long double _TLIBC_CDECL_ acoshl(long double);
long double _TLIBC_CDECL_ asinhl(long double);
long double _TLIBC_CDECL_ atanhl(long double);
long double _TLIBC_CDECL_ coshl(long double);
long double _TLIBC_CDECL_ sinhl(long double);
long double _TLIBC_CDECL_ tanhl(long double);

long double _TLIBC_CDECL_ expl(long double);
long double _TLIBC_CDECL_ exp2l(long double);
long double _TLIBC_CDECL_ expm1l(long double);
long double _TLIBC_CDECL_ frexpl(long double, int *);
int         _TLIBC_CDECL_ ilogbl(long double);
long double _TLIBC_CDECL_ ldexpl(long double, int);
long double _TLIBC_CDECL_ logl(long double);
long double _TLIBC_CDECL_ log10l(long double);
long double _TLIBC_CDECL_ log1pl(long double);
long double _TLIBC_CDECL_ log2l(long double);
long double _TLIBC_CDECL_ logbl(long double);
long double _TLIBC_CDECL_ modfl(long double, long double *);
long double _TLIBC_CDECL_ scalbnl(long double, int);
long double _TLIBC_CDECL_ scalblnl(long double, long int);

long double _TLIBC_CDECL_ cbrtl(long double);
long double _TLIBC_CDECL_ fabsl(long double);
long double _TLIBC_CDECL_ hypotl(long double, long double);
long double _TLIBC_CDECL_ powl(long double, long double);
long double _TLIBC_CDECL_ sqrtl(long double);

long double _TLIBC_CDECL_ erfl(long double);
long double _TLIBC_CDECL_ erfcl(long double);
long double _TLIBC_CDECL_ lgammal(long double);
long double _TLIBC_CDECL_ tgammal(long double);

long double _TLIBC_CDECL_ ceill(long double);
long double _TLIBC_CDECL_ floorl(long double);
long double _TLIBC_CDECL_ nearbyintl(long double);
long double _TLIBC_CDECL_ rintl(long double);
long int    _TLIBC_CDECL_ lrintl(long double);
long long int _TLIBC_CDECL_ llrintl(long double);
long double _TLIBC_CDECL_ roundl(long double);
long int    _TLIBC_CDECL_ lroundl(long double);
long long int _TLIBC_CDECL_ llroundl(long double);
long double _TLIBC_CDECL_ truncl(long double);

long double _TLIBC_CDECL_ fmodl(long double, long double);
long double _TLIBC_CDECL_ remainderl(long double, long double);
long double _TLIBC_CDECL_ remquol(long double, long double, int *);

long double _TLIBC_CDECL_ copysignl(long double, long double);
long double _TLIBC_CDECL_ nanl(const char *);
long double _TLIBC_CDECL_ nextafterl(long double, long double);

long double _TLIBC_CDECL_ fdiml(long double, long double);
long double _TLIBC_CDECL_ fmaxl(long double, long double);
long double _TLIBC_CDECL_ fminl(long double, long double);
long double _TLIBC_CDECL_ fmal(long double, long double, long double);
#else /* _TLIBC_WIN_ */

double       _TLIBC_CDECL_ __libm_nexttoward64(double, long double);
float        _TLIBC_CDECL_ __libm_nexttoward64f(float, long double);
long double  _TLIBC_CDECL_ __libm_nexttoward64l(long double, long double);

#ifndef __cplusplus
#define fdiml       fdim
#define acosl       acos
#define asinl       asin
#define atanl       atan
#define atan2l      atan2
#define cosl        cos
#define sinl        sin
#define tanl        tan
#define coshl       cosh
#define sinhl       sinh
#define tanhl       tanh
#define expl        exp
#define frexpl      frexp
#define ldexpl      ldexp
#define logl        log
#define log10l      log10
#define modfl       modf
#define powl        pow
#define sqrtl       sqrt
#define ceill       ceil
#define fabsl       fabs
#define floorl      floor
#define fmodl       fmod
//C99
#define acoshl      acosh
#define asinhl      asinh 
#define atanhl      atanh
#define exp2l       exp2
#define expm1l      expm1
#define ilogbl      ilogb
#define log1pl      log1p
#define log2l       log2
#define logbl       logb
#define scalbnl     scalbn
#define scalblnl    scalbnl
#define cbrtl       cbrt
#define hypotl      hypot
#define erfl        erf
#define erfcl       erfc
#define lgammal     lgamma
#define tgammal     tgamma
#define nearbyintl  nearbyint
#define rintl       rint
#define lrintl      lrint 
#define llrintl     llrint 
#define roundl      round
#define lroundl     lround 
#define llroundl    llround 
#define truncl      trunc
#define remainderl  remainder
#define remquol     remquo
#define copysignl   copysign
#define nanl        nan
#define nextafterl  nextafter
#define fmaxl       fmax
#define fminl       fmin
#define fmal        fma

#define nexttowardl __libm_nexttoward64l
#define nexttoward  __libm_nexttoward64
#define nexttowardf __libm_nexttoward64f

#else  // __cplusplus
inline long double _TLIBC_CDECL_ fdiml(long double x, long double y)
        { return (fdim((double)x, (double)y)); }
inline long double _TLIBC_CDECL_ acosl(long double x)
        { return (acos((double)x)); }
inline long double _TLIBC_CDECL_ asinl(long double x)
        { return (asin((double)x)); }        
inline long double _TLIBC_CDECL_ atanl(long double x)
        { return (atan((double)x)); }
inline long double _TLIBC_CDECL_ atan2l(long double y,  long double x)
        { return (atan2((double)y, (double)x)); }
inline long double _TLIBC_CDECL_ cosl(long double x)
        { return (cos((double)x)); }
inline long double _TLIBC_CDECL_ coshl(long double x)
        { return (cosh((double)x)); }
inline long double _TLIBC_CDECL_ sinl(long double x)
        { return (sin((double)x)); }
inline long double _TLIBC_CDECL_ sinhl(long double x)
        { return (sinh((double)x)); }
inline long double _TLIBC_CDECL_ tanl(long double x)
        { return (tan((double)x)); }
inline long double _TLIBC_CDECL_ tanhl(long double x)
        { return (tanh((double)x)); }

inline long double _TLIBC_CDECL_ expl(long double x)
        { return (exp((double)x)); } 
inline long double _TLIBC_CDECL_ frexpl(long double x, int *y)
        { return (frexp((double)x, y)); }
inline long double _TLIBC_CDECL_ ldexpl(long double x, int y)
        { return (ldexp((double)x, y)); }
inline long double _TLIBC_CDECL_ logl(long double x)
        { return (log((double)x)); }
inline long double _TLIBC_CDECL_ log10l(long double x)
        { return (log10((double)x)); }
inline long double _TLIBC_CDECL_ modfl(long double x, long double *y)
        { double _Di, _Df = modf((double)x, &_Di); *y = (long double)_Di; return (_Df); }
inline long double _TLIBC_CDECL_ powl(long double x, long double y)
        { return (pow((double)x, (double)y)); }
inline long double _TLIBC_CDECL_ sqrtl(long double x)
        { return (sqrt((double)x)); }

inline long double _TLIBC_CDECL_ ceill(long double x)
        { return (ceil((double)x)); }
inline long double _TLIBC_CDECL_ fabsl(long double x)
        { return (fabs((double)x)); }
inline long double _TLIBC_CDECL_ floorl(long double x)
        { return (floor((double)x)); }
inline long double _TLIBC_CDECL_ fmodl(long double x, long double y)
        { return (fmod((double)x, (double)y)); }

inline long double _TLIBC_CDECL_ acoshl(long double x)
        { return (acosh((double)x));}
inline long double _TLIBC_CDECL_ asinhl(long double x)
        { return (asinh((double)x));}
inline long double _TLIBC_CDECL_ atanhl(long double x)
        { return (atanh((double)x));}
inline long double _TLIBC_CDECL_ exp2l(long double x)
        { return (exp2((double)x));}
inline long double _TLIBC_CDECL_ expm1l(long double x)
        { return (expm1((double)x));}
inline int _TLIBC_CDECL_ ilogbl(long double x)
        { return (ilogb((double)x));}
inline long double _TLIBC_CDECL_ log1pl(long double x)
        { return (log1p((double)x));}

inline long double _TLIBC_CDECL_ log2l(long double x)
        { return (log2((double)x));}
inline long double _TLIBC_CDECL_ logbl(long double x)
        { return (logb((double)x));}

inline long double _TLIBC_CDECL_ scalbnl(long double x, int n)
        { return (scalbn((double)x, n)); }
inline long double _TLIBC_CDECL_ scalblnl(long double x, long int n)
        { return (scalbln((double)x, n)); }

inline long double _TLIBC_CDECL_ cbrtl(long double x)
        { return (cbrt((double)x));}
inline long double _TLIBC_CDECL_ hypotl(long double x, long double y)
        { return (hypot((double)x, (double)y)); }

inline long double _TLIBC_CDECL_ erfl(long double x)
        { return (erf((double)x));}
inline long double _TLIBC_CDECL_ erfcl(long double x)
        { return (erfc((double)x));}
inline long double _TLIBC_CDECL_ lgammal(long double x)
        { return (lgamma((double)x));}
inline long double _TLIBC_CDECL_ tgammal(long double x)
        { return (tgamma((double)x));}
inline long double _TLIBC_CDECL_ nearbyintl(long double x)
        { return (nearbyint((double)x));}

inline long double _TLIBC_CDECL_ rintl(long double x)
        { return (rint((double)x));}
inline long int _TLIBC_CDECL_ lrintl(long double x)
        { return (lrint((double)x));}
inline long long int _TLIBC_CDECL_ llrintl(long double x)
        { return (llrint((double)x));}
inline long double _TLIBC_CDECL_ roundl(long double x)
        { return (round((double)x));}
inline long int _TLIBC_CDECL_ lroundl(long double x)
        { return (lround((double)x));}
inline long long int _TLIBC_CDECL_ llroundl(long double x)
        { return (llround((double)x));}
inline long double _TLIBC_CDECL_ truncl(long double x)
        { return (trunc((double)x));}

inline long double _TLIBC_CDECL_ remainderl(long double x, long double y)
        { return (remainder((double)x, (double)y)); }
inline long double _TLIBC_CDECL_ remquol(long double x, long double y, int *quo)
        { return (remquo((double)x, (double)y, quo)); }

inline long double _TLIBC_CDECL_ copysignl(long double x, long double y)
        { return (copysign((double)x, (double)y)); }
static inline long double _TLIBC_CDECL_ nanl(const char * x)
        { return (nan(x));}
inline long double _TLIBC_CDECL_ nextafterl(long double x, long double y)
        { return (nextafter((double)x, (double)y)); }

inline long double _TLIBC_CDECL_ fmaxl(long double x, long double y)
        { return (fmax((double)x, (double)y)); }
inline long double _TLIBC_CDECL_ fminl(long double x, long double y)
        { return (fmin((double)x, (double)y)); }
inline long double _TLIBC_CDECL_ fmal(long double x, long double y, long double z)
        { return (fma((double)x, (double)y, (double)z)); }

inline double nexttoward(double x, long double y)
        { return __libm_nexttoward64(x, y); }
inline float nexttowardf(float x, long double y)
        { return __libm_nexttoward64f(x, y); }
inline long double nexttowardl(long double x, long double y)
        { return __libm_nexttoward64l(x, y); }
#endif //!__cplusplus
#endif /* _TLIBC_WIN_ */

/*
 * Library implementation
 */
int _TLIBC_CDECL_ __fpclassify(double);
int _TLIBC_CDECL_ __fpclassifyf(float);
int _TLIBC_CDECL_ __isfinite(double);
int _TLIBC_CDECL_ __isfinitef(float);
int _TLIBC_CDECL_ __isinf(double);
int _TLIBC_CDECL_ __isinff(float);
int _TLIBC_CDECL_ __isnan(double);
int _TLIBC_CDECL_ __isnanf(float);
int _TLIBC_CDECL_ __isnormal(double);
int _TLIBC_CDECL_ __isnormalf(float);
int _TLIBC_CDECL_ __signbit(double);
int _TLIBC_CDECL_ __signbitf(float);

#ifndef _TLIBC_WIN_
int _TLIBC_CDECL_ __fpclassifyl(long double);
int _TLIBC_CDECL_ __isfinitel(long double);
int _TLIBC_CDECL_ __isinfl(long double);
int _TLIBC_CDECL_ __isnanl(long double);
int _TLIBC_CDECL_ __isnormall(long double);
int _TLIBC_CDECL_ __signbitl(long double);
#else
#define __fpclassifyl(x)    __fpclassify((double)(x))
#define __isfinitel(x)      __isfinite((double)(x))
#define __isinfl(x)         __isinf((double)(x))
#define __isnanl(x)         __isnan((double)(x))
#define __isnormall(x)      __isnormal((double)(x))
#define __signbitl(x)       __signbit((double)(x))
#endif /* _TLIBC_WIN_ */

#ifdef _TLIBC_GNU_
/* 
 * Non-C99 functions.
 */
double _TLIBC_CDECL_ drem(double, double);
double _TLIBC_CDECL_ exp10(double);
double _TLIBC_CDECL_ gamma(double);
double _TLIBC_CDECL_ gamma_r(double, int *);
double _TLIBC_CDECL_ j0(double);
double _TLIBC_CDECL_ j1(double);
double _TLIBC_CDECL_ jn(int, double);
double _TLIBC_CDECL_ lgamma_r(double, int *);
double _TLIBC_CDECL_ pow10(double);
double _TLIBC_CDECL_ scalb(double, double);
/* C99 Macro signbit.*/
double _TLIBC_CDECL_ significand(double);
void   _TLIBC_CDECL_ sincos(double, double *, double *);
double _TLIBC_CDECL_ y0(double);
double _TLIBC_CDECL_ y1(double);
double _TLIBC_CDECL_ yn(int, double);
/* C99 Macro isinf.*/
/* C99 Macro isnan.*/
int    _TLIBC_CDECL_ finite(double);

float _TLIBC_CDECL_ dremf(float, float);
float _TLIBC_CDECL_ exp10f(float);
float _TLIBC_CDECL_ gammaf(float);
float _TLIBC_CDECL_ gammaf_r(float, int *);
float _TLIBC_CDECL_ j0f(float);
float _TLIBC_CDECL_ j1f(float);
float _TLIBC_CDECL_ jnf(int, float);
float _TLIBC_CDECL_ lgammaf_r(float, int *);
float _TLIBC_CDECL_ pow10f(float);
float _TLIBC_CDECL_ scalbf(float, float);
int   _TLIBC_CDECL_ signbitf(float);
float _TLIBC_CDECL_ significandf(float);
void  _TLIBC_CDECL_ sincosf(float, float *, float *);
float _TLIBC_CDECL_ y0f(float);
float _TLIBC_CDECL_ y1f(float);
float _TLIBC_CDECL_ ynf(int, float);
int   _TLIBC_CDECL_ finitef(float);
int   _TLIBC_CDECL_ isinff(float);
int   _TLIBC_CDECL_ isnanf(float);

long double _TLIBC_CDECL_ dreml(long double, long double);
long double _TLIBC_CDECL_ exp10l(long double);
long double _TLIBC_CDECL_ gammal(long double);
long double _TLIBC_CDECL_ gammal_r(long double, int *);
long double _TLIBC_CDECL_ j0l(long double);
long double _TLIBC_CDECL_ j1l(long double);
long double _TLIBC_CDECL_ jnl(int, long double);
long double _TLIBC_CDECL_ lgammal_r(long double, int *);
long double _TLIBC_CDECL_ pow10l(long double);
long double _TLIBC_CDECL_ scalbl(long double, long double);
int         _TLIBC_CDECL_ signbitl(long double);
long double _TLIBC_CDECL_ significandl(long double);
void        _TLIBC_CDECL_ sincosl(long double, long double *, long double *);
long double _TLIBC_CDECL_ y1l(long double);
long double _TLIBC_CDECL_ y0l(long double);
long double _TLIBC_CDECL_ ynl(int, long double);
int         _TLIBC_CDECL_ finitel(long double);
int         _TLIBC_CDECL_ isinfl(long double);
int         _TLIBC_CDECL_ isnanl(long double);

/* 
 * TODO: From Intel Decimal Floating-Point Math Library
 * signbitd32/signbitd64/signbitd128, finited32/finited64/finited128
 * isinfd32/isinfd64/isinfd128, isnand32/isnand64/isnand128
 */
#if defined(__cplusplus) && defined(_TLIBC_GNU_)
/* Clang does not support decimal floating point types.
 *
 * c.f.:
 * http://clang.llvm.org/docs/UsersManual.html#gcc-extensions-not-implemented-yet
 */
#if !defined(__clang__)
typedef float _Decimal32 __attribute__((mode(SD)));
typedef float _Decimal64 __attribute__((mode(DD)));
typedef float _Decimal128 __attribute__((mode(TD)));
#endif
#endif

#endif /* _TLIBC_GNU_ */

__END_DECLS

#endif /* !_MATH_H_ */
