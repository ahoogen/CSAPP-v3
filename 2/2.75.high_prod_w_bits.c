#include <stdio.h>

/*
Suppose we want to compute the complete 2w-bit representation of x * y where
both x and y are unsigned. On a machine for which data type unsigned is w bits.
The low-order w bits of the product can be computed with the expression x*y, so
we only requre a procedure with prototype:

unsigned unsigned_high_prod(unsigned x, unsigned y);

that computes the high-order w bits of x * y for unsigned variables.

We have access to a library function with prototype:

int signed_high_prod(int x, int y);

that computes the high-order w bits of x * y for the case where x and y are in
two's complement form. Write code calling this procedure to implement the
function for unsigned arguments. Justify the correctness of your solution.

Hint: Look at x' * y' in the derivation of Equation 2.18.
*/
unsigned unsigned_high_prod(unsigned x, unsigned y) {
    return (unsigned)signed_high_prod((int)x, (int)y);
}

/*
Justification for this solution:

This is not the correct solution, or if it is I have no justification for why...
I was working under the assumption that there is a bit-level equivelance between
signed and unsigned multiplication. However, that only applies to the low-order,
or modulus 2^w result. There is not a high-order equivelance of bits between
signed and unsigned.

I've moved on to other things, but will return to this.
*/
