#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
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

typedef struct color_cell {
  SDL_Rect rect;
  color color;
} COLOR_Cell;

void freeColorCell(COLOR_Cell* cell) {
  if (cell) {
    //if (cell->rect) SDL_free(cell->rect);
    free(cell);
  }
}

SDL_Color getColorFromGameColor(color c) {
  switch (c) {
    case 0:
      return (SDL_Color){255, 0, 0, 1};
      break;
    case 1:
      return (SDL_Color){0, 255, 0, 1};
      break;
    case 2:
      return (SDL_Color){0, 0, 255, 1};
      break;
    case 3:
      return (SDL_Color){255, 255, 0, 1};
      break;
    case 4:
      return (SDL_Color){255, 0, 255, 1};
      break;
    case 5:
      return (SDL_Color){0, 255, 255, 1};
      break;
    case 6:
      return (SDL_Color){255, 153, 0, 1};
      break;
    case 7:
      return (SDL_Color){255, 0, 153, 1};
      break;
    case 8:
      return (SDL_Color){153, 255, 0, 1};
      break;
    case 9:
      return (SDL_Color){153, 0, 255, 1};
      break;
    case 10:
      return (SDL_Color){0, 153, 255, 1};
      break;
    case 11:
      return (SDL_Color){0, 255, 153, 1};
      break;
    case 12:
      return (SDL_Color){153, 255, 153, 1};
      break;
    case 13:
      return (SDL_Color){255, 153, 153, 1};
      break;
    case 14:
      return (SDL_Color){153, 153, 255, 1};
      break;
    case 15:
      return (SDL_Color){255, 255, 255, 1};
      break;

    default:
      return (SDL_Color){0, 0, 0, 1};
      break;
  }
}

typedef struct button {
  SDL_Rect rect;
  color color;
  bool pressed;
  bool clicked;
} BUTTON;

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
  COLOR_Cell** cells;
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
  if (!env->background)
    ERROR("SDL error", "Error: IMG_LoadTexture (%s)\n", SDL_GetError());

  // Load icon
  env->icon = IMG_Load(ICON);
  if (!env->icon) ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());

  // Load shadows
  env->sShadowBox0 = IMG_Load(SHADOWBOX0);
  if (!env->sShadowBox0)
    ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());
  env->shadowBox0 = SDL_CreateTextureFromSurface(ren, env->sShadowBox0);

  env->sShadowBox1 = IMG_Load(SHADOWBOX1);
  if (!env->sShadowBox1)
    ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());
  env->shadowBox1 = SDL_CreateTextureFromSurface(ren, env->sShadowBox1);

  env->sShadowBox2 = IMG_Load(SHADOWBOX2);
  if (!env->sShadowBox2)
    ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());
  env->shadowBox2 = SDL_CreateTextureFromSurface(ren, env->sShadowBox2);

  env->sShadowBox3 = IMG_Load(SHADOWBOX3);
  if (!env->sShadowBox3)
    ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());
  env->shadowBox3 = SDL_CreateTextureFromSurface(ren, env->sShadowBox3);

  // Set icon
  SDL_SetWindowIcon(win, env->icon);

  env->cells =
      calloc(game_height(env->g) * game_width(env->g), sizeof(COLOR_Cell*));

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
  int gameW = game_width(env->g);
  int gameH = game_height(env->g);

  SDL_GetWindowSize(win, &winW, &winH);

  int xWinPadding = winW * 8 / 100;
  int yWinPadding = winH * 4 / 100;

  int gridPadding = 18;

  int gridMaxW = winW - xWinPadding * 2;
  int gridMaxH = winH - yWinPadding * 4;

  int cellSize =
      gridMaxW / gameW > gridMaxH / gameH ? gridMaxH / gameH : gridMaxW / gameW;

  int gridW = cellSize * gameW;
  int gridH = cellSize * gameH;

  cellSize = gridMaxW / gameW > gridMaxH / gameH
                 ? (gridMaxH - gridPadding * 2) / gameH
                 : (gridMaxW - gridPadding * 2) / gameW;

  int gridX = (winW - gridW) / 2;
  int gridY = (winH - yWinPadding * 3 - gridH) / 2;

  // Draw rounded surface for the color grid
  SDL_Rect rect = {gridX, gridY, gridW, gridH};
  SDL_RenderCopy(ren, env->shadowBox1, NULL, &rect);

  // Draw grid

  // Remove last cells
  for (uint i = 0; i < game_height(env->g) * game_width(env->g); i++)
    freeColorCell(env->cells[i]);

  // Create new cells
  for (int y = 0; y < gameH; y++)
    for (int x = 0; x < gameW; x++) {
      // SDL_Rect* rect = SDL_malloc(sizeof(SDL_Rect));
      rect.x = cellSize * x + gridX + gridPadding;
      rect.y = cellSize * y + gridY + gridPadding;
      rect.w = cellSize;
      rect.h = cellSize;
      COLOR_Cell* cell = malloc(sizeof(COLOR_Cell));
      cell->rect = rect;
      cell->color = game_cell_current_color(env->g, x, y);
      env->cells[(y * gameW) + x] = cell;

      SDL_Color c = getColorFromGameColor(cell->color);

      SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, 200);
      SDL_RenderFillRect(ren, &rect);
    }

  // Draw line
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderDrawLine(ren, 0, winH - yWinPadding * 3, winW,
                     winH - yWinPadding * 3);
}

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  if (e->type == SDL_QUIT) {
    return true;
  }
  if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_FINGERUP) {
    for (uint i = 0; i < game_height(env->g) * game_width(env->g); i++)
      if (e->button.button == SDL_BUTTON_LEFT &&
          e->button.x > env->cells[i]->rect.x &&
          e->button.y > env->cells[i]->rect.y &&
          e->button.x < env->cells[i]->rect.x + env->cells[i]->rect.w &&
          e->button.y < env->cells[i]->rect.y + env->cells[i]->rect.h) {
        game_play_one_move(env->g, env->cells[i]->color);
      } else if (e->tfinger.x > env->cells[i]->rect.x &&
          e->tfinger.y > env->cells[i]->rect.y &&
          e->tfinger.x < env->cells[i]->rect.x + env->cells[i]->rect.w &&
          e->tfinger.y < env->cells[i]->rect.y + env->cells[i]->rect.h)
        game_play_one_move(env->g, env->cells[i]->color);
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
  free(env->cells);
  game_delete(env->g);
  free(env);
}
