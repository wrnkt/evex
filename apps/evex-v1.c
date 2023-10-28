#include "evex/evex.h"
#include "util/util.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage(stderr);
        exit(1);
    }

    size_t MAX_ARGS = argc - 1;
    Arg* args = malloc(MAX_ARGS*(sizeof(Arg)));

    argv++;
    if (!infix_validate(MAX_ARGS, argv, args)) {
        exit(1);
    }

    int result = infix_evaluate(args, MAX_ARGS);
    printf("[RESULT]: %d\n", result);
    free(args);

    return 0;
}
