#include <iostream>
#include <omp.h>

int main()
{
	int A[80], i, n, sum;
	sum = 0;
/* Заполним исходный массив */
	for (i=0; i<80; i++)
		{
			A[i]=1;
		}
#pragma omp parallel shared(A) private(i, n) reduction(+: sum)
	{
		/* Получим номер текущей нити */
		n = omp_get_thread_num();
#pragma omp for
		for (i=0; i<80; i++)
		{
			sum += A[i];
			// printf("Нить %d прибавила A[%d] к переменной sum, sum=%d\n",
			// n, i, sum);
		}
	}
	printf("sum = %d\n", sum);

sum = 0;
#pragma omp parallel shared(A) private(i, n)
{
	int local_sum = 0;
	// n = omp_get_thread_num();
#pragma omp for
	for(i=0; i<80; i++)
		{
			local_sum += A[i];
			// printf("Нить %d прибавила %d к local_sum. local_sum == %d\n",
			// n, A[i], local_sum);
		}		
#pragma omp atomic
	sum += local_sum;
	// printf("Нить %d прибавила local_sum==%d к sum. sum == %d\n",
	// 		n, local_sum, sum);
}
printf("sum = %d\n", sum);

sum = 0;
#pragma omp parallel
	{
#pragma omp for
		for(i=0; i<80; i++)
#pragma omp critical
			{
				sum += A[i];
			}
	}
printf("sum == %d\n", sum);
}