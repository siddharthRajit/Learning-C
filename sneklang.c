#include "sneklang.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    stack_t *stack1 = stack_new(5);

    stack_push(stack1, &a);
    stack_push(stack1, &b);
    stack_push(stack1, &c);
    stack_push(stack1, &d);
    stack_pop(stack1);

    for (size_t i = 0; i < stack1->count; i++) {
        printf("%d\n", *(int *)stack1->data[i]);
    }
}

void format_object(snek_object_t obj, char *buffer) {
    switch (obj.kind) {
        case INTEGER:
            printf("int: %d", obj.data.v_int);
            return;
        case STRING:
            printf("string: %s", obj.data.v_string);
            return;
        default:
            printf("unknown");
            return;
    }
}

snek_object_t new_integer(const int i) {
    return (snek_object_t) {
        .kind = INTEGER,
        .data = {.v_int = i},
    };
}

snek_object_t new_string(char *str) {
    return (snek_object_t) {
    .kind = STRING,
    .data = {.v_string = str}
    };
}

stack_t *stack_new(size_t capacity) {
    stack_t *s = malloc(sizeof(stack_t));
    if (s == NULL) { return NULL; }

    s->count = 0;
    s->capacity = capacity;
    s->data = malloc(sizeof(void *) * capacity);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    return s;
}

void stack_push(stack_t *stack, void *obj) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, sizeof(void *) * stack->capacity);
        if (stack->data == NULL) { return; }
    }

    stack->data[stack->count] = obj;
    stack->count++;
}

void *stack_pop(stack_t *stack) {
    if (stack->count == 0) { return NULL; }
    stack->count--;
    return stack->data[stack->count];
}
