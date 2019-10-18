
#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) 
{ 

	#pragma omp parallel 
	{ 

		printf("Hello World... from thread = %d\n",omp_get_thread_num()); 
	} 
	#pragma omp parallel
    {
        #pragma omp single
        {
            printf("Number of Threads : %d\n", omp_get_num_threads());
        }
    }
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Number of Threads : %d\n", omp_get_num_threads());
        }
    }
    #pragma omp parallel num_threads(2)
    {
        #pragma omp single
        {
            printf("Number of Threads : %d\n", omp_get_num_threads());
        }
    }

} 
