/*===---- stdatomic.h - Standard header for atomic types and operations -----===
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*===-----------------------------------------------------------------------===
*/

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#error "<stdatomic.h> is supported on Windows only when using ICL"
#else /* defined(_MSC_VER) && !defined(__INTEL_COMPILER) */

#ifndef __STDATOMIC_H
#define __STDATOMIC_H

#include <stdbool.h>
#include <wchar.h>

#ifndef __cplusplus

/*All operations used ICC Intrinsic atomic instructions, so always lock_free*/
#define ATOMIC_XXX_LOCK_FREE 2
#define ATOMIC_BOOL_LOCK_FREE       ATOMIC_XXX_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE       ATOMIC_XXX_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE   ATOMIC_XXX_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE   ATOMIC_XXX_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE    ATOMIC_XXX_LOCK_FREE
#define ATOMIC_SHORT_T_LOCK_FREE    ATOMIC_XXX_LOCK_FREE
#define ATOMIC_INT_T_LOCK_FREE      ATOMIC_XXX_LOCK_FREE
#define ATOMIC_LONG_T_LOCK_FREE     ATOMIC_XXX_LOCK_FREE
#define ATOMIC_LLONG_T_LOCK_FREE    ATOMIC_XXX_LOCK_FREE
#define ATOMIC_POINTER_T_LOCK_FREE  ATOMIC_XXX_LOCK_FREE

#define ATOMIC_FLAG_INIT { false }
#define ATOMIC_VAR_INIT(value) {value}

#define atomic_init(ptr, val) ((ptr)->_Value = (val)) 

typedef enum memory_order {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
} memory_order;

#define kill_dependency(y) (y)

#define atomic_is_lock_free(obj) true

#define DECLARE_Atomic(type, atomic_type) typedef struct atomic_type {\
    type _Value;\
} atomic_type;

DECLARE_Atomic(_Bool,              atomic_bool)
DECLARE_Atomic(char,               atomic_char)
DECLARE_Atomic(signed char,        atomic_schar)
DECLARE_Atomic(unsigned char,      atomic_uchar)
DECLARE_Atomic(short,              atomic_short)
DECLARE_Atomic(unsigned short,     atomic_ushort)
DECLARE_Atomic(int,                atomic_int)
DECLARE_Atomic(unsigned int,       atomic_uint)
DECLARE_Atomic(long,               atomic_long)
DECLARE_Atomic(unsigned long,      atomic_ulong)
DECLARE_Atomic(long long,          atomic_llong)
DECLARE_Atomic(unsigned long long, atomic_ullong)
DECLARE_Atomic(size_t,             atomic_size_t)
DECLARE_Atomic(wchar_t,            atomic_wchar_t)

#define atomic_store(object, desired) __atomic_store_explicit(&(object)->_Value, (desired), memory_order_seq_cst)
#define atomic_store_explicit(object, desired, order) __atomic_store_explicit(&(object)->_Value, (desired), (order))

#define atomic_load(object) __atomic_load_explicit(&(object)->_Value, memory_order_seq_cst)
#define atomic_load_explicit(object, order) __atomic_load_explicit(&(object)->_Value, (order))

#define atomic_exchange(object, desired) __atomic_exchange_explicit(&(object)->_Value, (desired), memory_order_seq_cst)
#define atomic_exchange_explicit(object, desired, order) __atomic_exchange_explicit(&(object)->_Value, (desired), (order))

#define atomic_compare_exchange_strong(object, expected, desired) __atomic_compare_exchange_strong_explicit(&(object)->_Value, (expected), (desired), memory_order_seq_cst, memory_order_seq_cst)
#define atomic_compare_exchange_strong_explicit(object, expected, desired, order_s, order_f) __atomic_compare_exchange_strong_explicit(&(object)->_Value, (expected), (desired), (order_s), (order_f))

#define atomic_compare_exchange_weak(object, expected, desired) __atomic_compare_exchange_weak_explicit(&(object)->_Value, (expected), (desired), memory_order_seq_cst, memory_order_seq_cst)
#define atomic_compare_exchange_weak_explicit(object, expected, desired, order_s, order_f) __atomic_compare_exchange_weak_explicit(&(object)->_Value, (expected), (desired), (order_s), (order_f))

#define atomic_fetch_add(object, operand) __atomic_fetch_add_explicit(&(object)->_Value, (operand), memory_order_seq_cst)
#define atomic_fetch_add_explicit(object, operand, order) __atomic_fetch_add_explicit(&(object)->_Value, (operand), (order))

#define atomic_fetch_sub(object, operand) __atomic_fetch_sub_explicit(&(object)->_Value, (operand), memory_order_seq_cst)
#define atomic_fetch_sub_explicit(object, operand, order) __atomic_fetch_sub_explicit(&(object)->_Value, (operand), (order))

#define atomic_fetch_or(object, operand) __atomic_fetch_or_explicit(&(object)->_Value, (operand), memory_order_seq_cst)
#define atomic_fetch_or_explicit(object, operand, order) __atomic_fetch_or_explicit(&(object)->_Value, (operand), (order))

#define atomic_fetch_xor(object, operand) __atomic_fetch_xor_explicit(&(object)->_Value, (operand), memory_order_seq_cst)
#define atomic_fetch_xor_explicit(object, operand, order) __atomic_fetch_xor_explicit(&(object)->_Value, (operand), (order))

#define atomic_fetch_and(object, operand) __atomic_fetch_and_explicit(&(object)->_Value, (operand), memory_order_seq_cst)
#define atomic_fetch_and_explicit(object, operand, order) __atomic_fetch_and_explicit(&(object)->_Value, (operand), (order))

typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;

static _Bool atomic_flag_test_and_set(volatile atomic_flag * flag) {
    return __atomic_flag_test_and_set_explicit(&flag->_Value, memory_order_seq_cst);
}
static _Bool atomic_flag_test_and_set_explicit(volatile atomic_flag * flag, memory_order order) {
    return __atomic_flag_test_and_set_explicit(&flag->_Value, order);
}
static void atomic_flag_clear(volatile atomic_flag * flag) {
    __atomic_flag_clear_explicit(&flag->_Value, memory_order_seq_cst);
}
static void atomic_flag_clear_explicit(volatile atomic_flag * flag, memory_order order) {
    __atomic_flag_clear_explicit(&flag->_Value, order);
}

#define atomic_flag_test_and_set(object) __atomic_flag_test_and_set_explicit(&(object)->_Value, memory_order_seq_cst)
#define atomic_flag_test_and_set_explicit(object, order) __atomic_flag_test_and_set_explicit(&(object)->_Value, (order))

#define atomic_flag_clear(object) __atomic_flag_clear_explicit(&(object)->_Value, memory_order_seq_cst)
#define atomic_flag_clear_explicit(object, order) __atomic_flag_clear_explicit(&(object)->_Value, (order))

#endif //ifndef __cplusplus
#endif /* __CLANG_STDATOMIC_H */

#endif /* defined(_MSC_VER) && !defined(__INTEL_COMPILER) */
