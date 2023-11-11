#ifndef __UTILS__
#define __UTILS__

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>

#define IMAX_BITS(m) ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))
#define RAND_MAX_WIDTH IMAX_BITS(RAND_MAX)

// string to integer
uint64_t toint(const std::string& s, const int& base = 10);

// From a Twofish code (modified)
// Bitwise rotation to the right
template <typename T>
T ROR(T x, const uint64_t& n, const uint64_t& bits)
{
    static_assert(std::is_integral<T>::value, "Error: Value being rotated should be integral.");
    return (x >> n) | ((x & ((1ULL << n) - 1)) << (bits - n));
}

// Rotate Left
// Bitwise rotation to the left
template <typename T>
T ROL(const T& x, const uint64_t& n, const uint64_t& bits)
{
    static_assert(std::is_integral<T>::value, "Error: Value being rotated should be integral.");
    return ROR(x, bits - n, bits);
}

template <typename T>
std::string makehex(T value, unsigned int size = 2 * sizeof(T), bool caps = false)
{
    if(!size)
    {
        std::stringstream out;
        out << std::hex << value;
        return out.str();
    }

    std::string out(size, '0');
    while(value && size)
    {
        if(caps)
        {
            out[--size] = "0123456789ABCDEF"[value & 15];
        }
        else
        {
            out[--size] = "0123456789abcdef"[value & 15];
        }
        value >>= 4;
    }
    return out;
}

// ASCII string to hex string
std::string hexlify(const std::string& in, bool caps = false);

// character to hex string
std::string hexlify(const char in, bool caps = false);

// hex string to ASCII string
std::string unhexlify(const std::string& in);

std::string pkcs5(const std::string& data, const unsigned int& blocksize);

std::string remove_pkcs5(std::string data);

// xor the contents of 2 strings, up to the last character of the shorter string
std::string xor_strings(const std::string& str1, const std::string& str2);

std::string rand32key(void);

#endif
