#include "Enigma.h"
#include "Encoder.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <sys/types.h>
#include <vector>

std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";

Encoder setup_encoder()
{
    Encoder encoder(alphabet.size(), alphabet);

    return encoder;
}

Enigma setup_enigma()
{
    srand(time(NULL));
    Rotor r;
    Enigma enigma(alphabet.size(),
                  3,
                  Reflector(rand() % alphabet.size(), alphabet.size()),
                  r.rotors({rand() % (int)alphabet.size(),
                            rand() % (int)alphabet.size(),
                            rand() % (int)alphabet.size()},
                           alphabet.size()),
                  Commutator(rand() % alphabet.size(), alphabet.size()));

    return enigma;
}

TEST(Enigma, Encode)
{
    Encoder encoder = setup_encoder();
    Enigma enigma = setup_enigma();
    std::string new_message{"test"};
    std::vector<uint8_t> message(new_message.begin(), new_message.end());

    ASSERT_FALSE(enigma.encrypt(encoder, message) == message);
}

TEST(Enigma, Decode)
{
    Encoder encoder = setup_encoder();
    Enigma enigma_encrypt = setup_enigma();
    Enigma enigma_decrypt = setup_enigma();
    std::string new_message{"test"};
    std::vector<uint8_t> message(new_message.begin(), new_message.end());
    std::vector<uint8_t> enc_msg = enigma_encrypt.encrypt(encoder, message);

    ASSERT_TRUE(enigma_decrypt.encrypt(encoder, enc_msg) == message);
}
