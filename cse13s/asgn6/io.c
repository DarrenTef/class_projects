#include "io.h"
#include <unistd.h>
#include <assert.h>
#include "endian.h"

// Buffer is an area of memory for reading into or writing from
// Buffer = 4096 for reads. wants to read one byte at a time.

// static buffer_pair[BLOCK];
// static index_pair;
// static length_pair;

// static buffer_sym[BLOCK];
// static uint8_t index_sym;
// static uint16_t length_sym;

// static Write buffer and write index
// local statics for reading, need read buffer, read buffer size, and read index
// read bits for read pairs, write bits for write pairs

// Done
int read_bytes(int infile, uint8_t *buf, int to_read) {
    uint64_t bytes_read = 0;
    uint64_t cul_byte = 0;
    int tr = to_read;
    while (tr > 0) {
        bytes_read = read(infile, buf + cul_byte, to_read);
        if (bytes_read != -1) {
            cul_byte += bytes_read;
            tr = tr - bytes_read;
        }
        if (bytes_read == 0) {
            break;
        }
    }
    return cul_byte;
}

// Done
int write_bytes(int outfile, uint8_t *buf, int to_write) {
    uint64_t bytes_wrote = 0;
    uint64_t cul_byte = 0;
    int tw = to_write;
    while (tw > 0) {
        bytes_wrote = write(infile, buf + cul_byte, tw);
        if (bytes_wrote != -1) {
            cul_byte += bytes_wrote;
            tw = tw - bytes_wrote;
        }
        if (bytes_wrote == 0) {
            break;
        }
    }
    return cul_byte;
}

// Done
void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(header));
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    assert(header->magic == MAGIC);
}

// Done
void write_header(int outfile, FileHeader *header) {
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(header));
}

// Done
bool read_sym(int infile, uint8_t *sym) {
    static uint16_t buf[BLOCK];
    static uint16_t size = 0;
    static uint16_t index = 0;

    if (index == size)
        ; // out of bytes
    {
        size = read_bytes(infile, buf, BLOCK);
        index = 0;
    }
    if (index == size) {
        return false;
    }
    *sym = buf[index];
    index += 1;
    return true;
}

// writes pair to outfile
// pair = code, symbol
// the bits of code are buffered first, starting with LSB, then the symbols are buffered starting with LSB
// code buffered has the bit-length of bitlen
// write out the buffer whenever filled
// Code has a variable that takes 16 bits
// but bit len is determining how many of these 16 are valid
// so if bit len = 7, only care about 7/16 bits of the code

// Goal is to read the individual bits from a byte within a buffer
void read_bit() {
    index = BLOCK * 8;
    bit = read_bytes();
    buf[index / 8] ^= 1 << index % 8;
}

void write_bit() {
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    static uint16_t buf[BLOCK];
    static uint16_t size = 0;
    static uint16_t index = 0;
}

void flush_pairs(int outfile) {

    write(outfile, );
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
}

void write_word(int outfile, Word *w) {
}
