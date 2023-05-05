// optimized versions of matrix diagonal summing
#include "matvec.h"

int matsquare_FUNC(matrix_t mat, matrix_t matsq) {
  
  // Resets the squared array
  for(int i=0; i<mat.rows; i++){
    for(int j=0; j<mat.cols; j++){
      MSET(matsq,i,j,0);                          // set to 0
    }
  }

  // Pre-declare local variables
  int lead,mult1,mult2,curr1,curr2;

  // Utilizes C's row-major structure
  for(int i=0; i<mat.rows; i++){
    for(int j=0; j<mat.cols; j++){
      lead=MGET(mat,i,j);                         // lead value for each multiplication
      int k;
      for(k=0;k<mat.rows-2;k+=2){
        mult1=MGET(mat,j,k);                      // the multiplied value (2 at a time with unrolling)
        mult2=MGET(mat,j,k+1);
        curr1=MGET(matsq,i,k)+(lead*mult1);       // previous value plus the new calculation (2 at a time)
        curr2=MGET(matsq,i,k+1)+(lead*mult2);
        MSET(matsq,i,k,curr1);                    // set the new value
        MSET(matsq,i,k+1,curr2);
      }
      for(;k<mat.rows;k++){                       // cleans up odd dimension matrices (same operations as above)
        mult1=MGET(mat,j,k);
        curr1=MGET(matsq,i,k)+(lead*mult1);
        MSET(matsq,i,k,curr1);
      }
    }
  }
  
  return 0;
}

int matsquare_OPTM(matrix_t mat, matrix_t matsq) {
  if(mat.rows != mat.cols ||                       // must be a square matrix to square it
     mat.rows != matsq.rows || mat.cols != matsq.cols)
  {
    printf("matsquare_OPTM: dimension mismatch\n");
    return 1;
  }

  return matsquare_FUNC(mat, matsq);
}