# include "resize.h"

SDL_Surface *resize(SDL_Surface *img, SDL_Rect rsrc, int w, int h) {
    SDL_Surface *res = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    //SDL_Rect rect = {0,0,28,28};
    SDL_BlitScaled(img, &rsrc, res, NULL);
    return res;
}
