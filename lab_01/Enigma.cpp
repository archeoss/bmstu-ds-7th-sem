#include "Enigma.h"
#include "Encoder.h"

Enigma::Enigma(uint8_t size_rotor,
               uint8_t num_rotors,
               const Reflector& reflector_place,
               const std::vector<Rotor>& rotors_place,
               const Commutator& commutator_place)
    : size_rotor{size_rotor}
    , num_rotors{num_rotors}
    , reflector{reflector_place}
    , commutator{commutator_place}
    , rotors{rotors_place}
{ }

uint8_t Enigma::find_rotor(uint8_t num, uint8_t code)
{
    for(int i = 0; i < size_rotor; ++i)
    {
        if(rotors[num].inner[i] == code)
        {
            return i;
        }
    }
    throw std::out_of_range("Code doesn't founded");
}

void Enigma::rotor_shift(uint8_t num)
{
    uint8_t temp = rotors[num].inner[size_rotor - 1];
    for(int i = size_rotor - 1; i > 0; --i)
    {
        rotors[num].inner[i] = rotors[num].inner[i - 1];
    }
    rotors[num].inner[0] = temp;
}

uint8_t Enigma::encrypt(Encoder& encoder, uint8_t code)
{
    code = encoder.encode(code);
    uint64_t rotor_queue = 1;

    if(code > size_rotor)
    {
        throw std::out_of_range("Code bigger than size of rotor");
    }
    code = commutator.inner[code];

    for(auto& rotor : rotors)
    {
        code = rotor.inner[code];
    }
    code = reflector.inner[code];

    for(int i = num_rotors - 1; i >= 0; --i)
    {
        try
        {
            code = find_rotor(i, code);
        }
        catch(const std::overflow_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    counter++;
    for(int i = 0; i < num_rotors; ++i)
    {
        if(counter % rotor_queue == 0)
        {
            rotor_shift(i);
        }
        rotor_queue *= size_rotor;
    }
    code = commutator.inner[code];

    return code;
}

std::vector<uint8_t> Enigma::encrypt(Encoder& encoder, std::vector<uint8_t>& codes)
{
    std::vector<uint8_t> res;
    for(auto& symbol : codes)
    {
        try
        {
            uint8_t encoded_ch = encrypt(encoder, symbol);
            uint8_t decoded_ch = encoder.decode(encoded_ch);
            res.push_back(decoded_ch);
        }
        catch(std::overflow_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return res;
}
