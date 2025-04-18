#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 

# define NPOINTS 2000
# define MAXITER 400


int main(){

  double a[NPOINTS][NPOINTS], b[NPOINTS][NPOINTS], x[NPOINTS][NPOINTS];
  double diff, maxdiff, tmp; 
  double start, finish; 

  start = omp_get_wtime();  

  
//#pragma omp parallel for default(none) shared(a,b,x) num_threads(8)       //# no performance increase
  for (int i=0; i<NPOINTS; i++) {               //loop_1
 //   #pragma omp parallel for default(none) shared(a,b,x,i) num_threads(4)  //     # no performance increase
    for (int j=0; j<NPOINTS; j++) {             //loop_2
       a[i][j] = 1.0; 
       b[i][j] = 3.14159265359; 
       x[i][j] = 1.0; 
    }
  }
  
  maxdiff = 0.0; 
  for (int iters = 0; iters < MAXITER; iters++){ //loop_3
    for (int i=1; i<NPOINTS; i++) {             // loop_4
#pragma omp parallel num_threads(16) default(none) shared(x,b,a,i) private(tmp)
{
//      #pragma omp parallel for default(none) shared(a,b,x,i) private(tmp) num_threads(16) nowait // working but slow
    #pragma omp for nowait 
      for (int j=0; j<NPOINTS; j++) {           //loop_5
  	    tmp = a[i][j]/b[i-1][j];              
        x[i][j] -= x[i-1][j] * tmp;         
	      b[i][j] -= a[i][j] * tmp; 
      }
    }
  }

    diff = 0.0; 

//    #pragma omp parallel for default(none) shared(a,b,x) private(tmp) num_threads(32) reduction(+:diff) // working! 5.8 seconds.
#pragma omp parallel num_threads(16) default(none) shared(x,b,a) private(tmp) reduction(+:diff) 
{
    #pragma omp for nowait
    for (int i=0; i<NPOINTS; i++) {             //loop_6
      for (int j=1; j<NPOINTS; j++) {           //loop_7
      	tmp = a[i][j]/b[i][j-1];
        x[i][j] -= x[i][j-1] * tmp;
	      b[i][j] -= a[i][j] * tmp; 
	      diff += fabs(a[i][j] * tmp)/(NPOINTS*NPOINTS);
      }
    }
}

    maxdiff = fmax(diff,maxdiff); 

  }

  finish = omp_get_wtime();  

/*
 *  Output the results
 */

  printf("Max Diff = %12.8f \n",maxdiff);
  printf("Time = %8.4f seconds\n",finish-start);

  }
