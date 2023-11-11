#include "Utils.h"

uint64_t toint(const std::string& s, const int& base)
{
    // Changees strings to uint64_t
    uint64_t value = 0;
    switch(base)
    {
    case 2:
        for(const unsigned char c : s)
        {
            value = (value << 1) + (static_cast<uint8_t>(c) - '\x30');
        }
        break;
    case 8:
        std::stringstream(s) >> std::oct >> value;
        break;
    case 10:
        std::stringstream(s) >> std::dec >> value;
        break;
    case 16:
        std::stringstream(s) >> std::hex >> value; // Thanks to Oli Charlesworth @ stackoverflow
        break;
    case 256:
        for(const unsigned char c : s)
        {
            value = (value << 8) + static_cast<uint8_t>(c);
        }
        break;
    default:
        std::stringstream s;
        s << std::dec << base;
        throw std::runtime_error("Error: toint() undefined for base: " + s.str());
        break;
    };
    return value;
}

// Changes an ASCII string to an ASCII string containing the
// hexadecimal representation of the original chars
std::string hexlify(const std::string& in, bool caps)
{
    std::string out(in.size() << 1, '0');
    unsigned int i = 0;
    for(unsigned char const c : in)
    {
        std::string h = hexlify(c, caps);
        out[i++] = h[0];
        out[i++] = h[1];
    }

    return out;
}

std::string hexlify(const char in, bool caps)
{
    return makehex(static_cast<uint8_t>(in), 2, caps);
}

std::string unhexlify(const std::string& in)
{
    // Reverse hexlify
    if(in.size() & 1)
    {
        throw std::runtime_error("Error: input string of odd length.");
    }
    std::string out(in.size() >> 1, 0);
    for(unsigned int x = 0; x < in.size(); x += 2)
    {
        if(('0' <= in[x]) && (in[x] <= '9'))
        {
            out[x >> 1] = static_cast<uint8_t>((in[x] - '0') << 4);
        }
        else if(('a' <= in[x]) && (in[x] <= 'f'))
        {
            out[x >> 1] = static_cast<uint8_t>((in[x] - 'a' + 10) << 4);
        }
        else if(('A' <= in[x]) && (in[x] <= 'F'))
        {
            out[x >> 1] = static_cast<uint8_t>((in[x] - 'A' + 10) << 4);
        }
        else
        {
            throw std::runtime_error("Error: Invalid character found: " + std::string(1, in[x]));
        }
        if(('0' <= in[x + 1]) && (in[x + 1] <= '9'))
        {
            out[x >> 1] |= static_cast<uint8_t>(in[x + 1] - '0');
        }
        else if(('a' <= in[x + 1]) && (in[x + 1] <= 'f'))
        {
            out[x >> 1] |= static_cast<uint8_t>(in[x + 1] - 'a' + 10);
        }
        else if(('A' <= in[x + 1]) && (in[x + 1] <= 'F'))
        {
            out[x >> 1] |= static_cast<uint8_t>(in[x + 1] - 'A' + 10);
        }
        else
        {
            throw std::runtime_error("Error: Invalid character found: " +
                                     std::string(1, in[x + 1]));
        }
    }
    return out;
}

std::string pkcs5(const std::string& data, const unsigned int& blocksize)
{
    // Adds PKCS5 Padding
    int pad = blocksize - (data.size() % blocksize);
    std::string padding(pad, static_cast<char>(pad));
    return data + padding;
}

std::string remove_pkcs5(std::string data)
{
    // Removes PKCS Padding
    uint8_t pad = static_cast<uint8_t>(data[data.size() - 1]);
    if((pad > data.size()) ||
       (std::string(pad, static_cast<char>(pad)) != data.substr(data.size() - pad, pad)))
    {
        throw std::runtime_error("Error: Could not remove pkcs5 padding.");
    }
    data.resize(data.size() - pad);
    return data;
}

// xor the contents of 2 strings, up to the last character of the shorter string
std::string xor_strings(const std::string& str1, const std::string& str2)
{
    std::string::size_type end = std::min(str1.size(), str2.size());
    std::string out = str1.substr(0, end);
    for(std::string::size_type i = 0; i < end; i++)
    {
        out[i] ^= str2[i];
    }
    return out;
}

std::string rand32key(void)
{
    std::string res{};
    for(int i = 0; i < 32; ++i)
    {
        res.push_back('a' + rand() % 26);
    }

    return res;
}
