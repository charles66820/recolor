#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.c"

uint nb_color (game g){
  return 0;
}

/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 */
solution find_one(game g){
  uint nb_col = 
    return NULL;
}

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 */
uint nb_sol(game g){
  return 0;
}

/**
 * @brief find the solution who require the smallest amount of moves
 *
 * @param g game with cells to print
 */
solution find_min(game g){
  return NULL;
}

int main(int* argc, int* argv[]){
    if (argc!=4){
        fprintf(stderr, "Error: invalid arguments");
        exit(EXIT_FAILURE);
    }

    solution retsol = NULL;
    game g = game_load(argv[1]);
    if (!strcmp(argv[1], "FIND_ONE"))
      retsol = find_one(g);
    else if (!strcmp(argv[1], "NB_SOL"))
      retsol = nb_sol(g);
    else if (!strcmp(argv[1], "FIND_MIN"))
      retsol = find_min(g);
    else{
      fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    // on test si retsol est null sinon on écrit dans le fichier
}
