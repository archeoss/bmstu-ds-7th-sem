#ifndef __RSAset__
#define __RSAset__

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <vector>

// hold matching plaintext/key tuples
typedef std::tuple<std::string, std::string> PlainKeyCipher;

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/des/Des-64-64.test-vectors>

static const std::vector<PlainKeyCipher> SHA_SET_1 = {
    std::make_tuple("abc", "a9993e364706816aba3e25717850c26c9cd0d89d"),
    std::make_tuple("", "da39a3ee5e6b4b0d3255bfef95601890afd80709"),
    std::make_tuple("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
                    "84983e441c3bd26ebaae4aa1f95129e5e54670f1"),
    std::make_tuple("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmno"
                    "pqklmnopqrlmnopqrsmnopqrstnopqrstu",
                    "a49b2446a02c645bf419f995b67091253a04a259"),
    std::make_tuple("The quick brown fox jumps over the lazy cog",
                    "de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3"),
    std::make_tuple("The quick brown fox jumps over the lazy dog",
                    "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"),
    std::make_tuple("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmno"
                    "pqklmnopqrlmnopqrsmnopqrstnopqrstu",
                    "a49b2446a02c645bf419f995b67091253a04a259"),
};

#endif // __DESnessieset1__#endif // __AES__
