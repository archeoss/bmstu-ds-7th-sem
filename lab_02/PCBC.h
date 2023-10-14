// Propagating Cipher - Block Chaining
#ifndef __PCBC__
#define __PCBC__

#include "SymAlg.h"
#include "Utils.h"
#include <cstdint>

class PCBC
{
private:
    SymAlg* algo;
    std::string const_IV;
    uint8_t blocksize;

public:
    PCBC(SymAlg* instance, const std::string& iv = "");
    PCBC(SymAlg* instance, const uint64_t = 12345);
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);
};

#endif
