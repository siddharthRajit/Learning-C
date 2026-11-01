#include <stdio.h>

typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

coordinate_t new_coordinate(int x, int y, int z);
coordinate_t scale_coordinate(struct Coordinate coord, int factor);
void coordinate_update_x(coordinate_t coord, int new_x);
coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x);

int main() {

    coordinate_t c = {
        .x = 2,
        .y = 3,
        .z = 4
    };

    printf("Coordinate 1: (%i, %i, %i)\n", c.x, c.y, c.z);
    coordinate_t c2 = coordinate_update_and_return_x(c, 10);
    printf("Coordinate updated: (%i, %i, %i)\n", c2.x, c2.y, c2.z);

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

coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x) {
    coord.x = new_x;
    return coord;
}
