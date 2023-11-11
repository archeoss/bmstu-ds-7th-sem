#ifndef __ARCHIVE_READER__
#define __ARCHIVE_READER__

#include "archive.h"
#include "archive_entry.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class ArchiveReader
{
public:
    ArchiveReader(std::string filename);
    std::string read_file_into_memory(const std::string& current_file);
    std::string read_data(struct archive* ar, size_t ssize);
    std::string extract_into_memory(const std::string& current_file);
    void reset();

    ~ArchiveReader();

private:
    std::string file_buffer_str;
    std::string filename;
    struct archive* archive;
    struct archive_entry* entry;
};

class ArchiveAlphabet
{
public:
    ArchiveAlphabet();
    std::vector<uint8_t> alphabet;
};

#endif
