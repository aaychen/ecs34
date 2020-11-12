#include "circular_queue.h"

#include <stdio.h>

int main()
{
    CirQueue* queue = cirQueueCreate(4);
    int val = 0;
    printf("1. Length: %d\n", cirQueueLength(queue));
    cirQueueEnqueue(queue, 19);
    cirQueueEnqueue(queue, 37);
    cirQueueEnqueue(queue, 56);
    printf("2. Length: %d\n", cirQueueLength(queue));
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    printf("3. Length: %d\n", cirQueueLength(queue));
    cirQueueEnqueue(queue, 42);
    cirQueueEnqueue(queue, 14);
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    cirQueueEnqueue(queue, 27);
    cirQueueEnqueue(queue, 58);
    printf("Enqueue failure retval: %d\n",
        cirQueueEnqueue(queue, 93));
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    cirQueueDequeue(queue, &val);
    printf("Dequeue: %d\n", val);
    printf("4. Length: %d\n", cirQueueLength(queue));
    cirQueueDestroy(queue);
}
