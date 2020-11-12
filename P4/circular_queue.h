#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct CirQueue CirQueue;

CirQueue* cirQueueCreate(int capacity);

int cirQueueDestroy(CirQueue* queue);

int cirQueueEnqueue(CirQueue* queue, int val);

int cirQueueDequeue(CirQueue* queue, int* val);

int cirQueueLength(const CirQueue* queue);

#endif // CIRCULAR_QUEUE_H
