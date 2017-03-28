#ifndef __STRING_H
#define __STRING_H

#define SIZE_BUF 33

// The following constants must be used during the function call.
enum Radix {
    BIN = 2,    //BINARY
    OCT = 8,    //OCTOPLE
    DEC = 10,   //DECIMAL
    HEX = 16    //HEXADEMICAL
};

extern unsigned char *_itoa(int value, unsigned int radix);

#endif /*__STRING_H*/

