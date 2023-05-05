#include <stdio.h>
#include <string.h>

char *answers[] = {
  "a set of dental instruments\n",
  "C++ without the ++ part\n",
  "assembly language\n",
  "trick question: it isn't convenient\n",
  "a gun that shoots forwards and backwards\n",
  "OCaml without type inference, garbage collection, or first-class functions\n",
  "Dvorak keyboards\n"
};
  

int verify(char *buf){
  int diff = strcmp(buf,answers[2]);
  if(diff == 0){
    return 0;
  }
  else{
    return 1;
  }
  
  // for(int i=0; i<19; i++){
  //   if(buf[i] != ans[i]){
  //     return 1;
  //   }
  // }
  // return 0;
}

