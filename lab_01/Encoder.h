#ifndef LAB_01_ENCODER_H
#define LAB_01_ENCODER_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

class Encoder
{

public:
    Encoder(uint16_t alphabet_size, std::string new_alphabet);
    Encoder(uint16_t alphabet_size, std::vector<uint8_t> new_alphabet);

    uint8_t encode(uint8_t symbol);
    uint8_t decode(uint8_t code);

private:
    uint16_t size_alpha;
    std::vector<uint8_t> alphabet;
};

class Reflector
{

public:
    Reflector() = default;
    Reflector(int reflector_number, int alphabet_size);

    std::vector<uint8_t> inner;
};

class Commutator
{

public:
    Commutator() = default;
    Commutator(int commutator_number, int alphabet_size);

    std::vector<uint8_t> inner;
};

class Rotor
{
public:
    Rotor() = default;
    Rotor(int rotor_number, int alphabet_size);
    std::vector<Rotor> rotors(std::vector<int> rotor_numbers, int alphabet_size);

    std::vector<uint8_t> inner;
};
#endif //LAB_01_ENCODER_H
