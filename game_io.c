#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#define MAXLINELEN 4096

/**
 * @brief take a line into a file of char
 * @param p_f an existing FILE
 * @param p_size the size 
 * @pre @p p_f != NULL
 * @return s the current line
 **/
char* read_next_line(FILE* p_f, long* p_size) {
  if (p_f == NULL) {
    fprintf (stderr,"Error with the file on the function read_next_line.\n");
    return NULL;
  }
  char* s = malloc(MAXLINELEN * sizeof(char));
  if(s==NULL) {
    fprintf (stderr, "Error : s is NULL on the function read_next_line.\n");
    return NULL;
  }
  long old_pos = ftell(p_f), len = 0;
  if(fgets(s, MAXLINELEN, p_f) != NULL) {
    len = ftell(p_f) - old_pos;
    if(s[len-1] == "\n") {
      s[len-1] = "\0";
      len--;
    }
    else {
      if(!feof(p_f)) {
      fprintf(stderr,"Line too long.\n");
      exit(EXIT_FAILURE);
      }
    }
    (*p_size)=len;
    return s;
  }
  free(s);
  return NULL;
}

/**
 * @brief turn a line of char into an array
 * @param line the already existing line from a file
 * @param p_size the size of the line
 * @return the array
 **/
long* convert_line(char* line,long* p_size) {
  long* arr = malloc((*p_size)*sizeof(long));
  if(arr == NULL) {
    fprinft (stderr, "Error : arr is NULL on the function convert_line.\n");
  }
  long arr_s=0;
  char * token = strtok(line," ");
  while(token != NULL) {
    char* endval = token;
    long val = strtol(token, &endval, 10);
    if ((*endval)=="\0") {
      arr[arr_s]=val;
      arr_s++;
    }
    else {
      free(arr);
      return NULL;
    }
    token = strtok(NULL, " ");
  }
  (*p_size)=arr_s;
  return arr;
}

/**
 * @brief print the array
 * @param arr the array from the line
 * @param s the size of the array
 **/
void treat(long* arr, long s) {
  while(s>0) {
    printf("%ld ",(*arr)+1);
    arr++;
    s--;
  }
  printf("\n");
}


game game_load(char* filename) {  //  A FINIR
  if (filename == NULL) {
    fprintf (stderr, "Incorrect file in the function game_load.\n");
    return NULL;
  }
  FILE* file_loaded = fopen(filename, "r");
  if (file_loaded == NULL) {
    fprintf(stderr,
            "Problem when opening file on the function 'game_loaded'.\n");
    return NULL;
  }
  long size = 0;
  char* line = read_next_line(file_loaded,&size);
  long* arr;
  while (line != NULL) {
    arr = convert_line(line,&size);
    treat(arr,size);
    line = read_next_line(file_loaded,&size);
  }
  int width = arr[0];
  int height = arr[1];
  int nb_moves_max = arr[2];
  char wrapping = arr[3];
  color *cells;
  bool is_wrap;
  if (wrapping = "N") {
    is_wrap = false;
  }
  if (wrapping = "S") {
    is_wrap = true;
  }
  else {
    fprintf(stderr, "Error with the swap choice on the file.");
    return NULL;
  }
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      cells = fgetc (file_loaded);
    }
  }
  fclose(file_loaded);
  return game_new_ext(width, height, cells, nb_moves_max, is_wrap);
}



void game_save(cgame g, char* name) {
  if (g == NULL || name == NULL) {
    printf("At least one of the pointers is invalid");
    exit(EXIT_FAILURE);
  }
  
  // Creation of the name of the file
  char* filename = malloc(strlen(name) + 4);
  strcat(filename, name);
  strcat(filename, ".rec");
  FILE* savefile = NULL;
  savefile = fopen(filename, "w");
  if (savefile == NULL) {
    printf("The file couldn't be created");
    exit(EXIT_FAILURE);
  }

  // Writting of the parameters of the game in the file
  fprintf(savefile, "%u %u %u %B\n", game_width(g), game_height(g),
          game_nb_moves_max(g), game_is_wrapping(g));
  // Writting of the table of the game in the file
  for (int y = 0; y < game_height(g); y++) {  //
    for (int x = 0; x < game_width(g); x++) {
      fprintf(savefile, "%u", game_cell_current_color(g, x, y));
      if (x != game_width(g)-1){
        fprintf(savefile," ");
      }
    }
    fprintf(savefile, "\n");
  }

  fclose(savefile);
}