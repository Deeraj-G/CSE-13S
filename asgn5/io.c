#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntil.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

// Got the code for read_bytes and write_bytes from TA Eugene's section

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes = 0;
    int bytes_read = 0;

    // Read the bytes into buf until bytes is less than 1
    do {
        
        // Advance the buf pointer by bytes_read number of bytes each time read() is called
        // Subtract nbytes by bytes_read to read the correct number of bytes to the buffer
        bytes = read(infile, buf + bytes_read, nbytes - bytes_read);
        
        // Increment bytes_read by bytes to properly track how many bytes still nead to be read
        bytes_read += bytes;

    } while(bytes > 0);

    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {

    int bytes = 0;
    int bytes_write = 0;

    // Write the bytes from buf into the outfile until bytes is less than 1
    do {

        // Advance the buf pointer by bytes_write number of bytes each time write() is called
        // Subtract nbytes by bytes_write to write the correct number of bytes to the buffer
        bytes = write(outfile, buf + bytes_write, nbytes - bytes_write);

        // Increment bytes_write by bytes to properly track how many bytes still nead to be written
        bytes_write += bytes;

    } while(bytes > 0);

    return bytes_write;
}

bool read_bit(int infile, uint8_t *bit) {

}

void write_code(int outfile, Code *c) {

}

void flush_codes(int outfile) {

}

