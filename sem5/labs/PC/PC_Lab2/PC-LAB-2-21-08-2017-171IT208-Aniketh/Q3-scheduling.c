#include <omp.h>
#include <stdio.h> 
#include <stdlib.h>

int main(){
    long int i,N=327000;
    long int a[N];
    double b[N];
    double start,end; 
    
    for(i=0;i<N;++i){
        a[i] = i; 
    }   

    start = omp_get_wtime();

    for(i=0; i<N-1;i++) {
        b[i]=(a[i]+a[i+1])/2.0;
    }
    
    end = omp_get_wtime();
    printf("Time taken for serial scheduling approach = %lf s\n", end - start);

    start = omp_get_wtime(); 
    #pragma omp parallel
    {
        #pragma omp for
        for(i=0; i<N-1;i++) {
            b[i]=(a[i]+a[i+1])/2.0;
        }
    }
    end = omp_get_wtime();

    printf("Time taken for parallel scheduling approach = %lf s\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(static,1000)
        for(i=0; i<N-1;i++) {
            b[i]=(a[i]+a[i+1])/2.0;
        }
    }
    end = omp_get_wtime();

    printf("Time taken for parallel static scheduling approach = %lf s\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic,1000)
        for(i=0; i<N-1;i++) {
            b[i]=(a[i]+a[i+1])/2.0;
        }
    }
    end = omp_get_wtime();

    printf("Time taken for parallel dynamic scheduling approach = %lf s\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(guided,1000)
        for(i=0; i<N-1;i++) {
            b[i]=(a[i]+a[i+1])/2.0;
        }
    }
    end = omp_get_wtime();
    printf("Time taken for parallel guided scheduling approach = %lf s\n", end - start);
    return 0;
}
