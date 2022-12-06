#include <stdio.h>
#include <omp.h>

void fill_rand();
int sum_array();

#define TAM 100
int array[TAM];

int main(int argc, char const *argv[])
{

    int flag, sum;

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            fill_rand();
            #pragma omp flush // flush the array
            flag = 1;
            #pragma omp flush(flag)
        }

        #pragma omp section
        {
            #pragma omp flush(flag)
            while (flag == 0) {
                // For the compiler not to copy the flag value on the registrer
                #pragma omp flush(flag)
            }
            #pragma omp flush // flush the array
            sum = sum_array();
        }
    }
    printf("Sum: %d\n", sum);
    return 0;
}

void fill_rand()
{
    for (int i = 0; i < TAM; i++)
    {
        array[i] = i + 1;
    }
}


int sum_array()
{
    int sum = 0;
    for (int i = 0; i < TAM; i++)
    {
        sum += array[i];
    }
    return sum;
}

