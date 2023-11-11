#include "AES.h"
#include "ArchiveReader.h"
#include "CFB.h"
#include "SymAlg.h"
#include "Utils.h"
#include <cstdint>
#include <fstream>
#include <string>

int main()
{
    // Setup Encryption
    auto instance = new AES(rand32key());
    auto cfb = CFB(instance, "");

    // ArchiveReader arch_reader("input.tar.gz");
    // std::string archive_data = arch_reader.extract_into_memory("input.txt");
    ArchiveReader arch_reader("");
    std::string archive_data = arch_reader.read_file_into_memory("input.txt");

    std::cout << "Message: " << archive_data << std::endl;
    std::vector<uint8_t> message(archive_data.begin(), archive_data.end());
    std::cout << "Encrypted message: ";
    auto encrypted_data = cfb.encrypt(archive_data);
    std::cout << encrypted_data << std::endl;

    std::ofstream encrypted_file;
    encrypted_file.open("aes.bin");
    encrypted_file << encrypted_data;
    encrypted_file.close();

    std::string crypted_data = arch_reader.read_file_into_memory("aes.bin");
    std::cout << "Decrypted message: ";
    auto decrypted_data = cfb.decrypt(crypted_data);
    std::cout << decrypted_data << std::endl;

    std::ofstream decrypted_file;
    decrypted_file.open("output.txt");
    decrypted_file << decrypted_data;
    decrypted_file.close();

    return 0;
}
