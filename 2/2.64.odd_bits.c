/*
Write code to implement the following functions:
Return 1 when any odd bit of x equals 1; 0 otherwise.
Assume w=32.

int any_odd_one(unsigned x);
*/
#include <stdio.h>

int any_odd_one(unsigned x) {
    return !!(x & 0xAAAAAA);
}

int main() {
    unsigned x = 0xAAAAAAAA;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0xBBBBBBBB;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0x1;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0x50505050;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));

    return 0;
}

/*
Here the solution is pretty obvious. With the constraint of w=32 bits,
a simple mask selecting the odd bits of a number will suffice. Since 0xA has
bit representation 1010, we're selecting the odd bits w-1 and w-3, and discarding
the even bits w-2 and w-4.

Since the problem asks us to return a 1 or a 0, we use the double logical negation
to evaluate the result and return logical "true" or "false", 1 or 0 respectively.
You *could* simply return the result x & 0xAAAAAAAA, but this would return 0 or
any number including one. To guarantee we only return a zero or a one, the
logical negation converts the value of x & 0xAAAAAAAA to its truthiness and then
negates it. Since we're only using the negation for it's logical effects we want
to reverse the first negation with a second negation.

Since we're only interested in the effect of the logical operation, we can use
any logical operation here. (x & 0xAAAAAAAA) && (x & 0xAAAAAAAA) would also work
but is less efficient since we have to perform the bitwize operation twice, also
it just looks bad. You could also assign x & 0xAAAAAAAA back to x and return
x && x, or x || x. However I consider !!(x & 0xAAAAAAAA) to be more compact and
the meaning better communicated.
*/
