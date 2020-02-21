#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.h"

bool test_string_solution() {
  char tab[] = { '1';
  '2';
  '3';
  '4';
  '5';
  '6';
  '7';
  '8';
  '9';
  '10';
  '11';
  '12';
  '13';
  '14';
  '15';
}
uint length = 16;
solution sol = create_solution(tab, 16);
/*if (sol == NULL) {
  fprintf(stderr, "Error : invalid solution.\n");
  return false;
}
delete_solution(g);*/
return true;
}  // TO FINISH

int main(int argc, char const *argv[]) {
  bool ok = false;

  if (argc == 1) {
    /* fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE); */

    ok = test_game_nb_moves_max() && test_game_nb_moves_cur() &&
         test_game_cell_current_color() && test_game_play_one_move() &&
         test_game_width() && test_game_new_empty_ext();

  } else {
    if (!strcmp(argv[1], "game_nb_moves_max"))
      ok = test_game_nb_moves_max();
    else if (!strcmp(argv[1], "game_nb_moves_cur"))
      ok = test_game_nb_moves_cur();
    else if (!strcmp(argv[1], "game_cell_current_color"))
      ok = test_game_cell_current_color();
    else if (!strcmp(argv[1], "game_play_one_move"))
      ok = test_game_play_one_move();
    else if (!strcmp(argv[1], "game_width"))
      ok = test_game_width();
    else if (!strcmp(argv[1], "game_new_empty_ext"))
      ok = test_game_new_empty_ext();
    else {
      fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  }

  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}