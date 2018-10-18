#ifndef _ICC2MSVS_INTR_ATOMIC_H
#define _ICC2MSVS_INTR_ATOMIC_H

// Intrinsic map (ICC to MSVS)
#if !defined(_MSC_VER) || defined(__INTEL_COMPILER)
#error Should only include this header from a MSVC compiler
#endif

extern "C" {
/**
 * Intrinsic declarations are inspired from Visual C++ include/intrin.h
 */

#if !defined (_M_X64)
#define __ATOMIC_INTR_CDECL __cdecl
#else
#define __ATOMIC_INTR_CDECL
#endif

    unsigned char _interlockedbittestandset(volatile long *a, long b);
    void _ReadWriteBarrier(void);

    long __ATOMIC_INTR_CDECL _InterlockedExchange(long volatile * _Target, long _Value);

    char _InterlockedExchangeAdd8(char volatile * _Addend, char _Value);
    short _InterlockedExchangeAdd16(short volatile * _Addend, short _Value);
    long __ATOMIC_INTR_CDECL _InterlockedExchangeAdd(long volatile * Addend, long Value);

    char _InterlockedAnd8(char volatile * _Addend, char _Value);
    char _InterlockedXor8(char volatile * _Addend, char _Value);
    char _InterlockedOr8(char volatile * _Addend, char _Value);
    char _InterlockedCompareExchange8(char volatile * _Destination, char _Exchange, char _Comparand);

    short _InterlockedAnd16(short volatile * _Addend, short _Value);
    short _InterlockedXor16(short volatile * _Addend, short _Value);
    short _InterlockedOr16(short volatile * _Addend, short _Value);
    short _InterlockedCompareExchange16(short volatile * _Destination, short _Exchange, short _Comparand);

    long _InterlockedAnd(long volatile * Addend, long Value);
    long _InterlockedXor(long volatile * Addend, long Value);
    long _InterlockedOr(long volatile * Addend, long Value);
    long _InterlockedCompareExchange(long volatile * _Destination, long _Exchange, long _Comparand);


#if defined (_M_X64)
    /* Intrinsics with 64 suffix are only available for the x64 target */
    __int64 _InterlockedExchangeAdd64(__int64 volatile *Addend, __int64 Value);
    __int64 _InterlockedAnd64(__int64 volatile *Addend, __int64 Value);
    __int64 _InterlockedXor64(__int64 volatile *Addend, __int64 Value);
    __int64 _InterlockedOr64(__int64 volatile *Addend, __int64 Value);
#endif /* X64 */
    __int64 _InterlockedCompareExchange64(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand);
} /* extern "C" */

namespace _atomic_msvc_wrapper {

    /**
     * In order to pass functions as template parameters, they need to be
     * actual functions (i.e. not intrinsics). Otherwise we will get a
     * linker error.
     * To solve this, we use wrapper functions that call the intrinsics.
     */
    static inline char InterlockedExchangeAdd8(volatile char *a, char v) {
        return _InterlockedExchangeAdd8(a, v);
    }

    static inline char InterlockedAnd8(volatile char *a, char v) {
        return _InterlockedAnd8(a, v);
    }

    static inline char InterlockedXor8(volatile char *a, char v) {
        return _InterlockedXor8(a, v);
    }

    static inline char InterlockedOr8(volatile char *a, char v) {
        return _InterlockedOr8(a, v);
    }

    static inline bool InterlockedCompareExchange8(volatile char *__val, volatile char __expected, char __after) {
		return(__expected == _InterlockedCompareExchange8(__val, __after, __expected));
    }

    static inline short InterlockedExchangeAdd16(volatile short *a, short v) {
        return _InterlockedExchangeAdd16(a, v);
    }

    static inline short InterlockedAnd16(volatile short *a, short v) {
        return _InterlockedAnd16(a, v);
    }

    static inline short InterlockedXor16(volatile short *a, short v) {
        return _InterlockedXor16(a, v);
    }

    static inline short InterlockedOr16(volatile short *a, short v) {
        return _InterlockedOr16(a, v);
    }

    static inline bool InterlockedCompareExchange16(volatile short *__val, volatile short __expected, short __after) {
		return(__expected == _InterlockedCompareExchange16(__val, __after, __expected));
    }

    static inline long InterlockedExchangeAdd(volatile long *a, long v) {
        return _InterlockedExchangeAdd(a, v);
    }

    static inline long InterlockedAnd(volatile long *a, long v) {
        return _InterlockedAnd(a, v);
    }

    static inline long InterlockedXor(volatile long *a, long v) {
        return _InterlockedXor(a, v);
    }

    static inline long InterlockedOr(volatile long *a, long v) {
        return _InterlockedOr(a, v);
    }

