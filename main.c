#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "st_pipeline.h"

void print_usage()
{
    printf("Usage: st_pipeline <num_tasks> <seed>\n");
}

pthread_cond_t setupCompleteCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t setupCompleteMutex = PTHREAD_MUTEX_INITIALIZER;

void waitForSetupComplete()
{
    pthread_mutex_lock(&setupCompleteMutex);
    pthread_cond_wait(&setupCompleteCond, &setupCompleteMutex);
    pthread_mutex_unlock(&setupCompleteMutex);
}

void notifySetupComplete()
{
    pthread_mutex_lock(&setupCompleteMutex);
    pthread_cond_signal(&setupCompleteCond);
    pthread_mutex_unlock(&setupCompleteMutex);
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        print_usage();
        return 1;
    }

    int N = atoi(argv[1]);
    int seed = (argc == 3) ? atoi(argv[2]) : INVALID_SEED;

    setup_pipeline(N, seed);
    waitForSetupComplete(); // Wait for setup to complete

    stop_pipeline();

    return 0;
}
