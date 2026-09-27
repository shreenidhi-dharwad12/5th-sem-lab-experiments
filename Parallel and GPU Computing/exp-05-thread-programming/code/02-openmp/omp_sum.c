#include <stdio.h>
#include <omp.h>

int main()
{
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int size = 8;
    int total_sum = 0;

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < size; i++)
    {
        total_sum += array[i];
    }

    printf("Total sum = %d\n", total_sum);

    return 0;
}
