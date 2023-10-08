#include "Encoder.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Encoder, Encode_Decode_Positive)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";
    Encoder encoder(alphabet.size(), alphabet);
    ASSERT_TRUE(encoder.decode(encoder.encode('c')) == 'c');
}

TEST(Encoder, Encode_Decode_Negative)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";
    Encoder encoder(alphabet.size(), alphabet);
    ASSERT_FALSE(encoder.encode('c') == 'c');
}
