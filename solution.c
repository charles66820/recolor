#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct solution_s {
  uint* tab;
  uint tab_len;
};

uint solution_len(solution sol) {
  uint length = sol->tab_len;
  return length;
}

char* solution_string(solution sol) {
  char* string;
  for (uint i = 0; i < sol->tab_len; i++) {
    sprintf(string, "%d", sol->tab[i]);
  }
  return string;
}

solution create_solution(uint* tab, uint length) {
  solution sol = malloc(sizeof(struct solution_s));
  sol->tab = tab;
  sol->tab_len = length;
  return sol;
}

void delete_solution(solution sol);