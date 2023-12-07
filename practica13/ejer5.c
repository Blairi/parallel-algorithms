#include <stdio.h>
#include <omp.h>

int counter = 0;
#pragma omp threadprivate(counter)

int increment_counter(int id_thread)
{
    return ++counter + id_thread;
}

int main()
{
    #pragma omp parallel
    {
        int sum = 0;
        int id = omp_get_thread_num();

        sum = increment_counter( id );

        printf("Thread %d => %d + %d = %d\n", id, counter, id, sum);
    }

    printf("Final counter: %d\n", counter);

    return 0;
}
