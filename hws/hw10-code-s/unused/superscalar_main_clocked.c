// main function to call one of the loopin algorithms in superscalar_funcs.c.
//
// This version uses the clock() function to time execution of the loop.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>               // for clock() function and structs

// struct to hold pointers and info on algorithms for timing
typedef struct{
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);
  // ^^ nutty declaration of a function pointer
  char *name;                   // name of algorithm
  char *description;            // description of alg
} alg_t;

extern alg_t algs[];

void print_usage(char *prog_name){
  printf("usage: %s <ALG> <MULT> <EXP>\n",prog_name);
  printf("  <MULT> and <ALG> are integers, iterates for MULT * 2^{EXP} iterations\n");
  printf("  <ALG> is one of\n");
  for(int i=0; algs[i].alg_func != NULL; i++){
    printf("%18s : %s\n",algs[i].name,algs[i].description);
  }
}  

int main(int argc, char *argv[]){
  if(argc < 4){
    print_usage(argv[0]);
    return 1;
  }


  // Function pointer associated with alg
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);

  char *alg_name = argv[1];
  alg_func = NULL;

  // select algorithm to use
  for(int i=0; algs[i].alg_func != NULL; i++){
    if(strcmp(alg_name, algs[i].name) == 0){
      alg_func = algs[i].alg_func;
    }
  }
  if(alg_func == NULL){
    printf("Unknown algorithm '%s'\n",alg_name);
    print_usage(argv[0]);
    return 1;
  }

  // determine number of iterations
  unsigned long mult = atol(argv[2]);
  unsigned long exp  = atol(argv[3]);
  unsigned long one  = 1;                    // bothersome but necessary
  unsigned long iters = mult * (one << exp); // exponentiate 2 with a shift

  unsigned long start = 0;
  unsigned long delta = 3;

  printf("%s for %lu * 2^{%lu} = %lu iterations... ",alg_name,mult,exp,iters);
  fflush(stdout);

  // Time the running of the algorithm using library timing functions
  // See: https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html#CPU-Time
  clock_t begin = clock();                 // get current moment

  alg_func(iters, &start, &delta);         // run the specified algorithm

  clock_t end = clock();                   // get later moment to compare to start
  double user_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;

  printf("complete\n");

  printf("User CPU usage: %.3f sec\n",user_cpu_time);
  return 0;
}
