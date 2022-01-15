#include <stdlib.h>
#include <string.h>

char **split(char *str, const char *delim)
{
    int x = 0;
    char *next;
    char **dst = NULL;

    next = strtok(strdup(str), delim);

    dst = realloc(dst, (x+1) * sizeof(char));

    while( next != NULL ) {
        dst[x]=next;
        next = strtok(NULL, delim);
        x++;
    }

    return dst;
}
