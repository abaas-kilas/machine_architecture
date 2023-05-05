// Complete this main to benchmark the search algorithms outlined in
// the project specification

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "search.h"

// Main Benchmark
int main(int argc, char *argv[]){
  
  // Choose Algorithms
  int *algos=malloc(4*sizeof(int));                 // {array,list,binary,tree}, default to "on" for all
  algos[0]=1;algos[1]=1;algos[2]=1;algos[3]=1;
  if(argc>4){                                       // algos specified. some or all will run
    char *cmnd=argv[4];
    algos[0]=0;algos[1]=0;algos[2]=0;algos[3]=0;
    for(int chr=0;chr<strlen(cmnd);chr++){          // "turn on" specified algorithms
      if(cmnd[chr]=='a'){algos[0]=1;}
      else if(cmnd[chr]=='l'){algos[1]=1;}
      else if(cmnd[chr]=='b'){algos[2]=1;}
      else if(cmnd[chr]=='t'){algos[3]=1;}
    }
  }
  // Gather Additional Commands
  int min=1<<atoi(argv[1]);                         // min and max length, also searches
  int max=1<<atoi(argv[2]);
  int src=atoi(argv[3]);

  // Format Header
  printf("=======================SEARCH ALGORITHM TIMINGS=======================\n");
  printf("%8s ","LENGTH");                          // length and searches always printed
  printf("%8s ","SEARCHES");
  if(algos[0]==1){                                  // checks algorithm headers, follows array indices
    printf("%12s ","array");
  }
  if(algos[1]==1){
    printf("%12s ","list");
  }
  if(algos[2]==1){
    printf("%12s ","binary");
  }
  if(algos[3]==1){
    printf("%12s ","tree");
  }
  printf("\n");

  // Run Algorithms
  for(long curr=min;curr<=max;curr*=2){            // similar structure as headers, this time in a loop
    printf("%8ld ",curr);
    printf("%8ld ",curr*src*2);
    clock_t begin, end;
    if(algos[0]==1){                               // array search (clock only searches)
      int *array=make_evens_array(curr);
      begin=clock();
      for(int reps=0;reps<src;reps++){
        for(int query=0;query<curr*2;query++){
          linear_array_search(array,curr,query);
        }
      }
      end=clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%12.4e ",time);
      free(array);
    }
    if(algos[1]==1){                               // list search (clock only searches)
      list_t *list=make_evens_list(curr);
      begin=clock();
      for(int reps=0;reps<src;reps++){
        for(int query=0;query<curr*2;query++){
          linkedlist_search(list,curr,query);
        }
      }
      end=clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%12.4e ",time);
      list_free(list);
    }
    if(algos[2]==1){                               // binary search (clock only searches)
      int *binary=make_evens_array(curr);
      begin=clock();
      for(int reps=0;reps<src;reps++){
        for(int query=0;query<curr*2;query++){
          binary_array_search(binary,curr,query);
        }
      }
      end=clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%12.4e ",time);
      free(binary);
    }
    if(algos[3]==1){                               // tree search (clock only searches)
      bst_t *tree=make_evens_tree(curr);
      begin=clock();
      for(int reps=0;reps<src;reps++){
        for(int query=0;query<curr*2;query++){
          binary_tree_search(tree,curr,query);
        }
      }
      end=clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%12.4e ",time);
      bst_free(tree);
    }
    printf("\n");
  }
  
  // End Benchmark
  free(algos);                                     // free excess mem
  return 0;
}