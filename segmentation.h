#ifndef _SEG_
#define _SEG_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void binarisation(SDL_Surface* image);

/*SDL_Surface ***/void SurfaceSplit(SDL_Surface *img, int histo[]);//, int *ref);

int *HistoHorizontal(SDL_Surface *image);

#endif
