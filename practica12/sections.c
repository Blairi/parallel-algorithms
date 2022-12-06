#include<stdio.h>
#include <omp.h>

void section_a(int thread);
void section_b(int thread);
void section_c(int thread);

int main(int argc, char const *argv[])
{
    int id;

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            section_a( omp_get_thread_num() );
            #pragma omp section
            section_b( omp_get_thread_num() );
            #pragma omp section
            section_c( omp_get_thread_num() );
            
        }

        id = omp_get_thread_num();
        printf("Parallel block thread %d. \n", id);
    }

    return 0;
}


void section_a(int thread)
{
    int sum = 0;

    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            sum += i + j;
        }
        
    }
    
    printf("Section a: %d\n", thread);
}


void section_b(int thread)
{
    int sum = 0;

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            sum += i + j;
        }
        
    }
    printf("Section b: %d\n", thread);
}


void section_c(int thread)
{
    printf("Section c: %d\n", thread);
}


