#include "SDL_error.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "window.h"
#include "defs.h"

Window window;

void throwError(char component[]) { //probably leaks memory, fuck the user for having a shitty system :p
  printf("Failed to initialise %s! Error details: %s", component, SDL_GetError());
  exit(1);
}

void initialise(void) {
  // set up

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throwError("SDL VIDEO");
  }

  int rendererFlags = SDL_RENDERER_ACCELERATED;
  int windowFlags = 0;

  window.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINWIDTH*SCALE, WINHEIGHT*SCALE, windowFlags);
  if (!window.window) {
    throwError("SDL WINDOW");
  }

  //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  window.renderer = SDL_CreateRenderer(window.window, -1, rendererFlags);
  if (!window.renderer) {
    throwError("SDL RENDERER");
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  // fully initialised!
}

void cleanup(void) {
  SDL_DestroyRenderer(window.renderer);
  SDL_DestroyWindow(window.window);
  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *loadTexture(char *filename) {
  SDL_Texture *texture;
  texture = IMG_LoadTexture(window.renderer, filename);
  return texture;
}

void blitCropped(SDL_Texture *texture, int x, int y, int w, int h, int cx, int cy, int cw, int ch) {
  if (y+h < 0 || x+w < 0 || y > WINHEIGHT*SCALE || x > WINWIDTH*SCALE) return;
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_Rect src;
  src.x = cx;
  src.y = cy;
  src.w = cw;
  src.h = ch;
  SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
  SDL_RenderCopy(window.renderer, texture, &src, &dest);
}

void blitExCropped(SDL_Texture *texture, int x, int y, int w, int h, int cx, int cy, int cw, int ch, double angle, SDL_Point center, SDL_RendererFlip flip) {
  if (y+h < 0 || x+w < 0 || y > WINHEIGHT*SCALE || x > WINWIDTH*SCALE) return;
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_Rect src;
  src.x = cx;
  src.y = cy;
  src.w = cw;
  src.h = ch;
  SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
  SDL_RenderCopyEx(window.renderer, texture, &src, &dest, angle, &center, flip);
}

void blit(SDL_Texture *texture, int x, int y, int w, int h) {
  // check if out of bounds, if is out of bounds, don't render.
  // it'd be pointless - you can't even see it
  if (y+h < 0 || x+w < 0 || y > WINHEIGHT*SCALE || x > WINWIDTH*SCALE) return;
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
  SDL_RenderCopy(window.renderer, texture, NULL, &dest);
}

// drawing post init

void draw(void) {
  SDL_SetRenderDrawColor(window.renderer, BGR, BGG, BGB, 255);
  SDL_RenderClear(window.renderer);
}

void present(void) {
  SDL_RenderPresent(window.renderer);
}