    static inline bool InterlockedCompareExchange(volatile long *__val, volatile long __expected, long __after) {
		return(__expected == _InterlockedCompareExchange(__val, __after, __expected));
    }

#if defined (_M_X64)
    static inline __int64 InterlockedExchangeAdd64(__int64 volatile *Ptr, __int64 Value) {
        return _InterlockedExchangeAdd64(Ptr, Value);
    }

    static inline __int64 InterlockedAnd64(__int64 volatile *Ptr, __int64 Value) {
        return _InterlockedAnd64(Ptr, Value);
    }

    static inline __int64 InterlockedXor64(__int64 volatile *Ptr, __int64 Value) {
        return _InterlockedXor64(Ptr, Value);
    }

    static inline __int64 InterlockedOr64(__int64 volatile *Ptr, __int64 Value) {
        return _InterlockedOr64(Ptr, Value);
    }
#else
    /**
     * Implementation of the 64-bit versions of the intrinsics.
     * The base function is AtomicTryLoop, which tries to do the atomic operation
     * until it succeeds.
     * The writing is based on the _InterlockedCompareExchange64 intrinsic, which
     * is available for the x86 target.
     * This function has a template parameter with the operation (add, or, etc).
     */
    extern "C" __int64 _InterlockedCompareExchange64(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand);

    static inline __int64 op_second(__int64, __int64 b) {
        return b;
    }

    static inline __int64 op_add(__int64 a, __int64 b) {
        return a + b;
    }

    static inline __int64 op_and(__int64 a, __int64 b) {
        return a & b;
    }

    static inline __int64 op_xor(__int64 a, __int64 b) {
        return a ^ b;
    }

    static inline __int64 op_or(__int64 a, __int64 b) {
        return a | b;
    }

    template<__int64(*F)(__int64, __int64)>
    static inline __int64 AtomicTryLoop(__int64 volatile *Ptr, __int64 Value) {
        __int64 OldVal, NewVal;
        _ReadWriteBarrier();
        do {
            OldVal = *Ptr;
            NewVal = F(OldVal, Value);
        } while (OldVal != _InterlockedCompareExchange64(Ptr, NewVal, OldVal));
        _ReadWriteBarrier();
        return OldVal;
    }

    static inline __int64 InterlockedExchange64(__int64 volatile *Ptr, __int64 Value) {
        return AtomicTryLoop<op_second>(Ptr, Value);
    }

    static inline __int64 InterlockedExchangeAdd64(__int64 volatile *Ptr, __int64 Value) {
        return AtomicTryLoop<op_add>(Ptr, Value);
    }

    static inline __int64 InterlockedAnd64(__int64 volatile *Ptr, __int64 Value) {
        return AtomicTryLoop<op_and>(Ptr, Value);
    }

    static inline __int64 InterlockedXor64(__int64 volatile *Ptr, __int64 Value) {
        return AtomicTryLoop<op_xor>(Ptr, Value);
    }

    static inline __int64 InterlockedOr64(__int64 volatile *Ptr, __int64 Value) {
        return AtomicTryLoop<op_or>(Ptr, Value);
    }
#endif /* !x64 */

    static inline bool InterlockedCompareExchange64(volatile __int64 *__val, volatile __int64 __expected, __int64 __after) {
		return(__expected == _InterlockedCompareExchange64(__val, __after, __expected));
    }


    /**
     * Utility function for calling the desired function and inserting
     * explicit casts as required.
     * There are no available intrinsics for 'int', so we need to cast 'int'
     * to another type that has the same size (from 'char', 'short', 'long'
     * and '__int64'. After we call the intrinsic, we need to ast back to the
     * original type.
     */
    template <typename _Tp, typename basetype, basetype(*F)(volatile basetype *, basetype)>
    static inline _Tp cast_call_and_cast(volatile _Tp *a, _Tp v) {
        // Make sure we only change the semantic of the variable (i.e.
        // we don't generate sign/zero extend or truncate) by checking
        // the size of the 2 types.
        static_assert(sizeof(_Tp) == sizeof(basetype), "Unsupported size");
        return static_cast<_Tp>(F(
            (volatile basetype *)(a),
            static_cast<basetype>(v)));
    }

    /**
     * Use a class parameterized by the size of the type that has specific
     * implementation for 1, 2, 4 and 8.
     * The 4 methods in this class will call the required MSVC intrinsic by
     * using the utility function for casting.
     */
    template<size_t N>
    struct FetchClass {
    };

