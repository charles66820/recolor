#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"
#include "solution.h"

typedef struct nb_color_s {
  uint* tab;
  uint tab_len;
} nb_color_struct;

nb_color_struct* nb_color(game g) {
  uint* tab = (uint*)malloc(16 * sizeof(uint));
  if (tab == NULL) {
    exit(EXIT_FAILURE);
  }
  uint cpt = 1;
  for (int i = 0; i < game_height(g) * game_width(g);
       i++) {  // I go through all the tab
    bool exist = false;
    for (int y = 0; y < cpt; y++) {
      if (tab[y] ==
          game_cell_current_color(
              g, i % 12,
              i / 12)) {  // if the color is already in the tab, we don't add it
        exist = true;
      }
    }
    if (exist == false) {
      tab[cpt] = game_cell_current_color(
          g, i % 12, i / 12);  // if the color isn't in the tab, we add it and
                               // we increment the cpt
      cpt++;
    }  // We should do a realloc but It is not necessary in this exercise
  }
  nb_color_struct* col_tab = malloc(sizeof(nb_color_struct));
  col_tab->tab = tab;
  col_tab->tab_len = cpt;
  return col_tab;
}

solution uint_to_tab_sol(uint k, uint n, uint base, uint tab[]) {
  uint x[k];
  for (int i = k - 1; i != -1; i--) {
    if (n / (base ^ i) > 0) {
      x[i] = tab[n / (base ^ i)];
      n = n - (base ^ i);
    } else {
      x[i] = tab[0];
    }
  }
  return create_solution(x, k);
}

// This fonction test all the possibles solutions
solution* all_possibilities(uint tab[], uint nb_color, uint size_sol) {
  solution* solutions = malloc(sizeof(solutions) * nb_color ^ size_sol);
  for (int i = 0; i < (nb_color ^ size_sol);
       i++) {  // we try all the possibilities
    solutions[i] = uint_to_tab_sol(size_sol, i, nb_color, tab);
    // here, we have to test if the solution works
  }
  return solutions;
}

/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 * @return solution a struct with the solution or the msg "NO SOLUTION"
 */
solution find_one(game g) {
  nb_color_struct* nb_col = nb_color(g);
  uint nb_move = game_nb_moves_max(g);
  
  return NULL;
  /* for (uint i=0, i <= )
  bool is_sol = false;  // if true, return the sol for the file, if false
  return
                        // an arr of char (it contain "NO SOLUTION\n") for the
                        // file
  uint* nb_col = nb_color(g);


  solution sol = create_solution();
  return sol; */
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

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Error: invalid arguments");
    exit(EXIT_FAILURE);
  }

  solution retsol = NULL;
  game g = game_load(argv[2]);
  if (!strcmp(argv[1], "FIND_ONE"))
    retsol = find_one(g);
  else if (!strcmp(argv[1], "NB_SOL"))
    printf("nb sul if : %u\n", nb_sol(g));
  else if (!strcmp(argv[1], "FIND_MIN"))
    retsol = find_min(g);
  else {
    fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // on test si retsol est null sinon on écrit dans le fichier
  if (retsol != NULL) printf("la solution est : %s", string_solution(retsol));

  return EXIT_SUCCESS;
}
