# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include "scanner.h"
# include "mem.h"
#include "uart_driver.h"

// the clock speed of the CPU in Hz
#define F_CPU 16000000UL

// the max length of any command in characters plus 1 for a null terminator
# define MAX_LEN_CMD 6

// prototype for print_err function (below main)
void print_err(int type, const char * spec);

int main(void) {

	// initialize the USART
	uart_init(19200, F_CPU);

    int reference = 5;
    printf("Reference Location: 0x%X\n", (unsigned int) &reference);

    while (1) {

    	// print input prompt
        printf(">> ");

        // fill the scanner buffer
        sc_get();

        // if the scanner has a next token
        if ( sc_hasnext() ) {

            // command string is 6 chars long because the longest command is 5 chars + a null terminator
            char cmd[MAX_LEN_CMD];

            // get the next token from the scanner
            sc_next(cmd, MAX_LEN_CMD);

            // if the dump command has been given
            if ( !strcmp(cmd, "dump") ) {

                // initialize the parameters
                int addr;
                int len = 16;

                // if the scanner has no next token, print out the command info
                if ( !sc_hasnext() ) {
                    printf(
                        "Command: Memory Dump\n"
                        "Description: Dumps a section of memory.\n"
                        "Syntax: dump <address> <length>\n"
                    );
                }

                // if the command has an address parameter
            	else if ( sc_hasnexti() || sc_hasnextx() ) {

                    // get the address parameter depending on its identified type
                    if ( sc_hasnexti() ) {
                        addr = sc_nexti();
                    } else {
                        addr = sc_nextx();
                    }

                    // if the command has a length paramter
                    if ( sc_hasnexti() ) {
                        // get the next integer and use it as the length parameter
                        len = sc_nexti();
                    }

                    // print the memory dump
                    mem_dump((uint8_t *) addr, len);

                } else {
                    print_err(1, "address");
                }

            }

            // if the help command has been given
            else if ( !strcmp(cmd, "help") ) {
                printf(
                    "\n"
                    " Help Context:\n"
                    "  - dump  <address> <length> \t Dumps a section of memory.\n"
                    "  - help \t\t\t Displays the help context.\n"
                    "  - read  <address> \t\t Reads a word from a location in memory.\n"
                    "  - write <address> <data> \t Writes a word to a location in memory.\n"
                );
            }

            // if the read command has been given
            else if ( !strcmp(cmd, "read") ) {

                // initialize the parameters
                int addr;

                // if the scanner has no next token, print out the command info
                if ( !sc_hasnext() ) {
                    printf(
                        "Command: Memory Read\n"
                        "Description: Reads a word from a location in memory.\n"
                        "Syntax: read <address>\n"
                    );
                }

                // if the command has an address parameter
            	else if ( sc_hasnexti() || sc_hasnextx() ) {

                    // get the address parameter depending on its identified type
                    if ( sc_hasnexti() ) {
                        addr = sc_nexti();
                    } else {
                        addr = sc_nextx();
                    }

                    // print the read data
                    mem_read((uint32_t *) addr);

                }

            }

            // if the write command has been given
            else if ( !strcmp(cmd, "write") ) {

                // initialize the parameters
                int addr;
                int data;

                // if the scanner has no next token, print out the command info
                if ( !sc_hasnext() ) {
                    printf(
                        "Command: Memory Write\n"
                        "Description: Writes a word to a location in memory.\n"
                        "Syntax: write <address> <data>\n"
                    );
                }

                // if the command has an address parameter
            	else if ( sc_hasnexti() || sc_hasnextx() ) {

                    // get the address parameter depending on its identified type
                    if ( sc_hasnexti() ) {
                        addr = sc_nexti();
                    } else {
                        addr = sc_nextx();
                    }

                    // if the command has a data parameter
                    if ( sc_hasnexti() || sc_hasnextx() ) {

                        // get the data parameter depending on its identified type
                        if ( sc_hasnexti() ) {
                            data = sc_nexti();
                        } else {
                            data = sc_nextx();
                        }

                        // perform the write
                        mem_write((uint32_t *) addr, data);

                    } else {
                        print_err(1, "data");
                    }

                }

            }

            // if an invalid command has been given
            else {
                print_err(0, cmd);
            }

            // print a new line for spacing
            printf("\n");

        }
    }
}

void print_err(int type, const char * spec) {
    switch (type) {

        // unknown command
        case 0:
            printf("\'%s\' is not recognized as a command.\n", spec);
            break;

        // syntax error
        case 1:
            printf("Command missing parameter \'%s\'.\n", spec);
            break;

        // unknown error
        default:
            printf("An unknown error has occurred.\n");
    }
}
