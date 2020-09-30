#ifndef GCKRPC_LAYER_H_
#define GCKRPC_LAYER_H_

#ifdef _WINDOWS
#pragma pack(push, cryptoki, 1)
#endif
#include "pkcs11/pkcs11.h"
#ifdef _WINDOWS
#pragma pack(pop, cryptoki)
#endif

/* ------------------------------------------------------------------
 * DISPATCHER
 */

/* Call to initialize the module and start listening, returns socket or -1 */
int gck_rpc_layer_initialize(const char *prefix, CK_FUNCTION_LIST_PTR funcs);

/* Should be called to cleanup dispatcher */
void gck_rpc_layer_uninitialize(void);

/* Accept a new connection. Should be called when above fd has read */
void gck_rpc_layer_accept(void);

#endif /* GCKRPC_LAYER_H_ */
