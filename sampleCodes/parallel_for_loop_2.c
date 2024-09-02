
//Here we try to estimate pi. The following code is the ordinary for loop: 

/* #include<stdio.h>

int main()
{
    static long num_steps = 1000000;
    double step;
    int i; double x,pi,sum=0.0;
    step = 1.0/(double)num_steps;

    for(i=0; i < num_steps; i++)
    {
        x = ((double)(i+0.5))*step;
        sum += 4.0/(1.0 + x*x);
    }

    pi = step*sum;
    printf("%.24f", pi);
    return 0;
} */


#include<stdio.h>
#include<omp.h>

#define NUM_OF_THREADS 8

int main()
{
    static long num_steps = 10000000;
    double step;
    int i; double x,pi,sum=0.0;
    step = 1.0/(double)num_steps;
    double thread_sum[NUM_OF_THREADS];

    omp_set_num_threads(NUM_OF_THREADS);

    #pragma omp parallel
    {
        
        int ID = omp_get_thread_num();

        #pragma omp for
            
        for (i=0; i < num_steps; i++)
        {
            x = ((double)(i+0.5))*step;
            thread_sum[ID] += 4.0/(1.0 + x*x);
        }
    }

    for(i=0; i < NUM_OF_THREADS; i++)
    {
        x = ((double)(i+0.5))*step;
        sum += thread_sum[i];
    }

    pi = step*sum;
    printf("%.24f\n", pi);
    return 0;
}