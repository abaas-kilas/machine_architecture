// main function for a rudimentary binary search tree manager

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "treemap.h"

int main(int argc, char *argv[]){
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }

  printf("TreeMap Editor\n"); // this will be the list of options at the start of the program
  printf("Commands:\n");
  printf("  quit:            exit the program\n");
  printf("  print:           shows contents of the tree in reverse sorted order\n");
  printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
  printf("  get <key>:       prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  clear:           eliminates all key/vals from the tree\n");
  printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:     clears the current tree and loads the one in the given file\n");
  
  char cmd[128]; // the first input
  treemap_t tree; // stack variable for the tree
  int success; // to see if the function was completed or not
  treemap_init(&tree); // tree initialization

  while(1){
    printf("TM> ");   // type the prompt
    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){ // no input, break loop
      printf("\n"); 
      break;
    }

    if( strcmp("quit", cmd)==0 ){     // quit command
      if(echo){
        printf("quit\n");
      }
      break;
    }

    else if( strcmp("add", cmd)==0 ){ // add command
      char key[128], value[128];
      fscanf(stdin,"%s",key); // second input key
      fscanf(stdin,"%s",value); // third input value
      if(echo){
        printf("add %s %s\n",key,value);
      }
      success = treemap_add(&tree,key,value); // calls add function. 1 if added successfully.
      if(!success){
        printf("modified existing key\n");
      }
    }

    else if( strcmp("get", cmd)==0 ){     // get command
      char key[128];
      fscanf(stdin,"%s",key); // second input key
      if(echo){
        printf("get %s\n",key);
      }
      char *got = treemap_get(&tree, key); // the return value from the get function
      if(got == NULL){
        printf("NOT FOUND\n");
      }
      else {
        printf("FOUND: %s\n",got);
      }
    }

    else if( strcmp("clear", cmd)==0 ){   // clear command
      if(echo){
        printf("clear\n");
      }
      treemap_clear(&tree); // calls clear
    }

    else if( strcmp("print", cmd)==0 ){   // print command
      if(echo){
        printf("print\n");
      }
      treemap_print_revorder(&tree); // calls reverse order print
    }

    else if( strcmp("preorder", cmd)==0 ){   // preorder command
      if(echo){
        printf("preorder\n");
      }
      treemap_print_preorder(&tree); // calls preorder print
    }

    else if( strcmp("load", cmd)==0 ){ // load command
      char fname[128];
      fscanf(stdin,"%s",fname); // second input file to read
      if(echo){
        printf("load %s\n",fname);
      }
      success=treemap_load(&tree,fname); // calls load. 1 if loaded successfully.
      if(!success){
        printf("load failed\n");
      }
    }

    else if( strcmp("save", cmd)==0 ){ // save command
      char fname[128];
      fscanf(stdin,"%s",fname); // second input file to write
      if(echo){
        printf("save %s\n",fname);
      }
      treemap_save(&tree,fname); // calls save
    }

    else{                                 // unknown command
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command %s\n",cmd); // loop continues
    }
  }
  treemap_clear(&tree); // frees tree memory
  return 0; // end program
}  