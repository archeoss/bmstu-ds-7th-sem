#ifndef __DES__
#define __DES__

#include "Const.h"
#include "SymAlg.h"
#include "Utils.h"
#include <algorithm>
#include <cstdint>
#include <cstring>

class DES : public SymAlg
{
private:
    uint64_t keys[16];
    std::string run(const std::string& data);

public:
    DES();
    DES(const std::string& KEY);
    DES(const uint64_t KEY);
    void setkey(const std::string& KEY);
    std::string encrypt(const std::string& DATA);
    std::string decrypt(const std::string& DATA);
    unsigned int blocksize() const;
};

#endif
