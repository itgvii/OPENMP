#include <iostream>
#include <omp.h>

int main() {
    int j, i, n = 1000000;
    long double pi;
    double start_time, finish_time;

    for (j=1; j<11; j++){
        pi = 0;
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(j) private(i) reduction(+: pi)
        {
            #pragma omp for
            for(i=0; i<n; i++){
                pi += 4 / (1 + ((i + 0.5)/n)*((i + 0.5)/n));
            }
        }
        pi /= n;

        finish_time = omp_get_wtime();

        std::cout << j << " потоков, время = " << finish_time - start_time << ", pi = " << pi << '\n';
    }
}