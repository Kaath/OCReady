#ifndef _SEG_
#define _SEG_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void binarisation(SDL_Surface* image);

SDL_Surface **SurfaceSplit(SDL_Surface *img, int histo[], int *ref);

int *HistoMake(SDL_Surface *image, int vert);

#endif
