//
// Created by desmond on 18-9-18.
//

#ifndef ENCRYPT_MODEL_D3DES_THRALL_H
#define ENCRYPT_MODEL_D3DES_THRALL_H

#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "openssl/aes.h"

#define LENGTH 16

static const char *des_key = "~!@#$%^&*()_+QWE";

#ifdef __cplusplus
extern "C" {
#endif

int do_encryption_aes(const char *file_to_be_encrypt, int file_length, char **encrypted_file,
                      size_t *encrypted_file_length);

int do_decryption_aes(const char *file_to_be_decrypt, int file_length, char **decrypted_file,
                      size_t *decrypted_file_length);

#ifdef __cplusplus
}
#endif

#endif //ENCRYPT_MODEL_D3DES_THRALL_H
