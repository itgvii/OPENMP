#include <iostream>
#include <omp.h>

int main()
{
    using namespace std;
    int count, num;

    printf("Последовательная область 1\n");

    count = omp_get_num_threads();
    num = omp_get_thread_num();
    if (num == 0) printf("Всего нитей: %d\n", count);
    else printf("Нить номер %d\n", num);

    omp_set_num_threads(1);
#pragma omp parallel num_threads(32744)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0) printf("Параллельная область 1. Всего нитей: %d\n", count);
        else printf("Параллельная область 1. Нить номер %d\n", num);
    }
#pragma omp parallel
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0) printf("Параллельная область 2. Всего нитей: %d\n", count);
        else printf("Параллельная область 2. Нить номер %d\n", num);
    }
    
    printf("Последовательная область 2\n");

    count = omp_get_num_threads();
    num = omp_get_thread_num();
    if (num == 0) printf("Всего нитей: %d\n", count);
    else printf("Нить номер %d\n", num);



    return 0;
}
