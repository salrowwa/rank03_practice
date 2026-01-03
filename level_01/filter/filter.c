#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 1024

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t i;
    unsigned char *d = dst;
    const unsigned char *s = src;

    if (!dst && !src)
        return NULL;

    for (i = 0; i < n; i++)
        d[i] = s[i];

    return dst;
}

int main(int argc, char const *argv[])
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);

    char buffer[BUFFERSIZE];
    char *alltext = NULL;
    char *temp_buffer;
    char *replace;

    ssize_t numbers_of_byts;
    size_t len_alltext = 0;
    size_t index;
    size_t i;
    size_t len_argv = strlen(argv[1]);

    while ((numbers_of_byts = read(0, buffer, BUFFERSIZE)) > 0)
    {
        temp_buffer = realloc(alltext, len_alltext + numbers_of_byts);
        if (NULL == temp_buffer)
        {
            perror("Error");
            free(alltext);
            return (1);
        }
        alltext = temp_buffer;
        memcpy(alltext + len_alltext, buffer, numbers_of_byts);
        len_alltext += numbers_of_byts;
    }

    if (numbers_of_byts < 0)
    {
        perror("Error");
        free(alltext);
        return (1);
    }

    while ((replace = memmem(alltext, len_alltext, argv[1], len_argv)))
    {
        index = replace - alltext;
        write (1, alltext, index);
        i = 0;
        while (i < len_argv)
        {
            write (1, "*", 1);
            i++;
        }
        memmove(alltext, replace + len_argv, len_alltext - index - len_argv);
        len_alltext -= (index + len_argv);
    }

    if (len_alltext > 0)
        write (1, alltext, len_alltext);

    free(alltext);
    return (0);
}
