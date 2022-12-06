#include<stdio.h>
#include <omp.h>
#define NUM_STEPS 1000000

int main(){

    int threads = omp_get_max_threads();
    omp_set_num_threads(threads);
    
    double suma = 0;
    double ini, fin;

    ini = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        double diferencial = 1.0 / (float) NUM_STEPS; // 0.000001

        double step = (double)threads*diferencial; // 0.000012

        double x = (double)id*diferencial; // 0.0000{id}

        double sub_sum = 0;

        for (x; x <= 1.0; x += step)
        {
            double fx = 4.0/( 1 + (x * x ) );
            double area = diferencial * fx;
            sub_sum += area;
        }

        #pragma omp critical
        {
            suma += sub_sum;
        }

    }

    fin = omp_get_wtime();

    printf("Time: %f\n", fin - ini);
    printf("Pi: %f\n",suma);
    return 0;
}
