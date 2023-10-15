#include <stdarg.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>

int custom_fprintf(FILE *stream, const char *format, ...)
{
    va_list args;
    int length, result;
    char *buffer;
    va_start(args, format);

    length = vsnprintf(NULL, 0, format, args) + 1; 
    va_end(args);

    buffer = malloc(length);
    if (buffer == NULL) {
      
        exit(EXIT_FAILURE);
    }

    va_start(args, format);
    vsnprintf(buffer, length, format, args);
    va_end(args);

    result = write(fileno(stream), buffer, length - 1);
    free(buffer);

    return (result);
}
