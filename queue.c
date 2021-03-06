#include "queue.h"

static inline void list_add_node_t(node_t **list, node_t *node) {
    node->next = *list;
    *list = node;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}

void quicksort_nonrecursive(node_t *list) {
    int eleNum = 0;
    node_t *elePtr = list;
    while (elePtr) {
        elePtr = elePtr->next;
        eleNum++;
    }
    
    int pivot, i = 0, leftIndex, rightIndex,
        *data = malloc(sizeof(int) * eleNum),
        *begin = malloc(sizeof(int) * eleNum),
        *end = malloc(sizeof(int) * eleNum);
    
    elePtr = list;
    eleNum = 0;
    while (elePtr) {
        data[eleNum] = elePtr->value;
        elePtr = elePtr->next;
        eleNum++;
    }
    
    begin[0] = 0; 
    end[0] = eleNum;
    while (i >= 0) {
        leftIndex = begin[i];
        rightIndex = end[i] - 1;
        if (leftIndex < rightIndex) {
            pivot = data[leftIndex];
            while (leftIndex < rightIndex) {
                while (data[rightIndex] >= pivot && leftIndex < rightIndex) 
                    rightIndex--;
                if (leftIndex < rightIndex)
                    data[leftIndex++] = data[rightIndex];
                
                while (data[leftIndex] <= pivot && leftIndex < rightIndex)
                    leftIndex++;
                if (leftIndex < rightIndex)
                    data[rightIndex--] = data[leftIndex];
            }
            data[leftIndex] = pivot;
            begin[i + 1] = leftIndex + 1;
            end[i + 1] = end[i];
            end[i++] = leftIndex;
        }
        else {
            i--;
        }
    }
    elePtr = list;
    for (int i = 0; i < eleNum; i++) {
        elePtr->value = data[i];
        elePtr = elePtr->next;
    }
    free(data);
    free(begin);
    free(end);
}