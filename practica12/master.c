#include<stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
    int id;

    #pragma omp parallel
    {
        #pragma omp master
        {
            id = omp_get_thread_num();
            printf("Master block thread %d.\n", id);
        }

        id = omp_get_thread_num();
        printf("Parallel block thread %d.\n", id);
    }

    return 0;
}

