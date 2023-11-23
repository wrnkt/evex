#include <cassert>
#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstdarg>
#include <cassert>
#include <util/util.hpp>

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
