//   TODO:
// check for any memory leaks (im new to C)
// the memory leak program is valgrind

#include <stdbool.h>
#include <stdlib.h>

#include "SDL2/SDL_timer.h"
#include "window.h"
#include "defs.h"
#include "input.h"
#include "object.h"

extern Window window;
extern Player player;
int framecount = 0;

bool greenscreen;

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[]) {
  memset(&window, 0, sizeof(Window));
  memset(&player, 0, sizeof(Player));
  initialise(); // initialise SDL
  atexit(cleanup); // free SDL on exit 

  initialiseObjects();

  long then = SDL_GetTicks();
  float remainder = 0;
  
  while(1) {
    draw();
    getEvents();
    renderObjects();
    capFrameRate(&then, &remainder);
    present();
    framecount++;
  }
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}