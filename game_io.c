#define _GNU_SOURCE
#include "game.h"
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * @brief turn a line of char into an array
 * @param line the already existing line from a file
 * @param p_size the size of the line
 * @return the array
 **/
char** convert_line(char* line, size_t* p_size) {
  char** arr = malloc(*p_size * sizeof(char*));
  if (arr == NULL) {
    fprintf(stderr,
            "Error : Not enough memory on the function convert_line.\n");
    return NULL;
  }

  uint arr_s = 0;
  char* token = strtok(line, " ");
  char* iarr;
  while (token != NULL) {
    iarr = malloc((strlen(token) + 1) * sizeof(char));
    if (iarr == NULL) {
      fprintf(stderr,
              "Error : Not enough memory on the function convert_line.\n");
      for (uint i = 0; i < arr_s; i++) free(arr[i]);
      free(arr);
      return NULL;
    }
    strcpy(iarr, token);
    arr[arr_s] = iarr;
    arr_s++;
    token = strtok(NULL, " ");
  }

  (*p_size) = arr_s;
  return arr;
}

game game_load(char* filename) {
  if (filename == NULL) {
    fprintf(stderr, "Incorrect file in the function game_load.\n");
    return NULL;
  }

  FILE* file_loaded = fopen(filename, "r");
  if (file_loaded == NULL) {
    fprintf(stderr,
            "Problem when opening file on the function 'game_loaded'.\n");
    return NULL;
  }

  char* row = NULL;
  size_t len = 0;
  size_t read;

  // load first row
  read = getline(&row, &len, file_loaded);
  if (row[read - 1] == '\n') {
    row[read - 1] = '\0';
    read--;
  }

  // convert the string into a array of char
  char** arr = convert_line(row, &read);
  if (arr == NULL) {
    free(row);
    fclose(file_loaded);
    return NULL;
  }

  // affect the char from the array into int local var via atoi function
  int width = atoi(arr[0]);
  int height = atoi(arr[1]);
  int nb_moves_max = atoi(arr[2]);
  char wrapping = *arr[3];

  // free the array
  for (uint i = 0; i < read; i++) free(arr[i]);
  free(arr);
  free(row);
  row = NULL;

  bool is_wrap;
  if (wrapping == 'N') {
    is_wrap = false;
  } else if (wrapping == 'S') {
    is_wrap = true;
  } else {
    fprintf(stderr, "Error with the swap choice on the file.\n");
    fclose(file_loaded);
    return NULL;
  }

  // load cells
  color* cells = malloc(width * height * sizeof(color));
  if (cells == NULL) {
    fprintf(stderr, "Not enough memory on the function game_load.\n");
    return NULL;
  }
  uint h = 0;
  while ((read = getline(&row, &len, file_loaded)) != -1) {
    if (row[read - 1] == '\n') {
      row[read - 1] = '\0';
      read--;
    }

    arr = convert_line(row, &read);
    if (arr == NULL) {
      free(row);
      free(cells);
      fclose(file_loaded);
      return NULL;
    }

    if (read != width) {
      fprintf(stderr, "Incorrect cells width in the function game_load.\n");
      for (uint i = 0; i < read; i++) free(arr[i]);
      free(arr);
      free(row);
      free(cells);
      fclose(file_loaded);
      return NULL;
    }

    if (h >= height) {
      fprintf(stderr, "Incorrect cells height in the function game_load.\n");
      for (uint i = 0; i < read; i++) free(arr[i]);
      free(arr);
      free(row);
      free(cells);
      fclose(file_loaded);
      return NULL;
    }

    for (uint j = 0; j < read; j++) cells[(h * width) + j] = atoi(arr[j]);

    for (uint i = 0; i < read; i++) free(arr[i]);
    free(arr);

    free(row);
    row = NULL;

    h++;
  }
  free(row);

  fclose(file_loaded);
  game g = game_new_ext(width, height, cells, nb_moves_max, is_wrap);
  free(cells);
  return g;
}

void game_save(cgame g, char* name) {
  if (g == NULL || name == NULL) {
    printf("At least one of the pointers is invalid\n");
    exit(EXIT_FAILURE);
  }

  // Creation of the name of the file
  uint filenamelen = (uint)strlen(name) + 4;
  char* filename = malloc(sizeof(char*) * filenamelen);
  if (filename == NULL) {
    printf("Not enough memory!\n");
    exit(EXIT_FAILURE);
  }
  strcpy(filename, name);

  // if file path contain folder
  char* dir = malloc(sizeof(char*) * filenamelen);
  if (dir == NULL) {
    printf("Not enough memory!\n");
    free(filename);
    exit(EXIT_FAILURE);
  }
  strcpy(dir, filename);
  strcat(filename, ".rec");

  dirname(dir);
  if (strcmp(".", dir)) {
    char* mkcmd = malloc(sizeof(char*) * filenamelen);
    if (mkcmd == NULL) {
      printf("Not enough memory!\n");
      free(filename);
      free(dir);
      exit(EXIT_FAILURE);
    }
    sprintf(mkcmd, "mkdir -p %s", dir);
    system(mkcmd);
    free(mkcmd);
  }
  free(dir);

  FILE* savefile = NULL;
  savefile = fopen(filename, "w");
  if (savefile == NULL) {
    printf("The file couldn't be created\n");
    free(filename);
    exit(EXIT_FAILURE);
  }
  free(filename);

  // Writting of the parameters of the game in the file
  fprintf(savefile, "%u %u %u %c\n", game_width(g), game_height(g),
          game_nb_moves_max(g), game_is_wrapping(g) ? 'S' : 'N');
  // Writting of the table of the game in the file
  for (int y = 0; y < game_height(g); y++) {  //
    for (int x = 0; x < game_width(g); x++) {
      fprintf(savefile, "%u", game_cell_current_color(g, x, y));
      if (x != game_width(g) - 1) {
        fprintf(savefile, " ");
      }
    }
    fprintf(savefile, "\n");
  }

  fclose(savefile);
}