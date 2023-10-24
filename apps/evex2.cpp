#include <iostream>

#include "./util.h"

typedef enum {
    op,
    arg,
    open_paren,
    close_paren,
} token_kind_t;

typedef union {
    char c;
    int i;
    double d;
} value_t;

typedef enum {
    chrctr,
    ntgr,
    dbl
} value_type_t;

typedef struct {
    token_kind_t kind;
    value_type_t value;
} token_t;

int main(int argc, char** argv)
{
    if( argc < 2) {
        usage(stderr);
    }
    return 0;
}
