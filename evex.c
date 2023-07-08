#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "./util.c"

// NOTE: follow order of operations 0 -> END
#define SUPPORTED_OPS (char[]) {'*', '+', '-'}
#define SUPPORTED_OPS_LEN (size_t) sizeof(SUPPORTED_OPS)/sizeof(SUPPORTED_OPS[0])

#define Arg_Fmt "(TYPE: %s | Value: %d | Op: %c | Visited: %d)\n"
#define Deconstruct_Arg(a) get_type_name(a.type), a.value, a.op, a.visited
#define Deconstruct_Arg_Ptr(a) get_type_name(a->type), a->value, a->op, a->visited

#define RIGHT 1
#define LEFT 0

#define LAST_FROM(dir, len) ((dir) ? ((len) - 1) : (0))
#define DIRECTION(dir) ((dir) ? (1) : (-1))


typedef enum {
    UNDEF = -1,
    OP = 0,
    NUM,
} TYPE;

typedef char operator;
typedef size_t priority;
typedef int visited;
typedef int direction;

typedef struct {
    TYPE type;
    int value;
    operator op;
    priority priority;
    visited visited;
} Arg;


const char *get_type_name(TYPE t);
void print_curr_expr(size_t count, Arg* args);

int is_op(char *c);
int is_number(char *c);
TYPE type_of(char *c);

int infix_valid_against_prev(char *cur, char* prev);
int infix_validate(int count, char **inputs, Arg *args);
int infix_next_operand(direction dir, Arg *args, size_t len, size_t operator_idx, Arg **arg);
int infix_left_eval_op(Arg *l, Arg *r, Arg *op);
int infix_evaluate(Arg *args, size_t len);

size_t op_priority(Arg arg);
size_t get_priority_op_idx(Arg* args, size_t len);


const char *get_type_name(TYPE t) {
    switch (t) {
        case UNDEF: return "Undefined";
        case OP: return "Operation";
        case NUM: return "Number";
        default:
            return "UNKNOWN";
            //assert(0);
    }
}


int is_op(char *c)
{
    if (strlen(c) != 1) {
        return 0;
    }

    for (size_t i = 0; i < SUPPORTED_OPS_LEN; ++i) {
        if (*c == SUPPORTED_OPS[i]) {
            return 1;
        }
    }

    return 0;
}

int is_number(char *c)
{
    return isdigit(*c);
}

TYPE type_of(char *c)
{
    if (c == NULL) {
        return -1;
    }

    // NOTE: these branches are evaluated twice when true??
    if (is_op(c)) {
        return OP;
    } else if (is_number(c)) {
        return NUM;
    }
    exit(1);
}

int infix_valid_against_prev(char *cur, char* prev)
{
    TYPE t = type_of(cur);
    if (t == type_of(prev)) {
        char *type_desc = (t == OP) ? "the operator" : "the number";
        error("%s '%s' cannot follow '%s' in infix notation.", type_desc, cur, prev);
        return 0;
    }
    return 1;
}

int infix_validate(int count, char **inputs, Arg *args)
{
    TYPE t;
    char *prev_elem;
    char *input;
    for (int i = 0; i < count; ++i) {
        input = inputs[i];

        if (!infix_valid_against_prev(input, prev_elem)) {
            return 0;
        }

        t = type_of(input);

        if (t == OP) {
            // printf("|%s| is a valid operation.\n", input);
            args[i].op = *input;
        } else if (t == NUM) {
            // printf("|%s| is a valid number.\n", input);
            args[i].value = atoi(input);
        } else {
            // printf("|%s| is an invalid input.\n", input);
            usage(stderr);
            return 0;
        }
        args[i].type = t;
        prev_elem = input;
    }
    return 1;
}

void print_curr_expr(size_t count, Arg* args)
{
    printf("CURRENT EXPR:\n");
    printf("-----------------\n");
    for (size_t i = 0; i < count; i++) {
        printf(Arg_Fmt, Deconstruct_Arg(args[i]));
    }
    printf("-----------------\n");
}

size_t op_priority(Arg arg)
{
    assert((arg.type == OP) && arg.op && !arg.value);
    for (size_t i = 0; i < SUPPORTED_OPS_LEN; i++) {
        if (arg.op == SUPPORTED_OPS[i]) {
            return i;
        }
    }
    error("Could not find operation '%c' in SUPPORTED_OPS.", arg.op);
    assert(0 && "Something went wrong.");
}

size_t get_priority_op_idx(Arg* args, size_t len)
{
    int priority_assigned = 0;
    size_t priority_op_idx = 0;
    for (size_t i = 0; i < len; ++i) {
        if (args[i].op) {
            if (args[i].visited) {
                continue;
            }
            if (!priority_assigned) {
                priority_op_idx = i;
                priority_assigned = 1;
            }

            size_t cur_op_priority = op_priority(args[i]);

            if (cur_op_priority == 0) {
                priority_op_idx = i;
                break;
            }

            if (cur_op_priority <= op_priority(args[priority_op_idx])) {
                priority_op_idx = i;
            }
        }
    }
    return priority_op_idx;
}

int infix_left_eval_op(Arg *l, Arg *r, Arg *op)
{
    assert(l->type == NUM);
    assert(r->type == NUM);
    assert(op->type == OP);
    int result;
    operator o = op->op;
    if (o == '+') {
        result = l->value + r->value;
        l->value = result;
        r->value = 0;
    } else {
        error("Operation '%c' not implemented.\n");
        assert(0 && "BAD OPERATION.");
    }
    op->visited = 1;
    return 0;
}

int infix_next_operand(direction dir, Arg *args, size_t len, size_t operator_idx, Arg **arg)
{
    if (operator_idx == LAST_FROM(dir, len)) {
        return 0;
    }

    size_t offset = 1;
    size_t idx = operator_idx + (offset * DIRECTION(dir));

    *arg = &args[idx];
    while( (*arg)->type != NUM ) {
        ++offset;
        idx = operator_idx + (offset * DIRECTION(dir));
        *arg = &args[idx];
    }
    return 1;
}

int infix_evaluate(Arg *args, size_t len)
{
    size_t op_idx;
    Arg *op;
    Arg *l_operand = args, *r_operand = args;
    size_t l_operand_idx, r_operand_idx;
    do {
        op_idx = get_priority_op_idx(args, len);
        op = &args[op_idx];

        if (
            infix_next_operand(LEFT, args, len, op_idx, &l_operand)
            &&
            infix_next_operand(RIGHT, args, len, op_idx, &r_operand)
        ) {
            infix_left_eval_op(l_operand, r_operand, op);
        } else {
            break;
        }

        assert( (l_operand != r_operand) && "The left and right operand are equal." );

    } while (1);

    return l_operand->value;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage(stderr);
        exit(1);
    }

    size_t MAX_ARGS = argc - 1;
    Arg* args = malloc(MAX_ARGS);

    argv++;
    if (!infix_validate(MAX_ARGS, argv, args)) {
        exit(1);
    }

    int result = infix_evaluate(args, MAX_ARGS);
    printf("[RESULT]: %d\n", result);

    return 0;
}
