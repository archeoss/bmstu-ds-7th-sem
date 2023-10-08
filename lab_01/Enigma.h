#ifndef LAB_01_ENIGMA_H
#define LAB_01_ENIGMA_H

#include "Encoder.h"
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

class Enigma
{

public:
    Enigma(uint8_t size_rotor,
           uint8_t num_rotors,
           const Reflector& reflector_place,
           const std::vector<Rotor>& rotors_place,
           const Commutator& commutator_place);

    uint8_t encrypt(Encoder& encoder, uint8_t code);
    std::vector<uint8_t> encrypt(Encoder& encoder, std::vector<uint8_t>& codes);

private:
    uint8_t find_rotor(uint8_t num, uint8_t code);
    void rotor_shift(uint8_t num);

private:
    uint64_t counter = 0;
    uint8_t size_rotor;
    uint8_t num_rotors;
    Reflector reflector;
    Commutator commutator;
    std::vector<Rotor> rotors;
};

#endif
