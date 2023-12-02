#ifndef __SHA1_H__
#define __SHA1_H__

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class SHA1
{
public:
    SHA1();
    void update(const std::string& s);
    void update(std::istream& is);
    std::string final();
    static std::string from_file(const std::string& filename);

private:
    uint32_t digest[5];
    std::string buffer;
    uint64_t transforms;
};

#define MAX_BUF_SIZE 1024
#define RESULT_SIZE 20

static const size_t BLOCK_INTS = 16;
static const size_t BLOCK_BYTES = BLOCK_INTS * 4;

#endif
