#include "activeObject.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void *active_object_thread(void *arg)
{
    ActiveObject *activeObj = (ActiveObject *)arg;
    Queue *queue = activeObj->queue;
    TaskFunction func = activeObj->func;
    void *task;

    while (activeObj->active)
    {
        task = queue_dequeue(queue);
        if (task != NULL)
        {
            func(task);
        }
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
    printf("Stopping active object...\n");
    activeObj->active = false;
    queue_enqueue(activeObj->queue, NULL); // Enqueue a NULL task to wake up the thread
    pthread_join(activeObj->thread, NULL);
    free(activeObj);
    printf("Active object stopped.\n");
}
