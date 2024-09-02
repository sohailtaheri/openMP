#include<stdio.h>
#include<omp.h> //openMP library

// To complie the code, run the following command in terminal:
// gcc -fopenmp .\helloworld.c
// then run ./a.exe

void main()
{
    int id;

    // Set the number of threads
    omp_set_num_threads(8);

    // Create parallel region 
    #pragma omp parallel
    {
        id = omp_get_thread_num();
        printf("Thread ID %d: Hello world!\n", id);
    }

    return;
}