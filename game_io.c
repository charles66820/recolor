#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief load a new game from a file
 *
 * @param filename name of file with the save
 * @return game
 * @pre @p filename != NULL
 */
game game_load(char *filename) { return NULL; }

void game_save(cgame g, char *name) {
  if (g == NULL || name == NULL) {
    printf("At least one of the pointers is invalid");
    exit(EXIT_FAILURE);
  }

  // Creation of the name of the file
  char *filename = malloc(strlen(name) + 4);
  strcat(filename, name);
  strcat(filename, ".txt");
  FILE *savefile = NULL;
  savefile = fopen(filename, "w");
  if (savefile == NULL) {
    printf("The file couldn't be created");
    exit(EXIT_FAILURE);

  // Writting of the parameters of the game in the file
  fprintf(savefile, "%u %u %u %d\n", game_width(g), game_height(g),
          game_nb_moves_max(g), game_is_wrapping(g));
  // Writting of the table of the game in the file
  for (int y = 0; y < game_height(g); y++) {  //
    for (int x = 0; x < game_width(g); x++) {
      fprintf(savefile, "%u ", game_cell_current_color(g, x, y));
    }
    fprintf(savefile, "\n");
  }

  fclose(savefile);
}