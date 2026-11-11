#include <stdio.h>
#include <string.h>

typedef struct {
    size_t length;
    char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src) {

    if (dest == NULL || src == NULL) {
        return 1;
    }

    const int BUFFER = 64;
    int src_len = strlen(src);
    int remaining_space = 64 - dest.length - 1;

    if (src_len > remaining_space) {
        strncat(dest.buffer, src, remaining_space);
    }

    return 0;

}
