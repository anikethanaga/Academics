#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define m1 170                 /* number of rows in matrix A */
#define n1  160                /* number of columns in matrix A */
#define n2 150                 /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
    int tid, nthreads, i, j, k, chunk;
    double  a[m1][n1],           /* matrix A to be multiplied */
    b[n1][n2],           /* matrix B to be multiplied */
    c[m1][n2];           /* result matrix C */
  
    //printf("Initializing matrices...\n");

    //Initialize matrices
    for (i=0; i<m1; i++)
    for (j=0; j<n1; j++)
      a[i][j]= i*j;
 
    for (i=0; i<n1; i++)
        for (j=0; j<n2; j++)
        b[i][j]= i+j;
  
    for (i=0; i<m1; i++)
        for (j=0; j<n2; j++)
        c[i][j]= 0;

    double start = omp_get_wtime();
    for (i=0; i<m1; i++)    
    {
        for(j=0; j<n2; j++)       
            for (k=0; k<n1; k++)
                c[i][j] += a[i][k] * b[k][j];
    }
    double end = omp_get_wtime();  

    printf("Total time taken for serial approach= %g ms\n",(end-start)*1000);

    chunk = 2;                    //set loop iteration chunk size

    
    // Spawn a parallel region explicitly scoping all variables

    start = omp_get_wtime();
    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
    {

        //Do matrix multiply sharing iterations on outer loop       
        #pragma omp for schedule (static, chunk)
        for (i=0; i<m1; i++)    
        {
            for(j=0; j<n2; j++)       
                for (k=0; k<n1; k++)
                    c[i][j] += a[i][k] * b[k][j];
        }
    }   // End of parallel region
    end = omp_get_wtime();

    printf("Total time taken for parallel approach= %g ms\n",(end-start)*1000);
}