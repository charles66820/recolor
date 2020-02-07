#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
//$ clang-format -i test_game_vandrault.c
// tests//

/**
 * @brief Unite test for game_new
 *
 * @return bool
 */
bool test_game_new() {
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  game g1 = game_new(cells, 12);
  if (g1 == NULL) {  // testing if g1 is a valid pointer
    return false;
  }
  if (game_nb_moves_max(g1) != 12) {  // testing if the number of max moves is
                                      // the same as the one we entered
    game_delete(g1);
    return false;
  }
  if (sizeof(cells) !=
      SIZE * SIZE * sizeof(int)) {  // testing if the table is of the right size
    game_delete(g1);
    return false;
  }
  for (uint i = 0; i < game_height(g1) * game_width(g1);
       i += 1) {  // testing if the cells of the game are the same as the ones
                  // of the table
    if (game_cell_current_color(g1, i % 12, i / 12) != cells[i]) {
      game_delete(g1);
      return false;
    }
  }
  if (game_nb_moves_cur(g1) != 0) {
    game_delete(g1);
    return false;
  }
  game_play_one_move(g1, 2);
  if (game_nb_moves_cur(g1) != 1) {
    game_delete(g1);
    return false;
  }

  game_restart(g1);

  // cells for test all moves on game not wrapping
  color cellst[13][SIZE * SIZE] = {
      {0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2,
       0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells0
      {3, 3, 3, 2, 0, 2, 1, 0, 1, 0, 3, 0, 3, 3, 3, 1, 1, 1, 1, 3, 2,
       0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells1
      {1, 1, 1, 2, 0, 2, 1, 0, 1, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 3, 2,
       0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells2
      {3, 3, 3, 2, 0, 2, 3, 0, 1, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 2,
       0, 1, 0, 3, 0, 3, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 3, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells3
      {1, 1, 1, 2, 0, 2, 1, 0, 1, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
       0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2, 0, 3, 3, 2, 2, 1, 1, 0, 1, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 1, 1, 1, 1, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells4
      {0, 0, 0, 2, 0, 2, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
       0, 1, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 3, 3, 2, 2, 0, 0, 0, 0, 2,
       0, 0, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 0, 0, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells5
      {3, 3, 3, 2, 3, 2, 3, 3, 1, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 2,
       0, 1, 0, 3, 3, 3, 2, 3, 2, 3, 2, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2,
       3, 3, 3, 2, 2, 0, 2, 3, 2, 3, 3, 3, 3, 2, 3, 1, 0, 0, 0, 3, 3,
       3, 3, 3, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 3, 3, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 3, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 3, 3, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 3, 3, 3, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells6
      {1, 1, 1, 2, 1, 2, 1, 1, 1, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
       0, 1, 0, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0, 1, 1,
       1, 1, 1, 2, 1, 1, 2, 1, 3, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
       1, 3, 1, 3, 1, 1, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 1, 1, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 1, 1, 1, 1, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells7
      {0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
       0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2,
       0, 0, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 2, 0, 0, 2, 0, 3, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2,
       0, 3, 1, 3, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 0, 0, 0, 0, 2, 0, 0,
       0, 3, 0, 1, 3, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 1, 3, 3, 0, 0, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells8
      {1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
       1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2,
       1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 2, 1, 1, 2, 1, 3, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
       1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 3, 3, 1, 3, 1, 1, 1, 1, 2, 1, 1,
       1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 1, 1, 2, 2, 0, 2, 3, 1, 1, 1, 1, 2, 3, 1, 1},  // cells9
      {3, 3, 3, 2, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
       3, 3, 3, 3, 3, 3, 2, 3, 2, 3, 2, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2,
       3, 3, 3, 2, 2, 3, 2, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 2, 3, 3, 2, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
       2, 3, 2, 3, 3, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 3, 3, 3},  // cells10
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},  // cells11
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
      // cells12
  };

  // all moves for win game not wrapping
  color moves[12] = {3, 1, 3, 1, 0, 3, 1, 0, 1, 3, 2, 0};

  // test all moves on game not wrapping
  for (uint j = 0; j < 13; j++) {
    if (j) game_play_one_move(g1, moves[j - 1]);
    for (uint i = 0; i < game_height(g1) * game_width(g1); i += 1)
      if (game_cell_current_color(g1, i % 12, i / 12) != cellst[j][i]) {
        fprintf(stderr,
                "Error on play %d moves game cells are not equal to cells%d.\n",
                j, j);
        game_delete(g1);
        return false;
      }
  }

  game_delete(g1);
  g1 = game_new_ext(12, 12, cells, 12, true);

  // cells for test all moves on game with wrapping
  color cellstw[13][SIZE * SIZE] = {
      {0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2,
       0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells0
      {3, 3, 3, 2, 0, 2, 1, 0, 1, 0, 3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 2,
       0, 1, 3, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 3, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells1
      {1, 1, 1, 2, 0, 2, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2,
       0, 1, 1, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       1, 1, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 1, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 1, 1, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 1, 1, 1, 1, 2,
       2, 3, 2, 0, 0, 2, 2, 1, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1},  // cells2
      {2, 2, 2, 2, 0, 2, 2, 0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2,
       0, 2, 2, 2, 0, 2, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 2, 0, 3, 2,
       1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 2, 2, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
       2, 2, 2, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 2, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 2, 2, 2, 0, 0, 0, 3, 2, 3, 1, 0, 0, 2, 2, 2, 2, 2, 2,
       2, 3, 2, 0, 0, 2, 2, 2, 2, 3, 0, 2, 2, 2, 2, 3, 0, 2},  // cells3
      {3, 3, 3, 3, 0, 3, 3, 0, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
       0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 2, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3,
       1, 1, 1, 2, 2, 0, 3, 1, 3, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
       0, 1, 1, 2, 3, 3, 2, 1, 3, 3, 3, 3, 3, 3, 0, 0, 1, 3, 1, 1, 3,
       3, 3, 3, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
       1, 3, 0, 3, 3, 3, 0, 0, 0, 3, 2, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},  // cells4
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       1, 1, 1, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0,
       0, 1, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 1, 0,
       0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 1, 1,
       1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // cells5
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // cells6
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},  // cells7
      {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},  // cells8
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // cells9
  };

  // all moves for win game with wrapping
  color movesw[9] = {3, 1, 2, 3, 0, 1, 2, 3, 0};

  // test all moves on game not wrapping
  for (uint j = 0; j < 10; j++) {
    if (j) game_play_one_move(g1, movesw[j - 1]);
    for (uint i = 0; i < game_height(g1) * game_width(g1); i += 1)
      if (game_cell_current_color(g1, i % 12, i / 12) != cellstw[j][i]) {
        fprintf(stderr,
                "Error on play %d moves game wrapping cells are not equal to "
                "cells%d.\n",
                j, j);
        game_delete(g1);
        return false;
      }
  }

  game_delete(g1);  // deleting g1 to free the memory
  return true;
}

/**
 * @brief Unite test for game_new_empty
 *
 * @return bool
 */
bool test_game_new_empty() {
  game g = game_new_empty();
  if (g == NULL) {  // testing if g is a valid pointer
    return false;
  }
  if (game_nb_moves_max(g) != 0) {  // testing if the number of max moves is 0
    game_delete(g);
    return false;
  }
  if (game_nb_moves_cur(g) != 0) {  // testing if the number of current moves is 0
    game_delete(g);
    return false;
  }
  game_play_one_move(g, 0);
  for (uint i = 0; i < game_height(g) * game_width(g);
       i += 1) {  // testing if each cell of the game is equal to RED
    if (game_cell_current_color(g, i % 12, i / 12) != RED) {
      game_delete(g);
      return false;
    }
  }
  game_delete(g);  // deleting g to free the memory
  return true;
}

/**
 * @brief Unite test for game_set_cell_init
 *
 * @return bool
 */
bool test_game_set_cell_init() {
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  game g1 = game_new(cells, 12);
  if (g1 == NULL) {  // testing if g1 is a valid pointer
    return false;
  }
  game_play_one_move(g1, 2);
  game_set_cell_init(g1, 5, 8, 1);
  if (game_cell_current_color(g1, 5, 8) !=
      1) {  // testing if the color of the cell has been changed
    game_delete(g1);
    return false;
  }
  game_delete(g1);  // deleting g1 to free the memory
  return true;
}

/**
 * @brief Unite test for game_set_max_moves
 *
 * @return bool
 */
bool test_game_set_max_moves() {
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  game g1 = game_new(cells, 12);
  if (g1 == NULL) {  // testing if g1 is a valid pointer
    return false;
  }
  game_set_max_moves(g1, 14);
  if (g1 == NULL) {  // testing if g1 is still a valid pointer after changing
                     // the number of max moves
    return false;
  }
  if (game_nb_moves_max(g1) !=
      14) {  // testing if the number of max moves is changed
    game_delete(g1);
    return false;
  }

  // test if set nb max move work
  game_set_max_moves(g1, 15);
  if (game_nb_moves_max(g1) != 15) {
    fprintf(stderr, "Error: invalid game nb max moves!\n");
    game_delete(g1);
    return false;
  }

  game_delete(g1);  // deleting g1 to free the memory
  return true;
}

/**
 * @brief Unite test for game_height
 *
 * @return bool
 */
bool test_game_height(){
  uint nbMax = 12;
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, nbMax);
  if (g == NULL) {  // testing if g1 is a valid pointer
    return false;
  }
  if (game_height(g)<1){
    fprintf(stderr,"invalid height in g\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

/**
 * @brief Unite test for game_wrapping
 *
 * @return bool
 */
bool test_game_wrapping(){
  uint nbMax = 12;
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, nbMax);
  if (g == NULL) {  // testing if g1 is a valid pointer
    return false;
  }
  if (game_is_wrapping(g) != false){
    fprintf(stderr,"invalid wrapping in g\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

// main//

int main(int argc, char *argv[]) {
  bool ok = false;

  if (argc == 1) {
    /* fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE); */

    ok = test_game_new() && test_game_new_empty() &&
         test_game_set_cell_init() && test_game_set_max_moves() &&
         test_game_height() && test_game_wrapping();

  } else {
    if (!strcmp(argv[1], "new"))
      ok = test_game_new();
    else if (!strcmp(argv[1], "new_empty"))
      ok = test_game_new_empty();
    else if (!strcmp(argv[1], "set_cell_init"))
      ok = test_game_set_cell_init();
    else if (!strcmp(argv[1], "set_max_moves"))
      ok = test_game_set_max_moves();
    else if (!strcmp(argv[1], "height"))
      ok = test_game_height();
    else if (!strcmp(argv[1], "wrapping"))
      ok = test_game_wrapping();
    else {
      fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  }

  // print test result
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}