#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SDL_model.h"
#include "game.h"
#include "game_io.h"
#include "game_rand.h"

// Games assets
#ifdef __WINDOWS__
// See for install dir
#endif
#ifdef __LINUX__
// See for install dir
#else
// Default dir
#endif

#define FONT_ROBOTO "assets/Roboto-Regular.ttf"
#define FONT_OPENDYSLEXIC "assets/OpenDyslexic-Regular.otf"
#define FONTSIZE 12
#define BACKGROUND "assets/background.png"
#define BUTTON_SPRITE "assets/button.png"
#define ICON "assets/icon.png"
#define SHADOWBOX0 "assets/shadowBox0.png"
#define SHADOWBOX1 "assets/shadowBox1.png"
#define SHADOWBOX2 "assets/shadowBox2.png"
#define SHADOWBOX3 "assets/shadowBox3.png"

typedef struct color_cell {
  SDL_Rect rect;
  color color;
} COLOR_Cell;

static SDL_Color getColorFromGameColor(color c) {
  switch (c) {
    case 0:
      return (SDL_Color){255, 0, 0, SDL_ALPHA_OPAQUE};
      break;
    case 1:
      return (SDL_Color){0, 255, 0, SDL_ALPHA_OPAQUE};
      break;
    case 2:
      return (SDL_Color){0, 0, 255, SDL_ALPHA_OPAQUE};
      break;
    case 3:
      return (SDL_Color){255, 255, 0, SDL_ALPHA_OPAQUE};
      break;
    case 4:
      return (SDL_Color){255, 0, 255, SDL_ALPHA_OPAQUE};
      break;
    case 5:
      return (SDL_Color){0, 255, 255, SDL_ALPHA_OPAQUE};
      break;
    case 6:
      return (SDL_Color){255, 153, 0, SDL_ALPHA_OPAQUE};
      break;
    case 7:
      return (SDL_Color){153, 51, 0, SDL_ALPHA_OPAQUE};
      break;
    case 8:
      return (SDL_Color){153, 204, 0, SDL_ALPHA_OPAQUE};
      break;
    case 9:
      return (SDL_Color){153, 0, 255, SDL_ALPHA_OPAQUE};
      break;
    case 10:
      return (SDL_Color){0, 153, 255, SDL_ALPHA_OPAQUE};
      break;
    case 11:
      return (SDL_Color){0, 255, 153, SDL_ALPHA_OPAQUE};
      break;
    case 12:
      return (SDL_Color){153, 255, 153, SDL_ALPHA_OPAQUE};
      break;
    case 13:
      return (SDL_Color){255, 153, 153, SDL_ALPHA_OPAQUE};
      break;
    case 14:
      return (SDL_Color){153, 153, 255, SDL_ALPHA_OPAQUE};
      break;
    case 15:
      return (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE};
      break;

    default:
      return (SDL_Color){0, 0, 0, SDL_ALPHA_OPAQUE};
      break;
  }
}

static SDL_Cursor* createPaintBucket(color c) {
  SDL_Color rgbaColor = getColorFromGameColor(c);

  // Define paint color
  Uint32 pxRgbColor = (rgbaColor.r << 24) + (rgbaColor.g << 16) +
                      (rgbaColor.b << 8) + (rgbaColor.a << 0);

  // Create painting bucket cursor with paint color
  Uint32 pixels[32 * 32] = {
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 1
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 2
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x000000FF,
      0x000000FF, 0x000000FF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 3
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 4
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 5
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 6
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x000000FF, 0x000000FF, 0xFFFFFFFF, 0x000000FF,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 7
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 8
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x000000FF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 9
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x000000FF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 10
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x000000FF, 0x000000FF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 11
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x000000FF, 0x000000FF, pxRgbColor, 0x000000FF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 12
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x000000FF, pxRgbColor, pxRgbColor, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 13
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x000000FF,
      pxRgbColor, pxRgbColor, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 14
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor,
      pxRgbColor, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 15
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor,
      0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 16
      0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor, pxRgbColor,
      0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 17
      0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor, pxRgbColor,
      0x000000FF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000,  // Row 18
      0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor, pxRgbColor,
      pxRgbColor, pxRgbColor, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF,
      0x00000000, 0x00000000,  // Row 19
      0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor, pxRgbColor,
      pxRgbColor, 0x000000FF, 0x000000FF, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000,  // Row 20
      0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor, pxRgbColor,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 21
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 22
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, pxRgbColor, pxRgbColor,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 23
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, pxRgbColor,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 24
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 25
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 26
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0xFFFFFFFF,
      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 27
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x000000FF, 0x000000FF, 0x000000FF, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 28
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 29
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 30
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 31
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
      0x00000000, 0x00000000,  // Row 32
  };

  // Create rgb surface with format rgba
  SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
      pixels, 32, 32, 32, 32 * 4, SDL_PIXELFORMAT_RGBA8888);

  // Create cursot with this format
  SDL_Cursor* cs = SDL_CreateColorCursor(surface, 6, 25);  // 2,17
  SDL_FreeSurface(surface);
  return cs;
}

