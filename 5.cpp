#include <iostream>
#include <omp.h>

int main()
{	
	// Определяем массивы
	int size = 1000000000;
	int i, j;
	int* A = new int[size];
	int* B = new int[size];
	int mult;
	
#pragma omp parallel shared(A, B) private(i)
	{
#pragma omp for
		for(i=0; i<size; i++){
			A[i] = 2;
			B[i] = 3;
		}
	}


	double start_time, end_time, tick;

	// В цикле умножаем с помощью 1, ... , 10 потоков
	for(j=1; j<11; j++){
		mult = 0;
		start_time = omp_get_wtime();
#pragma omp parallel private(i) num_threads(j) reduction(+: mult)
		{
		
#pragma omp for
			for(i=0; i<size; i++){
				mult += A[i] * B[i];
			}
		}
		end_time = omp_get_wtime();

		tick = omp_get_wtick();

		printf("\n %d потоков, mult = %d, время: %lf\n", j, mult, end_time-start_time);

	}
	delete [] A, B;
}