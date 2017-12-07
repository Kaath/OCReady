#ifndef _SDL_OP_
#define _SDL_OP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "pixel_operations.h"
#include "segmentation.h"
#include "Sobel.h"

void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface* LoadImage(const char *path);
SDL_Surface* display_image(SDL_Window *win, SDL_Surface *img);

#endif
