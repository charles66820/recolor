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
} nb_color_s;

nb_color_s* nb_color(game g) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }

  uint* colors_tab = (uint*)malloc(16 * sizeof(uint));
  if (colors_tab == NULL) {
    exit(EXIT_FAILURE);
  }
  uint cpt = 0;

  // I go through all the tab
  for (int i = 0; i < game_height(g) * game_width(g); i++) {
    // check if the color is already in the tab, we don't add it
    bool exist = false;
    for (int y = 0; y < cpt; y++)
      if (colors_tab[y] == game_cell_current_color(g, i % 12, i / 12))
        exist = true;

    // if the color isn't in the tab, we add it and we increment the cpt
    if (!exist) {
      colors_tab[cpt] = game_cell_current_color(g, i % 12, i / 12);
      cpt++;
    }  // We should do a realloc but It is not necessary in this exercise
  }

  // create struture for return colors and nuber of colors
  nb_color_s* col_tab = malloc(sizeof(nb_color_s));
  if (col_tab == NULL) {
    exit(EXIT_FAILURE);
  }
  uint* tab = (uint*)malloc(cpt + 1 * sizeof(uint));
  if (tab == NULL) {
    exit(EXIT_FAILURE);
  }

  for (uint i = 0; i < cpt + 1; i++) tab[i] = colors_tab[i];
  free(colors_tab);
  col_tab->tab = tab;
  col_tab->tab_len = cpt;
  return col_tab;
}

/**
 * @brief This fonction test all the possibles solutions.
 * @param tab_colors an array of colors
 * @param nb_colors the colors number in game grid +1 (tab_colors length)
 * @param size_sol the solution length (number of moves)
 * @return one array of solutions
 * @pre @p tab is not NULL
 **/
solution* all_possibilities(uint tab_colors[], uint nb_colors, uint size_sol) {
  int nb_solutions = (int)pow(nb_colors, size_sol);
  solution* solutions = malloc(sizeof(solution) * nb_solutions);
  if (solutions == NULL) {
    exit(EXIT_FAILURE);
  }

  // we create all the possibilities
  for (int i = 0; i < nb_solutions; i++) {
    // we create one possibilities
    uint* x = malloc(sizeof(uint) * size_sol);
    if (x == NULL) {
      exit(EXIT_FAILURE);
    }
    int n = i;  // the solution number (solution index °~°. fist, second...)
    for (uint j = size_sol; j > 0; j--) {  // form size_sol-1 to 0
      int pv = (int)pow(nb_colors, j - 1);
      if (n / pv > 0) {
        x[j - 1] = tab_colors[(n / pv)];
        n = n - pv;  // n*(n/pv)
      } else {
        x[j - 1] = tab_colors[0];
      }
    }

    solutions[i] = create_solution(x, size_sol);
    free(x);
  }
  return solutions;
}

/**
 * @brief This fonction test all the possibles solutions.
 * @param nb_colors structure with tab of colors (tab_colors) in game grid and
 * tab_colors length the colors number in game grid +1
 * @param size_sol the solution length (number of moves)
 * @param g the game will be test
 * @param solution an unsigne int table for store solution
 * @param k is k length of solution in recurcive call
 * @param ltr is if solution is generate from right to left or left to right
 * @return if one solution as found or not
 * @pre @p nb_color_s is not NULL
 * @pre @p g is not NULL
 * @pre @p solution is not NULL
 **/
bool find_one_solution(nb_color_s* nb_colors, uint size_sol, game g,
                       uint* solution, uint k, bool ltr) {
  // On solution are completly create
  if (k == 0) {
    /* //Debug
    printf("comb :");
    for (uint i = 0; i < size_sol; i++) printf("%u", solution[i]);
    printf("\n"); //*/
    // check if solution work
    game_restart(g);
    if (ltr)
      for (int i = size_sol - 1; i >= 0; i--) {
        game_play_one_move(g, solution[i]);
        if (game_is_over(g)) {
          uint* tmp = calloc(size_sol, sizeof(uint));
          // revers solution
          uint j;
          for (j = 0; j < size_sol; j++) tmp[j] = solution[j];
          uint k = size_sol;
          for (j = 0; j < size_sol; j++) solution[--k] = tmp[j];
          free(tmp);
          return true;
        }
      }
    else
      for (uint i = 0; i < size_sol; i++) {
        game_play_one_move(g, solution[i]);
        if (game_is_over(g)) return true;
      }

    return false;
  }

  // Recurcive call with k-1 length for make all posible solutions with all
  // colors
  for (uint i = 0; i < nb_colors->tab_len; i++) {
    solution[size_sol - k] = nb_colors->tab[i];  // add color to end of solution
    if (find_one_solution(nb_colors, size_sol, g, solution, k - 1, ltr))
      return true;
  }
  return false;
}

/**
 * @brief This fonction write solution in file with a new line.
 * @param filename file will be generate with the solution
 * @param solution the string with the solution
 * @pre @p filename is not NULL
 * @pre @p solution is not NULL
 **/
void save_sol_in_file(char* filename, char* solution);
/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 * @return solution a struct with the solution or the msg "NO SOLUTION"
 */
solution find_one(game g) {
  solution the_solution = NULL;

  nb_color_s* nb_col = nb_color(g);
  uint nb_move = game_nb_moves_max(g);

  uint* sol = malloc(sizeof(uint) * nb_move);
  if (find_one_solution(nb_col, nb_move, g, sol, nb_move, true))
    the_solution = create_solution(sol, nb_move);

  free(nb_col->tab);
  free(nb_col);
  free(sol);
  game_delete(g);

  return the_solution;
}

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 * @return uint the number of solutions for the game g
 */
uint nb_sol(game g) {
  uint nb_sol = 0;

  nb_color_s* nb_col = nb_color(g);
  uint nb_move = game_nb_moves_max(g);

  solution* all_poss = all_possibilities(nb_col->tab, nb_col->tab_len, nb_move);

  for (uint i = 0; i < ((int)pow(nb_col->tab_len, nb_move)); i++) {
    uint* tab = int_solution(all_poss[i]);
    for (uint j = 0; j < len_solution(all_poss[i]); j++) {
      game_play_one_move(g, tab[j]);
      if (game_is_over(g)) {
        nb_sol++;
        break;
      }
    }
    free(tab);
    game_restart(g);
    delete_solution(all_poss[i]);
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
solution find_min(game g) {
  return find_one(g);  // pour ne pas avoir 0/100
}
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
    printf("nb sul is : %u\n", nb_sol(g));
  else if (!strcmp(argv[1], "FIND_MIN"))
    retsol = find_min(g);
  else {
    fprintf(stderr, "Error:  \"%s\" doesn't exist!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // try if retsol is NULL else we can write in the file
  if (retsol != NULL)
    printf("The solution : %s\n", string_solution(retsol));
  else
    printf("No solution\n");

  return EXIT_SUCCESS;
}
