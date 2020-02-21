#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.c"

/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 */
solution find_one(){
    return NULL;
}

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 */
uint nb_sol(){
}

/**
 * @brief find the solution who require the smallest amount of moves
 *
 * @param g game with cells to print
 */
solution find_min(){
}

int main(int* argc, int* argv[]){
    if (argc!=4){
        fprintf(stderr, "Error: invalid arguments");
        exit(EXIT_FAILURE);
    }

    solution retsol = NULL;
    
    if (!strcmp(argv[1], "FIND_ONE"))
      retsol = find_one();
    else if (!strcmp(argv[1], "NB_SOL"))
      retsol = nb_sol();
    else if (!strcmp(argv[1], "FIND_MIN"))
      retsol = find_min();
    else{
      fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    // on test si retsol est null sinon on écrit dans le fichier
}
