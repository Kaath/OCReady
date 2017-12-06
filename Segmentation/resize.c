# include "resize.h"

SDL_Surface *resize(SDL_Surface *img, int w, int h) {
    SDL_Surface *res = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            putpixel(res, i, j, getpixel(img, j*(img->w/28.0), i*(img->h/28.0)));
        }
    }
    return res;
}
