#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16

int main () {

    int i,nthreads;
    double pi=0.0,sum[NUM_THREADS],start_time,time_taken;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int i,id,nt;
        double x;

        id = omp_get_thread_num();
        nt = omp_get_num_threads();

        if(id==0) 
            nthreads = nt;

        for(i=id,sum[id] = 0.0;i<num_steps;i+=nt){
            x = (i+0.5)*step;
            sum[id] += 4.0/(1.0 + x*x);
        }
    }
    for(i=0;i<nthreads;++i){
        pi += sum[i]*step;
    }
    
    time_taken = omp_get_wtime() - start_time;
    
    printf("Value of pi: %lf. Time taken for basic parallel approach: %lf s\n",pi,time_taken); 

    return 0;
}