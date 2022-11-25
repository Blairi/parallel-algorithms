#include<stdio.h>
#include <omp.h>

#define TAM 1000000

int main()
{

    double inicial, final;
    inicial = omp_get_wtime();

    printf("Num procs: %d\n", omp_get_num_procs());

    long long suma = 0;

    int vector[TAM];
    for (int i = 0; i < TAM; i++) // Inicializando vectores
    {
        vector[i] = i + 1;
    }

    int threads = omp_get_max_threads();
    printf("Max threads: %d\n", threads);

    long long sumas[ threads ];
    for (int i = 0; i < threads; i++) // Inicializando vectores
    {
        sumas[i] = 0;
    }

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        
        int rango_inicio = TAM / threads * id;
        int rango_final = (TAM / threads) * id + (TAM / threads) - 1;

        for (int i = rango_inicio; i <= rango_final; i++)
        {
            sumas[id] += vector[i];
        }

        printf("Thread %d sumara de [%d, %d] = %lld\n", id, rango_inicio, rango_final, sumas[id] );
    }

    for (int i = 0; i < threads; i++) // Sumando todos los calculos
    {
        suma += sumas[i];
    }

    for (int i = TAM - TAM % threads; i < TAM; i++) // Sumando el residuo
    {
        suma += vector[i];
    }

    final = omp_get_wtime();

    printf("Suma total: %lld\nTime: %f\n", suma, final - inicial);

}