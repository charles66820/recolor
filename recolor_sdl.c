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
  SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);
  SDL_RenderClear(ren);

  // Draw background image
  SDL_RenderCopy(ren, env->background, NULL, NULL);

  // Local vars
  int winW = SCREEN_WIDTH;
  int winH = SCREEN_HEIGHT;

  SDL_GetWindowSize(win, &winW, &winH);

  int xMarging = winW * 8 / 100;
  int yMarging = winH * 8 / 100;

  // Draw div rectangle
  int divW = winW - xMarging * 2;
  int divH = winH - yMarging * 2;

  SDL_Rect rec = {xMarging, yMarging, divW, divH};
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderDrawRect(ren, &rec);
  SDL_RenderFillRect(ren, &rec);

  // Draw line
  SDL_SetRenderDrawColor(ren, 42, 42, 42, 255);
  SDL_RenderDrawLine(ren, 0, winH - yMarging, winW, winH - yMarging);


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
