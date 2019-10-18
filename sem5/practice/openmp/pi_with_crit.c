//DOSENT USE PADDING
#include<omp.h>
#include<stdio.h>
static long num_steps=100000;
double step;
#define NUM_THREADS 2
void main()
{
	double pi=0.0,sum;
	step=1.0/(double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double a = omp_get_wtime();
	#pragma omp parallel
	{
		int i,id,nthreads;
		double x,sum;
		id=omp_get_thread_num();
		nthreads=omp_get_num_threads();
		//if(id==1) nthreads=nthrds;
		//if(id==0) nthreads=nthrds;
		for(i=id,sum=0.0;i<num_steps;i+=nthreads){
			x=(i+0.5)*step;
			sum+=4.0/(1.0+x*x);
		}
		/*#pragma omp critical
		pi+=sum*steo*/
		/*#pragma omp barrier
			pi+=sum*step;*/
		#pragma omp atomic
			pi+=sum*step;
	}
	double b=omp_get_wtime();

	printf("%lf\n",pi);
	printf("Time taken : %lf\n",(b-a));
}