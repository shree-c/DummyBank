#include <stdio.h>
#include <stdlib.h>
int main() {
    char **lineptr;
    char *test;
    lineptr = (char **) malloc(10 * sizeof(char*));
    //*lineptr = (char *) malloc(30*sizeof(char*));
    size_t *n;
    *n = 0;
    size_t i = getline(lineptr, n, stdin);
    printf("%s", *lineptr);
}
