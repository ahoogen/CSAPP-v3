/*
Write a function int_shifts_are_arithmetic() that yields 1 when run on a machine
that uses arithmetic right shifts for data type int and yields 0 otherwise. Your
code should work on a machine with any word size.
*/
#include <stdio.h>

// int_shifts_are_arithmetic checks for arithmetical right shifting in both
// signed and unsigned integers.
int int_shifts_are_arithmetic() {
    int x = 1 << ((sizeof(int)<<3)-1);
    unsigned ux = (unsigned)x;
    x = x >> 8;
    ux = ux >> 8;

    return (x & 1 << ((sizeof(int)<<3)-1)) && // sign bit of x is carried after shifting
            !(ux & 1 << ((sizeof(int)<<3)-1)) && // ux msb is zero after shifting
            (ux & 1 << (((sizeof(int)-1)<<3)-1)); // ux shift worked properly. Necessary??
}

int main() {
    printf("This machine ");
    if (int_shifts_are_arithmetic()) {
        printf("DOES ");
    } else {
        printf("DOES NOT ");
    }
    printf("perform arithmetical right shifts.\n");
    return 0;
}

/*
I've only run this on my Macbook Pro, since all I have are x86 architecture
machines. If I really, really wanted to I could compile this for my ATMEL
ATMega68 microcontroller, but I don't want to have to build the power supply,
programmer and a readout LED to tell me if it works or not...

The logic here is to check whether a right shift is arithmetical or logical.
Arithmetic right shifts carry sign bits on signed integers, whereas logical
right shifts left-pad with zeros.

To test for this, one simply right shifts a signed number with the sign bit set,
then checks to make sure that the sign bit is still set after the shift.

Here, I've included tests to ensure that arithmetical right shifts are NOT used
on unsigned numbers that have their most significant bit set to 1. But, for the
scope of this assignment, it isn't strictly necessary.
*/
