
#include<stdio.h>
#include<omp.h>
void main()
{
	omp_set_num_threads(5);
	/*#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("A %d\n",omp_get_thread_num());
			}
			#pragma omp taskwait
			{
				printf("B %d\n",omp_get_thread_num());
			}	
		}
		
		#pragma omp task
		{
			printf("A %d\n",omp_get_thread_num());
			//printf("B %d\n",omp_get_thread_num());
		}
		#pragma omp single
		{
			#pragma omp task
			{
				printf("C %d\n",omp_get_thread_num());
			}
		}
	}*/
	#pragma omp task
		{
			printf("A %d\n",omp_get_thread_num());
			//printf("B %d\n",omp_get_thread_num());
		}
		#pragma omp single
		{
			#pragma omp task
			{
				printf("C %d\n",omp_get_thread_num());
			}
		}

}