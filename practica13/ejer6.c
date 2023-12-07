#include <stdio.h>
#include <omp.h>

#define RA 30
#define CA 50
#define RB 50
#define CB 30

void multiply(int a[RA][CA], int b[RB][CB], int c[RA][CB])
{
    int i, j, k;
    for (i = 0; i < RA; i++)
        for (j = 0; j < CB; j++)
            for (k = 0; k < CA; k++)
                c[i][j] += a[i][k] * b[k][j];
}

void init_a(int a[RA][CA])
{
    for (int i = 0; i < RA; i++)
        for (int j = 0; j < CA; j++)
            a[i][j] = (i + 1) * 10;
}

void init_b(int b[RB][CB])
{
    for (int i = 0; i < RB; i++)
        for (int j = 0; j < CB; j++)
            b[i][j] = (i + 1) * 12;
}

void init_c(int c[RA][CB])
{
    for (int i = 0; i < RA; i++)
        for (int j = 0; j < CB; j++)
            c[i][j] = 0;
}

int main(int argc, char const *argv[])
{
    double ini, fin;
    int a[RA][CA], b[RB][CB], c[RA][CB];

    ini = omp_get_wtime();
    init_a(a);
    init_b(b);
    init_c(c);

    multiply(a, b, c);
    fin = omp_get_wtime();

    printf("a:\n");
    for (int i = 0; i < RA; i++)
    {
        for (int j = 0; j < CA; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nb:\n");
    for (int i = 0; i < RB; i++)
    {
        for (int j = 0; j < CB; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    printf("\na x b = c:\n");
    for (int i = 0; i < RA; i++)
    {
        for (int j = 0; j < CB; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    printf("Time: %f\n", fin - ini);
    
    return 0;
}
