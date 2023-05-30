#include "st_pipeline.h"
#include "is_prime.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

ActiveObject *ao1;
ActiveObject *ao2;
ActiveObject *ao3;
ActiveObject *ao4;

void task_1(void *arg)
{
    Task *task = (Task *)arg;
    int seed = task->seed;
    srand(seed);

    for (int i = 0; i < task->task_count; i++)
    {
        int number = rand() % 900000 + 100000;
        task->number = number;
        queue_enqueue(getQueue(ao2), task);
        sleep(1);
    }

    free(task);
}

void task_2(void *arg)
{
    Task *task = (Task *)arg;
    int number = task->number;
    printf("%d\n", number);
    task->is_prime = isPrime(number);
    printf("%s\n", task->is_prime ? "true" : "false");
    number += 11;
    task->number = number;
    queue_enqueue(getQueue(ao3), task);
}

void task_3(void *arg)
{
    Task *task = (Task *)arg;
    int number = task->number;
    printf("%d\n", number);
    task->is_prime = isPrime(number);
    printf("%s\n", task->is_prime ? "true" : "false");
    number -= 13;
    task->number = number;
    queue_enqueue(getQueue(ao4), task);
}

void task_4(void *arg)
{
    Task *task = (Task *)arg;
    int number = task->number;
    printf("%d\n", number);
    number += 2;
    printf("%d\n", number);
    if (number == task->seed)
        stop_pipeline();
    free(task);
}

void setup_pipeline(int num_tasks, int seed)
{
    Queue *queue1 = (Queue *)malloc(sizeof(Queue));
    queue_init(queue1, num_tasks);

    Queue *queue2 = (Queue *)malloc(sizeof(Queue));
    queue_init(queue2, num_tasks);

    Queue *queue3 = (Queue *)malloc(sizeof(Queue));
    queue_init(queue3, num_tasks);

    Queue *queue4 = (Queue *)malloc(sizeof(Queue));
    queue_init(queue4, num_tasks);

    ao1 = CreateActiveObject(queue1, task_1);
    ao2 = CreateActiveObject(queue2, task_2);
    ao3 = CreateActiveObject(queue3, task_3);
    ao4 = CreateActiveObject(queue4, task_4);

    Task *task = (Task *)malloc(sizeof(Task));
    task->seed = seed;
    task->task_count = num_tasks;
    queue_enqueue(getQueue(ao1), task);
}

void stop_pipeline()
{
    StopActiveObject(ao1);
    StopActiveObject(ao2);
    StopActiveObject(ao3);
    StopActiveObject(ao4);
}
