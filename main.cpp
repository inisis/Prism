#include <iostream>
#include "string"
#include "Encryptor.h"
#if defined(__linux__)
    #include <getopt.h>
#endif

using namespace std;

void
print_help()
{
    printf("Encryptor [options] sourcefile destinationfile\n"
           "   -h, --help             print help\n"
           "\n");
    printf("   -e, --encrypt          perform encryption\n"
           "   -d, --decrypt          perform decryption\n"
           "\n");
}

int main(int argc, char* argv[])
{

    int encrypt = 0;
    int decrypt = 0;

#if defined(__linux__)
    // Parse command line
    struct option longopts[] = {
            {"help",                    no_argument,       0, 'h'},
            {"encode",                  no_argument,       0, 'e'},
            {"decode",                  no_argument,       0, 'd'},
            0
    };
    char ch = '\0';
    int optindex = 0;
    while ( (ch = getopt_long(argc, argv, "hed", longopts, &optindex)) != -1 ) {
        switch (ch) {
            case 'e':
                encrypt = 1;
                break;
            case 'd':
                decrypt = 1;
                break;
            default:
                print_help();
                return -1;
        }
    }
    argc -= optind;
    argv += optind;
#else
    fprintf(stderr, "Parsing command line options isn't implemented in current OS\n");
    return -1;
#endif

    if ( argc < 2 ) {
        std::cout << "Please supply source and destination filename" << std::endl;
        print_help();
        return -1;
    }

    FILE * fp = fopen(argv[0], "rb");
    if(fp == nullptr)
    {
        std::cout << "file not exist" << std::endl;
        return 0;
    }

    fseek (fp , 0 , SEEK_END);
    long lSize = ftell (fp);
    rewind (fp);

    std::cout << "original file length : " << lSize << std::endl;

    char *buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    size_t result = fread (buffer,1, lSize, fp);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    fclose (fp);

    if(encrypt == 1)
    {
        char *encrypted_file = nullptr;
        size_t encrypted_file_length = 0;

        do_encryption_aes(buffer, lSize, &encrypted_file, &encrypted_file_length);

        std::cout << "encrypted file length : " << encrypted_file_length << std::endl;

        free (buffer);

        fp = fopen (argv[1], "wb");
        fwrite (encrypted_file , sizeof(char), encrypted_file_length, fp);
        fclose (fp);
    }

    if(decrypt == 1)
    {
        char *decrypted_file = nullptr;
        size_t decrypted_file_length = 0;
        do_decryption_aes(buffer, lSize, &decrypted_file, &decrypted_file_length);

        std::cout << "decrypted file length : " << decrypted_file_length << std::endl;

        free (buffer);

        fp = fopen (argv[1], "wb");
        fwrite (decrypted_file , sizeof(char), decrypted_file_length, fp);
        fclose (fp);
    }
    return 0;
}