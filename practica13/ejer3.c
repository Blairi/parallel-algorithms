#include <stdio.h>
#include <omp.h>

void func()
{
    int tmp = 99;
    #pragma omp parallel firstprivate(tmp)
    {
        printf("Thread %d => tmp: %d\n", omp_get_thread_num(), tmp);
        #pragma omp for
        for (int j = 0; j < 1000; ++j)
        {
            tmp += j;
        }
        printf("Thread %d => new tmp: %d\n", omp_get_thread_num(), tmp);
    }
    printf("tmp: %d\n", tmp);
}

int main(int argc, char const *argv[])
{
    func();
    return 0;
}
