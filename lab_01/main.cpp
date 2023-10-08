#include "ArchiveReader.h"
#include "Encoder.h"
#include "Enigma.h"

int main()
{
    uint8_t num_rotors = 3;
    srand(time(NULL));

    // Setting up Encoder
    ArchiveAlphabet alphabet_arch = ArchiveAlphabet();
    int alphabet_size = alphabet_arch.alphabet.size();
    Encoder encoder(alphabet_arch.alphabet.size(), alphabet_arch.alphabet);

    // std::string alphabet_english = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\n\t";
    // Encoder encoder(alphabet_english.size(), alphabet_english);
    // int alphabet_size = alphabet_english.size();
    // ------------------------

    // Reflectors
    int reflector_number = rand() % alphabet_size;
    Reflector reflector(reflector_number, alphabet_size);
    // -----

    // Commutator
    int commutator_number = rand() % alphabet_size;
    Commutator commutator(commutator_number, alphabet_size);
    // -----

    // Rotors
    std::vector<int> rotor_nums;
    for(uint8_t i = 0; i < num_rotors; ++i)
    {
        rotor_nums.push_back(rand() % alphabet_size);
    }
    Rotor r;
    std::vector<Rotor> rotors = r.rotors(rotor_nums, alphabet_size);

    // Starting Enigma machine
    // ArchiveReader arch_reader("input.tar.gz");
    // std::string archive_data = arch_reader.extract_into_memory("Enigma.h");
    ArchiveReader arch_reader("");
    std::string archive_data = arch_reader.read_file_into_memory("input.txt");

    std::cout << "Message: " << archive_data << std::endl;
    std::vector<uint8_t> message(archive_data.begin(), archive_data.end());
    std::cout << "Encrypted message: ";
    Enigma enigma(alphabet_size, num_rotors, reflector, rotors, commutator);
    std::vector<uint8_t> new_message = enigma.encrypt(encoder, message);
    std::cout << new_message.data() << std::endl;

    std::cout << "Decrypted message: ";
    Enigma enigma_two(alphabet_size, num_rotors, reflector, rotors, commutator);
    std::vector<uint8_t> decrypted_message = enigma_two.encrypt(encoder, new_message);
    std::cout << decrypted_message.data() << std::endl;

    return 0;
}
