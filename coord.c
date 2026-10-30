#include <stdio.h>

struct Coordinate new_coordinate(int x, int y, int z);
struct Coordinate scale_coordinate(struct Coordinate coord, int factor);

typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

int main() {

    coordinate_t c = {
        .x = 2,
        .y = 3,
        .z = 4
    };

    printf("Coordinate 1: (%i, %i, %i)\n", c.x, c.y, c.z);

    int scale;
    printf("Scale: ");
    scanf("%i", &scale);

    coordinate_t coord_scaled = scale_coordinate(c, scale);
    printf("Coordinate scaled by %i: (%i, %i, %i)\n", scale, coord_scaled.x, coord_scaled.y, coord_scaled.z);

}

coordinate_t new_coordinate(int x, int y, int z) {
    coordinate_t new_c = {
        .x = x,
        .y = y,
        .z = z
    };
    return new_c;
};

coordinate_t scale_coordinate(coordinate_t coord, int factor) {
    coordinate_t scaled = {
        .x = coord.x * factor,
        .y = coord.y * factor,
        .z = coord.z * factor
    };
    return scaled;
};
