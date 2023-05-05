#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *earliest_word(char *fname, int *nwords){
   FILE *fin=fopen(fname,"r");
   if(fin==NULL){
      *nwords=-1;
      return NULL;
   }
   char first;
   int end=fscanf(fin,"%s",first);
   int total=1;
   while (end!=EOF){
      char curr;
      end=fscanf(fin,"%s",curr);
      if(strcmp(curr,first)<0){
         first=curr;
      }
      total++;
   }
   fclose(fin);
   *nwords=total;
   return first;
}
// Opens the file fname and reads words from it
// until the end of file is reached then closes
// the file. If the file to be opened doesn't
// exist, returns NULL and sets nwords to
// -1. Tracks the alphabetic "earliest" word that
// is read in as indicated by strcmp(). Tracks how
// many words in total are read and sets nwords to
// that value.  Allocates a block of memory and
// copies the earliest word found into the block
// using strcpy(). Returns a pointer to the
// freshly allocated block.
//
// ASSUMPTIONS: Words are no longer than 127
// characters so will fit in an array of size
// 128. Files have at least one word in them.
    
int main(){
  int count; char *file; char *early;
  file = "vegetables.txt";
  // pumpkin carrot beet squash cucumber
  early = earliest_word(file, &count);
  printf("%s: %d words, %s earliest\n",
         file,count,early);
  // vegetables.txt: 5 words, beet earliest
  free(early);

  file = "fruits.txt";
  // banana peach orange apple pineapple strawberry
  early = earliest_word(file, &count);
  printf("%s: %d words, %s earliest\n",
         file,count,early);
  // fruits.txt: 6 words, apple earliest
  free(early);
  
  file = "not-there.txt";
  early = earliest_word(file, &count);
  if(early==NULL){
    printf("%s not found\n",file);
    // not-there.txt not found
  }
  return 0;
}