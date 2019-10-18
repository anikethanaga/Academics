/*
**  PROGRAM: Finding the nth Fibonacci Number
**
**  PURPOSE: This is a program to find the nth Fibonacci number
**   		 using the formula :
**
**                fib(n)  = fib(n-1) + fib(n-2)
**
**           The formula is implemented using a function that 
**			 uses recursion calls.
**
**  USAGE:   The programs prompts the user to input a number. 
**           The programs prints the corresponding fibonacci number 
**			 ex : 0th fibonacci number is 0
**			  	  1st fibonacci number is 1
**				  and so on
**			 For n>=30, a stark difference in runtimes between
**			 the serial version and parallelised version of the 
**			 function is observed.
**
**  HISTORY: Written by Aniketh, Aug 2019.
*/
#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h>


long long int fib_serial(long long int n) 
{
	/*This is the serial version of the function to find nth fibonacci number*/
  	long long int i, j;
  	if (n<2)
    return n;
  	else 
  	{
    	i=fib_serial(n-1);
    	j=fib_serial(n-2);
    	return i+j;
  	}
}

long long int fib_parallel(long long int n) 
{
	/*This is the parallelised version of the function to find nth fibonacci number*/
	/*To get good performance you need to use a cutoff value for "n". 
	Otherwise, too many small tasks will be generated. 
	Once the value of "n" gets below this threshold it is best to simply execute the serial version without tasking.*/
  	long long int i, j;
  	if (n<20)
    return fib_serial(n);
  	else 
  	{
    	#pragma omp task shared(i)
    	i=fib_parallel(n-1);
    	#pragma omp task shared(j)
    	j=fib_parallel(n-2);
    	#pragma omp taskwait
    	return i+j;
  	}
}

int main()
{
	double start,end;
	long long int n,answer;
	printf("Enter the nth fibonacci number to print\n");
	scanf("%lld",&n);
	/* Taking user input */
	
	start = omp_get_wtime();
	/* start stores the timestamp for the beginning of code execution*/
	answer = fib_serial(n);
	end = omp_get_wtime();
	/* end stores the timestamp for the ending of code execution*/
	printf("Time taken for serial program = %lf milliseconds\n",(end-start)*1000);
	printf("The nth fibonacci number = %lld\n",answer);

	start = omp_get_wtime();
	omp_set_num_threads(10);
	#pragma omp parallel
	{
		#pragma omp single
		answer = fib_serial(n);
	}
	end = omp_get_wtime();
	printf("Time taken for parallel program = %lf milliseconds\n",(end-start)*1000);
	printf("The nth fibonacci number = %lld\n",answer);

	start = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		answer = fib_parallel(n);
	}
	end = omp_get_wtime();
	printf("Time taken for parallel program with task construct = %lf milliseconds\n",(end-start)*1000);
	printf("The nth fibonacci number = %lld\n",answer);


	return 0;
} 


