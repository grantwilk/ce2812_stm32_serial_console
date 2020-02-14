// file: scanner.c
// created by: Grant Wilk
// date created: 1/10/2020
// last modified: 1/20/2020
// description: A simplified recreation of the Scanner class from Java

# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include "scanner.h"

// the size of the input buffer
# define INPUT_BUFFER_SIZE 250

// the maximum length of a 32-bit signed integer in digits
# define INT_MAX_LEN_DIGITS 12

// the maximum length of a signed double in digits
# define DOUBLE_MAX_LEN_DIGITS 18

// determines whether a character is a scanner terminator character (i.e. a null terminator or a whitespace control character)
# define isterm(c) (c == '\0' || (isspace(c) && !isblank(c)))

// the buffer that stores the input for the scanner
static char input_buffer[INPUT_BUFFER_SIZE];

// a pointer to keep track of the position in the input buffer
static volatile int b_offset = 0;

/*
Fills the scanner's input buffer by getting input from the input source
@ param void
@ return void
*/
void sc_get(void) {

    // get a string from the input source
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);

    // flush the input source to get rid of extra characters that won't fit in the buffer
    fflush(stdin);

    // reset the buffer offset back to the start of the input buffer
    b_offset = 0;

}

/*
Copies the next token from the input buffer into the destination string, provided it is long enough. If the destination string is not long enough, as much of the token will be copied as possible. If there is no next token, the destination string will be filled with a null string.
@ param void
@ return void
*/
void sc_next(char * dest, int len) {

    // move the buffer offset right until we hit a printable non-whitespace character or a scanner terminator
    while ( !( ( !isspace(input_buffer[b_offset]) && isprint(input_buffer[b_offset]) ) || isterm(input_buffer[b_offset]) ) ) {
        b_offset++;
    }

    // initialize the offset into the destination string
    int dest_offset = 0;

    // append each character from the input buffer to the destination string until we hit a whitespace character, an unprintable character, a scanner terminator, or we run out of room in the destination buffer
    while ( !( isspace(input_buffer[b_offset]) || !isprint(input_buffer[b_offset]) || isterm(input_buffer[b_offset]) || dest_offset >= len - 1 ) ) {
        dest[dest_offset++] = input_buffer[b_offset++];
    }

    // if the buffer offset is not at a scanner terminator and is not at the end of the destination string, move it over one more character to account for the whitespace/unprintable character
    if ( !( isterm(input_buffer[b_offset]) || dest_offset >= len - 1 ) ) {
        b_offset++;
    }

    // terminate the next token string with a null terminator
    dest[dest_offset] = '\0';

}

/*
Copies the next line from the input buffer into the destination string, provided it is long enough. If the destination string is not long enough, as much of the line will be copied as possible. If there is no next line, the destination string will be filled with a null string.
@ param void
@ return void
*/
void sc_nextln(char * dest, int len) {

	// initialize the offset into the destination string
	int dest_offset = 0;

	// append each character from the input buffer to the destination string until we hit a scanner terminator or we run out of room in the destination buffer
	while ( !( isterm(input_buffer[b_offset]) || dest_offset >= len - 1 ) ) {
		dest[dest_offset++] = input_buffer[b_offset++];
	}

	// terminate the next token string with a null terminator
	dest[dest_offset] = '\0';

}

/*
Gets the next integer from the input buffer and returns it
@ param void
@ return the next integer from the input buffer
*/
int sc_nexti(void) {

	char int_str[INT_MAX_LEN_DIGITS];

	sc_next(int_str, INT_MAX_LEN_DIGITS);

	long long int conversion = strtoll(int_str, NULL, 10);

	if (conversion > INT_MAX || conversion < INT_MIN) {
		return 0;
	} else {
		return (int) conversion;
	}
}

/*
Gets the next integer from the input buffer and returns it
@ param void
@ return the next integer from the input buffer
*/
int sc_nextx(void) {

	char int_str[INT_MAX_LEN_DIGITS];

	sc_next(int_str, INT_MAX_LEN_DIGITS);

	long long int conversion = strtoull(int_str, NULL, 16);

	if ( conversion > UINT_MAX ) {
		return 0;
	} else {
		return (int) conversion;
	}
}

