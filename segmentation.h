#ifndef _SEG_
#define _SEG_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void binarisation(SDL_Surface* image);

SDL_Surface **SurfaceSplit(SDL_Surface *img, int histo[], int *ref);

SDL_Surface **SurfaceCharacter(SDL_Surface **lignes, int *histo[], int *h, int *w);

int *HistoMake(SDL_Surface *image, int vert);

#endif
