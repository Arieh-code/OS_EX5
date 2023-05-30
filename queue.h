#pragma once
// #include <bits/pthreadtypes.h>
#include <pthread.h>

typedef struct
{
    void **buffer;
    int size;
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

void queue_init(Queue *queue, int size);

void queue_enqueue(Queue *queue, void *element);

void *queue_dequeue(Queue *queue);

void queue_destroy(Queue *queue);