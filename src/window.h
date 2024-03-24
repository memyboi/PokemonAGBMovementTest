#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

void initialise(void);
void draw(void);
void present(void);
void cleanup(void);
SDL_Texture *loadTexture(char *filename);
void blit(SDL_Texture *texture, int x, int y, int w, int h);
void blitCropped(SDL_Texture *texture, int x, int y, int w, int h, int cx, int cy, int cw, int ch);
void blitExCropped(SDL_Texture *texture, int x, int y, int w, int h, int cx, int cy, int cw, int ch, double angle, SDL_Point center, SDL_RendererFlip flip);

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Window;
