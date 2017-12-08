#ifndef _SEG_
#define _SEG_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "pixel_operations.h"
#include "Sobel.h"
#include "sdl_OP.h"
#include "resize.h"

void binarisation(SDL_Surface* image);

SDL_Surface **SurfaceSplit(SDL_Surface *img, int histo[], int *ref);

SDL_Surface **characterSplit(SDL_Surface **lignes, int *histo[], int *ref);

int *HistoMake(SDL_Surface *image, int vert);

#endif
