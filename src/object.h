#include "SDL2/SDL_render.h"
#include <stdbool.h>

void initialiseObjects(void);
void renderObjects(void);

typedef struct {
  int x;
  int y;
  int w;
  int h;

  int relativeX;
  int relativeY;

  int animCount;
  int animFrame;
  int animType;
  bool animFlip;
  int moveType;
  bool playerMoving;
  bool awaitingMovement;

  bool gender; //true = female

  bool up;
  bool down;
  bool left;
  bool right;
  bool sprint;
  bool snapped;
  
  SDL_Texture *texture;
} Player;

typedef struct {
  int x;
  int y;
  bool trackPlayer;
} Camera;

typedef struct {
  int x;
  int y;
  int w;
  int h;
  
  SDL_Texture *texture;
} Entity;

typedef struct {
  int x;
  int y;
  int w;
  int h;

  int srcx;
  int srcy;
  int srcw;
  int srch;

  int copyTileX;
  int copyTileY;

  SDL_Texture *texture;
} Tile;

typedef struct {
  int x;
  int y;
  int w;
  int h;

  int srcx;
  int srcy;
  int srcw;
  int srch;

  int frames; //assuming all tiles are side by side with the same gap
  int jump;
  int speed;

  int copyTileX;
  int copyTileY;

  SDL_Texture *texture;
} AnimatedTile;