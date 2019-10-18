#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main() {

    int i;
    double x,pi,sum=0.0,start_time,time_taken;

    start_time = omp_get_wtime();

    step = 1.0/(double)num_steps;

    #pragma omp serial
    {
        for(i=0;i<num_steps;++i){
            x = (i+0.5)*step;
            sum += 4.0/(1.0 + x*x);
        }
        pi = step*sum;
    }
    

    time_taken = omp_get_wtime() - start_time;
    
    printf("Value of pi: %lf. Time taken for serial approach: %lf s\n",pi,time_taken);

    return 0;
}