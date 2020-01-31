#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>

game game_load(char* filename) {  //  A FINIR
  if (filename == NULL) {
    return NULL;
  }
  FILE* file_loaded = fopen(filename, "r");
  if (file_loaded == NULL) {
    fprintf(stderr,
            "Problem when opening file on the function 'game_loaded'.\n");
    return NULL;
  }
  char* c;
  uint w;
  uint h;
  uint nb_max;
  bool wrapping;
  for (uint i = 0; i <= 4; i++) {
    fscanf(file_loaded, "%s", c);
    int w = atoi(c);
    ftell(file_loaded);
  }

  fclose(file_loaded);
  return;
}

void game_save(cgame g, char* name) {
  if (g == NULL || name == NULL) {
    printf("At least one of the pointers is invalid");
    exit(EXIT_FAILURE);
  }
  // Creation of the name of the file
  char* filename = malloc(strlen(name) + 4);
  strcat(filename, name);
  strcat(filename, ".txt");
  FILE* savefile = NULL;
  savefile = fopen(filename, "w");
  if (savefile == NULL) {
    printf("The file couldn't be created");
    exit(EXIT_FAILURE);
  }

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