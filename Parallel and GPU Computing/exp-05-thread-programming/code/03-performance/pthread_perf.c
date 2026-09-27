#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define N 1000000000L
#define MAX_THREADS 32

double partial_sum[MAX_THREADS];

typedef struct
{
    int thread_id;
    int num_threads;
} ThreadData;

void* compute_sum(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    int thread_id = data->thread_id;
    int num_threads = data->num_threads;

    long start = thread_id * (N / num_threads);
    long end = (thread_id == num_threads - 1)
               ? N
               : start + (N / num_threads);

    partial_sum[thread_id] = 0.0;

    for (long i = start; i < end; i++)
    {
        partial_sum[thread_id] += (double)i * 0.000001;
    }

    return NULL;
}

int main()
{
    int num_threads;

    printf("Enter number of threads (1-32): ");
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > MAX_THREADS)
    {
        printf("Invalid number of threads.\n");
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].num_threads = num_threads;

        pthread_create(
            &threads[i],
            NULL,
            compute_sum,
            &thread_data[i]
        );
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    double total_sum = 0.0;

    for (int i = 0; i < num_threads; i++)
    {
        total_sum += partial_sum[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double time_taken =
        (end_time.tv_sec - start_time.tv_sec) +
        (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Pthreads Sum = %.2f\n", total_sum);
    printf("Number of Threads = %d\n", num_threads);
    printf("Execution Time = %.6f seconds\n", time_taken);

    return 0;
}
