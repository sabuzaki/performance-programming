#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
using namespace std;

#ifdef ORIGINAL
//Simple 2d matrix matrix multiplication
__attribute__((noinline)) void compute_simple(double **A, double **B, double **C, int N) {
  for (int i = 0 ; i < N; i++) {
    for (int j = 0;  j < N; j++) {
      for (int k = 0; k < N; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

#elif OPTIMISED
// Optimised 2d matrix matrix multiplication
__attribute__((noinline)) void compute_optimised(double **A, double **B, double **C, int N) {
  for (int i = 0 ; i < N; i++) {
    for (int k = 0; k < N; k++) {
      for (int j = 0;  j < N; j++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

#endif

// Allocate the matrices
__attribute__((noinline)) void create_matrix(double **&A, double **&B, double **&C, int N) {

  A = new double*[N];
  B = new double*[N];
  C = new double*[N];

  for (int i = 0 ; i < N; i++) {
    A[i] = new double[N];
    B[i] = new double[N];
    C[i] = new double[N];
  }
}

// Initialise the matrices
__attribute__((noinline)) void init_matrix(double **A, double **B, double **C, int N){
  for (int i=0; i<N; i++) {
    for (int j = 0 ; j < N; j++) {
      A[i][j]=((double) rand() / (RAND_MAX));
      B[i][j]=((double) rand() / (RAND_MAX));
      C[i][j]=0.0;
    }
  }
}

// Delete the matrices
__attribute__((noinline)) void free_matrix(double **A, double **B, double **C, int N) {
  for (int i = 0 ; i < N; i++)  {
    delete A[i];
    delete B[i];
    delete C[i];
  }
  delete A;
  delete B;
  delete C;
}

__attribute__((noinline)) void print_check(double **Z, int N) {

  cout<<Z[0][0]<<" "<<Z[1][1]<<" "<<Z[2][2]<<endl;
}

__attribute__((noinline)) void zero_result(double **C, int N) {
  for (int i = 0 ; i < N; i++) {
    for (int j = 0;  j < N; j++) {
        C[i][j] = 0.0;
    }
  }
}
