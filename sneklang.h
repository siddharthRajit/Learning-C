#pragma once
#include <stddef.h>

typedef enum SnekObjectKind {
    INTEGER,
    STRING,
} snek_object_kind_t;

typedef union SnekObjectData {
    int v_int;
    char *v_string;
} snek_object_data_t;

typedef struct SnekObject {
    snek_object_kind_t kind;
    snek_object_data_t data;
} snek_object_t;

typedef struct Stack {
    size_t count;
    size_t capacity;
    void **data;
} stack_t;

snek_object_t new_integer(int);
snek_object_t new_string(char *str);
void format_object(snek_object_t obj, char *buffer);
stack_t *stack_new(size_t capacity);
void stack_push(stack_t *stack, void *obj);
void *stack_pop(stack_t *stack);
void stack_free(stack_t *stack);
void scary_stack_push(stack_t *stack);

