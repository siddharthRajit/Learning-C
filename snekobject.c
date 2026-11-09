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
