#include "stdio.h"

typedef enum HttpErrorCode {
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_INTERNAL_SERVER_ERROR = 501,
} http_error_code_t;

typedef enum BigNums {
    BIG = 501787485734085034,
    BIGGER,
    BIGGEST
} big_nums_t;

char *http_to_string(http_error_code_t code) {
    switch (code) {
        case HTTP_BAD_REQUEST: return "Bad Request";
        case HTTP_NOT_FOUND: return "Not Found";
        case HTTP_UNAUTHORIZED: return "Unauthorized";
        case HTTP_FORBIDDEN: return "Forbidden";
        case HTTP_INTERNAL_SERVER_ERROR: return "Internal Server Error";
        default: return "Unknown HTTP status code";
    }
}

int main() {
    printf("%zu\n", sizeof(http_error_code_t));
    printf("%zu\n", sizeof(big_nums_t));
}