    /**
     * For most sizes, the atomic loads/stores are simple reads/writes
     * from/to the memory.
     * The exception is sizeof(_Tp) == 8, for x86.
     * In this case, we need intrinsics.
     * For load, we use OR with 0 in order to obtain the value, without modifing it.
     * For store, we exchange the value with a new one (and ignore the old value).
     */
    template<size_t N>
    struct LoadStoreClass {
        static inline void barrier(memory_order m) {
            if (m != memory_order_relaxed) {
                _ReadWriteBarrier();
            }
        }
        template<typename _Tp>
        static inline _Tp load(volatile const _Tp *a) {
            static_assert(sizeof(_Tp) == N, "Unsupported size");
            return *a;
        }
        template<typename _Tp>
        static inline void store(volatile _Tp *a, _Tp v) {
            static_assert(sizeof(_Tp) == N, "Unsupported size");
            *a = v;
        }
    };
#if !defined (_M_X64)
    template<>
    struct LoadStoreClass<8> {
        static inline void barrier(memory_order) {
            // Nothing to do.
            // Barriers are required only for normal read/writes,
            // not for Interlocked intrinsics.
        }
        template<typename _Tp>
        static inline _Tp load(volatile const _Tp *a) {
            static_assert(sizeof(_Tp) == sizeof(__int64), "Unsupported size");
            __int64 Value = InterlockedOr64((volatile __int64 *)a, 0);
            return (_Tp)Value;
        }
        template<typename _Tp>
        static inline _Tp store(volatile _Tp *a, _Tp v) {
            static_assert(sizeof(_Tp) == sizeof(__int64), "Unsupported size");
            InterlockedExchange64((volatile __int64 *)a, (__int64)v);
        }
    };
#endif

    // Handle operations for char type
    template<>
    struct FetchClass<1> {
        typedef char basetype;
        template<typename _Tp>
        static inline _Tp add(volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedExchangeAdd8>(a, v);
        }
        template<typename _Tp>
        static inline _Tp and (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedAnd8>(a, v);
        }
        template<typename _Tp>
        static inline _Tp xor (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedXor8>(a, v);
        }
        template<typename _Tp>
        static inline _Tp or (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedOr8>(a, v);
        }
        template<typename _Tp>
        static inline bool compare_exchange (volatile _Tp *__val, volatile _Tp __expected, _Tp __after){
            return InterlockedCompareExchange8(__val, __expected, __after);
        }
    };

    // Handle operations for short type
    template<>
    struct FetchClass<2> {
        typedef short basetype;
        template<typename _Tp>
        static inline _Tp add(volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedExchangeAdd16>(a, v);
        }
        template<typename _Tp>
        static inline _Tp and (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedAnd16>(a, v);
        }
        template<typename _Tp>
        static inline _Tp xor (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedXor16>(a, v);
        }
        template<typename _Tp>
        static inline _Tp or (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedOr16>(a, v);
        }
        template<typename _Tp>
        static inline bool compare_exchange (volatile _Tp *__val, volatile _Tp __expected, _Tp __after){
            return InterlockedCompareExchange16(__val, __expected, __after);
        }
    };

    // Handle operations for long type
    template<>
    struct FetchClass<4> {
        typedef long basetype;
        template<typename _Tp>
        static inline _Tp * add(_Tp * volatile *a, ptrdiff_t v) {
            static_assert(sizeof(ptrdiff_t) <= sizeof(basetype), "Unsupported size");
            static_assert(sizeof(_Tp *) == sizeof(basetype), "Unsupported size");
            return reinterpret_cast<_Tp *>(InterlockedExchangeAdd(
                (volatile basetype *)(a),
                static_cast<basetype>(v)));
        }
        template<typename _Tp>
        static inline _Tp add(volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedExchangeAdd>(a, v);
        }
        template<typename _Tp>
        static inline _Tp and (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedAnd>(a, v);
        }
        template<typename _Tp>
        static inline _Tp xor (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedXor>(a, v);
        }
        template<typename _Tp>
        static inline _Tp or (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedOr>(a, v);
        }
        template<typename _Tp>
        static inline bool compare_exchange (volatile _Tp *__val, volatile _Tp __expected, _Tp __after){
            return InterlockedCompareExchange(__val, __expected, __after);
        }
    };

    // Handle operations for __int64 type
    template<>
    struct FetchClass<8> {
        typedef __int64 basetype;
        template<typename _Tp>
        static inline _Tp * add(_Tp * volatile *a, ptrdiff_t v) {
            static_assert(sizeof(ptrdiff_t) <= sizeof(basetype), "Unsupported size");
            static_assert(sizeof(_Tp *) == sizeof(basetype), "Unsupported size");
            return reinterpret_cast<_Tp *>(InterlockedExchangeAdd64(
                (volatile basetype *)(a),
                static_cast<basetype>(v)));
        }
        template<typename _Tp>
        static inline _Tp add(volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedExchangeAdd64>(a, v);
        }
        template<typename _Tp>
        static inline _Tp and (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedAnd64>(a, v);
        }
        template<typename _Tp>
        static inline _Tp xor (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedXor64>(a, v);
        }
        template<typename _Tp>
        static inline _Tp or (volatile _Tp *a, _Tp v) {
            return cast_call_and_cast<_Tp, basetype, InterlockedOr64>(a, v);
        }
        template<typename _Tp>
        static inline bool compare_exchange (volatile _Tp *__val, volatile _Tp __expected, _Tp __after){
            return InterlockedCompareExchange64(__val, __expected, __after);
        }
    };

} // end namespace

