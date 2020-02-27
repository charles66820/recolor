#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct solution_s {
  uint* tab;
  uint tab_len;
};

/**
 * @brief Check if pointer is null
 *
 * @param p pointer will be check
 * @param msg message will print if pointer is null
 */
static void check_pointer(const void* p, char* msg) {
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

static char int_to_char(int x) { return x + '0'; }

char* string_solution(solution sol) {
  check_pointer(sol, "sol parameter on the function string_solution is null.");
  char* string = malloc(sizeof(char) * sol->tab_len * 2);

  uint j = 0;
  for (uint i = 0; i < sol->tab_len - 1; i++) {
    if (sol->tab[i] >= 0 && sol->tab[i] <= 9) {
      string[j] = int_to_char(sol->tab[i]);
      if (i < sol->tab_len - 2) string[j + 1] = ' ';
    } else if (sol->tab[i] >= 10 && sol->tab[i] < 16) {
      string[j] = (char)(sol->tab[i] + 55);
      if (i < sol->tab_len - 2) string[j + 1] = ' ';
    }
    j += 2;
  }
  return string;
}

solution* create_solution(uint* tab, uint length) {
  solution* sol = malloc(sizeof(struct solution_s));
  check_pointer(sol, "sol parameter on the function create_solution is null.");
  (*sol)->tab = tab;
  (*sol)->tab_len = length;
  return sol;
}

void delete_solution(solution sol) {
  if (sol != NULL) {
    if (sol->tab != NULL) {
      free(sol->tab);
    }
    free(sol);
  }
}