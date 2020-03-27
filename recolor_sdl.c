#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL_model.h"

// Games assets
#define FONT "assets/Roboto-Regular.ttf"  // TEMP: see for multiple fonts
#define FONTSIZE 36
#define BACKGROUND "assets/nodejs.svg"  // TEMP: change with real bg
#define ICON "assets/129Magikarp.png"   // TEMP: change with real icon

struct Env_t {
  SDL_Texture* background;
  SDL_Surface* icon;
};

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]) {
  Env* env = malloc(sizeof(struct Env_t));

  // Load background texture
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if (!env->background) {
    ERROR("IMG_LoadTexture: %s\n", BACKGROUND);
    SDL_ShowSimpleMessageBox(0, "IMG_LoadTexture", SDL_GetError(), win);
  }

  // Load icon
  env->icon = IMG_Load(ICON);
  if (!env->icon) {
    ERROR("IMG_Load: %s\n", ICON);
    SDL_ShowSimpleMessageBox(0, "IMG_Load", SDL_GetError(), win);
  }

  // Set icon
  SDL_SetWindowIcon(win, env->icon);



  return env;
}

void render(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  // set background color
  SDL_SetRenderDrawColor(ren, 160, 160, 160, 255);
  SDL_RenderClear(ren);

  // Draw background
  SDL_RenderCopy(ren, env->background, NULL, NULL);

}

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  if (e->type == SDL_QUIT) {
    return true;
  }

  return false;
}

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  SDL_DestroyTexture(env->background);
  SDL_FreeSurface(env->icon);
  free(env);
}
