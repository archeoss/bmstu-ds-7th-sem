#include <argp.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <string>

#include "rsa.h"
#include "sha1.h"

static char doc[] = "MD5 with RSA";
static char args_doc[] = "TARGET --hash --decrypt --encrypt";
static struct argp_option options[] = {{"hash", 'h', 0, 0, "Outputs file hash (sha1)"},
                                       {"encrypt", 'e', 0, 0, "Encryption mode"},
                                       {"decrypt", 'd', 0, 0, "Decryption mode"},
                                       {0}};

typedef enum
{
    HASH = 0,
    ENCRYPT,
    DECRYPT
} Modes;

struct arguments
{
    Modes mode;
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
    struct arguments* arguments = (struct arguments*)state->input;
    switch(key)
    {
    case 'h':
        arguments->mode = HASH;
        break;
    case 'e':
        arguments->mode = ENCRYPT;
        break;
    case 'd':
        arguments->mode = DECRYPT;
        break;
    case ARGP_KEY_ARG:
        return 0;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

int main(const int argc, char* argv[])
{
    struct arguments arguments;
    arguments.mode = HASH;
    auto hasher = SHA1();
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if(arguments.mode == HASH)
    {
        auto res = hasher.from_file(argv[1]);
        std::cout << res << std::endl;
    }
    else if(arguments.mode == ENCRYPT)
    {
        struct pub_key_t pub[1];
        struct priv_key_t priv[1];

        std::string line;
        std::getline(std::cin, line);
        auto c_line = line.data();
        uint8_t hash[RESULT_SIZE] = {0};
        for(int i = 1; i < RESULT_SIZE + 1; ++i)
        {
            int idx = i * 2;
            char tmp = line[idx];
            c_line[idx] = 0;
            sscanf(c_line + idx - 2, "%hhX", &hash[i - 1]);
            c_line[idx] = tmp;
        }
        rsa_gen_keys(pub, priv);

        for(int i = 0; i < RESULT_SIZE; ++i)
        {
            long long int encrypted = rsa_encrypt((long long int)hash[i], priv);
            printf("%lld ", encrypted);
        }
        printf("\n");
    }
    else
    {
        struct pub_key_t pub[1];
        struct priv_key_t priv[1];

        rsa_gen_keys(pub, priv);

        for(int i = 0; i < RESULT_SIZE; ++i)
        {
            long long int encrypted;
            scanf("%lld", &encrypted);
            uint8_t decrypted = rsa_decrypt(encrypted, pub);
            printf("%02x", decrypted);
        }
    }

    return 0;
}
