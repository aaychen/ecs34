#include "circular_queue.h"

#include <stdio.h>

#include <assert.h>

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
    printf("Enqueue failure retval: %d\n", cirQueueEnqueue(queue, 93));
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

    // OWN TESTS
    val = 0;
    // Test functions with null pointers
    assert(cirQueueEnqueue(NULL, 12) == 0);
    assert(cirQueueDequeue(NULL, &val) == 0);
    assert(val == 0);
    assert(cirQueueLength(NULL) == 0);
    assert(cirQueueDestroy(NULL) == 0);

    // Test queue with capacity 0
    queue = cirQueueCreate(0);
    assert(queue == NULL);
    assert(cirQueueLength(queue) == 0);
    assert(cirQueueEnqueue(queue, 93) == 0);
    assert(cirQueueLength(queue) == 0);
    assert(cirQueueDequeue(queue, &val) == 0);
    assert(cirQueueLength(queue) == 0);
    assert(val == 0);
    assert(cirQueueDestroy(queue) == 0);

    // Test queue with capacity 1
    val = 0;
    queue = cirQueueCreate(1);
    assert(queue != NULL);
    assert(cirQueueLength(queue) == 0);
    assert(cirQueueEnqueue(queue, 93) == 1);
    assert(cirQueueLength(queue) == 1);
    assert(cirQueueEnqueue(queue, 3) == 0);
    assert(cirQueueLength(queue) == 1);
    assert(cirQueueEnqueue(queue, 145) == 0);
    assert(cirQueueLength(queue) == 1);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 0);
    assert(val == 93);
    assert(cirQueueDequeue(queue, &val) == 0);
    assert(cirQueueLength(queue) == 0);
    assert(val == 93);
    assert(cirQueueDequeue(queue, &val) == 0);
    assert(cirQueueLength(queue) == 0);
    assert(val == 93);
    assert(cirQueueDestroy(queue) == 1);

    val = 0;
    queue = cirQueueCreate(5);
    assert(queue != NULL);
    assert(cirQueueLength(queue) == 0);
    assert(cirQueueEnqueue(queue, 2) == 1);
    assert(cirQueueEnqueue(queue, 4) == 1);
    assert(cirQueueEnqueue(queue, 12) == 1);
    assert(cirQueueEnqueue(queue, 59) == 1);
    assert(cirQueueEnqueue(queue, 15) == 1);
    assert(cirQueueLength(queue) == 5);
    assert(cirQueueEnqueue(queue, 10) == 0);
    assert(cirQueueLength(queue) == 5);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 4);
    assert(val == 2);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 3);
    assert(val == 4);
    assert(cirQueueEnqueue(queue, 176) == 1);
    assert(cirQueueLength(queue) == 4);
    assert(cirQueueEnqueue(queue, 123) == 1);
    assert(cirQueueLength(queue) == 5);
    assert(cirQueueEnqueue(queue, 2041) == 0);
    assert(cirQueueLength(queue) == 5);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 4);
    assert(val == 12);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 3);
    assert(val == 59);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 2);
    assert(val == 15);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 1);
    assert(val == 176);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 0);
    assert(val == 123);
    assert(cirQueueEnqueue(queue, 34) == 1);
    assert(cirQueueLength(queue) == 1);
    assert(cirQueueDequeue(queue, &val) == 1);
    assert(cirQueueLength(queue) == 0);
    assert(val == 34);
    assert(cirQueueDestroy(queue) == 1);
}
