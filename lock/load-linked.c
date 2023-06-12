#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct __lock_t
{
    int flag;
} lock_t;

void lock(lock_t *lock)
{
    while (true)
    {
        while (lock->flag == 1)
        {
            // spin wait
        }

        int oldval = __sync_val_compare_and_swap(&lock->flag, 0, 1);
        if (oldval == 0)
        {
            return;
        }
    }
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}

lock_t counter_lock;
int counter = 0;

void *increment_counter(void *arg)
{
    int num_increments = *(int *)arg;
    for (int i = 0; i < num_increments; i++)
    {
        lock(&counter_lock);
        counter++;
        unlock(&counter_lock);
    }
    return NULL;
}

int main()
{
    int num_threads = 10;
    int num_increments_per_thread = 1000000;

    pthread_t threads[num_threads];
    int increments[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        increments[i] = num_increments_per_thread;
        pthread_create(&threads[i], NULL, increment_counter, &increments[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Counter value = %d\n", counter);

    return 0;
}