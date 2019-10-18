#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h>

int main()
{
	long long int n1=100000,n2=5642342,count1=0,count2=0;
	double a=omp_get_wtime();
	for(long long int i=1;i<n1;i++)
	{
		if(n1%i==0)
			count1++;
	}
	for(long long int i=1;i<n2;i++)
	{
		if(n2%i==0)
			count2++;
	}
	double b=omp_get_wtime();
	double serial_time = b-a;

	printf("Time taken for program using serial approach : %g seconds\n",serial_time);

	int n=omp_get_num_threads();
	
	a=omp_get_wtime();
	#pragma omp sections
	{
		#pragma omp section
			for(long long int i=1;i<n1;i++)
			{
				if(n1%i==0)
					count1++;
			}
		#pragma omp section
			for(long long int i=1;i<n2;i++)
			{
				if(n2%i==0)
					count2++;
			}
	}
	b=omp_get_wtime();
	double parallel_time = b-a;
	printf("Time taken for program using work sharing construct : %g seconds\n",parallel_time);

	a=omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for nowait
			for(long long int i=1;i<n1;i++)
			{
				if(n1%i==0)
					count1++;
			}
		#pragma omp for nowait
			for(long long int i=1;i<n2;i++)
			{
				if(n2%i==0)
					count2++;
			}
	}
	b=omp_get_wtime();
	double no_wait_time = b-a;
	printf("Time taken for program using nowait clause : %g seconds\n",no_wait_time);

	return 0;
} 