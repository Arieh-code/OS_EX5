#pragma once

#include <stdbool.h>
#include "queue.h"
#include "activeObject.h"

#define INVALID_SEED (-1)
typedef struct
{
    int number;
    bool is_prime;
    int seed;
    int task_count;
} Task;

void task_1(void *arg);

void task_2(void *arg);

void task_3(void *arg);

void task_4(void *arg);

void setup_pipeline(int num_tasks, int seed);

void stop_pipeline();
