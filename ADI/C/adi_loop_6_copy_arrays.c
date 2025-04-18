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
  for (int iters = 0; iters < MAXITER; iters++){ //loop_3

    for (int i=1; i<NPOINTS; i++) {             // loop_4
      // works but very slow:
//      #pragma omp parallel for default(none) shared(a,b,x,maxdiff,i) private(diff,tmp) num_threads(32)
      for (int j=0; j<NPOINTS; j++) {           //loop_5
  	    tmp = a[i][j]/b[i-1][j];              
        x[i][j] -= x[i-1][j] * tmp;         
	      b[i][j] -= a[i][j] * tmp; 
      }
    }

    diff = 0.0; 

//    #pragma omp parallel for default(none) shared(a,b,x) private(tmp) num_threads(16) reduction(+:diff)     // working! 5.8 seconds.
    #pragma omp parallel for default(none) private(tmp) shared(a,b,x) num_threads(16) reduction(+:diff)     // working! 5.8 seconds.
    for (int i=0; i<NPOINTS; i++) {             //loop_6
      double a_local[NPOINTS], b_local[NPOINTS], x_local[NPOINTS];        //my_code
       for (int j = 0; j < NPOINTS; j++) {                                //mycode
        a_local[j] = a[i][j];
        b_local[j] = b[i][j];
        x_local[j] = x[i][j];
      }
//    original code:
/*      for (int j=1; j<NPOINTS; j++) {           //loop_7
      	tmp = a[i][j]/b[i][j-1];
        x[i][j] -= x[i][j-1] * tmp;
	      b[i][j] -= a[i][j] * tmp; 
	      diff += fabs(a[i][j] * tmp)/(NPOINTS*NPOINTS);
      }*/
      
      #pragma omp parallel for default(none) private(tmp) shared(x_local,a_local,b_local)  num_threads(4) reduction(+:diff)
       for (int j = 1; j < NPOINTS; j++) {        //my_code
        tmp = a_local[j] / b_local[j - 1];
        x_local[j] -= x_local[j - 1] * tmp;
        b_local[j] -= a_local[j] * tmp;
        diff += fabs(a_local[j] * tmp) / (NPOINTS * NPOINTS);
    }

      for (int j = 0; j < NPOINTS; j++) {       // my_code
        a[i][j] = a_local[j];
        b[i][j] = b_local[j];
        x[i][j] = x_local[j];
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
