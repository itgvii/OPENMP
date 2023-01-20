#include <iostream>
#include <omp.h>

int main() {
    // Заполняем массив
    const int size = 2000000;
    int* arr = new int[size];
    int i, j, n;

#pragma omp parallel shared(arr, size) private(i) default(none)
    {
#pragma omp for
        for(i=0; i<size; i++)
        {
            arr[i] = 2;
        }
    }
    arr[3] = 5;

    // Поиск максимума в цикле с помощью 1, ... , 10 потоков
    double start_time, end_time;

    int max_element = arr[0];

    for(j=1; j<11; j++){
        start_time = omp_get_wtime();
#pragma omp parallel shared(arr) private(i, n) num_threads(j) reduction(max: max_element) default(none)
        {
#pragma omp for
            for (i=0; i<size; i++) {
                if (max_element < arr[i]) {
                    max_element = arr[i];
                }
            }
        }
        end_time = omp_get_wtime();
        printf("%d потоков, время: %lf, max_element == %d\n", j, end_time - start_time, max_element);
        }
}
