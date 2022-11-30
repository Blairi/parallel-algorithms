#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int big_call1(int id);
int big_call2(int id);

int main()
{
    
    omp_set_num_threads( NUM_THREADS );

    int A[NUM_THREADS], B[NUM_THREADS], id;

    #pragma omp parallel
    {
        id = omp_get_thread_num();

        A[id] = big_call1( id );

        #pragma omp barrier
        B[id] = big_call2( id );
    }

    return 0;
}

int big_call1(int id)
{
    long long suma = 0;

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int k = 0; k < 1000; k++)
            {
                suma += i + j + k * id;
            }
        }
    }

    printf("big_call1 : Thread [%d] calculo: %lld\n", id, suma % 97);

    return (int)suma % 97;
}

int big_call2(int id)
{
    int suma = 0;

    for (int i = 0; i < 9999; i++)
    {
        suma += i;
        for (int j = 0; j < 9999; j++)
        {
            suma += j;
        }
    }

    printf("big_call2 : Thread [%d] calculo: %d\n", id, suma);

    return suma;
    
}