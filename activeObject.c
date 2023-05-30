#include "activeObject.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

void *active_object_thread(void *arg)
{
    ActiveObject *activeObj = (ActiveObject *)arg;
    Queue *queue = activeObj->queue;
    TaskFunction func = activeObj->func;
    void *task;

    while ((task = queue_dequeue(queue)) != NULL)
    {
        func(task);
    }

    pthread_exit(NULL);
}

ActiveObject *CreateActiveObject(Queue *queue, TaskFunction func)
{
    ActiveObject *activeObj = (ActiveObject *)malloc(sizeof(ActiveObject));
    if (activeObj == NULL)
    {
        return NULL;
    }

    activeObj->queue = queue;
    activeObj->func = func;
    activeObj->active = true;

    int result = pthread_create(&activeObj->thread, NULL, active_object_thread, (void *)activeObj);
    if (result != 0)
    {
        free(activeObj);
        return NULL;
    }

    return activeObj;
}

Queue *getQueue(ActiveObject *activeObj)
{
    return activeObj->queue;
}

void StopActiveObject(ActiveObject *activeObj)
{
    activeObj->active = false;
    pthread_join(activeObj->thread, NULL);
    free(activeObj);
}
