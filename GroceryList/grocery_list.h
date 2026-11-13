#pragma once

typedef struct Item {
    char item_name[50];
    int quantity;
    bool checked;
} item_t;

int add_item(item_t *items, char *item_name, int quantity, int *count);
void save_items(item_t *items, int *count);
void load_items(item_t *items, int *count);


