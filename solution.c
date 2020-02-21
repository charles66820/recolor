#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct solution_s {
  uint* tab;
  uint tab_len;
};

void check_pointer(const void* p, char* msg) {
  if (p == NULL) {
    if (msg == NULL)
      fprintf(stderr, "Null pointer error.\n");
    else
      fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
  }
}

uint len_solution(solution sol) {
  check_pointer(sol, "sol parameter on the function len_solution is null.");
  uint length = sol->tab_len;
  return length;
}

char int_to_char(int x) { return x + '0'; }

char* string_solution(solution sol) {
  check_pointer(sol, "sol parameter on the function string_solution is null.");
  char* string;
  for (uint i = 0; i < sol->tab_len; i++) {
    if (int_to_char(sol->tab[i]) >= 0 && int_to_char(sol->tab[i]) <= 9) {
      string[i] = int_to_char(sol->tab[i])
    } else if (int_to_char(sol->tab[i]) >= 10 &&
               int_to_char(sol->tab[i]) < 16) {
      string[i] = (char)(sol->tab[i] + 55)
    }
  }
  return string;
}

solution create_solution(uint* tab, uint length) {
  solution sol = malloc(sizeof(struct solution_s));
  check_pointer(sol, "sol parameter on the function create_solution is null.");
  sol->tab = tab;
  sol->tab_len = length;
  return sol;
}

void delete_solution(solution sol) {
  if (sol != NULL) {
    if (sol->tab != NULL) {
      for (uint i = 0; i < sol->tab_len; i++) {
        free(sol->tab[i]);
      }
      free(sol->tab);
    }
    if (sol->tab_len != NULL) {
      free(sol->tab_len);
    }
  }
}