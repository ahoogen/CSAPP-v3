#include <stdio.h>
/*
You just started working for a company that is implementing a set of procedures
to operate on a data structure where 4 signed bytes are packed into a 32-bit
unsigned. Bytes within the word are numbered from 0 (least significant) to 3
(most significant). You have been assigned the task of implementing a function
for a machine using two's-complement arithmetic and arithmetic right shifts with
the following prototype:

// Declaration of data type where 4 bytes are packed into an unsigned
typedef unsinged packed_t;

// Extract byte from word. Return as signed integer
int xbyte(packed_t word, int bytenum);

That is, the function will extract the designated byte and sign extend it to be
a 32-bit int.

Your predecessor (who was fired for incompetence) wrote the following code:

// Failed attempt at xbyte
int xbyte(packed_t word, int bytenum)
{
    return (word >> (bytenum << 3)) & 0xFF;
}

A. What is wrong with this code?
B. Give a correct implementation of the function that uses only left and right
shifts, along with one subtraction.

Answer A:
---------
Right-shifting on an unsigned will use logical right shift. Even if an arithmetic
right shift were used, using the mask to isolate the one byte will eliminate
any sign bits. But moot point, since in this case there will never be any
sign bits to eliminate, meaning only positive integers are possible in the range
0 to 255.
*/

typedef unsigned packed_t;

/*
Answer B:
---------
*/
int xbyte(packed_t word, int bytenum)
{
    int shift = (sizeof(word) - 1) << 3;
    return ((int)word << (shift - (bytenum << 3))) >> shift;
}

/*
Solution explanation:

Here my soluton uses two subtractions instead of one, since I did not assume
that word size is 32 bits. The additional subtraction was to calculate the
proper shift amount. Otherwise this solution uses the correct limitations of
operations. In this solution, however, xbyte() will function porperly in cases
where packed_t is of any width of at least one byte. Well... It would if I were
allowed to use conditionals to check the safety of the input of bytenum to fall
within allowed ranges of sizeof(packed_t)....

In order to isolate and return the correct signed byte integer extracted from
packed_t word, you left-shift word by shift - (bytenum << 3) number of bits.
This is the one subtraction allowed in the solution. In this case, shift is set
to 24 since packed_t is 32 bits, and represents the maximum shift amount to get
the zero-index byte shifted to the left, and then back to the zero-index byte
position. As bytenum increases, the left-shift amount decreases so that the
left-shift will always place the desired byte in the most-significant byte
position.

The results of the left shift are cast to a signed integer before the result
is then right-shifted to the least-significant byte position. Because of the
cast to signed integer, the right shift will perform arithmetical right shift
carrying the sign bit during the shift operation.
*/
int main() {
    // word values 3, 7, -4, -7
    packed_t word = 0x0307FCF9;
    printf("The values of word 0x%08X are:\n", word);
    printf("Index %d should be %d", 0, -7);
    printf("\tAt index %d: %d\n", 0, xbyte(word, 0));
    printf("Index %d should be %d", 1, -4);
    printf("\tAt index %d: %d\n", 1, xbyte(word, 1));
    printf("Index %d should be %d", 2, 7);
    printf("\tAt index %d: %d\n", 2, xbyte(word, 2));
    printf("Index %d should be %d", 3, 3);
    printf("\tAt index %d: %d\n", 3, xbyte(word, 3));
    return 0;
}
