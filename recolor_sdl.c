#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL_model.h"

struct Env_t { };

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]) {
  Env* env = malloc(sizeof(struct Env_t));

  return env;
}

void render(SDL_Window* win, SDL_Renderer* ren, Env* env) { }

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  if (e->type == SDL_QUIT) {
    return true;
  }

  return false;
}

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  free(env);
}
