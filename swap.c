#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_ints(int *x, int *y);
void swap_strings(char **x, char **y);
void swap(void *p1, void *p, int size);

int main () {
    int a = 5;
    int b = 6;
    swap(&a, &b, sizeof(int));
    printf("a: %d\n", a);
    printf("b: %d\n", b);
}

void swap_ints(int *x, int *y) {
    int tmp = *x; // Stores value of x (1) into tmp, tmp = 1
    *x = *y; // Stores value of x = 2
    *y = tmp; //stores y as temp = 1
}

void swap_strings(char **x, char **y) {
    char *tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap(void *p1, void *p2, int size) {
    void *tmp = malloc(size);

    memcpy(tmp, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, tmp, size);

    free(tmp);
}
