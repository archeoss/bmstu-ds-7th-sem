// Propagating Cipher - Block Chaining
#ifndef __PCBC__
#define __PCBC__

#include "SymAlg.h"
#include "Utils.h"
#include <cstdint>

class CFB
{
private:
    SymAlg* algo;
    std::string const_IV;
    uint8_t blocksize;

public:
    CFB(SymAlg* instance, const std::string& iv = "");
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);
};

#endif
