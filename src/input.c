#include "SDL2/SDL_events.h"
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_scancode.h"
#include "object.h" 
#include "defs.h"

extern Player player;
extern Camera cam;

void setPlayerMovement(int moveType, bool down) {
  // 0 - down, 1 - up, 2 - left, 3 - right, 4 - run
  switch (moveType) {
    case 0:
      player.down = down;
      break;

    case 1:
      player.up = down;
      break;
    
    case 2:
      player.left = down;
      break;

    case 3:
      player.right = down;
      break;
    
    case 4:
      player.sprint = down;
      break;
  }
}

void handleKeyDown(SDL_KeyboardEvent *event) {
  switch (event->keysym.scancode) {
    case SDL_SCANCODE_R:
      cam.trackPlayer = !cam.trackPlayer;
      break;

    case SDL_SCANCODE_T:
      // can't stop yourself from going crazy in a completely blank void? Well, introducing to you:
      player.relativeX = 16*SCALE;
      player.relativeY = 16*SCALE;
      break;

    case SDL_SCANCODE_UP:
      setPlayerMovement(1, true);
      break;

    case SDL_SCANCODE_W:
      setPlayerMovement(1, true);
      break;

    case SDL_SCANCODE_DOWN:
      setPlayerMovement(0, true);
      break;

    case SDL_SCANCODE_S:
      setPlayerMovement(0, true);
      break;

    case SDL_SCANCODE_LEFT:
      setPlayerMovement(2, true);
      break;

    case SDL_SCANCODE_A:
      setPlayerMovement(2, true);
      break;

    case SDL_SCANCODE_RIGHT:
      setPlayerMovement(3, true);
      break;

    case SDL_SCANCODE_D:
      setPlayerMovement(3, true);
      break;

    case SDL_SCANCODE_G:
      player.gender = !player.gender;
      break;

    case SDL_SCANCODE_LSHIFT:
      setPlayerMovement(4, true);
      break;

    default:
      break;
  }
}

void handleKeyUp(SDL_KeyboardEvent *event) {
  switch (event->keysym.scancode) {
    case SDL_SCANCODE_LSHIFT:
      setPlayerMovement(4, false);
      break;

    case SDL_SCANCODE_UP:
      setPlayerMovement(1, false);
      break;

    case SDL_SCANCODE_W:
      setPlayerMovement(1, false);
      break;

    case SDL_SCANCODE_DOWN:
      setPlayerMovement(0, false);
      break;

    case SDL_SCANCODE_S:
      setPlayerMovement(0, false);
      break;

    case SDL_SCANCODE_LEFT:
      setPlayerMovement(2, false);
      break;

    case SDL_SCANCODE_A:
      setPlayerMovement(2, false);
      break;

    case SDL_SCANCODE_RIGHT:
      setPlayerMovement(3, false);
      break;

    case SDL_SCANCODE_D:
      setPlayerMovement(3, false);
      break;
    
    default:
      break;
  }
}

void getEvents(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
        break;

      case SDL_KEYDOWN:
        handleKeyDown(&event.key);
        break;

      case SDL_KEYUP:
        handleKeyUp(&event.key);
        break;

      default:
        break;
    }
  }
}
