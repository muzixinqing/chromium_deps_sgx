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

#pragma once

#ifndef _SGX_TEDMM_H_
#define _SGX_TEDMM_H_

#include "sgx_error.h"
#include "stddef.h"
#include "sgx_defs.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SGX_MEM_COMMIT_IMMEDIATE 0x0800
#define SGX_MEM_RESERVE          0x2000
#define SGX_MEM_DECOMMIT         0x4000
#define SGX_MEM_RELEASE          0x8000

#define SGX_PAGE_NOACCESS          0x01     // -
#define SGX_PAGE_READONLY          0x02     // R
#define SGX_PAGE_READWRITE         0x04     // RW
#define SGX_PAGE_EXECUTE_READ      0x20     // RX
#define SGX_PAGE_EXECUTE_READWRITE 0x40     // RWX

#ifndef SIZE_T
#define SIZE_T size_t
#endif

/* sgx_virtual_protect()
 *
 *
 * Parameters:
 *      addr - page aligned address
 *      size - size as a multiple of page size
 *      new_prot - new page protections
 *               - SGX_PAGE_NOACCESS
 *               - SGX_PAGE_READONLY
 *               - SGX_PAGE_READWRITE
 *               - SGX_PAGE_EXECUTE_READ
 *               - SGX_PAGE_EXECUTE_READWRITE
 *      old_prot - optional, if passed in is set with old page protections
 *      error - optional, if passed in, returns information on failure condition
 *            - SGX_ERROR_UNEXPECTED - General runtime error
 *            - SGX_ERROR_FEATURE_NOT_SUPPORTED - EDMM not supported on platform
 *            - SGX_ERROR_INVALID_PARAMETER - Invalid permission type, non page aligned params, etc
 *            - SGX_ERROR_INVALID_STATE - The pages are not in the correct state for the requested operation
 *            - SGX_ERROR_MEMORY_LOCKED - Special LOCKED regions of memory should not be changed by EDMM functions
 *
 * Return Value:
 *      0 - failure
 *      nonzero - success
 */
int SGXAPI sgx_virtual_protect(void *addr, const size_t size, const uint32_t new_prot, uint32_t* old_prot, sgx_status_t* error);

#ifdef __cplusplus
}
#endif

#endif
