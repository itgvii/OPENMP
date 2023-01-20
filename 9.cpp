#include <iostream>
#include <mpi.h>

using namespace std;

int main (int argc, char *argv[])
{
	int rank, size;

	MPI_Init (&argc, &argv); /* запуск MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* получить идентификатор текущего процесса */
	MPI_Comm_size (MPI_COMM_WORLD, &size); /* получить число процессов */
	
	cout << "Hello world! from process" << rank << "\n";
	
	MPI_Finalize(); /* завершение MPI */
	return 0;
}