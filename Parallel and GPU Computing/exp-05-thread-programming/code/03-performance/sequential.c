#include <stdio.h>
#include <time.h>

#define N 1000000000L

int main()
{
    double sum = 0.0;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long i = 0; i < N; i++)
    {
        sum += (double)i * 0.000001;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Sequential Sum = %.2f\n", sum);
    printf("Execution Time = %.6f seconds\n", time_taken);

    return 0;
}