typedef struct button {
  SDL_Rect rect;
  bool hover;
  bool pressed;
} BUTTON;

bool requestQuit(SDL_Window* win) {
  const SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quitter"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Annuler"},
  };

  const SDL_MessageBoxColorScheme colorScheme = {
      {{250, 250, 250}, {40, 40, 40}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}}};

  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_WARNING,
      win,
      "Quitter ?",
      "Vous êtes sur de vouloirs quitté, notre super jeu recolor ? :'(",
      SDL_arraysize(buttons),
      buttons,
      &colorScheme};

  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
    ERROR("SDL error", "Error: SDL_ShowMessageBox (%s)\n", SDL_GetError());

  if (buttonid == -1 || buttonid == 2) {
    return false;
  } else {
    return true;
  }
}

struct Env_t {
  bool allowBackground;
  bool allowCursor;
  bool allowDyslexic;
  bool allowTransparency;
  SDL_Texture* background;
  SDL_Cursor* cursor;
  SDL_Cursor* tempCursor;
  SDL_Surface* icon;
  SDL_Texture* button;
  TTF_Font* font;
  SDL_Surface* sShadowBox0;
  SDL_Surface* sShadowBox1;
  SDL_Surface* sShadowBox2;
  SDL_Surface* sShadowBox3;
  SDL_Texture* shadowBox0;
  SDL_Texture* shadowBox1;
  SDL_Texture* shadowBox2;
  SDL_Texture* shadowBox3;
  game g;
  COLOR_Cell* cells;
  BUTTON btnRestart;
  BUTTON btnQuit;
};

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]) {
  Env* env = malloc(sizeof(struct Env_t));
  if (!env) ERROR("Game error", "Error: malloc (Not enought memory)\n");

  // Settings
  env->allowBackground = true;
  env->allowCursor = true;
  env->allowDyslexic = false;
  env->allowTransparency = true;

  srand(time(0));

  // Init game
  if (argc == 2) {
    env->g = game_load(argv[1]);
    if (!env->g)
      ERROR("Game error", "Error on game load : The default game as load\n");
  }

  if (argc == 4) {
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int nb_moves_max = atoi(argv[3]);
    env->g = game_random_ext(width, height, nb_moves_max, 4, true);
  }
  if (argc == 5) {
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int nb_moves_max = atoi(argv[3]);
    int wrapping = atoi(argv[4]);
    if (wrapping == 'N') {
      env->g = game_random_ext(width, height, nb_moves_max, 4, false);
    } else if (wrapping == 'S') {
      env->g = game_random_ext(width, height, nb_moves_max, 4, true);
    } else {
      int nb_colors = atoi(argv[4]);
      env->g = game_random_ext(width, height, nb_moves_max, nb_colors, true);
    }
  }
  if (argc == 6) {
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int nb_moves_max = atoi(argv[3]);
    int nb_colors = atoi(argv[4]);
    int wrapping = atoi(argv[5]);
    if (wrapping == 'N') {
      env->g = game_random_ext(width, height, nb_moves_max, nb_colors, false);
    } else {
      env->g = game_random_ext(width, height, nb_moves_max, nb_colors, true);
    }
  }

  if (argc == 1 || !env->g) {  // if game is launch without arguments or
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
  if (env->allowBackground) {
    env->background = IMG_LoadTexture(ren, BACKGROUND);
    if (!env->background)
      ERROR("SDL error", "Error: IMG_LoadTexture (%s)\n", SDL_GetError());
  }

  // Load icon
  env->icon = IMG_Load(ICON);
  if (!env->icon) ERROR("SDL error", "Error: IMG_Load (%s)\n", SDL_GetError());

  // Load button texture
  env->button = IMG_LoadTexture(ren, BUTTON_SPRITE);
  if (!env->button)
    ERROR("SDL error", "Error: IMG_LoadTexture (%s)\n", SDL_GetError());

  // Load font
  env->font = TTF_OpenFont(env->allowDyslexic ? FONT_OPENDYSLEXIC : FONT_ROBOTO,
                           FONTSIZE);
  if (!env->font)
    ERROR("TTF error", "Error: TTF_OpenFont (%s)\n", SDL_GetError());

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

  // Init color grid cells
  env->cells =
      calloc(game_height(env->g) * game_width(env->g), sizeof(COLOR_Cell));

  // Init cursors
  if (env->allowCursor) {
    env->tempCursor = createPaintBucket(0);
    if (!env->tempCursor)
      ERROR("SDL error", "Error: createPaintBucket (%s)\n", SDL_GetError());
    env->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_SetCursor(env->cursor);
  }

  // Set buttons attribute to default value
  env->btnRestart.pressed = false;
  env->btnRestart.hover = false;
  env->btnQuit.pressed = false;
  env->btnQuit.hover = false;

  return env;
}

void render(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  // set background color
  SDL_SetRenderDrawColor(ren, 250, 250, 250, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren);

  // Local vars
  SDL_Texture* text;
  SDL_Surface* s;
  SDL_Rect rect;
  int winW = SCREEN_WIDTH;
  int winH = SCREEN_HEIGHT;
  int gameW = game_width(env->g);
  int gameH = game_height(env->g);

  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);

  SDL_GetWindowSize(win, &winW, &winH);

  int xWinPadding = winW * 4 / 100;
  int yWinPadding = winH * 4 / 100;

  int gridMaxW = winW - xWinPadding * 2;
  int gridMaxH = winH - yWinPadding * 4;

  int cellSize =
      gridMaxW / gameW > gridMaxH / gameH ? gridMaxH / gameH : gridMaxW / gameW;

  int gridW = cellSize * gameW;
  int gridH = cellSize * gameH;

  int gridXPadding = gridW * 3 / 100;
  int gridYPadding = gridH * 3 / 100;

  cellSize = gridMaxW / gameW > gridMaxH / gameH
                 ? (gridMaxH - gridYPadding * 2) / gameH
                 : (gridMaxW - gridXPadding * 2) / gameW;

  int gridX = (winW - gridW) / 2;
  int gridY = (winH - yWinPadding * 3 - gridH) / 2;

  // Draw background image
  if (env->allowBackground) {
    rect.x = 0;
    rect.y = 0;
    rect.w = winW;
    rect.h = winH - yWinPadding * 3;
    SDL_RenderCopy(ren, env->background, NULL, &rect);
  }

  // Draw rounded surface for the color grid
  if (env->allowTransparency) SDL_SetTextureAlphaMod(env->shadowBox1, 175);
  rect.x = gridX;
  rect.y = gridY;
  rect.w = gridW;
  rect.h = gridH;
  SDL_RenderCopy(ren, env->shadowBox1, NULL, &rect);

  // Create and draw grid cells
  for (int y = 0; y < gameH; y++)
    for (int x = 0; x < gameW; x++) {
      rect.x = cellSize * x + gridX + gridXPadding;
      rect.y = cellSize * y + gridY + gridYPadding;
      rect.w = cellSize;
      rect.h = cellSize;
      COLOR_Cell cell;
      cell.rect = rect;
      cell.color = game_cell_current_color(env->g, x, y);
      env->cells[(y * gameW) + x] = cell;

      SDL_Color c = getColorFromGameColor(cell.color);

      SDL_SetRenderDrawColor(ren, c.r, c.g, c.b,
                             env->allowTransparency ? 175 : SDL_ALPHA_OPAQUE);
      SDL_RenderFillRect(ren, &rect);
    }

  // Draw line
  SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(ren, 0, winH - yWinPadding * 3, winW,
                     winH - yWinPadding * 3);

  // Draw game stats
  TTF_SetFontStyle(env->font, TTF_STYLE_BOLD);
  char* msg = malloc((50 + 78 * 2) * sizeof(char));
  if (!msg) ERROR("Game error", "Error: malloc (Not enought memory)\n");
  // 50 char in format + max char in uint * 2 uint
  sprintf(msg, "Nombre de coups joués / coups max: %u / %u",
          game_nb_moves_cur(env->g), game_nb_moves_max(env->g));

  s = TTF_RenderUTF8_Blended(env->font, msg,
                             (SDL_Color){61, 133, 198, SDL_ALPHA_OPAQUE});
  text = SDL_CreateTextureFromSurface(ren, s);
  SDL_FreeSurface(s);
  rect.x = xWinPadding / 2;
  rect.y = winH - yWinPadding * 3;
  SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
  SDL_RenderCopy(ren, text, NULL, &rect);
  SDL_DestroyTexture(text);
  free(msg);

  // Draw when game is lose or win
  if (game_nb_moves_cur(env->g) >= game_nb_moves_max(env->g) &&
      !game_is_over(env->g)) {
    s = TTF_RenderUTF8_Blended(env->font, "DOMMAGE",
                               (SDL_Color){255, 0, 0, SDL_ALPHA_OPAQUE});
    goto prinLoseWin;
  }
  if (game_is_over(env->g)) {
    s = TTF_RenderUTF8_Blended(env->font, "BRAVO",
                               (SDL_Color){0, 255, 0, SDL_ALPHA_OPAQUE});
  prinLoseWin:
    text = SDL_CreateTextureFromSurface(ren, s);
    SDL_FreeSurface(s);
    rect.x = xWinPadding / 2;
    rect.y = winH - yWinPadding * 3 + rect.h;
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(ren, text, NULL, &rect);
    SDL_DestroyTexture(text);
  }

  // Draw buttons
  SDL_Rect rs = {0, 0, 0, 0};
  SDL_QueryTexture(env->button, NULL, NULL, &rs.w, &rs.h);
  rs.h = rs.h / 3;

  // Draw quit button
  env->btnQuit.rect.w = 150;
  env->btnQuit.rect.h = 40;
  env->btnQuit.rect.x = winW - xWinPadding / 2 - env->btnQuit.rect.w;
  env->btnQuit.rect.y = winH - yWinPadding * 3 + rect.h;
  // Select btn sprite state
  rs.y = env->btnQuit.pressed ? rs.h * 2 : env->btnQuit.hover ? rs.h : 0;
  SDL_RenderCopy(ren, env->button, &rs, &env->btnQuit.rect);
  // Daw button text
  s = TTF_RenderUTF8_Blended(env->font, "Quit",
                             (SDL_Color){230, 92, 0, SDL_ALPHA_OPAQUE});
  text = SDL_CreateTextureFromSurface(ren, s);
  SDL_FreeSurface(s);
  SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->btnQuit.rect.x + ((env->btnQuit.rect.w - rect.w) / 2);
  rect.y = env->btnQuit.rect.y + ((env->btnQuit.rect.h - rect.h) / 2);
  SDL_RenderCopy(ren, text, NULL, &rect);
  SDL_DestroyTexture(text);

  // Draw restart button
  env->btnRestart.rect.w = 150;
  env->btnRestart.rect.h = 40;
  env->btnRestart.rect.x =
      winW - xWinPadding / 2 - env->btnRestart.rect.w - env->btnQuit.rect.w;
  env->btnRestart.rect.y = winH - yWinPadding * 3 + rect.h;
  // Select btn sprite state
  rs.y = env->btnRestart.pressed ? rs.h * 2 : env->btnRestart.hover ? rs.h : 0;
  SDL_RenderCopy(ren, env->button, &rs, &env->btnRestart.rect);
  // Daw button text
  s = TTF_RenderUTF8_Blended(env->font, "Restart",
                             (SDL_Color){153, 51, 255, SDL_ALPHA_OPAQUE});
  text = SDL_CreateTextureFromSurface(ren, s);
  SDL_FreeSurface(s);
  SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->btnRestart.rect.x + ((env->btnRestart.rect.w - rect.w) / 2);
  rect.y = env->btnRestart.rect.y + ((env->btnRestart.rect.h - rect.h) / 2);
  SDL_RenderCopy(ren, text, NULL, &rect);
  SDL_DestroyTexture(text);
}

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  // Set buttons attributes to default value
  env->btnRestart.hover = false;
  env->btnQuit.hover = false;

  switch (e->type) {
    case SDL_QUIT:
      return requestQuit(win);
      break;
    case SDL_MOUSEMOTION:
    case SDL_FINGERMOTION:
      // When color cell is hover change cursor to this color
      if (env->allowCursor) {
        bool onGrid = false;
        for (uint i = 0; i < game_height(env->g) * game_width(env->g); i++)
          if (e->button.x > env->cells[i].rect.x &&
              e->button.y > env->cells[i].rect.y &&
              e->button.x <= env->cells[i].rect.x + env->cells[i].rect.w &&
              e->button.y <= env->cells[i].rect.y + env->cells[i].rect.h) {
            SDL_SetCursor(env->tempCursor);
            SDL_FreeCursor(env->cursor);
            env->cursor = createPaintBucket(env->cells[i].color);
            if (!env->cursor)
              ERROR("SDL error", "Error: createPaintBucket (%s)\n",
                    SDL_GetError());
            SDL_SetCursor(env->cursor);
            onGrid = true;
            break;
          }
        if (onGrid) break;
      }

      // When button restart is hover the hover attribute is set to true
      if ((e->button.x > env->btnRestart.rect.x &&
           e->button.y > env->btnRestart.rect.y &&
           e->button.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->button.y < env->btnRestart.rect.y + env->btnRestart.rect.h) ||
          (e->tfinger.x > env->btnRestart.rect.x &&
           e->tfinger.y > env->btnRestart.rect.y &&
           e->tfinger.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->tfinger.y < env->btnRestart.rect.y + env->btnRestart.rect.h)) {
        if (env->allowCursor) {
          SDL_FreeCursor(env->cursor);
          env->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
          SDL_SetCursor(env->cursor);
        }
        env->btnRestart.hover = true;
        break;
      }

      // When button quit is hover the hover attribute is set to true
      if ((e->button.x > env->btnQuit.rect.x &&
           e->button.y > env->btnQuit.rect.y &&
           e->button.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->button.y < env->btnQuit.rect.y + env->btnQuit.rect.h) ||
          (e->tfinger.x > env->btnQuit.rect.x &&
           e->tfinger.y > env->btnQuit.rect.y &&
           e->tfinger.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->tfinger.y < env->btnQuit.rect.y + env->btnQuit.rect.h)) {
        if (env->allowCursor) {
          SDL_FreeCursor(env->cursor);
          env->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
          SDL_SetCursor(env->cursor);
        }
        env->btnQuit.hover = true;
        break;
      }

      if (env->allowCursor) {
        SDL_FreeCursor(env->cursor);
        env->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
        SDL_SetCursor(env->cursor);
      }
      break;
    case SDL_MOUSEBUTTONUP:
    case SDL_FINGERUP:
      // When color cell is clicked this color is play
      for (uint i = 0; i < game_height(env->g) * game_width(env->g); i++)
        if ((e->button.button == SDL_BUTTON_LEFT &&
             e->button.x > env->cells[i].rect.x &&
             e->button.y > env->cells[i].rect.y &&
             e->button.x <= env->cells[i].rect.x + env->cells[i].rect.w &&
             e->button.y <= env->cells[i].rect.y + env->cells[i].rect.h) ||
            (e->tfinger.x > env->cells[i].rect.x &&
             e->tfinger.y > env->cells[i].rect.y &&
             e->tfinger.x <= env->cells[i].rect.x + env->cells[i].rect.w &&
             e->tfinger.y <= env->cells[i].rect.y + env->cells[i].rect.h))
          if (env->cells[0].color != env->cells[i].color)
            game_play_one_move(env->g, env->cells[i].color);

      // When button restart is clicked the game is restart
      if ((e->button.button == SDL_BUTTON_LEFT &&
           e->button.x > env->btnRestart.rect.x &&
           e->button.y > env->btnRestart.rect.y &&
           e->button.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->button.y < env->btnRestart.rect.y + env->btnRestart.rect.h) ||
          (e->tfinger.x > env->btnRestart.rect.x &&
           e->tfinger.y > env->btnRestart.rect.y &&
           e->tfinger.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->tfinger.y < env->btnRestart.rect.y + env->btnRestart.rect.h))
        game_restart(env->g);

      // When button quit is clicked the game is quit
      if ((e->button.button == SDL_BUTTON_LEFT &&
           e->button.x > env->btnQuit.rect.x &&
           e->button.y > env->btnQuit.rect.y &&
           e->button.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->button.y < env->btnQuit.rect.y + env->btnQuit.rect.h) ||
          (e->tfinger.x > env->btnQuit.rect.x &&
           e->tfinger.y > env->btnQuit.rect.y &&
           e->tfinger.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->tfinger.y < env->btnQuit.rect.y + env->btnQuit.rect.h)) {
        env->btnQuit.pressed = false;
        return requestQuit(win);
      }

      // Set buttons pressed attribute to default value
      env->btnRestart.pressed = false;
      env->btnQuit.pressed = false;
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_FINGERDOWN:
      // When button restart is pressed the pressed attribute is set to true
      if ((e->button.button == SDL_BUTTON_LEFT &&
           e->button.x > env->btnRestart.rect.x &&
           e->button.y > env->btnRestart.rect.y &&
           e->button.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->button.y < env->btnRestart.rect.y + env->btnRestart.rect.h) ||
          (e->tfinger.x > env->btnRestart.rect.x &&
           e->tfinger.y > env->btnRestart.rect.y &&
           e->tfinger.x < env->btnRestart.rect.x + env->btnRestart.rect.w &&
           e->tfinger.y < env->btnRestart.rect.y + env->btnRestart.rect.h))
        env->btnRestart.pressed = true;
      // When button quit is pressed the pressed attribute is set to true
      if ((e->button.button == SDL_BUTTON_LEFT &&
           e->button.x > env->btnQuit.rect.x &&
           e->button.y > env->btnQuit.rect.y &&
           e->button.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->button.y < env->btnQuit.rect.y + env->btnQuit.rect.h) ||
          (e->tfinger.x > env->btnQuit.rect.x &&
           e->tfinger.y > env->btnQuit.rect.y &&
           e->tfinger.x < env->btnQuit.rect.x + env->btnQuit.rect.w &&
           e->tfinger.y < env->btnQuit.rect.y + env->btnQuit.rect.h))
        env->btnQuit.pressed = true;
      break;
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym) {
        case SDLK_r:
          game_restart(env->g);
          break;
        case SDLK_q:
          return requestQuit(win);
          break;
        case SDLK_s:
          game_save(env->g, "data/quickSave.rec");
          break;
        default:
          break;
      }
      break;

    default:
      break;
  }

  return false;
}

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env) {
  if (env->allowBackground) SDL_DestroyTexture(env->background);
  if (env->allowCursor) SDL_FreeCursor(env->cursor);
  if (env->allowCursor) SDL_FreeCursor(env->tempCursor);
  SDL_FreeSurface(env->icon);
  SDL_DestroyTexture(env->button);
  TTF_CloseFont(env->font);
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
