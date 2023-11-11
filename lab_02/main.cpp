#include "ArchiveReader.h"
#include "DES.h"
#include "PCBC.h"
#include "SymAlg.h"
#include "Utils.h"
#include <cstdint>
#include <fstream>
#include <string>

int main()
{
    // Setup Encryption
    auto instance = new DES(rand64());
    auto IV = rand64();
    auto pcbc = PCBC(instance, IV);

    // ArchiveReader arch_reader("input.tar.gz");
    // std::string archive_data = arch_reader.extract_into_memory("input.txt");
    ArchiveReader arch_reader("");
    std::string archive_data = arch_reader.read_file_into_memory("input.txt");

    std::cout << "Message: " << archive_data << std::endl;
    std::vector<uint8_t> message(archive_data.begin(), archive_data.end());
    std::cout << "Encrypted message: ";
    auto encrypted_data = pcbc.encrypt(archive_data);
    std::cout << encrypted_data << std::endl;

    std::ofstream encrypted_file;
    encrypted_file.open("des.bin");
    encrypted_file << encrypted_data;
    encrypted_file.close();

    std::string crypted_data = arch_reader.read_file_into_memory("des.bin");
    std::cout << "Decrypted message: ";
    auto decrypted_data = pcbc.decrypt(crypted_data);
    std::cout << decrypted_data << std::endl;

    std::ofstream decrypted_file;
    decrypted_file.open("output.txt");
    decrypted_file << decrypted_data;
    decrypted_file.close();

    return 0;
}
