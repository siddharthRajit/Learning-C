#include <stdio.h>
#include "grocery_list.h"

#include <string.h>

#define MAX_ITEMS 100
#define NAME_LEN 50

int main() {

    //Create variables and structs
    //Save grocery list somewhere
    item_t items[MAX_ITEMS];
    int count = 0;
    int user_input = 0;
    load_items(items, &count);

    while (user_input != 7) {
        printf("1. List grocery item\n");
        printf("2. Add grocery item\n");
        printf("3. Update grocery item\n");
        printf("4. Delete grocery item\n");
        printf("7. Exit program\n");
        printf("Enter a choice (1-5): ");
        scanf("%d", &user_input);

        //Add functionality to add to the list
        switch (user_input) {
            case 1: {

                for (int i = 0; i < count; i++) {
                    printf("Item%d: %s x%d\n", i + 1, items[i].item_name, items[i].quantity);
                }
                break;
            }
            case 2: {
                char name[NAME_LEN];
                int quantity;
                printf("Enter a item name and quantity: ");
                scanf("%49s %d", name, &quantity);
                int result = add_item(items, name, quantity, &count);
                if (result == -1) { printf("Error"); }
                save_items(items, &count);
                break;
            }
            case 7: break;
            default: printf("INVALID INPUT");
        }
    }

}

int add_item(item_t *items, char *item_name, int quantity, int *count) {
    if (item_name == NULL || quantity == 0) { return -1; }
    if (*count >= MAX_ITEMS) { return -1; }

    strncpy(items[*count].item_name, item_name, NAME_LEN - 1);
    items[*count].item_name[NAME_LEN - 1] = '\0';
    items[*count].quantity = quantity;

    (*count)++;
    return 0;
}

void save_items(item_t* items, int* count) {
    FILE *fp = fopen("list.txt", "w");
    if (fp == NULL) { return; }

    for (int i = 0; i < *count; i++) {
        fprintf(fp, "%s %d\n", items[i].item_name, items[i].quantity);
    }

    fclose(fp);
}

void load_items(item_t *items, int *count) {
    FILE *fp = fopen("list.txt", "r");
    if (fp == NULL) { return; }

    char name[50];
    int quantity;
    while (*count < MAX_ITEMS && fscanf(fp, "%49s %d", name, &quantity) == 2) {
        add_item(items, name, quantity, count);
    }

    fclose(fp);
}