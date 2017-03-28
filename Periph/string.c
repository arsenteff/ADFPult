#include "mystring.h"

static unsigned char buf[SIZE_BUF];
static unsigned int size;

//void itos(int val, char *buf, unsigned int size, unsigned int r)
unsigned char *_itoa(int value, unsigned int radix)
{
    unsigned char *offset;      // a pointer to a string
    unsigned char *first;       // a pointer to the first digit
    unsigned int delta_y;       // the value of a digit
    unsigned int count = 0;     // a number of digits in the string

    offset = buf;
    first = buf;
    size=SIZE_BUF;

    // val is negative, so let's add '-' to the begin of the string.
    if (value < 0) {
        *offset++ = '-';
        value = -value;
        first = offset;
    }

    // Take special actions for hexademical and
    // octople countable systems and insert to the
    // begin of the string either the "\0x" or '0'
    // prefixes respectively.
    if (radix == HEX) {
        *offset++ = '0';
        *offset++ = 'x';
        first = offset;
    }
    else if (radix == OCT) {
        *offset++ = '0';
        first = offset;
    }
    if (!value) {
        *offset++ = '0';
        first = offset;
    }
    // Read and store digits into the string.
    while (value > 0 && size-- >= 0) {
        delta_y = (int)(value % radix);
        value /= radix;

        if (delta_y > 9)
            // The hexademical format.
       *offset++ = (delta_y - 10 + 'A');
        else
            // Binary, dicimal and octople formats.
            *offset++ = (delta_y + '0');
        count++;
    }

    // Points to the last digit.
    *offset-- = '\0';

    // Now our string corresponds to the integer
    // digits but it is in the reverse order. So make
    // the backward transformation of it. If it has
    // only two characters just swap them without any
    // additional actions.
    /*if (count == 1)
        return;
    else*/ if (count == 1) {
        char temp = (char)*offset;
        *offset-- = *first;
        *first++ = temp;
    }
    // For more than two characters in the string
    // reverse full string in the folowing cycle.
    else {
        delta_y = count / 2;

        while (delta_y--) {
            char temp = (char)*first;
            *first++ = *offset;
            *offset-- = temp;
        }
    }
    return buf;
}


