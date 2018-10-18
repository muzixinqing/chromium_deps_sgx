/*
 *   Copyright(C) 2011-2018 Intel Corporation All Rights Reserved.
 *
 *   The source code, information  and  material ("Material") contained herein is
 *   owned  by Intel Corporation or its suppliers or licensors, and title to such
 *   Material remains  with Intel Corporation  or its suppliers or licensors. The
 *   Material  contains proprietary information  of  Intel or  its  suppliers and
 *   licensors. The  Material is protected by worldwide copyright laws and treaty
 *   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
 *   modified, published, uploaded, posted, transmitted, distributed or disclosed
 *   in any way  without Intel's  prior  express written  permission. No  license
 *   under  any patent, copyright  or  other intellectual property rights  in the
 *   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
 *   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
 *   intellectual  property  rights must  be express  and  approved  by  Intel in
 *   writing.
 *
 *   *Third Party trademarks are the property of their respective owners.
 *
 *   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
 *   this  notice or  any other notice embedded  in Materials by Intel or Intel's
 *   suppliers or licensors in any way.
 *
 */


#ifndef _INC_EH
#define _INC_EH

#ifndef __cplusplus
#error "eh.h is only for C++!"
#endif

typedef void (__cdecl *terminate_handler)();

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
__declspec(noreturn) void __cdecl terminate(void) noexcept;
extern "C" void __std_terminate(void); // this is needed by VS2015 compiler not icc16
terminate_handler __cdecl set_terminate(terminate_handler _new_func) noexcept;
#else
__declspec(noreturn) void __cdecl terminate(void);
terminate_handler __cdecl set_terminate(terminate_handler _new_func);
#endif
#endif /* _INC_EH */
