#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
The library function calloc has the following declaration:

void *calloc(size_t nmemb, size_t size);

According to the library documentation, "The calloc function allocates memory
for an array of nmemb elements of size bytes each. The ememory is set to zero.
If nmemb or size is zero, then calloc returns NULL."

Write an implementation of calloc that performs the allocation by a call to
malloc and sets the emory to zero via memset. Your code should not have any
vulnerabilities due to arithmetic overflow, and it should work correctly
regardless of the number of bits used to represent data of type size_t.

As a reference, functions malloc and memset have the following declarations:

void *malloc(size_t size);
void *memset(void *s, int c, size_t n);
*/

void* n_calloc(size_t nmemb, size_t size) {
    if (!nmemb || !size) {
        return NULL;
    }

    size_t b = nmemb * size;
    void *ar = NULL;

    if (b/nmemb == size) {
        ar = malloc(b);
        ar = memset(ar, 0, b);
    }

    return ar;
}

/*
Solution explanation (calloc renamed n_calloc to avoid name collision):

The vulnerability that could arrise in implementing your own version of calloc
is by allocating the needed memory to accommodate nmemb elements of size. The
total amount of memory needed is the multiplication of nmemb and size, which
can very easily overflow. So we will need to check for multiplication overflow.

The first requirement of calloc is that it returns NULL if nmemb or size is
zero. If multiplication succeeds without overflow, we can show this with the
formula (x == 0 || p/y == x). Since we don't want to allocate zero-length
memory the first part of this equation is handled by our check for zero on nmemb
and size.

Then we perform the multiplication b = nmemb * size, and then create a null
void pointer as our default return value in *ar. We then check if there has been
overflow in b when we multiplied nmemb and size by checking (b/nmemb == size).
If there were overflow, then this check would fail. If no overflow occurrs, then
we are safe to proceed with allocating b bytes of memory with malloc, and
setting b bytes of memory to 0 with memset.
*/

int main() {
    void *p = n_calloc(10, sizeof(int));
    if (p != NULL) {
        printf("Memory (10 * %lu) was allocated\n", sizeof(int));
    }

    free(p);

    p = n_calloc(10, SIZE_MAX);
    if (p == NULL) {
        printf("Memory (10 * %lu) was not allocated\n", SIZE_MAX);
    }
    free(p);
}
