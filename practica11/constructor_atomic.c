#include <stdio.h>
#include <omp.h>

double getNumber();
double funcBig(double B);

int main(int argc, char const *argv[])
{
    double A = 0;
    float res;
    #pragma omp parallel
    {
        double tmp, B;
        B = getNumber();
        tmp = funcBig(B);
        #pragma omp atomic
        A += tmp;
    }
    printf("A : %f\n", A);
    return 0;
}

double getNumber()
{
    return omp_get_wtime();
}

double funcBig(double B)
{
    double sum = 0.0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            sum += j + B;
        }
    }

    return sum;
    
}