// ICC intrinsic-like wrappers
template<class _Tp>
static inline _Tp __atomic_fetch_add_explicit(volatile _Tp *a, _Tp op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::add<_Tp>(a, op);
}

// This version of add is used by std::atomic<int *> aip;
template<class _Tp>
static inline _Tp * __atomic_fetch_add_explicit(_Tp * volatile *a, ptrdiff_t op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp *)>::add<_Tp>(a, op);
}

template<class _Tp>
static inline _Tp __atomic_add_fetch_explicit(volatile _Tp *a, _Tp op, memory_order) {
    _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::add<_Tp>(a, op);
    return *a;
}

// This version of add is used by std::atomic<int *> aip;
template<class _Tp>
static inline _Tp * __atomic_add_fetch_explicit(_Tp * volatile *a, ptrdiff_t op, memory_order) {
    _atomic_msvc_wrapper::FetchClass<sizeof(_Tp *)>::add<_Tp>(a, op);
    return a;
}

template<class _Tp>
static inline _Tp __atomic_fetch_sub_explicit(volatile _Tp *a, _Tp op, memory_order) {
    // Sub is an add with the negative of the value.
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::add<_Tp>(a, 0 - op);
}

// This version of sub is used by std::atomic<int *> aip;
template<class _Tp>
static inline _Tp * __atomic_fetch_sub_explicit(_Tp * volatile *a, ptrdiff_t op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp *)>::add<_Tp>(a, 0 - op);
}

template<class _Tp>
static inline _Tp __atomic_fetch_and_explicit(volatile _Tp *a, _Tp op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::and<_Tp>(a, op);
}

template<class _Tp>
static inline _Tp __atomic_fetch_xor_explicit(volatile _Tp *a, _Tp op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::xor<_Tp>(a, op);
}

template<class _Tp>
static inline _Tp __atomic_fetch_or_explicit(volatile _Tp *a, _Tp op, memory_order) {
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::or<_Tp>(a, op);
}

static inline bool __atomic_flag_test_and_set_explicit(volatile long *a, memory_order) {
    // Use double negation (!!) to change the type to bool without casting.
    return !!_interlockedbittestandset(a, 0);
}

template<class _Tp>
static inline void __atomic_store_explicit(volatile _Tp *a, _Tp Value, memory_order m) {
    _atomic_msvc_wrapper::LoadStoreClass<sizeof(_Tp)>::barrier(m);

    switch (m) {
    default:
        assert(false);
        return;
    case memory_order_relaxed:
    case memory_order_release:
    case memory_order_seq_cst:
        _atomic_msvc_wrapper::LoadStoreClass<sizeof(_Tp)>::store<_Tp>(a, Value);
        break;
    }
}

template<class _Tp>
static inline _Tp __atomic_load_explicit(volatile _Tp const *a, memory_order m) {
    _Tp Value = 0;
    switch (m) {
    default:
        assert(false);
        return 0;
    case memory_order_relaxed:
    case memory_order_consume:
    case memory_order_acquire:
    case memory_order_seq_cst:
        Value = _atomic_msvc_wrapper::LoadStoreClass<sizeof(_Tp)>::load<_Tp>(a);
        break;
    }

    _atomic_msvc_wrapper::LoadStoreClass<sizeof(_Tp)>::barrier(m);
    return Value;
}

template<class _Tp>
static inline _Tp __atomic_load_explicit(_Tp const *a, memory_order m) {
    return __atomic_load_explicit((volatile _Tp const *)a, m);
}

template<class _Tp>
static inline void __atomic_flag_clear_explicit(volatile _Tp *a, memory_order m) {
    __atomic_store_explicit(a, static_cast<_Tp>(0), m);
}

template<class _Tp>
static inline bool __atomic_compare_exchange_strong_explicit(volatile _Tp *__val, volatile _Tp *__expected, _Tp __after, int, int)
{
    return _atomic_msvc_wrapper::FetchClass<sizeof(_Tp)>::compare_exchange<_Tp>(__val, *__expected, __after);
}

#endif /* _ICC2MSVS_INTR_ATOMIC_H */
