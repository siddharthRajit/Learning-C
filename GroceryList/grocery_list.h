#pragma once

typedef struct Item {
    char *item_name;
    int quantity;
    bool checked;
} item_t;

int add_item(item_t *items, char *item_name, int quantity, int *count);


