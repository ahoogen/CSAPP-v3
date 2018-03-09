#include <stdio.h>
#include <string.h> // Definition of memcpy

/*
Tiy are given the task of writing a function that will copy an integer val into
a buffer buf, but it should do so only if enough space is available in the
buffer.

Here's the code you write:

// Copy integer into buffer if space is available
// WARNING: The following code is buggy
void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes-sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}

This code makes use of the library function memcpy. Although its use is a bit
artificial here, where we simply want to copy and int, it illustrates an
approach commonly used to copy larger data structures.

You carefully test the code and discover that it always copies the value to the
buffer, even when maxbytes is too small.

A. Explain why the conditional test in the code always succeeds. Hint: The sizeof
operator returns a value of type size_t.

B. Show how you can rewrite the conditional test to make it work properly.

Answer A:
---------
In this case, (integer - unsigned integer) causes the unsigned integer value to
wrap (overflow) if the result of the operation cannot be stored in an unsigned
integer. Since the two types are being used in the comparison, the unsigned
value causes the result of the operation to become unsigned, which due to
overflow will always be greater than zero.

Answer B:
---------
size_t is defined in stddef.h as an unsigned integer type of at least 16 bits.
Since the type is unsigned and we do not want to overflow into an unsigned
integer result we can simply cast the result of sizeof operator to signed
integer.
*/

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes-(int)sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}

int main() {
    return 0;
}
