#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

int partition_serial(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    return p + lt_n;
}

void quicksort_serial(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition_serial(a, p, r); 
        {   
            quicksort_serial(a, p, div - 1); 
            quicksort_serial(a, div + 1, r); 

        }
    }
}


int partition_parallel(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    return p + lt_n;
}

void quicksort_parallel(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition_parallel(a, p, r); 
    #pragma omp parallel sections
        {   
            #pragma omp section
                quicksort_parallel(a, p, div - 1); 
            #pragma omp section
                quicksort_parallel(a, div + 1, r); 
        }
    }
}

int main(void)
{
    double start,end;
    int a[10] = {5, 3, 8, 4, 0, 9, 2, 1, 7, 6};
    int i;

    start = omp_get_wtime();
    quicksort_parallel(a, 0, 9);
    end = omp_get_wtime();
    printf("serial : %lf\n",(end-start)*1000);

    start = omp_get_wtime();
    quicksort_parallel(a, 0, 9);
    end = omp_get_wtime();
    printf("parallel : %lf\n",(end-start)*1000);


    for(i = 0;i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}