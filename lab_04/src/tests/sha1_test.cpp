#include "sha1_test.h"
#include "rsa.h"
#include "sha1.h"

void sym_test(const std::vector<PlainKeyCipher>& test_vectors)
{
    for(PlainKeyCipher const& pkc : test_vectors)
    {
        std::string plain, key;
        std::tie(plain, key) = pkc;
        auto alg = SHA1();
        alg.update(plain);
        EXPECT_EQ(alg.final(), key);
    }
}

void sym_test_rsa(const std::vector<PlainKeyCipher>& test_vectors)
{
    struct pub_key_t pub[1];
    struct priv_key_t priv[1];
    rsa_gen_keys(pub, priv);
    for(PlainKeyCipher const& pkc : test_vectors)
    {
        std::string plain, key;
        std::tie(plain, key) = pkc;
        auto alg = SHA1();
        alg.update(plain);
        auto hash = alg.final();
        for(int i = 0; i < RESULT_SIZE; ++i)
        {
            long long int encrypted = rsa_encrypt((long long int)hash[i], priv);
            uint8_t decrypted = rsa_decrypt(encrypted, pub);
            EXPECT_EQ(hash[i], decrypted);
        }
    }
}

TEST(SHA1, set1)
{
    sym_test(SHA_SET_1);
}

TEST(RSA, sha_set1)
{
    sym_test_rsa(SHA_SET_1);
}
