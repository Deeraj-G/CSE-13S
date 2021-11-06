#include "code.h"
#include "defines.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntil.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

// Got the code for read_bytes and write_bytes from TA Eugene's section
// Got the code for most of read_bit from TA Eugene's section

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
    static uint8_t buffer[BLOCK];

    // Tracks bit position in buffer
    static int index = 0;
    // Tracks last valid bit
    static int end = -1;

    // Fill buffer if empty
    if (index == 0) {
        bytes = read_bytes(infile, buffer, BLOCK);
        // Ends if the number of bytes remaining is less than the BLOCK
        if (bytes < BLOCK) {
            // Set the end as 1 after the last valid bit
            end = (bytes * 8) + 1;
        }
    }

    // Return a bit out of the buffer
    *bit = buffer[index / 8] & (1 << (index % 8));
    index += 1;

    // Reset index if it reaches the end of the buffer
    if (index == BLOCK * 8) {
        index = 0;
    }

    // Return a boolean depending on if there's a valid byte to return
    return index != end;
}

bool read_byte(int infile, uint8_t *x) {
    static uint8_t buffer[BLOCK];
    static int index = 0; // tracks position in buffer
    static int end = -1; // tracks the index after the last valid byte
    int bytes;

    // Fill buffer if empty
    if (index == 0) {
        bytes = read_bytes(infile, buffer, BLOCK);
        // Ends if the number of bytes remaining is less than the BLOCK
        if (bytes < BLOCK) {
            // Set the end as 1 after the last valid byte
            end = (bytes * 8) + 1;
        }
    }

    // Return a byte out of the buffer
    *x = buffer[index];
    index += 1;
    
    // Reset index if it reaches the end of the buffer
    if (index == BLOCK) {
        index = 0;
    }

    // Return a boolean depending on if there's a valid byte to return
    return index != end;    
}

void flush_codes(int outfile) {
    // Flush bits out of buffer if it isn't empty
    if (index > 0) {
        // Convert index into bytes
        write_bytes(outfile, c);
    }
}

void write_code(int outfile, Code *c) {
    // Buffers a code
    // Buffer is written when filled
    // Buffer each bit into the buffer
    for (int i = 0; i < code_size(c); i++) {
        uint8_t bit = code_get_bit(c, i);
        
        if (bit == 1) {
            // Set the bit at index
            code_set_bit(c, index);
        }
        else {
            code_clr_bit(c, index);
        }

        index += 1;

        // How to know if the buffer is filled
        if (index != end) {
            flush_codes(outfile);
        }
    }
}











































