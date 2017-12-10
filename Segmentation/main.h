#ifndef _SEG_MAIN_H_
#define _SEG_MAIN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "resize.h"
#include "pixel_operations.h"
#include "segmentation.h"
#include "Sobel.h"
#include "sdl_OP.h"

float **decoupe(char *path, int *nbcharacters);

#endif
