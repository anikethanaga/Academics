#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;

int main() {

    int i;
    double x,pi,sum,aux,start_time,time_taken;

    x=0;
    sum = 0.0;
    step = 1.0/(double)num_steps;
    start_time = omp_get_wtime();

    #pragma omp parallel private(i,x,aux) shared(sum) 
    {
        #pragma omp for schedule(static) 
            for (i=0; i<num_steps; i=i+1){
                x=(i+0.5)*step;
                aux=4.0/(1.0+x*x);

            #pragma omp atomic
                sum = sum + aux;
            }
    }
    pi=step*sum;

    time_taken = omp_get_wtime() - start_time;
    
    printf("Value of pi: %lf. Time taken for atomic approach: %lf s\n",pi,time_taken);  

    return 0;
}