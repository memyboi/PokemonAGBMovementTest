#include <stdbool.h>

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "window.h"
#include "defs.h"
#include "object.h"

Player player;
Camera cam;

AnimatedTile test;
Tile grasspatch;

extern int framecount;

void initialiseCamera(void) {
  memset(&cam, 0, sizeof(Camera));
  cam.x = 0;
  cam.y = 0;
  cam.trackPlayer = true;
}

void initialisePlayer(void) {
  memset(&player, 0, sizeof(Player));
  player.w = 16;
  player.h = 19;
  player.x = (WINWIDTH*SCALE) / 2 - (player.w*SCALE) / 2;
  player.y = (WINHEIGHT*SCALE) / 2 - (player.h*SCALE) / 2;

  player.relativeX = 16*SCALE;
  player.relativeY = 16*SCALE;

  player.up = false;
  player.down = false;
  player.left = false;
  player.right = false;
  player.sprint = false;
  player.snapped = false;

  player.animCount = 0;
  player.moveType = 0;
  // index:
  // 0 - walk
  // 1 - run
  player.animFrame = 0;
  // index :
  // 0 - stand
  // 1 - left arm front
  // 2 - right arm front
  player.animType = 0;
  // index:
  // 0 - walk front
  // 1 - walk back
  // 2 - walk left
  player.animFlip = false;

  player.gender = false;

  player.texture = loadTexture("assets/player.png");
}

void initialiseTestSquare(void) {
  SDL_Texture *basictiles = loadTexture("assets/basictiles.png");
  grasspatch.w = 16;
  grasspatch.h = 16;
  grasspatch.x = ((WINWIDTH*SCALE) / 2 - (grasspatch.w*SCALE) / 2)-(16*SCALE);
  grasspatch.y = ((WINHEIGHT*SCALE) / 2 - (grasspatch.h*SCALE) / 2)-(16*SCALE);
  grasspatch.srcx = 6;
  grasspatch.srcy = 64;
  grasspatch.srcw = 16;
  grasspatch.srch = 16;
  grasspatch.copyTileX = 4;
  grasspatch.copyTileY = 4;
  grasspatch.texture = basictiles;

  test.w = 16;
  test.h = 16;
  test.x = ((WINWIDTH*SCALE) / 2 - (test.w*SCALE) / 2)+(16*5*SCALE);
  test.y = ((WINHEIGHT*SCALE) / 2 - (test.h*SCALE) / 2);
  test.srcx = 4;
  test.srcy = 3;
  test.srcw = 16;
  test.srch = 16;
  test.copyTileX = 5;
  test.copyTileY = 5;
  test.frames = 8; //assuming all tiles are side by side with the same gap
  test.jump = 17;
  test.speed = 16;
  test.texture = basictiles;
}

void renderTile(Tile *tile) {
  for (int ii = 0; ii < tile->copyTileY+1; ii++) {
    for (int i = 0; i < tile->copyTileX+1; i++) {
      blitCropped(tile->texture, tile->x-cam.x+(i*tile->w*SCALE), tile->y-cam.y+(ii*tile->h*SCALE), tile->w*SCALE, tile->h*SCALE, tile->srcx, tile->srcy, tile->srcw, tile->srch);
    }
  }
}

void renderAnimatedTile(AnimatedTile *tile) {
  int frame = (framecount/tile->speed) % tile->frames;
  for (int ii = 0; ii < tile->copyTileY+1; ii++) {
    for (int i = 0; i < tile->copyTileX+1; i++) {
      blitCropped(tile->texture, tile->x-cam.x+(i*tile->w*SCALE), tile->y-cam.y+(ii*tile->h*SCALE), tile->w*SCALE, tile->h*SCALE, tile->srcx + (frame*tile->jump), tile->srcy, tile->srcw, tile->srch);
    }
  }
}

void renderTiles(void) {
  renderTile(&grasspatch);
  renderAnimatedTile(&test);
}

