#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int* argc, int* argv[]){
    if (argc!=4){
        fprintf(stderr, "Error: invalid arguments");
        exit(EXIT_FAILURE);
    }
    if (!strcmp(argv[1], "FIND_ONE"))
      find_one(argv[2],argv[3]);
    else if (!strcmp(argv[1], "NB_SOL"))
      nb_sol(argv[2],argv[3]);
    else if (!strcmp(argv[1], "FIND_MIN"))
      find_min(argv[2],argv[3]);
    else{
      fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
      exit(EXIT_FAILURE);
    }
}