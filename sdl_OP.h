#ifndef _SDL_OP_
#define _SDL_OP_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface* LoadImage(const char *path);
SDL_Surface* display_image(SDL_Surface *img);

#endif
