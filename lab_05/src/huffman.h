#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 256
#define INVALID_BIT_READ -1
#define INVALID_BIT_WRITE -1

#define FAILURE 1
#define SUCCESS 0
#define FILE_OPEN_FAIL -1
#define END_OF_FILE -1
#define MEM_ALLOC_FAIL -1

typedef struct
{
    int index;
    unsigned int weight;
} node_t;

int read_header(FILE* f);
int write_header(FILE* f);
int read_bit(FILE* f);
int write_bit(FILE* f, int bit);
int flush_buffer(FILE* f);
void decode_bit_stream(FILE* fin, FILE* fout);
int decode(const char* ifile, const char* ofile);
void encode_alphabet(FILE* fout, int character);
int encode(const char* ifile, const char* ofile);
void build_tree();
void add_leaves();
int add_node(int index, int weight);
void finalise();
void init();
