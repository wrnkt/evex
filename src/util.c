#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <util/util.h>

void usage(FILE *stream)
{
    fprintf(stream, "Enter a simple math expression (no parenthesis) and get the result.\n");
}

void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    
    char *err_prefix = "[ERROR]: ";
    
    size_t len = 100;
    char err[len];
    char msg[len];

    size_t n = vsnprintf(msg, len, fmt, args);
    assert(n >= 0 && n < len);

    strcat(err, err_prefix);
    strcat(err, msg);
    strcat(err, "\n");
    fputs(err, stderr);
}
