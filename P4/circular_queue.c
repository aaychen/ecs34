#include "circular_queue.h"

#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

// FILE #3 TO SUBMIT

struct CirQueue
{
    int capacity;
    int* items;
    int headIndex;
    int length;
};

CirQueue* cirQueueCreate(int capacity)
{
    if (capacity < 1) return NULL;
    CirQueue* queue = malloc(sizeof(CirQueue));
    queue->capacity = capacity;
    queue->items = malloc(queue->capacity * sizeof(int));
    queue->headIndex = -1;
    queue->length = 0;
    return queue;
}

int cirQueueDestroy(CirQueue* queue)
{
    if (!queue) return 0;
    free(queue->items);
    free(queue);
    return 1;
}

// Insert at rightmost available slot
// If past end of array, instead insert at beginning of array
// If circular queue is full (no more available slots), enqueue fails
int cirQueueEnqueue(CirQueue* queue, int val)
{
    if (!queue || queue->length == queue->capacity) return 0;
    if(queue->headIndex == -1) {
        queue->items[0] = val;
        queue->headIndex = 0;
    } else {
        int tempIndex = queue->headIndex + queue->length;
        if (tempIndex < queue->capacity) {
            queue->items[tempIndex] = val;
        } else {
            int wrapIndex = (tempIndex - queue->capacity) % queue->capacity;
            queue->items[wrapIndex] = val;
        }
    }
    queue->length++;

    // printf("\nQueue after enqueue:\n");
    // for (int i = queue->headIndex; i < queue->headIndex + queue->length; i++) {
    //     printf("%d\n", *queue->items[i]);
    // }
    // printf("\n");

    return 1;
}

// Use lazy deletion instead (mark item as deleted instead of actually erasing)
int cirQueueDequeue(CirQueue* queue, int* val)
{
    if (!queue || queue->headIndex == -1) return 0;
    *val = queue->items[queue->headIndex];
    queue->items[queue->headIndex] = 1;
    queue->headIndex++;
    if (queue->headIndex == queue->capacity)
        queue->headIndex = 0;
    queue->length--;
    if (queue->length == 0) 
        queue->headIndex = -1;

    // printf("\nheadIndex: %d\n", queue->headIndex);
    // printf("Queue after dequeue:\n");
    // for (int i = queue->headIndex; i < queue->headIndex + queue->length; i++) {
    //     printf("%d\n", *queue->items[i]);
    // }
    // printf("\n");

    return 1;
}

int cirQueueLength(const CirQueue* queue)
{
    if(!queue) return 0;
    return queue->length;
}
