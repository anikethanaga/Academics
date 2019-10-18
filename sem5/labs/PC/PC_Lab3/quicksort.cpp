#include<iostream>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;

#define NUM_THREADS 4
#define ll long long int
#define f(i,g,n) for(int i=g;i<=n;i++)

void swap(ll *a,ll *b)
{
	ll t = *a;
	*a = *b;
	*b = t;
}

ll partition(ll A[],ll low,ll high)
{
	ll p = A[high];
	ll i = (low-1);
	f(j,low,high-1)
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

void quicksort_serial(ll A[],ll low,ll high)
{
	if(low < high)
	{
		ll p = partition(A,low,high);
		quicksort_serial(A,low,p-1);
		quicksort_serial(A,p+1,high);
	}
}

void quicksort_task(ll A[],ll low,ll high)
{
	if(low < high)
	{
		ll p = partition(A,low,high);
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

void quicksort_task_wait(ll A[],ll low,ll high)
{
	if(low < high)
	{
		ll p = partition(A,low,high);
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

void print(ll A[],ll n)
{
	f(i,0,n-1)
		cout<<A[i]<<" ";
	cout<<"\n";
}

int main()
{
	omp_set_num_threads(NUM_THREADS);
	srand(time(0));
	ll n;
	cin>>n;
	ll A[n],B[n],C[n]; 
	f(i,0,n-1)
	{
		A[i] = rand()%1000000;
		B[i] = A[i];
		C[i] = A[i];
	}
	cout<<"\nSerial Program\n";
	double time = omp_get_wtime();
	quicksort_serial(A,0,n-1);
	time = omp_get_wtime()-time;
	cout<<"Time taken: "<<setprecision(30)<<time<<"\n";
	f(i,0,75) cout<<"-"; cout<<"\n";

	bool val = true;
	cout<<"Parallel Program with task\n";
	time = omp_get_wtime();
	quicksort_task(B,0,n-1);
	time = omp_get_wtime()-time;
	cout<<"Time taken: "<<setprecision(30)<<time<<"\n";
	f(i,0,n-1)
	{
		if(A[i] != B[i])
		{
			val = false;
			break;
		}
	}
	val ? cout<<"Correct\n" : cout<<"Not correct\n";
	f(i,0,75) cout<<"-"; cout<<"\n";

	cout<<"Parallel Program with taskwait and data scoping\n";
	time = omp_get_wtime();
	quicksort_task_wait(C,0,n-1);
	time = omp_get_wtime()-time;
	cout<<"Time taken: "<<setprecision(30)<<time<<"\n";
	f(i,0,n-1)
	{
		if(A[i] != C[i])
		{
			val = false;
			break;
		}
	}
	val ? cout<<"Correct\n" : cout<<"Not correct\n";
	f(i,0,75) cout<<"-"; cout<<"\n";

	return 0;
}