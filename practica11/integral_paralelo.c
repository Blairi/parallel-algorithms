#include<stdio.h>
#include <omp.h>
#define NUM_STEPS 1000000

int main(){

    int threads = omp_get_max_threads();
    omp_set_num_threads(threads);
    
    double sumas[threads];
    double suma = 0;

    double ini, fin;

    ini = omp_get_wtime();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        double diferencial = 1.0 / (float) NUM_STEPS;

        double step = (double)threads*diferencial;

        double x = (double)id*diferencial;

        double sub_sum = 0;

        while( x <= 1.0 ){

            double fx = 4.0/( 1 + (x * x ) );
            double area = diferencial * fx;
            sub_sum += area;
            x += step;
        }

        sumas[id] = sub_sum;
    }

    for (int i = 0; i < threads; i++)
    {
        suma += sumas[i];
    }
    fin = omp_get_wtime();

    printf("Time: %f\n", fin - ini);
    printf("Pi: %f\n",suma);
    return 0;
}
