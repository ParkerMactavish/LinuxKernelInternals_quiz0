#ifndef _QUEUE_H
#define _QUEUE_H
#include <stddef.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

void quicksort(node_t **);
#endif