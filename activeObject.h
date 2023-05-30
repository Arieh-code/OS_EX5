#pragma once
#include "queue.h"

typedef void (*TaskFunction)(void *);

typedef struct
{
    Queue *queue;
    pthread_t thread;
    TaskFunction func;
    int active;
} ActiveObject;

ActiveObject *CreateActiveObject(Queue *queue, TaskFunction func);

Queue *getQueue(ActiveObject *activeObj);

void StopActiveObject(ActiveObject *activeObj);