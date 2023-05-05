#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>               // for clock() and other functions

// only add
void add_only(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long inc = *delta;
  for(unsigned long i=0; i<iters; i++){
    ret += inc;
  }
  *start = ret;
}

// only multiply
void mul_only(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long mul = *delta;
  for(unsigned long i=0; i<iters; i++){
    ret *= mul;
  }
  *start = ret;
}

// Add and multiply to separate destinations
void add_and_mul_sep(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long retM = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){
    retA += del;
    retM *= del;
  }
  *start = retA+retM;
}

// Add and multiply to the same destination
void add_and_mul_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){
    ret += del;
    ret *= del;
  }
  *start = ret;
}


// Add in a loop. Then multiply in a loop. Separate destinations.
void add_then_mul_sep(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long retM = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){ // add first
    retA += del;
  }
  for(unsigned long i=0; i<iters; i++){ // then multiply
    retM *= del;
  }
  *start = retA+retM;
}


// Add in a loop. Then multiply in a loop. Same destinations.
void add_then_mul_same(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long ret = *start;
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){ // add first
    ret += del;
  }
  for(unsigned long i=0; i<iters; i++){ // then multiply
    ret *= del;
  }
  *start = ret;
}


// Add in a loop. Then multiply in a loop. Same destinations.
void add_and_add_sep(unsigned long iters, unsigned long *start, unsigned long *delta)
{
  unsigned long retA = *start;
  unsigned long retB = (*start)+19; // add a different amount to force 2 adds (compiler may optimize away otherwise)
  unsigned long del = *delta;
  for(unsigned long i=0; i<iters; i++){ 
    retA += del;
    retB += del;
  }
  *start = retA+retB;
}




// struct to hold pointers and info on algorithms for timing
typedef struct{
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta);
  // ^^ nutty declaration of a function pointer
  char *name;                   // name of algorithm
  char *description;            // description of alg
} alg_t;

alg_t algs[] = {
  {add_only,"add_only","only add"},
  {mul_only,"mul_only","only multiply"},
  {add_and_mul_sep,"add_and_mul_sep","add and multiply in the same loop, different destinations"},
  {add_and_mul_same,"add_and_mul_same","add and multiply in the same loop, same destination "},
  {add_then_mul_sep,"add_then_mul_sep","add and multiply in different loops, separate destinations"},
  {add_then_mul_same,"add_then_mul_same","add and multiply in different loops, same destinations"},
  {add_and_add_sep,"add_and_add_sep","add and add in same loop, separate destinations"},
  {NULL,NULL,NULL}
};

void print_usage(char *prog_name){
  printf("usage: %s <ALG> <MULT> <EXP>\n",prog_name);
  printf("  <MULT> and <ALG> are integers\n");
  printf("  iterates for MULT*2^{EXP} iterations,\n");
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

  char *alg_name = argv[1];

  // Function pointer associated with alg
  void (*alg_func)(unsigned long iters, unsigned long *start, unsigned long *delta) = NULL;

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
  unsigned long iters = mult * (1 << exp); // exponentiate 2 with shifts

  unsigned long start = 0;
  unsigned long delta = 3;


  // Time the running of the algorithm using library timing functions
  // See: https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html#CPU-Time
  clock_t begin = clock();                 // get current moment

  alg_func(iters, &start, &delta);         // run the specified algorithm

  clock_t end = clock();                   // get later moment to compare to start
  double user_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;

  printf("User CPU usage: %.3f sec\n",user_cpu_time);
  return 0;
}
