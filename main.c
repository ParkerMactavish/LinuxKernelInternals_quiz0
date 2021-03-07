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
    if (argc > 1)
        count = atoi(argv[1]);
    srandom(time(NULL));
    int randNum;
    node_t *list1 = NULL, *list2 = NULL;
    while (count--) {
        randNum = random();
        list1 = list_make_node_t(list1, randNum % 1024);
        list2 = list_make_node_t(list2, randNum % 1024);
    }

    list_display(list1);
    struct timespec start, end, diff;
    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort_nonrecursive(list1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    list_display(list1);
    if ((end.tv_nsec-start.tv_nsec)<0) {
        diff.tv_sec = end.tv_sec - start.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        diff.tv_sec = end.tv_sec-start.tv_sec;
        diff.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    printf("which takes %ld.%09ld seconds\n", diff.tv_sec, diff.tv_nsec);
    list_display(list2);
    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort(&list2);
    clock_gettime(CLOCK_MONOTONIC, &end);
    list_display(list2);
    if ((end.tv_nsec-start.tv_nsec)<0) {
        diff.tv_sec = end.tv_sec - start.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        diff.tv_sec = end.tv_sec-start.tv_sec;
        diff.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    printf("which takes %ld.%09ld seconds\n", diff.tv_sec, diff.tv_nsec);
    list_display(list2);

    if (!list_is_ordered(list1) || !list_is_ordered(list2))
        return EXIT_FAILURE;

    list_free(&list1);
    list_free(&list2);
    return EXIT_SUCCESS;
}        