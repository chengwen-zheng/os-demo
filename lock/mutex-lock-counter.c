#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t counter_lock;
int counter = 0;

void *increment_counter(void *arg)
{
    int num_increments = *(int *)arg;
    for (int i = 0; i < num_increments; i++)
    {
        pthread_mutex_lock(&counter_lock);
        counter++;
        pthread_mutex_unlock(&counter_lock);
    }
    return NULL;
}

int main()
{
    int num_threads = 10;
    int num_increments_per_thread = 1000000;

    pthread_t threads[num_threads];
    int increments[num_threads];

    pthread_mutex_init(&counter_lock, NULL);

    for (int i = 0; i < num_threads; i++)
    {
        increments[i] = num_increments_per_thread;
        pthread_create(&threads[i], NULL, increment_counter, &increments[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter_lock);

    printf("Counter value = %d\n", counter);

    return 0;
}