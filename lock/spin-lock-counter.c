#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct __lock_t
{
    int flag;
} lock_t;

void init(lock_t *lock)
{
    lock->flag = 0;
}

void lock(lock_t *lock)
{
    while (__sync_lock_test_and_set(&lock->flag, 1) == 1)
    {
        // spin-wait (do nothing)
    }
}

void unlock(lock_t *lock)
{
    __sync_lock_release(&lock->flag);
}

lock_t counter_lock;
int counter = 0;

void increment_counter(int num_increments)
{
    for (int i = 0; i < num_increments; i++)
    {
        lock(&counter_lock);
        counter++;
        unlock(&counter_lock);
    }
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
        pthread_create(&threads[i], NULL, (void *(*)(void *))increment_counter, &increments[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Counter value = %d\n", counter);

    return 0;
}