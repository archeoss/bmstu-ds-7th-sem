#include "Encoder.h"
#include <iostream>
#include <string>

Encoder::Encoder(uint16_t alphabet_size, std::string new_alphabet)
    : size_alpha{alphabet_size}
{
    for(int i = 0; i < size_alpha; i++)
    {
        alphabet.push_back(new_alphabet[i]);
    }
}

Encoder::Encoder(uint16_t alphabet_size, std::vector<uint8_t> alphabet)
    : size_alpha{alphabet_size}
    , alphabet{alphabet} {};

uint8_t Encoder::encode(uint8_t symbol)
{
    for(int i = 0; i < size_alpha; ++i)
    {
        if(alphabet[i] == symbol)
        {
            return i;
        }
    }
    throw std::overflow_error("No symbol in encoder");
}

uint8_t Encoder::decode(uint8_t code)
{
    if(code > size_alpha)
    {
        throw std::overflow_error("No symbol in decoder");
    }
    return alphabet[code];
}

Reflector::Reflector(int reflector_number, int alphabet_size)
{
    inner.reserve(alphabet_size);
    for(int i = 0; i < alphabet_size; i++)
    {
        inner.push_back((reflector_number + alphabet_size - i) % alphabet_size);
    }
}

Commutator::Commutator(int commutator_number, int alphabet_size)
{
    inner.reserve(alphabet_size);
    for(int i = 0; i < alphabet_size; i++)
    {
        inner.push_back((commutator_number + i) % alphabet_size);
    }
}

Rotor::Rotor(int rotor_number, int alphabet_size)
{
    inner.reserve(alphabet_size);
    for(int j = 0; j < alphabet_size; ++j)
    {
        inner.push_back((rotor_number + j) % alphabet_size);
    }
}

std::vector<Rotor> Rotor::rotors(std::vector<int> rotor_numbers, int alphabet_size)
{
    std::vector<Rotor> rotors;
    for(int rotor_number : rotor_numbers)
    {
        Rotor rotor(rotor_number, alphabet_size);
        rotors.push_back(rotor);
    }

    return rotors;
}
