#include <stdio.h>

/*
Write code for a function whith the following prototype:

// Addition that saturates to TMin or TMax
int saturating_add(int x, int y);

Instead of overflowing the way normal two's complement addition does, saturating
addition returns TMax when there would be positive overflow, and TMin when there
would be negative overflow. Saturating arithmetic is commonly used in protrams
that perform digital signal processing.

Your function should follow the bit-level integer coding rules on page 165.
*/

#define TMax (((unsigned)1 << ((sizeof(int) << 3) - 1)) - 1)
#define TMin -(TMax + 1)

int saturating_add(int x, int y) {
    int w = sizeof(int) << 3;
    int sign_mask = 1 << (w-1);
    int sum = x + y;

    int x_sign = x & sign_mask;
    int y_sign = y & sign_mask;
    int sum_sign = sum & sign_mask;

    int pos_over = ~x_sign & ~y_sign & sum_sign;
    int neg_over = x_sign & y_sign & ~sum_sign;

    (pos_over) && (sum = TMax);
    (neg_over) && (sum = TMin);

    return sum;
}

/*
Solution explanation:

This solution works by detecting overflow by tracking the change in sign bit.
Recall that a positive overflow will result in a negative value, and a negative
overflow will result in a positive value. In order to overflow in either
direction the sign bits of both operands must be the same.

To detect the overflow the sign-bit must have changed. For positive
overflow we bitwise AND ~x_sign, ~y_sign and sum_sign, then any non-zero value
will indicate that a positive overflow has occurred. For negative overflow
we do the opposite with a bitwise AND of x_sign, y_sign and ~sum_sign.

Positive Overflow:
  0111  sign: ~0000 -->    1111
+ 0001        ~0000 -->  & 1111
------       ------ -->  & 1000
  1000         1000 -->  ------
                    -->    1000

No Positive Overflow:
  0111  sign: ~0000 -->    1111
+ 0000        ~0000 -->  & 1111
------      ------  -->  & 0000
  0111         0000 -->  ------
                    -->    0000

Negative Overflow:
  1000  sign: 1000 -->    1000
+ 1111        1000 -->  & 1000
------      ------ -->  & 1111
 10000       ~0000 -->  ------
                   -->    1000

No Negative Overflow:
  1010  sign: 1000 -->    1000
+ 1110        1000 -->  & 1000
------      ------ -->  & 0111
  1000       ~1000 -->  ------
                   -->    0000

This allows us to assign an overflow indicator for testing later on. But since
the problem solution dissallows the use of conditionals, we need an alternate
way to test for positive, negative or no overflow.

The latter is simple: if there is no overflow, then the value of sum is our
default return value. However, if there is positive or negative overflow we
need to somehow alter the value of sum to be either TMax or TMin respectively.

Recall that the logical AND operation (&&) takes two operands, and that the
second operand is only evaluated if the first evaluates to True. So we can use
logical AND as a conditional test where the second operand is an assignment of
the new value to sum.

int sum = x + y; // This is the default value, unchanged if no overflow happens
...
(pos_over) && (sum = TMax); // Only evaluated if pos_over is true
(neg_over) && (sum = TMin); // Only evaluated if neg_over is true

Both pos_over and neg_over can be false, which indicates that no overflow has
occurred. If overflow has occurred, however, only one of pos_over or neg_over
can be true at any one time, so only one of the two second operands will ever be
evaluated, re-assigning TMax or TMin into sum.

The best way to think of what is happening here is the use of a switch statement
where sum is the default, and pos_over and neg_over are the case statements, and
the sedond operands are the statements executed when a case is matched.
*/

int main() {
    printf("TMax is: %d\n", TMax);
    printf("TMin is: %d\n", TMin);
    int x = TMax - 1;
    int y = 1;
    printf("%d + %d = %d\n", x, y, saturating_add(x, y));
    x = TMax;
    printf("%d + %d = %d\n", x, y, saturating_add(x, y));
    x = TMin + 1;
    y = -1;
    printf("%d + %d = %d\n", x, y, saturating_add(x, y));
    x = TMin;
    printf("%d + %d = %d\n", x, y, saturating_add(x, y));
    x = -10;
    y = 10;
    printf("%d + %d = %d\n", x, y, saturating_add(x, y));
    return 0;
}
