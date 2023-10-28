#ifndef EVEX_H
#define EVEX_H

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "util/util.h"

// NOTE: follow order of operations 0 -> END
static const char SUPPORTED_OPS[] = {'*', '+', '-'};
#define SUPPORTED_OPS_LEN (size_t) sizeof(SUPPORTED_OPS)/sizeof(SUPPORTED_OPS[0])

#define Arg_Fmt "(TYPE: %s | Value: %d | Op: %c | Visited: %d)\n"
#define Deconstruct_Arg(a) get_type_name(a.type), a.value, a.op, a.visited
#define Deconstruct_Arg_Ptr(a) get_type_name(a->type), a->value, a->op, a->visited

#define RIGHT 1
#define LEFT 0

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

typedef enum {
    UNKNOWN,
    MULT,
    ADD,
    SUB
} OPERATION_T;


const char *get_type_name(TYPE t);
void print_curr_expr(size_t count, Arg* args);

int is_op(char *c);
int is_number(char *c);
TYPE type_of(char *c);

int infix_valid_against_prev(char *cur, char* prev);
int infix_validate(int count, char **inputs, Arg *args);
int infix_next_operand(direction dir, Arg *args, size_t len, size_t operator_idx, Arg **arg);
OPERATION_T op_type_from_operator(operator o);

int infix_left_eval_op(Arg *l, Arg *r, Arg *op);
int infix_left_eval_add(Arg *l, Arg *r);
int infix_left_eval_sub(Arg *l, Arg *r);
int (*get_operation(OPERATION_T op))(Arg*, Arg*);
int infix_evaluate(Arg *args, size_t len);

size_t LAST_FROM(int dir, size_t len);
int DIRECTION(int dir);

size_t op_priority(Arg arg);
size_t get_priority_op_idx(Arg* args, size_t len);


#endif // EVEX_H
