#include "ArchiveReader.h"
#include <iostream>

ArchiveReader::ArchiveReader(std::string filename)
    : filename{filename}
{
    file_buffer_str = read_file_into_memory(filename);
    archive = archive_read_new();
    archive_read_support_filter_all(archive);
    archive_read_support_format_all(archive);

    if(archive_read_open_memory(archive, file_buffer_str.data(), file_buffer_str.size()))
        throw std::runtime_error("Couldn't open archive");
}

std::string ArchiveReader::read_file_into_memory(const std::string& current_file)
{
    std::ifstream raw_file(current_file, std::ios::binary);
    auto buffer = [&raw_file] {
        std::ostringstream ss{};
        ss << raw_file.rdbuf();
        return ss.str();
    }();

    return buffer;
}

std::string ArchiveReader::extract_into_memory(const std::string& current_file)
{
    int r;
    std::string res{};
    for(;;)
    {
        r = archive_read_next_header(archive, &entry);
        if(r == ARCHIVE_EOF)
            break;
        if(r < ARCHIVE_OK)
            throw std::runtime_error(archive_error_string(archive));
        else if(archive_entry_size(entry) > 0 &&
                current_file.compare(archive_entry_pathname(entry)) == 0)
        {
            res = read_data(archive, archive_entry_size(entry));
            break;
        }
    }
    reset();
    if(r == ARCHIVE_EOF)
        throw std::runtime_error("File not found");

    return res;
}

std::string ArchiveReader::read_data(struct archive* ar, size_t ssize)
{
    std::string res;
    char* buff = (char*)malloc(ssize * sizeof(char));
    archive_read_data(ar, buff, ssize);
    res.insert(res.end(), buff, buff + ssize);

    return (res);
}

void ArchiveReader::reset()
{
    archive_read_close(archive);
    archive_read_free(archive);

    archive = archive_read_new();
    archive_read_support_filter_all(archive);
    archive_read_support_format_all(archive);

    if(archive_read_open_memory(archive, file_buffer_str.data(), file_buffer_str.size()))
        throw std::runtime_error("Couldn't open archive");
}

ArchiveReader::~ArchiveReader()
{
    archive_read_close(archive);
    archive_read_free(archive);
}

ArchiveAlphabet::ArchiveAlphabet()
{
    for(uint8_t i = 0; i < 255; ++i)
    {
        alphabet.push_back(i);
    }
    alphabet.push_back(255);
}
