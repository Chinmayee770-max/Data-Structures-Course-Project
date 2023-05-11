#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MENU_ITEMS 10

struct MenuItem {
    int item_number;
    char name[50];
    int preparation_time;
};

struct OrderItem {
    int item_number;
    char name[50];
};

struct Order {
    int order_number;
    struct OrderItem* items;
    int item_count;
    int total_time;
    time_t time_ordered;
    struct Order* next;
};

struct MenuItem menu[MAX_MENU_ITEMS];
struct Order* order_list = NULL;
int order_count = 1;

void add_menu_item(int item_number, const char* name, int preparation_time) {
    if (item_number >= 0 && item_number < MAX_MENU_ITEMS) {
        menu[item_number].item_number = item_number;
        strncpy(menu[item_number].name, name, sizeof(menu[item_number].name));
        menu[item_number].preparation_time = preparation_time;
    }
}

void swap_orders(struct Order* order1, struct Order* order2) {
    int temp_order_number = order1->order_number;
    struct OrderItem* temp_items = order1->items;
    int temp_item_count = order1->item_count;
    int temp_total_time = order1->total_time;
    time_t temp_time_ordered = order1->time_ordered;

    order1->order_number = order2->order_number;
    order1->items = order2->items;
    order1->item_count = order2->item_count;
    order1->total_time = order2->total_time;
    order1->time_ordered = order2->time_ordered;

    order2->order_number = temp_order_number;
    order2->items = temp_items;
    order2->item_count = temp_item_count;
    order2->total_time = temp_total_time;
}

void take_order() {
    struct Order* new_order = (struct Order*)malloc(sizeof(struct Order));
    new_order->order_number = order_count++;
    new_order->time_ordered = time(NULL);
    new_order->next = NULL;

    int item_number;
    int total_time = 0;
    int item_count = 0;

    printf("Enter the number of items: ");
    scanf("%d", &item_count);

    new_order->items = (struct OrderItem*)malloc(item_count * sizeof(struct OrderItem));
    new_order->item_count = item_count;

    for (int i = 0; i < item_count; i++) {
        printf("Enter item number %d: ", i + 1);
        scanf("%d", &item_number);

        if (item_number < 0 || item_number >= MAX_MENU_ITEMS) {
            printf("Invalid item number: %d\n", item_number);
            i--;  
            continue;
        }

        new_order->items[i].item_number = item_number;
        strncpy(new_order->items[i].name, menu[item_number].name, sizeof(new_order->items[i].name));
        total_time += menu[item_number].preparation_time;
    }

    new_order->total_time = total_time;

    struct Order* current = order_list;
    struct Order* previous = NULL;

    if (order_list == NULL) {
        order_list = new_order;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_order;
    }

    struct Order* temp = NULL;
    int swapped;

    do {
        swapped = 0;
        current = order_list;

        while (current->next != temp) {
            if (current->total_time > current->next->total_time) {
                swap_orders(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        temp = current;
    } while (swapped);

    printf("Order taken successfully. Order number is %d\n", new_order->order_number);
}

void remove_order(int order_number) {
    struct Order* current = order_list;
    struct Order* previous = NULL;

    while (current != NULL && current->order_number != order_number) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Order not found.\n");
    } else {
        if (previous == NULL) {
            order_list = current->next;
        } else {
            previous->next = current->next;
        }
        free(current->items);
        free(current);
        printf("Order %d removed.\n", order_number);
    }
}

void display_orders() {
    printf("Orders:\n");
    struct Order* current = order_list;
    int previous_order_number = -1;

    while (current != NULL) {
        if (current->order_number != previous_order_number) {
            printf("Order Number: %d, Total Time: %d minutes\n", current->order_number, current->total_time);
            previous_order_number = current->order_number;
        }
        current = current->next;
    }
}

int main() {
   
    add_menu_item(0, "Espresso", 3);
    add_menu_item(1, "Cappuccino", 5);
    add_menu_item(2, "Latte", 5);
    add_menu_item(3, "Mocha", 7);
    add_menu_item(4, "Americano", 4);
    add_menu_item(5, "Macchiato", 6);

    int choice;

    while (1) {
        printf("\nCoffee Shop Order Management System\n");
        printf("1. Take Order\n");
        printf("2. Remove Order\n");
        printf("3. Display Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                take_order();
                break;
            case 2:
                printf("Enter the order number to remove: ");
                scanf("%d", &choice);
                remove_order(choice);
                break;
            case 3:
                display_orders();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
