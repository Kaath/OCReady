#ifndef _SOBEL_H_
#define _SOBEL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int* SobelH(SDL_Surface* img);

int* SobelV(SDL_Surface* img);

SDL_Surface* Sobel(SDL_Surface* img);

#endif
