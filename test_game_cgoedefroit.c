#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

/**
 * @brief Unite test for game_copy
 *
 * @return bool
 */
bool test_game_copy() {
  uint nbMaxHit = 13;

  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  // create new game
  game g = game_new(cells, nbMaxHit);

  // test if game has been create
  if (g == NULL) {
    fprintf(stderr, "Error: invalid new game!\n");

    return false;
  }

  // test of game_copy()
  game gc = game_copy(g);

  // copy test
  if (gc == NULL) {
    fprintf(stderr, "Error: invalid copy game!\n");

    game_delete(g);

    return false;
  }

  // copy of max move test
  if (game_nb_moves_max(gc) != game_nb_moves_max(g)) {
    fprintf(stderr, "Error: game and copy game max moves are not equal!\n");

    game_delete(g);
    game_delete(gc);

    return false;
  }

  // copy of nb current move test
  if (game_nb_moves_cur(gc) != game_nb_moves_cur(g)) {
    fprintf(stderr,
            "Error: game and copy game nb curent move are not equal!\n");

    game_delete(g);
    game_delete(gc);

    return false;
  }

  // copy of cells test
  for (int y = 0; y < game_height(g); y++)
    for (int x = 0; x < game_width(g); x++)
      if (game_cell_current_color(gc, x, y) !=
          game_cell_current_color(g, x, y)) {
        fprintf(stderr, "Error: game and copy game cells are not equal!\n");

        game_delete(g);
        game_delete(gc);

        return false;
      }

  // test of change table cell
  game_set_cell_init(g, 4, 4, BLUE);

  if (game_cell_current_color(g, 4, 4) != BLUE) {
    fprintf(stderr, "Error: invalid game set cell init!\n");

    game_delete(g);
    game_delete(gc);

    return false;
  }

  // test if cells has been copyed
  if (game_cell_current_color(gc, 4, 4) == game_cell_current_color(g, 4, 4)) {
    fprintf(stderr, "Error: game and copy game cells are not equal!\n");

    game_delete(g);
    game_delete(gc);

    return false;
  }

  game_delete(g);
  game_delete(gc);

  return true;
}

/**
 * @brief Unite test for game_delete
 *
 * @return bool
 */
bool test_game_delete() {
  // create new game
  game g = game_new_empty();
  if (g == NULL) {
    fprintf(stderr, "Error: invalid new empty game!\n");
    return false;
  }

  // delete game
  game_delete(g);

  return true;
}

/**
 * @brief Unite test for game_is_over
 *
 * @return bool
 */
bool test_game_is_over() {
  uint nbMaxHit = 12;

  color cells[SIZE * SIZE] = {
      0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0,
      1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
      1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1};

  // create new game
  game g = game_new(cells, nbMaxHit);

  // test if game has been create
  if (g == NULL) {
    fprintf(stderr, "Error: invalid new game!\n");

    return false;
  }

  // test game is over if game is not over
  if (game_is_over(g) == true) {
    fprintf(stderr, "Error: game is over when shouldn't be!\n");

    game_delete(g);

    return false;
  }

  // play 0
  game_play_one_move(g, 0);
  // play 1
  game_play_one_move(g, 1);
  // play 0
  game_play_one_move(g, 0);
  // play 1
  game_play_one_move(g, 1);

  // test game is not over if game is over
  if (game_is_over(g) == false) {
    fprintf(stderr, "Error: game is not over when it should be!\n");

    game_delete(g);

    return false;
  }

  game_delete(g);

  return true;
}

/**
 * @brief Unite test for game_restart
 *
 * @return bool
 */
