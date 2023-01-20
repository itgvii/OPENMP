#include <iostream>
#include <omp.h>
#include <ctime>

int main(){
    int i, j, k;
    const int size = 800;
    std::srand(time(0));

    //Объявление и заполнение массивов
    int** A = new int*[size];
    int** B = new int*[size];
    int** C = new int*[size];
    #pragma omp parallel private(i) shared(A, B, C, size) default(none)
    {
        #pragma omp for
        for(i=0; i<size; i++){
            A[i] = new int[size];
            B[i] = new int[size];
            C[i] = new int[size];
        }
    }
    #pragma omp parallel private(i, j) shared(A, B, C, size) default(none)
    {
        #pragma omp for
        for(i=0; i<size; i++){
            for(j=0; j<size; j++){
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
                C[i][j] = 0;
            }
        } 
    }

    //Вывод матриц A и B
    // std::cout << "\nA = \n";
    // for(i=0; i<size; i++){
    //     std::cout << '[';
    //     for(j=0; j<size; j++){
    //         std::cout << A[i][j] << ", ";
    //     }
    //     std::cout << "],\n";
    // }
    // std::cout << "\nB = \n";
    // for(i=0; i<size; i++){
    //     std::cout << '[';
    //     for(j=0; j<size; j++){
    //         std::cout << B[i][j] << ", ";
    //     }
    //     std::cout << "],\n";
    // }
    // std::cout << '\n';

    const int count = 80;

    double num_time[count]; // на n-том месте время, за которое считают n+1 потоков
    double start_time, finish_time;
    //Умножение в цикле с помощью 1, ... , 10 потоков
    for(int n=1; n<count+1; n++){

        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(n) private(i) shared(A, B, C, size) default(none)
        {
            #pragma omp for
            for(i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    for(int k=0; k<size; k++){
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        finish_time = omp_get_wtime();
        
        printf("%d потоков, время: %lf\n", n, finish_time - start_time);
        num_time[n-1] = finish_time-start_time;
    }

    printf("Зависимость t1/t_n:\n");
    for(int n=0; n<count; n++){
        printf("%d - %lf\n", n+1, num_time[0] / num_time[n]);
    }

    //Вывод результата
    
    // std::cout << "\n A x B = \n";
    // for(i=0; i<size; i++){
    //     std::cout << '[';
    //     for(j=0; j<size; j++){
    //         std::cout << C[i][j] << ", ";
    //     }
    //     std::cout << "],\n";
    // }

    delete[] A;
}