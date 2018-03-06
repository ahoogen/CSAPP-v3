#include <stdio.h>
/*
You are given the task of writing a procedure int_size_is_32() that yields 1
when run on a machine for which an int is 32 bits, and yelds 0 otherwise. You are
not allowed to use the sizeof operator. Here is a first attempt:

// The following code does not run properly on some machines
int bad_int_size_is_32() {
    // Set most significant bit (msb) of 32-bit machine
    int set_msb = 1 << 31;
    // Shift past msb of 32-bit word
    int beyond_msb = 1 << 32;

    // set_msb is nonzero when word size >= 32
    // beyond_msb is zero when word size <= 32
    return set_msb && !beyond_msb;
}

When compiled and run on a 32-bit SUN SPARC, however, this procedure returns 0.
The following compiler message gives us an indication of the problem:

Warning: left shift count >= width of type

A. In what way does our code fail to comply with the C standard?
B. Modify the code to run properly on any machine for which data type int is
at least 32 bits.
C. Modify the code to run properly on any machine for whcih data type int is
at least 16 bits.

Answer A:
---------
The C standard (c99) tells us: "The integer promotions are performed on each of
the operands. The type of the result is that of the promoted left operand. If
the value of the right operand is negative or is greater than or equal to the
width of the promoted left operand, the behavior is undefined."

So since we're trying to shift integer 1 to the left 1 bit larger than the width
of a 32-bit integer, the results of this shift are undefined, which is what the
compiler is warning us about.

What exactly is occurring on a SUN SPARC 32 bit machine I am not sure, since I
do not have access to this machine to inspect the contents of beyond_msb.
Regardless, since the result of running the program produces 0, this means that
!beyond_msb evaluates to false, which means that beyond_msb must evaluate to
true, indicating that the shift never occurred, or that beyond_msb has some
other garbage value contained within it.

Answer B:
---------
The goal is to produce a number whose bit representation is a 1 in the 33rd bit
position (bit index starts at 0). The way to accomplish this is to first
generate a bit pattern that will fit in a 32 bit integer by shifting a 1 into
bit position 32 with 1 << 31.

Then to produce a number one bit position higher than this we can shift this
number one position to the left with set_msb << 1 and store this result in
beyond_msb. Since 1 is less than the width of an integer, the behavior of the
shift operator is well defined and we can expect the result to be a bit pattern
of 1 in the 33rd position, which (with 32 bit integers) will get truncated to
a zero value once assigned to a 32 bit integer.

If beyond_msb retains the 1 in the 33rd bit position, then the integer must be
larger than 32 bits and will produce a False value in the logical tests returned.
*/
int int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

/*
Answer C:
---------
To handle machines with 16 bit integers you perform the same operations as in
Answer B, but set_smb is set to 1 << 15 to put a 1 in the most significant bit
position for a 16 bit integer. Then shift that to the left one place to produce
beyond_msb. The tests remain the same, and the logic if !beyond_msb produces
false is the same as when an integer is larger than 16 bits and can properly
represent the bit pattern of beyond_msb without losing any data due to type-
width truncation.
*/
int int_size_is_16() {
    int set_msb = 1 << 15;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main() {
    printf("This machine ");
    if (int_size_is_16()) {
        printf("HAS 16 bit integers.\n");
    } else {
        if (int_size_is_32()) {
            printf("HAS 32 bit integers.\n");
        } else {
            printf("HAS at least 64 bit integers.\n");
        }
    }
    return 0;
}