bool test_game_restart() {
  uint nbMaxHit = 12;

  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  // create new game
  game g = game_new(cells, nbMaxHit);

  // test if game has been create
  if (g == NULL) {
    fprintf(stderr, "Error: invalid new game!\n");

    return false;
  }

  // change cells

  // play 1
  game_play_one_move(g, GREEN);
  // play 2
  game_play_one_move(g, BLUE);

  // test restart
  game_restart(g);

  // test if game cells is equal to initial game cells
  for (int y = 0; y < game_height(g); y++)
    for (int x = 0; x < game_width(g); x++)
      if (game_cell_current_color(g, x, y) != cells[x + SIZE * y]) {
        fprintf(stderr,
                "Error: game cells are not equal to initial game cells!\n");

        game_delete(g);

        return false;
      }

  // test if current moves is not reset
  if (game_nb_moves_cur(g) != 0) {
    fprintf(stderr, "Error: current moves has not correclly reset!\n");

    game_delete(g);

    return false;
  }

  // test if max moves is not change
  if (game_nb_moves_max(g) != nbMaxHit) {
    fprintf(stderr, "Error: invalid game nb max moves!\n");

    game_delete(g);

    return false;
  }

  game_delete(g);

  return true;
}

/**
 * @brief Unite test for game_new_ext
 *
 * @return bool
 */
bool test_game_new_ext() {
  color cells[4 * 8] = {0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1,
                        1, 1, 1, 3, 2, 0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2};
  color cellsw[5 * 7] = {0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1,
                         1, 3, 2, 0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 2};

  game g = game_new_ext(4, 8, cells, 11, false);
  // check if game are not create
  if (g == NULL) {
    fprintf(stderr, "Error: invalid new game!\n");
    return false;
  }

  game gw = game_new_ext(5, 7, cellsw, 6, true);

  // check if game are not create
  if (gw == NULL) {
    fprintf(stderr, "Error: invalid new game!\n");
    game_delete(g);
    return false;
  }

  // check if the number of max moves is correctly define
  if (game_nb_moves_max(g) != 11) {
    fprintf(stderr,
            "Error: new game number of max moves is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if game width is correctly define
  if (game_width(g) != 4) {
    fprintf(stderr, "Error: new game width is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if game height is correctly define
  if (game_height(g) != 8) {
    fprintf(stderr, "Error: new game height is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if game wrapping is correctly define
  if (game_is_wrapping(g)) {
    fprintf(stderr, "Error: new game wrapping is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if game wrapping is correctly define
  if (!game_is_wrapping(gw)) {
    fprintf(stderr, "Error: new game wrapping is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if game nb current moves is correctly define
  if (!game_nb_moves_cur(g)) {
    fprintf(stderr,
            "Error: new game nb current moves is not correctly define!\n");
    game_delete(g);
    game_delete(gw);
    return false;
  }

  // check if cells is correctly define
  for (uint y = 0; y < 8; y++)
    for (uint x = 0; x < 4; x++)
      if (game_cell_current_color(g, x, y) != cells[x + 4 * y]) {
        fprintf(stderr, "Error: cells of new game is not correctly define!\n");
        game_delete(g);
        game_delete(gw);
        return false;
      }

  for (uint y = 0; y < 8; y++)
    for (uint x = 0; x < 4; x++)
      if (game_cell_current_color(gw, x, y) != cellsw[x + 4 * y]) {
        fprintf(stderr, "Error: cells of new game is not correctly define!\n");
        game_delete(g);
        game_delete(gw);
        return false;
      }

  game_delete(g);
  game_delete(gw);
  return true;
}

int main(int argc, char const *argv[]) {
  bool ok = false;

  // in case if program is run without args
  if (argc == 1) {
    /* fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);*/

    ok = test_game_copy() && test_game_delete() && test_game_is_over() && test_game_restart() && test_game_restart();

  } else {
    // select test from args
    if (!strcmp(argv[1], "copy"))
      ok = test_game_copy();
    else if (!strcmp(argv[1], "delete"))
      ok = test_game_delete();
    else if (!strcmp(argv[1], "is_over"))
      ok = test_game_is_over();
    else if (!strcmp(argv[1], "restart"))
      ok = test_game_restart();
    else if (!strcmp(argv[1], "new_ext"))
      ok = test_game_restart();
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
