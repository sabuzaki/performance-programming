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

  
//#pragma omp parallel for default(none) shared(a,b,x)
  for (int i=0; i<NPOINTS; i++) {               //loop_1
    for (int j=0; j<NPOINTS; j++) {             //loop_2
       a[i][j] = 1.0; 
       b[i][j] = 3.14159265359; 
       x[i][j] = 1.0; 
    }
  }
  
  maxdiff = 0.0; 

#pragma omp parallel for default(none) shared(a,b,x,maxdiff) private(tmp) num_threads(8) reduction(+:diff)
  for (int iters = 0; iters < MAXITER; iters++){ //loop_3
   double a_local[NPOINTS][NPOINTS], b_local[NPOINTS][NPOINTS], x_local[NPOINTS][NPOINTS];        //my_code
    for (int i=0; i<NPOINTS; i++) {               //loop_1
      for (int j=0; j<NPOINTS; j++) {             //loop_2
        a_local[i][j] = a[i][j];
        b_local[i][j] = b[i][j];
        x_local[i][j] = x[i][j];
      }
    }
 for (int i=1; i<NPOINTS; i++) {             // loop_4
      // works but very slow:
//      #pragma omp parallel for default(none) shared(a,b,x,i) private(tmp) num_threads(16)   // working but slow
      for (int j=0; j<NPOINTS; j++) {           //loop_5
  	    tmp = a[i][j]/b[i-1][j];              
        x[i][j] -= x[i-1][j] * tmp;         
	      b[i][j] -= a[i][j] * tmp; 
      }
    }

    diff = 0.0; 
//    #pragma omp parallel for default(none) shared(a,b,x) private(tmp) num_threads(16) reduction(+:diff)     // working! 5.8 seconds.
    for (int i=0; i<NPOINTS; i++) {             //loop_6
      for (int j=1; j<NPOINTS; j++) {           //loop_7
      	tmp = a[i][j]/b[i][j-1];
        x[i][j] -= x[i][j-1] * tmp;
	      b[i][j] -= a[i][j] * tmp; 
	      diff += fabs(a[i][j] * tmp)/(NPOINTS*NPOINTS);
      }
    }

    for (int i=0; i<NPOINTS; i++) {               //loop_1
      for (int j=0; j<NPOINTS; j++) {             //loop_2
        a[i][j] = a_local[i][j];
        b[i][j] = b_local[i][j];
        x[i][j] = x_local[i][j];
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
