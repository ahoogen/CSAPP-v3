#include <stdio.h>
#include <limits.h>

/*
Write a function with the following prototype:

// Determine whether arguments can be subtracted without overflowing
int sub_ok(int x, int y);

This function should return 1 if the computation x-y does not overflow.
*/

int sub_ok(int x, int y) {
    int sum = x - y;

    int x_sign = x & INT_MIN;
    int y_sign = y & INT_MIN;
    int sum_sign = sum & INT_MIN;

    int pos_over = x_sign && ~y_sign && ~sum_sign;
    int neg_over = ~x_sign && y_sign && sum_sign;

    return !(pos_over||neg_over);
}

/*
Solution explanation:

This solution is almost exactly like that of 2.73.saturate_add.c. With addtion,
both signs need to be the same in order to overflow. But with subtraction, the
signs must be different. So for this solution we need to test the pair of
operands negated separately from the other, while still checking for a difference
in sign bit from the first operand to the result of the subtraction.

The problem asks for our solution to return a 1 if the subtraction succeeds
without overflow, or 0 otherwise. For this we check if either overflow occurrs
and negate the result. If no overflow occurrs, then the inner test will result
with false and the negation will convert to true.
*/

int main() {
    int x = -2147483648;
    int y = 1;
    printf("%d - %d = %d: Sub ok?: %d\n", x, y, x - y, sub_ok(x, y));
    x = 2147483647;
    y = -1;
    printf("%d - %d = %d: Sub ok?: %d\n", x, y, x - y, sub_ok(x, y));
    x = 25;
    y = -25;
    printf("%d - %d = %d: Sub ok?: %d\n", x, y, x - y, sub_ok(x, y));
    return 0;
}
