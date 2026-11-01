#include <stdio.h>

static void strcat(char *str1, const char *str2) {

    int idx = 1;
    while (1) {
        if (str1[idx] == '\0') {
            break;
        }
        idx++;
    }

    int str2_pointer = 0;
    while (1) {
        str1[idx + str2_pointer] = str2[str2_pointer];

        if (str2[str2_pointer] == '\0') {
            return;
        }
    str2_pointer++;
    }
}
