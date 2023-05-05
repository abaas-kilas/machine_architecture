// SOLUTION
// reversal_benchmark.c: Tests 2 versions of an array reversal
// code. Add timing information to determine which is more efficient
// and optionally implement a further optimized version.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void reverse_arr1(int *arr, long size){
  int *tmp = malloc(sizeof(int)*size);
  for(long i=0; i<size; i++){
    tmp[i] = arr[size-i-1];
  }
  for(long i=0; i<size; i++){
    arr[i] = tmp[i];
  }
  free(tmp);
}

void reverse_arr2(int *arr, long size){
  for(long i=0; i<size/2; i++){
    int tmp = arr[i];
    arr[i] = arr[size-i-1];
    arr[size-i-1] = tmp;
  }
}


// based on reverse_arr2() + unrolling
void reverse_arr_OPTM(int *arr, long size){
  long i;

  for(i=0; i<size/2-4; i+=4){   // unrolled loop
    int tmp0 = arr[i+0];
    arr[i+0] = arr[size-i-1-0];
    arr[size-i-1-0] = tmp0;

    int tmp1 = arr[i+1];
    arr[i+1] = arr[size-i-1-1];
    arr[size-i-1-1] = tmp1;

    int tmp2 = arr[i+2];
    arr[i+2] = arr[size-i-1-2];
    arr[size-i-1-2] = tmp2;

    int tmp3 = arr[i+3];
    arr[i+3] = arr[size-i-1-3];
    arr[size-i-1-3] = tmp3;
  }

  for(; i<size/2; i+=1){     // cleanup
    int tmp0 = arr[i+0];
    arr[i+0] = arr[size-i-1-0];
    arr[size-i-1-0] = tmp0;
  }
}

int main(int argc, char *argv[]){
  if(argc < 4){
    printf("usage: %s <min_pow2> <max_pow2> <repeats>\n",argv[0]);
    return 1;
  }
  int minsize = atoi(argv[1]);
  int maxsize = atoi(argv[2]);
  int repeats = atoi(argv[3]);

  printf("%10s ","SIZE");
  printf("%10s ","rev1");
  printf("%10s ","rev2");
  printf("%10s ","rev_OPTM");
  printf("\n");

  for(long s=minsize; s<=maxsize; s++){
    long size = 1 << s;

    printf("%10ld ",size);

    int *arr1 = malloc(sizeof(int)*size);
    int *arr2 = malloc(sizeof(int)*size);
    int *arr3 = malloc(sizeof(int)*size);
    for(long i=0; i<size; i++){
      arr1[i] = i;
      arr2[i] = i;
      arr3[i] = i;
    }


    clock_t begin, end;
    
    begin = clock();
    for(int i=0; i<repeats; i++){ // repeatedly run function
      reverse_arr1(arr1,size);
    }
    end = clock();
    double cpu_time1 = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%10.4e ",cpu_time1);
      
    begin = clock();
    for(int i=0; i<repeats; i++){ // repeatedly run function
      reverse_arr2(arr2,size);
    }
    end = clock();
    double cpu_time2 = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%10.4e ",cpu_time2);

    begin = clock();
    for(int i=0; i<repeats; i++){ // repeatedly run function
      reverse_arr_OPTM(arr3,size);
    }
    end = clock();
    double cpu_time3 = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%10.4e ",cpu_time3);

    printf("\n");

    // check array contents are correct 
    if(repeats % 2 == 0){       // even # repeats: arrays ordered
      for(long i=0; i<size; i++){
        assert(arr1[i] == i);
        assert(arr2[i] == i);
        assert(arr3[i] == i);
      }
    }
    else{                       // odd # repeats: arrays reversed
      for(long i=0; i<size; i++){
        assert(arr1[i] == size-i-1);
        assert(arr2[i] == size-i-1);
        assert(arr3[i] == size-i-1);
      }
    }

    free(arr1);
    free(arr2);
    free(arr3);
  }

  return 0;
}
