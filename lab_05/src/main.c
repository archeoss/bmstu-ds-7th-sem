#include "huffman.h"

void print_help()
{
    fprintf(stderr,
            "USAGE: ./huffman [encode | decode] "
            "<input out> <output file>\n");
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        print_help();
        return FAILURE;
    }
    init();
    if(strcmp(argv[1], "encode") == 0)
        encode(argv[2], argv[3]);
    else if(strcmp(argv[1], "decode") == 0)
        decode(argv[2], argv[3]);
    else
        print_help();
    finalise();

    return SUCCESS;
}
