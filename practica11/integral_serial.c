#include<stdio.h>
#include <omp.h>

int main()
{
    int num_steps = 1000000;
    int i;
    float x, pi, sum = 0.0;
    float step = 1.0 / (float) num_steps;
    double ini = omp_get_wtime();
    for (i = 0; i < num_steps; i++)
    {
        x = (i+0.5) * step;
        sum = sum + 4.0/(1.0+x*x);
    }

    pi = step * sum;
    printf("Time:%f\n",omp_get_wtime()-ini);
    printf("PI = %f\n", pi);
    
}