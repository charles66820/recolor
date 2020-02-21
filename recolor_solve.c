#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "solution.h"

uint nb_color(game g) {
  uint* tab = (uint*)malloc(16 * sizeof(uint));
  if (tab == NULL) {
    exit(EXIT_FAILURE);
  }
  uint cpt = 1;
  for (int i = 0; i < game_height(g) * game_width(g); i++) {
    bool exist = false;
    for (int y = 0; y < cpt; y++) {
      if (tab[y] == game_cell_current_color(g, i % 12, i / 12)) {
        exist = true;
      }
    }
    if (exist == false) {
      tab[cpt] = game_cell_current_color(g, i % 12, i / 12);
      cpt++;
    }
  }
  return tab;
}

/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 * @return solution a struct with the solution or the msg "NO SOLUTION"
 */
solution find_one(game g) {
  uint* nb_col = nb_color(g);
  uint nb_move = game_nb_moves_cur(g) - game_nb_moves_max(g);
  return NULL;
}

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 */
uint nb_sol(game g) { return 0; }

/**
 * @brief find the solution who require the smallest amount of moves
 *
 * @param g game with cells to print
 */
solution find_min(game g) { return NULL; }

int main(int* argc, int* argv[]) {
  if (argc != 4) {
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
  else {
    fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // on test si retsol est null sinon on écrit dans le fichier
}
