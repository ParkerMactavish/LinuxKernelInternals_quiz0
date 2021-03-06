#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

/* Self-defined list_make_node_t to suffice subroutine in main */
node_t *list_make_node_t(node_t *list, int number) {
    node_t *newh = malloc(sizeof(node_t));
    newh->next = list;
    newh->value = number;
    return newh;
}

/* Self-defined list_free to suffice subrouting in maine */
void list_free(node_t **list) {
    node_t *current = *list, *nextEle;
    while (current) {
        nextEle = current->next;
        free(current);
        current = nextEle;
    }
}

int main(int argc, char **argv) {
    size_t count = 20;

    node_t *list = NULL;
    while (count--) {
        list = list_make_node_t(list, random() % 1024);
    }

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}        