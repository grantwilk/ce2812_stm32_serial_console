// file: scanner.h
// created by: Grant Wilk
// date created: 1/17/2020
// last modified: 1/20/2020
// description: Header file for scanner.c

// Sets the source input stream for the scanner
// void sc_source(FILE source);

// Fills the scanner's input buffer by getting input from the input source
void sc_get(void);

// Gets the next token from the input buffer and returns it
void sc_next(char * dest, int len);

// Gets the next line from the input buffer and returns it
void sc_nextln(char * dest, int len);

// Gets the next integer from the input buffer and returns it
int sc_nexti(void);

// Gets the next hex-integer from the input buffer and returns it
int sc_nextx(void);

// Gets the next double from the input buffer and returns it
double sc_nextf(void);

// Determines whether or not the scanner has a next token in its input buffer
int sc_hasnext(void);

// Determines whether or not the scanner has a next line in its input buffer
int sc_hasnextln(void);

// Determines whether or not the scanner has a next integer in its input buffer
int sc_hasnexti(void);

// Determines whether or not the scanner has a next hex integer in its input buffer
int sc_hasnextx(void);

// Determines whether or not the scanner has a next double in its input buffer
int sc_hasnextf(void);
