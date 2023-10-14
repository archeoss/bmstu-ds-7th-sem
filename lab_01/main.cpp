#include "ArchiveReader.h"
#include "Encoder.h"
#include "Enigma.h"
#include <fstream>
#include <string>

int main()
{
    uint8_t num_rotors = 3;
    srand(time(NULL));

    // Setting up Encoder
    ArchiveAlphabet alphabet_arch = ArchiveAlphabet();
    int alphabet_size = alphabet_arch.alphabet.size();
    std::cout << std::to_string(alphabet_size) << "\n" << std::endl;
    // std::cout << symbol << std::endl;
    Encoder encoder(alphabet_size, alphabet_arch.alphabet);

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
    std::string archive_data = arch_reader.read_file_into_memory("main.pdf");

    std::cout << "Message: " << archive_data.size() << std::endl;
    std::vector<uint8_t> message(archive_data.begin(), archive_data.end());
    // std::cout << "Encrypted message: ";
    Enigma enigma(alphabet_size, num_rotors, reflector, rotors, commutator);
    std::vector<uint8_t> new_message = enigma.encrypt(encoder, message);
    std::cout << new_message.size() << std::endl;

    std::ofstream encrypted_file;
    encrypted_file.open("main.bin");
    encrypted_file << new_message.data();
    encrypted_file.close();

    // std::string crypted_data = arch_reader.read_file_into_memory("main.bin");
    // std::cout << "Decrypted message: ";
    std::vector<uint8_t> crypted_message(new_message.begin(), new_message.end());
    Enigma enigma_two(alphabet_size, num_rotors, reflector, rotors, commutator);
    std::vector<uint8_t> decrypted_message = enigma_two.encrypt(encoder, crypted_message);

    std::ofstream myfile;
    myfile.open("output.txt");
    myfile << new_message.data();
    myfile.close();

    std::string out_message(decrypted_message.begin(), decrypted_message.end());
    std::ofstream decrypted_file;
    decrypted_file.open("main_decr.pdf");
    decrypted_file << out_message;
    decrypted_file.close();

    return 0;
}
