#include "ArchiveReader.h"
#include "DES.h"
#include "PCBC.h"
#include "SymAlg.h"
#include <cstdint>
#include <fstream>
#include <string>

int main()
{
    // Setup Encryption
    SymAlg* instance = new DES(rand64());
    auto pcbc = PCBC(instance, rand64());
    ArchiveReader arch_reader("input.tar.gz");
    std::string archive_data = arch_reader.extract_into_memory("Enigma.h");
    // ArchiveReader arch_reader("");
    // std::string archive_data = arch_reader.read_file_into_memory("input.txt");

    std::cout << "Message: " << archive_data << std::endl;
    std::vector<uint8_t> message(archive_data.begin(), archive_data.end());
    std::cout << "Encrypted message: ";
    auto encrypted_data = PCBC(instance, "12345678").encrypt(archive_data);
    std::cout << encrypted_data << std::endl;

    std::cout << "Decrypted message: ";
    auto decrypted_data = PCBC(instance, "12345678").decrypt(encrypted_data);
    std::cout << decrypted_data << std::endl;

    std::ofstream myfile;
    myfile.open("output.txt");
    myfile << encrypted_data;
    myfile.close();

    return 0;
}
