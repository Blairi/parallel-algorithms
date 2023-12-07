#include <stdio.h>
#include <omp.h>

#define TAM 1000

int work1(int id);
int work2(int i, int A[]);
int work3(int C[], int i);
int work4(int id);

int main(int argc, char const *argv[])
{

    int num_threads = omp_get_max_threads();

    int id;
    int i;
    int A[num_threads], B[TAM], C[TAM];

    #pragma omp parallel shared(A, B, C) private(id)
    {
        id = omp_get_thread_num();
        A[id] = work1(id);
        printf("Thread %d finish work1\n", id);

        #pragma omp barrier

        #pragma omp for
        for (i = 0; i < TAM; i++)
        {
            C[i] = work2(i, A);
        }
        printf("Thread %d finish work2\n", id);

        #pragma omp for nowait
        for (i = 0; i < TAM; i++)
        {
            B[i] = work3(C, i);
        }
        printf("Thread %d finish work3\n", id);

        A[id] = work4(id);
        printf("Thread %d finish work4\n", id);
    }

    return 0;
}


int work1(int id)
{
    int sum = 0;
    for (int i = 0; i < id * 10; i++)
    {
        for (int j = 0; j < id * 10; j++)
        {
            sum += j + i;
        }
        
    }
    return sum;
}


int work2(int i, int A[])
{
    int sum = 0;
    for (int j = 0; j < i * 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            sum += k;
        }
        
    }
    return sum;
}


int work3(int C[], int i)
{
    int sum = 0;
    for (int j = 0; j < i * 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            sum += k;
        }
        
    }
    return sum;
}


int work4(int id)
{
    return id;
}


