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
  if (g==NULL){
    exit(EXIT_FAILURE);
  }
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
  if (col_tab == NULL) {
    exit(EXIT_FAILURE);
  }
  col_tab->tab = tab;
  col_tab->tab_len = cpt;
  return col_tab;
}

/**
 * @brief .
 * @param k the solution length
 * @param n the solution number
 * @param nb_col the numbers of colors
 * @param tab the array of colors
 * @return the solution
 **/
solution uint_to_tab_sol(uint k, uint n, uint nb_col, uint tab[]) {
  uint x[k];
  for (uint i = k - 1; i > -1; i--) {
    if (n / (int)pow(nb_col, i) > 0) {
      x[i] = tab[(n / (int)pow(nb_col, i))];
      n = n - (int)pow(nb_col, i);
    } else {
      x[i] = tab[0];
    }
  }
  return create_solution(x, k);
}

int int_pow(int base, int exp) {
  int result = 1;
  while (exp) {
    if (exp % 2) result *= base;
    exp /= 2;
    base *= base;
  }
  return result;
}

/**
 * @brief This fonction test all the possibles solutions.
 * @param tab an array of colors
 * @param nb_color the number of color in the array (the length of the array)
 * @param size_sol the size of the solution
 * @return one array of solutions
 * @pre @p tab is not NULL
 **/
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

  solution* first_sol =
      all_possibilities(nb_col->tab, nb_col->tab_len, nb_move);

  for (uint i = 0; i < (nb_col->tab_len ^ nb_move); i++) {
    int* tab = int_solution(first_sol[i]);
    for (uint j = 0; j < len_solution(first_sol[i]); j++) {
      game_play_one_move(g, tab[j]);
      if (game_is_over(g)) {
        uint* sol_tab = tab;
        uint len_sol_tab = len_solution(first_sol[i]);
        game_delete(g);
        free(first_sol);
        free(nb_col->tab);
        free(nb_col);
        return create_solution(sol_tab, len_sol_tab);
      }
      delete_solution(first_sol[i]);
      game_restart(g);
    }
  }
  game_delete(g);
  free(first_sol);
  free(nb_col->tab);
  free(nb_col);
  return NULL;
}

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 * @return uint the number of solutions for the game g
 */
uint nb_sol(game g) {
  uint nb_sol = 0;

  nb_color_struct* nb_col = nb_color(g);
  uint nb_move = game_nb_moves_max(g);

  solution* all_poss = all_possibilities(nb_col->tab, nb_col->tab_len, nb_move);

  for (uint i = 0; nb_col->tab_len ^ nb_move; i++) {
    int* tab = int_solution(all_poss[i]);
    for (uint j = 0; j < len_solution(all_poss[i]); j++) {
      game_play_one_move(g, tab[j]);
      if (game_is_over(g)) {
        nb_sol++;
        break;
      }
    }
    delete_solution(all_poss[i]);
    game_restart(g);
  }

  game_delete(g);
  free(all_poss);
  free(nb_col->tab);
  free(nb_col);

  return nb_sol;
}

/**
 * @brief find the solution who require the smallest amount of moves
 *
 * @param g game with cells to print
 * @return solution a struct with the smallest possible solution of the game g
 */
solution find_min(game g) { return NULL; }
/* Appeler FIND_ONE avec nb_coups_max = 1; puis 2 puis 3 jusqu'à n*/

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

  // try if retsol is NULL else we can write in the file
  if (retsol != NULL) printf("la solution est : %s", string_solution(retsol));

  return EXIT_SUCCESS;
}