void renderPlayer(void) {
  bool lock = false;
  bool moving;
  if (player.relativeX % (GRIDX) != 0 || player.relativeY % (GRIDY) != 0) {
    player.snapped = true;
    moving = true;
  } else {
    player.snapped = false;
    if (player.up) {
      moving = true;
      player.animFlip = false;
      player.animType = 1;
    } else if (player.down) {
      moving = true;
      player.animFlip = false;
      player.animType = 0;
    } else if (player.left) {
      moving = true;
      player.animFlip = false;
      player.animType = 2;
    } else if (player.right) {
      moving = true;
      player.animFlip = true;
      player.animType = 2;
    } else {
      moving = false;
    }
  }

  int speed = 1*SCALE*(player.sprint+1);

  if (moving || player.snapped) {
    switch (player.animType) {
      case 0:
        //move cam down
        player.relativeY += speed;
        break;
      
      case 1:
        //move cam up
        player.relativeY -= speed;
        break;

      case 2:
        if (player.animFlip) {
          //move cam right
          player.relativeX += speed;
        } else {
          //move cam left
          player.relativeX -= speed;
        }
        break;
      
      default:
        break;
    }
  }

  if (moving) {
  //if (moving || cam.x % 50 != 0 || cam.y % 50 != 0 ) {
    lock = false;
    player.moveType = player.sprint;
    if (player.moveType == 0) {
      float decider = (player.animCount % 30);
      if (decider <= 7.5) player.animFrame = 0;
      if (decider > 7.5 && decider <= 15) player.animFrame = 1;
      if (decider > 15 && decider <= 22.5) player.animFrame = 0;
      if (decider > 22.5) player.animFrame = 2;
    } else if (player.moveType == 1) {
      float decider = (player.animCount % 15);
      if (decider <= 3.75) player.animFrame = 0;
      if (decider > 3.75 && decider <= 7.5) player.animFrame = 1;
      if (decider > 7.5 && decider <= 11.25) player.animFrame = 0;
      if (decider > 11.25) player.animFrame = 2;
    }
  } else {
    player.animCount = 0;
    player.animFrame = 0;
    player.moveType = 0;
  }
  int XPOS = 24;
  int YPOS = 0;
  int extraPadding = 0;

  if (player.animFrame == 1) XPOS = 8;
  if (player.animFrame == 2) XPOS = 40;
  switch (player.animType) {
    case 0:
      YPOS = 36;
      break;
    
    case 1:
      YPOS = 68;
      break;
    
    case 2:
      YPOS = 100;
    
    default:
      break;
  }

  if (cam.trackPlayer) {
    cam.x = player.relativeX;
    cam.y = player.relativeY;
  }

  player.x = (player.relativeX + (WINWIDTH*SCALE) / 2 - (player.w*SCALE) / 2) - cam.x;
  player.y = (player.relativeY + (WINHEIGHT*SCALE) / 2 - (player.h*SCALE) / 2) - cam.y;

  if (player.gender) YPOS += 216;
  if (player.moveType == 1) XPOS += 56;
  if (player.gender && player.moveType == 1 && player.animType == 0) extraPadding += 2;
  if (player.animFlip) {
    SDL_Point point;
    point.x = 0;
    point.y = 0;
    blitExCropped(player.texture, player.x, player.y-extraPadding*SCALE, player.w*SCALE, player.h*SCALE+extraPadding*SCALE, XPOS, YPOS-extraPadding, player.w, player.h+1+extraPadding, 0.0, point, SDL_FLIP_HORIZONTAL);
  } else {
    blitCropped(player.texture, player.x, player.y-extraPadding*SCALE, player.w*SCALE, player.h*SCALE+extraPadding*SCALE, XPOS, YPOS-extraPadding, player.w, player.h+1+extraPadding);
  }
  if (!lock) player.animCount++;
}

void initialiseObjects(void) {
  initialiseCamera();
  initialiseTestSquare();
  initialisePlayer();
}

void renderObjects(void) {
  renderTiles();
  renderPlayer();
}