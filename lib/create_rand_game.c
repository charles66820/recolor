#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"
#include "game_rand.h"
#include "create_rand_game.h"


game create_rand_game(int argc, char* argv[]){
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int nb_moves_max = atoi(argv[3]);
    int nb_colors = 4;
    bool wrapping = false;
    game g = NULL;
    if (width <= 0 || height <= 0 || nb_moves_max <= 0)
      fprintf(stderr, "Invalid parameters. Loading default game...\n");
    else if (argc == 4)
      g = game_random_ext(width, height, nb_moves_max, nb_colors, wrapping);
    else if (argc == 5) {
      if (argv[4][0] == 'N')
        wrapping = false;
      else if (argv[4][0] == 'S')
        wrapping = true;
      else
        nb_colors = atoi(argv[4]);
      if (nb_colors >= 2 && nb_colors < 17)
        g = game_random_ext(width, height, nb_moves_max, nb_colors, wrapping);
      else
        fprintf(stderr, "Invalid parameters. Loading default game...\n");
    } else if (argc == 6) {
      nb_colors = atoi(argv[4]);
      if (nb_colors >= 2 && nb_colors < 17 &&
          (argv[5][0] == 'N' || argv[5][0] == 'S'))
        g = game_random_ext(width, height, nb_moves_max, nb_colors,
                            argv[5][0] == 'S');
      else
        fprintf(stderr, "Invalid parameters. Loading default game...\n");
    }
    return g;
}