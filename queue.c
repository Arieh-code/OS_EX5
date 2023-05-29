#include <stdio.h>
#include <pthread.h>
#include "queue.h"

void queue_init(Queue* queue, int size)
{
    // Allocate memory for the buffer
    queue->buffer = malloc(size * sizeof(void*));

    // Set the size, head, tail, and count of the queue
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;

    // Initialize the mutex and condition variable
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
}

void queue_enqueue(Queue* queue, void* element)
{
    pthread_mutex_lock(&queue->mutex);

    // Wait while the queue is full
    while (queue->count == queue->size)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    // Enqueue the element into the buffer
    queue->buffer[queue->tail] = element;
    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;

    // Signal waiting threads that the queue is not empty
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

void* queue_dequeue(Queue* queue)
{
    pthread_mutex_lock(&queue->mutex);

    // Wait while the queue is empty
    while (queue->count == 0)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    // Dequeue the element from the buffer
    void* element = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->count--;

    // Signal waiting threads that the queue is not full
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);

    return element;
}

void queue_destroy(Queue* queue)
{
    // Free the memory allocated for the buffer
    free(queue->buffer);

    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cond);
}
