#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>

// FILE #3 TO SUBMIT

struct CirQueue
{
    int capacity;
    int* items;
    int headIndex;
    int numItems;
};

// DELETE FUNCTION WHEN SUBMITTING
// For testing purposes
int printCirQueue(const CirQueue* queue) {
    if (!queue) {
        printf("\tQueue is NULL.\n");
        return 0;
    }
    printf("\n\theadIndex: %d\n", queue->headIndex);
    printf("\tnumItems: %d\n", queue->numItems);
    printf("\tQueue:\n");
    for (int i = queue->headIndex; i < queue->headIndex + queue->numItems; i++) {
        if (i >= queue->capacity) {
            int tempIndex = i - queue->capacity;
            printf("\t%d\n", queue->items[tempIndex]);
        } else {
            printf("\t%d\n", queue->items[i]);
        }
    }
    printf("\n");
    return 1;
}

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
    queue->headIndex = 0;
    queue->numItems = 0;
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
 * to the beginning. To find the wrap index, no modding is needed because the max 
 * index that exceeds capacity size is (capacity - 1 + capacity) = 2 * capacity - 1. 
 * If the queue is full (numItems == capacity), then enqueue fails.
 * 
 * @param queue Reference to the CirQueue instance
 * @param val Value to insert into the queue
 * @return 0 if enqueue fails; 1 otherwise
 */
int cirQueueEnqueue(CirQueue* queue, int val)
{
    if (!queue || queue->numItems == queue->capacity) return 0;
    if(!queue->numItems) {
        queue->items[queue->headIndex] = val;
    } else {
        int tempIndex = queue->headIndex + queue->numItems;
        if (tempIndex < queue->capacity) {
            queue->items[tempIndex] = val;
        } else {
            int wrapIndex = tempIndex - queue->capacity;
            queue->items[wrapIndex] = val;
        }
    }
    queue->numItems++;
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
    if (!queue || !queue->numItems) return 0;
    *val = queue->items[queue->headIndex];
    queue->headIndex++;
    if (queue->headIndex == queue->capacity)
        queue->headIndex = 0;
    queue->numItems--;
    return 1;
}

/**
 * Returns the number of items in the queue.
 * 
 * @param queue Reference to the CirQueue instance
 * @return 0 if queue is NULL; otherwise, number of items
 */
int cirQueueLength(const CirQueue* queue)
{
    if(!queue) return 0;
    return queue->numItems;
}