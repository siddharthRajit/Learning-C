#include "sneklang.h"
#include <stdio.h>

int main() {
    snek_object_t obj = {
        .kind = INTEGER,
        .data = { .v_int = 898583 }
    };
    format_object(obj, "Hello World");
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
