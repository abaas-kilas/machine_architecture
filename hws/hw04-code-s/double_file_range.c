// unused problem to find min/max in a file full of doubles

#include <stdio.h>

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("usage: %s <filename>\n", argv[1]);
  }

  FILE *fin = fopen(argv[1],"r");

  if(fin == NULL){
    printf("could not open the file\n");
    return 1;
  }

  double num;

  int ret = fscanf(fin,"%lf",&num);
  if(ret == EOF){
    printf("file was empty\n");
    fclose(fin);
    return 1;
  }
  double min=num, max=num;

  while(fscanf(fin, "%lf", &num) != EOF){
    if(num < min){
      min = num;
    }
    if(num > max){
      max = num;
    }
  }

  fclose(fin);
  printf("min: %f\n",min);
  printf("max: %f\n",max);
    
  return 0;
}
