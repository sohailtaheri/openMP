/*
Here is the format of an ordinary for loop: 

for (i = 1; i <= 100; i++)
{
    sum += i;
}

*/

#include<stdio.h>
#include<omp.h>

#define NUM_OF_THREADS 4

void main()
{
    
    int i,sum = 0;
    int thread_sum[NUM_OF_THREADS];

    omp_set_num_threads(NUM_OF_THREADS);

    #pragma omp parallel
    {
        // declaration inside the parallel region makes the variable private to that thread
        int ID = omp_get_thread_num();
        thread_sum[ID] = 0;

        #pragma omp for

        // for loop index in the parallel region is private by default. 
        // It is not shared between the threads.
        // It is better to declare for loop index variable inside the parallel region, 
        // however we declared it above to use in the second for loop as well.
        for(i = 1; i <= 100; i++)
        {
            thread_sum[ID] += i; 
        }
    }

    for (i=0; i<4; i++)
        sum += thread_sum[i];

    printf("Sum = %d", sum);    
}