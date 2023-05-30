#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "st_pipeline.h"

void print_usage()
{
    printf("Usage: st_pipeline <num_tasks> <seed>\n");
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

    stop_pipeline();

    return 0;
}