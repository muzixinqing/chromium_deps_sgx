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

#ifndef _SGX_UKEY_EXCHANGE_H_
#define _SGX_UKEY_EXCHANGE_H_

#include "sgx_eid.h"
#include "sgx_defs.h"
#include "sgx_key_exchange.h"

#ifdef  __cplusplus
extern "C" {
#endif


typedef sgx_status_t (* sgx_ecall_get_ga_trusted_t)(
    sgx_enclave_id_t eid,
    sgx_status_t* retval,
    sgx_ra_context_t context,
    sgx_ec256_public_t *g_a);

typedef sgx_status_t (* sgx_ecall_proc_msg2_trusted_t)(
    sgx_enclave_id_t eid,
    sgx_status_t* retval,
    sgx_ra_context_t context,
    const sgx_ra_msg2_t *p_msg2,
    const sgx_target_info_t *p_qe_target,
    sgx_report_t *p_report,
    sgx_quote_nonce_t* nonce);

typedef sgx_status_t (* sgx_ecall_get_msg3_trusted_t)(
    sgx_enclave_id_t eid,
    sgx_status_t* retval,
    sgx_ra_context_t context,
    uint32_t quote_size,
    sgx_report_t* qe_report,
    sgx_ra_msg3_t *p_msg3,
    uint32_t msg3_size);

/*
 * sgx_ra_get_msg1 is used to get the remote attestation and key exchange
 * protocol message 1 to send to a service provider. The application enclave
 * should use sgx_ra_init function to create the remote attestation and key
 * exchange process context and return to the untrusted code, before the
 * untrusted code can invoke this function.
 *
 * @param context       Context returned by the sgx_ra_init function inside the
 *                      application enclave.
 * @param eid           ID of the application enclave which is going to be
 *                      attested.
 * @param p_get_ga      Function pointer of the ECALL proxy sgx_ra_get_ga
 *                      generated by sgx_edger8r. The application enclave should
 *                      link with sgx_tkey_exchange library and import
 *                      sgx_tkey_exchange.edl in the enclave's EDL file to
 *                      expose the ECALL proxy for sgx_ra_get_ga.
 * @param p_msg1        Message 1 used by the remote attestation and key
 *                      exchange protocol.
 * @return sgx_status_t SGX_SUCCESS                     Indicates success.
 *                      SGX_ERROR_INVALID_PARAMETER     Invalid input parameters
 *                                                      detected.
 *                      SGX_ERROR_AE_INVALID_EPIDBLOB   The EPID blob is
 *                                                      corrupted.
 *                      SGX_ERROR_INVALID_STATE         SGX API is invoked in
 *                                                      incorrect order or
 *                                                      state.
 *                      SGX_ERROR_EPID_MEMBER_REVOKED   The EPID group
 *                                                      membership revoked.
 *                      SGX_ERROR_BUSY                  The requested service is
 *                                                      temporarily not
 *                                                      available.
 *                      SGX_ERROR_UPDATE_NEEDED         SGX needs to be updated.
 *                      SGX_ERROR_SERVICE_UNAVAILABLE   The AE service did not
 *                                                      respond.
 *                      SGX_ERROR_SERVICE_TIMEOUT       A request to the AE
 *                                                      service timed out.
 *                      SGX_ERROR_NETWORK_FAILURE       Network connecting or
 *                                                      proxy setting issue was
 *                                                      encountered.
 *                      SGX_ERROR_OUT_OF_MEMORY         There is not enough
 *                                                      memory available to
 *                                                      complete this operation.
 *                      SGX_ERROR_UNEXPECTED            Indicates an unexpected
 *                                                      error occurs.
 *                      And other possible return code from sgx_ecall.
 */
sgx_status_t SGXAPI sgx_ra_get_msg1(
    sgx_ra_context_t context,
    sgx_enclave_id_t eid,
    sgx_ecall_get_ga_trusted_t p_get_ga,
    sgx_ra_msg1_t *p_msg1);

/*
 * sgx_ra_proc_msg2 is used to process the remote attestation and key exchange
 * protocol message 2 from the service provider and generate message 3 to send
 * to the service provider. If the service provider accepts message 3,
 * negotiated session keys between the application enclave and the service
 * provider are ready for use. The application enclave can use sgx_ra_get_keys
 * function to retrieve the negotiated keys and use sgx_ra_close function to
 * release the context of the remote attestation and key exchange process.
 *
 * @param context       Context returned by the sgx_ra_init function inside the
 *                      application enclave.
 * @param eid           ID of the application enclave which is going to be
 *                      attested.
 * @param p_proc_msg2   Function pointer of the ECALL proxy sgx_ra_proc_msg2_trusted
 *                      generated by sgx_edger8r. The application enclave should
 *                      link with sgx_tkey_exchange library and import the
 *                      sgx_tkey_exchange.edl in the application enclave's EDL
 *                      file to expose the ECALL proxy for sgx_ra_proc_msg2.
 * @param p_get_msg3    Function pointer of the ECALL proxy sgx_ra_get_msg3_trusted
 *                      generated by sgx_edger8r. The application enclave should
 *                      link with sgx_tkey_exchange library and import the
 *                      sgx_tkey_exchange.edl in the application enclave's EDL
 *                      file to expose the ECALL proxy for sgx_ra_get_msg3.
 * @param p_msg2        sgx_ra_msg2_t message 2 from the service provider
 *                      received by application.
 * @param msg2_size     The length of msg2 (in bytes).
 * @param pp_msg3       sgx_ra_msg3_t message 3 to be sent to the service
 *                      provider. The message buffer is allocated by the
 *                      sgx_ukey_exchange library. The caller should free the
 *                      buffer after use.
 * @param p_msg3_size   The length of msg3 (in bytes).
 * @return sgx_status_t SGX_SUCCESS                     Indicates success.
 *                      SGX_ERROR_INVALID_PARAMETER     Invalid input parameters
 *                                                      detected.
 *                      SGX_ERROR_AE_INVALID_EPIDBLOB   The EPID blob is
 *                                                      corrupted.
 *                      SGX_ERROR_INVALID_STATE         SGX API is invoked in
 *                                                      incorrect order or
 *                                                      state.
 *                      SGX_ERROR_EPID_MEMBER_REVOKED   The EPID group
 *                                                      membership revoked.
 *                      SGX_ERROR_INVALID_SIGNATURE     The signature is invalid.
 *                      SGX_ERROR_MAC_MISMATCH          Indicates verification
 *                                                      error for reports, sealed 
 *                                                      data, etc.
 *                      SGX_ERROR_KDF_MISMATCH          Indicates key derivation
 *                                                      function doesn't match.
 *                      SGX_ERROR_BUSY                  The requested service is
 *                                                      temporarily not
 *                                                      available.
 *                      SGX_ERROR_UPDATE_NEEDED         SGX needs to be updated.
 *                      SGX_ERROR_SERVICE_UNAVAILABLE   The AE service did not
 *                                                      respond.
 *                      SGX_ERROR_SERVICE_TIMEOUT       A request to the AE
 *                                                      service timed out.
 *                      SGX_ERROR_NETWORK_FAILURE       Network connecting or
 *                                                      proxy setting issue was
 *                                                      encountered.
 *                      SGX_ERROR_OUT_OF_MEMORY         There is not enough
 *                                                      memory available to
 *                                                      complete this operation.
 *                      SGX_ERROR_UNEXPECTED            Indicates an unexpected
 *                                                      error occurs.
 *                      And other possible return code from sgx_ecall.
 */
sgx_status_t SGXAPI sgx_ra_proc_msg2(
    sgx_ra_context_t context,
    sgx_enclave_id_t eid,
    sgx_ecall_proc_msg2_trusted_t p_proc_msg2,
    sgx_ecall_get_msg3_trusted_t p_get_msg3,
    const sgx_ra_msg2_t *p_msg2,
    uint32_t msg2_size,
    sgx_ra_msg3_t **pp_msg3,
    uint32_t *p_msg3_size);

#ifdef  __cplusplus
}
#endif

#endif
