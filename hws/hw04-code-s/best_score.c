#include <stdio.h>

typedef struct {
  char name[128];               // name of student
  double score;                 // score on exam
} grade_t;
// struct which allows assignment of name/score such as in
//   best = curgrade;
//   printf("best is now: %s %f\n", best.name, best.score);

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("usage: %s <filename>\n", argv[0]);
    printf("<filename> should have columns of names, numbers as in\n");
    printf("Darlene 91.0\n");
    printf("Angela  76.5\n");
    printf("Elliot  94.5\n");
    printf("Tyrell  87.5\n");
    printf("Dom     70.0\n");
    printf("Phillip 55.5\n");
    return 1;
  }

  FILE *fin = fopen(argv[1],"r");

  if(fin == NULL){
    printf("could not open the file\n");
    return 1;
  }

  grade_t best;

  int ret = fscanf(fin,"%s %lf",best.name, &best.score);
  if(ret == EOF){
    printf("file was empty\n");
    fclose(fin);
    return 1;
  }
  
  grade_t grade;

  while(fscanf(fin, "%s %lf", grade.name, &grade.score) != EOF){
    if(grade.score > best.score){
      best = grade;
    }
  }

  fclose(fin);
  printf("Best score: %s %f\n",best.name, best.score);
  return 0;
}
