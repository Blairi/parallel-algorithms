#include <stdio.h>
#include <omp.h>

float big_job(float i);
float consume(float B);

int main(int argc, char const *argv[])
{
    int niters = 10;
    float res = 0;

    #pragma omp parallel
    {
        float B;
        int i, id, nthreads;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        for ( i = id; i < niters; i++)
        {
            B = big_job( i );
            // mutual exclusion
            #pragma omp critical
            res += consume(B);
        }

        printf("res = %f\n", res);
        
    }

    return 0;
}

float big_job(float i)
{
    float suma = 0.0;
    for (int j = 0; j < 1000; j++)
    {
        suma += j;
    }

    suma *= i;

    return suma;

}

float consume(float B)
{
    return (float)1000 * B;
}