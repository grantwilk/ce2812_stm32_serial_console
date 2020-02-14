// file: mem.h
// created by: Grant Wilk
// date created: 1/20/2020
// last modified: 1/20/2020
// description: Header file for mem.c

# include <stdint.h>

void mem_dump(uint8_t * addr, int len);

void mem_read(uint32_t * addr);

void mem_write(uint32_t * addr, int data);
