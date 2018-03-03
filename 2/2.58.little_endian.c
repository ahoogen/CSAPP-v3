/*
Write a procedure is_little_endian that will return 1 when compiled and run on a
little endian machine, and will return 0 when compiled and run on a big endian
machine. This program should run on any machine, regardless of its word size.
*/
#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
    int x = 0xFF000001;
    byte_pointer c = (byte_pointer)&x;
    return c[0] == 0x01;
}

int main() {
    printf("This machine is ");
    if (is_little_endian()) {
        printf("LITTLE ");
    } else {
        printf("BIG ");
    }
    printf("endian.\n");
    return 0;
}

/*
In order to test if your machine is little endian, you may be tempted to
simply test for a 1 in the position of the least significant bit. However
little endianness is abstracted away from the implementations of bit position
operations. Remember that little or big endianness is determined by how the
system *stores* values in memory.

To test for little or big endianness correctly you need to examine how your
value is physically stored in memory on the system under test. But you can't
access byte position x of a multibyte datatype, you can only access the entire
datatype's value when directly referencing it.

Therefore we will need to cast our test integer into a datatype we can examine
on a byte-by-byte level. This is where char pointers come in handy.

We create a new type called byte_pointer which has a datatype of unsigned char *.
Then we create our integer for test (0xFF000001, it has a "big" end and a
"little" end) and then cast this to a new byte_pointer we've named 'c'. We can
now inspect the individual bytes of our integer in the order in which they are
stored on the system.

Remember that in a little endian system, the least significant byte is stored
in the lower memory addresse, whereas in a big endian system the most
siginificant byte is stored in the lower memory address.

So for our integer value of 0xFF000001, on a big endian system (with a word size
of 32 bits) we would expect to see the value of c[0]--the first byte of our
integer in memory--to be equal to 0xFF. But in a little endian system, we would
expect the value of c[0] to be 0x01. So we test for c[0] to equal 0x01, and that
is our return.
*/
