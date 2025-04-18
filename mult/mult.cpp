#include "mult.h"

int main(int argc, char *argv[])
{
  int N; 
  int iters=10;    

  if(argc<2){
    cout << "Expecting an integer parameter specifying one dimension of the matrix size." << endl;
    exit(1);
  }else{
    N=atoi(argv[1]);
  }

  cout << "Running with matrix size of "<< N << "x" << N <<endl;
 
  double **A, **B, **C; 

  create_matrix(A, B, C, N);

  init_matrix(A, B, C, N);

  for (int i=0; i < iters; i++) {
    zero_result(C,N);
#ifdef ORIGINAL
    compute_simple(A,B,C,N);
#elif OPTIMISED
    compute_optimised(A,B,C,N);
#else
    cout << "Compiled incorrectly, no compute routine specified" << endl;
#endif
  }

  free_matrix(A, B, C, N);

  return 0;
}



