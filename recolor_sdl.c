#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_model.h"
#include "game.h"
#include "game_io.h"

// Games assets
#define FONT "assets/Roboto-Regular.ttf"  // TEMP: see for multiple fonts
#define FONTSIZE 36
#define BACKGROUND "assets/nodejs.svg"  // TEMP: change with real bg
#define ICON "assets/129Magikarp.png"   // TEMP: change with real icon
#define SHADOWBOX0 "assets/shadowBox0.png"
#define SHADOWBOX1 "assets/shadowBox1.png"
#define SHADOWBOX2 "assets/shadowBox2.png"
#define SHADOWBOX3 "assets/shadowBox3.png"

struct Env_t {
  SDL_Texture* background;
  SDL_Surface* icon;
  SDL_Surface* sShadowBox0;
  SDL_Surface* sShadowBox1;
  SDL_Surface* sShadowBox2;
  SDL_Surface* sShadowBox3;
  SDL_Texture* shadowBox0;
  SDL_Texture* shadowBox1;
  SDL_Texture* shadowBox2;
  SDL_Texture* shadowBox3;
  game g;
};

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]) {
  Env* env = malloc(sizeof(struct Env_t));

  // Init game
  if (argc > 1) {
    env->g = game_load(argv[1]);
    if (env->g == NULL)
      ERROR("Game error", "Error on game load : The default game as load\n");
  }

  if (argc == 1 || env->g == NULL) {  // if game is launch without arguments or
                                      // if game is null we create new game
    int nbMaxHit = 12;

    color cells[SIZE * SIZE] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

    // Create new game
    env->g = game_new(cells, nbMaxHit);
  }

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

  // Load shadows
  env->sShadowBox0 = IMG_Load(SHADOWBOX0);
  if (!env->sShadowBox0) {
    ERROR("IMG_Load: %s\n", ICON);
    SDL_ShowSimpleMessageBox(0, "IMG_Load", SDL_GetError(), win);
  }
  env->shadowBox0 = SDL_CreateTextureFromSurface(ren, env->sShadowBox0);

  env->sShadowBox1 = IMG_Load(SHADOWBOX1);
  if (!env->sShadowBox1) {
    ERROR("IMG_Load: %s\n", ICON);
    SDL_ShowSimpleMessageBox(0, "IMG_Load", SDL_GetError(), win);
  }
  env->shadowBox1 = SDL_CreateTextureFromSurface(ren, env->sShadowBox1);

  env->sShadowBox2 = IMG_Load(SHADOWBOX2);
  if (!env->sShadowBox2) {
    ERROR("IMG_Load: %s\n", ICON);
    SDL_ShowSimpleMessageBox(0, "IMG_Load", SDL_GetError(), win);
  }
  env->shadowBox2 = SDL_CreateTextureFromSurface(ren, env->sShadowBox2);

  env->sShadowBox3 = IMG_Load(SHADOWBOX3);
  if (!env->sShadowBox3) {
    ERROR("IMG_Load: %s\n", ICON);
    SDL_ShowSimpleMessageBox(0, "IMG_Load", SDL_GetError(), win);
  }
  env->shadowBox3 = SDL_CreateTextureFromSurface(ren, env->sShadowBox3);

  // Set icon
  SDL_SetWindowIcon(win, env->icon);

  return env;
}

void render(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  // set background color
  SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);
  SDL_RenderClear(ren);

  // Draw background image
  // SDL_RenderCopy(ren, env->background, NULL, NULL);

  // Local vars
  int winW = SCREEN_WIDTH;
  int winH = SCREEN_HEIGHT;

  SDL_GetWindowSize(win, &winW, &winH);

  int xMarging = winW * 8 / 100;
  int yMarging = winH * 4 / 100;

  // Draw rounded surface for the color grid
  int gridMaxW = winW - xMarging * 2;
  int gridMaxH = winH - yMarging * 4;

  int gridSize = gridMaxW > gridMaxH ? gridMaxH : gridMaxW;

  SDL_Rect rec = {(winW - gridSize) / 2, (winH - yMarging * 3 - gridSize) / 2,
                  gridSize, gridSize};
  SDL_RenderCopy(ren, env->shadowBox1, NULL, &rec);

  // Draw grid
  // SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  // SDL_RenderDrawRect(ren, &rec);
  // SDL_RenderFillRect(ren, &rec);

  // Draw line
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderDrawLine(ren, 0, winH - yMarging * 3, winW, winH - yMarging * 3);
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
  SDL_FreeSurface(env->sShadowBox0);
  SDL_FreeSurface(env->sShadowBox1);
  SDL_FreeSurface(env->sShadowBox2);
  SDL_FreeSurface(env->sShadowBox3);
  SDL_DestroyTexture(env->shadowBox0);
  SDL_DestroyTexture(env->shadowBox1);
  SDL_DestroyTexture(env->shadowBox2);
  SDL_DestroyTexture(env->shadowBox3);
  game_delete(env->g);
  free(env);
}
