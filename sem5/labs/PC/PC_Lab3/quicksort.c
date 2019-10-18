/*
**  PROGRAM: Implementing Quicksort using Task constructs
**
**  PURPOSE: This is a program to find implement the standard
**   		 Quicksort using task constructs and compare the 
**			 difference in runtime between the serial version 
**			 of the same.
**                
**
**  USAGE:   The program prompts the user to input a number. 
**           The program create a array of random numbers
**			 of size equal to the input 
**			 The array is sorted using the standard Quicksort
**			 algorithm, first serially , then using task 
**			 construct and then finally using taskwait
**			 and data scoping.
**			 
**
**  HISTORY: Written by Aniketh, Aug 2019.
*/
#include<omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void swap(long long int *a,long long int *b)
{
	long long int t = *a;
	*a = *b;
	*b = t;
}

long long int partition(long long int A[],long long int low,long long int high)
{
	long long int p = A[high];
	long long int i = (low-1);
	for(long long int j=low;j<=high-1;j++)
	{
		if(A[j] < p)
		{
			i++;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[i+1],&A[high]);
	return (i+1);
}

void quicksort_serial(long long int A[],long long int low,long long int high)
{
	if(low < high)
	{
		long long int p = partition(A,low,high);
		quicksort_serial(A,low,p-1);
		quicksort_serial(A,p+1,high);
	}
}

void quicksort_task(long long int A[],long long int low,long long int high)
{
	if(low < high)
	{
		long long int p = partition(A,low,high);
		if(high-low < 1000)
		{
			quicksort_serial(A,low,p-1);
			quicksort_serial(A,p+1,high);
		}
		else
		{
			#pragma omp task
				quicksort_task(A,low,p-1);
			#pragma omp task
				quicksort_task(A,p+1,high);
		}
	}
}

void quicksort_task_wait(long long int A[],long long int low,long long int high)
{
	if(low < high)
	{
		long long int p = partition(A,low,high);
		if(high-low < 1000)
		{
			quicksort_serial(A,low,p-1);
			quicksort_serial(A,p+1,high);
		}
		else
		{
			#pragma omp task shared(A) firstprivate(low,p)
				quicksort_task_wait(A,low,p-1);
			#pragma omp task shared(A) firstprivate(high,p)
				quicksort_task_wait(A,p+1,high);
			#pragma omp taskwait
		}
	}
}


int main()
{
	omp_set_num_threads(10);
	srand(time(0));
	long long int n;
	scanf("%lld",&n);
	long long int A[n],B[n],C[n]; 

	for(long long int i=0;i<=n-1;i++)
	{
		A[i] = rand()%1000000;
		B[i] = A[i];
		C[i] = A[i];
	}
	printf("Serial Program\n");
	double time = omp_get_wtime();
	quicksort_serial(A,0,n-1);
	time = omp_get_wtime()-time;
	printf("Time taken : %lf\n\n",time);
	
	printf("Time taken using task construct\n");
	time = omp_get_wtime();
	quicksort_task(B,0,n-1);
	time = omp_get_wtime()-time;
	printf("Time taken : %lf\n\n",time);


	printf("Time taken for parallelised version with taskwait and data scoping\n");
	time = omp_get_wtime();
	quicksort_task_wait(C,0,n-1);
	time = omp_get_wtime()-time;
	printf("Time taken : %lf\n\n",time);

	return 0;
}