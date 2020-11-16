#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>

// FILE #3 TO SUBMIT

struct CirQueue
{
    int capacity;
    int* items;
    int headIndex;
    int length;
};

/**
 * Creates a CirQueue given some capacity.
 * 
 * @param capacity Capacity to give the CirQueue instance
 * @return Reference to the CirQueue instance
 */
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

/**
 * Deallocates all space associated with queue.
 * 
 * @param queue The reference to the CirQueue instance we want to deallocate 
 * space of
 * @return 0 if queue is NULL; 1 otherwise
 */
int cirQueueDestroy(CirQueue* queue)
{
    if (!queue) return 0;
    free(queue->items);
    free(queue);
    return 1;
}

/**
 * Inserts val into queue into the rightmost available slot. If the rightmost 
 * available slot is past the end of the array, the function wraps around the queue 
 * to the beginning. If the queue is full (no more available slots), then enqueue 
 * fails.
 * 
 * @param queue Reference to the CirQueue instance
 * @param val Value to insert into the queue
 * @return 0 if enqueue fails; 1 otherwise
 */
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

/**
 * Deletes the earliest item that was inserted into the queue. Utilizes lazy deletion 
 * where the item is not actually erased.
 * 
 * @param queue Reference to the CirQueue instance
 * @param val References the variable to store the deleted item in
 * @return 0 if queue is NULL or empty; 1 if success in deletion
 */
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

/**
 * Returns the length of queue (i.e. the number of items in queue).
 * 
 * @param queue Reference to the CirQueue instance
 * @return 0 if queue is NULL; otherwise, length of queue
 */
int cirQueueLength(const CirQueue* queue)
{
    if(!queue) return 0;
    return queue->length;
}