/*
Gets the next double from the input buffer and returns it
@ param void
@ return the next double from the input buffer
*/
double sc_nextf(void) {
	// TO BE IMPLEMENTED
    return 0;
}

/*
Determines whether or not the scanner has a next token in its input buffer
@ param void
@ return 1 if the scanner has a next token, 0 otherwise
*/
int sc_hasnext(void) {

    volatile int i = 0;

    // move the iterator right until we hit a non-whitespace character and the character is not a scanner terminator
    while ( isspace(input_buffer[b_offset + i]) && !isterm(input_buffer[b_offset + i]) ) {
    	i++;
    }

    volatile int j = 0;

    // move the iterator right until we hit whitespace or a scanner terminator
    while ( !isspace(input_buffer[b_offset + i + j]) && !isterm(input_buffer[b_offset + i + j]) ) {
    	j++;
    }

    // there is no next token if our iterator has not moved across printable non-whitespace characters and we are at a scanner terminator
    return !(j == 0 && isterm(input_buffer[b_offset + i + j]));

}

/*
Determines whether or not the scanner has a next line in its input buffer
@ param void
@ return 1 if the scanner has a next line, 0 otherwise
*/
int sc_hasnextln(void) {

	int i = 0;

	// move the iterator right until we hit a scanner terminator
	while ( !isterm(input_buffer[b_offset + i]) ) {
		i++;
	}

	// there is a next line if our iterator has moved
	return i != 0;
}

/*
Determines whether or not the scanner has a next integer in its input buffer
@ param void
@ return 1 if the scanner has a next integer, 0 otherwise
*/
int sc_hasnexti(void) {

	int i = 0;
	int j = 0;

    if ( sc_hasnext() ) {

		// move the iterator right until we hit a non-whitespace character and the character is not a scanner terminator
	    while ( isspace(input_buffer[b_offset + i]) && !isterm(input_buffer[b_offset + i]) ) {
	    	i++;
	    }

        // if the character we land on is a '-', increment i one more time
        if (input_buffer[b_offset + i] == '-') i++;

		// move the iterator right until we hit a non-digit character
	    while ( isdigit(input_buffer[b_offset + i + j]) ) {
	    	j++;
	    }

	}

	// if our iterator has moved and we've landed on a whitespace character or a scanner terminator, then the next integer exists
	return ( j != 0 && ( isspace(input_buffer[b_offset + i + j]) || isterm(input_buffer[b_offset + i + j]) ) );
}

/*
Determines whether or not the scanner has a next hex integer in its input buffer
@ param void
@ return 1 if the scanner has a next integer, 0 otherwise
*/
int sc_hasnextx(void) {

	int i = 0;
	int j = 0;

    if ( sc_hasnext() ) {

		// move the iterator right until we hit a non-whitespace character and the character is not a scanner terminator
	    while ( isspace(input_buffer[b_offset + i]) && !isterm(input_buffer[b_offset + i]) ) {
	    	i++;
	    }

        // if the character we land on and the following character is a hex prefix "0x", increment the iterator two characters
        if (input_buffer[b_offset + i] == '0') {
            if (input_buffer[b_offset + i + 1] == 'x' || input_buffer[b_offset + i + 1] == 'X') {
                i += 2;
            }
        }

		// move the iterator right until we hit a non hex-digit character
	    while ( isxdigit(input_buffer[b_offset + i + j]) ) {
	    	j++;
	    }

	}

	// if the we have not iterated over any hex-digit characters, then no next integer exists
	return ( j != 0 && ( isspace(input_buffer[b_offset + i + j]) || isterm(input_buffer[b_offset + i + j]) ) );
}

/*
Determines whether or not the scanner has a next double in its input buffer
@ param void
@ return 1 if the scanner has a next double, 0 otherwise
*/
int sc_hasnextf(void) {
    // TO BE IMPLEMENTED
    return 0;
}
