#ifndef _SOBEL_H_
#define _SOBEL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "pixel_operations.h"
#include "segmentation.h"
#include "sdl_OP.h"

int* SobelH(SDL_Surface* img);

int* SobelV(SDL_Surface* img);

SDL_Surface* Sobel(SDL_Surface* img);

#endif
