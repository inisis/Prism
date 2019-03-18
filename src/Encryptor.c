#include "Encryptor.h"
//
// Created by desmond on 18-9-26.
//

#define MEMCHECK(variable, tag) \
    if (variable == NULL){ \
    printf("memory allocation failed\n"); \
    goto tag;}  \

int do_encryption_aes(const char* file_to_be_encrypt, int file_length, char ** encrypted_file, size_t *encrypted_file_length)
{

    //init key
    AES_KEY encrypt_key;

    AES_set_encrypt_key((unsigned char *)des_key, LENGTH * 8, &encrypt_key);

    unsigned char vi[LENGTH * 8] = {};

    if(file_to_be_encrypt == NULL)
        return -1;

    size_t i = 0;

    size_t pad_length = file_length % LENGTH == 0 ? file_length : ((file_length / LENGTH) + 1)* LENGTH;

    char* file_new = (char *)calloc(sizeof(unsigned char), pad_length + 1);
    MEMCHECK(file_new, exit1);
    memcpy(file_new, file_to_be_encrypt, pad_length + 1);

    *encrypted_file = (char *)calloc(sizeof(unsigned char), pad_length + 5);
    MEMCHECK(encrypted_file,exit2);

    for (i = 0; i < pad_length; i += LENGTH)
    {
        AES_cbc_encrypt((unsigned char *)file_new + i, (unsigned char *)(*encrypted_file + i), LENGTH, &encrypt_key, vi, AES_ENCRYPT);
    }

    *(int *)(*encrypted_file + pad_length) = file_length;

    *(*encrypted_file + pad_length + 4) = '\0';

    *encrypted_file_length = pad_length + 4;

    exit2:

    free(file_new);

    exit1:

    return 0;
}

int do_decryption_aes(const char* file_to_be_decrypt, int file_length, char ** decrypted_file, size_t *decrypted_file_length)
{

    //init key
    AES_KEY decrypt_key;

    AES_set_decrypt_key((unsigned char *)des_key, LENGTH * 8, &decrypt_key);

    unsigned char vi[LENGTH * 8] = {};

    if(file_to_be_decrypt == NULL)
        return -1;

    size_t i = 0;

    size_t pad_length = (file_length % LENGTH) == 0 ? file_length : (file_length - file_length % LENGTH);

    char *file_new = (char *)calloc(sizeof(unsigned char), pad_length);
    MEMCHECK(file_new, exit1);

    for (i = 0; i < pad_length; i += LENGTH)
    {
        AES_cbc_encrypt((unsigned char *)file_to_be_decrypt + i, (unsigned char *)(file_new + i), LENGTH, &decrypt_key, vi, AES_DECRYPT);
    }

    int real_size = *(int *)(file_to_be_decrypt + pad_length);

    *decrypted_file = (char *)calloc(sizeof(unsigned char), real_size + 1);
    MEMCHECK(decrypted_file, exit2);

    memcpy(*decrypted_file, file_new, real_size);

    *(*decrypted_file + real_size) = '\0';

    *decrypted_file_length = real_size;

    exit2:

    free(file_new);

    exit1:
    return 0;
}