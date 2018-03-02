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
