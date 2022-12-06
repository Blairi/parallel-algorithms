#include <stdio.h>
#include <omp.h>

void fill_rand();
int sum_array();

#define TAM 100
int array[TAM];

int main(int argc, char const *argv[])
{

    int tmp_flag, flag, sum;

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            fill_rand();
            #pragma omp flush // flush the array
            #pragma omp atomic write
            flag = 1;
            #pragma omp flush(flag)
        }

        #pragma omp section
        {
            while (1)
            {
                #pragma omp flush(flag)
                #pragma omp atomic read
                tmp_flag = flag;
                if (tmp_flag == 1)
                break;
            }
            #pragma omp flush
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

