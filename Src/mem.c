// file: mem.c
// created by: Grant Wilk
// date created: 1/20/2020
// last modified: 1/20/2020
// description: Contains functions for reading from and writing to memory

# include <stdio.h>
# include <stdint.h>
# include "mem.h"

void mem_dump(uint8_t * addr, int len) {

	// print dump information
	printf("\nDumping %d bytes of memory from 0x%08X to 0x%08X.\n", len, (unsigned int) addr, (unsigned int) (addr + len));

    // print column header
    printf("\n\t\t\t00 01 02 03\t\t04 05 06 07\t\t08 09 0A 0B\t\t0C 0D 0E 0F\n\n");

    // iterate through every byte in the range
    for ( int i = 0; i < len; i++ ) {

        // if we've printed 8 consecutive lines and it is not our first time through
        if (i % 128 == 0 && i != 0) {
            // print an extra line for spacing
            printf("\n");
        }

        // if we're at the beginning of a line
        if ( i % 16 == 0 ) {

            // if it isn't our first time though, print a new line
            if ( i != 0 ) {
            printf("\n");
            }

            // print the address we're currently at
            printf("0x%08X", (unsigned int) (addr + i));
        }

        // if we're at the end of a word, print some extra space
        if (i % 4 == 0) {
            printf("\t");
        }

        // print the next byte
        printf("%02X ", *(addr + i));

    }

    printf("\n");
}

void mem_read(uint32_t * addr) {
    printf("ADR: 0x%08X\n", (unsigned int) addr);
    printf("DEC: %d\n", *addr);
    printf("HEX: 0x%08X\n", *addr);
}

void mem_write(uint32_t * addr, int data) {
    *addr = data;
    mem_read(addr);
}
