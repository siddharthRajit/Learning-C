#include <stdlib.h>
#include "snekobject.h"
#include <string.h>
#include <stdio.h>

int main() {

    snek_object_t *obj1 = new_snek_array(3);
    snek_object_t *x = new_snek_integer(8);
    snek_object_t *y = new_snek_float(5.0);
    snek_object_t *z = new_snek_string("Hello");

    snek_array_set(obj1, 0, x);
    snek_array_set(obj1, 1, y);
    snek_array_set(obj1, 2, z);

    snek_object_t *x1 = snek_array_get(obj1, 0);
    snek_object_t *y1 = snek_array_get(obj1, 1);
    snek_object_t *z1 = snek_array_get(obj1, 2);

    printf("Index 0: %d\n", x1->data.v_int);
    printf("Index 1: %f\n", y1->data.v_float);
    printf("Index 2: %s\n", z1->data.v_string);

}

snek_object_t *new_snek_integer(int value ) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = INTEGER;
    obj->data.v_int = value;

    return obj;
}

snek_object_t *new_snek_float(float value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = FLOAT;
    obj->data.v_float = value;

    return obj;
}

snek_object_t *new_snek_string(char *value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = STRING;
    obj->data.v_string = malloc(strlen(value) + 1);
    if (obj->data.v_string == NULL) { return NULL; }
    strcpy(obj->data.v_string, value);

    return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x,
    snek_object_t *y,
    snek_object_t *z
) {
    if (x == NULL || y == NULL || z == NULL) { return NULL; }

    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        free(obj);
        return NULL;
    }

    obj->kind = VECTOR3;
    obj->data.v_vector3.x = x;
    obj->data.v_vector3.y = y;
    obj->data.v_vector3.z = z;

    return obj;
}

snek_object_t *new_snek_array(size_t size) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = ARRAY;

    snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
    if (elements == NULL) { return NULL; }
    obj->data.v_array = (snek_array_t){ .size = size, .elements = elements};


  return obj;
}

bool snek_array_set(
    snek_object_t *snek_object,
    size_t index,
    snek_object_t *value
) {
    if (snek_object == NULL || value == NULL) { return false; }
    if (snek_object->kind != ARRAY) { return false; }
    if (index >= snek_object->data.v_array.size) { return false; }

    snek_object->data.v_array.elements[index] = value;

    return true;
}
snek_object_t *snek_array_get(snek_object_t *snek_object, size_t index) {
    if (snek_object == NULL) { return NULL; }
    if (snek_object->kind != ARRAY) { return NULL; }
    if (index >= snek_object->data.v_array.size) { return NULL; }

    return snek_object->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj) {
    if (obj == NULL) { return -1; }

    switch (obj->kind) {
        case INTEGER: return 1;
        case FLOAT: return 1;
        case STRING: return (int)strlen(obj->data.v_string);
        case VECTOR3: return 3;
        case ARRAY: return (int)obj->data.v_array.size;
        default: return -1;
    }
    ;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) { return NULL; }

    switch (a->kind) {
        case INTEGER: {
            switch (b->kind) {
                case INTEGER: return new_snek_integer(a->data.v_int + b->data.v_int);
                case FLOAT: return new_snek_float((float)a->data.v_int + b->data.v_float);
                default: return NULL;
            }
        }
        case FLOAT: {
            switch (b->kind) {
                case INTEGER: return new_snek_float(a->data.v_float + (float)b->data.v_int);
                case FLOAT: return new_snek_float(a->data.v_float + b->data.v_float);
                default: return NULL;
            }
        }
        case STRING: {
            if (b->kind != STRING) { return NULL; }
            size_t length = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
            char *str = calloc(sizeof(char *), length);
            strcat(str, a->data.v_string);
            strcat(str, b->data.v_string);
            snek_object_t *newstr = new_snek_string(str);
            free(str);
            return newstr;
        }
        case VECTOR3: {
            if (b->kind != VECTOR3) { return NULL; }
            return new_snek_vector3(
                snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
                snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
                );

        }
        case ARRAY: {
            if (b->kind != ARRAY) { return NULL; }
            size_t length = a->data.v_array.size + b->data.v_array.size;
            snek_object_t *new_array = new_snek_array(length);

            for (size_t i = 0; i < a->data.v_array.size; i++) {
                snek_object_t *element = snek_array_get(a, i);
                snek_array_set(new_array, i, element);
            }

            for (size_t i = 0; i < b->data.v_array.size; i++) {
                snek_object_t *element = snek_array_get(b, i);
                snek_array_set(new_array, i + a->data.v_array.size, element);
            }
            return new_array;
        }
    }
}